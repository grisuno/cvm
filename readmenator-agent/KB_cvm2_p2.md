# Subsystem: cvm2 (page 2 of 2)
Previous: [KB_cvm2.md](KB_cvm2.md)

## cvm2/cvm_jit_x86.h
- Doc: JitBuf: /* Condition codes for Jcc / SETcc enum { CC_O   = 0x0, CC_NO  = 0x1, CC_B   = 0x2...
- Layer: utility
- Language: h
- Symbols:
  - `JitBuf` (struct, line 40)
  - `JitPatch` (struct, line 48)
  - `JitPatches` (struct, line 55)
  - `reg_needs_rex` (function, line 80) `static inline int reg_needs_rex(int r)`
  - `reg_high3` (function, line 81) `static inline int reg_high3(int r)`
  - `jit_buf_init` (function, line 63) `void jit_buf_init(JitBuf *b, size_t initial_cap);`
  - `jit_buf_free` (function, line 64) `void jit_buf_free(JitBuf *b);`
  - `jit_buf_reset` (function, line 65) `void jit_buf_reset(JitBuf *b);`
  - `jit_buf_failed` (function, line 66) `int jit_buf_failed(const JitBuf *b);`
  - `emit8` (function, line 71) `void emit8(JitBuf *b, uint8_t v);`
  - `emit16` (function, line 72) `void emit16(JitBuf *b, uint16_t v);`
  - `emit32` (function, line 73) `void emit32(JitBuf *b, uint32_t v);`
  - `emit64` (function, line 74) `void emit64(JitBuf *b, uint64_t v);`
  - `emit_bytes` (function, line 75) `void emit_bytes(JitBuf *b, const void *data, size_t len);`
  - `emit_mov_reg_imm64` (function, line 88) `void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm);`
  - `emit_mov_reg_imm32` (function, line 91) `void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm);`
  - `emit_mov_reg_reg` (function, line 94) `void emit_mov_reg_reg(JitBuf *b, int dst, int src);`
  - `emit_mov_reg_mem` (function, line 97) `void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp);`
  - `emit_mov_mem_reg` (function, line 100) `void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src);`
  - `emit_movzx_reg_mem8` (function, line 103) `void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp);`
  - `emit_movzx_reg_mem16` (function, line 106) `void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp);`
  - `emit_movsx_reg_mem32` (function, line 109) `void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp);`
  - `emit_mov32_reg_mem` (function, line 112) `void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp);`
  - `emit_mov32_mem_reg` (function, line 115) `void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src);`
  - `emit_lea_sib` (function, line 121) `void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp);`
  - `emit_mov_reg_sib` (function, line 126) `void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale);`
  - `emit_mov_sib_reg` (function, line 129) `void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src);`
  - `emit_push` (function, line 136) `void emit_push(JitBuf *b, int reg);`
  - `emit_pop` (function, line 139) `void emit_pop(JitBuf *b, int reg);`
  - `emit_add_reg_reg` (function, line 146) `void emit_add_reg_reg(JitBuf *b, int dst, int src);`
  - `emit_add_reg_imm32` (function, line 149) `void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm);`
  - `emit_sub_reg_reg` (function, line 152) `void emit_sub_reg_reg(JitBuf *b, int dst, int src);`
  - `emit_sub_reg_imm32` (function, line 155) `void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm);`
  - `emit_imul_reg_reg` (function, line 158) `void emit_imul_reg_reg(JitBuf *b, int dst, int src);`
  - `emit_idiv_reg` (function, line 162) `void emit_idiv_reg(JitBuf *b, int divisor);`
  - `emit_div_reg` (function, line 166) `void emit_div_reg(JitBuf *b, int divisor);`
  - `emit_cqo` (function, line 169) `void emit_cqo(JitBuf *b);`
  - `emit_neg_reg` (function, line 172) `void emit_neg_reg(JitBuf *b, int reg);`
  - `emit_inc_reg` (function, line 175) `void emit_inc_reg(JitBuf *b, int reg);`
  - `emit_dec_reg` (function, line 178) `void emit_dec_reg(JitBuf *b, int reg);`
  - `emit_and_reg_reg` (function, line 185) `void emit_and_reg_reg(JitBuf *b, int dst, int src);`
  - `emit_or_reg_reg` (function, line 188) `void emit_or_reg_reg(JitBuf *b, int dst, int src);`
  - `emit_xor_reg_reg` (function, line 191) `void emit_xor_reg_reg(JitBuf *b, int dst, int src);`
  - `emit_not_reg` (function, line 194) `void emit_not_reg(JitBuf *b, int reg);`
  - `emit_shl_reg_cl` (function, line 197) `void emit_shl_reg_cl(JitBuf *b, int reg);`
  - `emit_shr_reg_cl` (function, line 200) `void emit_shr_reg_cl(JitBuf *b, int reg);`
  - `emit_sar_reg_cl` (function, line 203) `void emit_sar_reg_cl(JitBuf *b, int reg);`
  - `emit_xor_reg_self` (function, line 206) `void emit_xor_reg_self(JitBuf *b, int reg);`
  - `emit_cmp_reg_reg` (function, line 213) `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg);`
  - `emit_test_reg_reg` (function, line 216) `void emit_test_reg_reg(JitBuf *buf, int a, int breg);`
  - `emit_setcc` (function, line 219) `void emit_setcc(JitBuf *b, int cc, int dst);`
  - `emit_jmp_rel32` (function, line 226) `size_t emit_jmp_rel32(JitBuf *b, int32_t rel);`
  - `emit_jcc_rel32` (function, line 229) `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel);`
  - `emit_jmp_buf` (function, line 232) `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p);`
  - `emit_jcc_buf` (function, line 235) `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p);`
  - `jit_apply_patches` (function, line 238) `void jit_apply_patches(JitBuf *b, const JitPatches *p);`
  - `emit_call_rel32` (function, line 241) `size_t emit_call_rel32(JitBuf *b, int32_t rel);`
  - `emit_call_reg` (function, line 244) `void emit_call_reg(JitBuf *b, int reg);`
  - `emit_ret` (function, line 247) `void emit_ret(JitBuf *b);`
  - `emit_syscall` (function, line 254) `void emit_syscall(JitBuf *b);`
  - `emit_int3` (function, line 257) `void emit_int3(JitBuf *b);`
  - `emit_nop` (function, line 260) `void emit_nop(JitBuf *b);`
  - `emit_call_abs` (function, line 269) `void emit_call_abs(JitBuf *b, void *func, int scratch);`
  - `emit_and_reg_imm32` (function, line 272) `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm);`
  - `emit_movzx_reg_reg8` (function, line 275) `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src);`
  - `emit_rex` (function, line 278) `void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b);`
  - `emit_modrm` (function, line 281) `void emit_modrm(JitBuf *buf, int mod, int reg, int rm);`
  - `emit_mov_mem_imm8` (function, line 288) `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm);`
  - `emit_mov_mem_imm32` (function, line 291) `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm);`
  - `CVM_JIT_X86_H` (macro, line 10) `#define CVM_JIT_X86_H`
  - `JIT_MAX_PATCHES` (macro, line 53) `#define JIT_MAX_PATCHES`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

## cvm2/cvm_ops.c
- Layer: utility
- Language: c
- Symbols:
  - `cvm_op_info` (function, line 72) `const CvmOpInfo *cvm_op_info(uint8_t opcode)`
  - `cvm_op_name` (function, line 78) `const char *cvm_op_name(uint8_t opcode)`
  - `cvm_ops_r8` (function, line 83) `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out)`
  - `cvm_ops_ru32` (function, line 89) `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off)`
  - `cvm_ops_ri32` (function, line 97) `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off)`
  - `cvm_ops_ri64` (function, line 101) `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off)`
  - `OP_INFOS_LEN` (macro, line 70) `#define OP_INFOS_LEN`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

## cvm2/cvm_ops.h
- Doc: cvm_op_info: CVM_OPK_U32   = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL   = 6, CVM_OPK_U8U8  = 7 }...
- Layer: utility
- Language: h
- Symbols:
  - `CvmOpInfo` (struct, line 30)
  - `cvm_op_info` (function, line 38) `const CvmOpInfo *cvm_op_info(uint8_t opcode);`
  - `cvm_op_name` (function, line 41) `const char *cvm_op_name(uint8_t opcode);`
  - `cvm_ops_ri32` (function, line 44) `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off);`
  - `cvm_ops_ri64` (function, line 45) `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off);`
  - `cvm_ops_ru32` (function, line 46) `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off);`
  - `cvm_ops_r8` (function, line 47) `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out);`
  - `CvmOpKind` (variable, line 16) `extern "C" { #endif typedef enum { CVM_OPK_NONE = 0, CVM_OPK_I8 = 1, CVM_OPK_I32 = 2, CVM_OPK_I64 = 3, CVM_OPK_U32 =...`
  - `CVM_OPS_H` (macro, line 10) `#define CVM_OPS_H`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_ops.c`, `cvm2/cvm_val_main.c`

## cvm2/cvm_val_main.c
- Doc: StackEffect: Stack effect of one instruction on the interval [lo,hi]: * required pops, then the...
- Layer: utility
- Language: c
- Symbols:
  - `DepthRange` (struct, line 33)
  - `ValCtx` (struct, line 38)
  - `FuncCtx` (struct, line 45)
  - `StackEffect` (struct, line 97)
  - `val_err` (function, line 56) `static void val_err(ValCtx *ctx, const char *what)`
  - `val_fun_err` (function, line 61) `static void val_fun_err(FuncCtx *fc, const char *what)`
  - `code_of` (function, line 68) `static const uint8_t *code_of(const CvmModuleView *v)`
  - `q_push` (function, line 72) `static void q_push(FuncCtx *fc, size_t off)`
  - `q_pop` (function, line 81) `static size_t q_pop(FuncCtx *fc)`
  - `dr_merge` (function, line 88) `static int dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)`
  - `stack_effect` (function, line 103) `static int stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...`
  - `check_static` (function, line 181) `static int check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)`
  - `analyze_stack` (function, line 361) `static int analyze_stack(FuncCtx *fc)`
  - `check_function` (function, line 435) `static int check_function(FuncCtx *fc, size_t *insn_count)`
  - `cmp_func` (function, line 450) `static int cmp_func(const void *a, const void *b)`
  - `main` (function, line 456) `int main(int argc, char **argv)`
  - `CVM_VAL_MAX_FUNCS` (macro, line 15) `#define CVM_VAL_MAX_FUNCS`
  - `CVM_VAL_MAX_GLOBALS` (macro, line 16) `#define CVM_VAL_MAX_GLOBALS`
  - `CVM_VAL_MAX_NATIVES` (macro, line 17) `#define CVM_VAL_MAX_NATIVES`
  - `CVM_VAL_MAX_CODE` (macro, line 18) `#define CVM_VAL_MAX_CODE`
  - `CVM_VAL_MAX_LOCALS` (macro, line 19) `#define CVM_VAL_MAX_LOCALS`
  - `CVM_VAL_MAX_ARGS` (macro, line 20) `#define CVM_VAL_MAX_ARGS`
  - `CVM_VAL_STACK_CAP` (macro, line 25) `#define CVM_VAL_STACK_CAP`
  - `CVM_VAL_WIDEN_BOUND` (macro, line 30) `#define CVM_VAL_WIDEN_BOUND`
  - `CVM_VAL_MAX_SARGS` (macro, line 31) `#define CVM_VAL_MAX_SARGS`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

## cvm2/cvm_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `rl32` (function, line 9) `static uint32_t rl32(const uint8_t *p)`
  - `rl16` (function, line 14) `static uint32_t rl16(const uint8_t *p)`
  - `cvm_view_strerror` (function, line 18) `const char *cvm_view_strerror(int error_code)`
  - `cvm_view_open` (function, line 29) `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size)`
  - `cvm_view_func` (function, line 72) `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i)`
  - `cvm_view_string` (function, line 78) `const char *cvm_view_string(const CvmModuleView *v, uint32_t off)`
  - `cvm_view_func_name` (function, line 87) `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,
                             ...`
  - `cvm_view_func_region` (function, line 108) `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,
                         size_t *be...`
- Depends on: `cvm2/cvm_view.h`

## cvm2/cvm_view.h
- Doc: cvm_view_open: uint32_t       num_strings; uint32_t       code_size; uint32_t...
- Layer: presentation
- Language: h
- Symbols:
  - `CvmModuleView` (struct, line 19)
  - `cvm_view_open` (function, line 41) `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size);`
  - `cvm_view_strerror` (function, line 44) `const char *cvm_view_strerror(int error_code);`
  - `cvm_view_func` (function, line 46) `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i);`
  - `cvm_view_string` (function, line 50) `const char *cvm_view_string(const CvmModuleView *v, uint32_t off);`
  - `cvm_view_func_name` (function, line 53) `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi, char *fallback, size_t cap);`
  - `cvm_view_func_region` (function, line 58) `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi, size_t *begin, size_t *end);`
  - `data` (variable, line 16) `extern "C" { #endif typedef struct { const uint8_t *data;`
  - `CVM_VIEW_H` (macro, line 9) `#define CVM_VIEW_H`
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.h`, `cvm2/cvm_dis_main.c`, `cvm2/cvm_val_main.c`, `cvm2/cvm_view.c`

## cvm2/deepseek_bash_20260808_653f26.sh
- Layer: utility
- Language: sh

## cvm2/gen_fib_cvm.c
- Layer: utility
- Language: c
- Symbols:
  - `emit_byte` (function, line 21) `static void emit_byte(uint8_t b)`
  - `emit_u32` (function, line 30) `static void emit_u32(uint32_t v)`
  - `emit_i32` (function, line 37) `static void emit_i32(int32_t v)`
  - `patch_i32` (function, line 39) `static void patch_i32(size_t pos, int32_t val)`
  - `write_le32` (function, line 46) `static void write_le32(uint8_t *p, uint32_t v)`
  - `emit_global_inc` (function, line 53) `static void emit_global_inc(void)`
  - `main` (function, line 64) `int main(int argc, char *argv[])`
  - `FIB_N` (macro, line 13) `#define FIB_N`
  - `EXPECTED_FIB10` (macro, line 14) `#define EXPECTED_FIB10`
  - `EXPECTED_CALLS` (macro, line 15) `#define EXPECTED_CALLS`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

## cvm2/gen_minimal.c
- Layer: utility
- Language: c
- Symbols:
  - `emit_byte` (function, line 14) `static void emit_byte(uint8_t b)`
  - `emit_u32` (function, line 21) `static void emit_u32(uint32_t v)`
  - `write_le32` (function, line 25) `static void write_le32(uint8_t *p, uint32_t v)`
  - `main` (function, line 30) `int main(void)`
- Depends on: `cvm2/cvm.h`

## cvm2/gen_test.py
- Doc: Generate a minimal .cvm that pushes 42 and halts.
- Layer: testing
- Language: py
- Symbols:
  - `emit_byte` (function, line 7) `def emit_byte(b)`
  - `emit_u32` (function, line 10) `def emit_u32(v)`

## cvm2/test.sh
- Doc: CVM v2 toolchain suite: interpreter, disassembler, validator (including corrupted-module...
- Layer: testing
- Language: sh
- Symbols:
  - `check` (function, line 13)
  - `reject` (function, line 24)

