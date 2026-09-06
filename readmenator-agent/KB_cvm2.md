# Subsystem: cvm2

## cvm2/cvm.c
- Layer: utility
- Language: c
- Symbols:
  - `xmal` (function, line 27) `static void *xmal(size_t s)`
  - `xcal` (function, line 33) `static void *xcal(size_t n, size_t s)`
  - `cvm_config_default` (function, line 39) `CvmConfig cvm_config_default(void)`
  - `cvm_create` (function, line 54) `CvmState *cvm_create(const CvmConfig *config)`
  - `cvm_destroy` (function, line 93) `void cvm_destroy(CvmState *vm)`
  - `cvm_strerror` (function, line 112) `const char *cvm_strerror(int e)`
  - `vp` (function, line 136) `static int vp(CvmState *vm, uint64_t v)`
  - `vo` (function, line 142) `static int vo(CvmState *vm, uint64_t *v)`
  - `r8` (function, line 148) `static int r8(CvmState *vm, uint8_t *o)`
  - `r32` (function, line 154) `static int r32(CvmState *vm, uint32_t *o)`
  - `ri32` (function, line 164) `static int ri32(CvmState *vm, int32_t *o)`
  - `r64` (function, line 172) `static int r64(CvmState *vm, uint64_t *o)`
  - `push_frame` (function, line 182) `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...`
  - `pop_frame` (function, line 195) `static void pop_frame(CvmState *vm)`
  - `cur_frame` (function, line 202) `static CvmFrame *cur_frame(CvmState *vm)`
  - `range_valid` (function, line 206) `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)`
  - `mem_valid` (function, line 214) `static int mem_valid(CvmState *vm, uint64_t a, size_t s)`
  - `heap_alloc` (function, line 226) `static uint64_t heap_alloc(CvmState *vm, size_t s)`
  - `cvm_heap_alloc` (function, line 234) `void *cvm_heap_alloc(CvmState *vm, size_t size)`
  - `data_w64` (function, line 238) `static void data_w64(CvmState *vm, size_t off, uint64_t v)`
  - `data_r64` (function, line 243) `static uint64_t data_r64(CvmState *vm, size_t off)`
  - `cvm_set_args` (function, line 249) `int cvm_set_args(CvmState *vm, int argc, char **argv)`
  - `cvm_register_native` (function, line 282) `int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn)`
  - `find_native` (function, line 293) `static int find_native(CvmState *vm, const char *name)`
  - `native_write` (function, line 304) `static int64_t native_write(void *vm, int ac, uint64_t *av)`
  - `native_read` (function, line 310) `static int64_t native_read(void *vm, int ac, uint64_t *av)`
  - `native_exit` (function, line 316) `static int64_t native_exit(void *vm, int ac, uint64_t *av)`
  - `native_abort` (function, line 323) `static int64_t native_abort(void *vm, int ac, uint64_t *av)`
  - `native_putchar` (function, line 328) `static int64_t native_putchar(void *vm, int ac, uint64_t *av)`
  - `native_puts` (function, line 335) `static int64_t native_puts(void *vm, int ac, uint64_t *av)`
  - `native_strlen` (function, line 349) `static int64_t native_strlen(void *vm, int ac, uint64_t *av)`
  - `native_strcmp` (function, line 355) `static int64_t native_strcmp(void *vm, int ac, uint64_t *av)`
  - `native_strncmp` (function, line 361) `static int64_t native_strncmp(void *vm, int ac, uint64_t *av)`
  - `native_strcpy` (function, line 368) `static int64_t native_strcpy(void *vm, int ac, uint64_t *av)`
  - `native_strncpy` (function, line 374) `static int64_t native_strncpy(void *vm, int ac, uint64_t *av)`
  - `native_strchr` (function, line 381) `static int64_t native_strchr(void *vm, int ac, uint64_t *av)`
  - `native_strstr` (function, line 387) `static int64_t native_strstr(void *vm, int ac, uint64_t *av)`
  - `native_memcpy` (function, line 394) `static int64_t native_memcpy(void *vm, int ac, uint64_t *av)`
  - `native_memmove` (function, line 401) `static int64_t native_memmove(void *vm, int ac, uint64_t *av)`
  - `native_memset` (function, line 408) `static int64_t native_memset(void *vm, int ac, uint64_t *av)`
  - `native_memcmp` (function, line 414) `static int64_t native_memcmp(void *vm, int ac, uint64_t *av)`
  - `native_malloc` (function, line 421) `static int64_t native_malloc(void *vm, int ac, uint64_t *av)`
  - `native_free` (function, line 427) `static int64_t native_free(void *vm, int ac, uint64_t *av)`
  - `native_calloc` (function, line 432) `static int64_t native_calloc(void *vm, int ac, uint64_t *av)`
  - `native_realloc` (function, line 441) `static int64_t native_realloc(void *vm, int ac, uint64_t *av)`
  - `native_atol` (function, line 450) `static int64_t native_atol(void *vm, int ac, uint64_t *av)`
  - `native_strtol` (function, line 456) `static int64_t native_strtol(void *vm, int ac, uint64_t *av)`
  - `vout_write` (function, line 471) `static void vout_write(Vout *vo, const char *s, size_t n)`
  - `vout_char` (function, line 483) `static void vout_char(Vout *vo, char c)`
  - `vout_uint` (function, line 485) `static void vout_uint(Vout *vo, uint64_t v, int base, int upper)`
  - `vformat` (function, line 498) `static void vformat(Vout *vo, const char *fmt, uint64_t *argv, int argc)`
  - `native_fprintf` (function, line 582) `static int64_t native_fprintf(void *vm, int ac, uint64_t *av)`
  - `native_printf` (function, line 592) `static int64_t native_printf(void *vm, int ac, uint64_t *av)`
  - `native_sprintf` (function, line 601) `static int64_t native_sprintf(void *vm, int ac, uint64_t *av)`
  - `native_snprintf` (function, line 612) `static int64_t native_snprintf(void *vm, int ac, uint64_t *av)`
  - `native_fopen` (function, line 624) `static int64_t native_fopen(void *vm, int ac, uint64_t *av)`
  - `native_fclose` (function, line 631) `static int64_t native_fclose(void *vm, int ac, uint64_t *av)`
  - `native_fread` (function, line 637) `static int64_t native_fread(void *vm, int ac, uint64_t *av)`
  - `native_fwrite` (function, line 644) `static int64_t native_fwrite(void *vm, int ac, uint64_t *av)`
  - `native_fseek` (function, line 651) `static int64_t native_fseek(void *vm, int ac, uint64_t *av)`
  - `native_ftell` (function, line 657) `static int64_t native_ftell(void *vm, int ac, uint64_t *av)`
  - `native_rewind` (function, line 663) `static int64_t native_rewind(void *vm, int ac, uint64_t *av)`
  - `native_fputs` (function, line 670) `static int64_t native_fputs(void *vm, int ac, uint64_t *av)`
  - `native_fputc` (function, line 676) `static int64_t native_fputc(void *vm, int ac, uint64_t *av)`
  - `native_fgetc` (function, line 682) `static int64_t native_fgetc(void *vm, int ac, uint64_t *av)`
  - `native_ungetc` (function, line 688) `static int64_t native_ungetc(void *vm, int ac, uint64_t *av)`
  - `native_fflush` (function, line 694) `static int64_t native_fflush(void *vm, int ac, uint64_t *av)`
  - `native_perror` (function, line 700) `static int64_t native_perror(void *vm, int ac, uint64_t *av)`
  - `native_stderr_addr` (function, line 711) `static int64_t native_stderr_addr(void *vm, int ac, uint64_t *av)`
  - `native_stdout_addr` (function, line 716) `static int64_t native_stdout_addr(void *vm, int ac, uint64_t *av)`
  - `native_stdin_addr` (function, line 721) `static int64_t native_stdin_addr(void *vm, int ac, uint64_t *av)`
  - `native_exit_core` (function, line 728) `static int64_t native_exit_core(void *vm, int ac, uint64_t *av)`
  - `register_defaults` (function, line 735) `static void register_defaults(CvmState *vm)`
  - `rl32` (function, line 788) `static uint32_t rl32(const uint8_t *p)`
  - `decompress_rle` (function, line 792) `static int decompress_rle(uint8_t *dst, size_t dsz, const uint8_t *src, size_t ssz)`
  - `cvm_free_module` (function, line 814) `static void cvm_free_module(CvmState *vm)`
  - `cvm_load_module` (function, line 829) `int cvm_load_module(CvmState *vm, const uint8_t *d, size_t sz)`
  - `cvm_load_module_file` (function, line 922) `int cvm_load_module_file(CvmState *vm, const char *path)`
  - `cvm_run_loop` (function, line 942) `static int cvm_run_loop(CvmState *vm)`
  - `cvm_run` (function, line 951) `int cvm_run(CvmState *vm)`
  - `cvm_continue` (function, line 990) `int cvm_continue(CvmState *vm)`
  - `cvm_break_set` (function, line 993) `int cvm_break_set(CvmState *vm, size_t ip)`
  - `cvm_break_clear` (function, line 1002) `int cvm_break_clear(CvmState *vm, size_t ip)`
  - `cvm_break_clear_all` (function, line 1013) `void cvm_break_clear_all(CvmState *vm)`
  - `cvm_break_hit` (function, line 1017) `int cvm_break_hit(const CvmState *vm)`
  - `cvm_profile_begin` (function, line 1023) `int cvm_profile_begin(CvmState *vm)`
  - `cvm_profile_end` (function, line 1033) `void cvm_profile_end(CvmState *vm)`
  - `cvm_step` (function, line 1039) `int cvm_step(CvmState *vm)`
  - `cvm_exit_code` (function, line 1326) `int64_t cvm_exit_code(const CvmState *vm)`
  - `cvm_instruction_count` (function, line 1328) `uint64_t cvm_instruction_count(const CvmState *vm)`
  - `main` (function, line 1331) `int main(int argc, char *argv[])`
  - `CVM_DEF_STACK` (macro, line 14)
  - `CVM_DEF_FRAMES` (macro, line 16)
  - `CVM_DEF_LOCALS` (macro, line 17)
  - `CVM_DEF_HEAP` (macro, line 18)
  - `CVM_DEF_GLOBALS` (macro, line 19)
  - `CVM_DEF_FUNCS` (macro, line 20)
  - `CVM_DEF_NATIVES` (macro, line 21)
  - `CVM_DEF_CODE` (macro, line 22)
  - `CVM_DEF_PROFILE` (macro, line 23)
  - `CVM_HEAP_ALIGN` (macro, line 24)
  - `CVM_MAX_NARGS` (macro, line 25)
  - `CVM_MAX_SARGS` (macro, line 26)

