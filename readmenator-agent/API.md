# API

## cvm.c

### cvm_error (function) `static void cvm_error(CVM *vm, const char *fmt, ...)`
- Defined: `cvm.c:12`
- Doc: cvm.c — C Virtual Machine interpreter  #include "cvm.h" #include <stdarg.h> #include <errno.h> /* ----------------------
- Depends on: `cvm.h`

### op_name (function) `static const char *op_name(uint8_t op)`
- Defined: `cvm.c:21`
- Depends on: `cvm.h`

### push (function) `static inline void push(CVM *vm, uint64_t v)`
- Defined: `cvm.c:78`
- Doc: case OP_RET: return "RET"; case OP_RET_VOID: return "RET_VOID"; case OP_ALLOC: return "ALLOC"; case OP_FREE: return "FRE
- Depends on: `cvm.h`

### pop (function) `static inline uint64_t pop(CVM *vm)`
- Defined: `cvm.c:85`
- Depends on: `cvm.h`

### peek (function) `static inline uint64_t peek(CVM *vm)`
- Defined: `cvm.c:93`
- Depends on: `cvm.h`

### push_frame (function) `static int push_frame(CVM *vm, CVM_Module *mod, uint16_t func_idx, int argc)`
- Defined: `cvm.c:102`
- Doc: cvm_error(vm, "operand stack underflow"); return 0; } return vm->stack[--vm->sp]; } static inline uint64_t peek(CVM *vm)
- Depends on: `cvm.h`

### pop_frame (function) `static void pop_frame(CVM *vm, int has_retval)`
- Defined: `cvm.c:141`
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
- Defined: `cvm.c:243`
- Depends on: `cvm.h`

### cvm_load_module_mem (function) `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name)`
- Defined: `cvm.c:267`
- Doc: free(m->natives); free(m->code); free(m->string_pool); free(m->global_mem); free(m); } free(vm->stack); free(vm->heap); 
- Depends on: `cvm.h`

### cvm_load_module (function) `int cvm_load_module(CVM *vm, const char *path)`
- Defined: `cvm.c:336`
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
- Defined: `cvm.c:750`
- Depends on: `cvm.h`

### cvm_emit_u16 (function) `void cvm_emit_u16(uint8_t **buf, size_t *cap, size_t *len, uint16_t v)`
- Defined: `cvm.c:755`
- Depends on: `cvm.h`

### cvm_emit_i32 (function) `void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v)`
- Defined: `cvm.c:760`
- Depends on: `cvm.h`

### cvm_emit_i64 (function) `void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v)`
- Defined: `cvm.c:765`
- Depends on: `cvm.h`

