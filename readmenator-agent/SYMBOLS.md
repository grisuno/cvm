# Symbols

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `call_native` | function | `cvm.c:175` | `static void call_native(CVM *vm, uint16_t idx, uint8_t argc)` |
| `cvm_create` | function | `cvm.c:227` | `CVM *cvm_create(void)` |
| `cvm_destroy` | function | `cvm.c:244` | `void cvm_destroy(CVM *vm)` |
| `cvm_emit_byte` | function | `cvm.c:743` | `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b)` |
| `cvm_emit_i16` | function | `cvm.c:751` | `void cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v)` |
| `cvm_emit_i32` | function | `cvm.c:761` | `void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v)` |
| `cvm_emit_i64` | function | `cvm.c:766` | `void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v)` |
| `cvm_emit_u16` | function | `cvm.c:756` | `void cvm_emit_u16(uint8_t **buf, size_t *cap, size_t *len, uint16_t v)` |
| `cvm_error` | function | `cvm.c:12` | `static void cvm_error(CVM *vm, const char *fmt, ...)` |
| `cvm_load_module` | function | `cvm.c:337` | `int cvm_load_module(CVM *vm, const char *path)` |
| `cvm_load_module_mem` | function | `cvm.c:267` | `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name)` |
| `cvm_run` | function | `cvm.c:700` | `int cvm_run(CVM *vm, const char *entry_name)` |
| `interpret` | function | `cvm.c:361` | `static int interpret(CVM *vm)` |
| `main` | function | `cvm.c:775` | `int main(int argc, char **argv)` |
| `op_name` | function | `cvm.c:22` | `static const char *op_name(uint8_t op)` |
| `peek` | function | `cvm.c:94` | `static inline uint64_t peek(CVM *vm)` |
| `pop` | function | `cvm.c:86` | `static inline uint64_t pop(CVM *vm)` |
| `pop_frame` | function | `cvm.c:142` | `static void pop_frame(CVM *vm, int has_retval)` |
| `push` | function | `cvm.c:78` | `static inline void push(CVM *vm, uint64_t v)` |
| `push_frame` | function | `cvm.c:102` | `static int push_frame(CVM *vm, CVM_Module *mod, uint16_t func_idx, int argc)` |
| `CVM` | struct | `cvm.h:182` | `` |
| `CVM_FRAME_DEPTH` | macro | `cvm.h:156` | `#define CVM_FRAME_DEPTH` |
| `CVM_Frame` | struct | `cvm.h:161` | `` |
| `CVM_FuncEntry` | struct | `cvm.h:126` | `` |
| `CVM_GlobalEntry` | struct | `cvm.h:136` | `` |
| `CVM_H` | macro | `cvm.h:8` | `#define CVM_H` |
| `CVM_HEAP_SIZE` | macro | `cvm.h:157` | `#define CVM_HEAP_SIZE` |
| `CVM_Header` | struct | `cvm.h:107` | `` |
| `CVM_MAGIC` | macro | `cvm.h:22` | `#define CVM_MAGIC` |
| `CVM_MAX_MODULES` | macro | `cvm.h:158` | `#define CVM_MAX_MODULES` |
| `CVM_MAX_NATIVES` | macro | `cvm.h:159` | `#define CVM_MAX_NATIVES` |
| `CVM_Module` | struct | `cvm.h:169` | `` |
| `CVM_NativeEntry` | struct | `cvm.h:147` | `` |
| `CVM_STACK_SIZE` | macro | `cvm.h:155` | `#define CVM_STACK_SIZE` |
| `CVM_StringEntry` | struct | `cvm.h:142` | `` |
| `CVM_VERSION` | macro | `cvm.h:23` | `#define CVM_VERSION` |
| `cvm_call` | function | `cvm.h:220` | `int cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);` |
| `cvm_create` | function | `cvm.h:215` | `CVM *cvm_create(void);` |
| `cvm_destroy` | function | `cvm.h:216` | `void cvm_destroy(CVM *vm);` |
| `cvm_emit_byte` | function | `cvm.h:223` | `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);` |
| `cvm_emit_i16` | function | `cvm.h:224` | `void cvm_emit_i16 (uint8_t **buf, size_t *cap, size_t *len, int16_t v);` |
| `cvm_emit_i32` | function | `cvm.h:225` | `void cvm_emit_i32 (uint8_t **buf, size_t *cap, size_t *len, int32_t v);` |
| `cvm_emit_i64` | function | `cvm.h:226` | `void cvm_emit_i64 (uint8_t **buf, size_t *cap, size_t *len, int64_t v);` |
| `cvm_emit_u16` | function | `cvm.h:227` | `void cvm_emit_u16 (uint8_t **buf, size_t *cap, size_t *len, uint16_t v);` |
| `cvm_load_module` | function | `cvm.h:217` | `int cvm_load_module(CVM *vm, const char *path);` |
| `cvm_load_module_mem` | function | `cvm.h:218` | `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);` |
| `cvm_run` | function | `cvm.h:219` | `int cvm_run(CVM *vm, const char *entry_name);` |
| `hdr` | type_alias | `cvm.h:168` | `typedef struct CVM_Module { CVM_Header hdr;` |
| `CVM_DEF_CODE` | macro | `cvm2/cvm.c:22` | `#define CVM_DEF_CODE` |
| `CVM_DEF_FRAMES` | macro | `cvm2/cvm.c:16` | `#define CVM_DEF_FRAMES` |
| `CVM_DEF_FUNCS` | macro | `cvm2/cvm.c:20` | `#define CVM_DEF_FUNCS` |
| `CVM_DEF_GLOBALS` | macro | `cvm2/cvm.c:19` | `#define CVM_DEF_GLOBALS` |
| `CVM_DEF_HEAP` | macro | `cvm2/cvm.c:18` | `#define CVM_DEF_HEAP` |
| `CVM_DEF_LOCALS` | macro | `cvm2/cvm.c:17` | `#define CVM_DEF_LOCALS` |
| `CVM_DEF_NATIVES` | macro | `cvm2/cvm.c:21` | `#define CVM_DEF_NATIVES` |
| `CVM_DEF_PROFILE` | macro | `cvm2/cvm.c:23` | `#define CVM_DEF_PROFILE` |
| `CVM_DEF_STACK` | macro | `cvm2/cvm.c:15` | `#define CVM_DEF_STACK` |
| `CVM_HEAP_ALIGN` | macro | `cvm2/cvm.c:24` | `#define CVM_HEAP_ALIGN` |
| `CVM_MAX_NARGS` | macro | `cvm2/cvm.c:25` | `#define CVM_MAX_NARGS` |
| `CVM_MAX_SARGS` | macro | `cvm2/cvm.c:26` | `#define CVM_MAX_SARGS` |
| `Vout` | struct | `cvm2/cvm.c:465` | `` |
| `cur_frame` | function | `cvm2/cvm.c:203` | `static CvmFrame *cur_frame(CvmState *vm)` |
| `cvm_break_clear` | function | `cvm2/cvm.c:1003` | `int cvm_break_clear(CvmState *vm, size_t ip)` |
| `cvm_break_clear_all` | function | `cvm2/cvm.c:1014` | `void cvm_break_clear_all(CvmState *vm)` |
| `cvm_break_hit` | function | `cvm2/cvm.c:1018` | `int cvm_break_hit(const CvmState *vm)` |
| `cvm_break_set` | function | `cvm2/cvm.c:994` | `int cvm_break_set(CvmState *vm, size_t ip)` |
| `cvm_config_default` | function | `cvm2/cvm.c:40` | `CvmConfig cvm_config_default(void)` |
| `cvm_continue` | function | `cvm2/cvm.c:990` | `int cvm_continue(CvmState *vm)` |
| `cvm_create` | function | `cvm2/cvm.c:55` | `CvmState *cvm_create(const CvmConfig *config)` |
| `cvm_destroy` | function | `cvm2/cvm.c:94` | `void cvm_destroy(CvmState *vm)` |
| `cvm_exit_code` | function | `cvm2/cvm.c:1351` | `int64_t cvm_exit_code(const CvmState *vm)` |
| `cvm_free_module` | function | `cvm2/cvm.c:815` | `static void cvm_free_module(CvmState *vm)` |
| `cvm_heap_alloc` | function | `cvm2/cvm.c:235` | `void *cvm_heap_alloc(CvmState *vm, size_t size)` |
| `cvm_instruction_count` | function | `cvm2/cvm.c:1352` | `uint64_t cvm_instruction_count(const CvmState *vm)` |
| `cvm_load_module` | function | `cvm2/cvm.c:830` | `int cvm_load_module(CvmState *vm, const uint8_t *d, size_t sz)` |
| `cvm_load_module_file` | function | `cvm2/cvm.c:923` | `int cvm_load_module_file(CvmState *vm, const char *path)` |
| `cvm_profile_begin` | function | `cvm2/cvm.c:1024` | `int cvm_profile_begin(CvmState *vm)` |
| `cvm_profile_end` | function | `cvm2/cvm.c:1034` | `void cvm_profile_end(CvmState *vm)` |
| `cvm_register_native` | function | `cvm2/cvm.c:283` | `int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn)` |
| `cvm_run` | function | `cvm2/cvm.c:952` | `int cvm_run(CvmState *vm)` |
| `cvm_run_loop` | function | `cvm2/cvm.c:942` | `static int cvm_run_loop(CvmState *vm)` |
| `cvm_set_args` | function | `cvm2/cvm.c:250` | `int cvm_set_args(CvmState *vm, int argc, char **argv)` |
| `cvm_step` | function | `cvm2/cvm.c:1039` | `int cvm_step(CvmState *vm)` |
| `cvm_strerror` | function | `cvm2/cvm.c:113` | `const char *cvm_strerror(int e)` |
| `data_r64` | function | `cvm2/cvm.c:244` | `static uint64_t data_r64(CvmState *vm, size_t off)` |
| `data_w64` | function | `cvm2/cvm.c:239` | `static void data_w64(CvmState *vm, size_t off, uint64_t v)` |
| `decompress_rle` | function | `cvm2/cvm.c:793` | `static int decompress_rle(uint8_t *dst, size_t dsz, const uint8_t *src, size_t ssz)` |
| `find_native` | function | `cvm2/cvm.c:294` | `static int find_native(CvmState *vm, const char *name)` |
| `heap_alloc` | function | `cvm2/cvm.c:227` | `static uint64_t heap_alloc(CvmState *vm, size_t s)` |
| `main` | function | `cvm2/cvm.c:1355` | `int main(int argc, char *argv[])` |
| `mem_valid` | function | `cvm2/cvm.c:215` | `static int mem_valid(CvmState *vm, uint64_t a, size_t s)` |
| `native_abort` | function | `cvm2/cvm.c:324` | `static int64_t native_abort(void *vm, int ac, uint64_t *av)` |
| `native_atol` | function | `cvm2/cvm.c:451` | `static int64_t native_atol(void *vm, int ac, uint64_t *av)` |
| `native_calloc` | function | `cvm2/cvm.c:433` | `static int64_t native_calloc(void *vm, int ac, uint64_t *av)` |
| `native_exit` | function | `cvm2/cvm.c:317` | `static int64_t native_exit(void *vm, int ac, uint64_t *av)` |
| `native_exit_core` | function | `cvm2/cvm.c:729` | `static int64_t native_exit_core(void *vm, int ac, uint64_t *av)` |
| `native_fclose` | function | `cvm2/cvm.c:632` | `static int64_t native_fclose(void *vm, int ac, uint64_t *av)` |
| `native_fflush` | function | `cvm2/cvm.c:695` | `static int64_t native_fflush(void *vm, int ac, uint64_t *av)` |
| `native_fgetc` | function | `cvm2/cvm.c:683` | `static int64_t native_fgetc(void *vm, int ac, uint64_t *av)` |
| `native_fopen` | function | `cvm2/cvm.c:625` | `static int64_t native_fopen(void *vm, int ac, uint64_t *av)` |
| `native_fprintf` | function | `cvm2/cvm.c:583` | `static int64_t native_fprintf(void *vm, int ac, uint64_t *av)` |
| `native_fputc` | function | `cvm2/cvm.c:677` | `static int64_t native_fputc(void *vm, int ac, uint64_t *av)` |
| `native_fputs` | function | `cvm2/cvm.c:671` | `static int64_t native_fputs(void *vm, int ac, uint64_t *av)` |
| `native_fread` | function | `cvm2/cvm.c:638` | `static int64_t native_fread(void *vm, int ac, uint64_t *av)` |
| `native_free` | function | `cvm2/cvm.c:428` | `static int64_t native_free(void *vm, int ac, uint64_t *av)` |
| `native_fseek` | function | `cvm2/cvm.c:652` | `static int64_t native_fseek(void *vm, int ac, uint64_t *av)` |
| `native_ftell` | function | `cvm2/cvm.c:658` | `static int64_t native_ftell(void *vm, int ac, uint64_t *av)` |
| `native_fwrite` | function | `cvm2/cvm.c:645` | `static int64_t native_fwrite(void *vm, int ac, uint64_t *av)` |
| `native_malloc` | function | `cvm2/cvm.c:422` | `static int64_t native_malloc(void *vm, int ac, uint64_t *av)` |
| `native_memcmp` | function | `cvm2/cvm.c:415` | `static int64_t native_memcmp(void *vm, int ac, uint64_t *av)` |
| `native_memcpy` | function | `cvm2/cvm.c:395` | `static int64_t native_memcpy(void *vm, int ac, uint64_t *av)` |
| `native_memmove` | function | `cvm2/cvm.c:402` | `static int64_t native_memmove(void *vm, int ac, uint64_t *av)` |
| `native_memset` | function | `cvm2/cvm.c:409` | `static int64_t native_memset(void *vm, int ac, uint64_t *av)` |
| `native_perror` | function | `cvm2/cvm.c:701` | `static int64_t native_perror(void *vm, int ac, uint64_t *av)` |
| `native_printf` | function | `cvm2/cvm.c:593` | `static int64_t native_printf(void *vm, int ac, uint64_t *av)` |
| `native_putchar` | function | `cvm2/cvm.c:329` | `static int64_t native_putchar(void *vm, int ac, uint64_t *av)` |
| `native_puts` | function | `cvm2/cvm.c:336` | `static int64_t native_puts(void *vm, int ac, uint64_t *av)` |
| `native_read` | function | `cvm2/cvm.c:311` | `static int64_t native_read(void *vm, int ac, uint64_t *av)` |
| `native_realloc` | function | `cvm2/cvm.c:442` | `static int64_t native_realloc(void *vm, int ac, uint64_t *av)` |
| `native_rewind` | function | `cvm2/cvm.c:664` | `static int64_t native_rewind(void *vm, int ac, uint64_t *av)` |
| `native_snprintf` | function | `cvm2/cvm.c:613` | `static int64_t native_snprintf(void *vm, int ac, uint64_t *av)` |
| `native_sprintf` | function | `cvm2/cvm.c:602` | `static int64_t native_sprintf(void *vm, int ac, uint64_t *av)` |
| `native_stderr_addr` | function | `cvm2/cvm.c:712` | `static int64_t native_stderr_addr(void *vm, int ac, uint64_t *av)` |
| `native_stdin_addr` | function | `cvm2/cvm.c:722` | `static int64_t native_stdin_addr(void *vm, int ac, uint64_t *av)` |
| `native_stdout_addr` | function | `cvm2/cvm.c:717` | `static int64_t native_stdout_addr(void *vm, int ac, uint64_t *av)` |
| `native_strchr` | function | `cvm2/cvm.c:382` | `static int64_t native_strchr(void *vm, int ac, uint64_t *av)` |
| `native_strcmp` | function | `cvm2/cvm.c:356` | `static int64_t native_strcmp(void *vm, int ac, uint64_t *av)` |
| `native_strcpy` | function | `cvm2/cvm.c:369` | `static int64_t native_strcpy(void *vm, int ac, uint64_t *av)` |
| `native_strlen` | function | `cvm2/cvm.c:350` | `static int64_t native_strlen(void *vm, int ac, uint64_t *av)` |
| `native_strncmp` | function | `cvm2/cvm.c:362` | `static int64_t native_strncmp(void *vm, int ac, uint64_t *av)` |
| `native_strncpy` | function | `cvm2/cvm.c:375` | `static int64_t native_strncpy(void *vm, int ac, uint64_t *av)` |
| `native_strstr` | function | `cvm2/cvm.c:388` | `static int64_t native_strstr(void *vm, int ac, uint64_t *av)` |
| `native_strtol` | function | `cvm2/cvm.c:457` | `static int64_t native_strtol(void *vm, int ac, uint64_t *av)` |
| `native_ungetc` | function | `cvm2/cvm.c:689` | `static int64_t native_ungetc(void *vm, int ac, uint64_t *av)` |
| `native_write` | function | `cvm2/cvm.c:305` | `static int64_t native_write(void *vm, int ac, uint64_t *av)` |
| `pop_frame` | function | `cvm2/cvm.c:196` | `static void pop_frame(CvmState *vm)` |
| `push_frame` | function | `cvm2/cvm.c:183` | `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...` |
| `r32` | function | `cvm2/cvm.c:155` | `static int r32(CvmState *vm, uint32_t *o)` |
| `r64` | function | `cvm2/cvm.c:173` | `static int r64(CvmState *vm, uint64_t *o)` |
| `r8` | function | `cvm2/cvm.c:149` | `static int r8(CvmState *vm, uint8_t *o)` |
| `range_valid` | function | `cvm2/cvm.c:207` | `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)` |
| `register_defaults` | function | `cvm2/cvm.c:736` | `static void register_defaults(CvmState *vm)` |
| `ri32` | function | `cvm2/cvm.c:165` | `static int ri32(CvmState *vm, int32_t *o)` |
| `rl32` | function | `cvm2/cvm.c:788` | `static uint32_t rl32(const uint8_t *p)` |
| `vformat` | function | `cvm2/cvm.c:499` | `static void vformat(Vout *vo, const char *fmt, uint64_t *argv, int argc)` |
| `vo` | function | `cvm2/cvm.c:143` | `static int vo(CvmState *vm, uint64_t *v)` |
| `vout_char` | function | `cvm2/cvm.c:484` | `static void vout_char(Vout *vo, char c)` |
| `vout_uint` | function | `cvm2/cvm.c:486` | `static void vout_uint(Vout *vo, uint64_t v, int base, int upper)` |
| `vout_write` | function | `cvm2/cvm.c:472` | `static void vout_write(Vout *vo, const char *s, size_t n)` |
| `vp` | function | `cvm2/cvm.c:137` | `static int vp(CvmState *vm, uint64_t v)` |
| `xcal` | function | `cvm2/cvm.c:34` | `static void *xcal(size_t n, size_t s)` |
| `xmal` | function | `cvm2/cvm.c:28` | `static void *xmal(size_t s)` |
| `CVM_DATA_ARGC` | macro | `cvm2/cvm.h:60` | `#define CVM_DATA_ARGC` |
| `CVM_DATA_ARGS` | macro | `cvm2/cvm.h:64` | `#define CVM_DATA_ARGS` |
| `CVM_DATA_ARGV` | macro | `cvm2/cvm.h:61` | `#define CVM_DATA_ARGV` |
| `CVM_DATA_RBP` | macro | `cvm2/cvm.h:63` | `#define CVM_DATA_RBP` |
| `CVM_DATA_RET` | macro | `cvm2/cvm.h:65` | `#define CVM_DATA_RET` |
| `CVM_DATA_RSP` | macro | `cvm2/cvm.h:62` | `#define CVM_DATA_RSP` |
| `CVM_DATA_STACK_BASE` | macro | `cvm2/cvm.h:70` | `#define CVM_DATA_STACK_BASE` |
| `CVM_DATA_STACK_SIZE` | macro | `cvm2/cvm.h:66` | `#define CVM_DATA_STACK_SIZE` |
| `CVM_FUNC_ENTRY_SIZE` | macro | `cvm2/cvm.h:48` | `#define CVM_FUNC_ENTRY_SIZE` |
| `CVM_GLOBAL_ENTRY_SIZE` | macro | `cvm2/cvm.h:49` | `#define CVM_GLOBAL_ENTRY_SIZE` |
| `CVM_H` | macro | `cvm2/cvm.h:28` | `#define CVM_H` |
| `CVM_MAGIC_0` | macro | `cvm2/cvm.h:41` | `#define CVM_MAGIC_0` |
| `CVM_MAGIC_1` | macro | `cvm2/cvm.h:42` | `#define CVM_MAGIC_1` |
| `CVM_MAGIC_2` | macro | `cvm2/cvm.h:43` | `#define CVM_MAGIC_2` |
| `CVM_MAGIC_3` | macro | `cvm2/cvm.h:44` | `#define CVM_MAGIC_3` |
| `CVM_MAX_BREAKPOINTS` | macro | `cvm2/cvm.h:203` | `#define CVM_MAX_BREAKPOINTS` |
| `CVM_MAX_NARGS` | macro | `cvm2/cvm.h:53` | `#define CVM_MAX_NARGS` |
| `CVM_MAX_SARGS` | macro | `cvm2/cvm.h:54` | `#define CVM_MAX_SARGS` |
| `CVM_MODULE_HEADER_SIZE` | macro | `cvm2/cvm.h:47` | `#define CVM_MODULE_HEADER_SIZE` |
| `CVM_NATIVE_ENTRY_SIZE` | macro | `cvm2/cvm.h:50` | `#define CVM_NATIVE_ENTRY_SIZE` |
| `CVM_SHIFT_MASK` | macro | `cvm2/cvm.h:55` | `#define CVM_SHIFT_MASK` |
| `CVM_STRING_ENTRY_SIZE` | macro | `cvm2/cvm.h:51` | `#define CVM_STRING_ENTRY_SIZE` |
| `CVM_SYS_EXIT` | macro | `cvm2/cvm.h:58` | `#define CVM_SYS_EXIT` |
| `CVM_SYS_READ` | macro | `cvm2/cvm.h:56` | `#define CVM_SYS_READ` |
| `CVM_SYS_WRITE` | macro | `cvm2/cvm.h:57` | `#define CVM_SYS_WRITE` |
| `CVM_VERSION_MAJOR` | macro | `cvm2/cvm.h:45` | `#define CVM_VERSION_MAJOR` |
| `CVM_VERSION_MINOR` | macro | `cvm2/cvm.h:46` | `#define CVM_VERSION_MINOR` |
| `CvmBreakpoint` | struct | `cvm2/cvm.h:205` | `` |
| `CvmConfig` | struct | `cvm2/cvm.h:176` | `` |
| `CvmFrame` | struct | `cvm2/cvm.h:189` | `` |
| `CvmFuncEntry` | struct | `cvm2/cvm.h:154` | `` |
| `CvmGlobalEntry` | struct | `cvm2/cvm.h:162` | `` |
| `CvmNative` | struct | `cvm2/cvm.h:198` | `` |
| `CvmNativeEntry` | struct | `cvm2/cvm.h:167` | `` |
| `CvmOpcode` | variable | `cvm2/cvm.h:38` | `extern "C" { #endif #define CVM_MAGIC_0 0x43 #define CVM_MAGIC_1 0x56 #define CVM_MAGIC_2 0x4D #define CVM_MAGIC_3 0x04 ` |
| `CvmState` | struct | `cvm2/cvm.h:209` | `` |
| `CvmStringEntry` | struct | `cvm2/cvm.h:171` | `` |
| `cvm_break_clear` | function | `cvm2/cvm.h:263` | `int cvm_break_clear(CvmState *vm, size_t ip);` |
| `cvm_break_clear_all` | function | `cvm2/cvm.h:264` | `void cvm_break_clear_all(CvmState *vm);` |
| `cvm_break_hit` | function | `cvm2/cvm.h:265` | `int cvm_break_hit(const CvmState *vm);` |
| `cvm_break_set` | function | `cvm2/cvm.h:262` | `int cvm_break_set(CvmState *vm, size_t ip);` |
| `cvm_continue` | function | `cvm2/cvm.h:252` | `int cvm_continue(CvmState *vm);` |
| `cvm_create` | function | `cvm2/cvm.h:247` | `CvmState *cvm_create(const CvmConfig *config);` |
| `cvm_destroy` | function | `cvm2/cvm.h:248` | `void cvm_destroy(CvmState *vm);` |
| `cvm_exit_code` | function | `cvm2/cvm.h:254` | `int64_t cvm_exit_code(const CvmState *vm);` |
| `cvm_heap_alloc` | function | `cvm2/cvm.h:260` | `void *cvm_heap_alloc(CvmState *vm, size_t size);` |
| `cvm_instruction_count` | function | `cvm2/cvm.h:255` | `uint64_t cvm_instruction_count(const CvmState *vm);` |
| `cvm_load_module` | function | `cvm2/cvm.h:249` | `int cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);` |
| `cvm_load_module_file` | function | `cvm2/cvm.h:250` | `int cvm_load_module_file(CvmState *vm, const char *path);` |
| `cvm_profile_begin` | function | `cvm2/cvm.h:266` | `int cvm_profile_begin(CvmState *vm);` |
| `cvm_profile_end` | function | `cvm2/cvm.h:267` | `void cvm_profile_end(CvmState *vm);` |
| `cvm_register_native` | function | `cvm2/cvm.h:258` | `int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn);` |
| `cvm_run` | function | `cvm2/cvm.h:251` | `int cvm_run(CvmState *vm);` |
| `cvm_set_args` | function | `cvm2/cvm.h:259` | `int cvm_set_args(CvmState *vm, int argc, char **argv);` |
| `cvm_step` | function | `cvm2/cvm.h:253` | `int cvm_step(CvmState *vm);` |
| `cvm_strerror` | function | `cvm2/cvm.h:256` | `const char *cvm_strerror(int error_code);` |
| `DBG_LINE_MAX` | macro | `cvm2/cvm_dbg_main.c:18` | `#define DBG_LINE_MAX` |
| `DBG_PROFILE_TOP` | macro | `cvm2/cvm_dbg_main.c:19` | `#define DBG_PROFILE_TOP` |
| `cmd_break` | function | `cvm2/cvm_dbg_main.c:98` | `static void cmd_break(char *arg)` |
| `cmd_bt` | function | `cvm2/cvm_dbg_main.c:194` | `static void cmd_bt(void)` |
| `cmd_delete` | function | `cvm2/cvm_dbg_main.c:133` | `static void cmd_delete(char *arg)` |
| `cmd_help` | function | `cvm2/cvm_dbg_main.c:304` | `static void cmd_help(void)` |
| `cmd_info` | function | `cvm2/cvm_dbg_main.c:225` | `static void cmd_info(void)` |
| `cmd_list` | function | `cvm2/cvm_dbg_main.c:71` | `static void cmd_list(char *arg)` |
| `cmd_locals` | function | `cvm2/cvm_dbg_main.c:213` | `static void cmd_locals(void)` |
| `cmd_next` | function | `cvm2/cvm_dbg_main.c:166` | `static void cmd_next(void)` |
| `cmd_profile` | function | `cvm2/cvm_dbg_main.c:241` | `static void cmd_profile(char *arg)` |
| `cmd_run` | function | `cvm2/cvm_dbg_main.c:184` | `static void cmd_run(void)` |
| `cmd_stack` | function | `cvm2/cvm_dbg_main.c:206` | `static void cmd_stack(void)` |
| `cmd_step` | function | `cvm2/cvm_dbg_main.c:152` | `static void cmd_step(void)` |
| `dispatch` | function | `cvm2/cvm_dbg_main.c:310` | `static void dispatch(char *line)` |
| `emit_stdout` | function | `cvm2/cvm_dbg_main.c:29` | `static int emit_stdout(void *ctx, const char *line)` |
| `func_display` | function | `cvm2/cvm_dbg_main.c:36` | `static const char *func_display(uint32_t fi, char *fb, size_t cap)` |
| `func_of_ip` | function | `cvm2/cvm_dbg_main.c:40` | `static int func_of_ip(size_t ip)` |
| `main` | function | `cvm2/cvm_dbg_main.c:337` | `int main(int argc, char **argv)` |
| `parse_u32` | function | `cvm2/cvm_dbg_main.c:51` | `static int parse_u32(const char *s, uint32_t *out)` |
| `report_run` | function | `cvm2/cvm_dbg_main.c:59` | `static void report_run(int rc)` |
| `CVM_DIS_LINE_MAX` | macro | `cvm2/cvm_dis.c:11` | `#define CVM_DIS_LINE_MAX` |
| `cvm_dis_function` | function | `cvm2/cvm_dis.c:153` | `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end,
                     CvmDi...` |