## cvm2/cvm.h
- Layer: utility
- Language: h
- Symbols:
  - `CVM_H` (macro, line 28)
  - `CVM_MAGIC_0` (macro, line 40)
  - `CVM_MAGIC_1` (macro, line 42)
  - `CVM_MAGIC_2` (macro, line 43)
  - `CVM_MAGIC_3` (macro, line 44)
  - `CVM_VERSION_MAJOR` (macro, line 45)
  - `CVM_VERSION_MINOR` (macro, line 46)
  - `CVM_MODULE_HEADER_SIZE` (macro, line 47)
  - `CVM_FUNC_ENTRY_SIZE` (macro, line 48)
  - `CVM_GLOBAL_ENTRY_SIZE` (macro, line 49)
  - `CVM_NATIVE_ENTRY_SIZE` (macro, line 50)
  - `CVM_STRING_ENTRY_SIZE` (macro, line 51)
  - `CVM_MAX_NARGS` (macro, line 52)
  - `CVM_MAX_SARGS` (macro, line 54)
  - `CVM_SHIFT_MASK` (macro, line 55)
  - `CVM_SYS_READ` (macro, line 56)
  - `CVM_SYS_WRITE` (macro, line 57)
  - `CVM_SYS_EXIT` (macro, line 58)
  - `CVM_DATA_ARGC` (macro, line 59)
  - `CVM_DATA_ARGV` (macro, line 61)
  - `CVM_DATA_RSP` (macro, line 62)
  - `CVM_DATA_RBP` (macro, line 63)
  - `CVM_DATA_ARGS` (macro, line 64)
  - `CVM_DATA_RET` (macro, line 65)
  - `CVM_DATA_STACK_SIZE` (macro, line 66)
  - `CVM_DATA_STACK_BASE` (macro, line 70)
  - `CVM_MAX_BREAKPOINTS` (macro, line 199)

