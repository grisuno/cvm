/**
 * @file cvm_jit_x86.h
 * @brief x86-64 code emitter for the CVM JIT compiler.
 * @license GPL-2.0-or-later
 *
 * Minimal assembler that emits x86-64 instructions into a growable buffer.
 * Designed for the CVM JIT: only the instructions the JIT actually needs.
 */
#ifndef CVM_JIT_X86_H
#define CVM_JIT_X86_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* x86-64 register identifiers (matching hardware encoding) */
enum {
    XAX = 0, XCX = 1, XDX = 2, XBX = 3,
    XSP = 4, XBP = 5, XSI = 6, XDI = 7,
    X8  = 8, X9  = 9, X10 = 10, X11 = 11,
    X12 = 12, X13 = 13, X14 = 14, X15 = 15
};

/* Condition codes for Jcc / SETcc */
enum {
    CC_O   = 0x0, CC_NO  = 0x1,
    CC_B   = 0x2, CC_AE  = 0x3,
    CC_E   = 0x4, CC_NE  = 0x5,
    CC_BE  = 0x6, CC_A   = 0x7,
    CC_S   = 0x8, CC_NS  = 0x9,
    CC_P   = 0xA, CC_NP  = 0xB,
    CC_L   = 0xC, CC_GE  = 0xD,
    CC_LE  = 0xE, CC_G   = 0xF
};

/* Growable code buffer backed by mmap'd RWX memory */
typedef struct {
    uint8_t *code;
    size_t   size;       /* current write offset */
    size_t   capacity;   /* allocated size */
    int      failed;     /* set on OOM or overflow */
} JitBuf;

/* Forward patch entry for unresolved jumps */
typedef struct {
    size_t patch_off;    /* offset in buf->code where rel32 lives */
    size_t target;       /* absolute target offset in the same buffer */
} JitPatch;

#define JIT_MAX_PATCHES 8192

typedef struct {
    JitPatch patches[JIT_MAX_PATCHES];
    size_t   count;
} JitPatches;

/* ------------------------------------------------------------------ */
/*  Buffer lifecycle                                                   */
/* ------------------------------------------------------------------ */
void  jit_buf_init(JitBuf *b, size_t initial_cap);
void  jit_buf_free(JitBuf *b);
void  jit_buf_reset(JitBuf *b);
int   jit_buf_failed(const JitBuf *b);

/* ------------------------------------------------------------------ */
/*  Byte emission (little-endian)                                       */
/* ------------------------------------------------------------------ */
void  emit8(JitBuf *b, uint8_t v);
void  emit16(JitBuf *b, uint16_t v);
void  emit32(JitBuf *b, uint32_t v);
void  emit64(JitBuf *b, uint64_t v);
void  emit_bytes(JitBuf *b, const void *data, size_t len);

/* ------------------------------------------------------------------ */
/*  Register checks                                                    */
/* ------------------------------------------------------------------ */
static inline int reg_needs_rex(int r) { return r >= X8; }
static inline int reg_high3(int r) { return (r >> 3) & 1; }

/* ------------------------------------------------------------------ */
/*  Data movement                                                      */
/* ------------------------------------------------------------------ */

/* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64) */
void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm);

/* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32) */
void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm);

/* MOV r64, r64  (3 bytes: REX.W 89 /r) */
void emit_mov_reg_reg(JitBuf *b, int dst, int src);

/* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10) */
void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp);

/* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10) */
void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src);

/* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10) */
void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp);

/* MOVZX r64, word [base + disp32]  (4 bytes: REX.W 0F B7 /r mod=10) */
void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp);

/* MOVSX r64, dword [base + disp32]  (4 bytes: REX.W 63 /r mod=10) */
void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp);

/* MOV r32, [base + disp32]  (zero-extends to r64, 6 bytes: 8B /r mod=10) */
void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp);

/* MOV [base + disp32], r32  (6 bytes: 89 /r mod=10) */
void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src);

/* LEA r64, [base + index*scale + disp]
 * scale: 0=1, 1=2, 2=4, 3=8
 * If index == -1, encodes [base + disp] only.
 */
void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp);

/* MOV r64, [base + index*scale]  (no displacement)
 * scale: 0=1, 1=2, 2=4, 3=8
 */
void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale);

/* MOV [base + index*scale], r64  (no displacement) */
void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src);

/* ------------------------------------------------------------------ */
/*  Stack operations                                                   */
/* ------------------------------------------------------------------ */

/* PUSH r64 (1 or 2 bytes depending on register) */
void emit_push(JitBuf *b, int reg);

/* POP r64 */
void emit_pop(JitBuf *b, int reg);

/* ------------------------------------------------------------------ */
/*  Arithmetic                                                         */
/* ------------------------------------------------------------------ */

/* ADD r64, r64  (REX.W 01 /r) */
void emit_add_reg_reg(JitBuf *b, int dst, int src);

