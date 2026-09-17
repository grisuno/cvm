/**
 * @file cvm_jit_x86.c
 * @brief x86-64 code emitter implementation for the CVM JIT compiler.
 * @license GPL-2.0-or-later
 *
 * Encodes x86-64 instructions into a growable buffer.  All memory
 * operands use the System V ABI register conventions.  The emitter is
 * self-contained: no dependency on the CVM headers.
 */
#include "cvm_jit_x86.h"
#include <stdlib.h>
#include <string.h>
#ifndef CVM_FREESTANDING
#include <sys/mman.h>
#endif

/* ------------------------------------------------------------------ */
/*  Buffer lifecycle                                                   */
/* ------------------------------------------------------------------ */

/* The JIT buffer must be executable.  On the host we map it with
 * PROT_EXEC; in a freestanding kernel the heap is identity-mapped
 * executable, so a plain malloc (which the kernel routes to kmalloc)
 * is sufficient and no mmap exists. */
#ifdef CVM_FREESTANDING
#define JIT_BUF_ALLOC(sz)      malloc(sz)
#define JIT_BUF_FREE(p, sz)    free(p)
#else
#define JIT_BUF_ALLOC(sz)      mmap(NULL, (sz), PROT_READ | PROT_WRITE | PROT_EXEC, \
                                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)
#define JIT_BUF_FREE(p, sz)    munmap((p), (sz))
#define JIT_BUF_FAILED         MAP_FAILED
#endif

void jit_buf_init(JitBuf *b, size_t cap) {
    if (cap < 4096) cap = 4096;
    b->code = (uint8_t *)JIT_BUF_ALLOC(cap);
#ifdef CVM_FREESTANDING
    if (!b->code) { b->failed = 1; cap = 0; }
#else
    if (b->code == MAP_FAILED) { b->code = NULL; b->failed = 1; cap = 0; }
#endif
    b->size = 0;
    b->capacity = cap;
    b->failed = (b->code == NULL);
}

void jit_buf_free(JitBuf *b) {
    if (b->code && b->capacity)
        JIT_BUF_FREE(b->code, b->capacity);
    b->code = NULL;
    b->size = 0;
    b->capacity = 0;
}

void jit_buf_reset(JitBuf *b) {
    b->size = 0;
    b->failed = 0;
}

int jit_buf_failed(const JitBuf *b) { return b->failed; }

/* ------------------------------------------------------------------ */
/*  Byte emission                                                      */
/* ------------------------------------------------------------------ */

static void emit_grow(JitBuf *b, size_t need) {
    if (b->failed) return;
    if (b->size + need <= b->capacity) return;
    size_t new_cap = b->capacity;
    while (new_cap < b->size + need) new_cap *= 2;
    uint8_t *p = (uint8_t *)JIT_BUF_ALLOC(new_cap);
#ifdef CVM_FREESTANDING
    if (!p) { b->failed = 1; return; }
#else
    if (p == MAP_FAILED) { b->failed = 1; return; }
#endif
    if (b->size) memcpy(p, b->code, b->size);
    JIT_BUF_FREE(b->code, b->capacity);
    b->code = p;
    b->capacity = new_cap;
}

void emit8(JitBuf *b, uint8_t v) {
    emit_grow(b, 1);
    if (!b->failed) b->code[b->size++] = v;
}

void emit16(JitBuf *b, uint16_t v) {
    emit_grow(b, 2);
    if (!b->failed) { memcpy(b->code + b->size, &v, 2); b->size += 2; }
}

void emit32(JitBuf *b, uint32_t v) {
    emit_grow(b, 4);
    if (!b->failed) { memcpy(b->code + b->size, &v, 4); b->size += 4; }
}

void emit64(JitBuf *b, uint64_t v) {
    emit_grow(b, 8);
    if (!b->failed) { memcpy(b->code + b->size, &v, 8); b->size += 8; }
}

void emit_bytes(JitBuf *b, const void *data, size_t len) {
    emit_grow(b, len);
    if (!b->failed) { memcpy(b->code + b->size, data, len); b->size += len; }
}

/* ------------------------------------------------------------------ */
/*  Internal encoding helpers                                          */
/* ------------------------------------------------------------------ */

