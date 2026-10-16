# Documentation Coverage

Overall: **47.8%** (196 of 410 public modules, types, and callables). Data members are excluded from the ratio.

[Back to index](index.md)

## By kind

| Kind | Documented | Total | Coverage |
|---|---|---|---|
| function | 183 | 270 | 67.8% |
| macro | 7 | 84 | 8.3% |
| module | 0 | 23 | 0.0% |
| struct | 6 | 32 | 18.8% |
| type_alias | 0 | 1 | 0.0% |

## By module (lowest first)

| Module | Documented | Total | Coverage |
|---|---|---|---|
| [`cvm2/cvm_dbg_main.c`](modules/cvm2.cvm_dbg_main.c.md) | 0 | 4 | 0.0% |
| [`cvm2/cvm_dis_main.c`](modules/cvm2.cvm_dis_main.c.md) | 0 | 2 | 0.0% |
| [`cvm2/deepseek_bash_20260808_653f26.sh`](modules/cvm2.deepseek_bash_20260808_653f26.sh.md) | 0 | 1 | 0.0% |
| [`cvm2/gen_fib_cvm.c`](modules/cvm2.gen_fib_cvm.c.md) | 0 | 5 | 0.0% |
| [`cvm2/gen_minimal.c`](modules/cvm2.gen_minimal.c.md) | 0 | 2 | 0.0% |
| [`gen_fib_cvm.c`](modules/gen_fib_cvm.c.md) | 0 | 3 | 0.0% |
| [`cvm2/cvm.h`](modules/cvm2.cvm.h.md) | 2 | 55 | 3.6% |
| [`cvm2/cvm.c`](modules/cvm2.cvm.c.md) | 5 | 35 | 14.3% |
| [`cvm.h`](modules/cvm.h.md) | 5 | 28 | 17.9% |
| [`cvm2/cvm_val_main.c`](modules/cvm2.cvm_val_main.c.md) | 3 | 15 | 20.0% |
| [`cvm2/cvm_jit.h`](modules/cvm2.cvm_jit.h.md) | 9 | 25 | 36.0% |
| [`cvm2/cvm_ops.c`](modules/cvm2.cvm_ops.c.md) | 3 | 8 | 37.5% |
| [`cvm2/cvm_ops.h`](modules/cvm2.cvm_ops.h.md) | 3 | 8 | 37.5% |
| [`cvm.c`](modules/cvm.c.md) | 5 | 12 | 41.7% |
| [`cvm2/cvm_dis.c`](modules/cvm2.cvm_dis.c.md) | 3 | 5 | 60.0% |
| [`cvm2/cvm_jit.c`](modules/cvm2.cvm_jit.c.md) | 11 | 18 | 61.1% |
| [`cvm2/cvm_view.h`](modules/cvm2.cvm_view.h.md) | 5 | 8 | 62.5% |
| [`cvm2/cvm_jit_help.c`](modules/cvm2.cvm_jit_help.c.md) | 8 | 12 | 66.7% |
| [`cvm2/cvm_view.c`](modules/cvm2.cvm_view.c.md) | 5 | 7 | 71.4% |
| [`cvm2/cvm_dis.h`](modules/cvm2.cvm_dis.h.md) | 3 | 4 | 75.0% |
| [`cvm2/cvm_jit_help.h`](modules/cvm2.cvm_jit_help.h.md) | 9 | 12 | 75.0% |
| [`cvm2/cvm_jit_x86.c`](modules/cvm2.cvm_jit_x86.c.md) | 57 | 70 | 81.4% |
| [`cvm2/cvm_jit_x86.h`](modules/cvm2.cvm_jit_x86.h.md) | 60 | 71 | 84.5% |

## Warnings

DOC001 undocumented public item, DOC002 parameter not documented, DOC003 documented parameter missing from the signature (stale doc), DOC004 return value not documented, DOC005 raised exception not documented.

DOC001: 214

