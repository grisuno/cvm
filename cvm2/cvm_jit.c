/**
 * @file cvm_jit.c
 * @brief Multi-tier JIT compiler for CVM v2 -- Tier 1 baseline implementation.
 * @license GPL-2.0-or-later
 *
 * Compiles each CVM function to x86-64 native code.  The operand stack
 * stays in memory (same layout as the interpreter).  Within a compiled
 * function the fetch-decode-dispatch loop is eliminated; the CPU
 * executes native instructions sequentially.
 *
 * Register assignment (see cvm_jit.h):
 *   r14 = CvmState *vm
 *   r12 = uint64_t *slots   (vm->slots)
 *   r13 = size_t sp          (vm->sp, element count)
 *   r15 = CvmFrame *frames   (vm->frames)
 *   rbx = CvmFrame *curframe (current frame)
 *
 * Calling convention for helpers (System V ABI):
 *   rdi = first arg, rsi = second, rdx = third, ...
 *   rax = return value
 *   Callee-saved: rbx, r12-r15, rbp
 */
#include "cvm_jit.h"
#include "cvm_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* vm->jit is void* in cvm.h; cast to the concrete type here */
#define JIT_STATE(vm) ((CvmJitState *)(vm)->jit)

/* ------------------------------------------------------------------ */
/*  JIT lifecycle                                                      */
/* ------------------------------------------------------------------ */

CvmJitState *cvm_jit_create(void) {
    CvmJitState *jit = (CvmJitState *)calloc(1, sizeof(CvmJitState));
    if (!jit) return NULL;
    jit_buf_init(&jit->buf, 1024 * 1024); /* 1 MB initial */
    cvm_jit_offsets_init(&jit->offsets);
    jit->enabled = 1;
    jit->max_tier = JIT_TIER_BASELINE;
    jit->warm_threshold = 1;
    jit->hot_threshold = 1000;
    return jit;
}

void cvm_jit_destroy(CvmJitState *jit) {
    if (!jit) return;
    jit_buf_free(&jit->buf);
    free(jit);
}

/* ------------------------------------------------------------------ */
/*  IP mapping helpers                                                 */
/* ------------------------------------------------------------------ */

static void ip_map_clear(CvmJitState *jit) {
    jit->ip_map_count = 0;
}

static void ip_map_add(CvmJitState *jit, size_t bc_ip, size_t native_off) {
    if (jit->ip_map_count >= JIT_IP_MAP_SIZE) return;
    jit->ip_map[jit->ip_map_count].bytecode_ip = bc_ip;
    jit->ip_map[jit->ip_map_count].native_offset = native_off;
    jit->ip_map_count++;
}

static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip) {
    for (size_t i = 0; i < jit->ip_map_count; i++) {
        if (jit->ip_map[i].bytecode_ip == bc_ip)
            return jit->ip_map[i].native_offset;
    }
    return (size_t)-1;
}

/* ------------------------------------------------------------------ */
/*  Function cache helpers                                             */
/* ------------------------------------------------------------------ */

static JitFuncEntry *func_cache_find(CvmJitState *jit, uint32_t func_idx) {
    for (size_t i = 0; i < jit->num_funcs_compiled; i++)
        if (jit->func_cache[i].func_idx == func_idx)
            return &jit->func_cache[i];
    return NULL;
}

static JitFuncEntry *func_cache_add(CvmJitState *jit, uint32_t func_idx,
                                    size_t native_off, size_t native_sz,
                                    JitTier tier) {
    if (jit->num_funcs_compiled >= JIT_MAX_FUNCS) return NULL;
    JitFuncEntry *e = &jit->func_cache[jit->num_funcs_compiled++];
    e->func_idx = func_idx;
    e->native_offset = native_off;
    e->native_size = native_sz;
    e->tier = tier;
    e->exec_count = 0;
    return e;
}

/* ------------------------------------------------------------------ */
/*  Instruction size lookup (for scanning)                              */
/* ------------------------------------------------------------------ */

static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip) {
    if (ip >= code_size) return 0;
    const CvmOpInfo *info = cvm_op_info(code[ip]);
    if (!info) return 1;
    return info->size;
}

/* ------------------------------------------------------------------ */
/*  Emit helpers: operand stack operations                              */
/* ------------------------------------------------------------------ */

/* Push rax onto the operand stack: slots[sp] = rax; sp++ */
static void emit_stack_push(JitBuf *b) {
    /* mov [r12 + r13*8], rax; inc r13 */
    emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1);
    emit_inc_reg(b, JIT_REG_SP);
}

/* Pop from operand stack into rax: sp--; rax = slots[sp] */
static void emit_stack_pop(JitBuf *b) {
    emit_dec_reg(b, JIT_REG_SP);
    emit_mov_reg_sib(b, JIT_SCRATCH1, JIT_REG_SLOTS, JIT_REG_SP, 3);
}

/* Pop from operand stack into dst */
static void emit_stack_pop_into(JitBuf *b, int dst) {
    emit_dec_reg(b, JIT_REG_SP);
    emit_mov_reg_sib(b, dst, JIT_REG_SLOTS, JIT_REG_SP, 3);
}

/* Push a register onto the operand stack */
static void emit_stack_push_reg(JitBuf *b, int reg) {
    emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, reg);
    emit_inc_reg(b, JIT_REG_SP);
}

/* ------------------------------------------------------------------ */
/*  Emit helpers: C function calls                                      */
/* ------------------------------------------------------------------ */

/* Call a C function with 1 arg (rdi).  Clobbers rax, rcx, rdx, rsi, rdi, r8-r11. */
static void emit_call1(JitBuf *b, void *fn, int arg) {
    if (arg != XDI) emit_mov_reg_reg(b, XDI, arg);
    emit_call_abs(b, fn, X10);
}

/* Call a C function with 2 args (rdi, rsi). */
static void emit_call2(JitBuf *b, void *fn, int a1, int a2) {
    if (a1 != XDI) emit_mov_reg_reg(b, XDI, a1);
    if (a2 != XSI) emit_mov_reg_reg(b, XSI, a2);
    emit_call_abs(b, fn, X10);
}

/* Call a C function with 3 args (rdi, rsi, rdx). */
static void emit_call3(JitBuf *b, void *fn, int a1, int a2, int a3) {
    if (a1 != XDI) emit_mov_reg_reg(b, XDI, a1);
    if (a2 != XSI) emit_mov_reg_reg(b, XSI, a2);
    if (a3 != XDX) emit_mov_reg_reg(b, XDX, a3);
    emit_call_abs(b, fn, X10);
}

/* ------------------------------------------------------------------ */
/*  Emit: function prologue and epilogue                                */
/* ------------------------------------------------------------------ */

