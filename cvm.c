/*
 * cvm.c — C Virtual Machine interpreter
 */

#include "cvm.h"
#include <stdarg.h>
#include <errno.h>

/* ------------------------------------------------------------------ */
/*  Debug helpers                                                     */
/* ------------------------------------------------------------------ */
static void cvm_error(CVM *vm, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    fprintf(stderr, "[CVM ERROR] ");
    vfprintf(stderr, fmt, ap);
    fprintf(stderr, "\n");
    va_end(ap);
    vm->running = 0;
}

static const char *op_name(uint8_t op) {
    switch (op) {
        case OP_NOP: return "NOP";
        case OP_PUSH_I8: return "PUSH_I8";
        case OP_PUSH_I32: return "PUSH_I32";
        case OP_PUSH_I64: return "PUSH_I64";
        case OP_DUP: return "DUP";
        case OP_POP: return "POP";
        case OP_LOAD_LOCAL: return "LOAD_LOCAL";
        case OP_STORE_LOCAL: return "STORE_LOCAL";
        case OP_LEA_LOCAL: return "LEA_LOCAL";
        case OP_LOAD_GLOBAL: return "LOAD_GLOBAL";
        case OP_STORE_GLOBAL: return "STORE_GLOBAL";
        case OP_LOAD8: return "LOAD8";
        case OP_LOAD32: return "LOAD32";
        case OP_LOAD64: return "LOAD64";
        case OP_STORE8: return "STORE8";
        case OP_STORE32: return "STORE32";
        case OP_STORE64: return "STORE64";
        case OP_ADD: return "ADD";
        case OP_SUB: return "SUB";
        case OP_MUL: return "MUL";
        case OP_DIV: return "DIV";
        case OP_MOD: return "MOD";
        case OP_NEG: return "NEG";
        case OP_AND: return "AND";
        case OP_OR: return "OR";
        case OP_XOR: return "XOR";
        case OP_NOT: return "NOT";
        case OP_SHL: return "SHL";
        case OP_SHR: return "SHR";
        case OP_CMP_EQ: return "CMP_EQ";
        case OP_CMP_NE: return "CMP_NE";
        case OP_CMP_LT: return "CMP_LT";
        case OP_CMP_LE: return "CMP_LE";
        case OP_CMP_GT: return "CMP_GT";
        case OP_CMP_GE: return "CMP_GE";
        case OP_JMP: return "JMP";
        case OP_JZ: return "JZ";
        case OP_JNZ: return "JNZ";
        case OP_CALL: return "CALL";
        case OP_CALL_NATIVE: return "CALL_NATIVE";
        case OP_RET: return "RET";
        case OP_RET_VOID: return "RET_VOID";
        case OP_ALLOC: return "ALLOC";
        case OP_FREE: return "FREE";
        case OP_SYSCALL: return "SYSCALL";
        case OP_PRINT_I64: return "PRINT_I64";
        case OP_HALT: return "HALT";
        default: return "???";
    }
}

/* ------------------------------------------------------------------ */
/*  Stack helpers                                                     */
/* ------------------------------------------------------------------ */
static inline void push(CVM *vm, uint64_t v) {
    if (vm->sp >= CVM_STACK_SIZE - 1) {
        cvm_error(vm, "operand stack overflow");
        return;
    }
    vm->stack[vm->sp++] = v;
}

static inline uint64_t pop(CVM *vm) {
    if (vm->sp <= 0) {
        cvm_error(vm, "operand stack underflow");
        return 0;
    }
    return vm->stack[--vm->sp];
}

static inline uint64_t peek(CVM *vm) {
    if (vm->sp <= 0) return 0;
    return vm->stack[vm->sp - 1];
}

/* ------------------------------------------------------------------ */
/*  Frame helpers                                                     */
/* ------------------------------------------------------------------ */
static int push_frame(CVM *vm, CVM_Module *mod, uint16_t func_idx, int argc) {
    if (vm->fp + 1 >= CVM_FRAME_DEPTH) {
        cvm_error(vm, "frame stack overflow");
        return -1;
    }
    CVM_FuncEntry *fe = &mod->funcs[func_idx];
    if (argc > fe->argc) {
        cvm_error(vm, "too many arguments for function %u", func_idx);
        return -1;
    }

    /* Pop args from operand stack into a temporary */
    uint64_t args[16];
    for (int i = argc - 1; i >= 0; i--)
        args[i] = pop(vm);

    vm->fp++;
    CVM_Frame *fr = &vm->frames[vm->fp];
    fr->num_locals = fe->max_locals;
    fr->func_idx = func_idx;
    fr->return_ip = vm->ip;
    fr->stack_base = (uint32_t)vm->sp;
    fr->locals = calloc(fe->max_locals, sizeof(uint64_t));
    if (!fr->locals) {
        cvm_error(vm, "out of memory for frame");
        vm->fp--;
        return -1;
    }

    /* Copy parameters into first local slots */
    for (int i = 0; i < argc; i++)
        fr->locals[i] = args[i];

    vm->current = mod;
    vm->code = mod->code;
    vm->code_size = mod->hdr.code_size;
    vm->ip = fe->code_off;
    return 0;
}