- DOC001 `cvm.c:1` module cvm.c is not documented
- DOC001 `cvm.c:244` function cvm_destroy is not documented
- DOC001 `cvm.c:337` function cvm_load_module is not documented
- DOC001 `cvm.c:751` function cvm_emit_i16 is not documented
- DOC001 `cvm.c:756` function cvm_emit_u16 is not documented
- DOC001 `cvm.c:761` function cvm_emit_i32 is not documented
- DOC001 `cvm.c:766` function cvm_emit_i64 is not documented
- DOC001 `cvm.h:1` module cvm.h is not documented
- DOC001 `cvm.h:22` macro CVM_MAGIC is not documented
- DOC001 `cvm.h:126` struct CVM_FuncEntry is not documented
- DOC001 `cvm.h:136` struct CVM_GlobalEntry is not documented
- DOC001 `cvm.h:142` struct CVM_StringEntry is not documented
- DOC001 `cvm.h:147` struct CVM_NativeEntry is not documented
- DOC001 `cvm.h:155` macro CVM_STACK_SIZE is not documented
- DOC001 `cvm.h:157` macro CVM_HEAP_SIZE is not documented
- DOC001 `cvm.h:158` macro CVM_MAX_MODULES is not documented
- DOC001 `cvm.h:159` macro CVM_MAX_NATIVES is not documented
- DOC001 `cvm.h:161` struct CVM_Frame is not documented
- DOC001 `cvm.h:168` type_alias hdr is not documented
- DOC001 `cvm.h:169` struct CVM_Module is not documented
- DOC001 `cvm.h:182` struct CVM is not documented
- DOC001 `cvm.h:216` function cvm_destroy is not documented
- DOC001 `cvm.h:217` function cvm_load_module is not documented
- DOC001 `cvm.h:218` function cvm_load_module_mem is not documented
- DOC001 `cvm.h:219` function cvm_run is not documented
- DOC001 `cvm.h:220` function cvm_call is not documented
- DOC001 `cvm.h:224` function cvm_emit_i16 is not documented
- DOC001 `cvm.h:225` function cvm_emit_i32 is not documented
- DOC001 `cvm.h:226` function cvm_emit_i64 is not documented
- DOC001 `cvm.h:227` function cvm_emit_u16 is not documented
- DOC001 `cvm2/cvm.c:1` module cvm2/cvm.c is not documented
- DOC001 `cvm2/cvm.c:15` macro CVM_DEF_STACK is not documented
- DOC001 `cvm2/cvm.c:16` macro CVM_DEF_FRAMES is not documented
- DOC001 `cvm2/cvm.c:17` macro CVM_DEF_LOCALS is not documented
- DOC001 `cvm2/cvm.c:18` macro CVM_DEF_HEAP is not documented
- DOC001 `cvm2/cvm.c:19` macro CVM_DEF_GLOBALS is not documented
- DOC001 `cvm2/cvm.c:20` macro CVM_DEF_FUNCS is not documented
- DOC001 `cvm2/cvm.c:21` macro CVM_DEF_NATIVES is not documented
- DOC001 `cvm2/cvm.c:22` macro CVM_DEF_CODE is not documented
- DOC001 `cvm2/cvm.c:23` macro CVM_DEF_PROFILE is not documented
- DOC001 `cvm2/cvm.c:24` macro CVM_HEAP_ALIGN is not documented
- DOC001 `cvm2/cvm.c:25` macro CVM_MAX_NARGS is not documented
- DOC001 `cvm2/cvm.c:26` macro CVM_MAX_SARGS is not documented
- DOC001 `cvm2/cvm.c:40` function cvm_config_default is not documented
- DOC001 `cvm2/cvm.c:94` function cvm_destroy is not documented
- DOC001 `cvm2/cvm.c:113` function cvm_strerror is not documented
- DOC001 `cvm2/cvm.c:235` function cvm_heap_alloc is not documented
- DOC001 `cvm2/cvm.c:250` function cvm_set_args is not documented
- DOC001 `cvm2/cvm.c:283` function cvm_register_native is not documented
- DOC001 `cvm2/cvm.c:830` function cvm_load_module is not documented
- DOC001 `cvm2/cvm.c:923` function cvm_load_module_file is not documented
- DOC001 `cvm2/cvm.c:952` function cvm_run is not documented
- DOC001 `cvm2/cvm.c:994` function cvm_break_set is not documented
- DOC001 `cvm2/cvm.c:1003` function cvm_break_clear is not documented
- DOC001 `cvm2/cvm.c:1014` function cvm_break_clear_all is not documented
- DOC001 `cvm2/cvm.c:1018` function cvm_break_hit is not documented
- DOC001 `cvm2/cvm.c:1024` function cvm_profile_begin is not documented
- DOC001 `cvm2/cvm.c:1034` function cvm_profile_end is not documented
- DOC001 `cvm2/cvm.c:1351` function cvm_exit_code is not documented
- DOC001 `cvm2/cvm.c:1352` function cvm_instruction_count is not documented
- DOC001 `cvm2/cvm.h:1` module cvm2/cvm.h is not documented
- DOC001 `cvm2/cvm.h:41` macro CVM_MAGIC_0 is not documented
- DOC001 `cvm2/cvm.h:42` macro CVM_MAGIC_1 is not documented
- DOC001 `cvm2/cvm.h:43` macro CVM_MAGIC_2 is not documented
- DOC001 `cvm2/cvm.h:44` macro CVM_MAGIC_3 is not documented
- DOC001 `cvm2/cvm.h:45` macro CVM_VERSION_MAJOR is not documented
- DOC001 `cvm2/cvm.h:46` macro CVM_VERSION_MINOR is not documented
- DOC001 `cvm2/cvm.h:47` macro CVM_MODULE_HEADER_SIZE is not documented
- DOC001 `cvm2/cvm.h:48` macro CVM_FUNC_ENTRY_SIZE is not documented
- DOC001 `cvm2/cvm.h:49` macro CVM_GLOBAL_ENTRY_SIZE is not documented
- DOC001 `cvm2/cvm.h:50` macro CVM_NATIVE_ENTRY_SIZE is not documented
- DOC001 `cvm2/cvm.h:51` macro CVM_STRING_ENTRY_SIZE is not documented
- DOC001 `cvm2/cvm.h:53` macro CVM_MAX_NARGS is not documented
- DOC001 `cvm2/cvm.h:54` macro CVM_MAX_SARGS is not documented
- DOC001 `cvm2/cvm.h:55` macro CVM_SHIFT_MASK is not documented
- DOC001 `cvm2/cvm.h:56` macro CVM_SYS_READ is not documented
- DOC001 `cvm2/cvm.h:57` macro CVM_SYS_WRITE is not documented
- DOC001 `cvm2/cvm.h:58` macro CVM_SYS_EXIT is not documented
- DOC001 `cvm2/cvm.h:60` macro CVM_DATA_ARGC is not documented
- DOC001 `cvm2/cvm.h:61` macro CVM_DATA_ARGV is not documented
- DOC001 `cvm2/cvm.h:62` macro CVM_DATA_RSP is not documented
- DOC001 `cvm2/cvm.h:63` macro CVM_DATA_RBP is not documented
- DOC001 `cvm2/cvm.h:64` macro CVM_DATA_ARGS is not documented
- DOC001 `cvm2/cvm.h:65` macro CVM_DATA_RET is not documented
- DOC001 `cvm2/cvm.h:66` macro CVM_DATA_STACK_SIZE is not documented
- DOC001 `cvm2/cvm.h:154` struct CvmFuncEntry is not documented
- DOC001 `cvm2/cvm.h:162` struct CvmGlobalEntry is not documented
- DOC001 `cvm2/cvm.h:167` struct CvmNativeEntry is not documented
- DOC001 `cvm2/cvm.h:171` struct CvmStringEntry is not documented
- DOC001 `cvm2/cvm.h:176` struct CvmConfig is not documented
- DOC001 `cvm2/cvm.h:189` struct CvmFrame is not documented
- DOC001 `cvm2/cvm.h:198` struct CvmNative is not documented
- DOC001 `cvm2/cvm.h:203` macro CVM_MAX_BREAKPOINTS is not documented
- DOC001 `cvm2/cvm.h:205` struct CvmBreakpoint is not documented
- DOC001 `cvm2/cvm.h:209` struct CvmState is not documented
- DOC001 `cvm2/cvm.h:248` function cvm_destroy is not documented
- DOC001 `cvm2/cvm.h:249` function cvm_load_module is not documented
- DOC001 `cvm2/cvm.h:250` function cvm_load_module_file is not documented
- DOC001 `cvm2/cvm.h:251` function cvm_run is not documented
- DOC001 `cvm2/cvm.h:252` function cvm_continue is not documented
- DOC001 `cvm2/cvm.h:253` function cvm_step is not documented
- DOC001 `cvm2/cvm.h:254` function cvm_exit_code is not documented
- DOC001 `cvm2/cvm.h:255` function cvm_instruction_count is not documented
- DOC001 `cvm2/cvm.h:256` function cvm_strerror is not documented
- DOC001 `cvm2/cvm.h:258` function cvm_register_native is not documented
- DOC001 `cvm2/cvm.h:259` function cvm_set_args is not documented
- DOC001 `cvm2/cvm.h:260` function cvm_heap_alloc is not documented
- DOC001 `cvm2/cvm.h:262` function cvm_break_set is not documented
- DOC001 `cvm2/cvm.h:263` function cvm_break_clear is not documented
- DOC001 `cvm2/cvm.h:264` function cvm_break_clear_all is not documented
- DOC001 `cvm2/cvm.h:265` function cvm_break_hit is not documented
- DOC001 `cvm2/cvm.h:266` function cvm_profile_begin is not documented
- DOC001 `cvm2/cvm.h:267` function cvm_profile_end is not documented
- DOC001 `cvm2/cvm_dbg_main.c:1` module cvm2/cvm_dbg_main.c is not documented
- DOC001 `cvm2/cvm_dbg_main.c:18` macro DBG_LINE_MAX is not documented
- DOC001 `cvm2/cvm_dbg_main.c:19` macro DBG_PROFILE_TOP is not documented
- DOC001 `cvm2/cvm_dbg_main.c:337` function main is not documented
- DOC001 `cvm2/cvm_dis.c:1` module cvm2/cvm_dis.c is not documented
- DOC001 `cvm2/cvm_dis.c:11` macro CVM_DIS_LINE_MAX is not documented
- DOC001 `cvm2/cvm_dis.h:1` module cvm2/cvm_dis.h is not documented
- DOC001 `cvm2/cvm_dis_main.c:1` module cvm2/cvm_dis_main.c is not documented
- DOC001 `cvm2/cvm_dis_main.c:18` function main is not documented
- DOC001 `cvm2/cvm_jit.c:1` module cvm2/cvm_jit.c is not documented
- DOC001 `cvm2/cvm_jit.c:267` function error is not documented
- DOC001 `cvm2/cvm_jit.c:288` struct JitCtx is not documented
- DOC001 `cvm2/cvm_jit.c:603` macro EMIT_CMP is not documented
- DOC001 `cvm2/cvm_jit.c:624` macro EMIT_CMP_SIGNED is not documented
- DOC001 `cvm2/cvm_jit.c:636` macro EMIT_CMP_UNSIGNED is not documented
- DOC001 `cvm2/cvm_jit.c:1397` function cvm_jit_exec_one is not documented
- DOC001 `cvm2/cvm_jit.h:1` module cvm2/cvm_jit.h is not documented
- DOC001 `cvm2/cvm_jit.h:45` macro JIT_REG_VM is not documented
- DOC001 `cvm2/cvm_jit.h:46` macro JIT_REG_SLOTS is not documented
- DOC001 `cvm2/cvm_jit.h:47` macro JIT_REG_SP is not documented
- DOC001 `cvm2/cvm_jit.h:48` macro JIT_REG_FRAMES is not documented
- DOC001 `cvm2/cvm_jit.h:49` macro JIT_REG_FRAME is not documented
- DOC001 `cvm2/cvm_jit.h:53` macro JIT_SCRATCH2 is not documented
- DOC001 `cvm2/cvm_jit.h:54` macro JIT_SCRATCH3 is not documented
- DOC001 `cvm2/cvm_jit.h:55` macro JIT_SCRATCH4 is not documented
- DOC001 `cvm2/cvm_jit.h:56` macro JIT_SCRATCH5 is not documented
- DOC001 `cvm2/cvm_jit.h:72` struct JitFuncEntry is not documented
- DOC001 `cvm2/cvm_jit.h:84` struct JitIpMap is not documented
- DOC001 `cvm2/cvm_jit.h:93` macro JIT_MAX_FUNCS is not documented
- DOC001 `cvm2/cvm_jit.h:94` macro JIT_IP_MAP_SIZE is not documented
- DOC001 `cvm2/cvm_jit.h:96` struct CvmJitState is not documented
- DOC001 `cvm2/cvm_jit.h:145` function returns is not documented
- DOC001 `cvm2/cvm_jit_help.c:1` module cvm2/cvm_jit_help.c is not documented
- DOC001 `cvm2/cvm_jit_help.c:16` macro CVM_HEAP_ALIGN is not documented
- DOC001 `cvm2/cvm_jit_help.c:176` function cvm_jit_ret is not documented
- DOC001 `cvm2/cvm_jit_help.c:213` function cvm_jit_memcheck is not documented
- DOC001 `cvm2/cvm_jit_help.h:1` module cvm2/cvm_jit_help.h is not documented
- DOC001 `cvm2/cvm_jit_help.h:70` function to is not documented
- DOC001 `cvm2/cvm_jit_help.h:84` function region is not documented
- DOC001 `cvm2/cvm_jit_x86.c:1` module cvm2/cvm_jit_x86.c is not documented
- DOC001 `cvm2/cvm_jit_x86.c:26` macro JIT_BUF_ALLOC is not documented
- DOC001 `cvm2/cvm_jit_x86.c:27` macro JIT_BUF_FREE is not documented
- DOC001 `cvm2/cvm_jit_x86.c:29` macro JIT_BUF_ALLOC is not documented
- DOC001 `cvm2/cvm_jit_x86.c:31` macro JIT_BUF_FREE is not documented
- DOC001 `cvm2/cvm_jit_x86.c:32` macro JIT_BUF_FAILED is not documented
- DOC001 `cvm2/cvm_jit_x86.c:48` function jit_buf_free is not documented
- DOC001 `cvm2/cvm_jit_x86.c:56` function jit_buf_reset is not documented
- DOC001 `cvm2/cvm_jit_x86.c:61` function jit_buf_failed is not documented
- DOC001 `cvm2/cvm_jit_x86.c:89` function emit16 is not documented
- DOC001 `cvm2/cvm_jit_x86.c:94` function emit32 is not documented
- DOC001 `cvm2/cvm_jit_x86.c:99` function emit64 is not documented
- DOC001 `cvm2/cvm_jit_x86.c:104` function emit_bytes is not documented
- DOC001 `cvm2/cvm_jit_x86.h:1` module cvm2/cvm_jit_x86.h is not documented
- DOC001 `cvm2/cvm_jit_x86.h:53` macro JIT_MAX_PATCHES is not documented
- DOC001 `cvm2/cvm_jit_x86.h:55` struct JitPatches is not documented
- DOC001 `cvm2/cvm_jit_x86.h:64` function jit_buf_free is not documented
- DOC001 `cvm2/cvm_jit_x86.h:65` function jit_buf_reset is not documented
- DOC001 `cvm2/cvm_jit_x86.h:66` function jit_buf_failed is not documented
- DOC001 `cvm2/cvm_jit_x86.h:72` function emit16 is not documented
- DOC001 `cvm2/cvm_jit_x86.h:73` function emit32 is not documented
- DOC001 `cvm2/cvm_jit_x86.h:74` function emit64 is not documented
- DOC001 `cvm2/cvm_jit_x86.h:75` function emit_bytes is not documented
- DOC001 `cvm2/cvm_jit_x86.h:81` function reg_high3 is not documented
- DOC001 `cvm2/cvm_ops.c:1` module cvm2/cvm_ops.c is not documented
- DOC001 `cvm2/cvm_ops.c:70` macro OP_INFOS_LEN is not documented
- DOC001 `cvm2/cvm_ops.c:83` function cvm_ops_r8 is not documented
- DOC001 `cvm2/cvm_ops.c:89` function cvm_ops_ru32 is not documented
- DOC001 `cvm2/cvm_ops.c:101` function cvm_ops_ri64 is not documented
- DOC001 `cvm2/cvm_ops.h:1` module cvm2/cvm_ops.h is not documented
- DOC001 `cvm2/cvm_ops.h:30` struct CvmOpInfo is not documented
- DOC001 `cvm2/cvm_ops.h:45` function cvm_ops_ri64 is not documented
- DOC001 `cvm2/cvm_ops.h:46` function cvm_ops_ru32 is not documented
- DOC001 `cvm2/cvm_ops.h:47` function cvm_ops_r8 is not documented
- DOC001 `cvm2/cvm_val_main.c:1` module cvm2/cvm_val_main.c is not documented
- DOC001 `cvm2/cvm_val_main.c:15` macro CVM_VAL_MAX_FUNCS is not documented
- DOC001 `cvm2/cvm_val_main.c:16` macro CVM_VAL_MAX_GLOBALS is not documented
- DOC001 `cvm2/cvm_val_main.c:17` macro CVM_VAL_MAX_NATIVES is not documented
- DOC001 `cvm2/cvm_val_main.c:18` macro CVM_VAL_MAX_CODE is not documented
- DOC001 `cvm2/cvm_val_main.c:19` macro CVM_VAL_MAX_LOCALS is not documented
- DOC001 `cvm2/cvm_val_main.c:20` macro CVM_VAL_MAX_ARGS is not documented
- DOC001 `cvm2/cvm_val_main.c:31` macro CVM_VAL_MAX_SARGS is not documented
- DOC001 `cvm2/cvm_val_main.c:33` struct DepthRange is not documented
- DOC001 `cvm2/cvm_val_main.c:38` struct ValCtx is not documented
- DOC001 `cvm2/cvm_val_main.c:45` struct FuncCtx is not documented
- DOC001 `cvm2/cvm_val_main.c:456` function main is not documented
- DOC001 `cvm2/cvm_view.c:1` module cvm2/cvm_view.c is not documented
- DOC001 `cvm2/cvm_view.c:72` function cvm_view_func is not documented
- DOC001 `cvm2/cvm_view.h:1` module cvm2/cvm_view.h is not documented
- DOC001 `cvm2/cvm_view.h:19` struct CvmModuleView is not documented
- DOC001 `cvm2/cvm_view.h:46` function cvm_view_func is not documented
- DOC001 `cvm2/deepseek_bash_20260808_653f26.sh:1` module cvm2/deepseek_bash_20260808_653f26.sh is not documented
- DOC001 `cvm2/gen_fib_cvm.c:1` module cvm2/gen_fib_cvm.c is not documented
- DOC001 `cvm2/gen_fib_cvm.c:13` macro FIB_N is not documented
- DOC001 `cvm2/gen_fib_cvm.c:14` macro EXPECTED_FIB10 is not documented
- DOC001 `cvm2/gen_fib_cvm.c:15` macro EXPECTED_CALLS is not documented
- DOC001 `cvm2/gen_fib_cvm.c:64` function main is not documented
- DOC001 `cvm2/gen_minimal.c:1` module cvm2/gen_minimal.c is not documented
- DOC001 `cvm2/gen_minimal.c:30` function main is not documented
- DOC001 `gen_fib_cvm.c:1` module gen_fib_cvm.c is not documented
- DOC001 `gen_fib_cvm.c:7` function fib is not documented
- DOC001 `gen_fib_cvm.c:36` function main is not documented