## cvm2/cvm_dbg_main.c
- Layer: utility
- Language: c
- Symbols:
  - `emit_stdout` (function, line 28) `static int emit_stdout(void *ctx, const char *line)`
  - `func_display` (function, line 35) `static const char *func_display(uint32_t fi, char *fb, size_t cap)`
  - `func_of_ip` (function, line 39) `static int func_of_ip(size_t ip)`
  - `parse_u32` (function, line 50) `static int parse_u32(const char *s, uint32_t *out)`
  - `report_run` (function, line 58) `static void report_run(int rc)`
  - `cmd_list` (function, line 70) `static void cmd_list(char *arg)`
  - `cmd_break` (function, line 97) `static void cmd_break(char *arg)`
  - `cmd_delete` (function, line 132) `static void cmd_delete(char *arg)`
  - `cmd_step` (function, line 151) `static void cmd_step(void)`
  - `cmd_next` (function, line 165) `static void cmd_next(void)`
  - `cmd_run` (function, line 183) `static void cmd_run(void)`
  - `cmd_bt` (function, line 193) `static void cmd_bt(void)`
  - `cmd_stack` (function, line 205) `static void cmd_stack(void)`
  - `cmd_locals` (function, line 212) `static void cmd_locals(void)`
  - `cmd_info` (function, line 224) `static void cmd_info(void)`
  - `cmd_profile` (function, line 240) `static void cmd_profile(char *arg)`
  - `cmd_help` (function, line 303) `static void cmd_help(void)`
  - `dispatch` (function, line 309) `static void dispatch(char *line)`
  - `main` (function, line 336) `int main(int argc, char **argv)`
  - `DBG_LINE_MAX` (macro, line 17)
  - `DBG_PROFILE_TOP` (macro, line 19)