/* REX prefix: 0100 WRXB */
void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b) {
    emit8(buf, (uint8_t)(0x40 | (w << 3) | (r << 2) | (x << 1) | rex_b));
}

/* ModRM byte */
void emit_modrm(JitBuf *b, int mod, int reg, int rm) {
    emit8(b, (uint8_t)((mod << 6) | ((reg & 7) << 3) | (rm & 7)));
}

/* ModRM + disp32 */
static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp) {
    emit_modrm(b, 2, reg, rm);
    emit32(b, (uint32_t)disp);
}

/* REX.W + opcode + ModRM(reg, r/m) -- 3-byte core for reg,reg ops */
static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm) {
    emit_rex(b, 1, reg_high3(reg), 0, reg_high3(rm));
    emit8(b, opc);
    emit_modrm(b, 3, reg, rm);
}

/* SIB byte */
static void emit_sib(JitBuf *b, int scale, int index, int base) {
    emit8(b, (uint8_t)((scale << 6) | ((index & 7) << 3) | (base & 7)));
}

/* ------------------------------------------------------------------ */
/*  Data movement                                                      */
/* ------------------------------------------------------------------ */

void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm) {
    /* REX.W + B8+rd + imm64 */
    emit_rex(b, 1, 0, 0, reg_high3(dst));
    emit8(b, (uint8_t)(0xB8 + (dst & 7)));
    emit64(b, imm);
}

void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm) {
    if (imm == 0) {
        /* XOR reg, reg -- shorter zero-idiom (3 bytes) */
        emit_xor_reg_self(b, dst);
        return;
    }
    /* REX.W + C7 /0 r/m + imm32 (sign-extended) -- 7 bytes */
    emit_rex(b, 1, 0, 0, reg_high3(dst));
    emit8(b, 0xC7);
    emit_modrm(b, 3, 0, dst);
    emit32(b, (uint32_t)imm);
}

void emit_mov_reg_reg(JitBuf *b, int dst, int src) {
    if (dst == src) return;
    /* REX.W + 89 /r (src -> dst, opcode direction bit = 1) */
    emit_rex_op_modrm(b, 0x89, src, dst);
}

void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp) {
    /* REX.W + 8B /r mod=10 + disp32 */
    emit_rex(b, 1, reg_high3(dst), 0, reg_high3(base));
    emit8(b, 0x8B);
    emit_modrm_disp32(b, dst, base, disp);
}

void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src) {
    /* REX.W + 89 /r mod=10 + disp32 */
    emit_rex(b, 1, reg_high3(src), 0, reg_high3(base));
    emit8(b, 0x89);
    emit_modrm_disp32(b, src, base, disp);
}

void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp) {
    /* REX.W + 0F B6 /r mod=10 + disp32 */
    emit_rex(b, 1, reg_high3(dst), 0, reg_high3(base));
    emit8(b, 0x0F); emit8(b, 0xB6);
    emit_modrm_disp32(b, dst, base, disp);
}

void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp) {
    /* REX.W + 0F B7 /r mod=10 + disp32 */
    emit_rex(b, 1, reg_high3(dst), 0, reg_high3(base));
    emit8(b, 0x0F); emit8(b, 0xB7);
    emit_modrm_disp32(b, dst, base, disp);
}

void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp) {
    /* REX.W + 63 /r mod=10 + disp32 (MOVSXD) */
    emit_rex(b, 1, reg_high3(dst), 0, reg_high3(base));
    emit8(b, 0x63);
    emit_modrm_disp32(b, dst, base, disp);
}

void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp) {
    /* 8B /r mod=10 + disp32 (no REX.W, zero-extends to 64-bit) */
    if (reg_high3(base) || reg_high3(dst))
        emit_rex(b, 0, reg_high3(dst), 0, reg_high3(base));
    emit8(b, 0x8B);
    emit_modrm_disp32(b, dst, base, disp);
}

void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src) {
    /* 89 /r mod=10 + disp32 -- MOV r/m32, r32 (no REX.W, zero-extends) */
    if (reg_high3(base) || reg_high3(src))
        emit_rex(b, 0, reg_high3(src), 0, reg_high3(base));
    emit8(b, 0x89);
    emit_modrm_disp32(b, src, base, disp);
}

