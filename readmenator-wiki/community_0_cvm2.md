# cvm2

*Community 0 | 22 files | cohesion 1.00*

## Definition

This community groups 22 file(s) rooted at `cvm2` with dominant language c (cohesion 1.00). Central symbols: `CVM`, `CVM_DATA_ARGC`, `CVM_DATA_ARGS`, `CVM_DATA_ARGV`, `CVM_DATA_RBP`, `CVM_DATA_RET`, `CVM_DATA_RSP`, `CVM_DATA_STACK_BASE`. Core file: `cvm2/cvm.c` (112 symbols).

## Files

### `cvm2` (19 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `cvm2/cvm.c` | c | utility | 112 | no |
| `cvm2/cvm.h` | h | utility | 58 | no |
| `cvm2/cvm_dbg_main.c` | c | utility | 35 | no |
| `cvm2/cvm_dis.c` | c | infrastructure | 10 | no |
| `cvm2/cvm_dis.h` | h | infrastructure | 5 | no |
| `cvm2/cvm_dis_main.c` | c | infrastructure | 9 | no |
| `cvm2/cvm_jit.c` | c | utility | 91 | no |
| `cvm2/cvm_jit.h` | h | utility | 26 | no |
| `cvm2/cvm_jit_help.c` | c | utility | 23 | no |
| `cvm2/cvm_jit_help.h` | h | utility | 13 | no |
| `cvm2/cvm_jit_x86.c` | c | utility | 74 | no |
| `cvm2/cvm_jit_x86.h` | h | utility | 70 | no |
| `cvm2/cvm_ops.c` | c | utility | 7 | no |
| `cvm2/cvm_ops.h` | h | utility | 9 | no |
| `cvm2/cvm_val_main.c` | c | utility | 33 | no |
| `cvm2/cvm_view.c` | c | presentation | 9 | no |
| `cvm2/cvm_view.h` | h | presentation | 9 | no |

### `.` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `cvm.c` | c | utility | 32 | no |
| `cvm.h` | h | utility | 28 | no |
| `gen_fib_cvm.c` | c | utility | 13 | no |

*... and 2 more files in this community.*


## Key Symbols

