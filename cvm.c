/**
 * @file cvm.c
 * @brief CVM interpreter implementation.
 * @license GPL-2.0-or-later
 */
#include "cvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CVM_DEF_STACK       65536
#define CVM_DEF_FRAMES      4096
#define CVM_DEF_LOCALS      512
#define CVM_DEF_HEAP        (16 * 1024 * 1024)
#define CVM_DEF_GLOBALS     4096
#define CVM_DEF_FUNCS       4096
#define CVM_DEF_NATIVES     512
#define CVM_DEF_CODE        (64 * 1024 * 1024)
#define CVM_HEAP_ALIGN      16
#define CVM_SHIFT_MASK      63
#define CVM_MAX_NARGS       16
#define CVM_MAX_SARGS       6
#define CVM_SYS_WRITE       1
#define CVM_SYS_EXIT        60

static void *xmal(size_t s) {
    void *p = malloc(s);
    if (!p) { fprintf(stderr, "cvm: oom\n"); exit(1); }
    return p;
}

static void *xcal(size_t n, size_t s) {
    void *p = calloc(n, s);
    if (!p) { fprintf(stderr, "cvm: oom\n"); exit(1); }
    return p;
}

CvmConfig cvm_config_default(void) {
    CvmConfig c;
    c.stack_capacity       = CVM_DEF_STACK;
    c.max_frames           = CVM_DEF_FRAMES;
    c.max_locals_per_frame = CVM_DEF_LOCALS;
    c.heap_size            = CVM_DEF_HEAP;
    c.max_globals          = CVM_DEF_GLOBALS;
    c.max_functions        = CVM_DEF_FUNCS;
    c.max_natives          = CVM_DEF_NATIVES;
    c.max_code_size        = CVM_DEF_CODE;
    c.trace_enabled        = 0;
    return c;
}

CvmState *cvm_create(const CvmConfig *config) {
    CvmConfig cfg = config ? *config : cvm_config_default();
    CvmState *vm = (CvmState *)xcal(1, sizeof(CvmState));
    vm->config = cfg;
    vm->slots = (uint64_t *)xcal(cfg.stack_capacity, sizeof(uint64_t));
    vm->capacity = cfg.stack_capacity;
    vm->sp = 0;
    vm->frames = (CvmFrame *)xcal(cfg.max_frames, sizeof(CvmFrame));
    vm->frame_count = 0;
    vm->max_frames = cfg.max_frames;
    vm->globals = (uint64_t *)xcal(cfg.max_globals, sizeof(uint64_t));
    vm->num_globals = 0;
    vm->heap = (uint8_t *)xcal(1, cfg.heap_size);
    vm->heap_size = cfg.heap_size;
    vm->heap_used = 0;
    vm->code = NULL;
    vm->code_size = 0;
    vm->ip = 0;
    vm->running = 0;
    vm->exit_code = 0;
    vm->instr_count = 0;
    vm->natives = (CvmNativeUnion *)xcal(cfg.max_natives, sizeof(CvmNativeUnion));
    vm->num_natives = 0;
    vm->string_pool = NULL;
    vm->string_pool_size = 0;
    vm->funcs = NULL;
    vm->num_funcs = 0;
    vm->entry_func = 0;
    return vm;
}

void cvm_destroy(CvmState *vm) {
    if (!vm) return;
    free(vm->slots);
    for (size_t i = 0; i < vm->frame_count; i++) {
        free(vm->frames[i].slots);
    }
    free(vm->frames);
    free(vm->globals);
    free(vm->heap);
    free(vm->code);
    free(vm->natives);
    free(vm->string_pool);
    free(vm->funcs);
    free(vm);
}

const char *cvm_strerror(int e) {
    switch (e) {
        case CVM_OK:              return "success";
        case CVM_ERR_ALLOC:       return "allocation failure";
        case CVM_ERR_STACK_OVER:  return "operand stack overflow";
        case CVM_ERR_STACK_UNDER: return "operand stack underflow";
        case CVM_ERR_BAD_OPCODE:  return "invalid opcode";
        case CVM_ERR_BAD_MODULE:  return "malformed module";
        case CVM_ERR_BAD_MAGIC:   return "invalid module magic";
        case CVM_ERR_BAD_VERSION: return "unsupported module version";
        case CVM_ERR_DIV_ZERO:    return "division by zero";
        case CVM_ERR_BAD_FUNC:    return "invalid function index";
        case CVM_ERR_BAD_NATIVE:  return "invalid native function";
        case CVM_ERR_BAD_ADDR:    return "invalid memory address";
        case CVM_ERR_FRAME_OVER:  return "call frame overflow";
        case CVM_ERR_HEAP_OVER:   return "heap exhaustion";
        case CVM_ERR_IO:          return "I/O error";
        case CVM_ERR_BOUNDS:      return "bounds check failure";
        default:                  return "unknown error";
    }
}

