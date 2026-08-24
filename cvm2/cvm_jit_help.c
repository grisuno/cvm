/**
 * @file cvm_jit_help.c
 * @brief Shared helper implementations for the CVM JIT compiler.
 * @license GPL-2.0-or-later
 *
 * These functions are called by JIT-compiled native code.  They
 * implement the same semantics as the interpreter's switch cases,
 * but are standalone C functions with a clean ABI.
 */
#include "cvm_jit_help.h"
#include "cvm_jit.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CVM_HEAP_ALIGN 16

/* ------------------------------------------------------------------ */
/*  Field offset computation                                           */
/* ------------------------------------------------------------------ */

void cvm_jit_offsets_init(CvmJitOffsets *o) {
    o->slots                = offsetof(CvmState, slots);
    o->sp                   = offsetof(CvmState, sp);
    o->frames               = offsetof(CvmState, frames);
    o->frame_count          = offsetof(CvmState, frame_count);
    o->globals              = offsetof(CvmState, globals);
    o->heap                 = offsetof(CvmState, heap);
    o->heap_used            = offsetof(CvmState, heap_used);
    o->code                 = offsetof(CvmState, code);
    o->code_size            = offsetof(CvmState, code_size);
    o->ip                   = offsetof(CvmState, ip);
    o->running              = offsetof(CvmState, running);
    o->exit_code            = offsetof(CvmState, exit_code);
    o->natives              = offsetof(CvmState, natives);
    o->native_map           = offsetof(CvmState, native_map);
    o->num_module_natives   = offsetof(CvmState, num_module_natives);
    o->funcs                = offsetof(CvmState, funcs);
    o->num_funcs            = offsetof(CvmState, num_funcs);
}

/* ------------------------------------------------------------------ */
/*  Internal helpers (shared with interpreter logic)                    */
/* ------------------------------------------------------------------ */

static void *xmal(size_t s) {
    void *p = malloc(s);
    if (!p) { fprintf(stderr, "cvm jit: oom\n"); exit(1); }
    return p;
}

static void *xcal(size_t n, size_t s) {
    void *p = calloc(n, s);
    if (!p) { fprintf(stderr, "cvm jit: oom\n"); exit(1); }
    return p;
}

static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      uint32_t func_idx) {
    if (vm->frame_count >= vm->max_frames) return CVM_ERR_FRAME_OVER;
    if (num_locals > vm->config.max_locals_per_frame) return CVM_ERR_BOUNDS;
    CvmFrame *f = &vm->frames[vm->frame_count];
    f->capacity = num_locals > 0 ? num_locals : 1;
    f->slots = (uint64_t *)xcal(f->capacity, sizeof(uint64_t));
    f->return_ip = return_ip;
    f->func_idx = func_idx;
    vm->frame_count++;
    return CVM_OK;
}

static void pop_frame(CvmState *vm) {
    if (!vm->frame_count) return;
    vm->frame_count--;
    free(vm->frames[vm->frame_count].slots);
    vm->frames[vm->frame_count].slots = NULL;
}

static CvmFrame *cur_frame(CvmState *vm) {
    return vm->frame_count > 0 ? &vm->frames[vm->frame_count - 1] : NULL;
}

static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len) {
    if (len == 0 || base == NULL) return 0;
    uint64_t b = (uint64_t)(uintptr_t)base;
    if (a < b) return 0;
    if (s > len) return 0;
    return a - b <= len - s;
}

static int mem_valid(const CvmState *vm, uint64_t a, size_t s) {
    if (range_valid(a, s, vm->heap, vm->heap_size)) return 1;
    if (range_valid(a, s, vm->globals, vm->globals_size)) return 1;
    if (range_valid(a, s, (const uint8_t *)vm->string_pool, vm->string_pool_size)) return 1;
    for (size_t i = 0; i < vm->frame_count; i++) {
        const CvmFrame *f = &vm->frames[i];
        if (range_valid(a, s, (const uint8_t *)f->slots, f->capacity * sizeof(uint64_t)))
            return 1;
    }
    return 0;
}

static uint64_t heap_alloc(CvmState *vm, size_t s) {
    size_t al = (s + CVM_HEAP_ALIGN - 1) & ~(size_t)(CVM_HEAP_ALIGN - 1);
    if (vm->heap_used + al > vm->heap_size) return 0;
    uint64_t a = (uint64_t)(uintptr_t)(vm->heap + vm->heap_used);
    vm->heap_used += al;
    return a;
}

static int find_native(const CvmState *vm, const char *name) {
    for (size_t i = 0; i < vm->num_natives; i++)
        if (strcmp(vm->natives[i].name, name) == 0) return (int)i;
    return -1;
}

/* ------------------------------------------------------------------ */
/*  Stack push/pop (operand stack)                                     */
/* ------------------------------------------------------------------ */

static int jit_vp(CvmState *vm, uint64_t v) {
    if (vm->sp >= vm->capacity) return CVM_ERR_STACK_OVER;
    vm->slots[vm->sp++] = v;
    return CVM_OK;
}