void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp) {
    if (index == -1) {
        /* [base + disp] -- LEA with no index */
        emit_rex(b, 1, reg_high3(dst), 0, reg_high3(base));
        emit8(b, 0x8D);
        if (disp == 0 && (base & 7) != XBP) {
            emit_modrm(b, 0, dst, base);
        } else if (disp >= -128 && disp <= 127) {
            emit_modrm(b, 1, dst, base);
            emit8(b, (uint8_t)(int8_t)disp);
        } else {
            emit_modrm_disp32(b, dst, base, disp);
        }
        return;
    }
    /* [base + index*scale + disp] via SIB.
     * mod=00: no disp (except base=RBP/R13 which needs disp8=0)
     * mod=01: disp8
     * mod=10: disp32 */
    int mod;
    if (disp == 0 && (base & 7) != XBP)
        mod = 0;
    else if (disp >= -128 && disp <= 127)
        mod = 1;
    else
        mod = 2;

    emit_rex(b, 1, reg_high3(dst), reg_high3(index), reg_high3(base));
    emit8(b, 0x8D);
    emit_modrm(b, mod, dst, 4 /* SIB follows */);
    emit_sib(b, scale, index, base);
    if (mod == 1)
        emit8(b, (uint8_t)(int8_t)disp);
    else if (mod == 2)
        emit32(b, (uint32_t)disp);
}

void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale) {
    /* REX.W + 8B /r SIB(mod=00) */
    emit_rex(b, 1, reg_high3(dst), reg_high3(index), reg_high3(base));
    emit8(b, 0x8B);
    emit_modrm(b, 0, dst, 4);
    emit_sib(b, scale, index, base);
}

void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src) {
    /* REX.W + 89 /r SIB(mod=00) */
    emit_rex(b, 1, reg_high3(src), reg_high3(index), reg_high3(base));
    emit8(b, 0x89);
    emit_modrm(b, 0, src, 4);
    emit_sib(b, scale, index, base);
}

/* ------------------------------------------------------------------ */
/*  Stack operations                                                   */
/* ------------------------------------------------------------------ */

void emit_push(JitBuf *b, int reg) {
    if (reg_needs_rex(reg))
        emit8(b, 0x41); /* REX.B=1 */
    emit8(b, (uint8_t)(0x50 + (reg & 7)));
}

void emit_pop(JitBuf *b, int reg) {
    if (reg_needs_rex(reg))
        emit8(b, 0x41);
    emit8(b, (uint8_t)(0x58 + (reg & 7)));
}

/* ------------------------------------------------------------------ */
/*  Arithmetic                                                         */
/* ------------------------------------------------------------------ */

void emit_add_reg_reg(JitBuf *b, int dst, int src) {
    emit_rex_op_modrm(b, 0x01, src, dst); /* ADD r/m64, r64 */
}

void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm) {
    if (imm == 0) return;
    /* REX.W + 81 /0 r/m + imm32 */
    emit_rex(b, 1, 0, 0, reg_high3(dst));
    emit8(b, 0x81);
    emit_modrm(b, 3, 0, dst);
    emit32(b, (uint32_t)imm);
}

void emit_sub_reg_reg(JitBuf *b, int dst, int src) {
    emit_rex_op_modrm(b, 0x29, src, dst); /* SUB r/m64, r64 */
}

void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm) {
    /* REX.W + 81 /5 r/m + imm32 */
    emit_rex(b, 1, 0, 0, reg_high3(dst));
    emit8(b, 0x81);
    emit_modrm(b, 3, 5, dst);
    emit32(b, (uint32_t)imm);
}

void emit_imul_reg_reg(JitBuf *b, int dst, int src) {
    /* REX.W + 0F AF /r -- IMUL r64, r/m64 */
    emit_rex(b, 1, reg_high3(dst), 0, reg_high3(src));
    emit8(b, 0x0F); emit8(b, 0xAF);
    emit_modrm(b, 3, dst, src);
}

void emit_idiv_reg(JitBuf *b, int divisor) {
    /* REX.W + F7 /7 r/m64 -- IDIV r/m64 (divides RDX:RAX) */
    emit_rex(b, 1, 0, 0, reg_high3(divisor));
    emit8(b, 0xF7);
    emit_modrm(b, 3, 7, divisor);
}