static void emit_prologue(JitBuf *b) {
    /* push rbp; mov rbp, rsp */
    emit_push(b, XBP);
    emit_mov_reg_reg(b, XBP, XSP);
    /* push callee-saved registers we use */
    emit_push(b, JIT_REG_FRAME);   /* rbx */
    emit_push(b, JIT_REG_SLOTS);   /* r12 */
    emit_push(b, JIT_REG_SP);      /* r13 */
    emit_push(b, JIT_REG_VM);      /* r14 */
    emit_push(b, JIT_REG_FRAMES);  /* r15 */
    /* Align stack to 16 bytes (6 pushes = 48 bytes, already aligned from
     * the call push of return address, so we're at 56 mod 16 = 8.  One
     * more push would align us.  But we entered with an even number of
     * pushes so let's just sub rsp, 8 if needed.  Actually the 6 pushes
     * + return address = 56 bytes.  56 mod 16 = 8.  We need 8 more to
     * align. */
    emit_sub_reg_imm32(b, XSP, 8);

    /* Load VM state into dedicated registers.
     * rdi = vm (first argument) */
    emit_mov_reg_reg(b, JIT_REG_VM, XDI);

    /* r12 = vm->slots */
    emit_mov_reg_mem(b, JIT_REG_SLOTS, JIT_REG_VM,
                     (int32_t)offsetof(CvmState, slots));

    /* r13 = vm->sp */
    emit_mov32_reg_mem(b, JIT_REG_SP, JIT_REG_VM,
                       (int32_t)offsetof(CvmState, sp));

    /* r15 = vm->frames */
    emit_mov_reg_mem(b, JIT_REG_FRAMES, JIT_REG_VM,
                     (int32_t)offsetof(CvmState, frames));

    /* rbx = vm->frames[frame_count-1].slots  (pointer to local slots array) */
    {
        /* rax = vm->frame_count */
        emit_mov_reg_mem(b, XAX, JIT_REG_VM,
                         (int32_t)offsetof(CvmState, frame_count));
        /* test rax, rax; jz .no_frame */
        size_t patch = emit_jcc_rel32(b, CC_E, 0); /* placeholder */
        /* dec rax */
        emit_dec_reg(b, XAX);
        /* rax = &frames[rax] -- each frame is 32 bytes.
         * SIB only supports scales ×1/×2/×4/×8, so pre-multiply:
         * rax *= 4 (shl 2), then use SIB ×8 (scale=3) for ×32 total. */
        emit_mov_reg_imm32(b, XCX, 2);
        emit_shl_reg_cl(b, XAX);
        emit_lea_sib(b, JIT_SCRATCH1, JIT_REG_FRAMES, XAX, 3 /* *8 */, 0);
        /* rax = frames[idx].slots (dereference the slots pointer) */
        emit_mov_reg_mem(b, XAX, JIT_SCRATCH1,
                         (int32_t)offsetof(CvmFrame, slots));
        emit_mov_reg_reg(b, JIT_REG_FRAME, XAX);
        /* .no_frame: */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch + 4));
            memcpy(b->code + patch, &rel, 4);
        }
    }
}

static void emit_epilogue(JitBuf *b) {
    /* Add stack alignment back */
    emit_add_reg_imm32(b, XSP, 8);
    /* Restore callee-saved registers (reverse order of prologue) */
    emit_pop(b, JIT_REG_FRAMES);  /* r15 */
    emit_pop(b, JIT_REG_VM);      /* r14 */
    emit_pop(b, JIT_REG_SP);      /* r13 */
    emit_pop(b, JIT_REG_SLOTS);   /* r12 */
    emit_pop(b, JIT_REG_FRAME);   /* rbx */
    emit_pop(b, XBP);             /* rbp */
    /* xor eax, eax (return 0) */
    emit_xor_reg_self(b, XAX);
    emit_ret(b);
}

/* ------------------------------------------------------------------ */
/*  Emit: save/restore VM state (for C calls)                          */
/* ------------------------------------------------------------------ */

/* Save vm->sp from r13 back to vm (before calling a C helper). */
static void emit_save_sp(JitBuf *b) {
    emit_mov32_mem_reg(b, JIT_REG_VM,
                       (int32_t)offsetof(CvmState, sp), JIT_REG_SP);
}

/* Restore vm->sp into r13 (after calling a C helper). */
static void emit_restore_sp(JitBuf *b) {
    emit_mov32_reg_mem(b, JIT_REG_SP, JIT_REG_VM,
                       (int32_t)offsetof(CvmState, sp));
}

/* Bail out of the current native function when the machine stopped
 * (exit/abort/error/HALT cleared vm->running inside a helper or native).
 * The interpreter checks running before every instruction; emitted code
 * must recheck at every point where running can change, otherwise it
 * keeps executing dead code after the stop: error() -> exit() returns
 * into the middle of the faulting function and parsing continues with
 * garbage state, cascading into wild stores. */
static void emit_bail_if_stopped(JitBuf *b) {
    emit_mov32_reg_mem(b, XAX, JIT_REG_VM,
                       (int32_t)offsetof(CvmState, running));
    emit_test_reg_reg(b, XAX, XAX);
    size_t patch_cont = emit_jcc_rel32(b, CC_NE, 0); /* jnz .cont */
    emit_epilogue(b);
    {
        size_t target = b->size;
        int32_t rel = (int32_t)(target - (patch_cont + 4));
        memcpy(b->code + patch_cont, &rel, 4);
    }
    /* .cont: */
}

/* ------------------------------------------------------------------ */
/*  Opcode code generation                                             */
/* ------------------------------------------------------------------ */

typedef struct {
    CvmState    *vm;
    JitBuf      *b;
    CvmJitState *jit;
    /* Heap-allocated: 8192 entries x 16 bytes = 128 KB, far too big for
     * a C stack local (it overflows small kernel stacks and lands on
     * low-memory page tables/MMIO). Allocated per compiled function and
     * freed before returning. */
    JitPatches   *patches;
    uint32_t     func_idx;
    size_t       func_bc_start;  /* bytecode offset of this function */
    size_t       func_bc_end;    /* bytecode offset of end */
} JitCtx;

