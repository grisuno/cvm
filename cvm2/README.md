# cvm v2

Stack-bytecode interpreter for the CVM v2 module format, the format the
[miniGCC](https://github.com/grisuno/miniGCC) + [ld](https://github.com/grisuno/ld)
toolchain emits and the [miniOS](https://github.com/grisuno/miniOS) ramdisk
carries (`run file.cvm`). The interpreter executes x86-64 assembly translated
into CVM bytecode by `ld -f cvm`; the module ABI mirrors the x86-64 entry
state (argc/argv/envp on the stack, register arguments via fixed global
slots), so the same startup code works for ELF and CVM output.

## Building

```bash
make            # cvm, gen_fib_cvm, cvm-dis, cvm-validate, cvmdbg
make test       # fib(10) = 55 through every tool
./test.sh       # the full toolchain suite (hard-fail on any check)
```

Requirements: GCC or Clang with C99 support, GNU Make, libdl.

## Producing a module

`ld -f cvm` (from the [ld](https://github.com/grisuno/ld) repository)
assembles x86-64 AT&T assembly into a CVM v2 module; the assembly can come
from miniGCC or from the host `gcc -S`:

```bash
minigcc hello.c > hello.s
ld -f cvm -o hello.cvm hello.s

# or from host gcc output
gcc -S -O0 -fno-pic -fno-stack-protector -fno-asynchronous-unwind-tables \
    -fno-reorder-functions -fno-pie hello.c
ld -f cvm -o hello.cvm hello.s
```

The default output format of `ld` is CVM, so `ld hello.s -o hello.cvm`
suffices.

## Running

```bash
./cvm hello.cvm                  # no arguments
./cvm hello.cvm arg1 arg2        # Linux-style argv: argv[0] = "hello.cvm"
./cvm hello.cvm --trace arg1     # --trace prints each instruction to stderr
echo $?                          # the entry function's return value
```

Arguments follow the Linux convention: the module path is `argv[0]`, the
following words are `argv[1..]`, and `argc` counts both. `cvm_set_args()`
copies the strings into the module heap and builds the argv pointer array in
the reserved area at the top of the x86 stack region, so the startup code
every module carries reads them exactly as it would on real hardware.

## Module format (v2, little-endian)

```
off  0:  magic            'C','V','M',0x04
off  4:  version          u16 major, u16 minor  (1.0)
off  8:  num_functions    u32
off 12:  num_globals      u32
off 16:  num_natives      u32
off 20:  num_strings      u32
off 24:  code_size        u32
off 28:  string_pool_size u32
off 32:  data_size        u32   (uncompressed)
off 36:  entry_func       u32
off 40:  CvmFuncEntry[num_functions]    20 bytes each
         CvmGlobalEntry[num_globals]     8 bytes each
         CvmNativeEntry[num_natives]     4 bytes each
         CvmStringEntry[num_strings]     8 bytes each
         code[code_size]
         data (RLE-compressed, expands to data_size bytes:
               tag 0..253  -> tag+1 zero bytes
               tag 254     -> next byte n, then n literal bytes)
         string_pool[string_pool_size]  (last section in the file)
```

CvmFuncEntry: `name_off u32, code_off u32, num_locals u32, argc u32,
flags u32`. CvmGlobalEntry: `name_off u32, size u32` (the size drives the
decompressed data-section size). CvmNativeEntry: `name_off u32`.
CvmStringEntry: 8 bytes each, reserved for the string table; `ld` emits
zero strings (`name_off` fields index into the trailing string pool).

### Data section layout (what `ld` emits)

```
0     argc        u64   (Linux-style argc; the interpreter fills it)
8     argv        u64   (address of the argv pointer array)
16    rsp         u64   (initial x86 stack pointer)
24    rbp         u64   (initial frame pointer)
32..   args[0..5] u64   (the six System V argument registers)
80    ret         u64   (return-value slot)
88    stack_size  u64   (x86 stack region size)
96    stack_base  u64   (offset of the x86 stack region within the data)
104.. globals, string blobs, extern slots
...   x86 stack region (stack_size bytes, grows down from rsp)
...   argv area         (the interpreter writes the argv pointer array here)
```

The x86 stack region is placed at the end of the data section, and `ld`
reserves the argv area above it, so argument passing can never overwrite
global data or string constants. Older modules that predate the stored
`stack_base` keep it zeroed; the interpreter then falls back to the fixed
96-byte layout.

## Tools

| Tool | Role |
|------|------|
| `cvm` | standalone interpreter with CLI (`--trace`, arguments) |
| `cvm-dis` | disassembler: header summary, function listing, resolved jump/call targets |
| `cvm-validate` | structural validator: balance, jump targets, bounds; `-v` for verbose |
| `cvmdbg` | scripted debugger: `break`, `run`, `bt`, `profile run`/`show`, `quit` |
| `gen_fib_cvm` | in-memory module builder and validator: fib(10) must return 55 |

## MiniOS wiring

Inside MiniOS the interpreter ships as `cvm.o` (an ET_REL object linked
against the kernel symbol table, entry `cvm_main`). `run <file>.cvm` loads
`cvm.o` on first use and calls it with the full argv, so `run minigcc.cvm
test.c` inside the OS compiles `test.c` just like the standalone runner
above. The kernel-level natives in `cvm_host.c` back `write`, `read`,
`exit` and the libc-style symbols the toolchain needs.

## License

AGPLv3 (see the parent repository).