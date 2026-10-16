# cvm2: cvm

*Community 0 | 12 files | cohesion 0.73*

## Definition

This community groups 12 file(s) rooted at `cvm2` with dominant language c (cohesion 0.73). Central symbols: `CVM`, `CVM_DATA_ARGC`, `CVM_DATA_ARGS`, `CVM_DATA_ARGV`, `CVM_DATA_RBP`, `CVM_DATA_RET`, `CVM_DATA_RSP`, `CVM_DATA_STACK_BASE`. Core file: `cvm2/cvm.c` (104 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `cvm.c` | c | utility | 20 | no |
| `cvm.h` | h | utility | 28 | no |
| `cvm2/cvm.c` | c | utility | 104 | no |
| `cvm2/cvm.h` | h | utility | 56 | no |
| `cvm2/cvm_jit.h` | h | utility | 26 | no |
| `cvm2/cvm_jit_help.c` | c | utility | 22 | no |
| `cvm2/cvm_jit_help.h` | h | utility | 13 | no |
| `cvm2/cvm_jit_x86.c` | c | utility | 73 | no |
| `cvm2/cvm_jit_x86.h` | h | utility | 71 | no |
| `cvm2/gen_fib_cvm.c` | c | utility | 10 | no |
| `cvm2/gen_minimal.c` | c | utility | 4 | no |
| `gen_fib_cvm.c` | c | utility | 3 | no |

## Key Symbols

- `cvm_error` (function, `cvm.c:12`) `static void cvm_error(CVM *vm, const char *fmt, ...)` - cvm.c — C Virtual Machine interpreter  #include "cvm.h" #include <stdarg.h> #include <errno.h> /* --
- `op_name` (function, `cvm.c:22`) `static const char *op_name(uint8_t op)`
- `push` (function, `cvm.c:78`) `static inline void push(CVM *vm, uint64_t v)` - case OP_RET: return "RET"; case OP_RET_VOID: return "RET_VOID"; case OP_ALLOC: return "ALLOC"; case
- `pop` (function, `cvm.c:86`) `static inline uint64_t pop(CVM *vm)`
- `peek` (function, `cvm.c:94`) `static inline uint64_t peek(CVM *vm)`
- `push_frame` (function, `cvm.c:102`) `static int push_frame(CVM *vm, CVM_Module *mod, uint16_t func_idx, int argc)` - cvm_error(vm, "operand stack underflow"); return 0; } return vm->stack[--vm->sp]; } static inline ui
- `pop_frame` (function, `cvm.c:142`) `static void pop_frame(CVM *vm, int has_retval)`
- `call_native` (function, `cvm.c:175`) `static void call_native(CVM *vm, uint16_t idx, uint8_t argc)` - if (has_retval) push(vm, ret); vm->running = 0; return; } /* restore previous module / code pointer
- `cvm_create` (function, `cvm.c:227`) `CVM *cvm_create(void)` - (void)fd; (void)buf; (void)len; } push(vm, 0); return; } /* generic: just pop args and push 0 for (i
- `cvm_destroy` (function, `cvm.c:244`) `void cvm_destroy(CVM *vm)`
- `cvm_load_module_mem` (function, `cvm.c:267`) `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *n` - free(m->natives); free(m->code); free(m->string_pool); free(m->global_mem); free(m); } free(vm->stac
- `cvm_load_module` (function, `cvm.c:337`) `int cvm_load_module(CVM *vm, const char *path)`
- `interpret` (function, `cvm.c:361`) `static int interpret(CVM *vm)` - if (!buf \|\| fread(buf, 1, (size_t)sz, f) != (size_t)sz) { free(buf); fclose(f); return -1; } fclose(
- `cvm_run` (function, `cvm.c:700`) `int cvm_run(CVM *vm, const char *entry_name)` - vm->running = 0; break; default: cvm_error(vm, "unknown opcode 0x%02x at ip=%u", op, vm->ip - 1); br
- `cvm_emit_byte` (function, `cvm.c:743`) `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b)` - if (vm->trace) fprintf(stderr, "Finished. instructions = %llu\n", (unsigned long long)vm->instr_coun
- `cvm_emit_i16` (function, `cvm.c:751`) `void cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v)`
- `cvm_emit_u16` (function, `cvm.c:756`) `void cvm_emit_u16(uint8_t **buf, size_t *cap, size_t *len, uint16_t v)`
- `cvm_emit_i32` (function, `cvm.c:761`) `void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v)`
- `cvm_emit_i64` (function, `cvm.c:766`) `void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v)`
- `main` (function, `cvm.c:775`) `int main(int argc, char **argv)` - void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v) { for (int i = 0; i < 4; i++)
- `CVM_H` (macro, `cvm.h:8`) `#define CVM_H`
- `CVM_MAGIC` (macro, `cvm.h:22`) `#define CVM_MAGIC`
- `CVM_VERSION` (macro, `cvm.h:23`) `#define CVM_VERSION`
- `CVM_Header` (struct, `cvm.h:107`) - /* Heap OP_ALLOC        = 0x80,   /* size on stack → ptr OP_FREE         = 0x81, /* Syscalls / misc
- `CVM_FuncEntry` (struct, `cvm.h:126`)
- `CVM_GlobalEntry` (struct, `cvm.h:136`)
- `CVM_StringEntry` (struct, `cvm.h:142`)
- `CVM_NativeEntry` (struct, `cvm.h:147`)
- `CVM_STACK_SIZE` (macro, `cvm.h:155`) `#define CVM_STACK_SIZE`
- `CVM_FRAME_DEPTH` (macro, `cvm.h:156`) `#define CVM_FRAME_DEPTH`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 14
- Cross-boundary resolved imports (EXTRACTED): 4

## Connections

- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: cvm2/cvm_dbg_main.c imports cvm2/cvm.h.
- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: cvm2/cvm_jit.c imports cvm2/cvm_jit.h.
- [INFERRED] bridges community 2 <-> 0 (strength 0.5): Inferred cross-community bridge: cvm2/cvm_dis.c reaches cvm2/cvm_jit_x86.c in 5 hops.
- [INFERRED] bridges community 1 <-> 0 (strength 0.5): Inferred cross-community bridge: cvm2/cvm_dis.h reaches cvm2/cvm_jit_x86.c in 5 hops.
- [INFERRED] bridges community 1 <-> 0 (strength 0.5): Inferred cross-community bridge: cvm2/cvm_dis_main.c reaches cvm2/cvm_jit_x86.c in 5 hops.
- [INFERRED] bridges community 0 <-> 2 (strength 0.5): Inferred cross-community bridge: cvm2/cvm_jit_x86.c reaches cvm2/cvm_val_main.c in 5 hops.
- [INFERRED] bridges community 0 <-> 1 (strength 0.5): Inferred cross-community bridge: cvm2/cvm_jit_x86.c reaches cvm2/cvm_view.c in 5 hops.

## Risks

- [dataflow UNCHECKED_ALLOC] `cvm.c:746` `cvm_emit_byte` `buf`: Result of allocator stored in `buf` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `cvm2/gen_minimal.c:17` `emit_byte` `code_buf`: Result of allocator stored in `code_buf` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `cvm2/gen_minimal.c:51` `main` `module`: Result of allocator stored in `module` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `cvm2/gen_minimal.c:83` `main` `f`: Result of allocator stored in `f` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `gen_fib_cvm.c:28` `add_string` `strpool`: Result of allocator stored in `strpool` is never checked against NULL.

## Open Questions

- Why do 12 file(s) lack file-level docs (e.g. `cvm.c`)? What purpose do they serve?
- What would break if the most connected file in cvm2: cvm changed?
- Should cvm2: cvm be split, given cohesion 0.73?

## Sources

- `cvm.c`
- `cvm.h`
- `cvm2/cvm.c`
- `cvm2/cvm.h`
- `cvm2/cvm_jit.h`
- `cvm2/cvm_jit_help.c`
- `cvm2/cvm_jit_help.h`
- `cvm2/cvm_jit_x86.c`
- `cvm2/cvm_jit_x86.h`
- `cvm2/gen_fib_cvm.c`
- `cvm2/gen_minimal.c`
- `gen_fib_cvm.c`