static int vp(CvmState *vm, uint64_t v) {
    if (vm->sp >= vm->capacity) return CVM_ERR_STACK_OVER;
    vm->slots[vm->sp++] = v;
    return CVM_OK;
}

static int vo(CvmState *vm, uint64_t *v) {
    if (vm->sp == 0) return CVM_ERR_STACK_UNDER;
    *v = vm->slots[--vm->sp];
    return CVM_OK;
}

static int r8(CvmState *vm, uint8_t *o) {
    if (vm->ip >= vm->code_size) return CVM_ERR_BOUNDS;
    *o = vm->code[vm->ip++];
    return CVM_OK;
}

static int r32(CvmState *vm, uint32_t *o) {
    if (vm->ip + 4 > vm->code_size) return CVM_ERR_BOUNDS;
    *o = (uint32_t)vm->code[vm->ip]
       | ((uint32_t)vm->code[vm->ip+1] << 8)
       | ((uint32_t)vm->code[vm->ip+2] << 16)
       | ((uint32_t)vm->code[vm->ip+3] << 24);
    vm->ip += 4;
    return CVM_OK;
}

static int ri32(CvmState *vm, int32_t *o) {
    uint32_t u;
    int rc = r32(vm, &u);
    if (rc) return rc;
    *o = (int32_t)u;
    return CVM_OK;
}

static int r64(CvmState *vm, uint64_t *o) {
    if (vm->ip + 8 > vm->code_size) return CVM_ERR_BOUNDS;
    uint64_t v = 0;
    for (int i = 0; i < 8; i++)
        v |= (uint64_t)vm->code[vm->ip+i] << (i*8);
    vm->ip += 8;
    *o = v;
    return CVM_OK;
}

static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip) {
    if (vm->frame_count >= vm->max_frames) return CVM_ERR_FRAME_OVER;
    if (num_locals > vm->config.max_locals_per_frame) return CVM_ERR_BOUNDS;
    CvmFrame *f = &vm->frames[vm->frame_count];
    f->capacity = num_locals > 0 ? num_locals : 1;
    f->slots = (uint64_t *)xcal(f->capacity, sizeof(uint64_t));
    f->return_ip = return_ip;
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
    return vm->frame_count > 0 ? &vm->frames[vm->frame_count-1] : NULL;
}

static int heap_valid(CvmState *vm, uint64_t a, size_t s) {
    uint64_t b = (uint64_t)(uintptr_t)vm->heap;
    return a >= b && a + s <= b + vm->heap_size;
}

static uint64_t heap_alloc(CvmState *vm, size_t s) {
    size_t al = (s + CVM_HEAP_ALIGN - 1) & ~(size_t)(CVM_HEAP_ALIGN - 1);
    if (vm->heap_used + al > vm->heap_size) return 0;
    uint64_t a = (uint64_t)(uintptr_t)(vm->heap + vm->heap_used);
    vm->heap_used += al;
    return a;
}

int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn) {
    (void)name;
    if (vm->num_natives >= vm->config.max_natives) return CVM_ERR_BOUNDS;
    CvmNativeUnion u;
    u.fn = (int64_t (*)(void*, int, uint64_t*))fn;
    vm->natives[vm->num_natives] = u;
    vm->num_natives++;
    return CVM_OK;
}

static int64_t native_write(CvmState *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return -1;
    return (int64_t)write((int)av[0], (const void *)(uintptr_t)av[1], (size_t)av[2]);
}

static int64_t native_exit(CvmState *vm, int ac, uint64_t *av) {
    (void)ac;
    vm->running = 0;
    vm->exit_code = (int64_t)av[0];
    return 0;
}

static int64_t native_putchar(CvmState *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    unsigned char c = (unsigned char)av[0];
    return (int64_t)write(1, &c, 1);
}

