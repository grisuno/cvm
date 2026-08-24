# Multi-Tier JIT Compiler for CVM v2

## Architecture Overview

```
┌─────────────────────────────────────────────────┐
│                  CVM Module (.cvm)               │
└──────────────────────┬──────────────────────────┘
                       │
         ┌─────────────┼─────────────┐
         ▼             ▼             ▼
   ┌──────────┐  ┌──────────┐  ┌──────────┐
   │ Tier 0   │  │ Tier 1   │  │ Tier 2   │
   │Interprete│  │ Baseline │  │Optimizing│
   │ switch   │  │ call JIT │  │reg alloc │
   └──────────┘  └──────────┘  └──────────┘
         ▲             ▲             ▲
         └─────────────┴─────────────┘
              Profile-guided tier-up
```

**Tier 0 (Interpreter):** Existing switch-based dispatch in `cvm.c`. No changes.
**Tier 1 (Baseline JIT):** Each CVM function compiled to x86-64. Opcode dispatch via
  native `call` to shared helpers. Eliminates fetch-decode loop.
**Tier 2 (Optimizing JIT):** Register allocation, peephole opts, basic block merging.
  Triggered by profile counters on hot functions.

## Files to Create

| File | Role |
|------|------|
| `cvm_jit.h` | JIT API, data structures, tier definitions |
| `cvm_jit.c` | JIT compiler core: scan, compile, cache, tier-up logic |
| `cvm_jit_x86.h` | x86-64 code emitter API |
| `cvm_jit_x86.c` | x86-64 instruction encoding (MOV, ADD, CMP, JMP, CALL, etc.) |
| `cvm_jit_help.h` | Shared opcode helper functions (called by JIT'd code) |
| `cvm_jit_help.c` | Helper implementations (extracted from interpreter logic) |

## Files to Modify

| File | Changes |
|------|---------|
| `cvm.h` | Add `CvmJitState` to `CvmState`, add JIT config flags |
| `cvm.c` | Integrate JIT dispatch in `cvm_run()`, add profiling hooks |
| `Makefile` | Build new files, add `cvm_jit_test` target |

## Phase 1: x86-64 Code Emitter (`cvm_jit_x86.c/h`)

A minimal assembler that emits x86-64 bytes into a growable buffer.

### Register Encoding

```
RAX=0, RCX=1, RDX=2, RBX=3, RSP=4, RBP=5, RSI=6, RDI=7
R8=8, R9=9, R10=10, R11=11, R12=12, R13=13, R14=14, R15=15
```

### Dedicated Registers (fixed assignment)

```
r14 = CvmState* vm       (callee-saved, set once at entry)
r13 = uint64_t* slots    (vm->slots, operand stack base)
r12 = size_t sp           (vm->sp, operand stack pointer)
r15 = CvmFrame* frames    (vm->frames, current frame array)
```

### Emitter API

```c
typedef struct {
    uint8_t *code;      // mmap'd buffer with PROT_READ|PROT_WRITE|PROT_EXEC
    size_t   size;      // current emission offset
    size_t   capacity;  // buffer size
    // Relocation patches for forward jumps
    struct { size_t patch_off; int32_t offset; } relocs[4096];
    size_t num_relocs;
} JitBuf;

void jit_buf_init(JitBuf *b, size_t initial_cap);
void jit_buf_free(JitBuf *b);
void jit_buf_patch_rel32(JitBuf *b, size_t patch_off, size_t target);

// x86-64 emission helpers
void emit8(JitBuf *b, uint8_t v);
void emit32(JitBuf *b, uint32_t v);
void emit64(JitBuf *b, uint64_t v);

// Register operations
void emit_mov_reg_imm64(JitBuf *b, int reg, uint64_t imm);
void emit_mov_reg_imm32(JitBuf *b, int reg, int32_t imm);
void emit_mov_reg_reg(JitBuf *b, int dst, int src);
void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t offset);
void emit_mov_mem_reg(JitBuf *b, int base, int32_t offset, int src);
void emit_lea_reg_mem(JitBuf *b, int dst, int base, int32_t offset);

// Stack operations
void emit_push(JitBuf *b, int reg);
void emit_pop(JitBuf *b, int reg);

// Arithmetic
void emit_add_reg_reg(JitBuf *b, int dst, int src);
void emit_sub_reg_reg(JitBuf *b, int dst, int src);
void emit_imul_reg_reg(JitBuf *b, int dst, int src);
void emit_idiv_reg(JitBuf *b, int divisor_reg);  // divides RDX:RAX
void emit_neg_reg(JitBuf *b, int reg);
void emit_and_reg_reg(JitBuf *b, int dst, int src);
void emit_or_reg_reg(JitBuf *b, int dst, int src);
void emit_xor_reg_reg(JitBuf *b, int dst, int src);
void emit_not_reg(JitBuf *b, int reg);
void emit_shl_reg_cl(JitBuf *b, int reg);   // shift by CL
void emit_shr_reg_cl(JitBuf *b, int reg);   // arithmetic shr
void emit_sar_reg_cl(JitBuf *b, int reg);   // logical shr (USHR)

// Comparison
void emit_cmp_reg_reg(JitBuf *b, int a, int b);
void emit_setcc(JitBuf *b, int cc, int dst_reg);  // SETcc

// Control flow
void emit_jmp_rel32(JitBuf *b, int32_t rel);
void emit_jcc_rel32(JitBuf *b, int cc, int32_t rel);
void emit_call_rel32(JitBuf *b, int32_t rel);
void emit_ret(JitBuf *b);
void emit_call_reg(JitBuf *b, int reg);

// Syscall
void emit_syscall(JitBuf *b);

// Helpers for calling C functions with args
void emit_mov_reg_imm64(JitBuf *b, int reg, uint64_t imm);
```

## Phase 2: Baseline JIT Compiler (`cvm_jit.c/h`)

### JIT State

```c
typedef struct {
    uint8_t *native_code;     // mmap'd executable buffer
    size_t   code_size;
    size_t   code_used;

    // Per-function compilation cache
    struct {
        size_t cvm_ip;        // bytecode offset of function start
        void  *native_entry;  // address of compiled native code
        size_t native_size;   // size of compiled code
        int    tier;          // 0=none, 1=baseline, 2=optimizing
    } *func_cache;
    size_t num_func_cache;
    size_t func_cache_cap;

    // IP -> native offset mapping (for jumps within a function)
    size_t *ip_map;           // ip_map[cvm_ip] = native offset
    size_t  ip_map_size;

    // Profile counters
    uint32_t *exec_count;     // per-function execution count
    uint32_t  hot_threshold;  // tier-up threshold (default: 1000)

    // Opcode helpers (function pointers to shared code)
    void *helpers[256];
} CvmJitState;

// Added to CvmState:
typedef struct CvmState {
    // ... existing fields ...
    CvmJitState *jit;
} CvmState;
```

### Compilation Pipeline

```
1. cvm_jit_compile_func(vm, func_idx)
   │
   ├─ Scan bytecode of function to find:
   │  - Basic block boundaries (after JMP/JZ/JNZ targets)
   │  - Max stack depth
   │  - Number of locals
   │
   ├─ Allocate native code buffer for this function
   │
   ├─ Emit prologue:
   │  - push rbp; mov rbp, rsp
   │  - push r12; push r13; push r14; push r15  (callee-saved)
   │  - mov r14, rdi          (vm pointer from first arg)
   │  - mov r13, [r14+off]    (vm->slots)
   │  - mov r12d, [r14+off]   (vm->sp)
   │  - mov r15, [r14+off]    (vm->frames)
   │
   ├─ For each opcode in function:
   │  - Emit native code sequence
   │  - Record ip_map[bytecode_ip] = native_offset
   │
   ├─ Emit epilogue:
   │  - mov [r14+off], r12d   (save vm->sp)
   │  - pop r15; pop r14; pop r13; pop r12
   │  - pop rbp; ret
   │
   └─ Patch forward jumps (JMP/JZ/JNZ targets)
```

### Opcode Translation Table

Each CVM opcode maps to a native code sequence. Examples:

| CVM Opcode | Native x86-64 Sequence |
|------------|----------------------|
| `PUSH_IMM64 val` | `mov qword [r13+r12*8], val; inc r12` |
| `PUSH_IMM32 val` | `mov qword [r13+r12*8], (sign-ext val); inc r12` |
| `PUSH_ZERO` | `mov qword [r13+r12*8], 0; inc r12` |
| `PUSH_ONE` | `mov qword [r13+r12*8], 1; inc r12` |
| `PUSH_LOCAL i` | `mov rax, [r15+i*8]; mov [r13+r12*8], rax; inc r12` |
| `STORE_LOCAL i` | `dec r12; mov rax, [r13+r12*8]; mov [r15+i*8], rax` |
| `PUSH_GLOBAL i` | `mov rax, [vm->globals+i*8]; mov [r13+r12*8], rax; inc r12` |
| `STORE_GLOBAL i` | `dec r12; mov rax, [r13+r12*8]; mov [vm->globals+i*8], rax` |
| `ADD` | `dec r12; mov rax, [r13+r12*8]; dec r12; add rax, [r13+r12*8]; mov [r13+r12*8], rax; inc r12` |
| `SUB` | `dec r12; mov rax, [r13+r12*8]; dec r12; sub [r13+r12*8], rax; inc r12` |
| `MUL` | `dec r12; mov rax, [r13+r12*8]; dec r12; imul rax, [r13+r12*8]; mov [r13+r12*8], rax; inc r12` |
| `CMP_EQ` | `dec r12; mov rax, [r13+r12*8]; dec r12; cmp [r13+r12*8], rax; sete al; movzx rax, al; mov [r13+r12*8], rax; inc r12` |
| `JMP off` | `add r12, 0; (patched jmp to target)` |
| `JZ off` | `dec r12; cmp qword [r13+r12*8], 0; je target` |
| `JNZ off` | `dec r12; cmp qword [r13+r12*8], 0; jne target` |
| `CALL fi, na` | `call cvm_jit_call_helper` |
| `RET` | `call cvm_jit_ret_helper` |
| `CALL_NATIVE ni, na` | `call cvm_jit_native_helper` |
| `LOAD64` | `dec r12; mov rax, [r13+r12*8]; call cvm_jit_memcheck_8; mov rax, [rax]; mov [r13+r12*8], rax; inc r12` |
| `STORE64` | `dec r12; mov rcx, [r13+r12*8]; dec r12; mov rax, [r13+r12*8]; call cvm_jit_memcheck_8; mov [rax], rcx` |
| `ALLOC` | `dec r12; mov rdi, r14; mov rsi, [r13+r12*8]; call cvm_jit_alloc_helper; mov [r13+r12*8], rax; inc r12` |
| `SYSCALL sn, na` | `call cvm_jit_syscall_helper` |
| `HALT` | `mov [r14+off_running], 0; pop r15...ret` |

### Shared Helpers (called by JIT'd code)

These are C functions that the JIT'd code calls for complex operations:

```c
// CALL helper: push frame, copy args, set IP
int64_t cvm_jit_call_helper(CvmState *vm, uint32_t func_idx, uint8_t argc);

// RET helper: pop frame, restore IP, push return value
int64_t cvm_jit_ret_helper(CvmState *vm, uint64_t retval);

// CALL_NATIVE helper: resolve and call host function
int64_t cvm_jit_native_helper(CvmState *vm, uint32_t native_idx, uint8_t argc);

// Memory check helpers (bounds validation)
int cvm_jit_memcheck_8(CvmState *vm, uint64_t addr);
int cvm_jit_memcheck_16(CvmState *vm, uint64_t addr);
int cvm_jit_memcheck_32(CvmState *vm, uint64_t addr);

// ALLOC helper
uint64_t cvm_jit_alloc_helper(CvmState *vm, size_t size);

// SYSCALL helper
int64_t cvm_jit_syscall_helper(CvmState *vm, uint8_t sn, uint8_t argc);

// Error handler: set vm->exit_code, longjmp back to JIT entry
void cvm_jit_error(CvmState *vm, int error_code);
```

### Jump Resolution

For JMP/JZ/JNZ, the compiler:
1. First pass: record all jump targets (bytecode IP -> native offset)
2. Second pass: emit code with placeholder rel32
3. After all code emitted: patch all forward jumps

```c
// During compilation:
typedef struct {
    size_t patch_off;     // offset in native code where rel32 needs patching
    size_t target_ip;     // bytecode IP of jump target
} JitPatch;

// After function compiled:
for each patch:
    native_target = ip_map[patch.target_ip];
    patch_rel32(buf, patch.patch_off, native_target);
```

## Phase 3: Integration

### Modified `cvm_run()`

```c
int cvm_run(CvmState *vm) {
    // ... existing setup ...
    
    if (vm->jit && vm->jit->enabled) {
        // Try JIT compilation of entry function
        void *entry = cvm_jit_compile_func(vm, vm->entry_func);
        if (entry) {
            // JIT entry: call native code directly
            typedef int64_t (*JitEntry)(CvmState *);
            vm->running = 1;
            int64_t result = ((JitEntry)entry)(vm);
            vm->exit_code = result;
            return CVM_OK;
        }
    }
    
    // Fallback to interpreter
    return cvm_run_loop(vm);
}
```

### Profile-Guided Tier-Up

```c
// In cvm_step(), after executing OP_CALL:
if (vm->jit && vm->jit->enabled) {
    vm->jit->exec_count[func_idx]++;
    if (vm->jit->exec_count[func_idx] >= vm->jit->hot_threshold) {
        cvm_jit_compile_func(vm, func_idx);  // compile to Tier 1
    }
}
```

### Deoptimization

If JIT'd code detects an error (bad memory access, stack overflow, etc.):
1. The helper function calls `cvm_jit_error(vm, error_code)`
2. This sets vm->running = 0 and vm->exit_code
3. Returns via longjmp to the JIT entry point
4. The entry point returns the error to the caller

## Phase 4: Optimizing JIT (Tier 2)

### Trigger
When `exec_count[func] >= hot_threshold * 10`, recompile with optimizations.

### Optimizations

1. **Constant Folding:** If both operands of ADD/SUB/MUL are PUSH_IMM, compute at compile time
2. **Dead Store Elimination:** If a STORE_LOCAL is followed by another STORE_LOCAL to the same slot without a PUSH_LOCAL in between, eliminate the first
3. **Register Allocation:** Map hot local variables to x86 registers instead of memory
4. **Peephole:** Combine PUSH_LOCAL i + PUSH_LOCAL j + ADD into a single sequence that loads both into registers and adds
5. **Basic Block Merging:** If a JMP target is the very next instruction, eliminate the JMP

### Register Allocator (Simplified)

For Tier 2, use a simple linear-scan allocator:
- Map the most-used local variables to callee-saved registers (rbx, rbp, r12-r15 are taken, use rsi, rdi, r8-r11 for locals)
- Spill to memory when registers exhausted
- The operand stack still lives in memory (full SSA is out of scope)

## Build Integration

### Makefile Changes

```makefile
JIT_OBJS = cvm_jit.o cvm_jit_x86.o cvm_jit_help.o

cvm: cvm.c cvm.h cvm_jit.c cvm_jit.h cvm_jit_x86.c cvm_jit_x86.h cvm_jit_help.c cvm_jit_help.h
	$(CC) $(CFLAGS) -DCVM_STANDALONE -DCVM_JIT -o $@ cvm.c $(JIT_OBJS) $(LDFLAGS)

cvm_jit_test: cvm_jit_test.c cvm_jit.c cvm_jit_x86.c cvm_jit_help.c cvm.c cvm.h
	$(CC) $(CFLAGS) -DCVM_STANDALONE -DCVM_JIT -o $@ cvm_jit_test.c cvm.c $(JIT_OBJS) $(LDFLAGS)
```

### Runtime Control

```bash
./cvm module.cvm --jit            # enable JIT (tier 1 only)
./cvm module.cvm --jit-opt        # enable JIT with optimization (tier 1+2)
./cvm module.cvm --trace          # existing trace mode
./cvm module.cvm --jit --trace    # both
```

## Testing Strategy

1. **Unit tests for x86-64 emitter:** emit each instruction, mmap as function, call it, verify result
2. **Interpreter parity:** Run fib.cvm with interpreter and JIT, compare exit codes
3. **Fuzzing:** Random bytecode, compare interpreter vs JIT behavior
4. **BDD integration:** `test_bdd.sh` should pass with `--jit` flag
5. **Performance:** Benchmark fib(40) interpreter vs JIT, expect >2x speedup on Tier 1

## Implementation Order

1. `cvm_jit_x86.c/h` - code emitter (can test independently)
2. `cvm_jit_help.c/h` - shared helpers
3. `cvm_jit.c/h` - baseline JIT compiler (Tier 1)
4. Integration with `cvm.h`/`cvm.c`
5. `Makefile` updates
6. Tests
7. Tier 2 optimizing JIT (optional, future)