void emit_div_reg(JitBuf *b, int divisor) {
    /* REX.W + F7 /6 r/m64 -- DIV r/m64 (divides RDX:RAX, unsigned) */
    emit_rex(b, 1, 0, 0, reg_high3(divisor));
    emit8(b, 0xF7);
    emit_modrm(b, 3, 6, divisor);
}

void emit_cqo(JitBuf *b) {
    /* REX.W + 99 -- CQO (sign-extend RAX into RDX:RAX) */
    emit8(b, 0x48);
    emit8(b, 0x99);
}

void emit_neg_reg(JitBuf *b, int reg) {
    /* REX.W + F7 /3 r/m64 */
    emit_rex(b, 1, 0, 0, reg_high3(reg));
    emit8(b, 0xF7);
    emit_modrm(b, 3, 3, reg);
}

void emit_inc_reg(JitBuf *b, int reg) {
    /* REX.W + FF /0 r/m64 */
    emit_rex(b, 1, 0, 0, reg_high3(reg));
    emit8(b, 0xFF);
    emit_modrm(b, 3, 0, reg);
}

void emit_dec_reg(JitBuf *b, int reg) {
    /* REX.W + FF /1 r/m64 */
    emit_rex(b, 1, 0, 0, reg_high3(reg));
    emit8(b, 0xFF);
    emit_modrm(b, 3, 1, reg);
}

/* ------------------------------------------------------------------ */
/*  Bitwise                                                            */
/* ------------------------------------------------------------------ */

void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm) {
    /* REX.W + 81 /4 r/m + imm32 */
    emit_rex(buf, 1, 0, 0, reg_high3(dst));
    emit8(buf, 0x81);
    emit_modrm(buf, 3, 4, dst);
    emit32(buf, (uint32_t)imm);
}

void emit_and_reg_reg(JitBuf *b, int dst, int src) {
    emit_rex_op_modrm(b, 0x21, src, dst); /* AND r/m64, r64 */
}

void emit_or_reg_reg(JitBuf *b, int dst, int src) {
    emit_rex_op_modrm(b, 0x09, src, dst); /* OR r/m64, r64 */
}

void emit_xor_reg_reg(JitBuf *b, int dst, int src) {
    emit_rex_op_modrm(b, 0x31, src, dst); /* XOR r/m64, r64 */
}

void emit_not_reg(JitBuf *b, int reg) {
    /* REX.W + F7 /2 r/m64 */
    emit_rex(b, 1, 0, 0, reg_high3(reg));
    emit8(b, 0xF7);
    emit_modrm(b, 3, 2, reg);
}

void emit_shl_reg_cl(JitBuf *b, int reg) {
    /* REX.W + D3 /4 r/m64 */
    emit_rex(b, 1, 0, 0, reg_high3(reg));
    emit8(b, 0xD3);
    emit_modrm(b, 3, 4, reg);
}

void emit_shr_reg_cl(JitBuf *b, int reg) {
    /* REX.W + D3 /5 r/m64 (SHR, logical) */
    emit_rex(b, 1, 0, 0, reg_high3(reg));
    emit8(b, 0xD3);
    emit_modrm(b, 3, 5, reg);
}

void emit_sar_reg_cl(JitBuf *b, int reg) {
    /* REX.W + D3 /7 r/m64 (SAR, arithmetic) */
    emit_rex(b, 1, 0, 0, reg_high3(reg));
    emit8(b, 0xD3);
    emit_modrm(b, 3, 7, reg);
}

void emit_xor_reg_self(JitBuf *b, int reg) {
    /* 31 /r -- XOR r32, r32 (zero-extends to 64-bit, no REX needed) */
    emit8(b, 0x31);
    emit_modrm(b, 3, reg, reg);
}

/* ------------------------------------------------------------------ */
/*  Comparison                                                         */
/* ------------------------------------------------------------------ */

void emit_cmp_reg_reg(JitBuf *buf, int a, int breg) {
    /* REX.W + 39 /r -- CMP r/m64, r64 */
    emit_rex_op_modrm(buf, 0x39, breg, a);
}

void emit_test_reg_reg(JitBuf *buf, int a, int breg) {
    /* REX.W + 85 /r -- TEST r/m64, r64 */
    emit_rex_op_modrm(buf, 0x85, breg, a);
}

