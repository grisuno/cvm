# API

## cvm.c

### cvm_error `static void cvm_error(CVM *vm, const char *fmt, ...)`
- Defined: `cvm.c:12`
- Doc: cvm.c — C Virtual Machine interpreter  #include "cvm.h" #include <stdarg.h> #include <errno.h> /* ----------------------

### op_name `static const char *op_name(uint8_t op)`
- Defined: `cvm.c:21`

### push `static inline void push(CVM *vm, uint64_t v)`
- Defined: `cvm.c:78`
- Doc: case OP_RET: return "RET"; case OP_RET_VOID: return "RET_VOID"; case OP_ALLOC: return "ALLOC"; case OP_FREE: return "FRE

### pop `static inline uint64_t pop(CVM *vm)`
- Defined: `cvm.c:85`

### peek `static inline uint64_t peek(CVM *vm)`
- Defined: `cvm.c:93`

### push_frame `static int push_frame(CVM *vm, CVM_Module *mod, uint16_t func_idx, int argc)`
- Defined: `cvm.c:102`
- Doc: cvm_error(vm, "operand stack underflow"); return 0; } return vm->stack[--vm->sp]; } static inline uint64_t peek(CVM *vm)

### pop_frame `static void pop_frame(CVM *vm, int has_retval)`
- Defined: `cvm.c:141`