static void register_defaults(CvmState *vm) {
    cvm_register_native(vm, "write", native_write);
    cvm_register_native(vm, "exit", native_exit);
    cvm_register_native(vm, "putchar", native_putchar);
}

static uint32_t rl32(const uint8_t *p) {
    return (uint32_t)p[0] | ((uint32_t)p[1]<<8)
         | ((uint32_t)p[2]<<16) | ((uint32_t)p[3]<<24);
}

int cvm_load_module(CvmState *vm, const uint8_t *d, size_t sz) {
    if (sz < CVM_MODULE_HEADER_SIZE) return CVM_ERR_BAD_MODULE;
    if (d[0]!=CVM_MAGIC_0 || d[1]!=CVM_MAGIC_1 ||
        d[2]!=CVM_MAGIC_2 || d[3]!=CVM_MAGIC_3) return CVM_ERR_BAD_MAGIC;
    if ((uint16_t)(d[4]|(d[5]<<8)) != CVM_VERSION_MAJOR) return CVM_ERR_BAD_VERSION;

    uint32_t nf = rl32(d+8);
    uint32_t ng = rl32(d+12);
    uint32_t nn = rl32(d+16);
    uint32_t ns = rl32(d+20);
    uint32_t cs = rl32(d+24);
    uint32_t sp = rl32(d+28);
    uint32_t ef = rl32(d+32);

    if (nf > vm->config.max_functions) return CVM_ERR_BAD_MODULE;
    if (ng > vm->config.max_globals) return CVM_ERR_BAD_MODULE;
    if (nn > vm->config.max_natives) return CVM_ERR_BAD_MODULE;
    if (cs > vm->config.max_code_size) return CVM_ERR_BAD_MODULE;

    size_t ft = (size_t)nf * CVM_FUNC_ENTRY_SIZE;
    size_t gt = (size_t)ng * 12;
    size_t nt = (size_t)nn * 4;
    size_t off = CVM_MODULE_HEADER_SIZE;

    if (off + ft + gt + nt + cs + sp > sz) return CVM_ERR_BAD_MODULE;

    vm->funcs = (CvmFuncEntry *)xcal(nf > 0 ? nf : 1, sizeof(CvmFuncEntry));
    vm->num_funcs = nf;
    for (uint32_t i = 0; i < nf; i++) {
        const uint8_t *fe = d + off + (size_t)i * CVM_FUNC_ENTRY_SIZE;
        vm->funcs[i].name_off   = rl32(fe + 0);
        vm->funcs[i].code_off   = rl32(fe + 4);
        vm->funcs[i].num_locals = rl32(fe + 8);
        vm->funcs[i].argc       = rl32(fe + 12);
        vm->funcs[i].flags      = rl32(fe + 16);
    }

    size_t code_off = off + ft + gt + nt;
    vm->code = (uint8_t *)xmal(cs > 0 ? cs : 1);
    vm->code_size = cs;
    memcpy(vm->code, d + code_off, cs);

    if (sp > 0) {
        vm->string_pool = (char *)xmal(sp + 1);
        memcpy(vm->string_pool, d + code_off + cs, sp);
        vm->string_pool[sp] = 0;
        vm->string_pool_size = sp;
    }

    vm->num_globals = ng;
    for (uint32_t i = 0; i < ng; i++) {
        uint64_t iv = 0;
        memcpy(&iv, d + off + ft + (size_t)i*12 + 4, 8);
        vm->globals[i] = iv;
    }

    vm->entry_func = ef;
    (void)ns;
    return CVM_OK;
}

int cvm_load_module_file(CvmState *vm, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return CVM_ERR_IO;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return CVM_ERR_IO; }
    rewind(f);
    uint8_t *buf = (uint8_t *)xmal((size_t)sz);
    size_t rd = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    if (rd != (size_t)sz) { free(buf); return CVM_ERR_IO; }
    int rc = cvm_load_module(vm, buf, (size_t)sz);
    free(buf);
    return rc;
}

