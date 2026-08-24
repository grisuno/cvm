/**
 * @file cvm_jit.h
 * @brief Multi-tier JIT compiler for CVM v2.
 * @license GPL-2.0-or-later
 *
 * Tier 0: Interpreter (existing switch-based dispatch)
 * Tier 1: Baseline JIT -- each function compiled to x86-64, no optimization
 * Tier 2: Optimizing JIT -- register allocation, peephole opts (future)
 *
 * The JIT compiles CVM bytecode to x86-64 native code at load time.
 * Each function is compiled independently and cached.  During execution,
 * a dispatch loop routes to compiled or interpreted functions.
 */
#ifndef CVM_JIT_H
#define CVM_JIT_H

#include "cvm.h"
#include "cvm_jit_x86.h"
#include "cvm_jit_help.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------------ */
/*  Register assignment for JIT-compiled code                          */
/* ------------------------------------------------------------------ */

/*
 * Callee-saved (preserved across C calls):
 *   r14 = CvmState *vm
 *   r12 = uint64_t *slots   (vm->slots)
 *   r13 = size_t sp          (vm->sp, element count)
 *   r15 = CvmFrame *frames   (vm->frames)
 *   rbx = CvmFrame *curframe (current frame pointer)
 *
 * Caller-saved (scratch):
 *   rax, rcx, rdx, rsi, rdi, r8, r9, r10, r11
 *
 * Stack access: [r12 + r13*8] = slots[sp]
 * Local access: [rbx + idx*8]  = frame->slots[idx]
 * VM fields:    [r14 + offset]
 */

#define JIT_REG_VM      X14
#define JIT_REG_SLOTS   X12
#define JIT_REG_SP      X13
#define JIT_REG_FRAMES  X15
#define JIT_REG_FRAME   XBX

/* Scratch registers for code generation */
#define JIT_SCRATCH1    XAX
#define JIT_SCRATCH2    XCX
#define JIT_SCRATCH3    XDX
#define JIT_SCRATCH4    XSI
#define JIT_SCRATCH5    XDI

/* ------------------------------------------------------------------ */
/*  JIT compilation tiers                                              */
/* ------------------------------------------------------------------ */

typedef enum {
    JIT_TIER_NONE       = 0,   /* not compiled */
    JIT_TIER_BASELINE   = 1,   /* Tier 1: call-based, no optimization */
    JIT_TIER_OPTIMIZING = 2,   /* Tier 2: register alloc, peephole (future) */
} JitTier;

/* ------------------------------------------------------------------ */
/*  Per-function compilation entry                                     */
/* ------------------------------------------------------------------ */

typedef struct {
    uint32_t func_idx;          /* CVM function index */
    size_t   native_offset;     /* offset into JitBuf.code */
    size_t   native_size;       /* size of compiled code in bytes */
    JitTier  tier;              /* compilation tier */
    uint32_t exec_count;        /* execution counter for tier-up */
} JitFuncEntry;

/* ------------------------------------------------------------------ */
/*  IP-to-native mapping (for jump resolution)                         */
/* ------------------------------------------------------------------ */

typedef struct {
    size_t bytecode_ip;         /* offset into CVM bytecode */
    size_t native_offset;       /* offset into native code buffer */
} JitIpMap;

/* ------------------------------------------------------------------ */
/*  JIT state (stored in CvmState.jit)                                 */
/* ------------------------------------------------------------------ */

#define JIT_MAX_FUNCS   8192
#define JIT_IP_MAP_SIZE (64 * 1024)

typedef struct {
    JitBuf          buf;                    /* executable code buffer */
    CvmJitOffsets   offsets;                /* CvmState field offsets */
    int             enabled;                /* JIT enabled flag */
    JitTier         max_tier;               /* maximum compilation tier */

    /* Per-function compilation cache */
    JitFuncEntry    func_cache[JIT_MAX_FUNCS];
    size_t          num_funcs_compiled;

    /* IP-to-native mapping (shared across all functions) */
    JitIpMap        ip_map[JIT_IP_MAP_SIZE];
    size_t          ip_map_count;

    /* Profile counters for tier-up */
    uint32_t        hot_threshold;          /* tier-up threshold */
    uint32_t        warm_threshold;         /* tier-1 threshold */
} CvmJitState;

/* ------------------------------------------------------------------ */
/*  JIT lifecycle                                                      */
/* ------------------------------------------------------------------ */

/* Create JIT state.  Call after cvm_create(). */
CvmJitState *cvm_jit_create(void);

/* Destroy JIT state.  Call before cvm_destroy(). */
void cvm_jit_destroy(CvmJitState *jit);

/* Compile all functions in a loaded module to native code.
 * Returns CVM_OK on success. */
int cvm_jit_compile_module(CvmState *vm);

/* Compile a single function.  Returns pointer to native code, or NULL. */
void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx);

/* Look up native code for a function.  Returns pointer or NULL. */
void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx);

/* ------------------------------------------------------------------ */
/*  JIT execution                                                      */
/* ------------------------------------------------------------------ */

/* Execute using the JIT.  Compiles all functions first, then dispatches
 * to compiled code.  Falls back to interpreter for uncompiled functions.
 * Returns CVM_OK on success. */
int cvm_jit_run(CvmState *vm);

/* Execute one compiled function at vm->ip.  Returns when the function
 * returns (via RET) or encounters an error. */
void cvm_jit_exec_one(CvmState *vm);

/* ------------------------------------------------------------------ */
/*  Statistics                                                          */
/* ------------------------------------------------------------------ */

/* Print JIT compilation statistics to stderr. */
void cvm_jit_stats(const CvmState *vm);

#ifdef __cplusplus
}
#endif
#endif /* CVM_JIT_H */
void cvm_jit_dump(const CvmState *vm);
