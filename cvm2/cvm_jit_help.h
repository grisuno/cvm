/**
 * @file cvm_jit_help.h
 * @brief Shared helper functions called by JIT-compiled CVM code.
 * @license GPL-2.0-or-later
 *
 * These C functions implement the complex operations that the JIT
 * emits calls to: CALL, RET, CALL_NATIVE, SYSCALL, memory checks,
 * ALLOC, and error handling.  They are NOT part of the interpreter;
 * the JIT compiler generates native code that calls them directly.
 */
#ifndef CVM_JIT_HELP_H
#define CVM_JIT_HELP_H

#include "cvm.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Register offsets into CvmState, used by JIT-compiled code for
 * direct field access.  These are computed once at JIT init time. */
typedef struct {
    size_t slots;
    size_t sp;
    size_t frames;
    size_t frame_count;
    size_t globals;
    size_t heap;
    size_t heap_used;
    size_t code;
    size_t code_size;
    size_t ip;
    size_t running;
    size_t exit_code;
    size_t natives;
    size_t native_map;
    size_t num_module_natives;
    size_t funcs;
    size_t num_funcs;
} CvmJitOffsets;

/* Compute and cache all field offsets.  Must be called once before
 * any JIT compilation begins. */
void cvm_jit_offsets_init(CvmJitOffsets *off);

/* ------------------------------------------------------------------ */
/*  Helpers called by JIT-compiled function prologues/epilogues        */
/* ------------------------------------------------------------------ */

/* Called at JIT function entry to sync interpreter state.
 * Returns the code pointer for the function. */
uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx);

/* Called at JIT function exit to sync interpreter state back. */
void cvm_jit_func_leave(CvmState *vm);

/* ------------------------------------------------------------------ */
/*  CALL / RET / CALL_NATIVE helpers                                   */
/* ------------------------------------------------------------------ */

/* Execute OP_CALL: push a new frame, copy arguments from the operand
 * stack into the new frame's locals, and set vm->ip to the callee.
 * Returns 0 on success, non-zero error code on failure.
 * On success, the JIT must jump to vm->ip (the callee's code).
 * On failure, vm->running is set to 0 and vm->exit_code is set. */
int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc);

/* Execute OP_RET: pop the current frame, push the return value onto
 * the operand stack, and set vm->ip to the caller's return address.
 * Returns 0 if there is a caller to return to (vm->ip is set).
 * Returns 1 if this was the entry frame (vm->running = 0, done). */
int cvm_jit_ret(CvmState *vm, uint64_t retval);

/* Execute OP_CALL_NATIVE: resolve the native function by index,
 * pop arguments from the operand stack, call the host function,
 * and push the result.  Returns 0 on success. */
int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc);

/* ------------------------------------------------------------------ */
/*  Memory check helpers                                               */
/* ------------------------------------------------------------------ */

/* Validate that [addr, addr+size) falls within a valid CVM memory
 * region (heap, globals, string pool, or any frame's locals).
 * Returns 1 if valid, 0 if invalid. */
int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size);

/* ------------------------------------------------------------------ */
/*  ALLOC helper                                                       */
/* ------------------------------------------------------------------ */

/* Bump-allocate 'size' bytes from the CVM heap.
 * Returns the heap pointer on success, 0 on exhaustion. */
uint64_t cvm_jit_alloc(CvmState *vm, size_t size);

/* ------------------------------------------------------------------ */
/*  SYSCALL helper                                                     */
/* ------------------------------------------------------------------ */

/* Execute a Linux-style syscall.  Pops 'argc' arguments from the
 * operand stack, dispatches by syscall number, and pushes the result.
 * Returns 0 on success.  On exit syscall, vm->running is set to 0. */
int cvm_jit_syscall(CvmState *vm, uint8_t syscall_nr, uint8_t argc);

/* ------------------------------------------------------------------ */
/*  Error handling                                                     */
/* ------------------------------------------------------------------ */

/* Set an error code and terminate the VM.  This is called when a
 * JIT-compiled function detects an unrecoverable error (bad address,
 * stack overflow, etc.).  Sets vm->running = 0 and vm->exit_code. */
void cvm_jit_error(CvmState *vm, int error_code);

#ifdef __cplusplus
}
#endif
#endif /* CVM_JIT_HELP_H */