### call_native `static void call_native(CVM *vm, uint16_t idx, uint8_t argc)`
- Defined: `cvm.c:175`
- Doc: if (has_retval) push(vm, ret); vm->running = 0; return; } /* restore previous module / code pointer if needed /* (for mu

### cvm_create `CVM *cvm_create(void)`
- Defined: `cvm.c:227`
- Doc: (void)fd; (void)buf; (void)len; } push(vm, 0); return; } /* generic: just pop args and push 0 for (int i = 0; i < argc; 

### cvm_destroy `void cvm_destroy(CVM *vm)`
- Defined: `cvm.c:243`

### cvm_load_module_mem `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name)`
- Defined: `cvm.c:267`
- Doc: free(m->natives); free(m->code); free(m->string_pool); free(m->global_mem); free(m); } free(vm->stack); free(vm->heap); 

### cvm_load_module `int cvm_load_module(CVM *vm, const char *path)`
- Defined: `cvm.c:336`

### interpret `static int interpret(CVM *vm)`
- Defined: `cvm.c:361`
- Doc: if (!buf || fread(buf, 1, (size_t)sz, f) != (size_t)sz) { free(buf); fclose(f); return -1; } fclose(f); int r = cvm_load

### cvm_run `int cvm_run(CVM *vm, const char *entry_name)`
- Defined: `cvm.c:700`
- Doc: vm->running = 0; break; default: cvm_error(vm, "unknown opcode 0x%02x at ip=%u", op, vm->ip - 1); break; } } return 0; }

### cvm_emit_byte `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b)`
- Defined: `cvm.c:743`
- Doc: if (vm->trace) fprintf(stderr, "Finished. instructions = %llu\n", (unsigned long long)vm->instr_count); /* if there is a

### cvm_emit_i16 `void cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v)`
- Defined: `cvm.c:750`

### cvm_emit_u16 `void cvm_emit_u16(uint8_t **buf, size_t *cap, size_t *len, uint16_t v)`
- Defined: `cvm.c:755`

### cvm_emit_i32 `void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v)`
- Defined: `cvm.c:760`

### cvm_emit_i64 `void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v)`
- Defined: `cvm.c:765`

### main `int main(int argc, char **argv)`
- Defined: `cvm.c:775`
- Doc: void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v) { for (int i = 0; i < 4; i++) cvm_emit_byte(buf, c

## cvm2/cvm.c

### xmal `static void *xmal(size_t s)`
- Defined: `cvm2/cvm.c:27`
- Doc: define CVM_DEF_STACK       65536 define CVM_DEF_FRAMES      4096 define CVM_DEF_LOCALS      512 define CVM_DEF_HEAP     

### xcal `static void *xcal(size_t n, size_t s)`
- Defined: `cvm2/cvm.c:33`

### cvm_config_default `CvmConfig cvm_config_default(void)`
- Defined: `cvm2/cvm.c:39`

### cvm_create `CvmState *cvm_create(const CvmConfig *config)`
- Defined: `cvm2/cvm.c:54`

### cvm_destroy `void cvm_destroy(CvmState *vm)`
- Defined: `cvm2/cvm.c:93`

### cvm_strerror `const char *cvm_strerror(int e)`
- Defined: `cvm2/cvm.c:112`

### vp `static int vp(CvmState *vm, uint64_t v)`
- Defined: `cvm2/cvm.c:136`

### vo `static int vo(CvmState *vm, uint64_t *v)`
- Defined: `cvm2/cvm.c:142`

### r8 `static int r8(CvmState *vm, uint8_t *o)`
- Defined: `cvm2/cvm.c:148`

### r32 `static int r32(CvmState *vm, uint32_t *o)`
- Defined: `cvm2/cvm.c:154`

### ri32 `static int ri32(CvmState *vm, int32_t *o)`
- Defined: `cvm2/cvm.c:164`

### r64 `static int r64(CvmState *vm, uint64_t *o)`
- Defined: `cvm2/cvm.c:172`

### push_frame `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...`
- Defined: `cvm2/cvm.c:182`

### pop_frame `static void pop_frame(CvmState *vm)`
- Defined: `cvm2/cvm.c:195`

### cur_frame `static CvmFrame *cur_frame(CvmState *vm)`
- Defined: `cvm2/cvm.c:202`

### range_valid `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)`
- Defined: `cvm2/cvm.c:206`

### mem_valid `static int mem_valid(CvmState *vm, uint64_t a, size_t s)`
- Defined: `cvm2/cvm.c:214`

### heap_alloc `static uint64_t heap_alloc(CvmState *vm, size_t s)`
- Defined: `cvm2/cvm.c:226`

### cvm_heap_alloc `void *cvm_heap_alloc(CvmState *vm, size_t size)`
- Defined: `cvm2/cvm.c:234`

### data_w64 `static void data_w64(CvmState *vm, size_t off, uint64_t v)`
- Defined: `cvm2/cvm.c:238`

### data_r64 `static uint64_t data_r64(CvmState *vm, size_t off)`
- Defined: `cvm2/cvm.c:243`

### cvm_set_args `int cvm_set_args(CvmState *vm, int argc, char **argv)`
- Defined: `cvm2/cvm.c:249`

### cvm_register_native `int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn)`
- Defined: `cvm2/cvm.c:282`

### find_native `static int find_native(CvmState *vm, const char *name)`
- Defined: `cvm2/cvm.c:293`

### native_write `static int64_t native_write(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:304`
- Doc: vm->num_natives++; return CVM_OK; } static int find_native(CvmState *vm, const char *name) { for (size_t i = 0; i < vm->

### native_read `static int64_t native_read(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:310`

### native_exit `static int64_t native_exit(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:316`

### native_abort `static int64_t native_abort(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:323`

### native_putchar `static int64_t native_putchar(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:328`

### native_puts `static int64_t native_puts(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:335`

### native_strlen `static int64_t native_strlen(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:349`

### native_strcmp `static int64_t native_strcmp(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:355`

### native_strncmp `static int64_t native_strncmp(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:361`

### native_strcpy `static int64_t native_strcpy(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:368`

### native_strncpy `static int64_t native_strncpy(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:374`

### native_strchr `static int64_t native_strchr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:381`

### native_strstr `static int64_t native_strstr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:387`

### native_memcpy `static int64_t native_memcpy(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:394`

### native_memmove `static int64_t native_memmove(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:401`

### native_memset `static int64_t native_memset(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:408`

### native_memcmp `static int64_t native_memcmp(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:414`

### native_malloc `static int64_t native_malloc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:421`

### native_free `static int64_t native_free(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:427`

### native_calloc `static int64_t native_calloc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:432`

### native_realloc `static int64_t native_realloc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:441`

### native_atol `static int64_t native_atol(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:450`

### native_strtol `static int64_t native_strtol(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:456`

### vout_write `static void vout_write(Vout *vo, const char *s, size_t n)`
- Defined: `cvm2/cvm.c:471`

### vout_char `static void vout_char(Vout *vo, char c)`
- Defined: `cvm2/cvm.c:483`

### vout_uint `static void vout_uint(Vout *vo, uint64_t v, int base, int upper)`
- Defined: `cvm2/cvm.c:485`

### vformat `static void vformat(Vout *vo, const char *fmt, uint64_t *argv, int argc)`
- Defined: `cvm2/cvm.c:498`

### native_fprintf `static int64_t native_fprintf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:582`

### native_printf `static int64_t native_printf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:592`

### native_sprintf `static int64_t native_sprintf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:601`

### native_snprintf `static int64_t native_snprintf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:612`

### native_fopen `static int64_t native_fopen(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:624`

### native_fclose `static int64_t native_fclose(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:631`

### native_fread `static int64_t native_fread(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:637`

### native_fwrite `static int64_t native_fwrite(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:644`

### native_fseek `static int64_t native_fseek(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:651`

### native_ftell `static int64_t native_ftell(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:657`

### native_rewind `static int64_t native_rewind(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:663`

### native_fputs `static int64_t native_fputs(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:670`

### native_fputc `static int64_t native_fputc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:676`

### native_fgetc `static int64_t native_fgetc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:682`

### native_ungetc `static int64_t native_ungetc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:688`

### native_fflush `static int64_t native_fflush(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:694`

### native_perror `static int64_t native_perror(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:700`

### native_stderr_addr `static int64_t native_stderr_addr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:711`

### native_stdout_addr `static int64_t native_stdout_addr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:716`

### native_stdin_addr `static int64_t native_stdin_addr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:721`

### native_exit_core `static int64_t native_exit_core(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:728`
- Doc: return (int64_t)(uintptr_t)stderr; } static int64_t native_stdout_addr(void *vm, int ac, uint64_t *av) { (void)vm; (void

### register_defaults `static void register_defaults(CvmState *vm)`
- Defined: `cvm2/cvm.c:735`

### rl32 `static uint32_t rl32(const uint8_t *p)`
- Defined: `cvm2/cvm.c:788`
- Doc: cvm_register_native(vm, "fputc", native_fputc); cvm_register_native(vm, "fgetc", native_fgetc); cvm_register_native(vm, 

### decompress_rle `static int decompress_rle(uint8_t *dst, size_t dsz, const uint8_t *src, size_t ssz)`
- Defined: `cvm2/cvm.c:792`

### cvm_free_module `static void cvm_free_module(CvmState *vm)`
- Defined: `cvm2/cvm.c:814`

### cvm_load_module `int cvm_load_module(CvmState *vm, const uint8_t *d, size_t sz)`
- Defined: `cvm2/cvm.c:829`

### cvm_load_module_file `int cvm_load_module_file(CvmState *vm, const char *path)`
- Defined: `cvm2/cvm.c:922`

### cvm_run_loop `static int cvm_run_loop(CvmState *vm)`
- Defined: `cvm2/cvm.c:942`
- Doc: if (sz < 0) { fclose(f); return CVM_ERR_IO; } rewind(f); uint8_t *buf = (uint8_t *)xmal((size_t)sz); size_t rd = fread(b

### cvm_run `int cvm_run(CvmState *vm)`
- Defined: `cvm2/cvm.c:951`

### cvm_continue `int cvm_continue(CvmState *vm)`
- Defined: `cvm2/cvm.c:990`
- Doc: rsp = top - 8; (uint64_t *)(uintptr_t)(top - 8) = 0; data_w64(vm, CVM_DATA_RSP, rsp); data_w64(vm, CVM_DATA_RBP, rsp); d

### cvm_break_set `int cvm_break_set(CvmState *vm, size_t ip)`
- Defined: `cvm2/cvm.c:993`

### cvm_break_clear `int cvm_break_clear(CvmState *vm, size_t ip)`
- Defined: `cvm2/cvm.c:1002`

### cvm_break_clear_all `void cvm_break_clear_all(CvmState *vm)`
- Defined: `cvm2/cvm.c:1013`

### cvm_break_hit `int cvm_break_hit(const CvmState *vm)`
- Defined: `cvm2/cvm.c:1017`

### cvm_profile_begin `int cvm_profile_begin(CvmState *vm)`
- Defined: `cvm2/cvm.c:1023`

### cvm_profile_end `void cvm_profile_end(CvmState *vm)`
- Defined: `cvm2/cvm.c:1033`

### cvm_step `int cvm_step(CvmState *vm)`
- Defined: `cvm2/cvm.c:1039`
- Doc: if (vm->code_size > vm->config.max_profile_code) return CVM_ERR_BOUNDS; if (!vm->ip_counts) vm->ip_counts = (uint32_t *)

### cvm_exit_code `int64_t cvm_exit_code(const CvmState *vm)`
- Defined: `cvm2/cvm.c:1326`

### cvm_instruction_count `uint64_t cvm_instruction_count(const CvmState *vm)`
- Defined: `cvm2/cvm.c:1328`

### main `int main(int argc, char *argv[])`
- Defined: `cvm2/cvm.c:1331`
- Doc: if defined(CVM_STANDALONE) && !defined(CVM_NO_MAIN)

## cvm2/cvm_dbg_main.c

### emit_stdout `static int emit_stdout(void *ctx, const char *line)`
- Defined: `cvm2/cvm_dbg_main.c:28`

### func_display `static const char *func_display(uint32_t fi, char *fb, size_t cap)`
- Defined: `cvm2/cvm_dbg_main.c:35`

### func_of_ip `static int func_of_ip(size_t ip)`
- Defined: `cvm2/cvm_dbg_main.c:39`

### parse_u32 `static int parse_u32(const char *s, uint32_t *out)`
- Defined: `cvm2/cvm_dbg_main.c:50`

### report_run `static void report_run(int rc)`
- Defined: `cvm2/cvm_dbg_main.c:58`

### cmd_list `static void cmd_list(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:70`

### cmd_break `static void cmd_break(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:97`

### cmd_delete `static void cmd_delete(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:132`

### cmd_step `static void cmd_step(void)`
- Defined: `cvm2/cvm_dbg_main.c:151`

### cmd_next `static void cmd_next(void)`
- Defined: `cvm2/cvm_dbg_main.c:165`

### cmd_run `static void cmd_run(void)`
- Defined: `cvm2/cvm_dbg_main.c:183`

### cmd_bt `static void cmd_bt(void)`
- Defined: `cvm2/cvm_dbg_main.c:193`

### cmd_stack `static void cmd_stack(void)`
- Defined: `cvm2/cvm_dbg_main.c:205`

### cmd_locals `static void cmd_locals(void)`
- Defined: `cvm2/cvm_dbg_main.c:212`

### cmd_info `static void cmd_info(void)`
- Defined: `cvm2/cvm_dbg_main.c:224`

### cmd_profile `static void cmd_profile(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:240`

### cmd_help `static void cmd_help(void)`
- Defined: `cvm2/cvm_dbg_main.c:303`

### dispatch `static void dispatch(char *line)`
- Defined: `cvm2/cvm_dbg_main.c:309`

### main `int main(int argc, char **argv)`
- Defined: `cvm2/cvm_dbg_main.c:336`

## cvm2/cvm_dis.c

### putc_str `static void putc_str(char *buf, size_t cap, size_t *n, char c)`
- Defined: `cvm2/cvm_dis.c:12`
- Doc: define CVM_DIS_LINE_MAX 160

### puts_str `static void puts_str(char *buf, size_t cap, size_t *n, const char *s)`
- Defined: `cvm2/cvm_dis.c:16`

### put_hex `static void put_hex(char *buf, size_t cap, size_t *n, uint64_t v, int digits)`
- Defined: `cvm2/cvm_dis.c:20`

### put_dec `static void put_dec(char *buf, size_t cap, size_t *n, int64_t v)`
- Defined: `cvm2/cvm_dis.c:34`

### pad_name `static void pad_name(char *buf, size_t cap, size_t *n, const char *name)`
- Defined: `cvm2/cvm_dis.c:48`

### cvm_dis_line `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end,
                 char *buf, size...`
- Defined: `cvm2/cvm_dis.c:55`

### cvm_dis_function `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end,
                     CvmDi...`
- Defined: `cvm2/cvm_dis.c:152`

### cvm_dis_module `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx)`
- Defined: `cvm2/cvm_dis.c:172`

## cvm2/cvm_dis_main.c

### print_line `static int print_line(void *ctx, const char *line)`
- Defined: `cvm2/cvm_dis_main.c:10`
- Doc: @file cvm_dis_main.c @brief Host front-end: cvm-dis <module.cvm> renders the module as text. @license GPL-2.0-or-later  

### main `int main(int argc, char **argv)`
- Defined: `cvm2/cvm_dis_main.c:17`

## cvm2/cvm_jit.c

### cvm_jit_create `CvmJitState *cvm_jit_create(void)`
- Defined: `cvm2/cvm_jit.c:35`
- Doc: Callee-saved: rbx, r12-r15, rbp  #include "cvm_jit.h" #include "cvm_ops.h" #include <stdio.h> #include <stdlib.h> #inclu

### cvm_jit_destroy `void cvm_jit_destroy(CvmJitState *jit)`
- Defined: `cvm2/cvm_jit.c:47`

### ip_map_clear `static void ip_map_clear(CvmJitState *jit)`
- Defined: `cvm2/cvm_jit.c:57`
- Doc: jit->warm_threshold = 1; jit->hot_threshold = 1000; return jit; } void cvm_jit_destroy(CvmJitState *jit) { if (!jit) ret

### ip_map_add `static void ip_map_add(CvmJitState *jit, size_t bc_ip, size_t native_off)`
- Defined: `cvm2/cvm_jit.c:61`

### ip_map_lookup `static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip)`
- Defined: `cvm2/cvm_jit.c:68`

### func_cache_find `static JitFuncEntry *func_cache_find(CvmJitState *jit, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit.c:80`
- Doc: jit->ip_map_count++; } static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip) { for (size_t i = 0; i < jit->i

### func_cache_add `static JitFuncEntry *func_cache_add(CvmJitState *jit, uint32_t func_idx,
                        ...`
- Defined: `cvm2/cvm_jit.c:87`

### opcode_total_size `static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip)`
- Defined: `cvm2/cvm_jit.c:104`
- Doc: JitTier tier) { if (jit->num_funcs_compiled >= JIT_MAX_FUNCS) return NULL; JitFuncEntry *e = &jit->func_cache[jit->num_f

### emit_stack_push `static void emit_stack_push(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:117`
- Doc: /* ------------------------------------------------------------------ static size_t opcode_total_size(const uint8_t *cod

### emit_stack_pop `static void emit_stack_pop(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:124`
- Doc: } /* ------------------------------------------------------------------ /*  Emit helpers: operand stack operations /* --

### emit_stack_pop_into `static void emit_stack_pop_into(JitBuf *b, int dst)`
- Defined: `cvm2/cvm_jit.c:130`
- Doc: /* Push rax onto the operand stack: slots[sp] = rax; sp++ static void emit_stack_push(JitBuf *b) { /* mov [r12 + r13*8],

### emit_stack_push_reg `static void emit_stack_push_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit.c:136`
- Doc: /* Pop from operand stack into rax: sp--; rax = slots[sp] static void emit_stack_pop(JitBuf *b) { emit_dec_reg(b, JIT_RE

### emit_call1 `static void emit_call1(JitBuf *b, void *fn, int arg)`
- Defined: `cvm2/cvm_jit.c:146`
- Doc: emit_mov_reg_sib(b, dst, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Push a register onto the operand stack static void emit_sta

### emit_call2 `static void emit_call2(JitBuf *b, void *fn, int a1, int a2)`
- Defined: `cvm2/cvm_jit.c:152`
- Doc: emit_inc_reg(b, JIT_REG_SP); } /* ------------------------------------------------------------------ /*  Emit helpers: C

### emit_call3 `static void emit_call3(JitBuf *b, void *fn, int a1, int a2, int a3)`
- Defined: `cvm2/cvm_jit.c:159`
- Doc: /* Call a C function with 1 arg (rdi).  Clobbers rax, rcx, rdx, rsi, rdi, r8-r11. static void emit_call1(JitBuf *b, void

### emit_prologue `static void emit_prologue(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:169`
- Doc: emit_call_abs(b, fn, X10); } /* Call a C function with 3 args (rdi, rsi, rdx). static void emit_call3(JitBuf *b, void *f

### emit_epilogue `static void emit_epilogue(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:231`

### emit_save_sp `static void emit_save_sp(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:252`
- Doc: emit_pop(b, JIT_REG_SP);      /* r13 emit_pop(b, JIT_REG_SLOTS);   /* r12 emit_pop(b, JIT_REG_FRAME);   /* rbx emit_pop(

### emit_restore_sp `static void emit_restore_sp(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:258`
- Doc: emit_ret(b); } /* ------------------------------------------------------------------ /*  Emit: save/restore VM state (fo

### emit_opcode `static int emit_opcode(JitCtx *ctx, size_t bc_ip)`
- Defined: `cvm2/cvm_jit.c:276`

### jit_apply_patches_local `static void jit_apply_patches_local(JitBuf *b, const JitPatches *p)`
- Defined: `cvm2/cvm_jit.c:1123`
- Doc: emit_mov_reg_reg(b, XDI, JIT_REG_VM); emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_OPCODE); emit_call_abs(b, (void *)(uintptr_

### cvm_jit_compile_func `void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit.c:1141`

### cvm_jit_compile_module `int cvm_jit_compile_module(CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1242`
- Doc: memcpy(jit->buf.code + off, &r, 4); } if (jit->buf.failed) return NULL; size_t native_size = jit->buf.size - native_star

### cvm_jit_lookup `void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit.c:1258`
- Doc: if (!vm->jit || !JIT_STATE(vm)->enabled) return CVM_OK; ip_map_clear(vm->jit); for (uint32_t i = 0; i < vm->num_funcs; i

### find_func_for_ip `static uint32_t find_func_for_ip(const CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1271`
- Doc: /* ------------------------------------------------------------------ void *cvm_jit_lookup(CvmState *vm, uint32_t func_i

### cvm_jit_exec_one `void cvm_jit_exec_one(CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1279`

### cvm_jit_run `int cvm_jit_run(CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1309`

### cvm_jit_stats `void cvm_jit_stats(const CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1370`
- Doc: } } /* Dispatch loop while (vm->running) { cvm_jit_exec_one(vm); } return CVM_OK; } /* ---------------------------------

### cvm_jit_dump `void cvm_jit_dump(const CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1381`

## cvm2/cvm_jit_help.c

### cvm_jit_offsets_init `void cvm_jit_offsets_init(CvmJitOffsets *o)`
- Defined: `cvm2/cvm_jit_help.c:21`
- Doc: implement the same semantics as the interpreter's switch cases, but are standalone C functions with a clean ABI.  #inclu

### xmal `static void *xmal(size_t s)`
- Defined: `cvm2/cvm_jit_help.c:45`
- Doc: o->code_size            = offsetof(CvmState, code_size); o->ip                   = offsetof(CvmState, ip); o->running   

### xcal `static void *xcal(size_t n, size_t s)`
- Defined: `cvm2/cvm_jit_help.c:51`

### push_frame `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...`
- Defined: `cvm2/cvm_jit_help.c:57`

### pop_frame `static void pop_frame(CvmState *vm)`
- Defined: `cvm2/cvm_jit_help.c:70`

### cur_frame `static CvmFrame *cur_frame(CvmState *vm)`
- Defined: `cvm2/cvm_jit_help.c:77`

### range_valid `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)`
- Defined: `cvm2/cvm_jit_help.c:81`

### mem_valid `static int mem_valid(const CvmState *vm, uint64_t a, size_t s)`
- Defined: `cvm2/cvm_jit_help.c:89`

### heap_alloc `static uint64_t heap_alloc(CvmState *vm, size_t s)`
- Defined: `cvm2/cvm_jit_help.c:101`

### find_native `static int find_native(const CvmState *vm, const char *name)`
- Defined: `cvm2/cvm_jit_help.c:109`

### jit_vp `static int jit_vp(CvmState *vm, uint64_t v)`
- Defined: `cvm2/cvm_jit_help.c:119`
- Doc: uint64_t a = (uint64_t)(uintptr_t)(vm->heap + vm->heap_used); vm->heap_used += al; return a; } static int find_native(co

### jit_vo `static int jit_vo(CvmState *vm, uint64_t *v)`
- Defined: `cvm2/cvm_jit_help.c:125`

### cvm_jit_func_enter `uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit_help.c:135`
- Doc: if (vm->sp >= vm->capacity) return CVM_ERR_STACK_OVER; vm->slots[vm->sp++] = v; return CVM_OK; } static int jit_vo(CvmSt

### cvm_jit_func_leave `void cvm_jit_func_leave(CvmState *vm)`
- Defined: `cvm2/cvm_jit_help.c:144`

### cvm_jit_call `int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc)`
- Defined: `cvm2/cvm_jit_help.c:154`
- Doc: Nothing to do in the general case; the JIT epilogue handles * register restoration.  This exists for symmetry and future

### cvm_jit_ret `int cvm_jit_ret(CvmState *vm, uint64_t retval)`
- Defined: `cvm2/cvm_jit_help.c:175`
- Doc: CvmFrame *f = cur_frame(vm); for (int i = (int)argc - 1; i >= 0; i--) { uint64_t a; rc = jit_vo(vm, &a); if (rc) return 

### cvm_jit_call_native `int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc)`
- Defined: `cvm2/cvm_jit_help.c:192`
- Doc: if (f && f->return_ip != 0) { size_t ret_ip = f->return_ip; pop_frame(vm); vm->ip = ret_ip; return jit_vp(vm, retval); }

### cvm_jit_memcheck `int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size)`
- Defined: `cvm2/cvm_jit_help.c:212`
- Doc: uint64_t args[CVM_MAX_NARGS]; for (int i = (int)argc - 1; i >= 0; i--) { int rc = jit_vo(vm, &args[i]); if (rc) return r

### cvm_jit_alloc `uint64_t cvm_jit_alloc(CvmState *vm, size_t size)`
- Defined: `cvm2/cvm_jit_help.c:220`
- Doc: return CVM_OK; } /* ------------------------------------------------------------------ /*  Memory check /* -------------

### cvm_jit_syscall `int cvm_jit_syscall(CvmState *vm, uint8_t sn, uint8_t argc)`
- Defined: `cvm2/cvm_jit_help.c:228`
- Doc: return mem_valid(vm, addr, size); } /* ------------------------------------------------------------------ /*  ALLOC /* -

### cvm_jit_error `void cvm_jit_error(CvmState *vm, int error_code)`
- Defined: `cvm2/cvm_jit_help.c:255`
- Doc: } #ifdef CVM_STANDALONE else if (sn == CVM_SYS_WRITE) res = (int64_t)write((int)args[0], (const void *)(uintptr_t)args[1

## cvm2/cvm_jit_x86.c

### jit_buf_init `void jit_buf_init(JitBuf *b, size_t cap)`
- Defined: `cvm2/cvm_jit_x86.c:34`
- Doc: define JIT_BUF_FREE(p, sz)    munmap((p), (sz)) define JIT_BUF_FAILED         MAP_FAILED endif

### jit_buf_free `void jit_buf_free(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:47`

### jit_buf_reset `void jit_buf_reset(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:55`

### jit_buf_failed `int jit_buf_failed(const JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:60`

### emit_grow `static void emit_grow(JitBuf *b, size_t need)`
- Defined: `cvm2/cvm_jit_x86.c:66`
- Doc: b->size = 0; b->capacity = 0; } void jit_buf_reset(JitBuf *b) { b->size = 0; b->failed = 0; } int jit_buf_failed(const J

### emit8 `void emit8(JitBuf *b, uint8_t v)`
- Defined: `cvm2/cvm_jit_x86.c:83`

### emit16 `void emit16(JitBuf *b, uint16_t v)`
- Defined: `cvm2/cvm_jit_x86.c:88`

### emit32 `void emit32(JitBuf *b, uint32_t v)`
- Defined: `cvm2/cvm_jit_x86.c:93`

### emit64 `void emit64(JitBuf *b, uint64_t v)`
- Defined: `cvm2/cvm_jit_x86.c:98`

### emit_bytes `void emit_bytes(JitBuf *b, const void *data, size_t len)`
- Defined: `cvm2/cvm_jit_x86.c:103`

### emit_rex `void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b)`
- Defined: `cvm2/cvm_jit_x86.c:114`
- Doc: emit_grow(b, 8); if (!b->failed) { memcpy(b->code + b->size, &v, 8); b->size += 8; } } void emit_bytes(JitBuf *b, const 

### emit_modrm `void emit_modrm(JitBuf *b, int mod, int reg, int rm)`
- Defined: `cvm2/cvm_jit_x86.c:119`
- Doc: emit_grow(b, len); if (!b->failed) { memcpy(b->code + b->size, data, len); b->size += len; } } /* ----------------------

### emit_modrm_disp32 `static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:124`
- Doc: /*  Internal encoding helpers /* ------------------------------------------------------------------ /* REX prefix: 0100 

### emit_rex_op_modrm `static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm)`
- Defined: `cvm2/cvm_jit_x86.c:130`
- Doc: } /* ModRM byte void emit_modrm(JitBuf *b, int mod, int reg, int rm) { emit8(b, (uint8_t)((mod << 6) | ((reg & 7) << 3) 

### emit_sib `static void emit_sib(JitBuf *b, int scale, int index, int base)`
- Defined: `cvm2/cvm_jit_x86.c:137`
- Doc: /* ModRM + disp32 static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp) { emit_modrm(b, 2, reg, rm); e

### emit_mov_reg_imm64 `void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:144`
- Doc: static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm) { emit_rex(b, 1, reg_high3(reg), 0, reg_high3(rm)

### emit_mov_reg_imm32 `void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:151`

### emit_mov_reg_reg `void emit_mov_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:164`

### emit_mov_reg_mem `void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:170`

### emit_mov_mem_reg `void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src)`
- Defined: `cvm2/cvm_jit_x86.c:177`

### emit_movzx_reg_mem8 `void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:184`

### emit_movzx_reg_mem16 `void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:191`

### emit_movsx_reg_mem32 `void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:198`

### emit_mov32_reg_mem `void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:205`

### emit_mov32_mem_reg `void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src)`
- Defined: `cvm2/cvm_jit_x86.c:213`

### emit_lea_sib `void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:221`

### emit_mov_reg_sib `void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale)`
- Defined: `cvm2/cvm_jit_x86.c:258`

### emit_mov_sib_reg `void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src)`
- Defined: `cvm2/cvm_jit_x86.c:266`

### emit_push `void emit_push(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:278`
- Doc: emit_sib(b, scale, index, base); } void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src) { /* REX.W 

### emit_pop `void emit_pop(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:284`

### emit_add_reg_reg `void emit_add_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:294`
- Doc: if (reg_needs_rex(reg)) emit8(b, 0x41); /* REX.B=1 emit8(b, (uint8_t)(0x50 + (reg & 7))); } void emit_pop(JitBuf *b, int

### emit_add_reg_imm32 `void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:298`

### emit_sub_reg_reg `void emit_sub_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:307`

### emit_sub_reg_imm32 `void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:311`

### emit_imul_reg_reg `void emit_imul_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:319`

### emit_idiv_reg `void emit_idiv_reg(JitBuf *b, int divisor)`
- Defined: `cvm2/cvm_jit_x86.c:326`

### emit_cqo `void emit_cqo(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:333`

### emit_neg_reg `void emit_neg_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:339`

### emit_inc_reg `void emit_inc_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:346`

### emit_dec_reg `void emit_dec_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:353`

### emit_and_reg_imm32 `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:364`
- Doc: emit8(b, 0xFF); emit_modrm(b, 3, 0, reg); } void emit_dec_reg(JitBuf *b, int reg) { /* REX.W + FF /1 r/m64 emit_rex(b, 1

### emit_and_reg_reg `void emit_and_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:372`

### emit_or_reg_reg `void emit_or_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:376`

### emit_xor_reg_reg `void emit_xor_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:380`

### emit_not_reg `void emit_not_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:384`

### emit_shl_reg_cl `void emit_shl_reg_cl(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:391`

### emit_shr_reg_cl `void emit_shr_reg_cl(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:398`

### emit_sar_reg_cl `void emit_sar_reg_cl(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:405`

### emit_xor_reg_self `void emit_xor_reg_self(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:412`

### emit_cmp_reg_reg `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg)`
- Defined: `cvm2/cvm_jit_x86.c:422`
- Doc: emit_rex(b, 1, 0, 0, reg_high3(reg)); emit8(b, 0xD3); emit_modrm(b, 3, 7, reg); } void emit_xor_reg_self(JitBuf *b, int 

### emit_test_reg_reg `void emit_test_reg_reg(JitBuf *buf, int a, int breg)`
- Defined: `cvm2/cvm_jit_x86.c:427`

### emit_setcc `void emit_setcc(JitBuf *b, int cc, int dst)`
- Defined: `cvm2/cvm_jit_x86.c:432`

### emit_movzx_reg_reg8 `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:441`

### emit_jmp_rel32 `size_t emit_jmp_rel32(JitBuf *b, int32_t rel)`
- Defined: `cvm2/cvm_jit_x86.c:452`
- Doc: emit8(b, (uint8_t)(0x90 + cc)); emit_modrm(b, 3, 0, dst); } void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src) { /*

### emit_jcc_rel32 `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel)`
- Defined: `cvm2/cvm_jit_x86.c:459`

### emit_jmp_buf `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p)`
- Defined: `cvm2/cvm_jit_x86.c:467`

### emit_jcc_buf `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p)`
- Defined: `cvm2/cvm_jit_x86.c:479`

### jit_apply_patches `void jit_apply_patches(JitBuf *b, const JitPatches *p)`
- Defined: `cvm2/cvm_jit_x86.c:492`

### emit_call_rel32 `size_t emit_call_rel32(JitBuf *b, int32_t rel)`
- Defined: `cvm2/cvm_jit_x86.c:504`

### emit_call_reg `void emit_call_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:511`

### emit_ret `void emit_ret(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:519`

### emit_syscall `void emit_syscall(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:527`
- Doc: /* FF /2 r/m64 -- CALL r/m64 if (reg_needs_rex(reg)) emit8(b, 0x41); emit8(b, 0xFF); emit_modrm(b, 3, 2, reg); } void em

### emit_int3 `void emit_int3(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:532`

### emit_nop `void emit_nop(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:536`

### emit_call_abs `void emit_call_abs(JitBuf *b, void *func, int scratch)`
- Defined: `cvm2/cvm_jit_x86.c:544`
- Doc: emit8(b, 0x05); } void emit_int3(JitBuf *b) { emit8(b, 0xCC); } void emit_nop(JitBuf *b) { emit8(b, 0x90); } /* --------

### emit_mov_mem_imm8 `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:553`
- Doc: } /* ------------------------------------------------------------------ /*  Absolute call to C function /* -------------

### emit_mov_mem_imm32 `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:561`

## cvm2/cvm_jit_x86.h

### reg_needs_rex `static inline int reg_needs_rex(int r)`
- Defined: `cvm2/cvm_jit_x86.h:80`
- Doc: int   jit_buf_failed(const JitBuf *b); /* ------------------------------------------------------------------ /*  Byte em

### reg_high3 `static inline int reg_high3(int r)`
- Defined: `cvm2/cvm_jit_x86.h:81`

## cvm2/cvm_ops.c

### cvm_op_info `const CvmOpInfo *cvm_op_info(uint8_t opcode)`
- Defined: `cvm2/cvm_ops.c:68`
- Doc: define OP_INFOS_LEN (sizeof(op_infos) / sizeof(op_infos[0]))

### cvm_op_name `const char *cvm_op_name(uint8_t opcode)`
- Defined: `cvm2/cvm_ops.c:74`

### cvm_ops_r8 `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out)`
- Defined: `cvm2/cvm_ops.c:79`

### cvm_ops_ru32 `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off)`
- Defined: `cvm2/cvm_ops.c:85`

### cvm_ops_ri32 `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off)`
- Defined: `cvm2/cvm_ops.c:93`

### cvm_ops_ri64 `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off)`
- Defined: `cvm2/cvm_ops.c:97`

## cvm2/cvm_val_main.c

### val_err `static void val_err(ValCtx *ctx, const char *what)`
- Defined: `cvm2/cvm_val_main.c:55`

### val_fun_err `static void val_fun_err(FuncCtx *fc, const char *what)`
- Defined: `cvm2/cvm_val_main.c:60`

### code_of `static const uint8_t *code_of(const CvmModuleView *v)`
- Defined: `cvm2/cvm_val_main.c:67`

### q_push `static void q_push(FuncCtx *fc, size_t off)`
- Defined: `cvm2/cvm_val_main.c:71`

### q_pop `static size_t q_pop(FuncCtx *fc)`
- Defined: `cvm2/cvm_val_main.c:80`

### dr_merge `static int dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)`
- Defined: `cvm2/cvm_val_main.c:87`

### stack_effect `static int stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...`
- Defined: `cvm2/cvm_val_main.c:102`

### check_static `static int check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)`
- Defined: `cvm2/cvm_val_main.c:176`

### analyze_stack `static int analyze_stack(FuncCtx *fc)`
- Defined: `cvm2/cvm_val_main.c:354`
- Doc: Abstract-interpretation stack balance: each instruction start carries a [lo,hi] interval of possible stack depths; a req

### check_function `static int check_function(FuncCtx *fc, size_t *insn_count)`
- Defined: `cvm2/cvm_val_main.c:427`

### cmp_func `static int cmp_func(const void *a, const void *b)`
- Defined: `cvm2/cvm_val_main.c:442`

### main `int main(int argc, char **argv)`
- Defined: `cvm2/cvm_val_main.c:448`

## cvm2/cvm_view.c

### rl32 `static uint32_t rl32(const uint8_t *p)`
- Defined: `cvm2/cvm_view.c:8`
- Doc: @file cvm_view.c @brief Module view parsing with fail-closed extent validation. @license GPL-2.0-or-later  include "cvm_

### rl16 `static uint32_t rl16(const uint8_t *p)`
- Defined: `cvm2/cvm_view.c:13`

### cvm_view_strerror `const char *cvm_view_strerror(int error_code)`
- Defined: `cvm2/cvm_view.c:17`

### cvm_view_open `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size)`
- Defined: `cvm2/cvm_view.c:28`

### cvm_view_func `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i)`
- Defined: `cvm2/cvm_view.c:71`

### cvm_view_string `const char *cvm_view_string(const CvmModuleView *v, uint32_t off)`
- Defined: `cvm2/cvm_view.c:77`

### cvm_view_func_name `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,
                             ...`
- Defined: `cvm2/cvm_view.c:86`

### cvm_view_func_region `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,
                         size_t *be...`
- Defined: `cvm2/cvm_view.c:107`

## cvm2/gen_fib_cvm.c

### emit_byte `static void emit_byte(uint8_t b)`
- Defined: `cvm2/gen_fib_cvm.c:20`

### emit_u32 `static void emit_u32(uint32_t v)`
- Defined: `cvm2/gen_fib_cvm.c:29`

### emit_i32 `static void emit_i32(int32_t v)`
- Defined: `cvm2/gen_fib_cvm.c:36`

### patch_i32 `static void patch_i32(size_t pos, int32_t val)`
- Defined: `cvm2/gen_fib_cvm.c:38`

### write_le32 `static void write_le32(uint8_t *p, uint32_t v)`
- Defined: `cvm2/gen_fib_cvm.c:45`

### emit_global_inc `static void emit_global_inc(void)`
- Defined: `cvm2/gen_fib_cvm.c:52`

### main `int main(int argc, char *argv[])`
- Defined: `cvm2/gen_fib_cvm.c:63`

## cvm2/gen_minimal.c

### emit_byte `static void emit_byte(uint8_t b)`
- Defined: `cvm2/gen_minimal.c:13`

### emit_u32 `static void emit_u32(uint32_t v)`
- Defined: `cvm2/gen_minimal.c:21`

### write_le32 `static void write_le32(uint8_t *p, uint32_t v)`
- Defined: `cvm2/gen_minimal.c:25`

### main `int main(void)`
- Defined: `cvm2/gen_minimal.c:29`

## cvm2/gen_test.py

### emit_byte `def emit_byte(b)`
- Defined: `cvm2/gen_test.py:7`

### emit_u32 `def emit_u32(v)`
- Defined: `cvm2/gen_test.py:10`

## cvm2/test.sh

### check
- Defined: `cvm2/test.sh:13`

### reject
- Defined: `cvm2/test.sh:24`

## gen_fib_cvm.c

### add_string `static uint32_t add_string(const char *s)`
- Defined: `gen_fib_cvm.c:23`

### main `int main(void)`
- Defined: `gen_fib_cvm.c:35`
