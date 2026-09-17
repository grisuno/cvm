# Subsystem: root

## cvm.c
- Layer: utility
- Language: c
- Symbols:
  - `cvm_error` (function, line 12) `static void cvm_error(CVM *vm, const char *fmt, ...)`
  - `op_name` (function, line 21) `static const char *op_name(uint8_t op)`
  - `push` (function, line 78) `static inline void push(CVM *vm, uint64_t v)`
  - `pop` (function, line 85) `static inline uint64_t pop(CVM *vm)`
  - `peek` (function, line 93) `static inline uint64_t peek(CVM *vm)`
  - `push_frame` (function, line 102) `static int push_frame(CVM *vm, CVM_Module *mod, uint16_t func_idx, int argc)`
  - `pop_frame` (function, line 141) `static void pop_frame(CVM *vm, int has_retval)`
  - `call_native` (function, line 175) `static void call_native(CVM *vm, uint16_t idx, uint8_t argc)`
  - `cvm_create` (function, line 227) `CVM *cvm_create(void)`
  - `cvm_destroy` (function, line 243) `void cvm_destroy(CVM *vm)`
  - `cvm_load_module_mem` (function, line 267) `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name)`
  - `cvm_load_module` (function, line 336) `int cvm_load_module(CVM *vm, const char *path)`
  - `interpret` (function, line 361) `static int interpret(CVM *vm)`
  - `cvm_run` (function, line 700) `int cvm_run(CVM *vm, const char *entry_name)`
  - `cvm_emit_byte` (function, line 743) `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b)`
  - `cvm_emit_i16` (function, line 750) `void cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v)`
  - `cvm_emit_u16` (function, line 755) `void cvm_emit_u16(uint8_t **buf, size_t *cap, size_t *len, uint16_t v)`
  - `cvm_emit_i32` (function, line 760) `void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v)`
  - `cvm_emit_i64` (function, line 765) `void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v)`
  - `main` (function, line 775) `int main(int argc, char **argv)`
- Depends on: `cvm.h`

## cvm.h
- Layer: utility
- Language: h
- Symbols:
  - `CVM_Module` (struct, line 169)
  - `CVM_Header` (struct, line 107)
  - `CVM_FuncEntry` (struct, line 126)
  - `CVM_GlobalEntry` (struct, line 136)
  - `CVM_StringEntry` (struct, line 142)
  - `CVM_NativeEntry` (struct, line 147)
  - `CVM_Frame` (struct, line 161)
  - `CVM` (struct, line 182)
  - `hdr` (type_alias, line 168) `typedef struct CVM_Module { CVM_Header hdr;`
  - `cvm_create` (function, line 215) `CVM *cvm_create(void);`
  - `cvm_destroy` (function, line 216) `void cvm_destroy(CVM *vm);`
  - `cvm_load_module` (function, line 217) `int cvm_load_module(CVM *vm, const char *path);`
  - `cvm_load_module_mem` (function, line 218) `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);`
  - `cvm_run` (function, line 219) `int cvm_run(CVM *vm, const char *entry_name);`
  - `cvm_call` (function, line 220) `int cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);`
  - `cvm_emit_byte` (function, line 223) `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);`
  - `cvm_emit_i16` (function, line 224) `void cvm_emit_i16 (uint8_t **buf, size_t *cap, size_t *len, int16_t v);`
  - `cvm_emit_i32` (function, line 225) `void cvm_emit_i32 (uint8_t **buf, size_t *cap, size_t *len, int32_t v);`
  - `cvm_emit_i64` (function, line 226) `void cvm_emit_i64 (uint8_t **buf, size_t *cap, size_t *len, int64_t v);`
  - `cvm_emit_u16` (function, line 227) `void cvm_emit_u16 (uint8_t **buf, size_t *cap, size_t *len, uint16_t v);`
  - `CVM_H` (macro, line 8) `#define CVM_H`
  - `CVM_MAGIC` (macro, line 22) `#define CVM_MAGIC`
  - `CVM_VERSION` (macro, line 23) `#define CVM_VERSION`
  - `CVM_STACK_SIZE` (macro, line 155) `#define CVM_STACK_SIZE`
  - `CVM_FRAME_DEPTH` (macro, line 156) `#define CVM_FRAME_DEPTH`
  - `CVM_HEAP_SIZE` (macro, line 157) `#define CVM_HEAP_SIZE`
  - `CVM_MAX_MODULES` (macro, line 158) `#define CVM_MAX_MODULES`
  - `CVM_MAX_NATIVES` (macro, line 159) `#define CVM_MAX_NATIVES`
- Imported by: `cvm.c`, `gen_fib_cvm.c`

## gen_fib_cvm.c
- Layer: utility
- Language: c
- Symbols:
  - `add_string` (function, line 23) `static uint32_t add_string(const char *s)`
  - `main` (function, line 35) `int main(void)`
  - `fib` (function, line 7) `* return fib(n-1) + fib(n-2);`
- Depends on: `cvm.h`

## test.sh
- Layer: testing
- Language: sh
