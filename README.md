# CVM - C Virtual Machine

A stack-based bytecode virtual machine for a C language subset, designed as an alternative execution backend for the [miniGCC](https://github.com/grisuno/miniGCC) and LazyC compilers. CVM compiles C source to a portable binary module format (`.cvm`) and interprets it at runtime, providing portability, sandboxing, and dynamic module loading without native code generation.

## Architecture

```
C source
  |
  v
miniGCC / LazyC (parser + semantic analysis)
  |
  +-- target=native --> x86-64 AT&T assembly --> as + ld --> ELF binary
  |
  +-- target=vm     --> CVM bytecode emitter --> .cvm module
                                                  |
                                                  v
                                            CVM interpreter
                                                  |
                                                  v
                                            Runtime (stack, heap, natives)
```

The parser and semantic analysis phases are shared across both targets. Only the code generation backend differs. The VM target emits bytecode instructions instead of x86-64 assembly, producing a self-contained binary module that the interpreter loads and executes.

## Project Structure

```
cvm.h            VM interface: opcodes, module format, runtime types, public API
cvm.c            Interpreter core: fetch-decode-execute loop, module loader,
                 frame management, heap allocator, native function registry,
                 bytecode emitter helpers, standalone CLI runner
gen_fib_cvm.c    Test module generator: builds a .cvm module in memory that
                 computes fib(10) recursively, serializes it to disk, then
                 loads and executes it through the VM to validate correctness
lazyc.c          LazyC compiler: C-to-x86-64 compiler with integrated ELF
                 hot-swap loader (BOF execution, trampoline-based far calls,
                 symbol resolution via dlsym)
minigcc.c        miniGCC compiler: self-hosting C compiler for x86-64 Linux,
                 generates standalone ELF with _start entry point
```

## Module Format (.cvm)

Every `.cvm` file follows a fixed binary layout:

```
Offset  Size  Field
0       4     Magic: 0x43 0x56 0x4D 0x01 ("CVM1")
4       2     Version major (currently 1)
6       2     Version minor (currently 0)
8       4     Number of functions
12      4     Number of globals
16      4     Number of native imports
20      4     Number of string constants
24      4     Code section size in bytes
28      4     String pool size in bytes
32      4     Entry function index
36      --    Function table (20 bytes per entry)
              - name_off:   u32, offset into string pool
              - code_off:   u32, offset into code section
              - num_locals: u32, local variable slot count
              - argc:       u32, parameter count
              - flags:      u32, reserved
--      --    Global table (12 bytes per entry)
              - name_off:   u32
              - init_value: u64
--      --    Native table (4 bytes per entry)
              - name_off:   u32
--      --    Code section (raw bytecode)
--      --    String pool (null-terminated strings)
```

All multi-byte integers are little-endian.

## Instruction Set

The VM is a 64-bit stack machine. All operand stack slots hold `uint64_t` values. Arithmetic operates on signed 64-bit integers unless otherwise noted.

### Constants and Stack

| Opcode | Hex  | Operands | Description |
|--------|------|----------|-------------|
| NOP | 0x00 | none | No operation |
| PUSH_IMM64 | 0x01 | i64 | Push 64-bit immediate |
| PUSH_IMM32 | 0x02 | i32 | Push sign-extended 32-bit immediate |
| PUSH_IMM8 | 0x03 | i8 | Push sign-extended 8-bit immediate |
| PUSH_ZERO | 0x04 | none | Push 0 |
| PUSH_ONE | 0x05 | none | Push 1 |

### Variables

| Opcode | Hex  | Operands | Description |
|--------|------|----------|-------------|
| PUSH_LOCAL | 0x10 | u32 slot | Push local variable value |
| STORE_LOCAL | 0x11 | u32 slot | Pop value into local variable |
| PUSH_GLOBAL | 0x12 | u32 index | Push global variable value |
| STORE_GLOBAL | 0x13 | u32 index | Pop value into global variable |

### Arithmetic

| Opcode | Hex  | Operands | Description |
|--------|------|----------|-------------|
| ADD | 0x20 | none | a + b |
| SUB | 0x21 | none | a - b |
| MUL | 0x22 | none | a * b |
| DIV | 0x23 | none | a / b (signed, traps on zero) |
| MOD | 0x24 | none | a % b (signed, traps on zero) |
| NEG | 0x25 | none | -a |

### Bitwise

| Opcode | Hex  | Operands | Description |
|--------|------|----------|-------------|
| AND | 0x30 | none | a & b |
| OR | 0x31 | none | a \| b |
| XOR | 0x32 | none | a ^ b |
| NOT | 0x33 | none | ~a |
| SHL | 0x34 | none | a << (b & 63) |
| SHR | 0x35 | none | a >> (b & 63), arithmetic |

### Comparison

| Opcode | Hex  | Operands | Description |
|--------|------|----------|-------------|
| CMP_EQ | 0x40 | none | Push 1 if a == b, else 0 |
| CMP_NE | 0x41 | none | Push 1 if a != b, else 0 |
| CMP_LT | 0x42 | none | Push 1 if a < b, else 0 |
| CMP_LE | 0x43 | none | Push 1 if a <= b, else 0 |
| CMP_GT | 0x44 | none | Push 1 if a > b, else 0 |
| CMP_GE | 0x45 | none | Push 1 if a >= b, else 0 |
| LNOT | 0x46 | none | Push 1 if a == 0, else 0 |

### Control Flow

| Opcode | Hex  | Operands | Description |
|--------|------|----------|-------------|
| JMP | 0x50 | i32 rel | Unconditional jump, relative to next instruction |
| JZ | 0x51 | i32 rel | Jump if top of stack is zero |
| JNZ | 0x52 | i32 rel | Jump if top of stack is nonzero |

### Functions

| Opcode | Hex  | Operands | Description |
|--------|------|----------|-------------|
| CALL | 0x60 | u32 func, u8 argc | Call VM function by index |
| RET | 0x61 | none | Return from function |
| CALL_NATIVE | 0x62 | u32 idx, u8 argc | Call registered native function |

### Memory

| Opcode | Hex  | Operands | Description |
|--------|------|----------|-------------|
| LOAD8 | 0x70 | none | Load signed byte from address |
| LOAD32 | 0x71 | none | Load signed 32-bit from address |
| LOAD64 | 0x72 | none | Load 64-bit from address |
| STORE8 | 0x73 | none | Store byte to address |
| STORE32 | 0x74 | none | Store 32-bit to address |
| STORE64 | 0x75 | none | Store 64-bit to address |
| LEA_LOCAL | 0x76 | u32 slot | Push address of local slot |
| LEA_GLOBAL | 0x77 | u32 index | Push address of global slot |

### System

| Opcode | Hex  | Operands | Description |
|--------|------|----------|-------------|
| ALLOC | 0x80 | none | Pop size, push heap pointer (bump allocator) |
| FREE | 0x81 | none | Pop pointer (no-op in bump allocator) |
| SYSCALL | 0x90 | u8 nr, u8 argc | Linux x86-64 syscall (write=1, exit=60) |
| HALT | 0xFF | none | Stop execution, exit code = top of stack |

## Building

Requirements: GCC or Clang with C99 support, GNU Make, libdl.

```bash
make all
```

This produces two binaries:

- `cvm` - Standalone interpreter with CLI
- `gen_fib_cvm` - Test module generator and validator

To build manually:

```bash
gcc -std=c99 -D_GNU_SOURCE -Wall -Wextra -Wpedantic -O2 \
    -DCVM_STANDALONE -o cvm cvm.c -ldl

gcc -std=c99 -D_GNU_SOURCE -Wall -Wextra -Wpedantic -O2 \
    -DCVM_NO_MAIN -o gen_fib_cvm gen_fib_cvm.c cvm.c -ldl
```

The `_GNU_SOURCE` define is required because `RTLD_DEFAULT` (used for native symbol resolution via `dlsym`) is a GNU extension not exposed under strict `-std=c99`.

## Usage

### Run the test suite

```bash
make test
```

This generates `fib.cvm`, executes it through the VM, and validates that `fib(10)` returns 55.

### Execute a module

```bash
./cvm module.cvm
```

The exit code of the process is the return value of the entry function.

### Execute with instruction trace

```bash
./cvm module.cvm --trace
```

Prints each instruction to stderr with its address, opcode, stack depth, and frame count.

### Generate and validate the test module

```bash
./gen_fib_cvm
```

Output:

```
Generated fib.cvm (132 bytes total, 56 bytes code)
fib(10) = 55 (expected 55)
instructions: 1769
STATUS: PASS
```

## Integration with miniGCC

The compiler parser remains unchanged. A `--target=vm` flag selects the bytecode backend. In each code generation function, a conditional branch emits either x86-64 assembly or CVM bytecode:

```c
static int target_vm = 0;

static void additive_expr(void) {
    multiplicative_expr();
    while (tok == '+' || tok == '-') {
        int op = tok;
        next_token();
        if (target_vm) {
            multiplicative_expr();
            if (op == '+') emit_op(OP_ADD);
            else           emit_op(OP_SUB);
        } else {
            emit("    pushq %%rax");
            multiplicative_expr();
            emit("    popq %%rcx");
            if (op == '+') emit("    addq %%rcx, %%rax");
            else {
                emit("    subq %%rax, %%rcx");
                emit("    movq %%rcx, %%rax");
            }
        }
    }
}
```

### Translation reference

| miniGCC x86-64 assembly | CVM bytecode | Size |
|--------------------------|--------------|------|
| `movq $42, %rax` | `PUSH_IMM8 42` | 2 bytes |
| `movq -8(%rbp), %rax` | `PUSH_LOCAL slot` | 5 bytes |
| `movq %rax, -8(%rbp)` | `STORE_LOCAL slot` | 5 bytes |
| `addq %rcx, %rax` (with push/pop) | `ADD` | 1 byte |
| `cmpq` + `setl` + `movzbq` | `CMP_LT` | 1 byte |
| `je .L5` | `JZ offset` | 5 bytes |
| `call printf` | `CALL_NATIVE idx argc` | 6 bytes |
| `leave` + `ret` | `RET` | 1 byte |

The bytecode is consistently smaller because the operand stack eliminates explicit register management.

## Runtime Limits

All limits are defined in `cvm.c` and configurable through `CvmConfig`:

| Parameter | Default | Description |
|-----------|---------|-------------|
| Stack capacity | 65536 slots | Operand stack depth |
| Max frames | 4096 | Call stack depth |
| Max locals per frame | 512 | Local variable slots |
| Heap size | 16 MB | Bump allocator region |
| Max globals | 4096 | Global variable slots |
| Max functions | 4096 | Functions per module |
| Max natives | 512 | Native function bindings |
| Max code size | 64 MB | Bytecode section limit |

## Native Functions

The VM registers three native functions by default:

| Index | Name | Signature | Description |
|-------|------|-----------|-------------|
| 0 | write | (fd, buf, len) -> ssize_t | POSIX write syscall |
| 1 | exit | (code) -> void | Terminate execution |
| 2 | putchar | (char) -> int | Write single byte to stdout |

Additional natives can be registered at runtime via `cvm_register_native()`.

## Error Handling

The interpreter returns negative error codes on failure:

| Code | Name | Description |
|------|------|-------------|
| 0 | CVM_OK | Success |
| -1 | CVM_ERR_ALLOC | Memory allocation failure |
| -2 | CVM_ERR_STACK_OVER | Operand stack overflow |
| -3 | CVM_ERR_STACK_UNDER | Operand stack underflow |
| -4 | CVM_ERR_BAD_OPCODE | Invalid opcode encountered |
| -5 | CVM_ERR_BAD_MODULE | Malformed module structure |
| -6 | CVM_ERR_BAD_MAGIC | Invalid module magic bytes |
| -7 | CVM_ERR_BAD_VERSION | Unsupported module version |
| -8 | CVM_ERR_DIV_ZERO | Division or modulo by zero |
| -9 | CVM_ERR_BAD_FUNC | Invalid function index |
| -10 | CVM_ERR_BAD_NATIVE | Invalid native function index |
| -11 | CVM_ERR_BAD_ADDR | Memory access outside heap bounds |
| -12 | CVM_ERR_FRAME_OVER | Call frame stack overflow |
| -13 | CVM_ERR_HEAP_OVER | Heap exhaustion |
| -14 | CVM_ERR_IO | File I/O error |
| -15 | CVM_ERR_BOUNDS | Index out of bounds |

## Testing

The test module (`gen_fib_cvm.c`) validates the full pipeline:

1. Bytecode emission for a recursive function with base case, conditional branch, two recursive calls, and arithmetic
2. Module serialization to the binary `.cvm` format
3. Module loading with header validation, table parsing, and code section extraction
4. Frame creation, parameter passing, and recursive call/return
5. Conditional branching (JZ with relative offset patching)
6. Arithmetic correctness (ADD, SUB, CMP_LE)
7. HALT with exit code propagation

Validated result: `fib(10) = 55`, 1769 instructions executed, zero compiler warnings under `-Wall -Wextra -Wpedantic`.

## License

AGPLv3

![Shell Script](https://img.shields.io/badge/shell_script-%23121011.svg?style=for-the-badge&logo=gnu-bash&logoColor=white) ![Flask](https://img.shields.io/badge/flask-%23000.svg?style=for-the-badge&logo=flask&logoColor=white) [![License: AGPL v3](https://img.shields.io/badge/License-AGPLv3-blue.svg)](https://www.gnu.org/licenses/agpl-3.0)

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/Y8Y2Z73AV)