static void pop_frame(CVM *vm, int has_retval) {
    if (vm->fp < 0) {
        vm->running = 0;
        return;
    }
    CVM_Frame *fr = &vm->frames[vm->fp];
    uint64_t ret = has_retval ? pop(vm) : 0;

    /* Restore operand stack to the base of this frame */
    vm->sp = (int32_t)fr->stack_base;

    free(fr->locals);
    fr->locals = NULL;

    uint32_t ret_ip = fr->return_ip;
    vm->fp--;

    if (vm->fp < 0) {
        /* returning from main */
        if (has_retval) push(vm, ret);
        vm->running = 0;
        return;
    }

    /* restore previous module / code pointer if needed */
    /* (for multi-module we would look up the previous frame's module) */
    vm->ip = ret_ip;
    if (has_retval) push(vm, ret);
}

/* ------------------------------------------------------------------ */
/*  Native call (very limited – only a few for the tests)             */
/* ------------------------------------------------------------------ */
static void call_native(CVM *vm, uint16_t idx, uint8_t argc) {
    CVM_Module *mod = vm->current;
    if (idx >= mod->hdr.num_natives) {
        cvm_error(vm, "invalid native index %u", idx);
        return;
    }
    void *fn = mod->native_ptrs[idx];
    if (!fn) {
        /* try resolve by name */
        const char *name = mod->string_pool + mod->natives[idx].name_off;
        fn = dlsym(RTLD_DEFAULT, name);
        mod->native_ptrs[idx] = fn;
        if (!fn) {
            cvm_error(vm, "cannot resolve native '%s'", name);
            return;
        }
    }

    /* Extremely simplified: we only support a few signatures for demos */
    const char *name = mod->string_pool + mod->natives[idx].name_off;

    if (strcmp(name, "printf") == 0 || strcmp(name, "puts") == 0) {
        /* expect format + args on stack; for demo just print the last integer */
        if (argc >= 1) {
            uint64_t v = pop(vm);
            for (int i = 1; i < argc; i++) pop(vm); /* discard rest */
            printf("%lld\n", (long long)(int64_t)v);
        }
        push(vm, 0);
        return;
    }

    if (strcmp(name, "write") == 0) {
        /* write(fd, buf, len) – we ignore and just print */
        if (argc >= 3) {
            uint64_t len = pop(vm);
            uint64_t buf = pop(vm);
            uint64_t fd  = pop(vm);
            (void)fd; (void)buf; (void)len;
        }
        push(vm, 0);
        return;
    }

    /* generic: just pop args and push 0 */
    for (int i = 0; i < argc; i++) pop(vm);
    push(vm, 0);
}

/* ------------------------------------------------------------------ */
/*  Create / destroy                                                  */
/* ------------------------------------------------------------------ */
CVM *cvm_create(void) {
    CVM *vm = calloc(1, sizeof(CVM));
    if (!vm) return NULL;
    vm->stack = calloc(CVM_STACK_SIZE, sizeof(uint64_t));
    vm->heap  = calloc(1, CVM_HEAP_SIZE);
    if (!vm->stack || !vm->heap) {
        free(vm->stack);
        free(vm->heap);
        free(vm);
        return NULL;
    }
    vm->heap_size = CVM_HEAP_SIZE;
    vm->fp = -1;
    vm->sp = 0;
    return vm;
}

void cvm_destroy(CVM *vm) {
    if (!vm) return;
    for (int i = 0; i <= vm->fp; i++)
        free(vm->frames[i].locals);
    for (int i = 0; i < vm->num_modules; i++) {
        CVM_Module *m = vm->modules[i];
        free(m->funcs);
        free(m->globals);
        free(m->strings);
        free(m->natives);
        free(m->code);
        free(m->string_pool);
        free(m->global_mem);
        free(m);
    }
    free(vm->stack);
    free(vm->heap);
    free(vm);
}