| `cvm_dis_line` | function | `cvm2/cvm_dis.c:56` | `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end,
                 char *buf, size...` |
| `cvm_dis_module` | function | `cvm2/cvm_dis.c:173` | `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx)` |
| `pad_name` | function | `cvm2/cvm_dis.c:49` | `static void pad_name(char *buf, size_t cap, size_t *n, const char *name)` |
| `put_dec` | function | `cvm2/cvm_dis.c:35` | `static void put_dec(char *buf, size_t cap, size_t *n, int64_t v)` |
| `put_hex` | function | `cvm2/cvm_dis.c:21` | `static void put_hex(char *buf, size_t cap, size_t *n, uint64_t v, int digits)` |
| `putc_str` | function | `cvm2/cvm_dis.c:13` | `static void putc_str(char *buf, size_t cap, size_t *n, char c)` |
| `puts_str` | function | `cvm2/cvm_dis.c:17` | `static void puts_str(char *buf, size_t cap, size_t *n, const char *s)` |
| `CVM_DIS_H` | macro | `cvm2/cvm_dis.h:10` | `#define CVM_DIS_H` |
| `cvm_dis_function` | function | `cvm2/cvm_dis.h:26` | `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end, CvmDisEmit emit, void *ctx);` |
| `cvm_dis_line` | function | `cvm2/cvm_dis.h:31` | `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end, char *buf, size_t cap);` |
| `cvm_dis_module` | function | `cvm2/cvm_dis.h:23` | `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx);` |
| `main` | function | `cvm2/cvm_dis_main.c:18` | `int main(int argc, char **argv)` |
| `print_line` | function | `cvm2/cvm_dis_main.c:11` | `static int print_line(void *ctx, const char *line)` |
| `EMIT_CMP` | macro | `cvm2/cvm_jit.c:603` | `#define EMIT_CMP(cc_signed)` |
| `EMIT_CMP_SIGNED` | macro | `cvm2/cvm_jit.c:624` | `#define EMIT_CMP_SIGNED(cc)` |
| `EMIT_CMP_UNSIGNED` | macro | `cvm2/cvm_jit.c:636` | `#define EMIT_CMP_UNSIGNED(cc)` |
| `JIT_STATE` | macro | `cvm2/cvm_jit.c:30` | `#define JIT_STATE(vm)` |
| `JitCtx` | struct | `cvm2/cvm_jit.c:288` | `` |
| `cvm_jit_compile_func` | function | `cvm2/cvm_jit.c:1253` | `void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx)` |
| `cvm_jit_compile_module` | function | `cvm2/cvm_jit.c:1360` | `int cvm_jit_compile_module(CvmState *vm)` |
| `cvm_jit_create` | function | `cvm2/cvm_jit.c:36` | `CvmJitState *cvm_jit_create(void)` |
| `cvm_jit_destroy` | function | `cvm2/cvm_jit.c:48` | `void cvm_jit_destroy(CvmJitState *jit)` |
| `cvm_jit_dump` | function | `cvm2/cvm_jit.c:1499` | `void cvm_jit_dump(const CvmState *vm)` |
| `cvm_jit_exec_one` | function | `cvm2/cvm_jit.c:1397` | `void cvm_jit_exec_one(CvmState *vm)` |
| `cvm_jit_lookup` | function | `cvm2/cvm_jit.c:1376` | `void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx)` |
| `cvm_jit_run` | function | `cvm2/cvm_jit.c:1427` | `int cvm_jit_run(CvmState *vm)` |
| `cvm_jit_stats` | function | `cvm2/cvm_jit.c:1488` | `void cvm_jit_stats(const CvmState *vm)` |
| `cvm_run` | function | `cvm2/cvm_jit.c:1430` | `extern int cvm_run(CvmState *);` |
| `cvm_step` | function | `cvm2/cvm_jit.c:1420` | `extern int cvm_step(CvmState *);` |
| `emit_call1` | function | `cvm2/cvm_jit.c:146` | `static void emit_call1(JitBuf *b, void *fn, int arg)` |
| `emit_call2` | function | `cvm2/cvm_jit.c:152` | `static void emit_call2(JitBuf *b, void *fn, int a1, int a2)` |
| `emit_call3` | function | `cvm2/cvm_jit.c:159` | `static void emit_call3(JitBuf *b, void *fn, int a1, int a2, int a3)` |
| `emit_epilogue` | function | `cvm2/cvm_jit.c:232` | `static void emit_epilogue(JitBuf *b)` |
| `emit_opcode` | function | `cvm2/cvm_jit.c:302` | `static int emit_opcode(JitCtx *ctx, size_t bc_ip)` |
| `emit_prologue` | function | `cvm2/cvm_jit.c:170` | `static void emit_prologue(JitBuf *b)` |
| `emit_restore_sp` | function | `cvm2/cvm_jit.c:258` | `static void emit_restore_sp(JitBuf *b)` |
| `emit_save_sp` | function | `cvm2/cvm_jit.c:252` | `static void emit_save_sp(JitBuf *b)` |
| `emit_stack_pop` | function | `cvm2/cvm_jit.c:124` | `static void emit_stack_pop(JitBuf *b)` |
| `emit_stack_pop_into` | function | `cvm2/cvm_jit.c:130` | `static void emit_stack_pop_into(JitBuf *b, int dst)` |
| `emit_stack_push` | function | `cvm2/cvm_jit.c:117` | `static void emit_stack_push(JitBuf *b)` |
| `emit_stack_push_reg` | function | `cvm2/cvm_jit.c:136` | `static void emit_stack_push_reg(JitBuf *b, int reg)` |
| `error` | function | `cvm2/cvm_jit.c:267` | `* keeps executing dead code after the stop: error() -> exit() returns
 * into the middle of the f...` |
