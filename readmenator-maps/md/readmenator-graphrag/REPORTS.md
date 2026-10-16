# GraphRAG Community Reports

Entities: 654 | Relationships: 1147 | Communities: 4 | Themes: 2 | Text units: 566

Query with `readmenator . ask "<question>"` (local: BM25 + Personalized PageRank; global: map-reduce over these reports) or the MCP tool `readmenator.graphrag`.

## Project overview (`root`, root, rating 7.0)

26 files in 4 communities and 2 themes. Highest-impact communities: cvm2: cvm (7.0), cvm2: cvm_dbg_main (2.5), cvm2: cvm_jit (1.8). God nodes: cvm.h, cvm2/cvm.h, cvm2/cvm_jit.h, cvm2/cvm.c, cvm2/cvm_view.h.

- [cvm2: cvm] rating 7.0: `cvm2/cvm.h` ranks 1 by PageRank, 8 importers, 56 symbols: CvmOpcode: ifdef __cplusplus
- [cvm2: cvm_dbg_main] rating 2.5: `cvm2/cvm_view.h` ranks 1 by PageRank, 5 importers, 9 symbols: cvm_view_open: uint32_t       num_strings; uint32_t       code_size; uint32_t       string_pool_size; uint32_t       data_size; uint32_t       entry_func; size_t         func_off; size_t         global_off; size_t         native_off...
- [cvm2: cvm_jit] rating 1.8: `cvm2/cvm_ops.h` ranks 1 by PageRank, 5 importers, 9 symbols: cvm_op_info: CVM_OPK_U32   = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL   = 6, CVM_OPK_U8U8  = 7 } CvmOpKind; typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for one opcode, or...
- [unassigned files] rating 1.0: `cvm2/deepseek_bash_20260808_653f26.sh` ranks 1 by PageRank, 0 importers, 0 symbols.
- Key entities: file:cvm2/cvm.c, file:cvm2/cvm_jit_x86.c, file:cvm2/cvm_dbg_main.c, file:cvm2/cvm_view.h, file:cvm2/cvm_jit.c, file:cvm2/cvm_val_main.c
- Children: t0, t1
- Root rating = highest community rating.

## cvm2: cvm + cvm2: cvm_dbg_main +1 (`t0`, theme, rating 7.0)

Theme of 3 communities and 22 files: cvm2: cvm (12 files, rating 7.0); cvm2: cvm_dbg_main (5 files, rating 2.5); cvm2: cvm_jit (5 files, rating 1.8).

