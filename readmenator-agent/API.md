# API

## cvm.c

### cvm_error (function) `static void cvm_error(CVM *vm, const char *fmt, ...)`
- Defined: `cvm.c:12`
- Doc: cvm.c — C Virtual Machine interpreter  #include "cvm.h" #include <stdarg.h> #include <errno.h> /* ----------------------
- Depends on: `cvm.h`

### op_name (function) `static const char *op_name(uint8_t op)`
- Defined: `cvm.c:22`
- Depends on: `cvm.h`

### push (function) `static inline void push(CVM *vm, uint64_t v)`
- Defined: `cvm.c:78`
- Doc: case OP_RET: return "RET"; case OP_RET_VOID: return "RET_VOID"; case OP_ALLOC: return "ALLOC"; case OP_FREE: return "FRE
- Depends on: `cvm.h`

### pop (function) `static inline uint64_t pop(CVM *vm)`
- Defined: `cvm.c:86`
- Depends on: `cvm.h`

### peek (function) `static inline uint64_t peek(CVM *vm)`
- Defined: `cvm.c:94`
- Depends on: `cvm.h`

### push_frame (function) `static int push_frame(CVM *vm, CVM_Module *mod, uint16_t func_idx, int argc)`
- Defined: `cvm.c:102`
- Doc: cvm_error(vm, "operand stack underflow"); return 0; } return vm->stack[--vm->sp]; } static inline uint64_t peek(CVM *vm)
- Depends on: `cvm.h`

### pop_frame (function) `static void pop_frame(CVM *vm, int has_retval)`
- Defined: `cvm.c:142`
- Depends on: `cvm.h`