## cvm2/cvm_dis.c
- Layer: infrastructure
- Language: c
- Symbols:
  - `putc_str` (function, line 12) `static void putc_str(char *buf, size_t cap, size_t *n, char c)`
  - `puts_str` (function, line 16) `static void puts_str(char *buf, size_t cap, size_t *n, const char *s)`
  - `put_hex` (function, line 20) `static void put_hex(char *buf, size_t cap, size_t *n, uint64_t v, int digits)`
  - `put_dec` (function, line 34) `static void put_dec(char *buf, size_t cap, size_t *n, int64_t v)`
  - `pad_name` (function, line 48) `static void pad_name(char *buf, size_t cap, size_t *n, const char *name)`
  - `cvm_dis_line` (function, line 55) `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end,
                 char *buf, size...`
  - `cvm_dis_function` (function, line 152) `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end,
                     CvmDi...`
  - `cvm_dis_module` (function, line 172) `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx)`
  - `CVM_DIS_LINE_MAX` (macro, line 10)

## cvm2/cvm_dis.h
- Layer: infrastructure
- Language: h
- Symbols:
  - `CVM_DIS_H` (macro, line 10)

## cvm2/cvm_dis_main.c
- Layer: infrastructure
- Language: c
- Symbols:
  - `print_line` (function, line 10) `static int print_line(void *ctx, const char *line)`
  - `main` (function, line 17) `int main(int argc, char **argv)`

## cvm2/cvm_jit.c
- Layer: utility
- Language: c
- Symbols:
  - `cvm_jit_create` (function, line 35) `CvmJitState *cvm_jit_create(void)`
  - `cvm_jit_destroy` (function, line 47) `void cvm_jit_destroy(CvmJitState *jit)`
  - `ip_map_clear` (function, line 57) `static void ip_map_clear(CvmJitState *jit)`
  - `ip_map_add` (function, line 61) `static void ip_map_add(CvmJitState *jit, size_t bc_ip, size_t native_off)`
  - `ip_map_lookup` (function, line 68) `static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip)`
  - `func_cache_find` (function, line 80) `static JitFuncEntry *func_cache_find(CvmJitState *jit, uint32_t func_idx)`
  - `func_cache_add` (function, line 87) `static JitFuncEntry *func_cache_add(CvmJitState *jit, uint32_t func_idx,
                        ...`
  - `opcode_total_size` (function, line 104) `static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip)`
  - `emit_stack_push` (function, line 117) `static void emit_stack_push(JitBuf *b)`
  - `emit_stack_pop` (function, line 124) `static void emit_stack_pop(JitBuf *b)`
  - `emit_stack_pop_into` (function, line 130) `static void emit_stack_pop_into(JitBuf *b, int dst)`
  - `emit_stack_push_reg` (function, line 136) `static void emit_stack_push_reg(JitBuf *b, int reg)`
  - `emit_call1` (function, line 146) `static void emit_call1(JitBuf *b, void *fn, int arg)`
  - `emit_call2` (function, line 152) `static void emit_call2(JitBuf *b, void *fn, int a1, int a2)`
  - `emit_call3` (function, line 159) `static void emit_call3(JitBuf *b, void *fn, int a1, int a2, int a3)`
  - `emit_prologue` (function, line 169) `static void emit_prologue(JitBuf *b)`
  - `emit_epilogue` (function, line 231) `static void emit_epilogue(JitBuf *b)`
  - `emit_save_sp` (function, line 252) `static void emit_save_sp(JitBuf *b)`
  - `emit_restore_sp` (function, line 258) `static void emit_restore_sp(JitBuf *b)`
  - `emit_opcode` (function, line 276) `static int emit_opcode(JitCtx *ctx, size_t bc_ip)`
  - `jit_apply_patches_local` (function, line 1123) `static void jit_apply_patches_local(JitBuf *b, const JitPatches *p)`
  - `cvm_jit_compile_func` (function, line 1141) `void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx)`
  - `cvm_jit_compile_module` (function, line 1242) `int cvm_jit_compile_module(CvmState *vm)`
  - `cvm_jit_lookup` (function, line 1258) `void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx)`
  - `find_func_for_ip` (function, line 1271) `static uint32_t find_func_for_ip(const CvmState *vm)`
  - `cvm_jit_exec_one` (function, line 1279) `void cvm_jit_exec_one(CvmState *vm)`
  - `cvm_jit_run` (function, line 1309) `int cvm_jit_run(CvmState *vm)`
  - `cvm_jit_stats` (function, line 1370) `void cvm_jit_stats(const CvmState *vm)`
  - `cvm_jit_dump` (function, line 1381) `void cvm_jit_dump(const CvmState *vm)`
  - `JIT_STATE` (macro, line 30)
  - `EMIT_CMP` (macro, line 527)
  - `EMIT_CMP_SIGNED` (macro, line 548)
  - `EMIT_CMP_UNSIGNED` (macro, line 560)