/* ADD r64, imm32  (sign-extended) */
void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm);

/* SUB r64, r64  (REX.W 29 /r) */
void emit_sub_reg_reg(JitBuf *b, int dst, int src);

/* SUB r64, imm32 */
void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm);

/* IMUL r64, r64  (REX.W 0F AF /r) */
void emit_imul_reg_reg(JitBuf *b, int dst, int src);

/* IDIV r64  (divides RDX:RAX by r64, quotient in RAX, remainder in RDX)
 * Requires RDX=0 before unsigned, or use CQO for signed. */
void emit_idiv_reg(JitBuf *b, int divisor);

/* DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX)
 * Requires RDX=0 before (xor edx,edx). */
void emit_div_reg(JitBuf *b, int divisor);

/* CQO  (sign-extend RAX into RDX:RAX) */
void emit_cqo(JitBuf *b);

/* NEG r64  (REX.W F7 /3) */
void emit_neg_reg(JitBuf *b, int reg);

/* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies) */
void emit_inc_reg(JitBuf *b, int reg);

/* DEC r64 */
void emit_dec_reg(JitBuf *b, int reg);

/* ------------------------------------------------------------------ */
/*  Bitwise                                                            */
/* ------------------------------------------------------------------ */

/* AND r64, r64 */
void emit_and_reg_reg(JitBuf *b, int dst, int src);

/* OR r64, r64 */
void emit_or_reg_reg(JitBuf *b, int dst, int src);

/* XOR r64, r64 */
void emit_xor_reg_reg(JitBuf *b, int dst, int src);

/* NOT r64 */
void emit_not_reg(JitBuf *b, int reg);

/* SHL r64, CL  (shift left by CL) */
void emit_shl_reg_cl(JitBuf *b, int reg);

/* SHR r64, CL  (logical shift right) */
void emit_shr_reg_cl(JitBuf *b, int reg);

/* SAR r64, CL  (arithmetic shift right) */
void emit_sar_reg_cl(JitBuf *b, int reg);

/* XOR reg, reg (zero-idiom, 3 bytes) */
void emit_xor_reg_self(JitBuf *b, int reg);

/* ------------------------------------------------------------------ */
/*  Comparison                                                         */
/* ------------------------------------------------------------------ */

/* CMP r64, r64  (REX.W 39 /r) */
void emit_cmp_reg_reg(JitBuf *buf, int a, int breg);

/* TEST r64, r64  (REX.W 85 /r) */
void emit_test_reg_reg(JitBuf *buf, int a, int breg);

/* SETcc r/m8  (0F 9x /0) */
void emit_setcc(JitBuf *b, int cc, int dst);

/* ------------------------------------------------------------------ */
/*  Control flow                                                       */
/* ------------------------------------------------------------------ */

/* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching */
size_t emit_jmp_rel32(JitBuf *b, int32_t rel);

/* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching */
size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel);

/* JMP to absolute offset within the buffer (emits rel32, records patch) */
void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p);

/* Jcc to absolute offset within the buffer */
void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p);

/* Apply all patches: for each patch, compute rel32 = target - (patch_off + 4) */
void jit_apply_patches(JitBuf *b, const JitPatches *p);

/* CALL rel32  (E8 imm32) */
size_t emit_call_rel32(JitBuf *b, int32_t rel);

/* CALL r/m64  (FF /2, 2 bytes) */
void emit_call_reg(JitBuf *b, int reg);

/* RET  (C3) */
void emit_ret(JitBuf *b);

/* ------------------------------------------------------------------ */
/*  System                                                             */
/* ------------------------------------------------------------------ */

/* SYSCALL  (0F 05) */
void emit_syscall(JitBuf *b);

/* INT3  (CC) -- debug breakpoint */
void emit_int3(JitBuf *b);

/* NOP  (90) */
void emit_nop(JitBuf *b);

/* ------------------------------------------------------------------ */
/*  Relative call to C function                                        */
/* ------------------------------------------------------------------ */

/* Emit a CALL to a C function pointer (trampoline-free, uses absolute call).
 * Loads the function address into a scratch register and calls it.
 * Clobbers: the scratch register used. */
void emit_call_abs(JitBuf *b, void *func, int scratch);

/* AND r64, imm32 */
void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm);

/* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension */
void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src);

/* REX prefix: exposed for inline asm emission */
void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b);

/* ModRM byte: exposed for inline asm emission */
void emit_modrm(JitBuf *buf, int mod, int reg, int rm);

/* ------------------------------------------------------------------ */
/*  Misc                                                               */
/* ------------------------------------------------------------------ */

/* MOV byte [base + disp], imm8  (REX.C6 /0) */
void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm);

/* MOV qword [base + disp], imm32 (sign-extended)  (REX.W C7 /0) */
void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm);

#ifdef __cplusplus
}
#endif
#endif /* CVM_JIT_X86_H */