### main (function) `int main(int argc, char **argv)`
- Defined: `cvm.c:775`
- Doc: void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v) { for (int i = 0; i < 4; i++) cvm_emit_byte(buf, c
- Depends on: `cvm.h`

### va_start (function) `va_start(ap, fmt);`
- Defined: `cvm.c:14`
- Depends on: `cvm.h`

### fprintf (function) `fprintf(stderr, "[CVM ERROR] ");`
- Defined: `cvm.c:15`
- Depends on: `cvm.h`

### vfprintf (function) `vfprintf(stderr, fmt, ap);`
- Defined: `cvm.c:16`
- Depends on: `cvm.h`

### va_end (function) `va_end(ap);`
- Defined: `cvm.c:18`
- Depends on: `cvm.h`

### free (function) `free(fr->locals);`
- Defined: `cvm.c:152`
- Depends on: `cvm.h`

### printf (function) `printf("%lld\n", (long long)(int64_t)v);`
- Defined: `cvm.c:201`
- Doc: if (!fn) { cvm_error(vm, "cannot resolve native '%s'", name); return; } } /* Extremely simplified: we only support a few
- Depends on: `cvm.h`

### strncpy (function) `strncpy(mod->name, name ? name : "anon", sizeof(mod->name) - 1);`
- Defined: `cvm.c:293`
- Depends on: `cvm.h`

### memcpy (function) `memcpy(mod->funcs, data + off, hdr->num_functions * sizeof(CVM_FuncEntry));`
- Defined: `cvm.c:297`
- Depends on: `cvm.h`

### memset (function) `memset(mod->native_ptrs, 0, sizeof(mod->native_ptrs));`
- Defined: `cvm.c:331`
- Doc: off += hdr->code_size; mod->string_pool = malloc(hdr->string_pool_size + 1); memcpy(mod->string_pool, data + off, hdr->s
- Depends on: `cvm.h`

### perror (function) `perror(path);`
- Defined: `cvm.c:340`
- Depends on: `cvm.h`

### fseek (function) `fseek(f, 0, SEEK_END);`
- Defined: `cvm.c:343`
- Depends on: `cvm.h`

### fclose (function) `fclose(f);`
- Defined: `cvm.c:349`
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
- Defined: `cvm2/cvm.c:27`
- Doc: define CVM_DEF_STACK       65536 define CVM_DEF_FRAMES      4096 define CVM_DEF_LOCALS      512 define CVM_DEF_HEAP     
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### xcal (function) `static void *xcal(size_t n, size_t s)`
- Defined: `cvm2/cvm.c:33`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_config_default (function) `CvmConfig cvm_config_default(void)`
- Defined: `cvm2/cvm.c:39`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_create (function) `CvmState *cvm_create(const CvmConfig *config)`
- Defined: `cvm2/cvm.c:54`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_destroy (function) `void cvm_destroy(CvmState *vm)`
- Defined: `cvm2/cvm.c:93`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_strerror (function) `const char *cvm_strerror(int e)`
- Defined: `cvm2/cvm.c:112`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vp (function) `static int vp(CvmState *vm, uint64_t v)`
- Defined: `cvm2/cvm.c:136`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vo (function) `static int vo(CvmState *vm, uint64_t *v)`
- Defined: `cvm2/cvm.c:142`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### r8 (function) `static int r8(CvmState *vm, uint8_t *o)`
- Defined: `cvm2/cvm.c:148`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### r32 (function) `static int r32(CvmState *vm, uint32_t *o)`
- Defined: `cvm2/cvm.c:154`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### ri32 (function) `static int ri32(CvmState *vm, int32_t *o)`
- Defined: `cvm2/cvm.c:164`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### r64 (function) `static int r64(CvmState *vm, uint64_t *o)`
- Defined: `cvm2/cvm.c:172`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### push_frame (function) `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...`
- Defined: `cvm2/cvm.c:182`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### pop_frame (function) `static void pop_frame(CvmState *vm)`
- Defined: `cvm2/cvm.c:195`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cur_frame (function) `static CvmFrame *cur_frame(CvmState *vm)`
- Defined: `cvm2/cvm.c:202`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### range_valid (function) `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)`
- Defined: `cvm2/cvm.c:206`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### mem_valid (function) `static int mem_valid(CvmState *vm, uint64_t a, size_t s)`
- Defined: `cvm2/cvm.c:214`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### heap_alloc (function) `static uint64_t heap_alloc(CvmState *vm, size_t s)`
- Defined: `cvm2/cvm.c:226`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_heap_alloc (function) `void *cvm_heap_alloc(CvmState *vm, size_t size)`
- Defined: `cvm2/cvm.c:234`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### data_w64 (function) `static void data_w64(CvmState *vm, size_t off, uint64_t v)`
- Defined: `cvm2/cvm.c:238`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### data_r64 (function) `static uint64_t data_r64(CvmState *vm, size_t off)`
- Defined: `cvm2/cvm.c:243`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_set_args (function) `int cvm_set_args(CvmState *vm, int argc, char **argv)`
- Defined: `cvm2/cvm.c:249`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_register_native (function) `int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn)`
- Defined: `cvm2/cvm.c:282`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### find_native (function) `static int find_native(CvmState *vm, const char *name)`
- Defined: `cvm2/cvm.c:293`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_write (function) `static int64_t native_write(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:304`
- Doc: vm->num_natives++; return CVM_OK; } static int find_native(CvmState *vm, const char *name) { for (size_t i = 0; i < vm->
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_read (function) `static int64_t native_read(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:310`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_exit (function) `static int64_t native_exit(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:316`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_abort (function) `static int64_t native_abort(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:323`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_putchar (function) `static int64_t native_putchar(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:328`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_puts (function) `static int64_t native_puts(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:335`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strlen (function) `static int64_t native_strlen(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:349`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strcmp (function) `static int64_t native_strcmp(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:355`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strncmp (function) `static int64_t native_strncmp(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:361`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strcpy (function) `static int64_t native_strcpy(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:368`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strncpy (function) `static int64_t native_strncpy(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:374`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strchr (function) `static int64_t native_strchr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:381`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strstr (function) `static int64_t native_strstr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:387`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_memcpy (function) `static int64_t native_memcpy(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:394`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_memmove (function) `static int64_t native_memmove(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:401`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_memset (function) `static int64_t native_memset(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:408`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_memcmp (function) `static int64_t native_memcmp(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:414`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_malloc (function) `static int64_t native_malloc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:421`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_free (function) `static int64_t native_free(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:427`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_calloc (function) `static int64_t native_calloc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:432`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_realloc (function) `static int64_t native_realloc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:441`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_atol (function) `static int64_t native_atol(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:450`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_strtol (function) `static int64_t native_strtol(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:456`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vout_write (function) `static void vout_write(Vout *vo, const char *s, size_t n)`
- Defined: `cvm2/cvm.c:471`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vout_char (function) `static void vout_char(Vout *vo, char c)`
- Defined: `cvm2/cvm.c:483`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vout_uint (function) `static void vout_uint(Vout *vo, uint64_t v, int base, int upper)`
- Defined: `cvm2/cvm.c:485`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### vformat (function) `static void vformat(Vout *vo, const char *fmt, uint64_t *argv, int argc)`
- Defined: `cvm2/cvm.c:498`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fprintf (function) `static int64_t native_fprintf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:582`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_printf (function) `static int64_t native_printf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:592`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_sprintf (function) `static int64_t native_sprintf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:601`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_snprintf (function) `static int64_t native_snprintf(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:612`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fopen (function) `static int64_t native_fopen(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:624`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fclose (function) `static int64_t native_fclose(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:631`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fread (function) `static int64_t native_fread(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:637`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fwrite (function) `static int64_t native_fwrite(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:644`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fseek (function) `static int64_t native_fseek(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:651`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_ftell (function) `static int64_t native_ftell(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:657`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_rewind (function) `static int64_t native_rewind(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:663`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fputs (function) `static int64_t native_fputs(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:670`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fputc (function) `static int64_t native_fputc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:676`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fgetc (function) `static int64_t native_fgetc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:682`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_ungetc (function) `static int64_t native_ungetc(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:688`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_fflush (function) `static int64_t native_fflush(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:694`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_perror (function) `static int64_t native_perror(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:700`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_stderr_addr (function) `static int64_t native_stderr_addr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:711`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_stdout_addr (function) `static int64_t native_stdout_addr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:716`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_stdin_addr (function) `static int64_t native_stdin_addr(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:721`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### native_exit_core (function) `static int64_t native_exit_core(void *vm, int ac, uint64_t *av)`
- Defined: `cvm2/cvm.c:728`
- Doc: return (int64_t)(uintptr_t)stderr; } static int64_t native_stdout_addr(void *vm, int ac, uint64_t *av) { (void)vm; (void
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### register_defaults (function) `static void register_defaults(CvmState *vm)`
- Defined: `cvm2/cvm.c:735`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### rl32 (function) `static uint32_t rl32(const uint8_t *p)`
- Defined: `cvm2/cvm.c:788`
- Doc: cvm_register_native(vm, "fputc", native_fputc); cvm_register_native(vm, "fgetc", native_fgetc); cvm_register_native(vm, 
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### decompress_rle (function) `static int decompress_rle(uint8_t *dst, size_t dsz, const uint8_t *src, size_t ssz)`
- Defined: `cvm2/cvm.c:792`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_free_module (function) `static void cvm_free_module(CvmState *vm)`
- Defined: `cvm2/cvm.c:814`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_load_module (function) `int cvm_load_module(CvmState *vm, const uint8_t *d, size_t sz)`
- Defined: `cvm2/cvm.c:829`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_load_module_file (function) `int cvm_load_module_file(CvmState *vm, const char *path)`
- Defined: `cvm2/cvm.c:922`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_run_loop (function) `static int cvm_run_loop(CvmState *vm)`
- Defined: `cvm2/cvm.c:942`
- Doc: if (sz < 0) { fclose(f); return CVM_ERR_IO; } rewind(f); uint8_t *buf = (uint8_t *)xmal((size_t)sz); size_t rd = fread(b
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_run (function) `int cvm_run(CvmState *vm)`
- Defined: `cvm2/cvm.c:951`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_continue (function) `int cvm_continue(CvmState *vm)`
- Defined: `cvm2/cvm.c:990`
- Doc: rsp = top - 8; (uint64_t *)(uintptr_t)(top - 8) = 0; data_w64(vm, CVM_DATA_RSP, rsp); data_w64(vm, CVM_DATA_RBP, rsp); d
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_break_set (function) `int cvm_break_set(CvmState *vm, size_t ip)`
- Defined: `cvm2/cvm.c:993`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_break_clear (function) `int cvm_break_clear(CvmState *vm, size_t ip)`
- Defined: `cvm2/cvm.c:1002`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_break_clear_all (function) `void cvm_break_clear_all(CvmState *vm)`
- Defined: `cvm2/cvm.c:1013`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_break_hit (function) `int cvm_break_hit(const CvmState *vm)`
- Defined: `cvm2/cvm.c:1017`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_profile_begin (function) `int cvm_profile_begin(CvmState *vm)`
- Defined: `cvm2/cvm.c:1023`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_profile_end (function) `void cvm_profile_end(CvmState *vm)`
- Defined: `cvm2/cvm.c:1033`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_step (function) `int cvm_step(CvmState *vm)`
- Defined: `cvm2/cvm.c:1039`
- Doc: if (vm->code_size > vm->config.max_profile_code) return CVM_ERR_BOUNDS; if (!vm->ip_counts) vm->ip_counts = (uint32_t *)
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_exit_code (function) `int64_t cvm_exit_code(const CvmState *vm)`
- Defined: `cvm2/cvm.c:1338`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_instruction_count (function) `uint64_t cvm_instruction_count(const CvmState *vm)`
- Defined: `cvm2/cvm.c:1340`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### main (function) `int main(int argc, char *argv[])`
- Defined: `cvm2/cvm.c:1343`
- Doc: if defined(CVM_STANDALONE) && !defined(CVM_NO_MAIN)
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### memset (function) `memset(vm->op_counts, 0, sizeof(vm->op_counts));`
- Defined: `cvm2/cvm.c:88`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### free (function) `free(vm->slots);`
- Defined: `cvm2/cvm.c:99`
- Doc: endif
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### memcpy (function) `memcpy(vm->globals + off, &v, 8);`
- Defined: `cvm2/cvm.c:241`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### write (function) `write(1, &nl, 1);`
- Defined: `cvm2/cvm.c:344`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### rewind (function) `rewind((FILE *)(uintptr_t)av[0]);`
- Defined: `cvm2/cvm.c:667`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### fseek (function) `fseek(f, 0, SEEK_END);`
- Defined: `cvm2/cvm.c:926`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### fclose (function) `fclose(f);`
- Defined: `cvm2/cvm.c:932`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### fprintf (function) `fprintf(stderr, "[%08lu] ip=%zu op=0x%02X sp=%zu fr=%zu\n", (unsigned long)vm->instr_count, ip_start, op, vm->sp, vm->frame_count);`
- Defined: `cvm2/cvm.c:1046`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

## cvm2/cvm.h

### int64_t (function) `typedef int64_t (*CvmNativeFn)(void *vm, int argc, uint64_t *argv);`
- Defined: `cvm2/cvm.h:193`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_config_default (function) `CvmConfig cvm_config_default(void);`
- Defined: `cvm2/cvm.h:243`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_create (function) `CvmState *cvm_create(const CvmConfig *config);`
- Defined: `cvm2/cvm.h:245`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_destroy (function) `void cvm_destroy(CvmState *vm);`
- Defined: `cvm2/cvm.h:246`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_load_module (function) `int cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);`
- Defined: `cvm2/cvm.h:247`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_load_module_file (function) `int cvm_load_module_file(CvmState *vm, const char *path);`
- Defined: `cvm2/cvm.h:248`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_run (function) `int cvm_run(CvmState *vm);`
- Defined: `cvm2/cvm.h:249`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_continue (function) `int cvm_continue(CvmState *vm);`
- Defined: `cvm2/cvm.h:250`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_step (function) `int cvm_step(CvmState *vm);`
- Defined: `cvm2/cvm.h:251`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_exit_code (function) `int64_t cvm_exit_code(const CvmState *vm);`
- Defined: `cvm2/cvm.h:252`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_instruction_count (function) `uint64_t cvm_instruction_count(const CvmState *vm);`
- Defined: `cvm2/cvm.h:253`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_strerror (function) `const char *cvm_strerror(int error_code);`
- Defined: `cvm2/cvm.h:254`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_register_native (function) `int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn);`
- Defined: `cvm2/cvm.h:255`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_set_args (function) `int cvm_set_args(CvmState *vm, int argc, char **argv);`
- Defined: `cvm2/cvm.h:257`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_heap_alloc (function) `void *cvm_heap_alloc(CvmState *vm, size_t size);`
- Defined: `cvm2/cvm.h:258`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_break_set (function) `int cvm_break_set(CvmState *vm, size_t ip);`
- Defined: `cvm2/cvm.h:259`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_break_clear (function) `int cvm_break_clear(CvmState *vm, size_t ip);`
- Defined: `cvm2/cvm.h:261`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_break_clear_all (function) `void cvm_break_clear_all(CvmState *vm);`
- Defined: `cvm2/cvm.h:262`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_break_hit (function) `int cvm_break_hit(const CvmState *vm);`
- Defined: `cvm2/cvm.h:263`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_profile_begin (function) `int cvm_profile_begin(CvmState *vm);`
- Defined: `cvm2/cvm.h:264`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

### cvm_profile_end (function) `void cvm_profile_end(CvmState *vm);`
- Defined: `cvm2/cvm.h:265`
- Imported by: `cvm2/cvm.c`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`, `cvm2/cvm_ops.c`, `cvm2/cvm_view.h`, `cvm2/gen_fib_cvm.c`, `cvm2/gen_minimal.c`

## cvm2/cvm_dbg_main.c

### emit_stdout (function) `static int emit_stdout(void *ctx, const char *line)`
- Defined: `cvm2/cvm_dbg_main.c:28`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### func_display (function) `static const char *func_display(uint32_t fi, char *fb, size_t cap)`
- Defined: `cvm2/cvm_dbg_main.c:35`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### func_of_ip (function) `static int func_of_ip(size_t ip)`
- Defined: `cvm2/cvm_dbg_main.c:39`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### parse_u32 (function) `static int parse_u32(const char *s, uint32_t *out)`
- Defined: `cvm2/cvm_dbg_main.c:50`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### report_run (function) `static void report_run(int rc)`
- Defined: `cvm2/cvm_dbg_main.c:58`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_list (function) `static void cmd_list(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:70`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_break (function) `static void cmd_break(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:97`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_delete (function) `static void cmd_delete(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:132`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_step (function) `static void cmd_step(void)`
- Defined: `cvm2/cvm_dbg_main.c:151`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_next (function) `static void cmd_next(void)`
- Defined: `cvm2/cvm_dbg_main.c:165`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_run (function) `static void cmd_run(void)`
- Defined: `cvm2/cvm_dbg_main.c:183`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_bt (function) `static void cmd_bt(void)`
- Defined: `cvm2/cvm_dbg_main.c:193`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_stack (function) `static void cmd_stack(void)`
- Defined: `cvm2/cvm_dbg_main.c:205`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_locals (function) `static void cmd_locals(void)`
- Defined: `cvm2/cvm_dbg_main.c:212`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_info (function) `static void cmd_info(void)`
- Defined: `cvm2/cvm_dbg_main.c:224`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_profile (function) `static void cmd_profile(char *arg)`
- Defined: `cvm2/cvm_dbg_main.c:240`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmd_help (function) `static void cmd_help(void)`
- Defined: `cvm2/cvm_dbg_main.c:303`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### dispatch (function) `static void dispatch(char *line)`
- Defined: `cvm2/cvm_dbg_main.c:309`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### main (function) `int main(int argc, char **argv)`
- Defined: `cvm2/cvm_dbg_main.c:336`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### fputs (function) `fputs(line, f);`
- Defined: `cvm2/cvm_dbg_main.c:31`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### fputc (function) `fputc('\n', f);`
- Defined: `cvm2/cvm_dbg_main.c:32`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cvm_view_func_name (function) `return cvm_view_func_name(&g_view, fi, fb, cap);`
- Defined: `cvm2/cvm_dbg_main.c:37`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### printf (function) `printf("breakpoint at 0x%04zx\n", g_vm->ip);`
- Defined: `cvm2/cvm_dbg_main.c:61`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cvm_dis_function (function) `cvm_dis_function(&g_view, begin, end, emit_stdout, stdout);`
- Defined: `cvm2/cvm_dbg_main.c:95`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cvm_break_clear_all (function) `cvm_break_clear_all(g_vm);`
- Defined: `cvm2/cvm_dbg_main.c:135`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cvm_profile_end (function) `cvm_profile_end(g_vm);`
- Defined: `cvm2/cvm_dbg_main.c:297`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### fprintf (function) `fprintf(stderr, "Usage: %s <module.cvm>\n", argv[0]);`
- Defined: `cvm2/cvm_dbg_main.c:339`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### fseek (function) `fseek(f, 0, SEEK_END);`
- Defined: `cvm2/cvm_dbg_main.c:347`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### rewind (function) `rewind(f);`
- Defined: `cvm2/cvm_dbg_main.c:349`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### fclose (function) `fclose(f);`
- Defined: `cvm2/cvm_dbg_main.c:352`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### free (function) `free(g_buf);`
- Defined: `cvm2/cvm_dbg_main.c:364`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cvm_destroy (function) `cvm_destroy(g_vm);`
- Defined: `cvm2/cvm_dbg_main.c:381`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### fflush (function) `fflush(stdout);`
- Defined: `cvm2/cvm_dbg_main.c:395`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

## cvm2/cvm_dis.c

### putc_str (function) `static void putc_str(char *buf, size_t cap, size_t *n, char c)`
- Defined: `cvm2/cvm_dis.c:12`
- Doc: define CVM_DIS_LINE_MAX 160
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### puts_str (function) `static void puts_str(char *buf, size_t cap, size_t *n, const char *s)`
- Defined: `cvm2/cvm_dis.c:16`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### put_hex (function) `static void put_hex(char *buf, size_t cap, size_t *n, uint64_t v, int digits)`
- Defined: `cvm2/cvm_dis.c:20`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### put_dec (function) `static void put_dec(char *buf, size_t cap, size_t *n, int64_t v)`
- Defined: `cvm2/cvm_dis.c:34`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### pad_name (function) `static void pad_name(char *buf, size_t cap, size_t *n, const char *name)`
- Defined: `cvm2/cvm_dis.c:48`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### cvm_dis_line (function) `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end,
                 char *buf, size...`
- Defined: `cvm2/cvm_dis.c:55`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### cvm_dis_function (function) `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end,
                     CvmDi...`
- Defined: `cvm2/cvm_dis.c:152`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### cvm_dis_module (function) `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx)`
- Defined: `cvm2/cvm_dis.c:172`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

### emit (function) `emit(ctx, line);`
- Defined: `cvm2/cvm_dis.c:164`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_ops.h`

## cvm2/cvm_dis.h

### int (function) `typedef int (*CvmDisEmit)(void *ctx, const char *line);`
- Defined: `cvm2/cvm_dis.h:19`
- Doc: endif
- Depends on: `cvm2/cvm_view.h`
- Imported by: `cvm2/cvm_dbg_main.c`, `cvm2/cvm_dis.c`, `cvm2/cvm_dis_main.c`

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
- Defined: `cvm2/cvm_dis_main.c:10`
- Doc: @file cvm_dis_main.c @brief Host front-end: cvm-dis <module.cvm> renders the module as text. @license GPL-2.0-or-later  
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

### main (function) `int main(int argc, char **argv)`
- Defined: `cvm2/cvm_dis_main.c:17`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

### fputs (function) `fputs(line, f);`
- Defined: `cvm2/cvm_dis_main.c:13`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

### fputc (function) `fputc('\n', f);`
- Defined: `cvm2/cvm_dis_main.c:14`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

### fprintf (function) `fprintf(stderr, "Usage: %s <module.cvm>\n", argv[0]);`
- Defined: `cvm2/cvm_dis_main.c:20`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

### fseek (function) `fseek(f, 0, SEEK_END);`
- Defined: `cvm2/cvm_dis_main.c:28`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

### rewind (function) `rewind(f);`
- Defined: `cvm2/cvm_dis_main.c:30`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

### fclose (function) `fclose(f);`
- Defined: `cvm2/cvm_dis_main.c:33`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

### free (function) `free(buf);`
- Defined: `cvm2/cvm_dis_main.c:44`
- Depends on: `cvm2/cvm_dis.h`, `cvm2/cvm_view.h`

## cvm2/cvm_jit.c

### cvm_jit_create (function) `CvmJitState *cvm_jit_create(void)`
- Defined: `cvm2/cvm_jit.c:35`
- Doc: Callee-saved: rbx, r12-r15, rbp  #include "cvm_jit.h" #include "cvm_ops.h" #include <stdio.h> #include <stdlib.h> #inclu
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_destroy (function) `void cvm_jit_destroy(CvmJitState *jit)`
- Defined: `cvm2/cvm_jit.c:47`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### ip_map_clear (function) `static void ip_map_clear(CvmJitState *jit)`
- Defined: `cvm2/cvm_jit.c:57`
- Doc: jit->warm_threshold = 1; jit->hot_threshold = 1000; return jit; } void cvm_jit_destroy(CvmJitState *jit) { if (!jit) ret
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### ip_map_add (function) `static void ip_map_add(CvmJitState *jit, size_t bc_ip, size_t native_off)`
- Defined: `cvm2/cvm_jit.c:61`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### ip_map_lookup (function) `static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip)`
- Defined: `cvm2/cvm_jit.c:68`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### func_cache_find (function) `static JitFuncEntry *func_cache_find(CvmJitState *jit, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit.c:80`
- Doc: jit->ip_map_count++; } static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip) { for (size_t i = 0; i < jit->i
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### func_cache_add (function) `static JitFuncEntry *func_cache_add(CvmJitState *jit, uint32_t func_idx,
                        ...`
- Defined: `cvm2/cvm_jit.c:87`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### opcode_total_size (function) `static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip)`
- Defined: `cvm2/cvm_jit.c:104`
- Doc: JitTier tier) { if (jit->num_funcs_compiled >= JIT_MAX_FUNCS) return NULL; JitFuncEntry *e = &jit->func_cache[jit->num_f
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
- Defined: `cvm2/cvm_jit.c:169`
- Doc: emit_call_abs(b, fn, X10); } /* Call a C function with 3 args (rdi, rsi, rdx). static void emit_call3(JitBuf *b, void *f
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_epilogue (function) `static void emit_epilogue(JitBuf *b)`
- Defined: `cvm2/cvm_jit.c:231`
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
- Defined: `cvm2/cvm_jit.c:301`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### jit_apply_patches_local (function) `static void jit_apply_patches_local(JitBuf *b, const JitPatches *p)`
- Defined: `cvm2/cvm_jit.c:1184`
- Doc: emit_mov_reg_reg(b, XDI, JIT_REG_VM); emit_mov_reg_imm32(b, XSI, CVM_ERR_BAD_OPCODE); emit_call_abs(b, (void *)(uintptr_
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_compile_func (function) `void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit.c:1202`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_compile_module (function) `int cvm_jit_compile_module(CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1309`
- Doc: } if (jit->buf.failed) { free(ctx.patches); return NULL; } size_t native_size = jit->buf.size - native_start; func_cache
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_lookup (function) `void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit.c:1325`
- Doc: if (!vm->jit || !JIT_STATE(vm)->enabled) return CVM_OK; ip_map_clear(vm->jit); for (uint32_t i = 0; i < vm->num_funcs; i
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### find_func_for_ip (function) `static uint32_t find_func_for_ip(const CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1338`
- Doc: /* ------------------------------------------------------------------ void *cvm_jit_lookup(CvmState *vm, uint32_t func_i
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_exec_one (function) `void cvm_jit_exec_one(CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1346`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_run (function) `int cvm_jit_run(CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1376`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_stats (function) `void cvm_jit_stats(const CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1437`
- Doc: } } /* Dispatch loop while (vm->running) { cvm_jit_exec_one(vm); } return CVM_OK; } /* ---------------------------------
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_dump (function) `void cvm_jit_dump(const CvmState *vm)`
- Defined: `cvm2/cvm_jit.c:1448`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### jit_buf_init (function) `jit_buf_init(&jit->buf, 1024 * 1024);`
- Defined: `cvm2/cvm_jit.c:39`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_jit_offsets_init (function) `cvm_jit_offsets_init(&jit->offsets);`
- Defined: `cvm2/cvm_jit.c:40`
- Doc: #include <stdlib.h> #include <string.h> /* vm->jit is void* in cvm.h; cast to the concrete type here #define JIT_STATE(v
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### jit_buf_free (function) `jit_buf_free(&jit->buf);`
- Defined: `cvm2/cvm_jit.c:50`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### free (function) `free(jit);`
- Defined: `cvm2/cvm_jit.c:51`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_mov_sib_reg (function) `emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1);`
- Defined: `cvm2/cvm_jit.c:119`
- Doc: static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip) { if (ip >= code_size) return 0; const
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_inc_reg (function) `emit_inc_reg(b, JIT_REG_SP);`
- Defined: `cvm2/cvm_jit.c:120`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_dec_reg (function) `emit_dec_reg(b, JIT_REG_SP);`
- Defined: `cvm2/cvm_jit.c:125`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_mov_reg_sib (function) `emit_mov_reg_sib(b, JIT_SCRATCH1, JIT_REG_SLOTS, JIT_REG_SP, 3);`
- Defined: `cvm2/cvm_jit.c:126`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_call_abs (function) `emit_call_abs(b, fn, X10);`
- Defined: `cvm2/cvm_jit.c:148`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_push (function) `emit_push(b, XBP);`
- Defined: `cvm2/cvm_jit.c:172`
- Doc: /* Call a C function with 3 args (rdi, rsi, rdx). static void emit_call3(JitBuf *b, void *fn, int a1, int a2, int a3) { 
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_mov_reg_reg (function) `emit_mov_reg_reg(b, XBP, XSP);`
- Defined: `cvm2/cvm_jit.c:173`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_sub_reg_imm32 (function) `emit_sub_reg_imm32(b, XSP, 8);`
- Defined: `cvm2/cvm_jit.c:186`
- Doc: Align stack to 16 bytes (6 pushes = 48 bytes, already aligned from the call push of return address, so we're at 56 mod 1
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_mov_reg_mem (function) `emit_mov_reg_mem(b, JIT_REG_SLOTS, JIT_REG_VM, (int32_t)offsetof(CvmState, slots));`
- Defined: `cvm2/cvm_jit.c:193`
- Doc: Load VM state into dedicated registers. * rdi = vm (first argument) emit_mov_reg_reg(b, JIT_REG_VM, XDI); /* r12 = vm->s
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_mov32_reg_mem (function) `emit_mov32_reg_mem(b, JIT_REG_SP, JIT_REG_VM, (int32_t)offsetof(CvmState, sp));`
- Defined: `cvm2/cvm_jit.c:197`
- Doc: Load VM state into dedicated registers. * rdi = vm (first argument) emit_mov_reg_reg(b, JIT_REG_VM, XDI); /* r12 = vm->s
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_mov_reg_imm32 (function) `emit_mov_reg_imm32(b, XCX, 2);`
- Defined: `cvm2/cvm_jit.c:216`
- Doc: rax = &frames[rax] -- each frame is 32 bytes. SIB only supports scales ×1/×2/×4/×8, so pre-multiply: * rax *= 4 (shl 2),
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_shl_reg_cl (function) `emit_shl_reg_cl(b, XAX);`
- Defined: `cvm2/cvm_jit.c:217`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_lea_sib (function) `emit_lea_sib(b, JIT_SCRATCH1, JIT_REG_FRAMES, XAX, 3 /* *8 */, 0);`
- Defined: `cvm2/cvm_jit.c:218`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### memcpy (function) `memcpy(b->code + patch, &rel, 4);`
- Defined: `cvm2/cvm_jit.c:227`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_add_reg_imm32 (function) `emit_add_reg_imm32(b, XSP, 8);`
- Defined: `cvm2/cvm_jit.c:234`
- Doc: emit_mov_reg_mem(b, XAX, JIT_SCRATCH1, (int32_t)offsetof(CvmFrame, slots)); emit_mov_reg_reg(b, JIT_REG_FRAME, XAX); /* 
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_pop (function) `emit_pop(b, JIT_REG_FRAMES);`
- Defined: `cvm2/cvm_jit.c:236`
- Doc: emit_mov_reg_reg(b, JIT_REG_FRAME, XAX); /* .no_frame: { size_t target = b->size; int32_t rel = (int32_t)(target - (patc
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_xor_reg_self (function) `emit_xor_reg_self(b, XAX);`
- Defined: `cvm2/cvm_jit.c:243`
- Doc: } } static void emit_epilogue(JitBuf *b) { /* Add stack alignment back emit_add_reg_imm32(b, XSP, 8); /* Restore callee-
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_ret (function) `emit_ret(b);`
- Defined: `cvm2/cvm_jit.c:244`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_mov32_mem_reg (function) `emit_mov32_mem_reg(b, JIT_REG_VM, (int32_t)offsetof(CvmState, sp), JIT_REG_SP);`
- Defined: `cvm2/cvm_jit.c:253`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_test_reg_reg (function) `emit_test_reg_reg(b, XAX, XAX);`
- Defined: `cvm2/cvm_jit.c:273`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_nop (function) `case OP_NOP: emit_nop(b);`
- Defined: `cvm2/cvm_jit.c:318`
- Doc: JitBuf *b = ctx->b; uint8_t *code = vm->code; size_t cs = vm->code_size; size_t ip = bc_ip; if (ip >= cs) return -1; uin
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_mov_reg_imm64 (function) `emit_mov_reg_imm64(b, JIT_SCRATCH1, v);`
- Defined: `cvm2/cvm_jit.c:329`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_mov_mem_reg (function) `emit_mov_mem_reg(b, JIT_REG_FRAME, (int32_t)(idx * 8), JIT_SCRATCH1);`
- Defined: `cvm2/cvm_jit.c:382`
- Doc: ip += 4; /* rax = frame->slots[idx] emit_mov_reg_mem(b, JIT_SCRATCH1, JIT_REG_FRAME, (int32_t)(idx * 8)); emit_stack_pus
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_add_reg_reg (function) `emit_add_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);`
- Defined: `cvm2/cvm_jit.c:419`
- Doc: emit_stack_pop(b); /* rcx = vm->globals emit_mov_reg_mem(b, JIT_SCRATCH2, JIT_REG_VM, (int32_t)offsetof(CvmState, global
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_sub_reg_reg (function) `emit_sub_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);`
- Defined: `cvm2/cvm_jit.c:426`
- Doc: } /* ---- Arithmetic ---- case OP_ADD: emit_stack_pop_into(b, JIT_SCRATCH2); /* b emit_stack_pop(b);                    
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_imul_reg_reg (function) `emit_imul_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);`
- Defined: `cvm2/cvm_jit.c:433`
- Doc: emit_add_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2); emit_stack_push(b); break; case OP_SUB: emit_stack_pop_into(b, JIT_SCRA
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_cqo (function) `emit_cqo(b);`
- Defined: `cvm2/cvm_jit.c:457`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_idiv_reg (function) `emit_idiv_reg(b, XCX);`
- Defined: `cvm2/cvm_jit.c:458`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_neg_reg (function) `emit_neg_reg(b, JIT_SCRATCH1);`
- Defined: `cvm2/cvm_jit.c:494`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_and_reg_reg (function) `emit_and_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);`
- Defined: `cvm2/cvm_jit.c:503`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_or_reg_reg (function) `emit_or_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);`
- Defined: `cvm2/cvm_jit.c:510`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_xor_reg_reg (function) `emit_xor_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);`
- Defined: `cvm2/cvm_jit.c:517`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_not_reg (function) `emit_not_reg(b, JIT_SCRATCH1);`
- Defined: `cvm2/cvm_jit.c:523`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_and_reg_imm32 (function) `emit_and_reg_imm32(b, XCX, CVM_SHIFT_MASK);`
- Defined: `cvm2/cvm_jit.c:530`
- Doc: emit_stack_pop(b); emit_xor_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2); emit_stack_push(b); break; case OP_NOT: emit_stack_p
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_sar_reg_cl (function) `emit_sar_reg_cl(b, JIT_SCRATCH1);`
- Defined: `cvm2/cvm_jit.c:539`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_shr_reg_cl (function) `emit_shr_reg_cl(b, JIT_SCRATCH1);`
- Defined: `cvm2/cvm_jit.c:547`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_cmp_reg_reg (function) `emit_cmp_reg_reg(b, JIT_SCRATCH1, JIT_SCRATCH2);`
- Defined: `cvm2/cvm_jit.c:556`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_setcc (function) `emit_setcc(b, cc_signed, JIT_SCRATCH1);`
- Defined: `cvm2/cvm_jit.c:557`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_movzx_reg_mem8 (function) `emit_movzx_reg_mem8(b, JIT_SCRATCH1, JIT_SCRATCH1, 0);`
- Defined: `cvm2/cvm_jit.c:559`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_rex (function) `emit_rex(b, 1, 0, 0, 0);`
- Defined: `cvm2/cvm_jit.c:580`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit8 (function) `emit8(b, 0x0F);`
- Defined: `cvm2/cvm_jit.c:581`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_modrm (function) `emit_modrm(b, 3, JIT_SCRATCH1, JIT_SCRATCH1);`
- Defined: `cvm2/cvm_jit.c:582`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### EMIT_CMP_SIGNED (function) `case OP_CMP_EQ: EMIT_CMP_SIGNED(CC_E);`
- Defined: `cvm2/cvm_jit.c:587`
- Doc: define EMIT_CMP_UNSIGNED(cc) EMIT_CMP_SIGNED(cc)
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### EMIT_CMP_UNSIGNED (function) `case OP_CMP_ULT: EMIT_CMP_UNSIGNED(CC_B);`
- Defined: `cvm2/cvm_jit.c:594`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_jmp_buf (function) `emit_jmp_buf(b, target_bc, ctx->patches);`
- Defined: `cvm2/cvm_jit.c:620`
- Doc: emit_modrm(b, 3, JIT_SCRATCH1, JIT_SCRATCH1); emit_stack_push(b); break; /* ---- Control Flow ---- case OP_JMP: { if (ip
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_jcc_buf (function) `emit_jcc_buf(b, CC_E, target_bc, ctx->patches);`
- Defined: `cvm2/cvm_jit.c:632`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_bail_if_stopped (function) `emit_bail_if_stopped(b);`
- Defined: `cvm2/cvm_jit.c:675`
- Doc: The callee may have stopped the machine (exit/HALT/error): * unwind instead of executing the ops after the call.
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### emit_mov_mem_imm32 (function) `emit_mov_mem_imm32(b, JIT_REG_VM, (int32_t)offsetof(CvmState, running), 0);`
- Defined: `cvm2/cvm_jit.c:1162`
- Doc: emit_mov32_reg_mem(b, XAX, JIT_REG_VM, (int32_t)offsetof(CvmState, sp)); emit_test_reg_reg(b, XAX, XAX); size_t patch_ha
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### fprintf (function) `fprintf(stderr, "cvm jit: failed to compile function %u\n", i);`
- Defined: `cvm2/cvm_jit.c:1316`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### void (function) `typedef void (*JitFn)(CvmState *);`
- Defined: `cvm2/cvm_jit.c:1359`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_step (function) `extern int cvm_step(CvmState *);`
- Defined: `cvm2/cvm_jit.c:1370`
- Doc: Fall back: interpret this function's bytecodes. We run the interpreter until ip leaves this function or * vm->running be
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_ops.h`