## cvm2/cvm_jit.h
- Layer: utility
- Language: h
- Symbols:
  - `CVM_JIT_H` (macro, line 15)
  - `JIT_REG_VM` (macro, line 44)
  - `JIT_REG_SLOTS` (macro, line 46)
  - `JIT_REG_SP` (macro, line 47)
  - `JIT_REG_FRAMES` (macro, line 48)
  - `JIT_REG_FRAME` (macro, line 49)
  - `JIT_SCRATCH1` (macro, line 52)
  - `JIT_SCRATCH2` (macro, line 53)
  - `JIT_SCRATCH3` (macro, line 54)
  - `JIT_SCRATCH4` (macro, line 55)
  - `JIT_SCRATCH5` (macro, line 56)
  - `JIT_MAX_FUNCS` (macro, line 92)
  - `JIT_IP_MAP_SIZE` (macro, line 94)

## cvm2/cvm_jit_help.c
- Layer: utility
- Language: c
- Symbols:
  - `cvm_jit_offsets_init` (function, line 21) `void cvm_jit_offsets_init(CvmJitOffsets *o)`
  - `xmal` (function, line 45) `static void *xmal(size_t s)`
  - `xcal` (function, line 51) `static void *xcal(size_t n, size_t s)`
  - `push_frame` (function, line 57) `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...`
  - `pop_frame` (function, line 70) `static void pop_frame(CvmState *vm)`
  - `cur_frame` (function, line 77) `static CvmFrame *cur_frame(CvmState *vm)`
  - `range_valid` (function, line 81) `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)`
  - `mem_valid` (function, line 89) `static int mem_valid(const CvmState *vm, uint64_t a, size_t s)`
  - `heap_alloc` (function, line 101) `static uint64_t heap_alloc(CvmState *vm, size_t s)`
  - `find_native` (function, line 109) `static int find_native(const CvmState *vm, const char *name)`
  - `jit_vp` (function, line 119) `static int jit_vp(CvmState *vm, uint64_t v)`
  - `jit_vo` (function, line 125) `static int jit_vo(CvmState *vm, uint64_t *v)`
  - `cvm_jit_func_enter` (function, line 135) `uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx)`
  - `cvm_jit_func_leave` (function, line 144) `void cvm_jit_func_leave(CvmState *vm)`
  - `cvm_jit_call` (function, line 154) `int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc)`
  - `cvm_jit_ret` (function, line 175) `int cvm_jit_ret(CvmState *vm, uint64_t retval)`
  - `cvm_jit_call_native` (function, line 192) `int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc)`
  - `cvm_jit_memcheck` (function, line 212) `int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size)`
  - `cvm_jit_alloc` (function, line 220) `uint64_t cvm_jit_alloc(CvmState *vm, size_t size)`
  - `cvm_jit_syscall` (function, line 228) `int cvm_jit_syscall(CvmState *vm, uint8_t sn, uint8_t argc)`
  - `cvm_jit_error` (function, line 255) `void cvm_jit_error(CvmState *vm, int error_code)`
  - `CVM_HEAP_ALIGN` (macro, line 15)