static int emit_opcode(JitCtx *ctx, size_t bc_ip) {
    CvmState *vm = ctx->vm;
    JitBuf *b = ctx->b;
    uint8_t *code = vm->code;
    size_t cs = vm->code_size;
    size_t ip = bc_ip;

    if (ip >= cs) return -1;
    uint8_t op = code[ip++];

    /* Record this bytecode IP -> native offset mapping */
    ip_map_add(ctx->jit, bc_ip, b->size);

    switch (op) {

    /* ---- Constants / Stack Push ---- */

    case OP_NOP:
        emit_nop(b);
        break;

    case OP_PUSH_IMM64: {
        if (ip + 8 > cs) return -1;
        uint64_t v = 0;
        for (int i = 0; i < 8; i++)
            v |= (uint64_t)code[ip + i] << (i * 8);
        ip += 8;
        emit_mov_reg_imm64(b, JIT_SCRATCH1, v);
        emit_stack_push(b);
        break;
    }

    case OP_PUSH_IMM32: {
        if (ip + 4 > cs) return -1;
        int32_t v = (int32_t)((uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                   | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24));
        ip += 4;
        emit_mov_reg_imm32(b, JIT_SCRATCH1, v);
        emit_stack_push(b);
        break;
    }

    case OP_PUSH_IMM8: {
        if (ip >= cs) return -1;
        int8_t v = (int8_t)code[ip++];
        emit_mov_reg_imm32(b, JIT_SCRATCH1, (int32_t)v);
        emit_stack_push(b);
        break;
    }

    case OP_PUSH_ZERO:
        emit_xor_reg_self(b, JIT_SCRATCH1);
        emit_stack_push(b);
        break;

    case OP_PUSH_ONE:
        emit_mov_reg_imm32(b, JIT_SCRATCH1, 1);
        emit_stack_push(b);
        break;

    /* ---- Variables ---- */

    case OP_PUSH_LOCAL: {
        if (ip + 4 > cs) return -1;
        uint32_t idx = (uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                     | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24);
        ip += 4;
        /* rax = frame->slots[idx] */
        emit_mov_reg_mem(b, JIT_SCRATCH1, JIT_REG_FRAME, (int32_t)(idx * 8));
        emit_stack_push(b);
        break;
    }

    case OP_STORE_LOCAL: {
        if (ip + 4 > cs) return -1;
        uint32_t idx = (uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                     | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24);
        ip += 4;
        emit_stack_pop(b);
        /* frame->slots[idx] = rax */
        emit_mov_mem_reg(b, JIT_REG_FRAME, (int32_t)(idx * 8), JIT_SCRATCH1);
        break;
    }

    case OP_PUSH_GLOBAL: {
        if (ip + 4 > cs) return -1;
        uint32_t idx = (uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                     | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24);
        ip += 4;
        /* rax = vm->globals */
        emit_mov_reg_mem(b, JIT_SCRATCH2, JIT_REG_VM,
                         (int32_t)offsetof(CvmState, globals));
        /* rax = globals[idx*8] */
        emit_mov_reg_mem(b, JIT_SCRATCH1, JIT_SCRATCH2, (int32_t)(idx * 8));
        emit_stack_push(b);
        break;
    }

    case OP_STORE_GLOBAL: {
        if (ip + 4 > cs) return -1;
        uint32_t idx = (uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                     | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24);
        ip += 4;
        emit_stack_pop(b);
        /* rcx = vm->globals */
        emit_mov_reg_mem(b, JIT_SCRATCH2, JIT_REG_VM,
                         (int32_t)offsetof(CvmState, globals));
        /* globals[idx*8] = rax */
        emit_mov_mem_reg(b, JIT_SCRATCH2, (int32_t)(idx * 8), JIT_SCRATCH1);
        break;
    }

    /* ---- Arithmetic ---- */

    case OP_ADD:
        emit_stack_pop_into(b, JIT_SCRATCH2); /* b */
        emit_stack_pop(b);                      /* a -> rax */
        emit_add_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);
        emit_stack_push(b);
        break;

    case OP_SUB:
        emit_stack_pop_into(b, JIT_SCRATCH2); /* b */
        emit_stack_pop(b);                      /* a -> rax */
        emit_sub_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);
        emit_stack_push(b);
        break;

    case OP_MUL:
        emit_stack_pop_into(b, JIT_SCRATCH2); /* b */
        emit_stack_pop(b);                      /* a -> rax */
        emit_imul_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);
        emit_stack_push(b);
        break;

    case OP_DIV: {
        /* signed divide: rax = a / b */
        emit_save_sp(b);
        emit_stack_pop_into(b, XCX);   /* b -> rcx */
        emit_stack_pop(b);              /* a -> rax */
        /* check div by zero */
        emit_test_reg_reg(b, XCX, XCX);
        size_t patch_ok = emit_jcc_rel32(b, CC_NE, 0);  /* jnz .ok */
        /* div by zero: call error, then return */
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_DIV_ZERO);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_DIV_ZERO);
        emit_epilogue(b);
        /* .ok: */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_ok + 4));
            memcpy(b->code + patch_ok, &rel, 4);
        }
        emit_cqo(b);
        emit_idiv_reg(b, XCX);
        emit_stack_push(b);
        break;
    }

    case OP_MOD: {
        /* signed modulo: rax = a % b */
        emit_save_sp(b);
        emit_stack_pop_into(b, XCX);   /* b -> rcx */
        emit_stack_pop(b);              /* a -> rax */
        /* check div by zero */
        emit_test_reg_reg(b, XCX, XCX);
        /* jnz .ok */
        size_t patch_bad = emit_jcc_rel32(b, CC_NE, 0);
        /* div by zero: call error, then return */
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_DIV_ZERO);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_DIV_ZERO);
        emit_epilogue(b);
        /* .ok: */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_bad + 4));
            memcpy(b->code + patch_bad, &rel, 4);
        }
        emit_cqo(b);
        emit_idiv_reg(b, XCX);
        /* remainder is in rdx */
        emit_mov_reg_reg(b, JIT_SCRATCH1, XDX);
        emit_stack_push(b);
        break;
    }

    case OP_NEG:
        emit_stack_pop(b);
        emit_neg_reg(b, JIT_SCRATCH1);
        emit_stack_push(b);
        break;

    /* ---- Bitwise ---- */

    case OP_AND:
        emit_stack_pop_into(b, JIT_SCRATCH2);
        emit_stack_pop(b);
        emit_and_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);
        emit_stack_push(b);
        break;

    case OP_OR:
        emit_stack_pop_into(b, JIT_SCRATCH2);
        emit_stack_pop(b);
        emit_or_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);
        emit_stack_push(b);
        break;

    case OP_XOR:
        emit_stack_pop_into(b, JIT_SCRATCH2);
        emit_stack_pop(b);
        emit_xor_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);
        emit_stack_push(b);
        break;

    case OP_NOT:
        emit_stack_pop(b);
        emit_not_reg(b, JIT_SCRATCH1);
        emit_stack_push(b);
        break;

    case OP_SHL:
        emit_stack_pop_into(b, XCX);   /* shift count -> cl */
        emit_stack_pop(b);              /* value -> rax */
        emit_and_reg_imm32(b, XCX, CVM_SHIFT_MASK);
        emit_shl_reg_cl(b, JIT_SCRATCH1);
        emit_stack_push(b);
        break;

    case OP_SHR:
        emit_stack_pop_into(b, XCX);
        emit_stack_pop(b);
        emit_and_reg_imm32(b, XCX, CVM_SHIFT_MASK);
        emit_sar_reg_cl(b, JIT_SCRATCH1);
        emit_stack_push(b);
        break;

    case OP_USHR:
        emit_stack_pop_into(b, XCX);
        emit_stack_pop(b);
        emit_and_reg_imm32(b, XCX, CVM_SHIFT_MASK);
        emit_shr_reg_cl(b, JIT_SCRATCH1);
        emit_stack_push(b);
        break;

    /* ---- Comparison ---- */

    #define EMIT_CMP(cc_signed) do {                         \
        emit_stack_pop_into(b, JIT_SCRATCH2); /* b */        \
        emit_stack_pop(b);                      /* a */      \
        emit_cmp_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);    \
        emit_setcc(b, cc_signed, JIT_SCRATCH1);             \
        /* zero-extend */                                    \
        emit_movzx_reg_mem8(b, JIT_SCRATCH1, JIT_SCRATCH1, 0); \
        emit_stack_push(b);                                  \
    } while (0)

    /* Actually, setcc writes to a byte register. We need to zero-extend.
     * MOVZX r64, r/m8: REX.W 0F B6 /r.  But setcc only writes to the
     * low byte.  We can use movzx with the same register:
     *   setcc al
     *   movzx rax, al
     * But movzx needs a memory or byte-reg operand.  setcc al sets al.
     * We can encode: REX.W 0F B6 C0 (movzx rax, al) which is 4 bytes.
     * Actually, we can skip the movzx if we just use the low byte and
     * know the upper bytes are garbage.  But the interpreter pushes 0 or 1
     * as a full 64-bit value.  Let's keep it correct. */

    #define EMIT_CMP_SIGNED(cc) do {                             \
        emit_stack_pop_into(b, JIT_SCRATCH2);                    \
        emit_stack_pop(b);                                       \
        emit_cmp_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);        \
        emit_setcc(b, cc, JIT_SCRATCH1);                        \
        /* movzx rax, al  (REX.W 0F B6 C0) */                   \
        emit_rex(b, 1, 0, 0, 0);                                \
        emit8(b, 0x0F); emit8(b, 0xB6);                         \
        emit_modrm(b, 3, JIT_SCRATCH1, JIT_SCRATCH1);           \
        emit_stack_push(b);                                      \
    } while (0)

    #define EMIT_CMP_UNSIGNED(cc) EMIT_CMP_SIGNED(cc)

    case OP_CMP_EQ:  EMIT_CMP_SIGNED(CC_E);  break;
    case OP_CMP_NE:  EMIT_CMP_SIGNED(CC_NE); break;
    case OP_CMP_LT:  EMIT_CMP_SIGNED(CC_L);  break;
    case OP_CMP_LE:  EMIT_CMP_SIGNED(CC_LE); break;
    case OP_CMP_GT:  EMIT_CMP_SIGNED(CC_G);  break;
    case OP_CMP_GE:  EMIT_CMP_SIGNED(CC_GE); break;
    case OP_CMP_ULT: EMIT_CMP_UNSIGNED(CC_B);  break;
    case OP_CMP_ULE: EMIT_CMP_UNSIGNED(CC_BE); break;
    case OP_CMP_UGT: EMIT_CMP_UNSIGNED(CC_A);  break;
    case OP_CMP_UGE: EMIT_CMP_UNSIGNED(CC_AE); break;

    case OP_LNOT:
        emit_stack_pop(b);
        emit_test_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH1);
        /* sete al */
        emit_setcc(b, CC_E, JIT_SCRATCH1);
        emit_rex(b, 1, 0, 0, 0);
        emit8(b, 0x0F); emit8(b, 0xB6);
        emit_modrm(b, 3, JIT_SCRATCH1, JIT_SCRATCH1);
        emit_stack_push(b);
        break;

    /* ---- Control Flow ---- */

    case OP_JMP: {
        if (ip + 4 > cs) return -1;
        int32_t rel = (int32_t)((uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                      | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24));
        ip += 4;
        /* Target bytecode IP = ip + rel */
        size_t target_bc = ip + (int64_t)rel;
        /* Emit jmp with placeholder, patch later */
        emit_jmp_buf(b, target_bc, ctx->patches);
        break;
    }

    case OP_JZ: {
        if (ip + 4 > cs) return -1;
        int32_t rel = (int32_t)((uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                      | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24));
        ip += 4;
        size_t target_bc = ip + (int64_t)rel;
        emit_stack_pop(b);
        emit_test_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH1);
        emit_jcc_buf(b, CC_E, target_bc, ctx->patches);
        break;
    }

    case OP_JNZ: {
        if (ip + 4 > cs) return -1;
        int32_t rel = (int32_t)((uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                      | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24));
        ip += 4;
        size_t target_bc = ip + (int64_t)rel;
        emit_stack_pop(b);
        emit_test_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH1);
        emit_jcc_buf(b, CC_NE, target_bc, ctx->patches);
        break;
    }

    /* ---- Function calls ---- */

    case OP_CALL: {
        if (ip + 5 > cs) return -1;
        uint32_t fi = (uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                    | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24);
        uint8_t na = code[ip + 4];
        ip += 5;
        /* Save sp, set vm->ip = return address, call helper, call exec_one, restore sp */
        emit_save_sp(b);
        /* Set vm->ip to the return bytecode IP so push_frame saves the right return_ip */
        emit_mov_reg_imm32(b, XAX, (int32_t)ip);
        emit_mov32_mem_reg(b, JIT_REG_VM, (int32_t)offsetof(CvmState, ip), XAX);
        /* rdi = vm, esi = fi, edx = na */
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, (int32_t)fi);
        emit_mov_reg_imm32(b, XDX, (int32_t)na);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_call, X10);
        /* check return: rax == 0 means ok */
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch = emit_jcc_rel32(b, CC_NE, 0);
        /* success: execute callee */
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_exec_one, X10);
        emit_restore_sp(b);
        /* The callee may have stopped the machine (exit/HALT/error):
         * unwind instead of executing the ops after the call. */
        emit_bail_if_stopped(b);
        /* .done: (patch the jnz here) */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch + 4));
            memcpy(b->code + patch, &rel, 4);
        }
        break;
    }

    case OP_CALL_INDIRECT: {
        /* Target function index rides the operand stack (pushed by the
         * caller); argument registers travel via the GSLOT_ARGS area exactly
         * like OP_CALL with zero stack args. The callee reads esi only, so
         * the full 64-bit pop is safe: high bits are ignored. */
        emit_stack_pop(b);  /* rax = target index */
        emit_mov_reg_reg(b, JIT_SCRATCH2, JIT_SCRATCH1);
        emit_save_sp(b);
        emit_mov_reg_imm32(b, XAX, (int32_t)ip);
        emit_mov32_mem_reg(b, JIT_REG_VM, (int32_t)offsetof(CvmState, ip), XAX);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH2);
        emit_mov_reg_imm32(b, XDX, 0);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_call, X10);
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch = emit_jcc_rel32(b, CC_NE, 0);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_exec_one, X10);
        emit_restore_sp(b);
        emit_bail_if_stopped(b);
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch + 4));
            memcpy(b->code + patch, &rel, 4);
        }
        break;
    }

    case OP_RET: {
        /* Pop return value from stack, but only if the stack is non-empty.
         * A void function can return with sp==0 (the interpreter guards with
         * `if (vm->sp > 0)`); an unconditional pop would underflow r13 to -1
         * and read/write slots[-1] out of bounds.  Mirror the interpreter. */
        emit_xor_reg_self(b, JIT_SCRATCH1);  /* rax = 0 (default retval) */
        emit_test_reg_reg(b, JIT_REG_SP, JIT_REG_SP);
        size_t patch_empty = emit_jcc_rel32(b, CC_E, 0);  /* jz .empty */
        emit_stack_pop(b);  /* rax = slots[--r13] */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_empty + 4));
            memcpy(b->code + patch_empty, &rel, 4);
        }
        /* Save sp and call ret helper */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH1);  /* retval */
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_ret, X10);
        /* Restore sp (cvm_jit_ret may have pushed return value) */
        emit_restore_sp(b);
        /* Always return from native function to the caller or dispatch loop.
         * The caller's CALL handler will continue after cvm_jit_exec_one. */
        emit_epilogue(b);
        break;
    }

    case OP_CALL_NATIVE: {
        if (ip + 5 > cs) return -1;
        uint32_t ni = (uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                    | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24);
        uint8_t na = code[ip + 4];
        ip += 5;
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, (int32_t)ni);
        emit_mov_reg_imm32(b, XDX, (int32_t)na);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_call_native, X10);
        emit_restore_sp(b);
        /* A native may stop the machine (exit/abort): unwind, mirroring
         * the interpreter's per-instruction running check. */
        emit_bail_if_stopped(b);
        break;
    }

    /* ---- Memory ---- */

    case OP_LOAD8: {
        emit_stack_pop(b);  /* address -> rax */
        /* check validity */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH1);
        emit_mov_reg_imm32(b, XDX, 1);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_memcheck, X10);
        emit_restore_sp(b);
        /* if rax == 0, error */
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch_ok = emit_jcc_rel32(b, CC_NE, 0);  /* jnz .good */
        /* Error path (fall through on failure) */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_ADDR);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_BAD_ADDR);
        emit_epilogue(b);
        /* Good path */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_ok + 4));
            memcpy(b->code + patch_ok, &rel, 4);
        }
        emit_mov_reg_sib(b, JIT_SCRATCH1, JIT_REG_SLOTS, JIT_REG_SP, 3);
        /* movsx rax, byte [rax]: REX.W 0F BE 00 */
        emit_rex(b, 1, 0, 0, 0);
        emit8(b, 0x0F); emit8(b, 0xBE);
        emit_modrm(b, 0, JIT_SCRATCH1, JIT_SCRATCH1);  /* [rax] */
        emit_stack_push(b);
        break;
    }

    case OP_LOAD16: {
        emit_stack_pop(b);
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH1);
        emit_mov_reg_imm32(b, XDX, 2);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_memcheck, X10);
        emit_restore_sp(b);
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch_ok = emit_jcc_rel32(b, CC_NE, 0);  /* jnz .good */
        /* Error path (fall through on failure) */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_ADDR);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_BAD_ADDR);
        emit_epilogue(b);
        /* Good path */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_ok + 4));
            memcpy(b->code + patch_ok, &rel, 4);
        }
        emit_mov_reg_sib(b, JIT_SCRATCH1, JIT_REG_SLOTS, JIT_REG_SP, 3);
        /* movsx rax, word [rax]: REX.W 0F BF 00 */
        emit_rex(b, 1, 0, 0, 0);
        emit8(b, 0x0F); emit8(b, 0xBF);
        emit_modrm(b, 0, JIT_SCRATCH1, JIT_SCRATCH1);
        emit_stack_push(b);
        break;
    }

    case OP_LOAD32: {
        emit_stack_pop(b);
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH1);
        emit_mov_reg_imm32(b, XDX, 4);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_memcheck, X10);
        emit_restore_sp(b);
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch_ok = emit_jcc_rel32(b, CC_NE, 0);  /* jnz .good */
        /* Error path (fall through on failure) */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_ADDR);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_BAD_ADDR);
        emit_epilogue(b);
        /* Good path */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_ok + 4));
            memcpy(b->code + patch_ok, &rel, 4);
        }
        emit_mov_reg_sib(b, JIT_SCRATCH1, JIT_REG_SLOTS, JIT_REG_SP, 3);
        /* movsxd rax, dword [rax]: REX.W 63 00 */
        emit_rex(b, 1, 0, 0, 0);
        emit8(b, 0x63);
        emit_modrm(b, 0, JIT_SCRATCH1, JIT_SCRATCH1);
        emit_stack_push(b);
        break;
    }

    case OP_LOAD64: {
        emit_stack_pop(b);
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH1);
        emit_mov_reg_imm32(b, XDX, 8);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_memcheck, X10);
        emit_restore_sp(b);
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch_ok = emit_jcc_rel32(b, CC_NE, 0);  /* jnz .good */
        /* Error path (fall through on failure) */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_ADDR);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_BAD_ADDR);
        emit_epilogue(b);
        /* Good path: reload address, dereference, push */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_ok + 4));
            memcpy(b->code + patch_ok, &rel, 4);
        }
        emit_mov_reg_sib(b, JIT_SCRATCH1, JIT_REG_SLOTS, JIT_REG_SP, 3);
        /* mov rax, [rax]: REX.W 8B 00 */
        emit_rex(b, 1, 0, 0, 0);
        emit8(b, 0x8B);
        emit_modrm(b, 0, JIT_SCRATCH1, JIT_SCRATCH1);
        emit_stack_push(b);
        break;
    }

    case OP_STORE8: {
        /* Pop value, pop address, store byte */
        emit_stack_pop_into(b, XCX);   /* value -> rcx, sp = N-1 */
        emit_stack_pop(b);              /* address -> rax, sp = N-2 */
        /* Save both to operand stack slots below sp (safe across C call) */
        emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, XCX);
        emit_inc_reg(b, JIT_REG_SP);
        emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1);
        /* memcheck(vm, address, 1) */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH1);
        emit_mov_reg_imm32(b, XDX, 1);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_memcheck, X10);
        emit_restore_sp(b);
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch_ok = emit_jcc_rel32(b, CC_NE, 0);  /* jnz .good */
        /* Error path (fall through on failure) */
        emit_dec_reg(b, JIT_REG_SP);
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_ADDR);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_BAD_ADDR);
        emit_epilogue(b);
        /* Good path: reload address and value, store byte */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_ok + 4));
            memcpy(b->code + patch_ok, &rel, 4);
        }
        emit_mov_reg_sib(b, X11, JIT_REG_SLOTS, JIT_REG_SP, 3); /* r11 = address */
        emit_dec_reg(b, JIT_REG_SP);
        emit_mov_reg_sib(b, XAX, JIT_REG_SLOTS, JIT_REG_SP, 3); /* rax = value */
        /* mov byte [r11], al: REX.B 88 mod=0 */
        emit8(b, 0x41);  /* REX.B=1 (r11) */
        emit8(b, 0x88);  /* MOV r/m8, r8 */
        emit_modrm(b, 0, XAX, X11);
        break;
    }

    case OP_STORE16: {
        emit_stack_pop_into(b, XCX);   /* value -> rcx, sp = N-1 */
        emit_stack_pop(b);              /* address -> rax, sp = N-2 */
        /* Save both to operand stack slots below sp (safe across C call) */
        emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, XCX);
        emit_inc_reg(b, JIT_REG_SP);
        emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1);
        /* memcheck(vm, address, 2) */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH1);
        emit_mov_reg_imm32(b, XDX, 2);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_memcheck, X10);
        emit_restore_sp(b);
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch_ok = emit_jcc_rel32(b, CC_NE, 0);  /* jnz .good */
        /* Error path (fall through on failure) */
        emit_dec_reg(b, JIT_REG_SP);
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_ADDR);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_BAD_ADDR);
        emit_epilogue(b);
        /* Good path: reload address and value, store word */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_ok + 4));
            memcpy(b->code + patch_ok, &rel, 4);
        }
        emit_mov_reg_sib(b, X11, JIT_REG_SLOTS, JIT_REG_SP, 3); /* r11 = address */
        emit_dec_reg(b, JIT_REG_SP);
        emit_mov_reg_sib(b, XAX, JIT_REG_SLOTS, JIT_REG_SP, 3); /* rax = value */
        /* mov word [r11], ax: 66 REX.B 89 mod=0 */
        emit8(b, 0x66);  /* operand size prefix */
        emit8(b, 0x41);  /* REX.B=1 (r11) */
        emit8(b, 0x89);  /* MOV r/m16, r16 */
        emit_modrm(b, 0, XAX, X11);
        break;
    }

    case OP_STORE32: {
        emit_stack_pop_into(b, XCX);   /* value -> rcx, sp = N-1 */
        emit_stack_pop(b);              /* address -> rax, sp = N-2 */
        /* Save both to operand stack slots below sp (safe across C call) */
        emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, XCX);
        emit_inc_reg(b, JIT_REG_SP);
        emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1);
        /* memcheck(vm, address, 4) */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH1);
        emit_mov_reg_imm32(b, XDX, 4);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_memcheck, X10);
        emit_restore_sp(b);
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch_ok = emit_jcc_rel32(b, CC_NE, 0);  /* jnz .good */
        /* Error path (fall through on failure) */
        emit_dec_reg(b, JIT_REG_SP);
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_ADDR);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_BAD_ADDR);
        emit_epilogue(b);
        /* Good path: reload address and value, store dword */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_ok + 4));
            memcpy(b->code + patch_ok, &rel, 4);
        }
        emit_mov_reg_sib(b, X11, JIT_REG_SLOTS, JIT_REG_SP, 3); /* r11 = address */
        emit_dec_reg(b, JIT_REG_SP);
        emit_mov_reg_sib(b, XAX, JIT_REG_SLOTS, JIT_REG_SP, 3); /* rax = value */
        /* mov dword [r11], eax: REX.B 89 mod=0 (no REX.W for 32-bit) */
        emit8(b, 0x41);  /* REX.B=1 (r11) */
        emit8(b, 0x89);  /* MOV r/m32, r32 */
        emit_modrm(b, 0, XAX, X11);
        break;
    }

    case OP_STORE64: {
        emit_stack_pop_into(b, XCX);   /* value -> rcx, sp = N-1 */
        emit_stack_pop(b);              /* address -> rax, sp = N-2 */
        /* Save both to operand stack slots below sp (valid memory, below the
         * stack pointer but within the allocated buffer).  The C call to
         * memcheck clobbers all caller-saved registers, so we must not hold
         * the value or address in registers across the call. */
        emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, XCX); /* slots[sp] = value */
        emit_inc_reg(b, JIT_REG_SP);                             /* sp = N-1 */
        emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1); /* slots[sp] = address */
        /* memcheck(vm, address, 8) */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH1);  /* rsi = rax = address */
        emit_mov_reg_imm32(b, XDX, 8);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_memcheck, X10);
        emit_restore_sp(b);
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch_ok = emit_jcc_rel32(b, CC_NE, 0);  /* jnz .good */
        /* Error path (fall through when memcheck fails): sp = N-2, then error */
        emit_dec_reg(b, JIT_REG_SP);                              /* sp = N-2 */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_ADDR);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_BAD_ADDR);
        emit_epilogue(b);
        /* Good path: reload address and value, store */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_ok + 4));
            memcpy(b->code + patch_ok, &rel, 4);
        }
        emit_mov_reg_sib(b, X11, JIT_REG_SLOTS, JIT_REG_SP, 3); /* r11 = address */
        emit_dec_reg(b, JIT_REG_SP);                              /* sp = N-2 */
        emit_mov_reg_sib(b, XAX, JIT_REG_SLOTS, JIT_REG_SP, 3); /* rax = value */
        /* mov [r11], rax: REX.W REX.B 89 mod=0 */
        emit8(b, 0x49);  /* REX.W=1, REX.B=1 (r11) */
        emit8(b, 0x89);  /* MOV r/m64, r64 */
        emit_modrm(b, 0, XAX, X11);
        break;
    }

    /* ---- LEA ---- */

    case OP_LEA_LOCAL: {
        if (ip + 4 > cs) return -1;
        uint32_t idx = (uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                     | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24);
        ip += 4;
        /* rax = &frame->slots[idx] = rbx + idx*8 */
        emit_lea_sib(b, JIT_SCRATCH1, JIT_REG_FRAME, -1, 0, (int32_t)(idx * 8));
        emit_stack_push(b);
        break;
    }

    case OP_LEA_GLOBAL: {
        if (ip + 4 > cs) return -1;
        uint32_t idx = (uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                     | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24);
        ip += 4;
        /* rax = &globals[idx*8] = vm->globals + idx*8 */
        emit_mov_reg_mem(b, JIT_SCRATCH1, JIT_REG_VM,
                         (int32_t)offsetof(CvmState, globals));
        emit_add_reg_imm32(b, JIT_SCRATCH1, (int32_t)(idx * 8));
        emit_stack_push(b);
        break;
    }

    case OP_LEA_DATA: {
        if (ip + 4 > cs) return -1;
        uint32_t off = (uint32_t)code[ip] | ((uint32_t)code[ip+1] << 8)
                     | ((uint32_t)code[ip+2] << 16) | ((uint32_t)code[ip+3] << 24);
        ip += 4;
        /* rax = vm->globals + off */
        emit_mov_reg_mem(b, JIT_SCRATCH1, JIT_REG_VM,
                         (int32_t)offsetof(CvmState, globals));
        emit_add_reg_imm32(b, JIT_SCRATCH1, (int32_t)off);
        emit_stack_push(b);
        break;
    }

    /* ---- Heap ---- */

    case OP_ALLOC: {
        emit_stack_pop(b);  /* size -> rax */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_reg(b, XSI, JIT_SCRATCH1);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_alloc, X10);
        emit_restore_sp(b);
        /* rax = pointer (0 on failure) */
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch_ok = emit_jcc_rel32(b, CC_NE, 0);
        /* failure: set error */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_HEAP_OVER);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_HEAP_OVER);
        emit_epilogue(b);
        /* .ok: */
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_ok + 4));
            memcpy(b->code + patch_ok, &rel, 4);
        }
        emit_stack_push(b);
        break;
    }

    case OP_FREE:
        emit_stack_pop(b);  /* pop and discard */
        break;

    /* ---- System ---- */

    case OP_SYSCALL: {
        if (ip + 2 > cs) return -1;
        uint8_t sn = code[ip++];
        uint8_t na = code[ip++];
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, (int32_t)sn);
        emit_mov_reg_imm32(b, XDX, (int32_t)na);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_syscall, X10);
        emit_restore_sp(b);
        /* CVM_SYS_EXIT stops the machine: unwind like CALL_NATIVE. */
        emit_bail_if_stopped(b);
        break;
    }

    case OP_HALT:
        /* vm->sp = sp, then if vm->sp > 0 set vm->exit_code = slots[sp-1] */
        emit_save_sp(b);
        /* rax = vm->sp (32-bit; sp fits) */
        emit_mov32_reg_mem(b, XAX, JIT_REG_VM, (int32_t)offsetof(CvmState, sp));
        emit_test_reg_reg(b, XAX, XAX);
        size_t patch_halt = emit_jcc_rel32(b, CC_E, 0);
        /* rcx = slots[sp-1] */
        emit_dec_reg(b, XAX);
        emit_mov_reg_sib(b, XCX, JIT_REG_SLOTS, XAX, 3);
        emit_mov_mem_reg(b, JIT_REG_VM,
                         (int32_t)offsetof(CvmState, exit_code), XCX);
        {
            size_t target = b->size;
            int32_t rel = (int32_t)(target - (patch_halt + 4));
            memcpy(b->code + patch_halt, &rel, 4);
        }
        /* mov dword [r14 + running], 0 */
        emit_mov_mem_imm32(b, JIT_REG_VM,
                           (int32_t)offsetof(CvmState, running), 0);
        emit_epilogue(b);
        break;

    default:
        /* Unknown opcode: fall back to error */
        emit_save_sp(b);
        emit_mov_reg_reg(b, XDI, JIT_REG_VM);
        emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_OPCODE);
        emit_call_abs(b, (void *)(uintptr_t)cvm_jit_error, X10);
        emit_mov_reg_imm32(b, XAX, CVM_ERR_BAD_OPCODE);
        emit_epilogue(b);
        break;
    }

    return (int)(ip - bc_ip);
}