| `find_func_for_ip` | function | `cvm2/cvm_jit.c:1388` | `static uint32_t find_func_for_ip(const CvmState *vm)` |
| `func_cache_add` | function | `cvm2/cvm_jit.c:88` | `static JitFuncEntry *func_cache_add(CvmJitState *jit, uint32_t func_idx,
                        ...` |
| `func_cache_find` | function | `cvm2/cvm_jit.c:81` | `static JitFuncEntry *func_cache_find(CvmJitState *jit, uint32_t func_idx)` |
| `ip_map_add` | function | `cvm2/cvm_jit.c:62` | `static void ip_map_add(CvmJitState *jit, size_t bc_ip, size_t native_off)` |
| `ip_map_clear` | function | `cvm2/cvm_jit.c:58` | `static void ip_map_clear(CvmJitState *jit)` |
| `ip_map_lookup` | function | `cvm2/cvm_jit.c:69` | `static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip)` |
| `jit_apply_patches_local` | function | `cvm2/cvm_jit.c:1235` | `static void jit_apply_patches_local(JitBuf *b, const JitPatches *p)` |
| `opcode_total_size` | function | `cvm2/cvm_jit.c:105` | `static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip)` |
| `CVM_JIT_H` | macro | `cvm2/cvm_jit.h:15` | `#define CVM_JIT_H` |
| `CvmJitState` | struct | `cvm2/cvm_jit.h:96` | `` |
| `JIT_IP_MAP_SIZE` | macro | `cvm2/cvm_jit.h:94` | `#define JIT_IP_MAP_SIZE` |
| `JIT_MAX_FUNCS` | macro | `cvm2/cvm_jit.h:93` | `#define JIT_MAX_FUNCS` |
| `JIT_REG_FRAME` | macro | `cvm2/cvm_jit.h:49` | `#define JIT_REG_FRAME` |
| `JIT_REG_FRAMES` | macro | `cvm2/cvm_jit.h:48` | `#define JIT_REG_FRAMES` |
| `JIT_REG_SLOTS` | macro | `cvm2/cvm_jit.h:46` | `#define JIT_REG_SLOTS` |
| `JIT_REG_SP` | macro | `cvm2/cvm_jit.h:47` | `#define JIT_REG_SP` |
| `JIT_REG_VM` | macro | `cvm2/cvm_jit.h:45` | `#define JIT_REG_VM` |
| `JIT_SCRATCH1` | macro | `cvm2/cvm_jit.h:52` | `#define JIT_SCRATCH1` |
| `JIT_SCRATCH2` | macro | `cvm2/cvm_jit.h:53` | `#define JIT_SCRATCH2` |
| `JIT_SCRATCH3` | macro | `cvm2/cvm_jit.h:54` | `#define JIT_SCRATCH3` |
| `JIT_SCRATCH4` | macro | `cvm2/cvm_jit.h:55` | `#define JIT_SCRATCH4` |
| `JIT_SCRATCH5` | macro | `cvm2/cvm_jit.h:56` | `#define JIT_SCRATCH5` |
| `JitFuncEntry` | struct | `cvm2/cvm_jit.h:72` | `` |
| `JitIpMap` | struct | `cvm2/cvm_jit.h:84` | `` |
| `JitTier` | variable | `cvm2/cvm_jit.h:22` | `extern "C" { #endif /* ------------------------------------------------------------------ */ /* Register assignment for ` |
| `cvm_jit_compile_func` | function | `cvm2/cvm_jit.h:130` | `void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx);` |
| `cvm_jit_compile_module` | function | `cvm2/cvm_jit.h:127` | `int cvm_jit_compile_module(CvmState *vm);` |
| `cvm_jit_create` | function | `cvm2/cvm_jit.h:120` | `CvmJitState *cvm_jit_create(void);` |
| `cvm_jit_destroy` | function | `cvm2/cvm_jit.h:123` | `void cvm_jit_destroy(CvmJitState *jit);` |
| `cvm_jit_dump` | function | `cvm2/cvm_jit.h:159` | `void cvm_jit_dump(const CvmState *vm);` |
| `cvm_jit_lookup` | function | `cvm2/cvm_jit.h:133` | `void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx);` |
| `cvm_jit_run` | function | `cvm2/cvm_jit.h:142` | `int cvm_jit_run(CvmState *vm);` |
| `cvm_jit_stats` | function | `cvm2/cvm_jit.h:153` | `void cvm_jit_stats(const CvmState *vm);` |
| `returns` | function | `cvm2/cvm_jit.h:145` | `* returns (via RET) or encounters an error. */ void cvm_jit_exec_one(CvmState *vm);` |
| `CVM_HEAP_ALIGN` | macro | `cvm2/cvm_jit_help.c:16` | `#define CVM_HEAP_ALIGN` |
| `cur_frame` | function | `cvm2/cvm_jit_help.c:78` | `static CvmFrame *cur_frame(CvmState *vm)` |
| `cvm_jit_alloc` | function | `cvm2/cvm_jit_help.c:221` | `uint64_t cvm_jit_alloc(CvmState *vm, size_t size)` |
| `cvm_jit_call` | function | `cvm2/cvm_jit_help.c:155` | `int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc)` |
| `cvm_jit_call_native` | function | `cvm2/cvm_jit_help.c:193` | `int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc)` |
| `cvm_jit_error` | function | `cvm2/cvm_jit_help.c:256` | `void cvm_jit_error(CvmState *vm, int error_code)` |
| `cvm_jit_func_enter` | function | `cvm2/cvm_jit_help.c:136` | `uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx)` |
| `cvm_jit_func_leave` | function | `cvm2/cvm_jit_help.c:145` | `void cvm_jit_func_leave(CvmState *vm)` |
| `cvm_jit_memcheck` | function | `cvm2/cvm_jit_help.c:213` | `int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size)` |
| `cvm_jit_offsets_init` | function | `cvm2/cvm_jit_help.c:22` | `void cvm_jit_offsets_init(CvmJitOffsets *o)` |
| `cvm_jit_ret` | function | `cvm2/cvm_jit_help.c:176` | `int cvm_jit_ret(CvmState *vm, uint64_t retval)` |
| `cvm_jit_syscall` | function | `cvm2/cvm_jit_help.c:229` | `int cvm_jit_syscall(CvmState *vm, uint8_t sn, uint8_t argc)` |
| `find_native` | function | `cvm2/cvm_jit_help.c:110` | `static int find_native(const CvmState *vm, const char *name)` |
| `heap_alloc` | function | `cvm2/cvm_jit_help.c:102` | `static uint64_t heap_alloc(CvmState *vm, size_t s)` |
| `jit_vo` | function | `cvm2/cvm_jit_help.c:126` | `static int jit_vo(CvmState *vm, uint64_t *v)` |
| `jit_vp` | function | `cvm2/cvm_jit_help.c:120` | `static int jit_vp(CvmState *vm, uint64_t v)` |
| `mem_valid` | function | `cvm2/cvm_jit_help.c:90` | `static int mem_valid(const CvmState *vm, uint64_t a, size_t s)` |
| `pop_frame` | function | `cvm2/cvm_jit_help.c:71` | `static void pop_frame(CvmState *vm)` |
| `push_frame` | function | `cvm2/cvm_jit_help.c:58` | `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...` |
| `range_valid` | function | `cvm2/cvm_jit_help.c:82` | `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)` |
| `xcal` | function | `cvm2/cvm_jit_help.c:52` | `static void *xcal(size_t n, size_t s)` |
| `xmal` | function | `cvm2/cvm_jit_help.c:46` | `static void *xmal(size_t s)` |
| `CVM_JIT_HELP_H` | macro | `cvm2/cvm_jit_help.h:12` | `#define CVM_JIT_HELP_H` |
| `CvmJitOffsets` | struct | `cvm2/cvm_jit_help.h:22` | `` |
| `cvm_jit_alloc` | function | `cvm2/cvm_jit_help.h:94` | `uint64_t cvm_jit_alloc(CvmState *vm, size_t size);` |
| `cvm_jit_call` | function | `cvm2/cvm_jit_help.h:66` | `int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc);` |
| `cvm_jit_call_native` | function | `cvm2/cvm_jit_help.h:77` | `int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc);` |
| `cvm_jit_error` | function | `cvm2/cvm_jit_help.h:112` | `void cvm_jit_error(CvmState *vm, int error_code);` |
| `cvm_jit_func_enter` | function | `cvm2/cvm_jit_help.h:52` | `uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx);` |
| `cvm_jit_func_leave` | function | `cvm2/cvm_jit_help.h:55` | `void cvm_jit_func_leave(CvmState *vm);` |
| `cvm_jit_offsets_init` | function | `cvm2/cvm_jit_help.h:44` | `void cvm_jit_offsets_init(CvmJitOffsets *off);` |
| `cvm_jit_syscall` | function | `cvm2/cvm_jit_help.h:103` | `int cvm_jit_syscall(CvmState *vm, uint8_t syscall_nr, uint8_t argc);` |
| `region` | function | `cvm2/cvm_jit_help.h:84` | `* region (heap, globals, string pool, or any frame's locals). * Returns 1 if valid, 0 if invalid. */ int cvm_jit_memchec` |
| `slots` | variable | `cvm2/cvm_jit_help.h:17` | `extern "C" { #endif /* Register offsets into CvmState, used by JIT-compiled code for * direct field access. These are co` |
| `to` | function | `cvm2/cvm_jit_help.h:70` | `* Returns 0 if there is a caller to return to (vm->ip is set). * Returns 1 if this was the entry frame (vm->running = 0,` |
| `JIT_BUF_ALLOC` | macro | `cvm2/cvm_jit_x86.c:26` | `#define JIT_BUF_ALLOC(sz)` |
| `JIT_BUF_ALLOC` | macro | `cvm2/cvm_jit_x86.c:29` | `#define JIT_BUF_ALLOC(sz)` |
| `JIT_BUF_FAILED` | macro | `cvm2/cvm_jit_x86.c:32` | `#define JIT_BUF_FAILED` |
| `JIT_BUF_FREE` | macro | `cvm2/cvm_jit_x86.c:27` | `#define JIT_BUF_FREE(p, sz)` |
| `JIT_BUF_FREE` | macro | `cvm2/cvm_jit_x86.c:31` | `#define JIT_BUF_FREE(p, sz)` |
| `emit16` | function | `cvm2/cvm_jit_x86.c:89` | `void emit16(JitBuf *b, uint16_t v)` |
| `emit32` | function | `cvm2/cvm_jit_x86.c:94` | `void emit32(JitBuf *b, uint32_t v)` |
| `emit64` | function | `cvm2/cvm_jit_x86.c:99` | `void emit64(JitBuf *b, uint64_t v)` |
| `emit8` | function | `cvm2/cvm_jit_x86.c:84` | `void emit8(JitBuf *b, uint8_t v)` |
| `emit_add_reg_imm32` | function | `cvm2/cvm_jit_x86.c:299` | `void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm)` |
| `emit_add_reg_reg` | function | `cvm2/cvm_jit_x86.c:295` | `void emit_add_reg_reg(JitBuf *b, int dst, int src)` |
| `emit_and_reg_imm32` | function | `cvm2/cvm_jit_x86.c:372` | `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm)` |
| `emit_and_reg_reg` | function | `cvm2/cvm_jit_x86.c:380` | `void emit_and_reg_reg(JitBuf *b, int dst, int src)` |
| `emit_bytes` | function | `cvm2/cvm_jit_x86.c:104` | `void emit_bytes(JitBuf *b, const void *data, size_t len)` |
| `emit_call_abs` | function | `cvm2/cvm_jit_x86.c:552` | `void emit_call_abs(JitBuf *b, void *func, int scratch)` |
| `emit_call_reg` | function | `cvm2/cvm_jit_x86.c:519` | `void emit_call_reg(JitBuf *b, int reg)` |
| `emit_call_rel32` | function | `cvm2/cvm_jit_x86.c:512` | `size_t emit_call_rel32(JitBuf *b, int32_t rel)` |
| `emit_cmp_reg_reg` | function | `cvm2/cvm_jit_x86.c:430` | `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg)` |
| `emit_cqo` | function | `cvm2/cvm_jit_x86.c:341` | `void emit_cqo(JitBuf *b)` |
| `emit_dec_reg` | function | `cvm2/cvm_jit_x86.c:361` | `void emit_dec_reg(JitBuf *b, int reg)` |
| `emit_div_reg` | function | `cvm2/cvm_jit_x86.c:334` | `void emit_div_reg(JitBuf *b, int divisor)` |
| `emit_grow` | function | `cvm2/cvm_jit_x86.c:67` | `static void emit_grow(JitBuf *b, size_t need)` |
| `emit_idiv_reg` | function | `cvm2/cvm_jit_x86.c:327` | `void emit_idiv_reg(JitBuf *b, int divisor)` |
| `emit_imul_reg_reg` | function | `cvm2/cvm_jit_x86.c:320` | `void emit_imul_reg_reg(JitBuf *b, int dst, int src)` |
| `emit_inc_reg` | function | `cvm2/cvm_jit_x86.c:354` | `void emit_inc_reg(JitBuf *b, int reg)` |
| `emit_int3` | function | `cvm2/cvm_jit_x86.c:540` | `void emit_int3(JitBuf *b)` |
| `emit_jcc_buf` | function | `cvm2/cvm_jit_x86.c:487` | `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p)` |
| `emit_jcc_rel32` | function | `cvm2/cvm_jit_x86.c:467` | `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel)` |
| `emit_jmp_buf` | function | `cvm2/cvm_jit_x86.c:475` | `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p)` |
| `emit_jmp_rel32` | function | `cvm2/cvm_jit_x86.c:460` | `size_t emit_jmp_rel32(JitBuf *b, int32_t rel)` |
| `emit_lea_sib` | function | `cvm2/cvm_jit_x86.c:222` | `void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp)` |
| `emit_modrm` | function | `cvm2/cvm_jit_x86.c:119` | `void emit_modrm(JitBuf *b, int mod, int reg, int rm)` |
| `emit_modrm_disp32` | function | `cvm2/cvm_jit_x86.c:124` | `static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp)` |
| `emit_mov32_mem_reg` | function | `cvm2/cvm_jit_x86.c:214` | `void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src)` |
| `emit_mov32_reg_mem` | function | `cvm2/cvm_jit_x86.c:206` | `void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp)` |
| `emit_mov_mem_imm32` | function | `cvm2/cvm_jit_x86.c:569` | `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm)` |
| `emit_mov_mem_imm8` | function | `cvm2/cvm_jit_x86.c:561` | `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm)` |
| `emit_mov_mem_reg` | function | `cvm2/cvm_jit_x86.c:178` | `void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src)` |
| `emit_mov_reg_imm32` | function | `cvm2/cvm_jit_x86.c:152` | `void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm)` |
| `emit_mov_reg_imm64` | function | `cvm2/cvm_jit_x86.c:145` | `void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm)` |
| `emit_mov_reg_mem` | function | `cvm2/cvm_jit_x86.c:171` | `void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp)` |
| `emit_mov_reg_reg` | function | `cvm2/cvm_jit_x86.c:165` | `void emit_mov_reg_reg(JitBuf *b, int dst, int src)` |
| `emit_mov_reg_sib` | function | `cvm2/cvm_jit_x86.c:259` | `void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale)` |
| `emit_mov_sib_reg` | function | `cvm2/cvm_jit_x86.c:267` | `void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src)` |
| `emit_movsx_reg_mem32` | function | `cvm2/cvm_jit_x86.c:199` | `void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp)` |
| `emit_movzx_reg_mem16` | function | `cvm2/cvm_jit_x86.c:192` | `void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp)` |
| `emit_movzx_reg_mem8` | function | `cvm2/cvm_jit_x86.c:185` | `void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp)` |
| `emit_movzx_reg_reg8` | function | `cvm2/cvm_jit_x86.c:449` | `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src)` |
| `emit_neg_reg` | function | `cvm2/cvm_jit_x86.c:347` | `void emit_neg_reg(JitBuf *b, int reg)` |
| `emit_nop` | function | `cvm2/cvm_jit_x86.c:544` | `void emit_nop(JitBuf *b)` |
| `emit_not_reg` | function | `cvm2/cvm_jit_x86.c:392` | `void emit_not_reg(JitBuf *b, int reg)` |
| `emit_or_reg_reg` | function | `cvm2/cvm_jit_x86.c:384` | `void emit_or_reg_reg(JitBuf *b, int dst, int src)` |
| `emit_pop` | function | `cvm2/cvm_jit_x86.c:285` | `void emit_pop(JitBuf *b, int reg)` |
| `emit_push` | function | `cvm2/cvm_jit_x86.c:279` | `void emit_push(JitBuf *b, int reg)` |
| `emit_ret` | function | `cvm2/cvm_jit_x86.c:527` | `void emit_ret(JitBuf *b)` |
| `emit_rex` | function | `cvm2/cvm_jit_x86.c:114` | `void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b)` |
| `emit_rex_op_modrm` | function | `cvm2/cvm_jit_x86.c:130` | `static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm)` |
| `emit_sar_reg_cl` | function | `cvm2/cvm_jit_x86.c:413` | `void emit_sar_reg_cl(JitBuf *b, int reg)` |
| `emit_setcc` | function | `cvm2/cvm_jit_x86.c:440` | `void emit_setcc(JitBuf *b, int cc, int dst)` |
| `emit_shl_reg_cl` | function | `cvm2/cvm_jit_x86.c:399` | `void emit_shl_reg_cl(JitBuf *b, int reg)` |
| `emit_shr_reg_cl` | function | `cvm2/cvm_jit_x86.c:406` | `void emit_shr_reg_cl(JitBuf *b, int reg)` |
| `emit_sib` | function | `cvm2/cvm_jit_x86.c:137` | `static void emit_sib(JitBuf *b, int scale, int index, int base)` |
| `emit_sub_reg_imm32` | function | `cvm2/cvm_jit_x86.c:312` | `void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm)` |
| `emit_sub_reg_reg` | function | `cvm2/cvm_jit_x86.c:308` | `void emit_sub_reg_reg(JitBuf *b, int dst, int src)` |
| `emit_syscall` | function | `cvm2/cvm_jit_x86.c:535` | `void emit_syscall(JitBuf *b)` |
| `emit_test_reg_reg` | function | `cvm2/cvm_jit_x86.c:435` | `void emit_test_reg_reg(JitBuf *buf, int a, int breg)` |
| `emit_xor_reg_reg` | function | `cvm2/cvm_jit_x86.c:388` | `void emit_xor_reg_reg(JitBuf *b, int dst, int src)` |
| `emit_xor_reg_self` | function | `cvm2/cvm_jit_x86.c:420` | `void emit_xor_reg_self(JitBuf *b, int reg)` |
| `jit_apply_patches` | function | `cvm2/cvm_jit_x86.c:500` | `void jit_apply_patches(JitBuf *b, const JitPatches *p)` |
| `jit_buf_failed` | function | `cvm2/cvm_jit_x86.c:61` | `int jit_buf_failed(const JitBuf *b)` |
| `jit_buf_free` | function | `cvm2/cvm_jit_x86.c:48` | `void jit_buf_free(JitBuf *b)` |
| `jit_buf_init` | function | `cvm2/cvm_jit_x86.c:35` | `void jit_buf_init(JitBuf *b, size_t cap)` |
| `jit_buf_reset` | function | `cvm2/cvm_jit_x86.c:56` | `void jit_buf_reset(JitBuf *b)` |
| `CVM_JIT_X86_H` | macro | `cvm2/cvm_jit_x86.h:10` | `#define CVM_JIT_X86_H` |
| `JIT_MAX_PATCHES` | macro | `cvm2/cvm_jit_x86.h:53` | `#define JIT_MAX_PATCHES` |
| `JitBuf` | struct | `cvm2/cvm_jit_x86.h:40` | `` |
| `JitPatch` | struct | `cvm2/cvm_jit_x86.h:48` | `` |
| `JitPatches` | struct | `cvm2/cvm_jit_x86.h:55` | `` |
| `emit16` | function | `cvm2/cvm_jit_x86.h:72` | `void emit16(JitBuf *b, uint16_t v);` |
| `emit32` | function | `cvm2/cvm_jit_x86.h:73` | `void emit32(JitBuf *b, uint32_t v);` |
| `emit64` | function | `cvm2/cvm_jit_x86.h:74` | `void emit64(JitBuf *b, uint64_t v);` |
| `emit8` | function | `cvm2/cvm_jit_x86.h:71` | `void emit8(JitBuf *b, uint8_t v);` |
| `emit_add_reg_imm32` | function | `cvm2/cvm_jit_x86.h:149` | `void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm);` |
| `emit_add_reg_reg` | function | `cvm2/cvm_jit_x86.h:146` | `void emit_add_reg_reg(JitBuf *b, int dst, int src);` |
| `emit_and_reg_imm32` | function | `cvm2/cvm_jit_x86.h:272` | `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm);` |
| `emit_and_reg_reg` | function | `cvm2/cvm_jit_x86.h:185` | `void emit_and_reg_reg(JitBuf *b, int dst, int src);` |
| `emit_bytes` | function | `cvm2/cvm_jit_x86.h:75` | `void emit_bytes(JitBuf *b, const void *data, size_t len);` |
| `emit_call_abs` | function | `cvm2/cvm_jit_x86.h:269` | `void emit_call_abs(JitBuf *b, void *func, int scratch);` |
| `emit_call_reg` | function | `cvm2/cvm_jit_x86.h:244` | `void emit_call_reg(JitBuf *b, int reg);` |
| `emit_call_rel32` | function | `cvm2/cvm_jit_x86.h:241` | `size_t emit_call_rel32(JitBuf *b, int32_t rel);` |
| `emit_cmp_reg_reg` | function | `cvm2/cvm_jit_x86.h:213` | `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg);` |
| `emit_cqo` | function | `cvm2/cvm_jit_x86.h:169` | `void emit_cqo(JitBuf *b);` |
| `emit_dec_reg` | function | `cvm2/cvm_jit_x86.h:178` | `void emit_dec_reg(JitBuf *b, int reg);` |
| `emit_div_reg` | function | `cvm2/cvm_jit_x86.h:166` | `void emit_div_reg(JitBuf *b, int divisor);` |
| `emit_idiv_reg` | function | `cvm2/cvm_jit_x86.h:162` | `void emit_idiv_reg(JitBuf *b, int divisor);` |
| `emit_imul_reg_reg` | function | `cvm2/cvm_jit_x86.h:158` | `void emit_imul_reg_reg(JitBuf *b, int dst, int src);` |
| `emit_inc_reg` | function | `cvm2/cvm_jit_x86.h:175` | `void emit_inc_reg(JitBuf *b, int reg);` |
| `emit_int3` | function | `cvm2/cvm_jit_x86.h:257` | `void emit_int3(JitBuf *b);` |
| `emit_jcc_buf` | function | `cvm2/cvm_jit_x86.h:235` | `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p);` |
| `emit_jcc_rel32` | function | `cvm2/cvm_jit_x86.h:229` | `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel);` |
| `emit_jmp_buf` | function | `cvm2/cvm_jit_x86.h:232` | `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p);` |
| `emit_jmp_rel32` | function | `cvm2/cvm_jit_x86.h:226` | `size_t emit_jmp_rel32(JitBuf *b, int32_t rel);` |
| `emit_lea_sib` | function | `cvm2/cvm_jit_x86.h:121` | `void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp);` |
| `emit_modrm` | function | `cvm2/cvm_jit_x86.h:281` | `void emit_modrm(JitBuf *buf, int mod, int reg, int rm);` |
| `emit_mov32_mem_reg` | function | `cvm2/cvm_jit_x86.h:115` | `void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src);` |
| `emit_mov32_reg_mem` | function | `cvm2/cvm_jit_x86.h:112` | `void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp);` |
| `emit_mov_mem_imm32` | function | `cvm2/cvm_jit_x86.h:291` | `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm);` |
| `emit_mov_mem_imm8` | function | `cvm2/cvm_jit_x86.h:288` | `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm);` |
| `emit_mov_mem_reg` | function | `cvm2/cvm_jit_x86.h:100` | `void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src);` |
| `emit_mov_reg_imm32` | function | `cvm2/cvm_jit_x86.h:91` | `void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm);` |
| `emit_mov_reg_imm64` | function | `cvm2/cvm_jit_x86.h:88` | `void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm);` |
| `emit_mov_reg_mem` | function | `cvm2/cvm_jit_x86.h:97` | `void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp);` |
| `emit_mov_reg_reg` | function | `cvm2/cvm_jit_x86.h:94` | `void emit_mov_reg_reg(JitBuf *b, int dst, int src);` |
| `emit_mov_reg_sib` | function | `cvm2/cvm_jit_x86.h:126` | `void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale);` |
| `emit_mov_sib_reg` | function | `cvm2/cvm_jit_x86.h:129` | `void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src);` |
| `emit_movsx_reg_mem32` | function | `cvm2/cvm_jit_x86.h:109` | `void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp);` |
| `emit_movzx_reg_mem16` | function | `cvm2/cvm_jit_x86.h:106` | `void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp);` |
| `emit_movzx_reg_mem8` | function | `cvm2/cvm_jit_x86.h:103` | `void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp);` |
| `emit_movzx_reg_reg8` | function | `cvm2/cvm_jit_x86.h:275` | `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src);` |
| `emit_neg_reg` | function | `cvm2/cvm_jit_x86.h:172` | `void emit_neg_reg(JitBuf *b, int reg);` |
| `emit_nop` | function | `cvm2/cvm_jit_x86.h:260` | `void emit_nop(JitBuf *b);` |
| `emit_not_reg` | function | `cvm2/cvm_jit_x86.h:194` | `void emit_not_reg(JitBuf *b, int reg);` |
| `emit_or_reg_reg` | function | `cvm2/cvm_jit_x86.h:188` | `void emit_or_reg_reg(JitBuf *b, int dst, int src);` |
| `emit_pop` | function | `cvm2/cvm_jit_x86.h:139` | `void emit_pop(JitBuf *b, int reg);` |
| `emit_push` | function | `cvm2/cvm_jit_x86.h:136` | `void emit_push(JitBuf *b, int reg);` |
| `emit_ret` | function | `cvm2/cvm_jit_x86.h:247` | `void emit_ret(JitBuf *b);` |
| `emit_rex` | function | `cvm2/cvm_jit_x86.h:278` | `void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b);` |
| `emit_sar_reg_cl` | function | `cvm2/cvm_jit_x86.h:203` | `void emit_sar_reg_cl(JitBuf *b, int reg);` |
| `emit_setcc` | function | `cvm2/cvm_jit_x86.h:219` | `void emit_setcc(JitBuf *b, int cc, int dst);` |
| `emit_shl_reg_cl` | function | `cvm2/cvm_jit_x86.h:197` | `void emit_shl_reg_cl(JitBuf *b, int reg);` |
| `emit_shr_reg_cl` | function | `cvm2/cvm_jit_x86.h:200` | `void emit_shr_reg_cl(JitBuf *b, int reg);` |
| `emit_sub_reg_imm32` | function | `cvm2/cvm_jit_x86.h:155` | `void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm);` |
| `emit_sub_reg_reg` | function | `cvm2/cvm_jit_x86.h:152` | `void emit_sub_reg_reg(JitBuf *b, int dst, int src);` |
| `emit_syscall` | function | `cvm2/cvm_jit_x86.h:254` | `void emit_syscall(JitBuf *b);` |
| `emit_test_reg_reg` | function | `cvm2/cvm_jit_x86.h:216` | `void emit_test_reg_reg(JitBuf *buf, int a, int breg);` |
| `emit_xor_reg_reg` | function | `cvm2/cvm_jit_x86.h:191` | `void emit_xor_reg_reg(JitBuf *b, int dst, int src);` |
| `emit_xor_reg_self` | function | `cvm2/cvm_jit_x86.h:206` | `void emit_xor_reg_self(JitBuf *b, int reg);` |
| `jit_apply_patches` | function | `cvm2/cvm_jit_x86.h:238` | `void jit_apply_patches(JitBuf *b, const JitPatches *p);` |
| `jit_buf_failed` | function | `cvm2/cvm_jit_x86.h:66` | `int jit_buf_failed(const JitBuf *b);` |
| `jit_buf_free` | function | `cvm2/cvm_jit_x86.h:64` | `void jit_buf_free(JitBuf *b);` |
| `jit_buf_init` | function | `cvm2/cvm_jit_x86.h:63` | `void jit_buf_init(JitBuf *b, size_t initial_cap);` |
| `jit_buf_reset` | function | `cvm2/cvm_jit_x86.h:65` | `void jit_buf_reset(JitBuf *b);` |
| `reg_high3` | function | `cvm2/cvm_jit_x86.h:81` | `static inline int reg_high3(int r)` |
| `reg_needs_rex` | function | `cvm2/cvm_jit_x86.h:80` | `static inline int reg_needs_rex(int r)` |
| `OP_INFOS_LEN` | macro | `cvm2/cvm_ops.c:70` | `#define OP_INFOS_LEN` |
| `cvm_op_info` | function | `cvm2/cvm_ops.c:72` | `const CvmOpInfo *cvm_op_info(uint8_t opcode)` |
| `cvm_op_name` | function | `cvm2/cvm_ops.c:78` | `const char *cvm_op_name(uint8_t opcode)` |
| `cvm_ops_r8` | function | `cvm2/cvm_ops.c:83` | `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out)` |
| `cvm_ops_ri32` | function | `cvm2/cvm_ops.c:97` | `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off)` |
| `cvm_ops_ri64` | function | `cvm2/cvm_ops.c:101` | `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off)` |
| `cvm_ops_ru32` | function | `cvm2/cvm_ops.c:89` | `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off)` |
| `CVM_OPS_H` | macro | `cvm2/cvm_ops.h:10` | `#define CVM_OPS_H` |
| `CvmOpInfo` | struct | `cvm2/cvm_ops.h:30` | `` |
| `CvmOpKind` | variable | `cvm2/cvm_ops.h:16` | `extern "C" { #endif typedef enum { CVM_OPK_NONE = 0, CVM_OPK_I8 = 1, CVM_OPK_I32 = 2, CVM_OPK_I64 = 3, CVM_OPK_U32 = 4, ` |
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
| `check_static` | function | `cvm2/cvm_val_main.c:181` | `static int check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)` |
| `cmp_func` | function | `cvm2/cvm_val_main.c:450` | `static int cmp_func(const void *a, const void *b)` |
| `code_of` | function | `cvm2/cvm_val_main.c:68` | `static const uint8_t *code_of(const CvmModuleView *v)` |
| `dr_merge` | function | `cvm2/cvm_val_main.c:88` | `static int dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)` |
| `main` | function | `cvm2/cvm_val_main.c:456` | `int main(int argc, char **argv)` |
| `q_pop` | function | `cvm2/cvm_val_main.c:81` | `static size_t q_pop(FuncCtx *fc)` |
| `q_push` | function | `cvm2/cvm_val_main.c:72` | `static void q_push(FuncCtx *fc, size_t off)` |
| `stack_effect` | function | `cvm2/cvm_val_main.c:103` | `static int stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...` |
| `val_err` | function | `cvm2/cvm_val_main.c:56` | `static void val_err(ValCtx *ctx, const char *what)` |
| `val_fun_err` | function | `cvm2/cvm_val_main.c:61` | `static void val_fun_err(FuncCtx *fc, const char *what)` |
| `cvm_view_func` | function | `cvm2/cvm_view.c:72` | `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i)` |
| `cvm_view_func_name` | function | `cvm2/cvm_view.c:87` | `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,
                             ...` |
| `cvm_view_func_region` | function | `cvm2/cvm_view.c:108` | `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,
                         size_t *be...` |
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