## cvm2/cvm_jit_help.h
- Layer: utility
- Language: h
- Symbols:
  - `CVM_JIT_HELP_H` (macro, line 12)

## cvm2/cvm_jit_x86.c
- Layer: utility
- Language: c
- Symbols:
  - `jit_buf_init` (function, line 34) `void jit_buf_init(JitBuf *b, size_t cap)`
  - `jit_buf_free` (function, line 47) `void jit_buf_free(JitBuf *b)`
  - `jit_buf_reset` (function, line 55) `void jit_buf_reset(JitBuf *b)`
  - `jit_buf_failed` (function, line 60) `int jit_buf_failed(const JitBuf *b)`
  - `emit_grow` (function, line 66) `static void emit_grow(JitBuf *b, size_t need)`
  - `emit8` (function, line 83) `void emit8(JitBuf *b, uint8_t v)`
  - `emit16` (function, line 88) `void emit16(JitBuf *b, uint16_t v)`
  - `emit32` (function, line 93) `void emit32(JitBuf *b, uint32_t v)`
  - `emit64` (function, line 98) `void emit64(JitBuf *b, uint64_t v)`
  - `emit_bytes` (function, line 103) `void emit_bytes(JitBuf *b, const void *data, size_t len)`
  - `emit_rex` (function, line 114) `void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b)`
  - `emit_modrm` (function, line 119) `void emit_modrm(JitBuf *b, int mod, int reg, int rm)`
  - `emit_modrm_disp32` (function, line 124) `static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp)`
  - `emit_rex_op_modrm` (function, line 130) `static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm)`
  - `emit_sib` (function, line 137) `static void emit_sib(JitBuf *b, int scale, int index, int base)`
  - `emit_mov_reg_imm64` (function, line 144) `void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm)`
  - `emit_mov_reg_imm32` (function, line 151) `void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm)`
  - `emit_mov_reg_reg` (function, line 164) `void emit_mov_reg_reg(JitBuf *b, int dst, int src)`
  - `emit_mov_reg_mem` (function, line 170) `void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp)`
  - `emit_mov_mem_reg` (function, line 177) `void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src)`
  - `emit_movzx_reg_mem8` (function, line 184) `void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp)`
  - `emit_movzx_reg_mem16` (function, line 191) `void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp)`
  - `emit_movsx_reg_mem32` (function, line 198) `void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp)`
  - `emit_mov32_reg_mem` (function, line 205) `void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp)`
  - `emit_mov32_mem_reg` (function, line 213) `void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src)`
  - `emit_lea_sib` (function, line 221) `void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp)`
  - `emit_mov_reg_sib` (function, line 258) `void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale)`
  - `emit_mov_sib_reg` (function, line 266) `void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src)`
  - `emit_push` (function, line 278) `void emit_push(JitBuf *b, int reg)`
  - `emit_pop` (function, line 284) `void emit_pop(JitBuf *b, int reg)`
  - `emit_add_reg_reg` (function, line 294) `void emit_add_reg_reg(JitBuf *b, int dst, int src)`
  - `emit_add_reg_imm32` (function, line 298) `void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm)`
  - `emit_sub_reg_reg` (function, line 307) `void emit_sub_reg_reg(JitBuf *b, int dst, int src)`
  - `emit_sub_reg_imm32` (function, line 311) `void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm)`
  - `emit_imul_reg_reg` (function, line 319) `void emit_imul_reg_reg(JitBuf *b, int dst, int src)`
  - `emit_idiv_reg` (function, line 326) `void emit_idiv_reg(JitBuf *b, int divisor)`
  - `emit_cqo` (function, line 333) `void emit_cqo(JitBuf *b)`
  - `emit_neg_reg` (function, line 339) `void emit_neg_reg(JitBuf *b, int reg)`
  - `emit_inc_reg` (function, line 346) `void emit_inc_reg(JitBuf *b, int reg)`
  - `emit_dec_reg` (function, line 353) `void emit_dec_reg(JitBuf *b, int reg)`
  - `emit_and_reg_imm32` (function, line 364) `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm)`
  - `emit_and_reg_reg` (function, line 372) `void emit_and_reg_reg(JitBuf *b, int dst, int src)`
  - `emit_or_reg_reg` (function, line 376) `void emit_or_reg_reg(JitBuf *b, int dst, int src)`
  - `emit_xor_reg_reg` (function, line 380) `void emit_xor_reg_reg(JitBuf *b, int dst, int src)`
  - `emit_not_reg` (function, line 384) `void emit_not_reg(JitBuf *b, int reg)`
  - `emit_shl_reg_cl` (function, line 391) `void emit_shl_reg_cl(JitBuf *b, int reg)`
  - `emit_shr_reg_cl` (function, line 398) `void emit_shr_reg_cl(JitBuf *b, int reg)`
  - `emit_sar_reg_cl` (function, line 405) `void emit_sar_reg_cl(JitBuf *b, int reg)`
  - `emit_xor_reg_self` (function, line 412) `void emit_xor_reg_self(JitBuf *b, int reg)`
  - `emit_cmp_reg_reg` (function, line 422) `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg)`
  - `emit_test_reg_reg` (function, line 427) `void emit_test_reg_reg(JitBuf *buf, int a, int breg)`
  - `emit_setcc` (function, line 432) `void emit_setcc(JitBuf *b, int cc, int dst)`
  - `emit_movzx_reg_reg8` (function, line 441) `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src)`
  - `emit_jmp_rel32` (function, line 452) `size_t emit_jmp_rel32(JitBuf *b, int32_t rel)`
  - `emit_jcc_rel32` (function, line 459) `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel)`
  - `emit_jmp_buf` (function, line 467) `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p)`
  - `emit_jcc_buf` (function, line 479) `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p)`
  - `jit_apply_patches` (function, line 492) `void jit_apply_patches(JitBuf *b, const JitPatches *p)`
  - `emit_call_rel32` (function, line 504) `size_t emit_call_rel32(JitBuf *b, int32_t rel)`
  - `emit_call_reg` (function, line 511) `void emit_call_reg(JitBuf *b, int reg)`
  - `emit_ret` (function, line 519) `void emit_ret(JitBuf *b)`
  - `emit_syscall` (function, line 527) `void emit_syscall(JitBuf *b)`
  - `emit_int3` (function, line 532) `void emit_int3(JitBuf *b)`
  - `emit_nop` (function, line 536) `void emit_nop(JitBuf *b)`
  - `emit_call_abs` (function, line 544) `void emit_call_abs(JitBuf *b, void *func, int scratch)`
  - `emit_mov_mem_imm8` (function, line 553) `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm)`
  - `emit_mov_mem_imm32` (function, line 561) `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm)`
  - `JIT_BUF_ALLOC` (macro, line 26)
  - `JIT_BUF_FREE` (macro, line 27)
  - `JIT_BUF_ALLOC` (macro, line 29)
  - `JIT_BUF_FREE` (macro, line 31)
  - `JIT_BUF_FAILED` (macro, line 32)