void emit_setcc(JitBuf *b, int cc, int dst) {
    /* 0F 9x /0 r/m8 -- SETcc r/m8 */
    if (reg_needs_rex(dst))
        emit8(b, 0x41);
    emit8(b, 0x0F);
    emit8(b, (uint8_t)(0x90 + cc));
    emit_modrm(b, 3, 0, dst);
}

void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src) {
    /* REX.W + 0F B6 /r (MOVZX r64, r/m8) */
    emit_rex(buf, 1, reg_high3(dst), 0, reg_high3(src));
    emit8(buf, 0x0F); emit8(buf, 0xB6);
    emit_modrm(buf, 3, dst, src);
}

/* ------------------------------------------------------------------ */
/*  Control flow                                                       */
/* ------------------------------------------------------------------ */

size_t emit_jmp_rel32(JitBuf *b, int32_t rel) {
    emit8(b, 0xE9);
    size_t off = b->size;
    emit32(b, (uint32_t)rel);
    return off;
}

size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel) {
    emit8(b, 0x0F);
    emit8(b, (uint8_t)(0x80 + cc));
    size_t off = b->size;
    emit32(b, (uint32_t)rel);
    return off;
}

void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p) {
    if (p->count < JIT_MAX_PATCHES) {
        emit8(b, 0xE9);
        p->patches[p->count].patch_off = b->size;
        p->patches[p->count].target = target;
        p->count++;
        emit32(b, 0); /* placeholder */
    } else {
        b->failed = 1;
    }
}

void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p) {
    if (p->count < JIT_MAX_PATCHES) {
        emit8(b, 0x0F);
        emit8(b, (uint8_t)(0x80 + cc));
        p->patches[p->count].patch_off = b->size;
        p->patches[p->count].target = target;
        p->count++;
        emit32(b, 0);
    } else {
        b->failed = 1;
    }
}

void jit_apply_patches(JitBuf *b, const JitPatches *p) {
    for (size_t i = 0; i < p->count; i++) {
        size_t off = p->patches[i].patch_off;
        size_t tgt = p->patches[i].target;
        /* rel32 = target - (patch_off + 4) */
        int64_t rel = (int64_t)tgt - (int64_t)(off + 4);
        if (rel < INT32_MIN || rel > INT32_MAX) { b->failed = 1; return; }
        int32_t r = (int32_t)rel;
        memcpy(b->code + off, &r, 4);
    }
}

size_t emit_call_rel32(JitBuf *b, int32_t rel) {
    emit8(b, 0xE8);
    size_t off = b->size;
    emit32(b, (uint32_t)rel);
    return off;
}

void emit_call_reg(JitBuf *b, int reg) {
    /* FF /2 r/m64 -- CALL r/m64 */
    if (reg_needs_rex(reg))
        emit8(b, 0x41);
    emit8(b, 0xFF);
    emit_modrm(b, 3, 2, reg);
}

void emit_ret(JitBuf *b) {
    emit8(b, 0xC3);
}

/* ------------------------------------------------------------------ */
/*  System                                                             */
/* ------------------------------------------------------------------ */

void emit_syscall(JitBuf *b) {
    emit8(b, 0x0F);
    emit8(b, 0x05);
}

void emit_int3(JitBuf *b) {
    emit8(b, 0xCC);
}

void emit_nop(JitBuf *b) {
    emit8(b, 0x90);
}

/* ------------------------------------------------------------------ */
/*  Absolute call to C function                                        */
/* ------------------------------------------------------------------ */

void emit_call_abs(JitBuf *b, void *func, int scratch) {
    emit_mov_reg_imm64(b, scratch, (uint64_t)(uintptr_t)func);
    emit_call_reg(b, scratch);
}

/* ------------------------------------------------------------------ */
/*  Misc memory stores                                                 */
/* ------------------------------------------------------------------ */

void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm) {
    /* REX.W + C6 /0 r/m + imm8 */
    emit_rex(b, 1, 0, 0, reg_high3(base));
    emit8(b, 0xC6);
    emit_modrm_disp32(b, 0, base, disp);
    emit8(b, imm);
}

void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm) {
    /* REX.W + C7 /0 r/m + imm32 (sign-extended) */
    emit_rex(b, 1, 0, 0, reg_high3(base));
    emit8(b, 0xC7);
    emit_modrm_disp32(b, 0, base, disp);
    emit32(b, (uint32_t)imm);
}