int cvm_run(CvmState *vm) {
    register_defaults(vm);
    vm->running = 1;
    vm->exit_code = 0;
    vm->instr_count = 0;
    int rc = CVM_OK;

    if (vm->entry_func < vm->num_funcs) {
        vm->ip = vm->funcs[vm->entry_func].code_off;
    } else {
        vm->ip = 0;
    }

    uint32_t entry_locals = 0;
    if (vm->entry_func < vm->num_funcs) {
        entry_locals = vm->funcs[vm->entry_func].num_locals;
    }
    rc = push_frame(vm, entry_locals > 0 ? entry_locals : 16, 0);
    if (rc) return rc;

    while (vm->running) {
        uint8_t op;
        rc = r8(vm, &op);
        if (rc) break;

        if (vm->config.trace_enabled) {
            fprintf(stderr, "[%08lu] ip=%zu op=0x%02X sp=%zu fr=%zu\n",
                    (unsigned long)vm->instr_count, vm->ip-1, op,
                    vm->sp, vm->frame_count);
        }
        vm->instr_count++;

        switch (op) {
        case OP_NOP:
            break;
        case OP_PUSH_IMM64: {
            uint64_t v; rc = r64(vm, &v);
            if (!rc) rc = vp(vm, v);
            break;
        }
        case OP_PUSH_IMM32: {
            int32_t v; rc = ri32(vm, &v);
            if (!rc) rc = vp(vm, (uint64_t)(int64_t)v);
            break;
        }
        case OP_PUSH_IMM8: {
            uint8_t v; rc = r8(vm, &v);
            if (!rc) rc = vp(vm, (uint64_t)(int64_t)(int8_t)v);
            break;
        }
        case OP_PUSH_ZERO: rc = vp(vm, 0); break;
        case OP_PUSH_ONE:  rc = vp(vm, 1); break;

        case OP_PUSH_LOCAL: {
            uint32_t i; rc = r32(vm, &i); if (rc) break;
            CvmFrame *f = cur_frame(vm);
            if (!f || i >= f->capacity) { rc = CVM_ERR_BOUNDS; break; }
            rc = vp(vm, f->slots[i]);
            break;
        }
        case OP_STORE_LOCAL: {
            uint32_t i; rc = r32(vm, &i); if (rc) break;
            CvmFrame *f = cur_frame(vm);
            if (!f || i >= f->capacity) { rc = CVM_ERR_BOUNDS; break; }
            uint64_t v; rc = vo(vm, &v);
            if (!rc) f->slots[i] = v;
            break;
        }
        case OP_PUSH_GLOBAL: {
            uint32_t i; rc = r32(vm, &i); if (rc) break;
            if (i >= vm->num_globals) { rc = CVM_ERR_BOUNDS; break; }
            rc = vp(vm, vm->globals[i]);
            break;
        }
        case OP_STORE_GLOBAL: {
            uint32_t i; rc = r32(vm, &i); if (rc) break;
            if (i >= vm->num_globals) { rc = CVM_ERR_BOUNDS; break; }
            uint64_t v; rc = vo(vm, &v);
            if (!rc) vm->globals[i] = v;
            break;
        }

        case OP_ADD: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a+b); break; }
        case OP_SUB: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a-b); break; }
        case OP_MUL: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a*b); break; }
        case OP_DIV: {
            uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if ((int64_t)b==0) { rc=CVM_ERR_DIV_ZERO; break; }
            rc=vp(vm,(uint64_t)((int64_t)a/(int64_t)b));
            break;
        }
        case OP_MOD: {
            uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if ((int64_t)b==0) { rc=CVM_ERR_DIV_ZERO; break; }
            rc=vp(vm,(uint64_t)((int64_t)a%(int64_t)b));
            break;
        }
        case OP_NEG: { uint64_t a; rc=vo(vm,&a); if(!rc) rc=vp(vm,(uint64_t)(-(int64_t)a)); break; }
        case OP_AND: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a&b); break; }
        case OP_OR:  { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a|b); break; }
        case OP_XOR: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a^b); break; }
        case OP_NOT: { uint64_t a; rc=vo(vm,&a); if(!rc) rc=vp(vm,~a); break; }
        case OP_SHL: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a<<(b&CVM_SHIFT_MASK)); break; }
        case OP_SHR: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(uint64_t)((int64_t)a>>(b&CVM_SHIFT_MASK))); break; }

        case OP_CMP_EQ: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a==(int64_t)b?1:0); break; }
        case OP_CMP_NE: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a!=(int64_t)b?1:0); break; }
        case OP_CMP_LT: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a<(int64_t)b?1:0); break; }
        case OP_CMP_LE: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a<=(int64_t)b?1:0); break; }
        case OP_CMP_GT: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a>(int64_t)b?1:0); break; }
        case OP_CMP_GE: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a>=(int64_t)b?1:0); break; }
        case OP_LNOT: { uint64_t a; rc=vo(vm,&a); if(!rc) rc=vp(vm,a==0?1:0); break; }

        case OP_JMP: {
            int32_t o; rc = ri32(vm, &o); if (rc) break;
            int64_t t = (int64_t)vm->ip + o;
            if (t < 0 || (uint64_t)t > vm->code_size) { rc = CVM_ERR_BOUNDS; break; }
            vm->ip = (size_t)t;
            break;
        }
        case OP_JZ: {
            int32_t o; rc = ri32(vm, &o); if (rc) break;
            uint64_t v; rc = vo(vm, &v); if (rc) break;
            if (v == 0) {
                int64_t t = (int64_t)vm->ip + o;
                if (t < 0 || (uint64_t)t > vm->code_size) { rc = CVM_ERR_BOUNDS; break; }
                vm->ip = (size_t)t;
            }
            break;
        }
        case OP_JNZ: {
            int32_t o; rc = ri32(vm, &o); if (rc) break;
            uint64_t v; rc = vo(vm, &v); if (rc) break;
            if (v != 0) {
                int64_t t = (int64_t)vm->ip + o;
                if (t < 0 || (uint64_t)t > vm->code_size) { rc = CVM_ERR_BOUNDS; break; }
                vm->ip = (size_t)t;
            }
            break;
        }

        case OP_CALL: {
            uint32_t fi; rc = r32(vm, &fi); if (rc) break;
            uint8_t na; rc = r8(vm, &na); if (rc) break;
            if (fi >= vm->num_funcs) { rc = CVM_ERR_BAD_FUNC; break; }
            CvmFuncEntry *fe = &vm->funcs[fi];
            rc = push_frame(vm, fe->num_locals > 0 ? fe->num_locals : 16, vm->ip);
            if (rc) break;
            CvmFrame *f = cur_frame(vm);
            for (int i = (int)na - 1; i >= 0; i--) {
                uint64_t a; rc = vo(vm, &a); if (rc) break;
                f->slots[i] = a;
            }
            if (rc) break;
            vm->ip = fe->code_off;
            break;
        }

        case OP_RET: {
            uint64_t rv = 0;
            if (vm->sp > 0) rv = vm->slots[--vm->sp];
            CvmFrame *f = cur_frame(vm);
            if (f && f->return_ip != 0) {
                size_t ret_ip = f->return_ip;
                pop_frame(vm);
                vm->ip = ret_ip;
                rc = vp(vm, rv);
            } else {
                vm->running = 0;
                vm->exit_code = (int64_t)rv;
            }
            break;
        }

        case OP_CALL_NATIVE: {
            uint32_t ni; rc = r32(vm, &ni); if (rc) break;
            uint8_t na; rc = r8(vm, &na); if (rc) break;
            if (ni >= vm->num_natives) { rc = CVM_ERR_BAD_NATIVE; break; }
            if (na > CVM_MAX_NARGS) { rc = CVM_ERR_BOUNDS; break; }
            uint64_t args[CVM_MAX_NARGS];
            for (int i = (int)na-1; i >= 0; i--) { rc = vo(vm, &args[i]); if (rc) break; }
            if (rc) break;
            CvmNativeFn fn = (CvmNativeFn)vm->natives[ni].fn;
            int64_t res = fn(vm, (int)na, args);
            if (vm->running) rc = vp(vm, (uint64_t)res);
            break;
        }

        case OP_LOAD8: {
            uint64_t a; rc=vo(vm,&a); if(rc) break;
            if(!heap_valid(vm,a,1)){rc=CVM_ERR_BAD_ADDR;break;}
            rc=vp(vm,(uint64_t)(int64_t)*(int8_t*)(uintptr_t)a);
            break;
        }
        case OP_LOAD32: {
            uint64_t a; rc=vo(vm,&a); if(rc) break;
            if(!heap_valid(vm,a,4)){rc=CVM_ERR_BAD_ADDR;break;}
            rc=vp(vm,(uint64_t)(int64_t)*(int32_t*)(uintptr_t)a);
            break;
        }
        case OP_LOAD64: {
            uint64_t a; rc=vo(vm,&a); if(rc) break;
            if(!heap_valid(vm,a,8)){rc=CVM_ERR_BAD_ADDR;break;}
            rc=vp(vm,*(uint64_t*)(uintptr_t)a);
            break;
        }
        case OP_STORE8: {
            uint64_t v,a; rc=vo(vm,&v); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if(!heap_valid(vm,a,1)){rc=CVM_ERR_BAD_ADDR;break;}
            *(uint8_t*)(uintptr_t)a=(uint8_t)v;
            break;
        }
        case OP_STORE32: {
            uint64_t v,a; rc=vo(vm,&v); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if(!heap_valid(vm,a,4)){rc=CVM_ERR_BAD_ADDR;break;}
            *(uint32_t*)(uintptr_t)a=(uint32_t)v;
            break;
        }
        case OP_STORE64: {
            uint64_t v,a; rc=vo(vm,&v); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if(!heap_valid(vm,a,8)){rc=CVM_ERR_BAD_ADDR;break;}
            *(uint64_t*)(uintptr_t)a=v;
            break;
        }
        case OP_LEA_LOCAL: {
            uint32_t i; rc=r32(vm,&i); if(rc) break;
            CvmFrame *f=cur_frame(vm);
            if(!f||i>=f->capacity){rc=CVM_ERR_BOUNDS;break;}
            rc=vp(vm,(uint64_t)(uintptr_t)&f->slots[i]);
            break;
        }
        case OP_LEA_GLOBAL: {
            uint32_t i; rc=r32(vm,&i); if(rc) break;
            if(i>=vm->num_globals){rc=CVM_ERR_BOUNDS;break;}
            rc=vp(vm,(uint64_t)(uintptr_t)&vm->globals[i]);
            break;
        }
        case OP_ALLOC: {
            uint64_t s; rc=vo(vm,&s); if(rc) break;
            uint64_t a=heap_alloc(vm,(size_t)s);
            if(!a){rc=CVM_ERR_HEAP_OVER;break;}
            rc=vp(vm,a);
            break;
        }
        case OP_FREE: { uint64_t a; rc=vo(vm,&a); (void)a; break; }
        case OP_SYSCALL: {
            uint8_t sn,na;
            rc=r8(vm,&sn); if(rc) break;
            rc=r8(vm,&na); if(rc) break;
            if(na>CVM_MAX_SARGS){rc=CVM_ERR_BOUNDS;break;}
            uint64_t args[CVM_MAX_SARGS];
            for(int i=(int)na-1;i>=0;i--){rc=vo(vm,&args[i]);if(rc)break;}
            if(rc) break;
            int64_t res=0;
            if(sn==CVM_SYS_WRITE)
                res=(int64_t)write((int)args[0],(const void*)(uintptr_t)args[1],(size_t)args[2]);
            else if(sn==CVM_SYS_EXIT){vm->running=0;vm->exit_code=(int64_t)args[0];}
            if(vm->running) rc=vp(vm,(uint64_t)res);
            break;
        }
        case OP_HALT:
            vm->running = 0;
            if (vm->sp > 0) vm->exit_code = (int64_t)vm->slots[vm->sp-1];
            break;
        default:
            rc = CVM_ERR_BAD_OPCODE;
            break;
        }
        if (rc) break;
    }
    return rc;
}

int64_t cvm_exit_code(const CvmState *vm) { return vm->exit_code; }
uint64_t cvm_instruction_count(const CvmState *vm) { return vm->instr_count; }

#ifndef CVM_NO_MAIN
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <module.cvm> [--trace]\n", argv[0]);
        return 1;
    }
    CvmConfig cfg = cvm_config_default();
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--trace") == 0) cfg.trace_enabled = 1;
    }
    CvmState *vm = cvm_create(&cfg);
    int rc = cvm_load_module_file(vm, argv[1]);
    if (rc != CVM_OK) {
        fprintf(stderr, "cvm: load: %s\n", cvm_strerror(rc));
        cvm_destroy(vm);
        return 1;
    }
    rc = cvm_run(vm);
    if (rc != CVM_OK) {
        fprintf(stderr, "cvm: runtime: %s (ip=%zu)\n", cvm_strerror(rc), vm->ip);
        cvm_destroy(vm);
        return 1;
    }
    int64_t ec = cvm_exit_code(vm);
    if (cfg.trace_enabled)
        fprintf(stderr, "cvm: %lu instructions\n", (unsigned long)cvm_instruction_count(vm));
    cvm_destroy(vm);
    return (int)ec;
}
#endif