/* ------------------------------------------------------------------ */
/*  Function compilation                                               */
/* ------------------------------------------------------------------ */

static void jit_apply_patches_local(JitBuf *b, const JitPatches *p) {
    for (size_t i = 0; i < p->count; i++) {
        size_t off = p->patches[i].patch_off;
        size_t bc_target = p->patches[i].target;
        /* Look up native offset for this bytecode IP */
        size_t native_off = ip_map_lookup(/* jit not available here */NULL, bc_target);
        if (native_off == (size_t)-1) {
            /* Target not found -- shouldn't happen if we compile the
             * whole function.  Leave as 0 (will jump to offset 0). */
            native_off = 0;
        }
        int64_t rel = (int64_t)native_off - (int64_t)(off + 4);
        if (rel < INT32_MIN || rel > INT32_MAX) { b->failed = 1; return; }
        int32_t r = (int32_t)rel;
        memcpy(b->code + off, &r, 4);
    }
}

void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx) {
    CvmJitState *jit = vm->jit;
    if (!jit || !jit->enabled) return NULL;
    if (func_idx >= vm->num_funcs) return NULL;

    /* Already compiled? */
    JitFuncEntry *existing = func_cache_find(jit, func_idx);
    if (existing) {
        return jit->buf.code + existing->native_offset;
    }

    CvmFuncEntry *fe = &vm->funcs[func_idx];
    size_t bc_start = fe->code_off;
    size_t bc_end = (func_idx + 1 < vm->num_funcs)
                    ? vm->funcs[func_idx + 1].code_off
                    : vm->code_size;

    /* IP map is per-function: jumps (JMP/JZ/JNZ) are local to a function
     * (CALL uses dynamic dispatch, not a direct jump), so reset it here.
     * Without this, the map fills up across the whole module and a late
     * function's instruction offsets are never recorded, leaving every
     * jump unresolved. */
    jit->ip_map_count = 0;

    JitCtx ctx;
    ctx.vm = vm;
    ctx.b = &jit->buf;
    ctx.jit = jit;
    ctx.patches = (JitPatches *)malloc(sizeof(JitPatches));
    if (!ctx.patches) {
        jit->buf.failed = 1;
        return NULL;
    }
    ctx.patches->count = 0;
    ctx.func_idx = func_idx;
    ctx.func_bc_start = bc_start;
    ctx.func_bc_end = bc_end;

    size_t native_start = jit->buf.size;

    /* Emit prologue */
    emit_prologue(&jit->buf);

    /* Compile each instruction */
    size_t ip = bc_start;
    while (ip < bc_end && !jit->buf.failed) {
        size_t instr_start_native = jit->buf.size;
        ip_map_add(jit, ip, jit->buf.size);

        int consumed = emit_opcode(&ctx, ip);
        if (consumed < 0) {
            /* Unknown or truncated instruction -- emit error */
            emit_save_sp(&jit->buf);
            emit_mov_reg_reg(&jit->buf, XDI, JIT_REG_VM);
            emit_mov_reg_imm32(&jit->buf, XSI, CVM_ERR_BAD_OPCODE);
            emit_call_abs(&jit->buf, (void *)cvm_jit_error, X10);
            emit_mov_reg_imm32(&jit->buf, XAX, CVM_ERR_BAD_OPCODE);
            emit_epilogue(&jit->buf);
            break;
        }
        ip += (size_t)consumed;
    }

    /* Emit epilogue if not already terminated */
    if (jit->buf.size > 0 && jit->buf.code[jit->buf.size - 1] != 0xC3) {
        emit_epilogue(&jit->buf);
    }

    /* Apply patches: for each jump, look up the native offset for the
     * target bytecode IP.  We need to search the ip_map. */
    for (size_t i = 0; i < ctx.patches->count; i++) {
        size_t off = ctx.patches->patches[i].patch_off;
        size_t bc_target = ctx.patches->patches[i].target;
        size_t native_target = (size_t)-1;
        /* Search from the beginning of ip_map */
        for (size_t j = 0; j < jit->ip_map_count; j++) {
            if (jit->ip_map[j].bytecode_ip == bc_target) {
                native_target = jit->ip_map[j].native_offset;
                break;
            }
        }
        if (native_target == (size_t)-1) {
            /* Target not in this function -- might be in another function.
             * For now, emit a return (target not compiled). */
            native_target = jit->buf.size;
            emit_mov_reg_imm32(&jit->buf, XAX, 0);
            emit_epilogue(&jit->buf);
        }
        int64_t rel = (int64_t)native_target - (int64_t)(off + 4);
        if (rel < INT32_MIN || rel > INT32_MAX) { jit->buf.failed = 1; break; }
        int32_t r = (int32_t)rel;
        memcpy(jit->buf.code + off, &r, 4);
    }

    if (jit->buf.failed) { free(ctx.patches); return NULL; }

    size_t native_size = jit->buf.size - native_start;
    func_cache_add(jit, func_idx, native_start, native_size, JIT_TIER_BASELINE);

    free(ctx.patches);
    return jit->buf.code + native_start;
}