### call_native (function) `static void call_native(CVM *vm, uint16_t idx, uint8_t argc)`
- Defined: `cvm.c:175`
- Doc: if (has_retval) push(vm, ret); vm->running = 0; return; } /* restore previous module / code pointer if needed /* (for mu
- Depends on: `cvm.h`

### cvm_create (function) `CVM *cvm_create(void)`
- Defined: `cvm.c:227`
- Doc: (void)fd; (void)buf; (void)len; } push(vm, 0); return; } /* generic: just pop args and push 0 for (int i = 0; i < argc; 
- Depends on: `cvm.h`

### cvm_destroy (function) `void cvm_destroy(CVM *vm)`
- Defined: `cvm.c:244`
- Depends on: `cvm.h`

### cvm_load_module_mem (function) `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name)`
- Defined: `cvm.c:267`
- Doc: free(m->natives); free(m->code); free(m->string_pool); free(m->global_mem); free(m); } free(vm->stack); free(vm->heap); 
- Depends on: `cvm.h`

### cvm_load_module (function) `int cvm_load_module(CVM *vm, const char *path)`
- Defined: `cvm.c:337`
- Depends on: `cvm.h`

### interpret (function) `static int interpret(CVM *vm)`
- Defined: `cvm.c:361`
- Doc: if (!buf || fread(buf, 1, (size_t)sz, f) != (size_t)sz) { free(buf); fclose(f); return -1; } fclose(f); int r = cvm_load
- Depends on: `cvm.h`

### cvm_run (function) `int cvm_run(CVM *vm, const char *entry_name)`
- Defined: `cvm.c:700`
- Doc: vm->running = 0; break; default: cvm_error(vm, "unknown opcode 0x%02x at ip=%u", op, vm->ip - 1); break; } } return 0; }
- Depends on: `cvm.h`

### cvm_emit_byte (function) `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b)`
- Defined: `cvm.c:743`
- Doc: if (vm->trace) fprintf(stderr, "Finished. instructions = %llu\n", (unsigned long long)vm->instr_count); /* if there is a
- Depends on: `cvm.h`

### cvm_emit_i16 (function) `void cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v)`
- Defined: `cvm.c:751`
- Depends on: `cvm.h`

### cvm_emit_u16 (function) `void cvm_emit_u16(uint8_t **buf, size_t *cap, size_t *len, uint16_t v)`
- Defined: `cvm.c:756`
- Depends on: `cvm.h`

### cvm_emit_i32 (function) `void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v)`
- Defined: `cvm.c:761`
- Depends on: `cvm.h`

### cvm_emit_i64 (function) `void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v)`
- Defined: `cvm.c:766`
- Depends on: `cvm.h`

### main (function) `int main(int argc, char **argv)`
- Defined: `cvm.c:775`
- Doc: void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v) { for (int i = 0; i < 4; i++) cvm_emit_byte(buf, c
- Depends on: `cvm.h`

## cvm.h

### cvm_create (function) `CVM *cvm_create(void);`
- Defined: `cvm.h:215`
- Doc: /* Heap (bump allocator for simplicity) uint8_t    *heap; size_t      heap_used; size_t      heap_size; /* Stats / debug
- Imported by: `cvm.c`, `gen_fib_cvm.c`

### cvm_destroy (function) `void cvm_destroy(CVM *vm);`
- Defined: `cvm.h:216`
- Imported by: `cvm.c`, `gen_fib_cvm.c`

### cvm_load_module (function) `int cvm_load_module(CVM *vm, const char *path);`
- Defined: `cvm.h:217`
- Imported by: `cvm.c`, `gen_fib_cvm.c`

### cvm_load_module_mem (function) `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);`
- Defined: `cvm.h:218`
- Imported by: `cvm.c`, `gen_fib_cvm.c`

### cvm_run (function) `int cvm_run(CVM *vm, const char *entry_name);`
- Defined: `cvm.h:219`
- Imported by: `cvm.c`, `gen_fib_cvm.c`

### cvm_call (function) `int cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);`
- Defined: `cvm.h:220`
- Imported by: `cvm.c`, `gen_fib_cvm.c`

### cvm_emit_byte (function) `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);`
- Defined: `cvm.h:223`
- Doc: int         trace; } CVM; /* ------------------------------------------------------------------ /*  Public API /* ------
- Imported by: `cvm.c`, `gen_fib_cvm.c`

### cvm_emit_i16 (function) `void cvm_emit_i16 (uint8_t **buf, size_t *cap, size_t *len, int16_t v);`
- Defined: `cvm.h:224`
- Imported by: `cvm.c`, `gen_fib_cvm.c`

### cvm_emit_i32 (function) `void cvm_emit_i32 (uint8_t **buf, size_t *cap, size_t *len, int32_t v);`
- Defined: `cvm.h:225`
- Imported by: `cvm.c`, `gen_fib_cvm.c`

### cvm_emit_i64 (function) `void cvm_emit_i64 (uint8_t **buf, size_t *cap, size_t *len, int64_t v);`
- Defined: `cvm.h:226`
- Imported by: `cvm.c`, `gen_fib_cvm.c`

### cvm_emit_u16 (function) `void cvm_emit_u16 (uint8_t **buf, size_t *cap, size_t *len, uint16_t v);`
- Defined: `cvm.h:227`
- Imported by: `cvm.c`, `gen_fib_cvm.c`

## cvm2/cvm.c

### xmal (function) `static void *xmal(size_t s)`
- Defined: `cvm2/cvm.c:28`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### xcal (function) `static void *xcal(size_t n, size_t s)`
- Defined: `cvm2/cvm.c:34`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_config_default (function) `CvmConfig cvm_config_default(void)`
- Defined: `cvm2/cvm.c:40`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_create (function) `CvmState *cvm_create(const CvmConfig *config)`
- Defined: `cvm2/cvm.c:55`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_destroy (function) `void cvm_destroy(CvmState *vm)`
- Defined: `cvm2/cvm.c:94`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_strerror (function) `const char *cvm_strerror(int e)`
- Defined: `cvm2/cvm.c:113`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vp (function) `static int vp(CvmState *vm, uint64_t v)`
- Defined: `cvm2/cvm.c:137`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vo (function) `static int vo(CvmState *vm, uint64_t *v)`
- Defined: `cvm2/cvm.c:143`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### r8 (function) `static int r8(CvmState *vm, uint8_t *o)`
- Defined: `cvm2/cvm.c:149`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### r32 (function) `static int r32(CvmState *vm, uint32_t *o)`
- Defined: `cvm2/cvm.c:155`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### ri32 (function) `static int ri32(CvmState *vm, int32_t *o)`
- Defined: `cvm2/cvm.c:165`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### r64 (function) `static int r64(CvmState *vm, uint64_t *o)`
- Defined: `cvm2/cvm.c:173`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### push_frame (function) `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...`
- Defined: `cvm2/cvm.c:183`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### pop_frame (function) `static void pop_frame(CvmState *vm)`
- Defined: `cvm2/cvm.c:196`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cur_frame (function) `static CvmFrame *cur_frame(CvmState *vm)`
- Defined: `cvm2/cvm.c:203`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### range_valid (function) `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)`
- Defined: `cvm2/cvm.c:207`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### mem_valid (function) `static int mem_valid(CvmState *vm, uint64_t a, size_t s)`
- Defined: `cvm2/cvm.c:215`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### heap_alloc (function) `static uint64_t heap_alloc(CvmState *vm, size_t s)`
- Defined: `cvm2/cvm.c:227`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_heap_alloc (function) `void *cvm_heap_alloc(CvmState *vm, size_t size)`
- Defined: `cvm2/cvm.c:235`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### data_w64 (function) `static void data_w64(CvmState *vm, size_t off, uint64_t v)`
- Defined: `cvm2/cvm.c:239`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### data_r64 (function) `static uint64_t data_r64(CvmState *vm, size_t off)`
- Defined: `cvm2/cvm.c:244`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_set_args (function) `int cvm_set_args(CvmState *vm, int argc, char **argv)`
- Defined: `cvm2/cvm.c:250`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_register_native (function) `int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn)`
- Defined: `cvm2/cvm.c:283`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### find_native (function) `static int find_native(CvmState *vm, const char *name)`
- Defined: `cvm2/cvm.c:294`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_write (function) `static int64_t native_write(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:305`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_read (function) `static int64_t native_read(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:311`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_exit (function) `static int64_t native_exit(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:317`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_abort (function) `static int64_t native_abort(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:324`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_putchar (function) `static int64_t native_putchar(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:329`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_puts (function) `static int64_t native_puts(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:336`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strlen (function) `static int64_t native_strlen(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:350`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strcmp (function) `static int64_t native_strcmp(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:356`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strncmp (function) `static int64_t native_strncmp(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:362`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strcpy (function) `static int64_t native_strcpy(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:369`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strncpy (function) `static int64_t native_strncpy(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:375`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strchr (function) `static int64_t native_strchr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:382`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strstr (function) `static int64_t native_strstr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:388`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_memcpy (function) `static int64_t native_memcpy(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:395`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_memmove (function) `static int64_t native_memmove(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:402`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_memset (function) `static int64_t native_memset(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:409`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_memcmp (function) `static int64_t native_memcmp(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:415`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_malloc (function) `static int64_t native_malloc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:422`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_free (function) `static int64_t native_free(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:428`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_calloc (function) `static int64_t native_calloc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:433`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_realloc (function) `static int64_t native_realloc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:442`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_atol (function) `static int64_t native_atol(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:451`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strtol (function) `static int64_t native_strtol(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:457`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vout_write (function) `static void vout_write(Vout *vo, const char *s, size_t n)`
- Defined: `cvm2/cvm.c:472`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vout_char (function) `static void vout_char(Vout *vo, char c)`
- Defined: `cvm2/cvm.c:484`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vout_uint (function) `static void vout_uint(Vout *vo, uint64_t v, int base, int upper)`
- Defined: `cvm2/cvm.c:486`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vformat (function) `static void vformat(Vout *vo, const char *fmt, uint64_t *argv, int argc)`
- Defined: `cvm2/cvm.c:499`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fprintf (function) `static int64_t native_fprintf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:583`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_printf (function) `static int64_t native_printf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:593`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_sprintf (function) `static int64_t native_sprintf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:602`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_snprintf (function) `static int64_t native_snprintf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:613`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fopen (function) `static int64_t native_fopen(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:625`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fclose (function) `static int64_t native_fclose(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:632`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fread (function) `static int64_t native_fread(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:638`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fwrite (function) `static int64_t native_fwrite(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:645`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fseek (function) `static int64_t native_fseek(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:652`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_ftell (function) `static int64_t native_ftell(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:658`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_rewind (function) `static int64_t native_rewind(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:664`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fputs (function) `static int64_t native_fputs(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:671`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fputc (function) `static int64_t native_fputc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:677`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fgetc (function) `static int64_t native_fgetc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:683`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_ungetc (function) `static int64_t native_ungetc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:689`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fflush (function) `static int64_t native_fflush(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:695`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_perror (function) `static int64_t native_perror(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:701`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_stderr_addr (function) `static int64_t native_stderr_addr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:712`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_stdout_addr (function) `static int64_t native_stdout_addr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:717`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_stdin_addr (function) `static int64_t native_stdin_addr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:722`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_exit_core (function) `static int64_t native_exit_core(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:729`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### register_defaults (function) `static void register_defaults(CvmState *vm)`
- Defined: `cvm2/cvm.c:736`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### rl32 (function) `static uint32_t rl32(const uint8_t *p)`
- Defined: `cvm2/cvm.c:788`
- Doc: cvm_register_native(vm, "fputc", native_fputc); cvm_register_native(vm, "fgetc", native_fgetc); cvm_register_native(vm, 
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### decompress_rle (function) `static int decompress_rle(uint8_t *dst, size_t dsz, const uint8_t *src, size_t ssz)`
- Defined: `cvm2/cvm.c:793`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_free_module (function) `static void cvm_free_module(CvmState *vm)`
- Defined: `cvm2/cvm.c:815`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_load_module (function) `int cvm_load_module(CvmState *vm, const uint8_t *d, size_t sz)`
- Defined: `cvm2/cvm.c:830`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_load_module_file (function) `int cvm_load_module_file(CvmState *vm, const char *path)`
- Defined: `cvm2/cvm.c:923`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_run_loop (function) `static int cvm_run_loop(CvmState *vm)`
- Defined: `cvm2/cvm.c:942`
- Doc: if (sz < 0) { fclose(f); return CVM_ERR_IO; } rewind(f); uint8_t *buf = (uint8_t *)xmal((size_t)sz); size_t rd = fread(b
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_run (function) `int cvm_run(CvmState *vm)`
- Defined: `cvm2/cvm.c:952`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_continue (function) `int cvm_continue(CvmState *vm)`
- Defined: `cvm2/cvm.c:990`
- Doc: rsp = top - 8; (uint64_t *)(uintptr_t)(top - 8) = 0; data_w64(vm, CVM_DATA_RSP, rsp); data_w64(vm, CVM_DATA_RBP, rsp); d
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_break_set (function) `int cvm_break_set(CvmState *vm, size_t ip)`
- Defined: `cvm2/cvm.c:994`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_break_clear (function) `int cvm_break_clear(CvmState *vm, size_t ip)`
- Defined: `cvm2/cvm.c:1003`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_break_clear_all (function) `void cvm_break_clear_all(CvmState *vm)`
- Defined: `cvm2/cvm.c:1014`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_break_hit (function) `int cvm_break_hit(const CvmState *vm)`
- Defined: `cvm2/cvm.c:1018`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_profile_begin (function) `int cvm_profile_begin(CvmState *vm)`
- Defined: `cvm2/cvm.c:1024`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_profile_end (function) `void cvm_profile_end(CvmState *vm)`
- Defined: `cvm2/cvm.c:1034`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_step (function) `int cvm_step(CvmState *vm)`
- Defined: `cvm2/cvm.c:1039`
- Doc: if (vm->code_size > vm->config.max_profile_code) return CVM_ERR_BOUNDS; if (!vm->ip_counts) vm->ip_counts = (uint32_t *)
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_exit_code (function) `int64_t cvm_exit_code(const CvmState *vm)`
- Defined: `cvm2/cvm.c:1351`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_instruction_count (function) `uint64_t cvm_instruction_count(const CvmState *vm)`
- Defined: `cvm2/cvm.c:1352`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### main (function) `int main(int argc, char *argv[])`
- Defined: `cvm2/cvm.c:1355`
- Doc: if defined(CVM_STANDALONE) && !defined(CVM_NO_MAIN)
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

## cvm2/cvm.h

### cvm_create (function) `CvmState *cvm_create(const CvmConfig *config);`
- Defined: `cvm2/cvm.h:247`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_destroy (function) `void cvm_destroy(CvmState *vm);`
- Defined: `cvm2/cvm.h:248`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_load_module (function) `int cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);`
- Defined: `cvm2/cvm.h:249`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_load_module_file (function) `int cvm_load_module_file(CvmState *vm, const char *path);`
- Defined: `cvm2/cvm.h:250`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_run (function) `int cvm_run(CvmState *vm);`
- Defined: `cvm2/cvm.h:251`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_continue (function) `int cvm_continue(CvmState *vm);`
- Defined: `cvm2/cvm.h:252`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_step (function) `int cvm_step(CvmState *vm);`
- Defined: `cvm2/cvm.h:253`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_exit_code (function) `int64_t cvm_exit_code(const CvmState *vm);`
- Defined: `cvm2/cvm.h:254`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_instruction_count (function) `uint64_t cvm_instruction_count(const CvmState *vm);`
- Defined: `cvm2/cvm.h:255`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_strerror (function) `const char *cvm_strerror(int error_code);`
- Defined: `cvm2/cvm.h:256`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_register_native (function) `int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn);`
- Defined: `cvm2/cvm.h:258`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_set_args (function) `int cvm_set_args(CvmState *vm, int argc, char **argv);`
- Defined: `cvm2/cvm.h:259`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_heap_alloc (function) `void *cvm_heap_alloc(CvmState *vm, size_t size);`
- Defined: `cvm2/cvm.h:260`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_break_set (function) `int cvm_break_set(CvmState *vm, size_t ip);`
- Defined: `cvm2/cvm.h:262`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_break_clear (function) `int cvm_break_clear(CvmState *vm, size_t ip);`
- Defined: `cvm2/cvm.h:263`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_break_clear_all (function) `void cvm_break_clear_all(CvmState *vm);`
- Defined: `cvm2/cvm.h:264`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_break_hit (function) `int cvm_break_hit(const CvmState *vm);`
- Defined: `cvm2/cvm.h:265`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_profile_begin (function) `int cvm_profile_begin(CvmState *vm);`
- Defined: `cvm2/cvm.h:266`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_profile_end (function) `void cvm_profile_end(CvmState *vm);`
- Defined: `cvm2/cvm.h:267`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

## cvm2/cvm_dbg_main.c

### emit_stdout (function) `static int emit_stdout(void *ctx, const char *line)`
- Defined: `cvm2/cvm_dbg_main.c:29`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### func_display (function) `static const char *func_display(uint32_t fi, char *fb, size_t cap)`
- Defined: `cvm2/cvm_dbg_main.c:36`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### func_of_ip (function) `static int func_of_ip(size_t ip)`
- Defined: `cvm2/cvm_dbg_main.c:40`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### parse_u32 (function) `static int parse_u32(const char *s, uint32_t *out)`
- Defined: `cvm2/cvm_dbg_main.c:51`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### report_run (function) `static void report_run(int rc)`
- Defined: `cvm2/cvm_dbg_main.c:59`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_list (function) `static void cmd_list(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:71`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_break (function) `static void cmd_break(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:98`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_delete (function) `static void cmd_delete(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:133`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_step (function) `static void cmd_step(void)`
- Defined: `cvm2/cvm_dbg_main.c:152`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_next (function) `static void cmd_next(void)`
- Defined: `cvm2/cvm_dbg_main.c:166`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_run (function) `static void cmd_run(void)`
- Defined: `cvm2/cvm_dbg_main.c:184`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_bt (function) `static void cmd_bt(void)`
- Defined: `cvm2/cvm_dbg_main.c:194`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_stack (function) `static void cmd_stack(void)`
- Defined: `cvm2/cvm_dbg_main.c:206`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_locals (function) `static void cmd_locals(void)`
- Defined: `cvm2/cvm_dbg_main.c:213`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_info (function) `static void cmd_info(void)`
- Defined: `cvm2/cvm_dbg_main.c:225`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_profile (function) `static void cmd_profile(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:241`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_help (function) `static void cmd_help(void)`
- Defined: `cvm2/cvm_dbg_main.c:304`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### dispatch (function) `static void dispatch(char *line)`
- Defined: `cvm2/cvm_dbg_main.c:310`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### main (function) `int main(int argc, char **argv)`
- Defined: `cvm2/cvm_dbg_main.c:337`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

## cvm2/cvm_dis.c

### putc_str (function) `static void putc_str(char *buf, size_t cap, size_t *n, char c)`
- Defined: `cvm2/cvm_dis.c:13`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### puts_str (function) `static void puts_str(char *buf, size_t cap, size_t *n, const char *s)`
- Defined: `cvm2/cvm_dis.c:17`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### put_hex (function) `static void put_hex(char *buf, size_t cap, size_t *n, uint64_t v, int digits)`
- Defined: `cvm2/cvm_dis.c:21`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### put_dec (function) `static void put_dec(char *buf, size_t cap, size_t *n, int64_t v)`
- Defined: `cvm2/cvm_dis.c:35`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### pad_name (function) `static void pad_name(char *buf, size_t cap, size_t *n, const char *name)`
- Defined: `cvm2/cvm_dis.c:49`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### cvm_dis_line (function) `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end,
                 char *buf, size...`
- Defined: `cvm2/cvm_dis.c:56`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### cvm_dis_function (function) `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end,
                     CvmDi...`
- Defined: `cvm2/cvm_dis.c:153`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### cvm_dis_module (function) `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx)`
- Defined: `cvm2/cvm_dis.c:173`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

## cvm2/cvm_dis.h

### cvm_dis_module (function) `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx);`
- Defined: `cvm2/cvm_dis.h:23`
- Doc: #ifndef CVM_DIS_H #define CVM_DIS_H #include <stddef.h> #include <stdint.h> #include "cvm_view.h" #ifdef __cplusplus ext
- Depends on: `cvm2/cvm_view.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_dis_main.c`

### cvm_dis_function (function) `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end, CvmDisEmit emit, void *ctx);`
- Defined: `cvm2/cvm_dis.h:26`
- Doc: #include <stddef.h> #include <stdint.h> #include "cvm_view.h" #ifdef __cplusplus extern "C" { #endif typedef int (*CvmDi
- Depends on: `cvm2/cvm_view.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_dis_main.c`

### cvm_dis_line (function) `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end, char *buf, size_t cap);`
- Defined: `cvm2/cvm_dis.h:31`
- Doc: One instruction at code offset off (within [begin,end)). Returns the * instruction size, or -1 when it does not decode i
- Depends on: `cvm2/cvm_view.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_dis_main.c`

## cvm2/cvm_dis_main.c

### print_line (function) `static int print_line(void *ctx, const char *line)`
- Defined: `cvm2/cvm_dis_main.c:11`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

### main (function) `int main(int argc, char **argv)`
- Defined: `cvm2/cvm_dis_main.c:18`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

## cvm2/cvm_jit.c

### cvm_jit_create (function) `CvmJitState *cvm_jit_create(void)`
- Defined: `cvm2/cvm_jit.c:36`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_destroy (function) `void cvm_jit_destroy(CvmJitState *jit)`
- Defined: `cvm2/cvm_jit.c:48`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### ip_map_clear (function) `static void ip_map_clear(CvmJitState *jit)`
- Defined: `cvm2/cvm_jit.c:58`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### ip_map_add (function) `static void ip_map_add(CvmJitState *jit, size_t bc_ip, size_t native_off)`
- Defined: `cvm2/cvm_jit.c:62`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### ip_map_lookup (function) `static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip)`
- Defined: `cvm2/cvm_jit.c:69`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### func_cache_find (function) `static JitFuncEntry *func_cache_find(CvmJitState *jit, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit.c:81`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### func_cache_add (function) `static JitFuncEntry *func_cache_add(CvmJitState *jit, uint32_t func_idx,
                        ...`
- Defined: `cvm2/cvm_jit.c:88`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### opcode_total_size (function) `static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip)`
- Defined: `cvm2/cvm_jit.c:105`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_stack_push (function) `static void emit_stack_push(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:117`
- Doc: /* ------------------------------------------------------------------ static size_t opcode_total_size(const uint8_t *cod
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_stack_pop (function) `static void emit_stack_pop(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:124`
- Doc: } /* ------------------------------------------------------------------ /*  Emit helpers: operand stack operations /* --
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_stack_pop_into (function) `static void emit_stack_pop_into(JitBuf *b, int dst)`
- Defined: `cvm2/cvm_jit.c:130`
- Doc: /* Push rax onto the operand stack: slots[sp] = rax; sp++ static void emit_stack_push(JitBuf *b) { /* mov [r12 + r13*8],
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_stack_push_reg (function) `static void emit_stack_push_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit.c:136`
- Doc: /* Pop from operand stack into rax: sp--; rax = slots[sp] static void emit_stack_pop(JitBuf *b) { emit_dec_reg(b, JIT_RE
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_call1 (function) `static void emit_call1(JitBuf *b, void *fn, int arg)`
- Defined: `cvm2/cvm_jit.c:146`
- Doc: emit_mov_reg_sib(b, dst, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Push a register onto the operand stack static void emit_sta
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_call2 (function) `static void emit_call2(JitBuf *b, void *fn, int a1, int a2)`
- Defined: `cvm2/cvm_jit.c:152`
- Doc: emit_inc_reg(b, JIT_REG_SP); } /* ------------------------------------------------------------------ /*  Emit helpers: C
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_call3 (function) `static void emit_call3(JitBuf *b, void *fn, int a1, int a2, int a3)`
- Defined: `cvm2/cvm_jit.c:159`
- Doc: /* Call a C function with 1 arg (rdi).  Clobbers rax, rcx, rdx, rsi, rdi, r8-r11. static void emit_call1(JitBuf *b, void
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_prologue (function) `static void emit_prologue(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:170`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_epilogue (function) `static void emit_epilogue(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:232`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_save_sp (function) `static void emit_save_sp(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:252`
- Doc: emit_pop(b, JIT_REG_SP);      /* r13 emit_pop(b, JIT_REG_SLOTS);   /* r12 emit_pop(b, JIT_REG_FRAME);   /* rbx emit_pop(
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_restore_sp (function) `static void emit_restore_sp(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:258`
- Doc: emit_ret(b); } /* ------------------------------------------------------------------ /*  Emit: save/restore VM state (fo
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### error (function) `* keeps executing dead code after the stop: error() -> exit() returns
 * into the middle of the f...`
- Defined: `cvm2/cvm_jit.c:267`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_opcode (function) `static int emit_opcode(JitCtx *ctx, size_t bc_ip)`
- Defined: `cvm2/cvm_jit.c:302`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### jit_apply_patches_local (function) `static void jit_apply_patches_local(JitBuf *b, const JitPatches *p)`
- Defined: `cvm2/cvm_jit.c:1235`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_compile_func (function) `void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit.c:1253`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_compile_module (function) `int cvm_jit_compile_module(CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1360`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_lookup (function) `void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit.c:1376`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### find_func_for_ip (function) `static uint32_t find_func_for_ip(const CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1388`
- Doc: /* ------------------------------------------------------------------ void *cvm_jit_lookup(CvmState *vm, uint32_t func_i
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_exec_one (function) `void cvm_jit_exec_one(CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1397`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_run (function) `int cvm_jit_run(CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1427`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_stats (function) `void cvm_jit_stats(const CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1488`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_dump (function) `void cvm_jit_dump(const CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1499`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_step (function) `extern int cvm_step(CvmState *);`
- Defined: `cvm2/cvm_jit.c:1420`
- Doc: Fall back: interpret this function's bytecodes. We run the interpreter until ip leaves this function or * vm->running be
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_run (function) `extern int cvm_run(CvmState *);`
- Defined: `cvm2/cvm_jit.c:1430`
- Doc: while (vm->running) { uint32_t cur = find_func_for_ip(vm); if (cur != start_func) break;  /* left this function /* Execu
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

## cvm2/cvm_jit.h

### cvm_jit_create (function) `CvmJitState *cvm_jit_create(void);`
- Defined: `cvm2/cvm_jit.h:120`
- Doc: /* IP-to-native mapping (shared across all functions) JitIpMap        ip_map[JIT_IP_MAP_SIZE]; size_t          ip_map_co
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_jit_x86.h`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_jit_help.c`, `cvm2/gen_fib_cvm.c`

### cvm_jit_destroy (function) `void cvm_jit_destroy(CvmJitState *jit);`
- Defined: `cvm2/cvm_jit.h:123`
- Doc: /* Profile counters for tier-up uint32_t        hot_threshold;          /* tier-up threshold uint32_t        warm_thresh
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_jit_x86.h`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_jit_help.c`, `cvm2/gen_fib_cvm.c`

### cvm_jit_compile_module (function) `int cvm_jit_compile_module(CvmState *vm);`
- Defined: `cvm2/cvm_jit.h:127`
- Doc: Compile all functions in a loaded module to native code. * Returns CVM_OK on success.
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_jit_x86.h`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_jit_help.c`, `cvm2/gen_fib_cvm.c`

### cvm_jit_compile_func (function) `void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx);`
- Defined: `cvm2/cvm_jit.h:130`
- Doc: Compile all functions in a loaded module to native code. * Returns CVM_OK on success. int cvm_jit_compile_module(CvmStat
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_jit_x86.h`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_jit_help.c`, `cvm2/gen_fib_cvm.c`

### cvm_jit_lookup (function) `void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx);`
- Defined: `cvm2/cvm_jit.h:133`
- Doc: Compile all functions in a loaded module to native code. * Returns CVM_OK on success. int cvm_jit_compile_module(CvmStat
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_jit_x86.h`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_jit_help.c`, `cvm2/gen_fib_cvm.c`

### cvm_jit_run (function) `int cvm_jit_run(CvmState *vm);`
- Defined: `cvm2/cvm_jit.h:142`
- Doc: Execute using the JIT.  Compiles all functions first, then dispatches to compiled code.  Falls back to interpreter for u
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_jit_x86.h`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_jit_help.c`, `cvm2/gen_fib_cvm.c`

### returns (function) `* returns (via RET) or encounters an error. */ void cvm_jit_exec_one(CvmState *vm);`
- Defined: `cvm2/cvm_jit.h:145`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_jit_x86.h`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_jit_help.c`, `cvm2/gen_fib_cvm.c`

### cvm_jit_stats (function) `void cvm_jit_stats(const CvmState *vm);`
- Defined: `cvm2/cvm_jit.h:153`
- Doc: Execute one compiled function at vm->ip.  Returns when the function * returns (via RET) or encounters an error. void cvm
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_jit_x86.h`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_jit_help.c`, `cvm2/gen_fib_cvm.c`

### cvm_jit_dump (function) `void cvm_jit_dump(const CvmState *vm);`
- Defined: `cvm2/cvm_jit.h:159`
- Doc: returns (via RET) or encounters an error. void cvm_jit_exec_one(CvmState *vm); /* --------------------------------------
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_jit_x86.h`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_jit_help.c`, `cvm2/gen_fib_cvm.c`

## cvm2/cvm_jit_help.c

### cvm_jit_offsets_init (function) `void cvm_jit_offsets_init(CvmJitOffsets *o)`
- Defined: `cvm2/cvm_jit_help.c:22`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### xmal (function) `static void *xmal(size_t s)`
- Defined: `cvm2/cvm_jit_help.c:46`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### xcal (function) `static void *xcal(size_t n, size_t s)`
- Defined: `cvm2/cvm_jit_help.c:52`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### push_frame (function) `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...`
- Defined: `cvm2/cvm_jit_help.c:58`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### pop_frame (function) `static void pop_frame(CvmState *vm)`
- Defined: `cvm2/cvm_jit_help.c:71`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cur_frame (function) `static CvmFrame *cur_frame(CvmState *vm)`
- Defined: `cvm2/cvm_jit_help.c:78`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### range_valid (function) `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)`
- Defined: `cvm2/cvm_jit_help.c:82`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### mem_valid (function) `static int mem_valid(const CvmState *vm, uint64_t a, size_t s)`
- Defined: `cvm2/cvm_jit_help.c:90`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### heap_alloc (function) `static uint64_t heap_alloc(CvmState *vm, size_t s)`
- Defined: `cvm2/cvm_jit_help.c:102`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### find_native (function) `static int find_native(const CvmState *vm, const char *name)`
- Defined: `cvm2/cvm_jit_help.c:110`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### jit_vp (function) `static int jit_vp(CvmState *vm, uint64_t v)`
- Defined: `cvm2/cvm_jit_help.c:120`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### jit_vo (function) `static int jit_vo(CvmState *vm, uint64_t *v)`
- Defined: `cvm2/cvm_jit_help.c:126`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_func_enter (function) `uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit_help.c:136`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_func_leave (function) `void cvm_jit_func_leave(CvmState *vm)`
- Defined: `cvm2/cvm_jit_help.c:145`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_call (function) `int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc)`
- Defined: `cvm2/cvm_jit_help.c:155`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_ret (function) `int cvm_jit_ret(CvmState *vm, uint64_t retval)`
- Defined: `cvm2/cvm_jit_help.c:176`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_call_native (function) `int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc)`
- Defined: `cvm2/cvm_jit_help.c:193`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_memcheck (function) `int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size)`
- Defined: `cvm2/cvm_jit_help.c:213`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_alloc (function) `uint64_t cvm_jit_alloc(CvmState *vm, size_t size)`
- Defined: `cvm2/cvm_jit_help.c:221`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_syscall (function) `int cvm_jit_syscall(CvmState *vm, uint8_t sn, uint8_t argc)`
- Defined: `cvm2/cvm_jit_help.c:229`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_error (function) `void cvm_jit_error(CvmState *vm, int error_code)`
- Defined: `cvm2/cvm_jit_help.c:256`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

## cvm2/cvm_jit_help.h

### cvm_jit_offsets_init (function) `void cvm_jit_offsets_init(CvmJitOffsets *off);`
- Defined: `cvm2/cvm_jit_help.h:44`
- Doc: Compute and cache all field offsets.  Must be called once before * any JIT compilation begins.
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.c`

