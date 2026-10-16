# Symbols (page 2 of 2)
Previous: [SYMBOLS.md](SYMBOLS.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `CVM_OPS_H` | macro | `cvm2/cvm_ops.h:10` | `#define CVM_OPS_H` |
| `CvmOpInfo` | struct | `cvm2/cvm_ops.h:30` | `` |
| `CvmOpKind` | variable | `cvm2/cvm_ops.h:16` | `extern "C" { #endif typedef enum { CVM_OPK_NONE = 0, CVM_OPK_I8 = 1, CVM_OPK_I32 = 2, CVM_OPK_I64 = 3, CVM_OPK_U32 =...` |
| `cvm_op_info` | function | `cvm2/cvm_ops.h:38` | `const CvmOpInfo *cvm_op_info(uint8_t opcode);` |
| `cvm_op_name` | function | `cvm2/cvm_ops.h:41` | `const char *cvm_op_name(uint8_t opcode);` |
| `cvm_ops_r8` | function | `cvm2/cvm_ops.h:47` | `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out);` |
| `cvm_ops_ri32` | function | `cvm2/cvm_ops.h:44` | `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off);` |
| `cvm_ops_ri64` | function | `cvm2/cvm_ops.h:45` | `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off);` |
| `cvm_ops_ru32` | function | `cvm2/cvm_ops.h:46` | `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off);` |
| `CVM_VAL_MAX_ARGS` | macro | `cvm2/cvm_val_main.c:20` | `#define CVM_VAL_MAX_ARGS` |
| `CVM_VAL_MAX_CODE` | macro | `cvm2/cvm_val_main.c:18` | `#define CVM_VAL_MAX_CODE` |
| `CVM_VAL_MAX_FUNCS` | macro | `cvm2/cvm_val_main.c:15` | `#define CVM_VAL_MAX_FUNCS` |
| `CVM_VAL_MAX_GLOBALS` | macro | `cvm2/cvm_val_main.c:16` | `#define CVM_VAL_MAX_GLOBALS` |
| `CVM_VAL_MAX_LOCALS` | macro | `cvm2/cvm_val_main.c:19` | `#define CVM_VAL_MAX_LOCALS` |
| `CVM_VAL_MAX_NATIVES` | macro | `cvm2/cvm_val_main.c:17` | `#define CVM_VAL_MAX_NATIVES` |
| `CVM_VAL_MAX_SARGS` | macro | `cvm2/cvm_val_main.c:31` | `#define CVM_VAL_MAX_SARGS` |
| `CVM_VAL_STACK_CAP` | macro | `cvm2/cvm_val_main.c:25` | `#define CVM_VAL_STACK_CAP` |
| `CVM_VAL_WIDEN_BOUND` | macro | `cvm2/cvm_val_main.c:30` | `#define CVM_VAL_WIDEN_BOUND` |
| `DepthRange` | struct | `cvm2/cvm_val_main.c:33` | `` |
| `FuncCtx` | struct | `cvm2/cvm_val_main.c:45` | `` |
| `StackEffect` | struct | `cvm2/cvm_val_main.c:97` | `` |
| `ValCtx` | struct | `cvm2/cvm_val_main.c:38` | `` |
| `analyze_stack` | function | `cvm2/cvm_val_main.c:361` | `static int analyze_stack(FuncCtx *fc)` |
| `check_function` | function | `cvm2/cvm_val_main.c:435` | `static int check_function(FuncCtx *fc, size_t *insn_count)` |
| `check_static` | function | `cvm2/cvm_val_main.c:181` | `static int check_static(FuncCtx *fc, size_t off, uint8_t op,                         size_t next_ip)` |
| `cmp_func` | function | `cvm2/cvm_val_main.c:450` | `static int cmp_func(const void *a, const void *b)` |
| `code_of` | function | `cvm2/cvm_val_main.c:68` | `static const uint8_t *code_of(const CvmModuleView *v)` |
| `dr_merge` | function | `cvm2/cvm_val_main.c:88` | `static int dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)` |
| `main` | function | `cvm2/cvm_val_main.c:456` | `int main(int argc, char **argv)` |
| `q_pop` | function | `cvm2/cvm_val_main.c:81` | `static size_t q_pop(FuncCtx *fc)` |
| `q_push` | function | `cvm2/cvm_val_main.c:72` | `static void q_push(FuncCtx *fc, size_t off)` |
| `stack_effect` | function | `cvm2/cvm_val_main.c:103` | `static int stack_effect(const CvmModuleView *v, size_t off, uint8_t op,                         S...` |
| `val_err` | function | `cvm2/cvm_val_main.c:56` | `static void val_err(ValCtx *ctx, const char *what)` |
| `val_fun_err` | function | `cvm2/cvm_val_main.c:61` | `static void val_fun_err(FuncCtx *fc, const char *what)` |
| `cvm_view_func` | function | `cvm2/cvm_view.c:72` | `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i)` |
| `cvm_view_func_name` | function | `cvm2/cvm_view.c:87` | `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,                              ...` |
| `cvm_view_func_region` | function | `cvm2/cvm_view.c:108` | `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,                          size_t *be...` |
| `cvm_view_open` | function | `cvm2/cvm_view.c:29` | `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size)` |
| `cvm_view_strerror` | function | `cvm2/cvm_view.c:18` | `const char *cvm_view_strerror(int error_code)` |
| `cvm_view_string` | function | `cvm2/cvm_view.c:78` | `const char *cvm_view_string(const CvmModuleView *v, uint32_t off)` |
| `rl16` | function | `cvm2/cvm_view.c:14` | `static uint32_t rl16(const uint8_t *p)` |
| `rl32` | function | `cvm2/cvm_view.c:9` | `static uint32_t rl32(const uint8_t *p)` |
| `CVM_VIEW_H` | macro | `cvm2/cvm_view.h:9` | `#define CVM_VIEW_H` |
| `CvmModuleView` | struct | `cvm2/cvm_view.h:19` | `` |
| `cvm_view_func` | function | `cvm2/cvm_view.h:46` | `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i);` |
| `cvm_view_func_name` | function | `cvm2/cvm_view.h:53` | `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi, char *fallback, size_t cap);` |
| `cvm_view_func_region` | function | `cvm2/cvm_view.h:58` | `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi, size_t *begin, size_t *end);` |
| `cvm_view_open` | function | `cvm2/cvm_view.h:41` | `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size);` |
| `cvm_view_strerror` | function | `cvm2/cvm_view.h:44` | `const char *cvm_view_strerror(int error_code);` |
| `cvm_view_string` | function | `cvm2/cvm_view.h:50` | `const char *cvm_view_string(const CvmModuleView *v, uint32_t off);` |
| `data` | variable | `cvm2/cvm_view.h:16` | `extern "C" { #endif typedef struct { const uint8_t *data;` |
| `EXPECTED_CALLS` | macro | `cvm2/gen_fib_cvm.c:15` | `#define EXPECTED_CALLS` |
| `EXPECTED_FIB10` | macro | `cvm2/gen_fib_cvm.c:14` | `#define EXPECTED_FIB10` |
| `FIB_N` | macro | `cvm2/gen_fib_cvm.c:13` | `#define FIB_N` |
| `emit_byte` | function | `cvm2/gen_fib_cvm.c:21` | `static void emit_byte(uint8_t b)` |
| `emit_global_inc` | function | `cvm2/gen_fib_cvm.c:53` | `static void emit_global_inc(void)` |
| `emit_i32` | function | `cvm2/gen_fib_cvm.c:37` | `static void emit_i32(int32_t v)` |
| `emit_u32` | function | `cvm2/gen_fib_cvm.c:30` | `static void emit_u32(uint32_t v)` |
| `main` | function | `cvm2/gen_fib_cvm.c:64` | `int main(int argc, char *argv[])` |
| `patch_i32` | function | `cvm2/gen_fib_cvm.c:39` | `static void patch_i32(size_t pos, int32_t val)` |
| `write_le32` | function | `cvm2/gen_fib_cvm.c:46` | `static void write_le32(uint8_t *p, uint32_t v)` |
| `emit_byte` | function | `cvm2/gen_minimal.c:14` | `static void emit_byte(uint8_t b)` |
| `emit_u32` | function | `cvm2/gen_minimal.c:21` | `static void emit_u32(uint32_t v)` |
| `main` | function | `cvm2/gen_minimal.c:30` | `int main(void)` |
| `write_le32` | function | `cvm2/gen_minimal.c:25` | `static void write_le32(uint8_t *p, uint32_t v)` |
| `emit_byte` | function | `cvm2/gen_test.py:7` | `def emit_byte(b)` |
| `emit_u32` | function | `cvm2/gen_test.py:10` | `def emit_u32(v)` |
| `check` | function | `cvm2/test.sh:13` | `` |
| `reject` | function | `cvm2/test.sh:24` | `` |
| `add_string` | function | `gen_fib_cvm.c:24` | `static uint32_t add_string(const char *s)` |
| `fib` | function | `gen_fib_cvm.c:7` | `* return fib(n-1) + fib(n-2);` |
| `main` | function | `gen_fib_cvm.c:36` | `int main(void)` |