## cvm2/cvm_jit_x86.h
- Layer: utility
- Language: h
- Symbols:
  - `reg_needs_rex` (function, line 80) `static inline int reg_needs_rex(int r)`
  - `reg_high3` (function, line 81) `static inline int reg_high3(int r)`
  - `CVM_JIT_X86_H` (macro, line 10)
  - `JIT_MAX_PATCHES` (macro, line 52)

## cvm2/cvm_ops.c
- Layer: utility
- Language: c
- Symbols:
  - `cvm_op_info` (function, line 68) `const CvmOpInfo *cvm_op_info(uint8_t opcode)`
  - `cvm_op_name` (function, line 74) `const char *cvm_op_name(uint8_t opcode)`
  - `cvm_ops_r8` (function, line 79) `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out)`
  - `cvm_ops_ru32` (function, line 85) `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off)`
  - `cvm_ops_ri32` (function, line 93) `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off)`
  - `cvm_ops_ri64` (function, line 97) `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off)`
  - `OP_INFOS_LEN` (macro, line 66)

## cvm2/cvm_ops.h
- Layer: utility
- Language: h
- Symbols:
  - `CVM_OPS_H` (macro, line 10)

## cvm2/cvm_val_main.c
- Layer: utility
- Language: c
- Symbols:
  - `val_err` (function, line 55) `static void val_err(ValCtx *ctx, const char *what)`
  - `val_fun_err` (function, line 60) `static void val_fun_err(FuncCtx *fc, const char *what)`
  - `code_of` (function, line 67) `static const uint8_t *code_of(const CvmModuleView *v)`
  - `q_push` (function, line 71) `static void q_push(FuncCtx *fc, size_t off)`
  - `q_pop` (function, line 80) `static size_t q_pop(FuncCtx *fc)`
  - `dr_merge` (function, line 87) `static int dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)`
  - `stack_effect` (function, line 102) `static int stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...`
  - `check_static` (function, line 176) `static int check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)`
  - `analyze_stack` (function, line 354) `static int analyze_stack(FuncCtx *fc)`
  - `check_function` (function, line 427) `static int check_function(FuncCtx *fc, size_t *insn_count)`
  - `cmp_func` (function, line 442) `static int cmp_func(const void *a, const void *b)`
  - `main` (function, line 448) `int main(int argc, char **argv)`
  - `CVM_VAL_MAX_FUNCS` (macro, line 14)
  - `CVM_VAL_MAX_GLOBALS` (macro, line 16)
  - `CVM_VAL_MAX_NATIVES` (macro, line 17)
  - `CVM_VAL_MAX_CODE` (macro, line 18)
  - `CVM_VAL_MAX_LOCALS` (macro, line 19)
  - `CVM_VAL_MAX_ARGS` (macro, line 20)
  - `CVM_VAL_STACK_CAP` (macro, line 25)
  - `CVM_VAL_WIDEN_BOUND` (macro, line 30)
  - `CVM_VAL_MAX_SARGS` (macro, line 31)