### cvm_jit_func_enter (function) `uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx);`
- Defined: `cvm2/cvm_jit_help.h:52`
- Doc: Called at JIT function entry to sync interpreter state. * Returns the code pointer for the function.
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.c`

### cvm_jit_func_leave (function) `void cvm_jit_func_leave(CvmState *vm);`
- Defined: `cvm2/cvm_jit_help.h:55`
- Doc: Called at JIT function entry to sync interpreter state. * Returns the code pointer for the function. uint8_t *cvm_jit_fu
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.c`

### cvm_jit_call (function) `int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc);`
- Defined: `cvm2/cvm_jit_help.h:66`
- Doc: Execute OP_CALL: push a new frame, copy arguments from the operand stack into the new frame's locals, and set vm->ip to 
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.c`

### to (function) `* Returns 0 if there is a caller to return to (vm->ip is set). * Returns 1 if this was the entry frame (vm->running = 0, done). */ int cvm_jit_ret(CvmState *vm, uint64_t retval);`
- Defined: `cvm2/cvm_jit_help.h:70`
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.c`

### cvm_jit_call_native (function) `int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc);`
- Defined: `cvm2/cvm_jit_help.h:77`
- Doc: Execute OP_CALL_NATIVE: resolve the native function by index, pop arguments from the operand stack, call the host functi
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.c`

### region (function) `* region (heap, globals, string pool, or any frame's locals). * Returns 1 if valid, 0 if invalid. */ int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size);`
- Defined: `cvm2/cvm_jit_help.h:84`
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.c`

### cvm_jit_alloc (function) `uint64_t cvm_jit_alloc(CvmState *vm, size_t size);`
- Defined: `cvm2/cvm_jit_help.h:94`
- Doc: Bump-allocate 'size' bytes from the CVM heap. * Returns the heap pointer on success, 0 on exhaustion.
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.c`

### cvm_jit_syscall (function) `int cvm_jit_syscall(CvmState *vm, uint8_t syscall_nr, uint8_t argc);`
- Defined: `cvm2/cvm_jit_help.h:103`
- Doc: Execute a Linux-style syscall.  Pops 'argc' arguments from the operand stack, dispatches by syscall number, and pushes t
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.c`

### cvm_jit_error (function) `void cvm_jit_error(CvmState *vm, int error_code);`
- Defined: `cvm2/cvm_jit_help.h:112`
- Doc: Set an error code and terminate the VM.  This is called when a JIT-compiled function detects an unrecoverable error (bad
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.c`

## cvm2/cvm_jit_x86.c

### jit_buf_init (function) `void jit_buf_init(JitBuf *b, size_t cap)`
- Defined: `cvm2/cvm_jit_x86.c:35`
- Depends on: `cvm2/cvm_jit_x86.h`

### jit_buf_free (function) `void jit_buf_free(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:48`
- Depends on: `cvm2/cvm_jit_x86.h`

### jit_buf_reset (function) `void jit_buf_reset(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:56`
- Depends on: `cvm2/cvm_jit_x86.h`

### jit_buf_failed (function) `int jit_buf_failed(const JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:61`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_grow (function) `static void emit_grow(JitBuf *b, size_t need)`
- Defined: `cvm2/cvm_jit_x86.c:67`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit8 (function) `void emit8(JitBuf *b, uint8_t v)`
- Defined: `cvm2/cvm_jit_x86.c:84`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit16 (function) `void emit16(JitBuf *b, uint16_t v)`
- Defined: `cvm2/cvm_jit_x86.c:89`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit32 (function) `void emit32(JitBuf *b, uint32_t v)`
- Defined: `cvm2/cvm_jit_x86.c:94`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit64 (function) `void emit64(JitBuf *b, uint64_t v)`
- Defined: `cvm2/cvm_jit_x86.c:99`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_bytes (function) `void emit_bytes(JitBuf *b, const void *data, size_t len)`
- Defined: `cvm2/cvm_jit_x86.c:104`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_rex (function) `void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b)`
- Defined: `cvm2/cvm_jit_x86.c:114`
- Doc: emit_grow(b, 8); if (!b->failed) { memcpy(b->code + b->size, &v, 8); b->size += 8; } } void emit_bytes(JitBuf *b, const 
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_modrm (function) `void emit_modrm(JitBuf *b, int mod, int reg, int rm)`
- Defined: `cvm2/cvm_jit_x86.c:119`
- Doc: emit_grow(b, len); if (!b->failed) { memcpy(b->code + b->size, data, len); b->size += len; } } /* ----------------------
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_modrm_disp32 (function) `static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:124`
- Doc: /*  Internal encoding helpers /* ------------------------------------------------------------------ /* REX prefix: 0100 
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_rex_op_modrm (function) `static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm)`
- Defined: `cvm2/cvm_jit_x86.c:130`
- Doc: } /* ModRM byte void emit_modrm(JitBuf *b, int mod, int reg, int rm) { emit8(b, (uint8_t)((mod << 6) | ((reg & 7) << 3) 
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_sib (function) `static void emit_sib(JitBuf *b, int scale, int index, int base)`
- Defined: `cvm2/cvm_jit_x86.c:137`
- Doc: /* ModRM + disp32 static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp) { emit_modrm(b, 2, reg, rm); e
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_reg_imm64 (function) `void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:145`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_reg_imm32 (function) `void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:152`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_reg_reg (function) `void emit_mov_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:165`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_reg_mem (function) `void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:171`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_mem_reg (function) `void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src)`
- Defined: `cvm2/cvm_jit_x86.c:178`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_movzx_reg_mem8 (function) `void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:185`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_movzx_reg_mem16 (function) `void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:192`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_movsx_reg_mem32 (function) `void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:199`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov32_reg_mem (function) `void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:206`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov32_mem_reg (function) `void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src)`
- Defined: `cvm2/cvm_jit_x86.c:214`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_lea_sib (function) `void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:222`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_reg_sib (function) `void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale)`
- Defined: `cvm2/cvm_jit_x86.c:259`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_sib_reg (function) `void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src)`
- Defined: `cvm2/cvm_jit_x86.c:267`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_push (function) `void emit_push(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:279`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_pop (function) `void emit_pop(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:285`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_add_reg_reg (function) `void emit_add_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:295`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_add_reg_imm32 (function) `void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:299`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_sub_reg_reg (function) `void emit_sub_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:308`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_sub_reg_imm32 (function) `void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:312`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_imul_reg_reg (function) `void emit_imul_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:320`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_idiv_reg (function) `void emit_idiv_reg(JitBuf *b, int divisor)`
- Defined: `cvm2/cvm_jit_x86.c:327`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_div_reg (function) `void emit_div_reg(JitBuf *b, int divisor)`
- Defined: `cvm2/cvm_jit_x86.c:334`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_cqo (function) `void emit_cqo(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:341`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_neg_reg (function) `void emit_neg_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:347`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_inc_reg (function) `void emit_inc_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:354`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_dec_reg (function) `void emit_dec_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:361`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_and_reg_imm32 (function) `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:372`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_and_reg_reg (function) `void emit_and_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:380`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_or_reg_reg (function) `void emit_or_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:384`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_xor_reg_reg (function) `void emit_xor_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:388`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_not_reg (function) `void emit_not_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:392`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_shl_reg_cl (function) `void emit_shl_reg_cl(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:399`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_shr_reg_cl (function) `void emit_shr_reg_cl(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:406`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_sar_reg_cl (function) `void emit_sar_reg_cl(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:413`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_xor_reg_self (function) `void emit_xor_reg_self(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:420`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_cmp_reg_reg (function) `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg)`
- Defined: `cvm2/cvm_jit_x86.c:430`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_test_reg_reg (function) `void emit_test_reg_reg(JitBuf *buf, int a, int breg)`
- Defined: `cvm2/cvm_jit_x86.c:435`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_setcc (function) `void emit_setcc(JitBuf *b, int cc, int dst)`
- Defined: `cvm2/cvm_jit_x86.c:440`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_movzx_reg_reg8 (function) `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:449`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_jmp_rel32 (function) `size_t emit_jmp_rel32(JitBuf *b, int32_t rel)`
- Defined: `cvm2/cvm_jit_x86.c:460`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_jcc_rel32 (function) `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel)`
- Defined: `cvm2/cvm_jit_x86.c:467`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_jmp_buf (function) `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p)`
- Defined: `cvm2/cvm_jit_x86.c:475`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_jcc_buf (function) `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p)`
- Defined: `cvm2/cvm_jit_x86.c:487`
- Depends on: `cvm2/cvm_jit_x86.h`

### jit_apply_patches (function) `void jit_apply_patches(JitBuf *b, const JitPatches *p)`
- Defined: `cvm2/cvm_jit_x86.c:500`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_call_rel32 (function) `size_t emit_call_rel32(JitBuf *b, int32_t rel)`
- Defined: `cvm2/cvm_jit_x86.c:512`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_call_reg (function) `void emit_call_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:519`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_ret (function) `void emit_ret(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:527`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_syscall (function) `void emit_syscall(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:535`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_int3 (function) `void emit_int3(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:540`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_nop (function) `void emit_nop(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:544`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_call_abs (function) `void emit_call_abs(JitBuf *b, void *func, int scratch)`
- Defined: `cvm2/cvm_jit_x86.c:552`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_mem_imm8 (function) `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:561`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_mem_imm32 (function) `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:569`
- Depends on: `cvm2/cvm_jit_x86.h`

## cvm2/cvm_jit_x86.h

### reg_needs_rex (function) `static inline int reg_needs_rex(int r)`
- Defined: `cvm2/cvm_jit_x86.h:80`
- Doc: int   jit_buf_failed(const JitBuf *b); /* ------------------------------------------------------------------ /*  Byte em
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### reg_high3 (function) `static inline int reg_high3(int r)`
- Defined: `cvm2/cvm_jit_x86.h:81`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### jit_buf_init (function) `void jit_buf_init(JitBuf *b, size_t initial_cap);`
- Defined: `cvm2/cvm_jit_x86.h:63`
- Doc: size_t patch_off;    /* offset in buf->code where rel32 lives size_t target;       /* absolute target offset in the same
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### jit_buf_free (function) `void jit_buf_free(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:64`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### jit_buf_reset (function) `void jit_buf_reset(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:65`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### jit_buf_failed (function) `int jit_buf_failed(const JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:66`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit8 (function) `void emit8(JitBuf *b, uint8_t v);`
- Defined: `cvm2/cvm_jit_x86.h:71`
- Doc: size_t   count; } JitPatches; /* ------------------------------------------------------------------ /*  Buffer lifecycle
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit16 (function) `void emit16(JitBuf *b, uint16_t v);`
- Defined: `cvm2/cvm_jit_x86.h:72`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit32 (function) `void emit32(JitBuf *b, uint32_t v);`
- Defined: `cvm2/cvm_jit_x86.h:73`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit64 (function) `void emit64(JitBuf *b, uint64_t v);`
- Defined: `cvm2/cvm_jit_x86.h:74`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_bytes (function) `void emit_bytes(JitBuf *b, const void *data, size_t len);`
- Defined: `cvm2/cvm_jit_x86.h:75`
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_reg_imm64 (function) `void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm);`
- Defined: `cvm2/cvm_jit_x86.h:88`
- Doc: void  emit64(JitBuf *b, uint64_t v); void  emit_bytes(JitBuf *b, const void *data, size_t len); /* ---------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_reg_imm32 (function) `void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm);`
- Defined: `cvm2/cvm_jit_x86.h:91`
- Doc: /* ------------------------------------------------------------------ /*  Register checks /* ---------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_reg_reg (function) `void emit_mov_reg_reg(JitBuf *b, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:94`
- Doc: static inline int reg_needs_rex(int r) { return r >= X8; } static inline int reg_high3(int r) { return (r >> 3) & 1; } /
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_reg_mem (function) `void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp);`
- Defined: `cvm2/cvm_jit_x86.h:97`
- Doc: /* ------------------------------------------------------------------ /*  Data movement /* -----------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_mem_reg (function) `void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src);`
- Defined: `cvm2/cvm_jit_x86.h:100`
- Doc: /* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64) void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm); /* MOV r64, 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_movzx_reg_mem8 (function) `void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp);`
- Defined: `cvm2/cvm_jit_x86.h:103`
- Doc: /* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32) void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t i
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_movzx_reg_mem16 (function) `void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp);`
- Defined: `cvm2/cvm_jit_x86.h:106`
- Doc: /* MOV r64, r64  (3 bytes: REX.W 89 /r) void emit_mov_reg_reg(JitBuf *b, int dst, int src); /* MOV r64, [base + disp32] 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_movsx_reg_mem32 (function) `void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp);`
- Defined: `cvm2/cvm_jit_x86.h:109`
- Doc: /* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10) void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t d
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov32_reg_mem (function) `void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp);`
- Defined: `cvm2/cvm_jit_x86.h:112`
- Doc: /* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10) void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov32_mem_reg (function) `void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src);`
- Defined: `cvm2/cvm_jit_x86.h:115`
- Doc: /* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10) void emit_movzx_reg_mem8(JitBuf *b, int dst, int ba
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_lea_sib (function) `void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp);`
- Defined: `cvm2/cvm_jit_x86.h:121`
- Doc: LEA r64, [base + index*scale + disp] scale: 0=1, 1=2, 2=4, 3=8 If index == -1, encodes [base + disp] only.
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_reg_sib (function) `void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale);`
- Defined: `cvm2/cvm_jit_x86.h:126`
- Doc: MOV r64, [base + index*scale]  (no displacement) scale: 0=1, 1=2, 2=4, 3=8
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_sib_reg (function) `void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src);`
- Defined: `cvm2/cvm_jit_x86.h:129`
- Doc: MOV r64, [base + index*scale]  (no displacement) scale: 0=1, 1=2, 2=4, 3=8  void emit_mov_reg_sib(JitBuf *b, int dst, in
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_push (function) `void emit_push(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:136`
- Doc: MOV r64, [base + index*scale]  (no displacement) scale: 0=1, 1=2, 2=4, 3=8  void emit_mov_reg_sib(JitBuf *b, int dst, in
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_pop (function) `void emit_pop(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:139`
- Doc: void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale); /* MOV [base + index*scale], r64  (no displac
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_add_reg_reg (function) `void emit_add_reg_reg(JitBuf *b, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:146`
- Doc: /*  Stack operations /* ------------------------------------------------------------------ /* PUSH r64 (1 or 2 bytes dep
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_add_reg_imm32 (function) `void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm);`
- Defined: `cvm2/cvm_jit_x86.h:149`
- Doc: /* PUSH r64 (1 or 2 bytes depending on register) void emit_push(JitBuf *b, int reg); /* POP r64 void emit_pop(JitBuf *b,
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_sub_reg_reg (function) `void emit_sub_reg_reg(JitBuf *b, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:152`
- Doc: /* POP r64 void emit_pop(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_sub_reg_imm32 (function) `void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm);`
- Defined: `cvm2/cvm_jit_x86.h:155`
- Doc: /* ------------------------------------------------------------------ /*  Arithmetic /* --------------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_imul_reg_reg (function) `void emit_imul_reg_reg(JitBuf *b, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:158`
- Doc: /* ADD r64, r64  (REX.W 01 /r) void emit_add_reg_reg(JitBuf *b, int dst, int src); /* ADD r64, imm32  (sign-extended) vo
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_idiv_reg (function) `void emit_idiv_reg(JitBuf *b, int divisor);`
- Defined: `cvm2/cvm_jit_x86.h:162`
- Doc: IDIV r64  (divides RDX:RAX by r64, quotient in RAX, remainder in RDX) * Requires RDX=0 before unsigned, or use CQO for s
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_div_reg (function) `void emit_div_reg(JitBuf *b, int divisor);`
- Defined: `cvm2/cvm_jit_x86.h:166`
- Doc: DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx).
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_cqo (function) `void emit_cqo(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:169`
- Doc: DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emi
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_neg_reg (function) `void emit_neg_reg(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:172`
- Doc: DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emi
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_inc_reg (function) `void emit_inc_reg(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:175`
- Doc: DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emi
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_dec_reg (function) `void emit_dec_reg(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:178`
- Doc: DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emi
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_and_reg_reg (function) `void emit_and_reg_reg(JitBuf *b, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:185`
- Doc: /* NEG r64  (REX.W F7 /3) void emit_neg_reg(JitBuf *b, int reg); /* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_or_reg_reg (function) `void emit_or_reg_reg(JitBuf *b, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:188`
- Doc: /* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies) void emit_inc_reg(JitBuf 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_xor_reg_reg (function) `void emit_xor_reg_reg(JitBuf *b, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:191`
- Doc: /* DEC r64 void emit_dec_reg(JitBuf *b, int reg); /* ------------------------------------------------------------------ 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_not_reg (function) `void emit_not_reg(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:194`
- Doc: /* ------------------------------------------------------------------ /*  Bitwise /* -----------------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_shl_reg_cl (function) `void emit_shl_reg_cl(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:197`
- Doc: /* AND r64, r64 void emit_and_reg_reg(JitBuf *b, int dst, int src); /* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int d
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_shr_reg_cl (function) `void emit_shr_reg_cl(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:200`
- Doc: /* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int dst, int src); /* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int d
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_sar_reg_cl (function) `void emit_sar_reg_cl(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:203`
- Doc: /* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int dst, int src); /* NOT r64 void emit_not_reg(JitBuf *b, int reg); /*
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_xor_reg_self (function) `void emit_xor_reg_self(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:206`
- Doc: /* NOT r64 void emit_not_reg(JitBuf *b, int reg); /* SHL r64, CL  (shift left by CL) void emit_shl_reg_cl(JitBuf *b, int
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_cmp_reg_reg (function) `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg);`
- Defined: `cvm2/cvm_jit_x86.h:213`
- Doc: /* SHR r64, CL  (logical shift right) void emit_shr_reg_cl(JitBuf *b, int reg); /* SAR r64, CL  (arithmetic shift right)
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_test_reg_reg (function) `void emit_test_reg_reg(JitBuf *buf, int a, int breg);`
- Defined: `cvm2/cvm_jit_x86.h:216`
- Doc: /* SAR r64, CL  (arithmetic shift right) void emit_sar_reg_cl(JitBuf *b, int reg); /* XOR reg, reg (zero-idiom, 3 bytes)
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_setcc (function) `void emit_setcc(JitBuf *b, int cc, int dst);`
- Defined: `cvm2/cvm_jit_x86.h:219`
- Doc: /* XOR reg, reg (zero-idiom, 3 bytes) void emit_xor_reg_self(JitBuf *b, int reg); /* -----------------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_jmp_rel32 (function) `size_t emit_jmp_rel32(JitBuf *b, int32_t rel);`
- Defined: `cvm2/cvm_jit_x86.h:226`
- Doc: /* CMP r64, r64  (REX.W 39 /r) void emit_cmp_reg_reg(JitBuf *buf, int a, int breg); /* TEST r64, r64  (REX.W 85 /r) void
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_jcc_rel32 (function) `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel);`
- Defined: `cvm2/cvm_jit_x86.h:229`
- Doc: /* TEST r64, r64  (REX.W 85 /r) void emit_test_reg_reg(JitBuf *buf, int a, int breg); /* SETcc r/m8  (0F 9x /0) void emi
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_jmp_buf (function) `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p);`
- Defined: `cvm2/cvm_jit_x86.h:232`
- Doc: /* SETcc r/m8  (0F 9x /0) void emit_setcc(JitBuf *b, int cc, int dst); /* ----------------------------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_jcc_buf (function) `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p);`
- Defined: `cvm2/cvm_jit_x86.h:235`
- Doc: /* ------------------------------------------------------------------ /*  Control flow /* ------------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### jit_apply_patches (function) `void jit_apply_patches(JitBuf *b, const JitPatches *p);`
- Defined: `cvm2/cvm_jit_x86.h:238`
- Doc: /* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching size_t emit_jmp_rel32(JitBuf *b, int32_t rel); /* J
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_call_rel32 (function) `size_t emit_call_rel32(JitBuf *b, int32_t rel);`
- Defined: `cvm2/cvm_jit_x86.h:241`
- Doc: /* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_call_reg (function) `void emit_call_reg(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:244`
- Doc: /* JMP to absolute offset within the buffer (emits rel32, records patch) void emit_jmp_buf(JitBuf *b, size_t target, Jit
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_ret (function) `void emit_ret(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:247`
- Doc: /* Jcc to absolute offset within the buffer void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p); /* Apply
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_syscall (function) `void emit_syscall(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:254`
- Doc: /* CALL rel32  (E8 imm32) size_t emit_call_rel32(JitBuf *b, int32_t rel); /* CALL r/m64  (FF /2, 2 bytes) void emit_call
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_int3 (function) `void emit_int3(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:257`
- Doc: /* CALL r/m64  (FF /2, 2 bytes) void emit_call_reg(JitBuf *b, int reg); /* RET  (C3) void emit_ret(JitBuf *b); /* ------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_nop (function) `void emit_nop(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:260`
- Doc: /* RET  (C3) void emit_ret(JitBuf *b); /* ------------------------------------------------------------------ /*  System 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_call_abs (function) `void emit_call_abs(JitBuf *b, void *func, int scratch);`
- Defined: `cvm2/cvm_jit_x86.h:269`
- Doc: Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch reg
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_and_reg_imm32 (function) `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm);`
- Defined: `cvm2/cvm_jit_x86.h:272`
- Doc: Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch reg
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_movzx_reg_reg8 (function) `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:275`
- Doc: Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch reg
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_rex (function) `void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b);`
- Defined: `cvm2/cvm_jit_x86.h:278`
- Doc: Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch reg
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_modrm (function) `void emit_modrm(JitBuf *buf, int mod, int reg, int rm);`
- Defined: `cvm2/cvm_jit_x86.h:281`
- Doc: Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used. void emit_call_a
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_mem_imm8 (function) `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm);`
- Defined: `cvm2/cvm_jit_x86.h:288`
- Doc: /* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension void emit_movzx_reg_reg8(JitBuf *buf, int dst, int
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_mem_imm32 (function) `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm);`
- Defined: `cvm2/cvm_jit_x86.h:291`
- Doc: /* REX prefix: exposed for inline asm emission void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b); /* ModRM byte
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

## cvm2/cvm_ops.c

### cvm_op_info (function) `const CvmOpInfo *cvm_op_info(uint8_t opcode)`
- Defined: `cvm2/cvm_ops.c:72`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

### cvm_op_name (function) `const char *cvm_op_name(uint8_t opcode)`
- Defined: `cvm2/cvm_ops.c:78`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

### cvm_ops_r8 (function) `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out)`
- Defined: `cvm2/cvm_ops.c:83`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

### cvm_ops_ru32 (function) `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off)`
- Defined: `cvm2/cvm_ops.c:89`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

### cvm_ops_ri32 (function) `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off)`
- Defined: `cvm2/cvm_ops.c:97`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

### cvm_ops_ri64 (function) `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off)`
- Defined: `cvm2/cvm_ops.c:101`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

## cvm2/cvm_ops.h

### cvm_op_info (function) `const CvmOpInfo *cvm_op_info(uint8_t opcode);`
- Defined: `cvm2/cvm_ops.h:38`
- Doc: CVM_OPK_U32   = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL   = 6, CVM_OPK_U8U8  = 7 } CvmOpKind; typedef struct { uint8_t     opc
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_ops.c`, `cvm2/cvm_val_main.c`

### cvm_op_name (function) `const char *cvm_op_name(uint8_t opcode);`
- Defined: `cvm2/cvm_ops.h:41`
- Doc: CVM_OPK_U8U8  = 7 } CvmOpKind; typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_ops.c`, `cvm2/cvm_val_main.c`

### cvm_ops_ri32 (function) `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off);`
- Defined: `cvm2/cvm_ops.h:44`
- Doc: typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for 
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_ops.c`, `cvm2/cvm_val_main.c`

### cvm_ops_ri64 (function) `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off);`
- Defined: `cvm2/cvm_ops.h:45`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_ops.c`, `cvm2/cvm_val_main.c`

### cvm_ops_ru32 (function) `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off);`
- Defined: `cvm2/cvm_ops.h:46`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_ops.c`, `cvm2/cvm_val_main.c`

### cvm_ops_r8 (function) `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out);`
- Defined: `cvm2/cvm_ops.h:47`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_jit.c`, `cvm2/cvm_ops.c`, `cvm2/cvm_val_main.c`

## cvm2/cvm_val_main.c

### val_err (function) `static void val_err(ValCtx *ctx, const char *what)`
- Defined: `cvm2/cvm_val_main.c:56`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### val_fun_err (function) `static void val_fun_err(FuncCtx *fc, const char *what)`
- Defined: `cvm2/cvm_val_main.c:61`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### code_of (function) `static const uint8_t *code_of(const CvmModuleView *v)`
- Defined: `cvm2/cvm_val_main.c:68`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### q_push (function) `static void q_push(FuncCtx *fc, size_t off)`
- Defined: `cvm2/cvm_val_main.c:72`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### q_pop (function) `static size_t q_pop(FuncCtx *fc)`
- Defined: `cvm2/cvm_val_main.c:81`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### dr_merge (function) `static int dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)`
- Defined: `cvm2/cvm_val_main.c:88`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### stack_effect (function) `static int stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...`
- Defined: `cvm2/cvm_val_main.c:103`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### check_static (function) `static int check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)`
- Defined: `cvm2/cvm_val_main.c:181`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### analyze_stack (function) `static int analyze_stack(FuncCtx *fc)`
- Defined: `cvm2/cvm_val_main.c:361`
- Doc: Abstract-interpretation stack balance: each instruction start carries a [lo,hi] interval of possible stack depths; a req
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### check_function (function) `static int check_function(FuncCtx *fc, size_t *insn_count)`
- Defined: `cvm2/cvm_val_main.c:435`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmp_func (function) `static int cmp_func(const void *a, const void *b)`
- Defined: `cvm2/cvm_val_main.c:450`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### main (function) `int main(int argc, char **argv)`
- Defined: `cvm2/cvm_val_main.c:456`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

## cvm2/cvm_view.c

### rl32 (function) `static uint32_t rl32(const uint8_t *p)`
- Defined: `cvm2/cvm_view.c:9`
- Depends on: `cvm2/cvm_view.h`

### rl16 (function) `static uint32_t rl16(const uint8_t *p)`
- Defined: `cvm2/cvm_view.c:14`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_strerror (function) `const char *cvm_view_strerror(int error_code)`
- Defined: `cvm2/cvm_view.c:18`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_open (function) `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size)`
- Defined: `cvm2/cvm_view.c:29`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_func (function) `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i)`
- Defined: `cvm2/cvm_view.c:72`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_string (function) `const char *cvm_view_string(const CvmModuleView *v, uint32_t off)`
- Defined: `cvm2/cvm_view.c:78`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_func_name (function) `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,
                             ...`
- Defined: `cvm2/cvm_view.c:87`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_func_region (function) `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,
                         size_t *be...`
- Defined: `cvm2/cvm_view.c:108`
- Depends on: `cvm2/cvm_view.h`

## cvm2/cvm_view.h

### cvm_view_open (function) `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size);`
- Defined: `cvm2/cvm_view.h:41`
- Doc: uint32_t       num_strings; uint32_t       code_size; uint32_t       string_pool_size; uint32_t       data_size; uint32_
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.h`, `cvm2/cvm_dis_main.c`, `cvm2/cvm_val_main.c`, `cvm2/cvm_view.c`

### cvm_view_strerror (function) `const char *cvm_view_strerror(int error_code);`
- Defined: `cvm2/cvm_view.h:44`
- Doc: uint32_t       data_size; uint32_t       entry_func; size_t         func_off; size_t         global_off; size_t         
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.h`, `cvm2/cvm_dis_main.c`, `cvm2/cvm_val_main.c`, `cvm2/cvm_view.c`

### cvm_view_func (function) `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i);`
- Defined: `cvm2/cvm_view.h:46`
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.h`, `cvm2/cvm_dis_main.c`, `cvm2/cvm_val_main.c`, `cvm2/cvm_view.c`

### cvm_view_string (function) `const char *cvm_view_string(const CvmModuleView *v, uint32_t off);`
- Defined: `cvm2/cvm_view.h:50`
- Doc: String from the pool, or NULL when the offset is outside it. The * pointer is only valid while the module data lives.
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.h`, `cvm2/cvm_dis_main.c`, `cvm2/cvm_val_main.c`, `cvm2/cvm_view.c`

### cvm_view_func_name (function) `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi, char *fallback, size_t cap);`
- Defined: `cvm2/cvm_view.h:53`
- Doc: String from the pool, or NULL when the offset is outside it. The * pointer is only valid while the module data lives. co
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.h`, `cvm2/cvm_dis_main.c`, `cvm2/cvm_val_main.c`, `cvm2/cvm_view.c`

### cvm_view_func_region (function) `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi, size_t *begin, size_t *end);`
- Defined: `cvm2/cvm_view.h:58`
- Doc: Code region of a function: [*begin, *end) where *end is the next * function's code offset or the end of the code section
- Depends on: `cvm2/cvm.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.h`, `cvm2/cvm_dis_main.c`, `cvm2/cvm_val_main.c`, `cvm2/cvm_view.c`

## cvm2/gen_fib_cvm.c

### emit_byte (function) `static void emit_byte(uint8_t b)`
- Defined: `cvm2/gen_fib_cvm.c:21`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### emit_u32 (function) `static void emit_u32(uint32_t v)`
- Defined: `cvm2/gen_fib_cvm.c:30`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### emit_i32 (function) `static void emit_i32(int32_t v)`
- Defined: `cvm2/gen_fib_cvm.c:37`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### patch_i32 (function) `static void patch_i32(size_t pos, int32_t val)`
- Defined: `cvm2/gen_fib_cvm.c:39`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### write_le32 (function) `static void write_le32(uint8_t *p, uint32_t v)`
- Defined: `cvm2/gen_fib_cvm.c:46`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### emit_global_inc (function) `static void emit_global_inc(void)`
- Defined: `cvm2/gen_fib_cvm.c:53`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### main (function) `int main(int argc, char *argv[])`
- Defined: `cvm2/gen_fib_cvm.c:64`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

## cvm2/gen_minimal.c

### emit_byte (function) `static void emit_byte(uint8_t b)`
- Defined: `cvm2/gen_minimal.c:14`
- Depends on: `cvm2/cvm.h`

### emit_u32 (function) `static void emit_u32(uint32_t v)`
- Defined: `cvm2/gen_minimal.c:21`
- Depends on: `cvm2/cvm.h`

### write_le32 (function) `static void write_le32(uint8_t *p, uint32_t v)`
- Defined: `cvm2/gen_minimal.c:25`
- Depends on: `cvm2/cvm.h`

### main (function) `int main(void)`
- Defined: `cvm2/gen_minimal.c:30`
- Depends on: `cvm2/cvm.h`

## cvm2/gen_test.py

### emit_byte (function) `def emit_byte(b)`
- Defined: `cvm2/gen_test.py:7`

### emit_u32 (function) `def emit_u32(v)`
- Defined: `cvm2/gen_test.py:10`

## cvm2/test.sh

### check (function)
- Defined: `cvm2/test.sh:13`

### reject (function)
- Defined: `cvm2/test.sh:24`

## gen_fib_cvm.c

### add_string (function) `static uint32_t add_string(const char *s)`
- Defined: `gen_fib_cvm.c:24`
- Depends on: `cvm.h`

### main (function) `int main(void)`
- Defined: `gen_fib_cvm.c:36`
- Depends on: `cvm.h`

### fib (function) `* return fib(n-1) + fib(n-2);`
- Defined: `gen_fib_cvm.c:7`
- Depends on: `cvm.h`
