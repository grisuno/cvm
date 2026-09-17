# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `cvm.h` (score: 22.80)
- `cvm2/cvm.h` (score: 21.60)
- `cvm2/cvm_jit.h` (score: 18.60)
- `cvm2/cvm.c` (score: 16.40)
- `cvm2/cvm_view.h` (score: 14.90)
- `cvm2/cvm_dbg_main.c` (score: 12.10)
- `cvm2/cvm_jit_x86.h` (score: 11.00)
- `cvm2/cvm_ops.h` (score: 10.90)
- `cvm2/cvm_jit_help.h` (score: 9.30)
- `cvm2/cvm_jit_x86.c` (score: 9.20)

## Hotspots (complexity + centrality)

- `cvm.h` -- complexity: 0.3, centrality: 1.0, combined: 0.7
- `cvm2/cvm.c` -- complexity: 1.0, centrality: 0.4, combined: 0.6
- `cvm2/cvm.h` -- complexity: 0.5, centrality: 0.7, combined: 0.6
- `cvm2/cvm_dbg_main.c` -- complexity: 0.2, centrality: 0.6, combined: 0.4
- `cvm2/cvm_jit_x86.c` -- complexity: 0.7, centrality: 0.2, combined: 0.4
- `cvm2/cvm_jit.h` -- complexity: 0.2, centrality: 0.5, combined: 0.4
- `cvm2/cvm_jit_x86.h` -- complexity: 0.7, centrality: 0.2, combined: 0.4
- `cvm2/cvm_jit.c` -- complexity: 0.4, centrality: 0.3, combined: 0.4
- `cvm2/cvm_val_main.c` -- complexity: 0.2, centrality: 0.3, combined: 0.3
- `cvm2/cvm_view.h` -- complexity: 0.1, centrality: 0.5, combined: 0.3

## Dataflow Issues (INFERRED, review each lead)

- `cvm.c:746` `cvm_emit_byte` [UNCHECKED_ALLOC] `buf`: Result of allocator stored in `buf` is never checked against NULL.
- `cvm2/cvm.c:605` `native_sprintf` [DEAD_STORE] `buf`: `buf` assigned at line 605 but never read afterwards.
- `cvm2/cvm.c:616` `native_snprintf` [DEAD_STORE] `buf`: `buf` assigned at line 616 but never read afterwards.
- `cvm2/cvm_jit.c:1249` `cvm_jit_compile_func` [DEAD_STORE] `instr_start_native`: `instr_start_native` assigned at line 1249 but never read afterwards.
- `cvm2/gen_minimal.c:17` `emit_byte` [UNCHECKED_ALLOC] `code_buf`: Result of allocator stored in `code_buf` is never checked against NULL.
- `cvm2/gen_minimal.c:51` `main` [UNCHECKED_ALLOC] `module`: Result of allocator stored in `module` is never checked against NULL.
- `cvm2/gen_minimal.c:83` `main` [UNCHECKED_ALLOC] `f`: Result of allocator stored in `f` is never checked against NULL.
- `gen_fib_cvm.c:28` `add_string` [UNCHECKED_ALLOC] `strpool`: Result of allocator stored in `strpool` is never checked against NULL.