## cvm2/cvm_view.c
- Layer: presentation
- Language: c
- Symbols:
  - `rl32` (function, line 8) `static uint32_t rl32(const uint8_t *p)`
  - `rl16` (function, line 13) `static uint32_t rl16(const uint8_t *p)`
  - `cvm_view_strerror` (function, line 17) `const char *cvm_view_strerror(int error_code)`
  - `cvm_view_open` (function, line 28) `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size)`
  - `cvm_view_func` (function, line 71) `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i)`
  - `cvm_view_string` (function, line 77) `const char *cvm_view_string(const CvmModuleView *v, uint32_t off)`
  - `cvm_view_func_name` (function, line 86) `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,
                             ...`
  - `cvm_view_func_region` (function, line 107) `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,
                         size_t *be...`

## cvm2/cvm_view.h
- Layer: presentation
- Language: h
- Symbols:
  - `CVM_VIEW_H` (macro, line 9)

## cvm2/deepseek_bash_20260808_653f26.sh
- Layer: utility
- Language: sh

## cvm2/gen_fib_cvm.c
- Layer: utility
- Language: c
- Symbols:
  - `emit_byte` (function, line 20) `static void emit_byte(uint8_t b)`
  - `emit_u32` (function, line 29) `static void emit_u32(uint32_t v)`
  - `emit_i32` (function, line 36) `static void emit_i32(int32_t v)`
  - `patch_i32` (function, line 38) `static void patch_i32(size_t pos, int32_t val)`
  - `write_le32` (function, line 45) `static void write_le32(uint8_t *p, uint32_t v)`
  - `emit_global_inc` (function, line 52) `static void emit_global_inc(void)`
  - `main` (function, line 63) `int main(int argc, char *argv[])`
  - `FIB_N` (macro, line 12)
  - `EXPECTED_FIB10` (macro, line 14)
  - `EXPECTED_CALLS` (macro, line 15)

## cvm2/gen_minimal.c
- Layer: utility
- Language: c
- Symbols:
  - `emit_byte` (function, line 13) `static void emit_byte(uint8_t b)`
  - `emit_u32` (function, line 21) `static void emit_u32(uint32_t v)`
  - `write_le32` (function, line 25) `static void write_le32(uint8_t *p, uint32_t v)`
  - `main` (function, line 29) `int main(void)`

## cvm2/gen_test.py
- Layer: testing
- Language: py
- Symbols:
  - `emit_byte` (function, line 7) `def emit_byte(b)`
  - `emit_u32` (function, line 10) `def emit_u32(v)`

## cvm2/test.sh
- Layer: testing
- Doc: CVM v2 toolchain suite: interpreter, disassembler, validator (including corrupted-module rejections) and the scripted de
- Language: sh
- Symbols:
  - `check` (function, line 13)
  - `reject` (function, line 24)
