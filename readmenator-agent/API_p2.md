# API (page 2 of 2)
Previous: [API.md](API.md)

## cvm2/gen_fib_cvm.c
Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`
- `emit_byte` (function) `cvm2/gen_fib_cvm.c:21` `static void emit_byte(uint8_t b)`
- `emit_u32` (function) `cvm2/gen_fib_cvm.c:30` `static void emit_u32(uint32_t v)`
- `emit_i32` (function) `cvm2/gen_fib_cvm.c:37` `static void emit_i32(int32_t v)`
- `patch_i32` (function) `cvm2/gen_fib_cvm.c:39` `static void patch_i32(size_t pos, int32_t val)`
- `write_le32` (function) `cvm2/gen_fib_cvm.c:46` `static void write_le32(uint8_t *p, uint32_t v)`
- `emit_global_inc` (function) `cvm2/gen_fib_cvm.c:53` `static void emit_global_inc(void)`
- `main` (function) `cvm2/gen_fib_cvm.c:64` `int main(int argc, char *argv[])`

## cvm2/gen_minimal.c
Depends on: `cvm2/cvm.h`
- `emit_byte` (function) `cvm2/gen_minimal.c:14` `static void emit_byte(uint8_t b)`
- `emit_u32` (function) `cvm2/gen_minimal.c:21` `static void emit_u32(uint32_t v)`
- `write_le32` (function) `cvm2/gen_minimal.c:25` `static void write_le32(uint8_t *p, uint32_t v)`
- `main` (function) `cvm2/gen_minimal.c:30` `int main(void)`

## gen_fib_cvm.c
Depends on: `cvm.h`
- `fib` (function) `gen_fib_cvm.c:7` `* return fib(n-1) + fib(n-2);`
- `add_string` (function) `gen_fib_cvm.c:24` `static uint32_t add_string(const char *s)`
- `main` (function) `gen_fib_cvm.c:36` `int main(void)`