- `cvm_error` (function, `cvm.c:12`) `static void cvm_error(CVM *vm, const char *fmt, ...)` - cvm.c — C Virtual Machine interpreter  #include "cvm.h" #include <stdarg.h> #include <errno.h> /* --
- `va_start` (function, `cvm.c:14`) `va_start(ap, fmt);`
- `fprintf` (function, `cvm.c:15`) `fprintf(stderr, "[CVM ERROR] ");`
- `vfprintf` (function, `cvm.c:16`) `vfprintf(stderr, fmt, ap);`
- `va_end` (function, `cvm.c:18`) `va_end(ap);`
- `op_name` (function, `cvm.c:21`) `static const char *op_name(uint8_t op)`
- `push` (function, `cvm.c:78`) `static inline void push(CVM *vm, uint64_t v)` - case OP_RET: return "RET"; case OP_RET_VOID: return "RET_VOID"; case OP_ALLOC: return "ALLOC"; case
- `pop` (function, `cvm.c:85`) `static inline uint64_t pop(CVM *vm)`
- `peek` (function, `cvm.c:93`) `static inline uint64_t peek(CVM *vm)`
- `push_frame` (function, `cvm.c:102`) `static int push_frame(CVM *vm, CVM_Module *mod, uint16_t func_idx, int argc)` - cvm_error(vm, "operand stack underflow"); return 0; } return vm->stack[--vm->sp]; } static inline ui
- `pop_frame` (function, `cvm.c:141`) `static void pop_frame(CVM *vm, int has_retval)`
- `free` (function, `cvm.c:152`) `free(fr->locals);`
- `call_native` (function, `cvm.c:175`) `static void call_native(CVM *vm, uint16_t idx, uint8_t argc)` - if (has_retval) push(vm, ret); vm->running = 0; return; } /* restore previous module / code pointer
- `printf` (function, `cvm.c:201`) `printf("%lld\n", (long long)(int64_t)v);` - if (!fn) { cvm_error(vm, "cannot resolve native '%s'", name); return; } } /* Extremely simplified: w
- `cvm_create` (function, `cvm.c:227`) `CVM *cvm_create(void)` - (void)fd; (void)buf; (void)len; } push(vm, 0); return; } /* generic: just pop args and push 0 for (i
- `cvm_destroy` (function, `cvm.c:243`) `void cvm_destroy(CVM *vm)`
- `cvm_load_module_mem` (function, `cvm.c:267`) `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *n` - free(m->natives); free(m->code); free(m->string_pool); free(m->global_mem); free(m); } free(vm->stac
- `strncpy` (function, `cvm.c:293`) `strncpy(mod->name, name ? name : "anon", sizeof(mod->name) - 1);`
- `memcpy` (function, `cvm.c:297`) `memcpy(mod->funcs, data + off, hdr->num_functions * sizeof(CVM_FuncEntry));`
- `memset` (function, `cvm.c:331`) `memset(mod->native_ptrs, 0, sizeof(mod->native_ptrs));` - off += hdr->code_size; mod->string_pool = malloc(hdr->string_pool_size + 1); memcpy(mod->string_pool
- `cvm_load_module` (function, `cvm.c:336`) `int cvm_load_module(CVM *vm, const char *path)`
- `perror` (function, `cvm.c:340`) `perror(path);`
- `fseek` (function, `cvm.c:343`) `fseek(f, 0, SEEK_END);`
- `fclose` (function, `cvm.c:349`) `fclose(f);`
- `interpret` (function, `cvm.c:361`) `static int interpret(CVM *vm)` - if (!buf \|\| fread(buf, 1, (size_t)sz, f) != (size_t)sz) { free(buf); fclose(f); return -1; } fclose(
- `cvm_run` (function, `cvm.c:700`) `int cvm_run(CVM *vm, const char *entry_name)` - vm->running = 0; break; default: cvm_error(vm, "unknown opcode 0x%02x at ip=%u", op, vm->ip - 1); br
- `cvm_emit_byte` (function, `cvm.c:743`) `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b)` - if (vm->trace) fprintf(stderr, "Finished. instructions = %llu\n", (unsigned long long)vm->instr_coun
- `cvm_emit_i16` (function, `cvm.c:750`) `void cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v)`
- `cvm_emit_u16` (function, `cvm.c:755`) `void cvm_emit_u16(uint8_t **buf, size_t *cap, size_t *len, uint16_t v)`
- `cvm_emit_i32` (function, `cvm.c:760`) `void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 31
- Cross-boundary resolved imports (EXTRACTED): 0

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- [high] `cvm2/cvm.c:372` (in `native_strcpy`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.

## Open Questions

- Why do 22 file(s) lack file-level docs (e.g. `cvm.c`)? What purpose do they serve?
- What would break if the most connected file in cvm2 changed?
- Should cvm2 be split, given cohesion 1.00?

## Sources

- `cvm.c`
- `cvm.h`
- `cvm2/cvm.c`
- `cvm2/cvm.h`
- `cvm2/cvm_dbg_main.c`
- `cvm2/cvm_dis.c`
- `cvm2/cvm_dis.h`
- `cvm2/cvm_dis_main.c`
- `cvm2/cvm_jit.c`
- `cvm2/cvm_jit.h`
- `cvm2/cvm_jit_help.c`
- `cvm2/cvm_jit_help.h`
- `cvm2/cvm_jit_x86.c`
- `cvm2/cvm_jit_x86.h`
- `cvm2/cvm_ops.c`
- `cvm2/cvm_ops.h`
- `cvm2/cvm_val_main.c`
- `cvm2/cvm_view.c`
- `cvm2/cvm_view.h`
- `cvm2/gen_fib_cvm.c`
- *... and 2 more*