/* ------------------------------------------------------------------ */
/*  Load module from memory                                           */
/* ------------------------------------------------------------------ */
int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name) {
    if (vm->num_modules >= CVM_MAX_MODULES) return -1;
    if (size < sizeof(CVM_Header)) return -1;

    const CVM_Header *hdr = (const CVM_Header *)data;
    if (hdr->magic != CVM_MAGIC || hdr->version != CVM_VERSION) {
        fprintf(stderr, "bad magic/version\n");
        return -1;
    }

    size_t off = sizeof(CVM_Header);
    size_t need = off
        + hdr->num_functions * sizeof(CVM_FuncEntry)
        + hdr->num_globals   * sizeof(CVM_GlobalEntry)
        + hdr->num_strings   * sizeof(CVM_StringEntry)
        + hdr->num_natives   * sizeof(CVM_NativeEntry)
        + hdr->code_size
        + hdr->string_pool_size;
    if (need > size) {
        fprintf(stderr, "module truncated\n");
        return -1;
    }

    CVM_Module *mod = calloc(1, sizeof(CVM_Module));
    if (!mod) return -1;
    mod->hdr = *hdr;
    strncpy(mod->name, name ? name : "anon", sizeof(mod->name) - 1);

    /* copy tables */
    mod->funcs = malloc(hdr->num_functions * sizeof(CVM_FuncEntry));
    memcpy(mod->funcs, data + off, hdr->num_functions * sizeof(CVM_FuncEntry));
    off += hdr->num_functions * sizeof(CVM_FuncEntry);

    mod->globals = malloc(hdr->num_globals * sizeof(CVM_GlobalEntry));
    if (hdr->num_globals)
        memcpy(mod->globals, data + off, hdr->num_globals * sizeof(CVM_GlobalEntry));
    off += hdr->num_globals * sizeof(CVM_GlobalEntry);

    mod->strings = malloc(hdr->num_strings * sizeof(CVM_StringEntry));
    if (hdr->num_strings)
        memcpy(mod->strings, data + off, hdr->num_strings * sizeof(CVM_StringEntry));
    off += hdr->num_strings * sizeof(CVM_StringEntry);

    mod->natives = malloc(hdr->num_natives * sizeof(CVM_NativeEntry));
    if (hdr->num_natives)
        memcpy(mod->natives, data + off, hdr->num_natives * sizeof(CVM_NativeEntry));
    off += hdr->num_natives * sizeof(CVM_NativeEntry);

    mod->code = malloc(hdr->code_size);
    memcpy(mod->code, data + off, hdr->code_size);
    off += hdr->code_size;

    mod->string_pool = malloc(hdr->string_pool_size + 1);
    memcpy(mod->string_pool, data + off, hdr->string_pool_size);
    mod->string_pool[hdr->string_pool_size] = '\0';

    /* allocate runtime globals */
    if (hdr->num_globals) {
        mod->global_mem = calloc(hdr->num_globals, sizeof(uint64_t));
        for (uint32_t i = 0; i < hdr->num_globals; i++)
            mod->global_mem[i] = mod->globals[i].init_value;
    }

    /* resolve natives lazily later */
    memset(mod->native_ptrs, 0, sizeof(mod->native_ptrs));

    vm->modules[vm->num_modules++] = mod;
    return vm->num_modules - 1;
}

int cvm_load_module(CVM *vm, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        perror(path);
        return -1;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t *buf = malloc((size_t)sz);
    if (!buf || fread(buf, 1, (size_t)sz, f) != (size_t)sz) {
        free(buf);
        fclose(f);
        return -1;
    }
    fclose(f);
    int r = cvm_load_module_mem(vm, buf, (size_t)sz, path);
    free(buf);
    return r;
}