/* ------------------------------------------------------------------ */
/*  Module compilation                                                  */
/* ------------------------------------------------------------------ */

int cvm_jit_compile_module(CvmState *vm) {
    if (!vm->jit || !JIT_STATE(vm)->enabled) return CVM_OK;
    ip_map_clear(vm->jit);
    for (uint32_t i = 0; i < vm->num_funcs; i++) {
        void *code = cvm_jit_compile_func(vm, i);
        if (!code) {
            fprintf(stderr, "cvm jit: failed to compile function %u\n", i);
        }
    }
    return CVM_OK;
}

/* ------------------------------------------------------------------ */
/*  Lookup                                                             */
/* ------------------------------------------------------------------ */

void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx) {
    if (!vm->jit) return NULL;
    JitFuncEntry *e = func_cache_find(vm->jit, func_idx);
    if (!e) return NULL;
    return JIT_STATE(vm)->buf.code + e->native_offset;
}

/* ------------------------------------------------------------------ */
/*  Execution                                                          */
/* ------------------------------------------------------------------ */

/* Find which function contains vm->ip */
static uint32_t find_func_for_ip(const CvmState *vm) {
    for (uint32_t i = 0; i < vm->num_funcs; i++) {
        size_t start = vm->funcs[i].code_off;
        size_t end = (i + 1 < vm->num_funcs) ? vm->funcs[i + 1].code_off : vm->code_size;
        if (vm->ip >= start && vm->ip < end) return i;
    }
    return (uint32_t)-1;
}