static int jit_vo(CvmState *vm, uint64_t *v) {
    if (vm->sp == 0) return CVM_ERR_STACK_UNDER;
    *v = vm->slots[--vm->sp];
    return CVM_OK;
}

/* ------------------------------------------------------------------ */
/*  JIT function entry/exit                                            */
/* ------------------------------------------------------------------ */

uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx) {
    if (func_idx >= vm->num_funcs) {
        vm->running = 0;
        vm->exit_code = CVM_ERR_BAD_FUNC;
        return NULL;
    }
    return vm->code + vm->funcs[func_idx].code_off;
}

void cvm_jit_func_leave(CvmState *vm) {
    /* Nothing to do in the general case; the JIT epilogue handles
     * register restoration.  This exists for symmetry and future use. */
    (void)vm;
}

/* ------------------------------------------------------------------ */
/*  CALL                                                               */
/* ------------------------------------------------------------------ */

int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc) {
    if (func_idx >= vm->num_funcs) return CVM_ERR_BAD_FUNC;
    CvmFuncEntry *fe = &vm->funcs[func_idx];
    int rc = push_frame(vm, fe->num_locals > 0 ? fe->num_locals : 16,
                        vm->ip, func_idx);
    if (rc) return rc;
    CvmFrame *f = cur_frame(vm);
    for (int i = (int)argc - 1; i >= 0; i--) {
        uint64_t a;
        rc = jit_vo(vm, &a);
        if (rc) return rc;
        f->slots[i] = a;
    }
    vm->ip = fe->code_off;
    return CVM_OK;
}

/* ------------------------------------------------------------------ */
/*  RET                                                                */
/* ------------------------------------------------------------------ */

int cvm_jit_ret(CvmState *vm, uint64_t retval) {
    CvmFrame *f = cur_frame(vm);
    if (f && f->return_ip != 0) {
        size_t ret_ip = f->return_ip;
        pop_frame(vm);
        vm->ip = ret_ip;
        return jit_vp(vm, retval);
    }
    vm->running = 0;
    vm->exit_code = (int64_t)retval;
    return 0;
}

/* ------------------------------------------------------------------ */
/*  CALL_NATIVE                                                        */
/* ------------------------------------------------------------------ */

int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc) {
    if (native_idx >= vm->num_module_natives) return CVM_ERR_BAD_NATIVE;
    int32_t host = vm->native_map[native_idx];
    if (host < 0) return CVM_ERR_NOMATCH;
    if (argc > CVM_MAX_NARGS) return CVM_ERR_BOUNDS;
    uint64_t args[CVM_MAX_NARGS];
    for (int i = (int)argc - 1; i >= 0; i--) {
        int rc = jit_vo(vm, &args[i]);
        if (rc) return rc;
    }
    CvmNativeFn fn = vm->natives[host].fn;
    int64_t res = fn(vm, (int)argc, args);
    if (vm->running) return jit_vp(vm, (uint64_t)res);
    return CVM_OK;
}

/* ------------------------------------------------------------------ */
/*  Memory check                                                       */
/* ------------------------------------------------------------------ */

int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size) {
    return mem_valid(vm, addr, size);
}

/* ------------------------------------------------------------------ */
/*  ALLOC                                                              */
/* ------------------------------------------------------------------ */

uint64_t cvm_jit_alloc(CvmState *vm, size_t size) {
    return heap_alloc(vm, size);
}

/* ------------------------------------------------------------------ */
/*  SYSCALL                                                            */
/* ------------------------------------------------------------------ */

int cvm_jit_syscall(CvmState *vm, uint8_t sn, uint8_t argc) {
    if (argc > CVM_MAX_SARGS) return CVM_ERR_BOUNDS;
    uint64_t args[CVM_MAX_SARGS];
    for (int i = (int)argc - 1; i >= 0; i--) {
        int rc = jit_vo(vm, &args[i]);
        if (rc) return rc;
    }
    int64_t res = -1;
    if (sn == CVM_SYS_EXIT) {
        vm->running = 0;
        vm->exit_code = (int64_t)args[0];
        res = (int64_t)args[0];
    }
#ifdef CVM_STANDALONE
    else if (sn == CVM_SYS_WRITE)
        res = (int64_t)write((int)args[0], (const void *)(uintptr_t)args[1], (size_t)args[2]);
    else if (sn == CVM_SYS_READ)
        res = (int64_t)read((int)args[0], (void *)(uintptr_t)args[1], (size_t)args[2]);
#endif
    if (vm->running) return jit_vp(vm, (uint64_t)res);
    return CVM_OK;
}

/* ------------------------------------------------------------------ */
/*  Error handling                                                     */
/* ------------------------------------------------------------------ */

void cvm_jit_error(CvmState *vm, int error_code) {
    vm->running = 0;
    vm->exit_code = (int64_t)error_code;
}