### cvm_run (function) `extern int cvm_run(CvmState *);`
- Defined: `cvm2/cvm_jit.c:1380`
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
- Defined: `cvm2/cvm_jit_help.c:21`
- Doc: implement the same semantics as the interpreter's switch cases, but are standalone C functions with a clean ABI.  #inclu
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### xmal (function) `static void *xmal(size_t s)`
- Defined: `cvm2/cvm_jit_help.c:45`
- Doc: o->code_size            = offsetof(CvmState, code_size); o->ip                   = offsetof(CvmState, ip); o->running   
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### xcal (function) `static void *xcal(size_t n, size_t s)`
- Defined: `cvm2/cvm_jit_help.c:51`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### push_frame (function) `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...`
- Defined: `cvm2/cvm_jit_help.c:57`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### pop_frame (function) `static void pop_frame(CvmState *vm)`
- Defined: `cvm2/cvm_jit_help.c:70`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cur_frame (function) `static CvmFrame *cur_frame(CvmState *vm)`
- Defined: `cvm2/cvm_jit_help.c:77`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### range_valid (function) `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)`
- Defined: `cvm2/cvm_jit_help.c:81`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### mem_valid (function) `static int mem_valid(const CvmState *vm, uint64_t a, size_t s)`
- Defined: `cvm2/cvm_jit_help.c:89`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### heap_alloc (function) `static uint64_t heap_alloc(CvmState *vm, size_t s)`
- Defined: `cvm2/cvm_jit_help.c:101`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### find_native (function) `static int find_native(const CvmState *vm, const char *name)`
- Defined: `cvm2/cvm_jit_help.c:109`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### jit_vp (function) `static int jit_vp(CvmState *vm, uint64_t v)`
- Defined: `cvm2/cvm_jit_help.c:119`
- Doc: uint64_t a = (uint64_t)(uintptr_t)(vm->heap + vm->heap_used); vm->heap_used += al; return a; } static int find_native(co
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### jit_vo (function) `static int jit_vo(CvmState *vm, uint64_t *v)`
- Defined: `cvm2/cvm_jit_help.c:125`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_func_enter (function) `uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx)`
- Defined: `cvm2/cvm_jit_help.c:135`
- Doc: if (vm->sp >= vm->capacity) return CVM_ERR_STACK_OVER; vm->slots[vm->sp++] = v; return CVM_OK; } static int jit_vo(CvmSt
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_func_leave (function) `void cvm_jit_func_leave(CvmState *vm)`
- Defined: `cvm2/cvm_jit_help.c:144`
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_call (function) `int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc)`
- Defined: `cvm2/cvm_jit_help.c:154`
- Doc: Nothing to do in the general case; the JIT epilogue handles * register restoration.  This exists for symmetry and future
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_ret (function) `int cvm_jit_ret(CvmState *vm, uint64_t retval)`
- Defined: `cvm2/cvm_jit_help.c:175`
- Doc: CvmFrame *f = cur_frame(vm); for (int i = (int)argc - 1; i >= 0; i--) { uint64_t a; rc = jit_vo(vm, &a); if (rc) return 
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_call_native (function) `int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc)`
- Defined: `cvm2/cvm_jit_help.c:192`
- Doc: if (f && f->return_ip != 0) { size_t ret_ip = f->return_ip; pop_frame(vm); vm->ip = ret_ip; return jit_vp(vm, retval); }
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_memcheck (function) `int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size)`
- Defined: `cvm2/cvm_jit_help.c:212`
- Doc: uint64_t args[CVM_MAX_NARGS]; for (int i = (int)argc - 1; i >= 0; i--) { int rc = jit_vo(vm, &args[i]); if (rc) return r
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_alloc (function) `uint64_t cvm_jit_alloc(CvmState *vm, size_t size)`
- Defined: `cvm2/cvm_jit_help.c:220`
- Doc: return CVM_OK; } /* ------------------------------------------------------------------ /*  Memory check /* -------------
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_syscall (function) `int cvm_jit_syscall(CvmState *vm, uint8_t sn, uint8_t argc)`
- Defined: `cvm2/cvm_jit_help.c:228`
- Doc: return mem_valid(vm, addr, size); } /* ------------------------------------------------------------------ /*  ALLOC /* -
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### cvm_jit_error (function) `void cvm_jit_error(CvmState *vm, int error_code)`
- Defined: `cvm2/cvm_jit_help.c:255`
- Doc: } #ifdef CVM_STANDALONE else if (sn == CVM_SYS_WRITE) res = (int64_t)write((int)args[0], (const void *)(uintptr_t)args[1
- Depends on: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_help.h`

### free (function) `free(vm->frames[vm->frame_count].slots);`
- Defined: `cvm2/cvm_jit_help.c:74`
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
- Defined: `cvm2/cvm_jit_x86.c:34`
- Doc: define JIT_BUF_FREE(p, sz)    munmap((p), (sz)) define JIT_BUF_FAILED         MAP_FAILED endif
- Depends on: `cvm2/cvm_jit_x86.h`

### jit_buf_free (function) `void jit_buf_free(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:47`
- Depends on: `cvm2/cvm_jit_x86.h`

### jit_buf_reset (function) `void jit_buf_reset(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:55`
- Depends on: `cvm2/cvm_jit_x86.h`

### jit_buf_failed (function) `int jit_buf_failed(const JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:60`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_grow (function) `static void emit_grow(JitBuf *b, size_t need)`
- Defined: `cvm2/cvm_jit_x86.c:66`
- Doc: b->size = 0; b->capacity = 0; } void jit_buf_reset(JitBuf *b) { b->size = 0; b->failed = 0; } int jit_buf_failed(const J
- Depends on: `cvm2/cvm_jit_x86.h`

### emit8 (function) `void emit8(JitBuf *b, uint8_t v)`
- Defined: `cvm2/cvm_jit_x86.c:83`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit16 (function) `void emit16(JitBuf *b, uint16_t v)`
- Defined: `cvm2/cvm_jit_x86.c:88`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit32 (function) `void emit32(JitBuf *b, uint32_t v)`
- Defined: `cvm2/cvm_jit_x86.c:93`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit64 (function) `void emit64(JitBuf *b, uint64_t v)`
- Defined: `cvm2/cvm_jit_x86.c:98`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_bytes (function) `void emit_bytes(JitBuf *b, const void *data, size_t len)`
- Defined: `cvm2/cvm_jit_x86.c:103`
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
- Defined: `cvm2/cvm_jit_x86.c:144`
- Doc: static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm) { emit_rex(b, 1, reg_high3(reg), 0, reg_high3(rm)
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_reg_imm32 (function) `void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:151`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_reg_reg (function) `void emit_mov_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:164`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_reg_mem (function) `void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:170`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_mem_reg (function) `void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src)`
- Defined: `cvm2/cvm_jit_x86.c:177`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_movzx_reg_mem8 (function) `void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:184`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_movzx_reg_mem16 (function) `void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:191`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_movsx_reg_mem32 (function) `void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:198`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov32_reg_mem (function) `void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:205`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov32_mem_reg (function) `void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src)`
- Defined: `cvm2/cvm_jit_x86.c:213`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_lea_sib (function) `void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp)`
- Defined: `cvm2/cvm_jit_x86.c:221`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_reg_sib (function) `void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale)`
- Defined: `cvm2/cvm_jit_x86.c:258`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_sib_reg (function) `void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src)`
- Defined: `cvm2/cvm_jit_x86.c:266`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_push (function) `void emit_push(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:278`
- Doc: emit_sib(b, scale, index, base); } void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src) { /* REX.W 
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_pop (function) `void emit_pop(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:284`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_add_reg_reg (function) `void emit_add_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:294`
- Doc: if (reg_needs_rex(reg)) emit8(b, 0x41); /* REX.B=1 emit8(b, (uint8_t)(0x50 + (reg & 7))); } void emit_pop(JitBuf *b, int
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_add_reg_imm32 (function) `void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:298`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_sub_reg_reg (function) `void emit_sub_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:307`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_sub_reg_imm32 (function) `void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:311`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_imul_reg_reg (function) `void emit_imul_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:319`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_idiv_reg (function) `void emit_idiv_reg(JitBuf *b, int divisor)`
- Defined: `cvm2/cvm_jit_x86.c:326`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_cqo (function) `void emit_cqo(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:333`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_neg_reg (function) `void emit_neg_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:339`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_inc_reg (function) `void emit_inc_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:346`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_dec_reg (function) `void emit_dec_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:353`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_and_reg_imm32 (function) `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:364`
- Doc: emit8(b, 0xFF); emit_modrm(b, 3, 0, reg); } void emit_dec_reg(JitBuf *b, int reg) { /* REX.W + FF /1 r/m64 emit_rex(b, 1
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_and_reg_reg (function) `void emit_and_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:372`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_or_reg_reg (function) `void emit_or_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:376`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_xor_reg_reg (function) `void emit_xor_reg_reg(JitBuf *b, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:380`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_not_reg (function) `void emit_not_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:384`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_shl_reg_cl (function) `void emit_shl_reg_cl(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:391`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_shr_reg_cl (function) `void emit_shr_reg_cl(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:398`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_sar_reg_cl (function) `void emit_sar_reg_cl(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:405`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_xor_reg_self (function) `void emit_xor_reg_self(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:412`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_cmp_reg_reg (function) `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg)`
- Defined: `cvm2/cvm_jit_x86.c:422`
- Doc: emit_rex(b, 1, 0, 0, reg_high3(reg)); emit8(b, 0xD3); emit_modrm(b, 3, 7, reg); } void emit_xor_reg_self(JitBuf *b, int 
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_test_reg_reg (function) `void emit_test_reg_reg(JitBuf *buf, int a, int breg)`
- Defined: `cvm2/cvm_jit_x86.c:427`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_setcc (function) `void emit_setcc(JitBuf *b, int cc, int dst)`
- Defined: `cvm2/cvm_jit_x86.c:432`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_movzx_reg_reg8 (function) `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src)`
- Defined: `cvm2/cvm_jit_x86.c:441`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_jmp_rel32 (function) `size_t emit_jmp_rel32(JitBuf *b, int32_t rel)`
- Defined: `cvm2/cvm_jit_x86.c:452`
- Doc: emit8(b, (uint8_t)(0x90 + cc)); emit_modrm(b, 3, 0, dst); } void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src) { /*
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_jcc_rel32 (function) `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel)`
- Defined: `cvm2/cvm_jit_x86.c:459`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_jmp_buf (function) `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p)`
- Defined: `cvm2/cvm_jit_x86.c:467`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_jcc_buf (function) `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p)`
- Defined: `cvm2/cvm_jit_x86.c:479`
- Depends on: `cvm2/cvm_jit_x86.h`

### jit_apply_patches (function) `void jit_apply_patches(JitBuf *b, const JitPatches *p)`
- Defined: `cvm2/cvm_jit_x86.c:492`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_call_rel32 (function) `size_t emit_call_rel32(JitBuf *b, int32_t rel)`
- Defined: `cvm2/cvm_jit_x86.c:504`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_call_reg (function) `void emit_call_reg(JitBuf *b, int reg)`
- Defined: `cvm2/cvm_jit_x86.c:511`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_ret (function) `void emit_ret(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:519`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_syscall (function) `void emit_syscall(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:527`
- Doc: /* FF /2 r/m64 -- CALL r/m64 if (reg_needs_rex(reg)) emit8(b, 0x41); emit8(b, 0xFF); emit_modrm(b, 3, 2, reg); } void em
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_int3 (function) `void emit_int3(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:532`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_nop (function) `void emit_nop(JitBuf *b)`
- Defined: `cvm2/cvm_jit_x86.c:536`
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_call_abs (function) `void emit_call_abs(JitBuf *b, void *func, int scratch)`
- Defined: `cvm2/cvm_jit_x86.c:544`
- Doc: emit8(b, 0x05); } void emit_int3(JitBuf *b) { emit8(b, 0xCC); } void emit_nop(JitBuf *b) { emit8(b, 0x90); } /* --------
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_mem_imm8 (function) `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:553`
- Doc: } /* ------------------------------------------------------------------ /*  Absolute call to C function /* -------------
- Depends on: `cvm2/cvm_jit_x86.h`

### emit_mov_mem_imm32 (function) `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm)`
- Defined: `cvm2/cvm_jit_x86.c:561`
- Depends on: `cvm2/cvm_jit_x86.h`

### JIT_BUF_FREE (function) `JIT_BUF_FREE(b->code, b->capacity);`
- Defined: `cvm2/cvm_jit_x86.c:79`
- Depends on: `cvm2/cvm_jit_x86.h`

### memcpy (function) `memcpy(b->code + off, &r, 4);`
- Defined: `cvm2/cvm_jit_x86.c:501`
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

### emit_cqo (function) `void emit_cqo(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:165`
- Doc: IDIV r64  (divides RDX:RAX by r64, quotient in RAX, remainder in RDX) * Requires RDX=0 before unsigned, or use CQO for s
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_neg_reg (function) `void emit_neg_reg(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:168`
- Doc: IDIV r64  (divides RDX:RAX by r64, quotient in RAX, remainder in RDX) * Requires RDX=0 before unsigned, or use CQO for s
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_inc_reg (function) `void emit_inc_reg(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:171`
- Doc: IDIV r64  (divides RDX:RAX by r64, quotient in RAX, remainder in RDX) * Requires RDX=0 before unsigned, or use CQO for s
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_dec_reg (function) `void emit_dec_reg(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:174`
- Doc: IDIV r64  (divides RDX:RAX by r64, quotient in RAX, remainder in RDX) * Requires RDX=0 before unsigned, or use CQO for s
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_and_reg_reg (function) `void emit_and_reg_reg(JitBuf *b, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:181`
- Doc: /* NEG r64  (REX.W F7 /3) void emit_neg_reg(JitBuf *b, int reg); /* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_or_reg_reg (function) `void emit_or_reg_reg(JitBuf *b, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:184`
- Doc: /* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies) void emit_inc_reg(JitBuf 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_xor_reg_reg (function) `void emit_xor_reg_reg(JitBuf *b, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:187`
- Doc: /* DEC r64 void emit_dec_reg(JitBuf *b, int reg); /* ------------------------------------------------------------------ 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_not_reg (function) `void emit_not_reg(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:190`
- Doc: /* ------------------------------------------------------------------ /*  Bitwise /* -----------------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_shl_reg_cl (function) `void emit_shl_reg_cl(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:193`
- Doc: /* AND r64, r64 void emit_and_reg_reg(JitBuf *b, int dst, int src); /* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int d
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_shr_reg_cl (function) `void emit_shr_reg_cl(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:196`
- Doc: /* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int dst, int src); /* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int d
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_sar_reg_cl (function) `void emit_sar_reg_cl(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:199`
- Doc: /* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int dst, int src); /* NOT r64 void emit_not_reg(JitBuf *b, int reg); /*
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_xor_reg_self (function) `void emit_xor_reg_self(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:202`
- Doc: /* NOT r64 void emit_not_reg(JitBuf *b, int reg); /* SHL r64, CL  (shift left by CL) void emit_shl_reg_cl(JitBuf *b, int
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_cmp_reg_reg (function) `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg);`
- Defined: `cvm2/cvm_jit_x86.h:209`
- Doc: /* SHR r64, CL  (logical shift right) void emit_shr_reg_cl(JitBuf *b, int reg); /* SAR r64, CL  (arithmetic shift right)
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_test_reg_reg (function) `void emit_test_reg_reg(JitBuf *buf, int a, int breg);`
- Defined: `cvm2/cvm_jit_x86.h:212`
- Doc: /* SAR r64, CL  (arithmetic shift right) void emit_sar_reg_cl(JitBuf *b, int reg); /* XOR reg, reg (zero-idiom, 3 bytes)
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_setcc (function) `void emit_setcc(JitBuf *b, int cc, int dst);`
- Defined: `cvm2/cvm_jit_x86.h:215`
- Doc: /* XOR reg, reg (zero-idiom, 3 bytes) void emit_xor_reg_self(JitBuf *b, int reg); /* -----------------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_jmp_rel32 (function) `size_t emit_jmp_rel32(JitBuf *b, int32_t rel);`
- Defined: `cvm2/cvm_jit_x86.h:222`
- Doc: /* CMP r64, r64  (REX.W 39 /r) void emit_cmp_reg_reg(JitBuf *buf, int a, int breg); /* TEST r64, r64  (REX.W 85 /r) void
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_jcc_rel32 (function) `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel);`
- Defined: `cvm2/cvm_jit_x86.h:225`
- Doc: /* TEST r64, r64  (REX.W 85 /r) void emit_test_reg_reg(JitBuf *buf, int a, int breg); /* SETcc r/m8  (0F 9x /0) void emi
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_jmp_buf (function) `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p);`
- Defined: `cvm2/cvm_jit_x86.h:228`
- Doc: /* SETcc r/m8  (0F 9x /0) void emit_setcc(JitBuf *b, int cc, int dst); /* ----------------------------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_jcc_buf (function) `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p);`
- Defined: `cvm2/cvm_jit_x86.h:231`
- Doc: /* ------------------------------------------------------------------ /*  Control flow /* ------------------------------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### jit_apply_patches (function) `void jit_apply_patches(JitBuf *b, const JitPatches *p);`
- Defined: `cvm2/cvm_jit_x86.h:234`
- Doc: /* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching size_t emit_jmp_rel32(JitBuf *b, int32_t rel); /* J
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_call_rel32 (function) `size_t emit_call_rel32(JitBuf *b, int32_t rel);`
- Defined: `cvm2/cvm_jit_x86.h:237`
- Doc: /* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_call_reg (function) `void emit_call_reg(JitBuf *b, int reg);`
- Defined: `cvm2/cvm_jit_x86.h:240`
- Doc: /* JMP to absolute offset within the buffer (emits rel32, records patch) void emit_jmp_buf(JitBuf *b, size_t target, Jit
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_ret (function) `void emit_ret(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:243`
- Doc: /* Jcc to absolute offset within the buffer void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p); /* Apply
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_syscall (function) `void emit_syscall(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:250`
- Doc: /* CALL rel32  (E8 imm32) size_t emit_call_rel32(JitBuf *b, int32_t rel); /* CALL r/m64  (FF /2, 2 bytes) void emit_call
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_int3 (function) `void emit_int3(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:253`
- Doc: /* CALL r/m64  (FF /2, 2 bytes) void emit_call_reg(JitBuf *b, int reg); /* RET  (C3) void emit_ret(JitBuf *b); /* ------
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_nop (function) `void emit_nop(JitBuf *b);`
- Defined: `cvm2/cvm_jit_x86.h:256`
- Doc: /* RET  (C3) void emit_ret(JitBuf *b); /* ------------------------------------------------------------------ /*  System 
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_call_abs (function) `void emit_call_abs(JitBuf *b, void *func, int scratch);`
- Defined: `cvm2/cvm_jit_x86.h:265`
- Doc: Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch reg
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_and_reg_imm32 (function) `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm);`
- Defined: `cvm2/cvm_jit_x86.h:268`
- Doc: Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch reg
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_movzx_reg_reg8 (function) `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src);`
- Defined: `cvm2/cvm_jit_x86.h:271`
- Doc: Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch reg
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_rex (function) `void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b);`
- Defined: `cvm2/cvm_jit_x86.h:274`
- Doc: Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch reg
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_modrm (function) `void emit_modrm(JitBuf *buf, int mod, int reg, int rm);`
- Defined: `cvm2/cvm_jit_x86.h:277`
- Doc: Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used. void emit_call_a
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_mem_imm8 (function) `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm);`
- Defined: `cvm2/cvm_jit_x86.h:284`
- Doc: /* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension void emit_movzx_reg_reg8(JitBuf *buf, int dst, int
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

### emit_mov_mem_imm32 (function) `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm);`
- Defined: `cvm2/cvm_jit_x86.h:287`
- Doc: /* REX prefix: exposed for inline asm emission void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b); /* ModRM byte
- Imported by: `cvm2/cvm_jit.h`, `cvm2/cvm_jit_x86.c`

## cvm2/cvm_ops.c

### cvm_op_info (function) `const CvmOpInfo *cvm_op_info(uint8_t opcode)`
- Defined: `cvm2/cvm_ops.c:69`
- Doc: define OP_INFOS_LEN (sizeof(op_infos) / sizeof(op_infos[0]))
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

### cvm_op_name (function) `const char *cvm_op_name(uint8_t opcode)`
- Defined: `cvm2/cvm_ops.c:75`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

### cvm_ops_r8 (function) `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out)`
- Defined: `cvm2/cvm_ops.c:80`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

### cvm_ops_ru32 (function) `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off)`
- Defined: `cvm2/cvm_ops.c:86`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

### cvm_ops_ri32 (function) `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off)`
- Defined: `cvm2/cvm_ops.c:94`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_ops.h`

### cvm_ops_ri64 (function) `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off)`
- Defined: `cvm2/cvm_ops.c:98`
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
- Defined: `cvm2/cvm_val_main.c:55`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### val_fun_err (function) `static void val_fun_err(FuncCtx *fc, const char *what)`
- Defined: `cvm2/cvm_val_main.c:60`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### code_of (function) `static const uint8_t *code_of(const CvmModuleView *v)`
- Defined: `cvm2/cvm_val_main.c:67`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### q_push (function) `static void q_push(FuncCtx *fc, size_t off)`
- Defined: `cvm2/cvm_val_main.c:71`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### q_pop (function) `static size_t q_pop(FuncCtx *fc)`
- Defined: `cvm2/cvm_val_main.c:80`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### dr_merge (function) `static int dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)`
- Defined: `cvm2/cvm_val_main.c:87`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### stack_effect (function) `static int stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...`
- Defined: `cvm2/cvm_val_main.c:102`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### check_static (function) `static int check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)`
- Defined: `cvm2/cvm_val_main.c:179`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### analyze_stack (function) `static int analyze_stack(FuncCtx *fc)`
- Defined: `cvm2/cvm_val_main.c:360`
- Doc: Abstract-interpretation stack balance: each instruction start carries a [lo,hi] interval of possible stack depths; a req
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### check_function (function) `static int check_function(FuncCtx *fc, size_t *insn_count)`
- Defined: `cvm2/cvm_val_main.c:433`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### cmp_func (function) `static int cmp_func(const void *a, const void *b)`
- Defined: `cvm2/cvm_val_main.c:448`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### main (function) `int main(int argc, char **argv)`
- Defined: `cvm2/cvm_val_main.c:454`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### fprintf (function) `fprintf(stderr, "%s: error: %s\n", ctx->path, what);`
- Defined: `cvm2/cvm_val_main.c:58`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### snprintf (function) `snprintf(msg, sizeof(msg), "local index %u out of range (locals=%u) at 0x%04zx", i, cap, off);`
- Defined: `cvm2/cvm_val_main.c:191`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### fseek (function) `fseek(f, 0, SEEK_END);`
- Defined: `cvm2/cvm_val_main.c:471`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### rewind (function) `rewind(f);`
- Defined: `cvm2/cvm_val_main.c:473`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### fclose (function) `fclose(f);`
- Defined: `cvm2/cvm_val_main.c:476`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### free (function) `free(buf);`
- Defined: `cvm2/cvm_val_main.c:487`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### qsort (function) `qsort(sorted, v.num_functions, CVM_FUNC_ENTRY_SIZE, cmp_func);`
- Defined: `cvm2/cvm_val_main.c:595`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

### printf (function) `printf("function %s: %zu instructions, stack balanced\n", fn, insn);`
- Defined: `cvm2/cvm_val_main.c:639`
- Depends on: `cvm2/cvm_ops.h`, `cvm2/cvm_view.h`

## cvm2/cvm_view.c

### rl32 (function) `static uint32_t rl32(const uint8_t *p)`
- Defined: `cvm2/cvm_view.c:8`
- Doc: @file cvm_view.c @brief Module view parsing with fail-closed extent validation. @license GPL-2.0-or-later  include "cvm_
- Depends on: `cvm2/cvm_view.h`

### rl16 (function) `static uint32_t rl16(const uint8_t *p)`
- Defined: `cvm2/cvm_view.c:13`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_strerror (function) `const char *cvm_view_strerror(int error_code)`
- Defined: `cvm2/cvm_view.c:17`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_open (function) `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size)`
- Defined: `cvm2/cvm_view.c:28`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_func (function) `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i)`
- Defined: `cvm2/cvm_view.c:71`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_string (function) `const char *cvm_view_string(const CvmModuleView *v, uint32_t off)`
- Defined: `cvm2/cvm_view.c:77`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_func_name (function) `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,
                             ...`
- Defined: `cvm2/cvm_view.c:86`
- Depends on: `cvm2/cvm_view.h`

### cvm_view_func_region (function) `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,
                         size_t *be...`
- Defined: `cvm2/cvm_view.c:107`
- Depends on: `cvm2/cvm_view.h`

### memset (function) `memset(v, 0, sizeof(*v));`
- Defined: `cvm2/cvm_view.c:30`
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
- Defined: `cvm2/cvm_view.h:45`
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
- Defined: `cvm2/gen_fib_cvm.c:20`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### emit_u32 (function) `static void emit_u32(uint32_t v)`
- Defined: `cvm2/gen_fib_cvm.c:29`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### emit_i32 (function) `static void emit_i32(int32_t v)`
- Defined: `cvm2/gen_fib_cvm.c:36`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### patch_i32 (function) `static void patch_i32(size_t pos, int32_t val)`
- Defined: `cvm2/gen_fib_cvm.c:38`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### write_le32 (function) `static void write_le32(uint8_t *p, uint32_t v)`
- Defined: `cvm2/gen_fib_cvm.c:45`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### emit_global_inc (function) `static void emit_global_inc(void)`
- Defined: `cvm2/gen_fib_cvm.c:52`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### main (function) `int main(int argc, char *argv[])`
- Defined: `cvm2/gen_fib_cvm.c:63`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### memcpy (function) `memcpy(module + CVM_MODULE_HEADER_SIZE + ft + gt, code_buf, code_len);`
- Defined: `cvm2/gen_fib_cvm.c:158`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### fwrite (function) `fwrite(module, 1, total, f);`
- Defined: `cvm2/gen_fib_cvm.c:163`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### fclose (function) `fclose(f);`
- Defined: `cvm2/gen_fib_cvm.c:164`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### printf (function) `printf("Generated fib.cvm (%zu bytes total, %zu bytes code)\n", total, code_len);`
- Defined: `cvm2/gen_fib_cvm.c:165`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### fprintf (function) `fprintf(stderr, "load failed: %s\n", cvm_strerror(rc));`
- Defined: `cvm2/gen_fib_cvm.c:171`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

### cvm_destroy (function) `cvm_destroy(vm);`
- Defined: `cvm2/gen_fib_cvm.c:172`
- Depends on: `cvm2/cvm.h`, `cvm2/cvm_jit.h`

## cvm2/gen_minimal.c

### emit_byte (function) `static void emit_byte(uint8_t b)`
- Defined: `cvm2/gen_minimal.c:13`
- Depends on: `cvm2/cvm.h`

### emit_u32 (function) `static void emit_u32(uint32_t v)`
- Defined: `cvm2/gen_minimal.c:21`
- Depends on: `cvm2/cvm.h`

### write_le32 (function) `static void write_le32(uint8_t *p, uint32_t v)`
- Defined: `cvm2/gen_minimal.c:25`
- Depends on: `cvm2/cvm.h`

### main (function) `int main(void)`
- Defined: `cvm2/gen_minimal.c:29`
- Depends on: `cvm2/cvm.h`

### memcpy (function) `memcpy(module + 40 + ft + gt, code_buf, code_size);`
- Defined: `cvm2/gen_minimal.c:80`
- Depends on: `cvm2/cvm.h`

### fwrite (function) `fwrite(module, 1, total, f);`
- Defined: `cvm2/gen_minimal.c:84`
- Depends on: `cvm2/cvm.h`

### fclose (function) `fclose(f);`
- Defined: `cvm2/gen_minimal.c:85`
- Depends on: `cvm2/cvm.h`

### printf (function) `printf("Generated minimal.cvm (%zu bytes)\n", total);`
- Defined: `cvm2/gen_minimal.c:86`
- Depends on: `cvm2/cvm.h`

### cvm_destroy (function) `cvm_destroy(vm);`
- Defined: `cvm2/gen_minimal.c:104`
- Depends on: `cvm2/cvm.h`

### free (function) `free(module);`
- Defined: `cvm2/gen_minimal.c:107`
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
- Defined: `gen_fib_cvm.c:23`
- Depends on: `cvm.h`

### main (function) `int main(void)`
- Defined: `gen_fib_cvm.c:35`
- Depends on: `cvm.h`

### fib (function) `* return fib(n-1) + fib(n-2);`
- Defined: `gen_fib_cvm.c:7`
- Depends on: `cvm.h`

### memcpy (function) `memcpy(strpool + strpool_len, s, n);`
- Defined: `gen_fib_cvm.c:31`
- Depends on: `cvm.h`

### cvm_emit_byte (function) `cvm_emit_byte(&code, &code_cap, &code_len, OP_LOAD_LOCAL);`
- Defined: `gen_fib_cvm.c:66`
- Doc: push 2 sub call fib 1 add ret  uint8_t *code = NULL; size_t code_cap = 0, code_len = 0; /* fib starts at offset 0 uint32
- Depends on: `cvm.h`

### cvm_emit_i16 (function) `cvm_emit_i16 (&code, &code_cap, &code_len, 0);`
- Defined: `gen_fib_cvm.c:67`
- Depends on: `cvm.h`

### cvm_emit_i32 (function) `cvm_emit_i32 (&code, &code_cap, &code_len, 0);`
- Defined: `gen_fib_cvm.c:79`
- Depends on: `cvm.h`

### cvm_emit_u16 (function) `cvm_emit_u16 (&code, &code_cap, &code_len, 0);`
- Defined: `gen_fib_cvm.c:99`
- Depends on: `cvm.h`

### memset (function) `memset(funcs, 0, sizeof(funcs));`
- Defined: `gen_fib_cvm.c:155`
- Depends on: `cvm.h`

### fwrite (function) `fwrite(&hdr, 1, sizeof(hdr), f);`
- Defined: `gen_fib_cvm.c:173`
- Depends on: `cvm.h`

### fclose (function) `fclose(f);`
- Defined: `gen_fib_cvm.c:178`
- Depends on: `cvm.h`

### printf (function) `printf("Generated fib.cvm (%zu bytes of code)\n", code_len);`
- Defined: `gen_fib_cvm.c:179`
- Depends on: `cvm.h`

### free (function) `free(code);`
- Defined: `gen_fib_cvm.c:181`
- Depends on: `cvm.h`