/* ------------------------------------------------------------------ */
/*  Main interpreter loop                                             */
/* ------------------------------------------------------------------ */
static int interpret(CVM *vm) {
    vm->running = 1;
    vm->instr_count = 0;

    while (vm->running) {
        if (vm->ip >= vm->code_size) {
            cvm_error(vm, "ip out of bounds");
            break;
        }
        uint8_t op = vm->code[vm->ip++];
        vm->instr_count++;

        if (vm->trace) {
            fprintf(stderr, "[%6llu] ip=%u  %-12s  sp=%d  fp=%d\n",
                    (unsigned long long)vm->instr_count, vm->ip - 1,
                    op_name(op), vm->sp, vm->fp);
        }

        switch (op) {
        case OP_NOP:
            break;

        case OP_PUSH_I8: {
            int8_t v = (int8_t)vm->code[vm->ip++];
            push(vm, (uint64_t)(int64_t)v);
            break;
        }
        case OP_PUSH_I32: {
            int32_t v;
            memcpy(&v, vm->code + vm->ip, 4);
            vm->ip += 4;
            push(vm, (uint64_t)(int64_t)v);
            break;
        }
        case OP_PUSH_I64: {
            int64_t v;
            memcpy(&v, vm->code + vm->ip, 8);
            vm->ip += 8;
            push(vm, (uint64_t)v);
            break;
        }
        case OP_DUP:
            push(vm, peek(vm));
            break;
        case OP_POP:
            pop(vm);
            break;
        case OP_SWAP: {
            uint64_t a = pop(vm), b = pop(vm);
            push(vm, a); push(vm, b);
            break;
        }

        case OP_LOAD_LOCAL: {
            int16_t off;
            memcpy(&off, vm->code + vm->ip, 2);
            vm->ip += 2;
            if (vm->fp < 0) { cvm_error(vm, "no frame"); break; }
            /* off is treated as slot index for simplicity */
            uint16_t slot = (uint16_t)off;
            if (slot >= vm->frames[vm->fp].num_locals) {
                cvm_error(vm, "local out of range %d", slot);
                break;
            }
            push(vm, vm->frames[vm->fp].locals[slot]);
            break;
        }
        case OP_STORE_LOCAL: {
            int16_t off;
            memcpy(&off, vm->code + vm->ip, 2);
            vm->ip += 2;
            if (vm->fp < 0) { cvm_error(vm, "no frame"); break; }
            uint16_t slot = (uint16_t)off;
            if (slot >= vm->frames[vm->fp].num_locals) {
                cvm_error(vm, "local out of range %d", slot);
                break;
            }
            vm->frames[vm->fp].locals[slot] = pop(vm);
            break;
        }
        case OP_LEA_LOCAL: {
            int16_t off;
            memcpy(&off, vm->code + vm->ip, 2);
            vm->ip += 2;
            /* return a fake “address” = pointer to the local slot */
            if (vm->fp < 0) { cvm_error(vm, "no frame"); break; }
            uint16_t slot = (uint16_t)off;
            push(vm, (uint64_t)(uintptr_t)&vm->frames[vm->fp].locals[slot]);
            break;
        }

        case OP_LOAD_GLOBAL: {
            uint16_t idx;
            memcpy(&idx, vm->code + vm->ip, 2);
            vm->ip += 2;
            if (idx >= vm->current->hdr.num_globals) {
                cvm_error(vm, "global out of range");
                break;
            }
            push(vm, vm->current->global_mem[idx]);
            break;
        }
        case OP_STORE_GLOBAL: {
            uint16_t idx;
            memcpy(&idx, vm->code + vm->ip, 2);
            vm->ip += 2;
            if (idx >= vm->current->hdr.num_globals) {
                cvm_error(vm, "global out of range");
                break;
            }
            vm->current->global_mem[idx] = pop(vm);
            break;
        }

        case OP_LOAD8: {
            uint64_t addr = pop(vm);
            int8_t v = *(int8_t *)(uintptr_t)addr;
            push(vm, (uint64_t)(int64_t)v);
            break;
        }
        case OP_LOAD32: {
            uint64_t addr = pop(vm);
            int32_t v = *(int32_t *)(uintptr_t)addr;
            push(vm, (uint64_t)(int64_t)v);
            break;
        }
        case OP_LOAD64:
        case OP_LOAD_PTR: {
            uint64_t addr = pop(vm);
            uint64_t v = *(uint64_t *)(uintptr_t)addr;
            push(vm, v);
            break;
        }
        case OP_STORE8: {
            uint64_t val = pop(vm);
            uint64_t addr = pop(vm);
            *(uint8_t *)(uintptr_t)addr = (uint8_t)val;
            break;
        }
        case OP_STORE32: {
            uint64_t val = pop(vm);
            uint64_t addr = pop(vm);
            *(uint32_t *)(uintptr_t)addr = (uint32_t)val;
            break;
        }
        case OP_STORE64:
        case OP_STORE_PTR: {
            uint64_t val = pop(vm);
            uint64_t addr = pop(vm);
            *(uint64_t *)(uintptr_t)addr = val;
            break;
        }

        case OP_ADD: {
            uint64_t b = pop(vm), a = pop(vm);
            push(vm, a + b);
            break;
        }
        case OP_SUB: {
            uint64_t b = pop(vm), a = pop(vm);
            push(vm, a - b);
            break;
        }
        case OP_MUL: {
            uint64_t b = pop(vm), a = pop(vm);
            push(vm, a * b);
            break;
        }
        case OP_DIV: {
            int64_t b = (int64_t)pop(vm), a = (int64_t)pop(vm);
            if (b == 0) { cvm_error(vm, "division by zero"); break; }
            push(vm, (uint64_t)(a / b));
            break;
        }
        case OP_MOD: {
            int64_t b = (int64_t)pop(vm), a = (int64_t)pop(vm);
            if (b == 0) { cvm_error(vm, "mod by zero"); break; }
            push(vm, (uint64_t)(a % b));
            break;
        }
        case OP_NEG: {
            int64_t a = (int64_t)pop(vm);
            push(vm, (uint64_t)(-a));
            break;
        }
        case OP_AND: {
            uint64_t b = pop(vm), a = pop(vm);
            push(vm, a & b);
            break;
        }
        case OP_OR: {
            uint64_t b = pop(vm), a = pop(vm);
            push(vm, a | b);
            break;
        }
        case OP_XOR: {
            uint64_t b = pop(vm), a = pop(vm);
            push(vm, a ^ b);
            break;
        }
        case OP_NOT: {
            uint64_t a = pop(vm);
            push(vm, ~a);
            break;
        }
        case OP_SHL: {
            uint64_t b = pop(vm), a = pop(vm);
            push(vm, a << (b & 63));
            break;
        }
        case OP_SHR: {
            int64_t b = (int64_t)pop(vm), a = (int64_t)pop(vm);
            push(vm, (uint64_t)(a >> (b & 63)));
            break;
        }
        case OP_USHR: {
            uint64_t b = pop(vm), a = pop(vm);
            push(vm, a >> (b & 63));
            break;
        }

        case OP_CMP_EQ: {
            uint64_t b = pop(vm), a = pop(vm);
            push(vm, a == b ? 1 : 0);
            break;
        }
        case OP_CMP_NE: {
            uint64_t b = pop(vm), a = pop(vm);
            push(vm, a != b ? 1 : 0);
            break;
        }
        case OP_CMP_LT: {
            int64_t b = (int64_t)pop(vm), a = (int64_t)pop(vm);
            push(vm, a < b ? 1 : 0);
            break;
        }
        case OP_CMP_LE: {
            int64_t b = (int64_t)pop(vm), a = (int64_t)pop(vm);
            push(vm, a <= b ? 1 : 0);
            break;
        }
        case OP_CMP_GT: {
            int64_t b = (int64_t)pop(vm), a = (int64_t)pop(vm);
            push(vm, a > b ? 1 : 0);
            break;
        }
        case OP_CMP_GE: {
            int64_t b = (int64_t)pop(vm), a = (int64_t)pop(vm);
            push(vm, a >= b ? 1 : 0);
            break;
        }

        case OP_JMP: {
            int32_t rel;
            memcpy(&rel, vm->code + vm->ip, 4);
            vm->ip += 4;
            vm->ip = (uint32_t)((int32_t)vm->ip + rel);
            break;
        }
        case OP_JZ: {
            int32_t rel;
            memcpy(&rel, vm->code + vm->ip, 4);
            vm->ip += 4;
            if (pop(vm) == 0)
                vm->ip = (uint32_t)((int32_t)vm->ip + rel);
            break;
        }
        case OP_JNZ: {
            int32_t rel;
            memcpy(&rel, vm->code + vm->ip, 4);
            vm->ip += 4;
            if (pop(vm) != 0)
                vm->ip = (uint32_t)((int32_t)vm->ip + rel);
            break;
        }

        case OP_CALL: {
            uint16_t fidx;
            uint8_t argc;
            memcpy(&fidx, vm->code + vm->ip, 2);
            vm->ip += 2;
            argc = vm->code[vm->ip++];
            if (push_frame(vm, vm->current, fidx, argc) != 0)
                return -1;
            break;
        }
        case OP_CALL_NATIVE: {
            uint16_t nidx;
            uint8_t argc;
            memcpy(&nidx, vm->code + vm->ip, 2);
            vm->ip += 2;
            argc = vm->code[vm->ip++];
            call_native(vm, nidx, argc);
            break;
        }
        case OP_RET:
            pop_frame(vm, 1);
            break;
        case OP_RET_VOID:
            pop_frame(vm, 0);
            break;

        case OP_ALLOC: {
            uint64_t sz = pop(vm);
            sz = (sz + 7) & ~7ULL;
            if (vm->heap_used + sz > vm->heap_size) {
                cvm_error(vm, "out of heap");
                break;
            }
            uint64_t ptr = (uint64_t)(uintptr_t)(vm->heap + vm->heap_used);
            vm->heap_used += (size_t)sz;
            push(vm, ptr);
            break;
        }
        case OP_FREE:
            /* bump allocator – free is a no-op for now */
            pop(vm);
            break;

        case OP_PRINT_I64: {
            int64_t v = (int64_t)pop(vm);
            printf("%lld\n", (long long)v);
            break;
        }
        case OP_HALT:
            vm->running = 0;
            break;

        default:
            cvm_error(vm, "unknown opcode 0x%02x at ip=%u", op, vm->ip - 1);
            break;
        }
    }
    return 0;
}

