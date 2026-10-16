# Index

| File | Purpose | Subsystem | Symbols | Used by |
|------|---------|-----------|---------|---------|
| `cvm.c` | cvm_error: — C Virtual Machine interpreter  #include "cvm.h" #include <stdarg.h> #include... | root | 20 | 0 |
| `cvm.h` | CVM_Header: /* Heap OP_ALLOC        = 0x80,   /* size on stack → ptr OP_FREE         = 0x81, /*... | root | 28 | 2 |
| `cvm2/cvm.c` | Vout: static int64_t native_atol(void *vm, int ac, uint64_t *av) { (void)vm; if (ac < 1) return... | cvm2 | 104 | 0 |
| `cvm2/cvm.h` | CvmOpcode: ifdef __cplusplus | cvm2 | 56 | 8 |
| `cvm2/cvm_dbg_main.c` | - | cvm2 | 21 | 0 |
| `cvm2/cvm_dis.c` | - | cvm2 | 9 | 0 |
| `cvm2/cvm_dis.h` | cvm_dis_module: #ifndef CVM_DIS_H #define CVM_DIS_H #include <stddef.h> #include <stdint.h>... | cvm2 | 4 | 3 |
| `cvm2/cvm_dis_main.c` | - | cvm2 | 2 | 0 |
| `cvm2/cvm_jit.c` | emit_stack_pop_into: /* Push rax onto the operand stack: slots[sp] = rax; sp++ static void... | cvm2 | 37 | 0 |
| `cvm2/cvm_jit.h` | cvm_jit_create: /* IP-to-native mapping (shared across all functions) JitIpMap... | cvm2 | 26 | 4 |
| `cvm2/cvm_jit_help.c` | - | cvm2 | 22 | 0 |
| `cvm2/cvm_jit_help.h` | CvmJitOffsets: Register offsets into CvmState, used by JIT-compiled code for * direct field access. | cvm2 | 13 | 2 |
| `cvm2/cvm_jit_x86.c` | emit_rex: emit_grow(b, 8); if (!b->failed) { memcpy(b->code + b->size, &v, 8); b->size += 8; } }... | cvm2 | 73 | 0 |
| `cvm2/cvm_jit_x86.h` | JitBuf: /* Condition codes for Jcc / SETcc enum { CC_O   = 0x0, CC_NO  = 0x1, CC_B   = 0x2... | cvm2 | 71 | 2 |
| `cvm2/cvm_ops.c` | - | cvm2 | 7 | 0 |
| `cvm2/cvm_ops.h` | cvm_op_info: CVM_OPK_U32   = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL   = 6, CVM_OPK_U8U8  = 7 }... | cvm2 | 9 | 5 |
| `cvm2/cvm_val_main.c` | StackEffect: Stack effect of one instruction on the interval [lo,hi]: * required pops, then the... | cvm2 | 25 | 0 |
| `cvm2/cvm_view.c` | - | cvm2 | 8 | 0 |
| `cvm2/cvm_view.h` | cvm_view_open: uint32_t       num_strings; uint32_t       code_size; uint32_t... | cvm2 | 9 | 5 |
| `cvm2/deepseek_bash_20260808_653f26.sh` | - | cvm2 | 0 | 0 |
| `cvm2/gen_fib_cvm.c` | - | cvm2 | 10 | 0 |
| `cvm2/gen_minimal.c` | - | cvm2 | 4 | 0 |
| `cvm2/gen_test.py` | Generate a minimal .cvm that pushes 42 and halts. | cvm2 | 2 | 0 |
| `cvm2/test.sh` | CVM v2 toolchain suite: interpreter, disassembler, validator (including corrupted-module... | cvm2 | 2 | 0 |
| `gen_fib_cvm.c` | - | root | 3 | 0 |
| `test.sh` | - | root | 0 | 0 |