void cvm_jit_exec_one(CvmState *vm) {
    CvmJitState *jit = JIT_STATE(vm);
    if (!jit || !jit->enabled) return;
    uint32_t func = find_func_for_ip(vm);
    if (func >= vm->num_funcs) {
        fprintf(stderr, "cvm jit: no function for ip=%zu\n", vm->ip);
        vm->running = 0;
        vm->exit_code = CVM_ERR_BAD_FUNC;
        return;
    }
    void *native = cvm_jit_lookup(vm, func);
    if (native) {
        typedef void (*JitFn)(CvmState *);
        ((JitFn)native)(vm);
    } else {
        /* Fall back: interpret this function's bytecodes.
         * We run the interpreter until ip leaves this function or
         * vm->running becomes 0. */
        uint32_t start_func = func;
        while (vm->running) {
            uint32_t cur = find_func_for_ip(vm);
            if (cur != start_func) break;  /* left this function */
            /* Execute one instruction via the step function */
            extern int cvm_step(CvmState *);
            int rc = cvm_step(vm);
            if (rc) break;
        }
    }
}

int cvm_jit_run(CvmState *vm) {
    if (!vm->jit || !JIT_STATE(vm)->enabled) {
        /* Should not be called without JIT; fall back to interpreter */
        extern int cvm_run(CvmState *);
        return cvm_run(vm);
    }

    /* Compile all functions */
    cvm_jit_compile_module(vm);

    /* Set up entry frame (same as cvm_run) */
    vm->running = 1;
    vm->exit_code = 0;
    vm->instr_count = 0;
    vm->sp = 0;
    while (vm->frame_count) {
        if (vm->frame_count > 0) {
            free(vm->frames[vm->frame_count - 1].slots);
            vm->frames[vm->frame_count - 1].slots = NULL;
            vm->frame_count--;
        }
    }

    if (vm->entry_func >= vm->num_funcs) return CVM_ERR_BAD_FUNC;
    uint32_t entry_locals = vm->funcs[vm->entry_func].num_locals;
    /* push_frame equivalent */
    if (vm->frame_count >= vm->max_frames) return CVM_ERR_FRAME_OVER;
    CvmFrame *f = &vm->frames[vm->frame_count];
    f->capacity = (entry_locals > 0 ? entry_locals : 16);
    f->slots = (uint64_t *)calloc(f->capacity, sizeof(uint64_t));
    f->return_ip = 0;
    f->func_idx = vm->entry_func;
    vm->frame_count++;
    vm->ip = vm->funcs[vm->entry_func].code_off;

    /* Set up stack base for argv (same as cvm_run) */
    /* data_w64 / data_r64 inline */
    if (vm->globals_size >= 104) {
        uint64_t stack_base = 0;
        if (vm->globals_size >= 96 + 8)
            memcpy(&stack_base, vm->globals + 96, 8);
        if (stack_base < CVM_MODULE_HEADER_SIZE) stack_base = 96;
        if (vm->globals_size >= stack_base + 8) {
            uint64_t stack_size = 0;
            memcpy(&stack_size, vm->globals + (size_t)stack_base + 88 - 96, 8);
            /* Actually, just use the same logic as interpreter */
        }
    }

    /* Dispatch loop */
    while (vm->running) {
        cvm_jit_exec_one(vm);
    }

    return CVM_OK;
}