- [cvm2: cvm] `cvm2/cvm.h` ranks 1 by PageRank, 8 importers, 56 symbols: CvmOpcode: ifdef __cplusplus
- [cvm2: cvm] `cvm.h` ranks 2 by PageRank, 2 importers, 28 symbols: CVM_Header: /* Heap OP_ALLOC        = 0x80,   /* size on stack → ptr OP_FREE         = 0x81, /* Syscalls / misc OP_SYSCALL      = 0x90,   /* nr, arg0..arg5 on stack (Linux x86-64 style) OP_PRINT_I64    = 0x91,   /* debug helper OP_HALT...
- [cvm2: cvm_dbg_main] `cvm2/cvm_view.h` ranks 1 by PageRank, 5 importers, 9 symbols: cvm_view_open: uint32_t       num_strings; uint32_t       code_size; uint32_t       string_pool_size; uint32_t       data_size; uint32_t       entry_func; size_t         func_off; size_t         global_off; size_t         native_off...
- [cvm2: cvm_dbg_main] `cvm2/cvm_dis.h` ranks 2 by PageRank, 3 importers, 4 symbols: cvm_dis_module: #ifndef CVM_DIS_H #define CVM_DIS_H #include <stddef.h> #include <stdint.h> #include "cvm_view.h" #ifdef __cplusplus extern "C" { #endif typedef int (*CvmDisEmit)(void *ctx, const char *line); /* Whole module: header...
- [cvm2: cvm_jit] `cvm2/cvm_ops.h` ranks 1 by PageRank, 5 importers, 9 symbols: cvm_op_info: CVM_OPK_U32   = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL   = 6, CVM_OPK_U8U8  = 7 } CvmOpKind; typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for one opcode, or...
- [cvm2: cvm_jit] `cvm2/cvm_dis.c` ranks 2 by PageRank, 0 importers, 9 symbols.
- Key entities: file:cvm2/cvm.c, file:cvm2/cvm_jit_x86.c, file:cvm2/cvm_dbg_main.c, file:cvm2/cvm_view.h, file:cvm2/cvm_jit.c, file:cvm2/cvm_val_main.c
- Children: c0, c1, c2
- Theme rating = highest child community rating.

## unassigned files (`t1`, theme, rating 1.0)

Theme of 1 communities and 4 files: unassigned files (4 files, rating 1.0).

- [unassigned files] `cvm2/deepseek_bash_20260808_653f26.sh` ranks 1 by PageRank, 0 importers, 0 symbols.
- [unassigned files] `cvm2/gen_test.py` ranks 2 by PageRank, 0 importers, 2 symbols: Generate a minimal .cvm that pushes 42 and halts.
- Key entities: file:cvm2/gen_test.py, file:cvm2/test.sh
- Children: c3
- Theme rating = highest child community rating.

## cvm2: cvm (`c0`, community, rating 7.0)

12 files under cvm2 (c 7, h 5), mostly utility. Core file cvm2/cvm.h (PageRank 0.2078, imported by 8 files): CvmOpcode: ifdef __cplusplus Key abstractions: CvmFuncEntry, CvmGlobalEntry, CvmNativeEntry, CvmStringEntry, CvmConfig, CvmFrame. Used by cvm2: cvm_dbg_main (2), cvm2: cvm_jit (2).

- `cvm2/cvm.h` ranks 1 by PageRank, 8 importers, 56 symbols: CvmOpcode: ifdef __cplusplus
- `cvm.h` ranks 2 by PageRank, 2 importers, 28 symbols: CVM_Header: /* Heap OP_ALLOC        = 0x80,   /* size on stack → ptr OP_FREE         = 0x81, /* Syscalls / misc OP_SYSCALL      = 0x90,   /* nr, arg0..arg5 on stack (Linux x86-64 style) OP_PRINT_I64    = 0x91,   /* debug helper OP_HALT...
- `cvm2/cvm_jit.h` ranks 3 by PageRank, 4 importers, 26 symbols: cvm_jit_create: /* IP-to-native mapping (shared across all functions) JitIpMap        ip_map[JIT_IP_MAP_SIZE]; size_t          ip_map_count; /* Profile counters for tier-up uint32_t        hot_threshold;          /* tier-up threshold...
- Hotspot `cvm.h`: 28 symbols, 20 connections (score 0.71).
- Hotspot `cvm2/cvm.c`: 104 symbols, 8 connections (score 0.64).
- Dataflow: 5 INFERRED issues (first: UNCHECKED_ALLOC in cvm_emit_byte).
- Surprising bridge: cvm_dis.c <-> cvm_jit_x86.c (5 hops across communities).
- Key entities: file:cvm2/cvm.c, file:cvm2/cvm_jit_x86.c, file:cvm2/cvm_jit_x86.h, file:cvm2/cvm.h, file:cvm.h, file:cvm2/cvm_jit.h, file:cvm.c, file:cvm2/cvm_jit_help.c
- Rating 7.0/10 = 7 x PageRank share 1.00 + 3 x risk 0.00. Internal imports: 14.

## cvm2: cvm_dbg_main (`c1`, community, rating 2.5)

5 files under cvm2 (c 3, h 2), mostly utility. Core file cvm2/cvm_view.h (PageRank 0.0977, imported by 5 files): cvm_view_open: uint32_t       num_strings; uint32_t       code_size; uint32_t       string_pool_size; uint32_t       data_size; uint32_t       entry_func; size_t         func_off; size_t         global_off; size_t         native_off... Key abstractions: CvmModuleView, CVM_VIEW_H, data, cvm_view_open, cvm_view_strerror, cvm_view_func. Depends on cvm2: cvm (2), cvm2: cvm_jit (1). Used by cvm2: cvm_jit (2).

- `cvm2/cvm_view.h` ranks 1 by PageRank, 5 importers, 9 symbols: cvm_view_open: uint32_t       num_strings; uint32_t       code_size; uint32_t       string_pool_size; uint32_t       data_size; uint32_t       entry_func; size_t         func_off; size_t         global_off; size_t         native_off...
- `cvm2/cvm_dis.h` ranks 2 by PageRank, 3 importers, 4 symbols: cvm_dis_module: #ifndef CVM_DIS_H #define CVM_DIS_H #include <stddef.h> #include <stdint.h> #include "cvm_view.h" #ifdef __cplusplus extern "C" { #endif typedef int (*CvmDisEmit)(void *ctx, const char *line); /* Whole module: header...
- `cvm2/cvm_dbg_main.c` ranks 3 by PageRank, 0 importers, 21 symbols.
- Hotspot `cvm2/cvm_dbg_main.c`: 21 symbols, 12 connections (score 0.44).
- Hotspot `cvm2/cvm_view.h`: 9 symbols, 9 connections (score 0.30).
- Surprising bridge: cvm_dis.h <-> cvm_jit_x86.c (5 hops across communities).
- Key entities: file:cvm2/cvm_dbg_main.c, file:cvm2/cvm_view.h, file:cvm2/cvm_dis.h, file:cvm2/cvm_view.c, file:cvm2/cvm_dis_main.c, sym:cvm2/cvm_view.c::cvm_view_func@72, sym:cvm2/cvm_view.c::cvm_view_func_name@87, sym:cvm2/cvm_view.c::cvm_view_func_region@108
- Rating 2.5/10 = 7 x PageRank share 0.36 + 3 x risk 0.00. Internal imports: 6.

## cvm2: cvm_jit (`c2`, community, rating 1.8)

5 files under cvm2 (c 4, h 1), mostly utility. Core file cvm2/cvm_ops.h (PageRank 0.0610, imported by 5 files): cvm_op_info: CVM_OPK_U32   = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL   = 6, CVM_OPK_U8U8  = 7 } CvmOpKind; typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for one opcode, or... Key abstractions: CvmOpInfo, CVM_OPS_H, CvmOpKind, cvm_op_info, cvm_op_name, cvm_ops_ri32. Depends on cvm2: cvm (2), cvm2: cvm_dbg_main (2). Used by cvm2: cvm_dbg_main (1).

- `cvm2/cvm_ops.h` ranks 1 by PageRank, 5 importers, 9 symbols: cvm_op_info: CVM_OPK_U32   = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL   = 6, CVM_OPK_U8U8  = 7 } CvmOpKind; typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for one opcode, or...
- `cvm2/cvm_dis.c` ranks 2 by PageRank, 0 importers, 9 symbols.
- `cvm2/cvm_jit.c` ranks 3 by PageRank, 0 importers, 37 symbols: emit_stack_pop_into: /* Push rax onto the operand stack: slots[sp] = rax; sp++ static void emit_stack_push(JitBuf *b) { /* mov [r12 + r13*8], rax; inc r13 emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1); emit_inc_reg(b...
- Hotspot `cvm2/cvm_jit.c`: 37 symbols, 7 connections (score 0.35).
- Hotspot `cvm2/cvm_val_main.c`: 25 symbols, 7 connections (score 0.31).
- Dataflow: 1 INFERRED issues (first: DEAD_STORE in cvm_jit_compile_func).
- Surprising bridge: cvm_dis.c <-> cvm_jit_x86.c (5 hops across communities).
- Key entities: file:cvm2/cvm_jit.c, file:cvm2/cvm_val_main.c, file:cvm2/cvm_ops.h, file:cvm2/cvm_dis.c, file:cvm2/cvm_ops.c, sym:cvm2/cvm_ops.c::OP_INFOS_LEN@70, sym:cvm2/cvm_ops.c::cvm_op_info@72, sym:cvm2/cvm_ops.c::cvm_op_name@78
- Rating 1.8/10 = 7 x PageRank share 0.25 + 3 x risk 0.00. Internal imports: 4.

## unassigned files (`c3`, community, rating 1.0)

4 files under cvm2 (sh 3, py 1), mostly testing. Core file cvm2/deepseek_bash_20260808_653f26.sh (PageRank 0.0209, imported by 0 files). Key abstractions: emit_byte, emit_u32, check, reject.

- `cvm2/deepseek_bash_20260808_653f26.sh` ranks 1 by PageRank, 0 importers, 0 symbols.
- `cvm2/gen_test.py` ranks 2 by PageRank, 0 importers, 2 symbols: Generate a minimal .cvm that pushes 42 and halts.
- `cvm2/test.sh` ranks 3 by PageRank, 0 importers, 2 symbols: CVM v2 toolchain suite: interpreter, disassembler, validator (including corrupted-module rejections) and the scripted debugger.
- Hotspot `cvm2/gen_test.py`: 2 symbols, 3 connections (score 0.10).
- Hotspot `cvm2/test.sh`: 2 symbols, 0 connections (score 0.01).
- Taint: 1 paths reach this group via subprocess.
- Key entities: file:cvm2/gen_test.py, file:cvm2/test.sh, sym:cvm2/test.sh::check@13, sym:cvm2/test.sh::reject@24, sym:cvm2/gen_test.py::emit_byte@7, sym:cvm2/gen_test.py::emit_u32@10, file:cvm2/deepseek_bash_20260808_653f26.sh, file:test.sh
- Rating 1.0/10 = 7 x PageRank share 0.15 + 3 x risk 0.00. Internal imports: 0.