/* ------------------------------------------------------------------ */
/*  Public run                                                        */
/* ------------------------------------------------------------------ */
int cvm_run(CVM *vm, const char *entry_name) {
    if (vm->num_modules == 0) return -1;
    CVM_Module *mod = vm->modules[0];

    int entry = -1;
    for (uint32_t i = 0; i < mod->hdr.num_functions; i++) {
        const char *n = mod->string_pool + mod->funcs[i].name_off;
        if (strcmp(n, entry_name) == 0 ||
            (entry_name == NULL && mod->funcs[i].is_main)) {
            entry = (int)i;
            break;
        }
    }
    if (entry < 0) {
        fprintf(stderr, "entry point '%s' not found\n", entry_name ? entry_name : "main");
        return -1;
    }

    vm->current = mod;
    vm->code = mod->code;
    vm->code_size = mod->hdr.code_size;
    vm->ip = 0;
    vm->sp = 0;
    vm->fp = -1;

    if (push_frame(vm, mod, (uint16_t)entry, 0) != 0)
        return -1;

    interpret(vm);

    if (vm->trace)
        fprintf(stderr, "Finished. instructions = %llu\n",
                (unsigned long long)vm->instr_count);

    /* if there is a return value left on the stack, return it as exit code */
    if (vm->sp > 0)
        return (int)(int64_t)vm->stack[vm->sp - 1];
    return 0;
}