/* ------------------------------------------------------------------ */
/*  Statistics                                                         */
/* ------------------------------------------------------------------ */

void cvm_jit_stats(const CvmState *vm) {
    if (!vm->jit) return;
    fprintf(stderr, "cvm jit: %zu functions compiled, %zu bytes of native code\n",
            JIT_STATE(vm)->num_funcs_compiled, JIT_STATE(vm)->buf.size);
    for (size_t i = 0; i < JIT_STATE(vm)->num_funcs_compiled; i++) {
        JitFuncEntry *e = &JIT_STATE(vm)->func_cache[i];
        fprintf(stderr, "  func %u: %zu bytes, tier %d, exec %u\n",
                e->func_idx, e->native_size, e->tier, e->exec_count);
    }
}

void cvm_jit_dump(const CvmState *vm) {
    if (!vm->jit) return;
    const CvmJitState *jit = JIT_STATE(vm);
    fprintf(stderr, "=== JIT DUMP: %zu functions ===\n", jit->num_funcs_compiled);
    for (size_t i = 0; i < jit->num_funcs_compiled; i++) {
        const JitFuncEntry *e = &jit->func_cache[i];
        fprintf(stderr, "func %u: offset=%zu size=%zu\n",
                e->func_idx, e->native_offset, e->native_size);
        const uint8_t *code = jit->buf.code + e->native_offset;
        for (size_t j = 0; j < e->native_size; j++) {
            fprintf(stderr, "%02x ", code[j]);
            if ((j+1) % 16 == 0) fprintf(stderr, "\n");
        }
        fprintf(stderr, "\n");
    }
}