/* ------------------------------------------------------------------ */
/*  Emitter helpers (used by the backend)                             */
/* ------------------------------------------------------------------ */
void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b) {
    if (*len + 1 > *cap) {
        *cap = *cap ? *cap * 2 : 256;
        *buf = realloc(*buf, *cap);
    }
    (*buf)[(*len)++] = b;
}

void cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v) {
    cvm_emit_byte(buf, cap, len, (uint8_t)(v & 0xff));
    cvm_emit_byte(buf, cap, len, (uint8_t)((v >> 8) & 0xff));
}

void cvm_emit_u16(uint8_t **buf, size_t *cap, size_t *len, uint16_t v) {
    cvm_emit_byte(buf, cap, len, (uint8_t)(v & 0xff));
    cvm_emit_byte(buf, cap, len, (uint8_t)((v >> 8) & 0xff));
}

void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v) {
    for (int i = 0; i < 4; i++)
        cvm_emit_byte(buf, cap, len, (uint8_t)((v >> (i * 8)) & 0xff));
}

void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v) {
    for (int i = 0; i < 8; i++)
        cvm_emit_byte(buf, cap, len, (uint8_t)((v >> (i * 8)) & 0xff));
}

/* ------------------------------------------------------------------ */
/*  Main (standalone runner)                                          */
/* ------------------------------------------------------------------ */
#ifdef CVM_STANDALONE
int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s module.cvm [--trace] [entry]\n", argv[0]);
        return 1;
    }
    const char *path = argv[1];
    int trace = 0;
    const char *entry = "main";
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--trace") == 0) trace = 1;
        else entry = argv[i];
    }

    CVM *vm = cvm_create();
    if (!vm) return 1;
    vm->trace = trace;

    if (cvm_load_module(vm, path) < 0) {
        cvm_destroy(vm);
        return 1;
    }

    int rc = cvm_run(vm, entry);
    if (trace)
        fprintf(stderr, "exit code = %d, instr = %llu\n",
                rc, (unsigned long long)vm->instr_count);
    cvm_destroy(vm);
    return rc;
}
#endif
