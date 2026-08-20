/**
 * @file cvm.c
 * @brief CVM interpreter implementation (module format v2).
 * @license GPL-2.0-or-later
 */
#include "cvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define CVM_DEF_STACK       65536
#define CVM_DEF_FRAMES      4096
#define CVM_DEF_LOCALS      512
#define CVM_DEF_HEAP        (16 * 1024 * 1024)
#define CVM_DEF_GLOBALS     65536
#define CVM_DEF_FUNCS       8192
#define CVM_DEF_NATIVES     512
#define CVM_DEF_CODE        (64 * 1024 * 1024)
#define CVM_DEF_PROFILE     (4 * 1024 * 1024)
#define CVM_HEAP_ALIGN      16
#define CVM_MAX_NARGS       16
#define CVM_MAX_SARGS       6

static void *xmal(size_t s) {
    void *p = malloc(s);
    if (!p) { fprintf(stderr, "cvm: oom\n"); exit(1); }
    return p;
}

static void *xcal(size_t n, size_t s) {
    void *p = calloc(n, s);
    if (!p) { fprintf(stderr, "cvm: oom\n"); exit(1); }
    return p;
}

CvmConfig cvm_config_default(void) {
    CvmConfig c;
    c.stack_capacity       = CVM_DEF_STACK;
    c.max_frames           = CVM_DEF_FRAMES;
    c.max_locals_per_frame = CVM_DEF_LOCALS;
    c.heap_size            = CVM_DEF_HEAP;
    c.max_globals          = CVM_DEF_GLOBALS;
    c.max_functions        = CVM_DEF_FUNCS;
    c.max_natives          = CVM_DEF_NATIVES;
    c.max_code_size        = CVM_DEF_CODE;
    c.max_profile_code     = CVM_DEF_PROFILE;
    c.trace_enabled        = 0;
    return c;
}

CvmState *cvm_create(const CvmConfig *config) {
    CvmConfig cfg = config ? *config : cvm_config_default();
    CvmState *vm = (CvmState *)xcal(1, sizeof(CvmState));
    vm->config = cfg;
    vm->slots = (uint64_t *)xcal(cfg.stack_capacity, sizeof(uint64_t));
    vm->capacity = cfg.stack_capacity;
    vm->sp = 0;
    vm->frames = (CvmFrame *)xcal(cfg.max_frames, sizeof(CvmFrame));
    vm->frame_count = 0;
    vm->max_frames = cfg.max_frames;
    vm->globals = NULL;
    vm->globals_size = 0;
    vm->num_globals = 0;
    vm->heap = (uint8_t *)xcal(1, cfg.heap_size);
    vm->heap_size = cfg.heap_size;
    vm->heap_used = 0;
    vm->code = NULL;
    vm->code_size = 0;
    vm->ip = 0;
    vm->running = 0;
    vm->exit_code = 0;
    vm->instr_count = 0;
    vm->natives = (CvmNative *)xcal(cfg.max_natives, sizeof(CvmNative));
    vm->num_natives = 0;
    vm->native_map = NULL;
    vm->num_module_natives = 0;
    vm->string_pool = NULL;
    vm->string_pool_size = 0;
    vm->funcs = NULL;
    vm->num_funcs = 0;
    vm->entry_func = 0;
    vm->num_breakpoints = 0;
    vm->ip_counts = NULL;
    memset(vm->op_counts, 0, sizeof(vm->op_counts));
    vm->profile_enabled = 0;
    return vm;
}

void cvm_destroy(CvmState *vm) {
    if (!vm) return;
    free(vm->slots);
    for (size_t i = 0; i < vm->frame_count; i++) free(vm->frames[i].slots);
    free(vm->frames);
    free(vm->globals);
    free(vm->heap);
    free(vm->code);
    free(vm->natives);
    free(vm->native_map);
    free(vm->string_pool);
    free(vm->funcs);
    free(vm->ip_counts);
    free(vm);
}

const char *cvm_strerror(int e) {
    switch (e) {
        case CVM_OK:              return "success";
        case CVM_ERR_ALLOC:       return "allocation failure";
        case CVM_ERR_STACK_OVER:  return "operand stack overflow";
        case CVM_ERR_STACK_UNDER: return "operand stack underflow";
        case CVM_ERR_BAD_OPCODE:  return "invalid opcode";
        case CVM_ERR_BAD_MODULE:  return "malformed module";
        case CVM_ERR_BAD_MAGIC:   return "invalid module magic";
        case CVM_ERR_BAD_VERSION: return "unsupported module version";
        case CVM_ERR_DIV_ZERO:    return "division by zero";
        case CVM_ERR_BAD_FUNC:    return "invalid function index";
        case CVM_ERR_BAD_NATIVE:  return "invalid native function";
        case CVM_ERR_BAD_ADDR:    return "invalid memory address";
        case CVM_ERR_FRAME_OVER:  return "call frame overflow";
        case CVM_ERR_HEAP_OVER:   return "heap exhaustion";
        case CVM_ERR_IO:          return "I/O error";
        case CVM_ERR_BOUNDS:      return "bounds check failure";
        case CVM_ERR_NOMATCH:     return "unresolved native symbol";
        case CVM_BREAK:           return "breakpoint";
        default:                  return "unknown error";
    }
}

static int vp(CvmState *vm, uint64_t v) {
    if (vm->sp >= vm->capacity) return CVM_ERR_STACK_OVER;
    vm->slots[vm->sp++] = v;
    return CVM_OK;
}

static int vo(CvmState *vm, uint64_t *v) {
    if (vm->sp == 0) return CVM_ERR_STACK_UNDER;
    *v = vm->slots[--vm->sp];
    return CVM_OK;
}

static int r8(CvmState *vm, uint8_t *o) {
    if (vm->ip >= vm->code_size) return CVM_ERR_BOUNDS;
    *o = vm->code[vm->ip++];
    return CVM_OK;
}

static int r32(CvmState *vm, uint32_t *o) {
    if (vm->ip + 4 > vm->code_size) return CVM_ERR_BOUNDS;
    *o = (uint32_t)vm->code[vm->ip]
       | ((uint32_t)vm->code[vm->ip+1] << 8)
       | ((uint32_t)vm->code[vm->ip+2] << 16)
       | ((uint32_t)vm->code[vm->ip+3] << 24);
    vm->ip += 4;
    return CVM_OK;
}

static int ri32(CvmState *vm, int32_t *o) {
    uint32_t u;
    int rc = r32(vm, &u);
    if (rc) return rc;
    *o = (int32_t)u;
    return CVM_OK;
}

static int r64(CvmState *vm, uint64_t *o) {
    if (vm->ip + 8 > vm->code_size) return CVM_ERR_BOUNDS;
    uint64_t v = 0;
    for (int i = 0; i < 8; i++)
        v |= (uint64_t)vm->code[vm->ip+i] << (i*8);
    vm->ip += 8;
    *o = v;
    return CVM_OK;
}

static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      uint32_t func_idx) {
    if (vm->frame_count >= vm->max_frames) return CVM_ERR_FRAME_OVER;
    if (num_locals > vm->config.max_locals_per_frame) return CVM_ERR_BOUNDS;
    CvmFrame *f = &vm->frames[vm->frame_count];
    f->capacity = num_locals > 0 ? num_locals : 1;
    f->slots = (uint64_t *)xcal(f->capacity, sizeof(uint64_t));
    f->return_ip = return_ip;
    f->func_idx = func_idx;
    vm->frame_count++;
    return CVM_OK;
}

static void pop_frame(CvmState *vm) {
    if (!vm->frame_count) return;
    vm->frame_count--;
    free(vm->frames[vm->frame_count].slots);
    vm->frames[vm->frame_count].slots = NULL;
}

static CvmFrame *cur_frame(CvmState *vm) {
    return vm->frame_count > 0 ? &vm->frames[vm->frame_count-1] : NULL;
}

static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len) {
    if (len == 0 || base == NULL) return 0;
    uint64_t b = (uint64_t)(uintptr_t)base;
    if (a < b) return 0;
    if (s > len) return 0;
    return a - b <= len - s;
}

static int mem_valid(CvmState *vm, uint64_t a, size_t s) {
    if (range_valid(a, s, vm->heap, vm->heap_size)) return 1;
    if (range_valid(a, s, vm->globals, vm->globals_size)) return 1;
    if (range_valid(a, s, (const uint8_t *)vm->string_pool, vm->string_pool_size)) return 1;
    for (size_t i = 0; i < vm->frame_count; i++) {
        CvmFrame *f = &vm->frames[i];
        if (range_valid(a, s, (const uint8_t *)f->slots, f->capacity * sizeof(uint64_t)))
            return 1;
    }
    return 0;
}

static uint64_t heap_alloc(CvmState *vm, size_t s) {
    size_t al = (s + CVM_HEAP_ALIGN - 1) & ~(size_t)(CVM_HEAP_ALIGN - 1);
    if (vm->heap_used + al > vm->heap_size) return 0;
    uint64_t a = (uint64_t)(uintptr_t)(vm->heap + vm->heap_used);
    vm->heap_used += al;
    return a;
}

void *cvm_heap_alloc(CvmState *vm, size_t size) {
    return (void *)(uintptr_t)heap_alloc(vm, size);
}

static void data_w64(CvmState *vm, size_t off, uint64_t v) {
    if (off + 8 > vm->globals_size) return;
    memcpy(vm->globals + off, &v, 8);
}

static uint64_t data_r64(CvmState *vm, size_t off) {
    uint64_t v = 0;
    if (off + 8 <= vm->globals_size) memcpy(&v, vm->globals + off, 8);
    return v;
}

int cvm_set_args(CvmState *vm, int argc, char **argv) {
    if (argc < 0) argc = 0;
    if (argc > 1024) return CVM_ERR_BOUNDS;
    /* The data section holds the stack base where the module's own startup
     * expects argc at top-8 and the argv array from top upward. ld reserves
     * that argv area at the end of the data region; older modules without
     * the stored base fall back to the fixed layout. */
    uint64_t stack_base = data_r64(vm, CVM_DATA_STACK_BASE);
    if (stack_base < CVM_MODULE_HEADER_SIZE) stack_base = CVM_DATA_STACK_BASE;
    if (vm->globals_size < stack_base) return CVM_OK;
    uint64_t stack_size = data_r64(vm, CVM_DATA_STACK_SIZE);
    if (stack_size < (size_t)(argc + 2) * 8) return CVM_ERR_BOUNDS;
    uint64_t base = (uint64_t)(uintptr_t)vm->globals;
    uint64_t top = base + stack_base + stack_size;
    if (top < base || top + (uint64_t)(argc + 1) * 8 > base + vm->globals_size)
        return CVM_ERR_BOUNDS;
    for (int i = 0; i < argc; i++) {
        size_t n = strlen(argv[i]) + 1;
        uint64_t s = heap_alloc(vm, n);
        if (!s) return CVM_ERR_HEAP_OVER;
        memcpy((void *)(uintptr_t)s, argv[i], n);
        *(uint64_t *)(uintptr_t)(top + (size_t)i * 8) = s;
    }
    *(uint64_t *)(uintptr_t)(top + (size_t)argc * 8) = 0;
    *(uint64_t *)(uintptr_t)(top - 8) = (uint64_t)argc;
    uint64_t rsp = top - 8;
    data_w64(vm, CVM_DATA_RSP, rsp);
    data_w64(vm, CVM_DATA_RBP, rsp);
    data_w64(vm, CVM_DATA_ARGC, (uint64_t)argc);
    data_w64(vm, CVM_DATA_ARGV, top);
    return CVM_OK;
}

int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn) {
    if (vm->num_natives >= vm->config.max_natives) return CVM_ERR_BOUNDS;
    size_t n = strlen(name);
    if (n >= sizeof(vm->natives[0].name)) return CVM_ERR_BOUNDS;
    CvmNative *na = &vm->natives[vm->num_natives];
    memcpy(na->name, name, n + 1);
    na->fn = fn;
    vm->num_natives++;
    return CVM_OK;
}

static int find_native(CvmState *vm, const char *name) {
    for (size_t i = 0; i < vm->num_natives; i++)
        if (strcmp(vm->natives[i].name, name) == 0) return (int)i;
    return -1;
}

/* ------------------------------------------------------------------ */
/*  Host natives (standalone builds)                                  */
/* ------------------------------------------------------------------ */
#ifdef CVM_STANDALONE

static int64_t native_write(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return -1;
    return (int64_t)write((int)av[0], (const void *)(uintptr_t)av[1], (size_t)av[2]);
}

static int64_t native_read(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return -1;
    return (int64_t)read((int)av[0], (void *)(uintptr_t)av[1], (size_t)av[2]);
}

static int64_t native_exit(void *vm, int ac, uint64_t *av) {
    CvmState *v = (CvmState *)vm;
    v->running = 0;
    v->exit_code = (int64_t)(ac > 0 ? av[0] : 0);
    return 0;
}

static int64_t native_abort(void *vm, int ac, uint64_t *av) {
    (void)ac; (void)av;
    return native_exit(vm, 0, 0);
}

static int64_t native_putchar(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    unsigned char c = (unsigned char)av[0];
    return (int64_t)write(1, &c, 1);
}

static int64_t native_puts(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    const char *s = (const char *)(uintptr_t)av[0];
    size_t n = strlen(s);
    int64_t r = (int64_t)write(1, s, n);
    if (r == (int64_t)n) {
        char nl = '\n';
        write(1, &nl, 1);
        r++;
    }
    return r;
}

static int64_t native_strlen(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    return (int64_t)strlen((const char *)(uintptr_t)av[0]);
}

static int64_t native_strcmp(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return 0;
    return (int64_t)strcmp((const char *)(uintptr_t)av[0], (const char *)(uintptr_t)av[1]);
}

static int64_t native_strncmp(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)strncmp((const char *)(uintptr_t)av[0],
                            (const char *)(uintptr_t)av[1], (size_t)av[2]);
}

static int64_t native_strcpy(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return 0;
    return (int64_t)(uintptr_t)strcpy((char *)(uintptr_t)av[0], (const char *)(uintptr_t)av[1]);
}

static int64_t native_strncpy(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)(uintptr_t)strncpy((char *)(uintptr_t)av[0],
                                       (const char *)(uintptr_t)av[1], (size_t)av[2]);
}

static int64_t native_strchr(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return 0;
    return (int64_t)(uintptr_t)strchr((const char *)(uintptr_t)av[0], (int)av[1]);
}

static int64_t native_strstr(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return 0;
    return (int64_t)(uintptr_t)strstr((const char *)(uintptr_t)av[0],
                                      (const char *)(uintptr_t)av[1]);
}

static int64_t native_memcpy(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)(uintptr_t)memcpy((void *)(uintptr_t)av[0],
                                      (const void *)(uintptr_t)av[1], (size_t)av[2]);
}

static int64_t native_memmove(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)(uintptr_t)memmove((void *)(uintptr_t)av[0],
                                       (const void *)(uintptr_t)av[1], (size_t)av[2]);
}

static int64_t native_memset(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)(uintptr_t)memset((void *)(uintptr_t)av[0], (int)av[1], (size_t)av[2]);
}

static int64_t native_memcmp(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return 0;
    return (int64_t)memcmp((const void *)(uintptr_t)av[0],
                           (const void *)(uintptr_t)av[1], (size_t)av[2]);
}

static int64_t native_malloc(void *vm, int ac, uint64_t *av) {
    CvmState *v = (CvmState *)vm;
    if (ac < 1) return 0;
    return (int64_t)heap_alloc(v, (size_t)av[0]);
}

static int64_t native_free(void *vm, int ac, uint64_t *av) {
    (void)vm; (void)ac; (void)av;
    return 0;
}

static int64_t native_calloc(void *vm, int ac, uint64_t *av) {
    CvmState *v = (CvmState *)vm;
    if (ac < 2) return 0;
    size_t n = (size_t)av[0] * (size_t)av[1];
    uint64_t a = heap_alloc(v, n);
    if (a) memset((void *)(uintptr_t)a, 0, n);
    return (int64_t)a;
}

static int64_t native_realloc(void *vm, int ac, uint64_t *av) {
    CvmState *v = (CvmState *)vm;
    if (ac < 2) return 0;
    size_t n = (size_t)av[1];
    uint64_t a = heap_alloc(v, n);
    if (a) memcpy((void *)(uintptr_t)a, (const void *)(uintptr_t)av[0], n);
    return (int64_t)a;
}

static int64_t native_atol(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return 0;
    return (int64_t)strtol((const char *)(uintptr_t)av[0], NULL, 10);
}

static int64_t native_strtol(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return 0;
    int base = ac > 1 ? (int)av[1] : 10;
    return (int64_t)strtol((const char *)(uintptr_t)av[0], NULL, base);
}

/* ---- mini printf engine ---- */
typedef struct {
    FILE   *f;
    char   *buf;
    size_t  cap;
    size_t  len;
} Vout;

static void vout_write(Vout *vo, const char *s, size_t n) {
    if (!vo) return;
    if (vo->f) { fwrite(s, 1, n, vo->f); return; }
    if (vo->buf) {
        size_t room = vo->cap - vo->len;
        if (n > room) n = room;
        if (n) { memcpy(vo->buf + vo->len, s, n); vo->len += n; }
        return;
    }
    (void)write(1, s, n);
}

static void vout_char(Vout *vo, char c) { vout_write(vo, &c, 1); }

static void vout_uint(Vout *vo, uint64_t v, int base, int upper) {
    char tmp[24];
    int i = 23;
    tmp[i--] = 0;
    if (v == 0) tmp[i--] = '0';
    while (v) {
        int d = (int)(v % (uint64_t)base);
        v /= (uint64_t)base;
        tmp[i--] = (char)(d < 10 ? '0' + d : (upper ? 'A' : 'a') + d - 10);
    }
    vout_write(vo, tmp + i + 1, (size_t)(23 - i - 1));
}

static void vformat(Vout *vo, const char *fmt, uint64_t *argv, int argc) {
    int ai = 0;
    while (*fmt) {
        if (*fmt != '%') { vout_char(vo, *fmt++); continue; }
        fmt++;
        if (*fmt == '%') { vout_char(vo, '%'); fmt++; continue; }
        int left = 0, zero = 0, plus = 0, space = 0;
        for (;;) {
            if (*fmt == '-') { left = 1; fmt++; }
            else if (*fmt == '0') { zero = 1; fmt++; }
            else if (*fmt == '+') { plus = 1; fmt++; }
            else if (*fmt == ' ') { space = 1; fmt++; }
            else break;
        }
        int width = 0;
        while (*fmt >= '0' && *fmt <= '9') { width = width * 10 + (*fmt - '0'); fmt++; }
        int prec = -1;
        if (*fmt == '.') {
            fmt++;
            prec = 0;
            while (*fmt >= '0' && *fmt <= '9') { prec = prec * 10 + (*fmt - '0'); fmt++; }
        }
        int is_long = 0;
        while (*fmt == 'l') { is_long = 1; fmt++; }
        (void)is_long;
        char c = *fmt++;
        uint64_t val = ai < argc ? argv[ai++] : 0;
        if (c == 's') {
            const char *s = (const char *)(uintptr_t)val;
            if (!s) s = "(null)";
            size_t n = strlen(s);
            if (prec >= 0 && (size_t)prec < n) n = (size_t)prec;
            int pad = width - (int)n;
            if (pad > 0 && !left) while (pad-- > 0) vout_char(vo, ' ');
            vout_write(vo, s, n);
            if (pad > 0 && left) while (pad-- > 0) vout_char(vo, ' ');
        } else if (c == 'd' || c == 'i') {
            int64_t sv = (int64_t)val;
            int ndig = 1;
            uint64_t m = sv < 0 ? (uint64_t)(-sv) : (uint64_t)sv;
            if (prec > 0 && prec > ndig) ndig = prec;
            int slen = (sv < 0 || plus || space) ? 1 : 0;
            int pad = width - ndig - slen;
            if (pad > 0 && !left && !zero) while (pad-- > 0) vout_char(vo, ' ');
            if (sv < 0) vout_char(vo, '-');
            else if (plus) vout_char(vo, '+');
            else if (space) vout_char(vo, ' ');
            if (pad > 0 && !left && zero) while (pad-- > 0) vout_char(vo, '0');
            int lead = 0;
            if (prec > 0) {
                int d2 = 1;
                uint64_t t = m;
                while (t >= 10) { t /= 10; d2++; }
                lead = prec - d2;
                while (lead-- > 0) vout_char(vo, '0');
            }
            if (prec != 0 || m != 0) vout_uint(vo, m, 10, 0);
            if (pad > 0 && left) while (pad-- > 0) vout_char(vo, ' ');
        } else if (c == 'u') {
            uint64_t uv = val;
            int pad = width - 1;
            if (pad > 0 && !left && !zero) while (pad-- > 0) vout_char(vo, ' ');
            if (pad > 0 && !left && zero) while (pad-- > 0) vout_char(vo, '0');
            vout_uint(vo, uv, 10, 0);
            if (pad > 0 && left) while (pad-- > 0) vout_char(vo, ' ');
        } else if (c == 'x' || c == 'X') {
            int pad = width - 1;
            if (pad > 0 && !left && !zero) while (pad-- > 0) vout_char(vo, ' ');
            if (pad > 0 && !left && zero) while (pad-- > 0) vout_char(vo, '0');
            vout_uint(vo, val, 16, c == 'X');
            if (pad > 0 && left) while (pad-- > 0) vout_char(vo, ' ');
        } else if (c == 'o') {
            vout_uint(vo, val, 8, 0);
        } else if (c == 'p') {
            vout_write(vo, "0x", 2);
            vout_uint(vo, val, 16, 0);
        } else if (c == 'c') {
            vout_char(vo, (char)(val & 0xFF));
        } else {
            vout_char(vo, c);
        }
    }
}

static int64_t native_fprintf(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return -1;
    Vout vo;
    vo.f = (FILE *)(uintptr_t)av[0];
    vo.buf = NULL; vo.cap = 0; vo.len = 0;
    vformat(&vo, (const char *)(uintptr_t)av[1], av + 2, ac - 2);
    return 0;
}

static int64_t native_printf(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    Vout vo;
    vo.f = NULL; vo.buf = NULL; vo.cap = 0; vo.len = 0;
    vformat(&vo, (const char *)(uintptr_t)av[0], av + 1, ac - 1);
    return 0;
}

static int64_t native_sprintf(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return -1;
    char *buf = (char *)(uintptr_t)av[0];
    Vout vo;
    vo.f = NULL; vo.buf = buf; vo.cap = (size_t)-1; vo.len = 0;
    vformat(&vo, (const char *)(uintptr_t)av[1], av + 2, ac - 2);
    buf[vo.len] = 0;
    return (int64_t)vo.len;
}

static int64_t native_snprintf(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return -1;
    char *buf = (char *)(uintptr_t)av[0];
    size_t n = (size_t)av[1];
    Vout vo;
    vo.f = NULL; vo.buf = buf; vo.cap = n > 0 ? n - 1 : 0; vo.len = 0;
    vformat(&vo, (const char *)(uintptr_t)av[2], av + 3, ac - 3);
    if (n > 0) buf[vo.len < n ? vo.len : n - 1] = 0;
    return (int64_t)vo.len;
}

static int64_t native_fopen(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return 0;
    return (int64_t)(uintptr_t)fopen((const char *)(uintptr_t)av[0],
                                     (const char *)(uintptr_t)av[1]);
}

static int64_t native_fclose(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    return (int64_t)fclose((FILE *)(uintptr_t)av[0]);
}

static int64_t native_fread(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 4) return 0;
    return (int64_t)fread((void *)(uintptr_t)av[0], (size_t)av[1], (size_t)av[2],
                          (FILE *)(uintptr_t)av[3]);
}

static int64_t native_fwrite(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 4) return 0;
    return (int64_t)fwrite((const void *)(uintptr_t)av[0], (size_t)av[1], (size_t)av[2],
                           (FILE *)(uintptr_t)av[3]);
}

static int64_t native_fseek(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 3) return -1;
    return (int64_t)fseek((FILE *)(uintptr_t)av[0], (long)av[1], (int)av[2]);
}

static int64_t native_ftell(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    return (int64_t)ftell((FILE *)(uintptr_t)av[0]);
}

static int64_t native_rewind(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    rewind((FILE *)(uintptr_t)av[0]);
    return 0;
}

static int64_t native_fputs(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return -1;
    return (int64_t)fputs((const char *)(uintptr_t)av[0], (FILE *)(uintptr_t)av[1]);
}

static int64_t native_fputc(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return -1;
    return (int64_t)fputc((int)av[0], (FILE *)(uintptr_t)av[1]);
}

static int64_t native_fgetc(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    return (int64_t)fgetc((FILE *)(uintptr_t)av[0]);
}

static int64_t native_ungetc(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 2) return -1;
    return (int64_t)ungetc((int)av[0], (FILE *)(uintptr_t)av[1]);
}

static int64_t native_fflush(void *vm, int ac, uint64_t *av) {
    (void)vm;
    FILE *f = ac > 0 ? (FILE *)(uintptr_t)av[0] : NULL;
    return (int64_t)fflush(f);
}

static int64_t native_perror(void *vm, int ac, uint64_t *av) {
    (void)vm;
    if (ac < 1) return -1;
    const char *s = (const char *)(uintptr_t)av[0];
    Vout vo;
    vo.f = stderr; vo.buf = NULL; vo.cap = 0; vo.len = 0;
    vout_write(&vo, s, strlen(s));
    vout_write(&vo, "\n", 1);
    return 0;
}

static int64_t native_stderr_addr(void *vm, int ac, uint64_t *av) {
    (void)vm; (void)ac; (void)av;
    return (int64_t)(uintptr_t)stderr;
}

static int64_t native_stdout_addr(void *vm, int ac, uint64_t *av) {
    (void)vm; (void)ac; (void)av;
    return (int64_t)(uintptr_t)stdout;
}

static int64_t native_stdin_addr(void *vm, int ac, uint64_t *av) {
    (void)vm; (void)ac; (void)av;
    return (int64_t)(uintptr_t)stdin;
}

#endif /* CVM_STANDALONE */

static int64_t native_exit_core(void *vm, int ac, uint64_t *av) {
    CvmState *v = (CvmState *)vm;
    v->running = 0;
    v->exit_code = (int64_t)(ac > 0 ? av[0] : 0);
    return 0;
}

static void register_defaults(CvmState *vm) {
    if (vm->num_natives > 0) return;
    cvm_register_native(vm, "exit", native_exit_core);
#ifdef CVM_STANDALONE
    cvm_register_native(vm, "write", native_write);
    cvm_register_native(vm, "read", native_read);
    cvm_register_native(vm, "putchar", native_putchar);
    cvm_register_native(vm, "puts", native_puts);
    cvm_register_native(vm, "abort", native_abort);
    cvm_register_native(vm, "strlen", native_strlen);
    cvm_register_native(vm, "strcmp", native_strcmp);
    cvm_register_native(vm, "strncmp", native_strncmp);
    cvm_register_native(vm, "strcpy", native_strcpy);
    cvm_register_native(vm, "strncpy", native_strncpy);
    cvm_register_native(vm, "strchr", native_strchr);
    cvm_register_native(vm, "strstr", native_strstr);
    cvm_register_native(vm, "memcpy", native_memcpy);
    cvm_register_native(vm, "memmove", native_memmove);
    cvm_register_native(vm, "memset", native_memset);
    cvm_register_native(vm, "memcmp", native_memcmp);
    cvm_register_native(vm, "malloc", native_malloc);
    cvm_register_native(vm, "free", native_free);
    cvm_register_native(vm, "calloc", native_calloc);
    cvm_register_native(vm, "realloc", native_realloc);
    cvm_register_native(vm, "atol", native_atol);
    cvm_register_native(vm, "strtol", native_strtol);
    cvm_register_native(vm, "printf", native_printf);
    cvm_register_native(vm, "fprintf", native_fprintf);
    cvm_register_native(vm, "sprintf", native_sprintf);
    cvm_register_native(vm, "snprintf", native_snprintf);
    cvm_register_native(vm, "fopen", native_fopen);
    cvm_register_native(vm, "fclose", native_fclose);
    cvm_register_native(vm, "fread", native_fread);
    cvm_register_native(vm, "fwrite", native_fwrite);
    cvm_register_native(vm, "fseek", native_fseek);
    cvm_register_native(vm, "ftell", native_ftell);
    cvm_register_native(vm, "rewind", native_rewind);
    cvm_register_native(vm, "fputs", native_fputs);
    cvm_register_native(vm, "fputc", native_fputc);
    cvm_register_native(vm, "fgetc", native_fgetc);
    cvm_register_native(vm, "ungetc", native_ungetc);
    cvm_register_native(vm, "fflush", native_fflush);
    cvm_register_native(vm, "perror", native_perror);
    cvm_register_native(vm, "stderr_addr", native_stderr_addr);
    cvm_register_native(vm, "stdout_addr", native_stdout_addr);
    cvm_register_native(vm, "stdin_addr", native_stdin_addr);
#endif
}

/* ------------------------------------------------------------------ */
/*  Module loader                                                     */
/* ------------------------------------------------------------------ */
static uint32_t rl32(const uint8_t *p) {
    return (uint32_t)p[0] | ((uint32_t)p[1]<<8)
         | ((uint32_t)p[2]<<16) | ((uint32_t)p[3]<<24);
}

static int decompress_rle(uint8_t *dst, size_t dsz, const uint8_t *src, size_t ssz) {
    size_t o = 0, i = 0;
    while (o < dsz) {
        if (i >= ssz) return -1;
        uint8_t t = src[i++];
        if (t == 254) {
            if (i >= ssz) return -1;
            size_t n = src[i++];
            if (n > dsz - o || i + n > ssz) return -1;
            memcpy(dst + o, src + i, n);
            i += n;
            o += n;
        } else {
            size_t n = (size_t)t + 1;
            if (n > dsz - o) return -1;
            memset(dst + o, 0, n);
            o += n;
        }
    }
    return o == dsz ? 0 : -1;
}

static void cvm_free_module(CvmState *vm) {
    free(vm->globals);       vm->globals = NULL;
    free(vm->code);          vm->code = NULL;
    free(vm->native_map);    vm->native_map = NULL;
    free(vm->string_pool);   vm->string_pool = NULL;
    free(vm->funcs);         vm->funcs = NULL;
    vm->globals_size = 0;
    vm->num_globals = 0;
    vm->code_size = 0;
    vm->num_module_natives = 0;
    vm->string_pool_size = 0;
    vm->num_funcs = 0;
    vm->entry_func = 0;
}

int cvm_load_module(CvmState *vm, const uint8_t *d, size_t sz) {
    if (sz < CVM_MODULE_HEADER_SIZE) return CVM_ERR_BAD_MODULE;
    cvm_free_module(vm);
    register_defaults(vm);    if (d[0]!=CVM_MAGIC_0 || d[1]!=CVM_MAGIC_1 ||
        d[2]!=CVM_MAGIC_2 || d[3]!=CVM_MAGIC_3) return CVM_ERR_BAD_MAGIC;
    if ((uint16_t)(d[4]|(d[5]<<8)) != CVM_VERSION_MAJOR) return CVM_ERR_BAD_VERSION;
    if ((uint16_t)(d[6]|(d[7]<<8)) > CVM_VERSION_MINOR) return CVM_ERR_BAD_VERSION;

    uint32_t nf = rl32(d+8);
    uint32_t ng = rl32(d+12);
    uint32_t nn = rl32(d+16);
    uint32_t ns = rl32(d+20);
    uint32_t cs = rl32(d+24);
    uint32_t sp = rl32(d+28);
    uint32_t ds = rl32(d+32);
    uint32_t ef = rl32(d+36);

    if (nf > vm->config.max_functions) return CVM_ERR_BAD_MODULE;
    if (ng > vm->config.max_globals) return CVM_ERR_BAD_MODULE;
    if (nn > vm->config.max_natives) return CVM_ERR_BAD_MODULE;
    if (cs > vm->config.max_code_size) return CVM_ERR_BAD_MODULE;

    size_t ft = (size_t)nf * CVM_FUNC_ENTRY_SIZE;
    size_t gt = (size_t)ng * CVM_GLOBAL_ENTRY_SIZE;
    size_t nt = (size_t)nn * CVM_NATIVE_ENTRY_SIZE;
    size_t st = (size_t)ns * CVM_STRING_ENTRY_SIZE;
    size_t off = CVM_MODULE_HEADER_SIZE;
    size_t code_off = off + ft + gt + nt + st;
    size_t pool_off = sz - sp;

    if (pool_off < code_off + cs || pool_off > sz) return CVM_ERR_BAD_MODULE;

    vm->funcs = (CvmFuncEntry *)xcal(nf > 0 ? nf : 1, sizeof(CvmFuncEntry));
    vm->num_funcs = nf;
    for (uint32_t i = 0; i < nf; i++) {
        const uint8_t *fe = d + off + (size_t)i * CVM_FUNC_ENTRY_SIZE;
        vm->funcs[i].name_off   = rl32(fe + 0);
        vm->funcs[i].code_off   = rl32(fe + 4);
        vm->funcs[i].num_locals = rl32(fe + 8);
        vm->funcs[i].argc       = rl32(fe + 12);
        vm->funcs[i].flags      = rl32(fe + 16);
        if (vm->funcs[i].code_off > cs) return CVM_ERR_BAD_MODULE;
        if (vm->funcs[i].num_locals > vm->config.max_locals_per_frame)
            return CVM_ERR_BAD_MODULE;
    }

    size_t data_size = 0;
    for (uint32_t i = 0; i < ng; i++) {
        const uint8_t *ge = d + off + ft + (size_t)i * CVM_GLOBAL_ENTRY_SIZE;
        uint64_t gs = (uint64_t)rl32(ge + 4);
        gs = (gs + 7) & ~(uint64_t)7;
        if (gs > (uint64_t)((size_t)-1) - data_size) return CVM_ERR_BAD_MODULE;
        data_size += (size_t)gs;
    }
    vm->num_globals = ng;
    if ((size_t)ds > data_size) data_size = (size_t)ds;
    vm->globals_size = data_size;
    vm->globals = data_size ? (uint8_t *)xcal(1, data_size) : NULL;
    if (ds > 0) {
        size_t comp = pool_off - (code_off + cs);
        if (decompress_rle(vm->globals, ds, d + code_off + cs, comp) != 0)
            return CVM_ERR_BAD_MODULE;
    }

    vm->native_map = nn ? (int32_t *)xmal((size_t)nn * sizeof(int32_t)) : NULL;
    vm->num_module_natives = nn;
    for (uint32_t i = 0; i < nn; i++) {
        const uint8_t *ne = d + off + ft + gt + (size_t)i * CVM_NATIVE_ENTRY_SIZE;
        uint32_t name_off = rl32(ne + 0);
        int32_t host = -1;
        if (sp > 0 && name_off < sp) {
            const char *name = (const char *)d + pool_off + name_off;
            if (name + strlen(name) < (const char *)d + pool_off + sp)
                host = (int32_t)find_native(vm, name);
        }
        vm->native_map[i] = host;
    }

    vm->code = (uint8_t *)xmal(cs > 0 ? cs : 1);
    vm->code_size = cs;
    memcpy(vm->code, d + code_off, cs);

    if (sp > 0) {
        vm->string_pool = (char *)xmal(sp + 1);
        memcpy(vm->string_pool, d + pool_off, sp);
        vm->string_pool[sp] = 0;
        vm->string_pool_size = sp;
    }

    vm->entry_func = ef;
    return CVM_OK;
}

int cvm_load_module_file(CvmState *vm, const char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) return CVM_ERR_IO;
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    if (sz < 0) { fclose(f); return CVM_ERR_IO; }
    rewind(f);
    uint8_t *buf = (uint8_t *)xmal((size_t)sz);
    size_t rd = fread(buf, 1, (size_t)sz, f);
    fclose(f);
    if (rd != (size_t)sz) { free(buf); return CVM_ERR_IO; }
    int rc = cvm_load_module(vm, buf, (size_t)sz);
    free(buf);
    return rc;
}

/* ------------------------------------------------------------------ */
/*  Interpreter                                                       */
/* ------------------------------------------------------------------ */
static int cvm_run_loop(CvmState *vm) {
    int rc = CVM_OK;
    while (vm->running) {
        if (cvm_break_hit(vm)) return CVM_BREAK;
        rc = cvm_step(vm);
        if (rc) break;
    }
    return rc;
}

int cvm_run(CvmState *vm) {
    register_defaults(vm);
    vm->running = 1;
    vm->exit_code = 0;
    vm->instr_count = 0;
    vm->sp = 0;
    while (vm->frame_count) pop_frame(vm);
    int rc = CVM_OK;

    if (vm->entry_func >= vm->num_funcs) return CVM_ERR_BAD_FUNC;
    uint32_t entry_locals = vm->funcs[vm->entry_func].num_locals;
    rc = push_frame(vm, entry_locals > 0 ? entry_locals : 16, 0,
                    vm->entry_func);
    if (rc) return rc;
    vm->ip = vm->funcs[vm->entry_func].code_off;

    uint64_t stack_base = data_r64(vm, CVM_DATA_STACK_BASE);
    if (stack_base < CVM_MODULE_HEADER_SIZE) stack_base = CVM_DATA_STACK_BASE;
    if (vm->globals_size >= stack_base + 8) {
        uint64_t stack_size = data_r64(vm, CVM_DATA_STACK_SIZE);
        if (stack_size > 0 && stack_size <= vm->globals_size - stack_base) {
            uint64_t rsp = data_r64(vm, CVM_DATA_RSP);
            uint64_t top = (uint64_t)(uintptr_t)(vm->globals + stack_base) + stack_size;
            if (rsp == 0 || rsp > top || rsp + 8 < top - stack_size) {
                rsp = top - 8;
                *(uint64_t *)(uintptr_t)(top - 8) = 0;
                data_w64(vm, CVM_DATA_RSP, rsp);
                data_w64(vm, CVM_DATA_RBP, rsp);
                data_w64(vm, CVM_DATA_ARGC, 0);
                data_w64(vm, CVM_DATA_ARGV, 0);
            }
        }
    }

    return cvm_run_loop(vm);
}

/* Run after a breakpoint: same loop, no state reset. */
int cvm_continue(CvmState *vm) {
    return cvm_run_loop(vm);
}

int cvm_break_set(CvmState *vm, size_t ip) {
    if (ip >= vm->code_size) return CVM_ERR_BOUNDS;
    for (size_t i = 0; i < vm->num_breakpoints; i++)
        if (vm->breakpoints[i].ip == ip) return CVM_OK;
    if (vm->num_breakpoints >= CVM_MAX_BREAKPOINTS) return CVM_ERR_BOUNDS;
    vm->breakpoints[vm->num_breakpoints++].ip = ip;
    return CVM_OK;
}

int cvm_break_clear(CvmState *vm, size_t ip) {
    for (size_t i = 0; i < vm->num_breakpoints; i++) {
        if (vm->breakpoints[i].ip == ip) {
            vm->breakpoints[i] = vm->breakpoints[vm->num_breakpoints - 1];
            vm->num_breakpoints--;
            return CVM_OK;
        }
    }
    return CVM_ERR_NOMATCH;
}

void cvm_break_clear_all(CvmState *vm) {
    vm->num_breakpoints = 0;
}

int cvm_break_hit(const CvmState *vm) {
    for (size_t i = 0; i < vm->num_breakpoints; i++)
        if (vm->breakpoints[i].ip == vm->ip) return 1;
    return 0;
}

int cvm_profile_begin(CvmState *vm) {
    if (vm->code_size > vm->config.max_profile_code) return CVM_ERR_BOUNDS;
    if (!vm->ip_counts)
        vm->ip_counts = (uint32_t *)xcal(vm->code_size > 0 ? vm->code_size : 1,
                                         sizeof(uint32_t));
    memset(vm->op_counts, 0, sizeof(vm->op_counts));
    vm->profile_enabled = 1;
    return CVM_OK;
}

void cvm_profile_end(CvmState *vm) {
    vm->profile_enabled = 0;
}

/* Execute exactly one instruction at vm->ip. */
int cvm_step(CvmState *vm) {
    size_t ip_start = vm->ip;
    uint8_t op;
    int rc = r8(vm, &op);
    if (rc) return rc;

    if (vm->config.trace_enabled) {
        fprintf(stderr, "[%08lu] ip=%zu op=0x%02X sp=%zu fr=%zu\n",
                (unsigned long)vm->instr_count, ip_start, op,
                vm->sp, vm->frame_count);
    }
    vm->instr_count++;
    if (vm->profile_enabled) {
        vm->op_counts[op]++;
        vm->ip_counts[ip_start]++;
    }

    switch (op) {
        case OP_NOP:
            break;
        case OP_PUSH_IMM64: {
            uint64_t v; rc = r64(vm, &v);
            if (!rc) rc = vp(vm, v);
            break;
        }
        case OP_PUSH_IMM32: {
            int32_t v; rc = ri32(vm, &v);
            if (!rc) rc = vp(vm, (uint64_t)(int64_t)v);
            break;
        }
        case OP_PUSH_IMM8: {
            uint8_t v; rc = r8(vm, &v);
            if (!rc) rc = vp(vm, (uint64_t)(int64_t)(int8_t)v);
            break;
        }
        case OP_PUSH_ZERO: rc = vp(vm, 0); break;
        case OP_PUSH_ONE:  rc = vp(vm, 1); break;

        case OP_PUSH_LOCAL: {
            uint32_t i; rc = r32(vm, &i); if (rc) break;
            CvmFrame *f = cur_frame(vm);
            if (!f || i >= f->capacity) { rc = CVM_ERR_BOUNDS; break; }
            rc = vp(vm, f->slots[i]);
            break;
        }
        case OP_STORE_LOCAL: {
            uint32_t i; rc = r32(vm, &i); if (rc) break;
            CvmFrame *f = cur_frame(vm);
            if (!f || i >= f->capacity) { rc = CVM_ERR_BOUNDS; break; }
            uint64_t v; rc = vo(vm, &v);
            if (!rc) f->slots[i] = v;
            break;
        }
        case OP_PUSH_GLOBAL: {
            uint32_t i; rc = r32(vm, &i); if (rc) break;
            if ((size_t)i * 8 + 8 > vm->globals_size) { rc = CVM_ERR_BOUNDS; break; }
            uint64_t v;
            memcpy(&v, vm->globals + (size_t)i * 8, 8);
            rc = vp(vm, v);
            break;
        }
        case OP_STORE_GLOBAL: {
            uint32_t i; rc = r32(vm, &i); if (rc) break;
            if ((size_t)i * 8 + 8 > vm->globals_size) { rc = CVM_ERR_BOUNDS; break; }
            uint64_t v; rc = vo(vm, &v);
            if (!rc) memcpy(vm->globals + (size_t)i * 8, &v, 8);
            break;
        }
        case OP_LEA_DATA: {
            uint32_t o; rc = r32(vm, &o); if (rc) break;
            if (o > vm->globals_size) { rc = CVM_ERR_BOUNDS; break; }
            rc = vp(vm, (uint64_t)(uintptr_t)(vm->globals + o));
            break;
        }

        case OP_ADD: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a+b); break; }
        case OP_SUB: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a-b); break; }
        case OP_MUL: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a*b); break; }
        case OP_DIV: {
            uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if ((int64_t)b==0) { rc=CVM_ERR_DIV_ZERO; break; }
            rc=vp(vm,(uint64_t)((int64_t)a/(int64_t)b));
            break;
        }
        case OP_MOD: {
            uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if ((int64_t)b==0) { rc=CVM_ERR_DIV_ZERO; break; }
            rc=vp(vm,(uint64_t)((int64_t)a%(int64_t)b));
            break;
        }
        case OP_NEG: { uint64_t a; rc=vo(vm,&a); if(!rc) rc=vp(vm,(uint64_t)(-(int64_t)a)); break; }
        case OP_AND: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a&b); break; }
        case OP_OR:  { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a|b); break; }
        case OP_XOR: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a^b); break; }
        case OP_NOT: { uint64_t a; rc=vo(vm,&a); if(!rc) rc=vp(vm,~a); break; }
        case OP_SHL: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a<<(b&CVM_SHIFT_MASK)); break; }
        case OP_SHR: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(uint64_t)((int64_t)a>>(b&CVM_SHIFT_MASK))); break; }
        case OP_USHR: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,a>>(b&CVM_SHIFT_MASK)); break; }

        case OP_CMP_EQ: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a==(int64_t)b?1:0); break; }
        case OP_CMP_NE: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a!=(int64_t)b?1:0); break; }
        case OP_CMP_LT: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a<(int64_t)b?1:0); break; }
        case OP_CMP_LE: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a<=(int64_t)b?1:0); break; }
        case OP_CMP_GT: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a>(int64_t)b?1:0); break; }
        case OP_CMP_GE: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(int64_t)a>=(int64_t)b?1:0); break; }
        case OP_CMP_ULT: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(uint64_t)a<(uint64_t)b?1:0); break; }
        case OP_CMP_ULE: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(uint64_t)a<=(uint64_t)b?1:0); break; }
        case OP_CMP_UGT: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(uint64_t)a>(uint64_t)b?1:0); break; }
        case OP_CMP_UGE: { uint64_t b,a; rc=vo(vm,&b); if(rc) break; rc=vo(vm,&a); if(!rc) rc=vp(vm,(uint64_t)a>=(uint64_t)b?1:0); break; }
        case OP_LNOT: { uint64_t a; rc=vo(vm,&a); if(!rc) rc=vp(vm,a==0?1:0); break; }

        case OP_JMP: {
            int32_t o; rc = ri32(vm, &o); if (rc) break;
            int64_t t = (int64_t)vm->ip + o;
            if (t < 0 || (uint64_t)t > vm->code_size) { rc = CVM_ERR_BOUNDS; break; }
            vm->ip = (size_t)t;
            break;
        }
        case OP_JZ: {
            int32_t o; rc = ri32(vm, &o); if (rc) break;
            uint64_t v; rc = vo(vm, &v); if (rc) break;
            if (v == 0) {
                int64_t t = (int64_t)vm->ip + o;
                if (t < 0 || (uint64_t)t > vm->code_size) { rc = CVM_ERR_BOUNDS; break; }
                vm->ip = (size_t)t;
            }
            break;
        }
        case OP_JNZ: {
            int32_t o; rc = ri32(vm, &o); if (rc) break;
            uint64_t v; rc = vo(vm, &v); if (rc) break;
            if (v != 0) {
                int64_t t = (int64_t)vm->ip + o;
                if (t < 0 || (uint64_t)t > vm->code_size) { rc = CVM_ERR_BOUNDS; break; }
                vm->ip = (size_t)t;
            }
            break;
        }

        case OP_CALL: {
            uint32_t fi; rc = r32(vm, &fi); if (rc) break;
            uint8_t na; rc = r8(vm, &na); if (rc) break;
            if (fi >= vm->num_funcs) { rc = CVM_ERR_BAD_FUNC; break; }
            CvmFuncEntry *fe = &vm->funcs[fi];
            rc = push_frame(vm, fe->num_locals > 0 ? fe->num_locals : 16,
                            vm->ip, fi);
            if (rc) break;
            CvmFrame *f = cur_frame(vm);
            for (int i = (int)na - 1; i >= 0; i--) {
                uint64_t a; rc = vo(vm, &a); if (rc) break;
                f->slots[i] = a;
            }
            if (rc) break;
            vm->ip = fe->code_off;
            break;
        }

        case OP_RET: {
            uint64_t rv = 0;
            if (vm->sp > 0) rv = vm->slots[--vm->sp];
            CvmFrame *f = cur_frame(vm);
            if (f && f->return_ip != 0) {
                size_t ret_ip = f->return_ip;
                pop_frame(vm);
                vm->ip = ret_ip;
                rc = vp(vm, rv);
            } else {
                vm->running = 0;
                vm->exit_code = (int64_t)rv;
            }
            break;
        }

        case OP_CALL_NATIVE: {
            uint32_t ni; rc = r32(vm, &ni); if (rc) break;
            uint8_t na; rc = r8(vm, &na); if (rc) break;
            if (ni >= vm->num_module_natives) { rc = CVM_ERR_BAD_NATIVE; break; }
            int32_t host = vm->native_map[ni];
            if (host < 0) { rc = CVM_ERR_NOMATCH; break; }
            if (na > CVM_MAX_NARGS) { rc = CVM_ERR_BOUNDS; break; }
            uint64_t args[CVM_MAX_NARGS];
            for (int i = (int)na-1; i >= 0; i--) { rc = vo(vm, &args[i]); if (rc) break; }
            if (rc) break;
            CvmNativeFn fn = vm->natives[host].fn;
            int64_t res = fn(vm, (int)na, args);
            if (vm->running) rc = vp(vm, (uint64_t)res);
            break;
        }

        case OP_LOAD8: {
            uint64_t a; rc=vo(vm,&a); if(rc) break;
            if(!mem_valid(vm,a,1)){rc=CVM_ERR_BAD_ADDR;break;}
            rc=vp(vm,(uint64_t)(int64_t)*(int8_t*)(uintptr_t)a);
            break;
        }
        case OP_LOAD16: {
            uint64_t a; rc=vo(vm,&a); if(rc) break;
            if(!mem_valid(vm,a,2)){rc=CVM_ERR_BAD_ADDR;break;}
            rc=vp(vm,(uint64_t)(int64_t)*(int16_t*)(uintptr_t)a);
            break;
        }
        case OP_LOAD32: {
            uint64_t a; rc=vo(vm,&a); if(rc) break;
            if(!mem_valid(vm,a,4)){rc=CVM_ERR_BAD_ADDR;break;}
            rc=vp(vm,(uint64_t)(int64_t)*(int32_t*)(uintptr_t)a);
            break;
        }
        case OP_LOAD64: {
            uint64_t a; rc=vo(vm,&a); if(rc) break;
            if(!mem_valid(vm,a,8)){rc=CVM_ERR_BAD_ADDR;break;}
            rc=vp(vm,*(uint64_t*)(uintptr_t)a);
            break;
        }
        case OP_STORE8: {
            uint64_t v,a; rc=vo(vm,&v); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if(!mem_valid(vm,a,1)){rc=CVM_ERR_BAD_ADDR;break;}
            *(uint8_t*)(uintptr_t)a=(uint8_t)v;
            break;
        }
        case OP_STORE16: {
            uint64_t v,a; rc=vo(vm,&v); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if(!mem_valid(vm,a,2)){rc=CVM_ERR_BAD_ADDR;break;}
            *(uint16_t*)(uintptr_t)a=(uint16_t)v;
            break;
        }
        case OP_STORE32: {
            uint64_t v,a; rc=vo(vm,&v); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if(!mem_valid(vm,a,4)){rc=CVM_ERR_BAD_ADDR;break;}
            *(uint32_t*)(uintptr_t)a=(uint32_t)v;
            break;
        }
        case OP_STORE64: {
            uint64_t v,a; rc=vo(vm,&v); if(rc) break; rc=vo(vm,&a); if(rc) break;
            if(!mem_valid(vm,a,8)){rc=CVM_ERR_BAD_ADDR;break;}
            *(uint64_t*)(uintptr_t)a=v;
            break;
        }
        case OP_LEA_LOCAL: {
            uint32_t i; rc=r32(vm,&i); if(rc) break;
            CvmFrame *f=cur_frame(vm);
            if(!f||i>=f->capacity){rc=CVM_ERR_BOUNDS;break;}
            rc=vp(vm,(uint64_t)(uintptr_t)&f->slots[i]);
            break;
        }
        case OP_LEA_GLOBAL: {
            uint32_t i; rc=r32(vm,&i); if(rc) break;
            if ((size_t)i * 8 + 8 > vm->globals_size) { rc = CVM_ERR_BOUNDS; break; }
            rc=vp(vm,(uint64_t)(uintptr_t)(vm->globals + (size_t)i * 8));
            break;
        }
        case OP_ALLOC: {
            uint64_t s; rc=vo(vm,&s); if(rc) break;
            uint64_t a=heap_alloc(vm,(size_t)s);
            if(!a){rc=CVM_ERR_HEAP_OVER;break;}
            rc=vp(vm,a);
            break;
        }
        case OP_FREE: { uint64_t a; rc=vo(vm,&a); (void)a; break; }
        case OP_SYSCALL: {
            uint8_t sn,na;
            rc=r8(vm,&sn); if(rc) break;
            rc=r8(vm,&na); if(rc) break;
            if(na>CVM_MAX_SARGS){rc=CVM_ERR_BOUNDS;break;}
            uint64_t args[CVM_MAX_SARGS];
            for(int i=(int)na-1;i>=0;i--){rc=vo(vm,&args[i]);if(rc)break;}
            if(rc) break;
            int64_t res=-1;
            if(sn==CVM_SYS_EXIT){vm->running=0;vm->exit_code=(int64_t)args[0];res=(int64_t)args[0];}
#ifdef CVM_STANDALONE
            else if(sn==CVM_SYS_WRITE)
                res=(int64_t)write((int)args[0],(const void*)(uintptr_t)args[1],(size_t)args[2]);
            else if(sn==CVM_SYS_READ)
                res=(int64_t)read((int)args[0],(void*)(uintptr_t)args[1],(size_t)args[2]);
#endif
            if(vm->running) rc=vp(vm,(uint64_t)res);
            break;
        }
        case OP_HALT:
            vm->running = 0;
            if (vm->sp > 0) vm->exit_code = (int64_t)vm->slots[vm->sp-1];
            break;
        default:
            rc = CVM_ERR_BAD_OPCODE;
            break;
    }
    return rc;
}

int64_t cvm_exit_code(const CvmState *vm) { return vm->exit_code; }
uint64_t cvm_instruction_count(const CvmState *vm) { return vm->instr_count; }

#if defined(CVM_STANDALONE) && !defined(CVM_NO_MAIN)
int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <module.cvm> [--trace] [args...]\n", argv[0]);
        return 1;
    }
    CvmConfig cfg = cvm_config_default();
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--trace") == 0) cfg.trace_enabled = 1;
    }
    CvmState *vm = cvm_create(&cfg);
    int rc = cvm_load_module_file(vm, argv[1]);
    if (rc != CVM_OK) {
        fprintf(stderr, "cvm: load: %s\n", cvm_strerror(rc));
        cvm_destroy(vm);
        return 1;
    }
    /* The module sees a Linux-style argv: argv[0] is the module path and
     * the remaining words are the program arguments. The x86 startup code
     * every ld-compiled module carries reads argc/argv from the stack that
     * cvm_set_args builds, so both must be passed here. */
    int prog_argc = 1;
    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "--trace") != 0) prog_argc++;
    }
    {
        char **pargv = (char **)malloc(sizeof(char *) * (size_t)prog_argc);
        if (!pargv) { cvm_destroy(vm); return 1; }
        int k = 0;
        pargv[k++] = argv[1];
        for (int i = 2; i < argc; i++)
            if (strcmp(argv[i], "--trace") != 0) pargv[k++] = argv[i];
        rc = cvm_set_args(vm, prog_argc, pargv);
        free(pargv);
        if (rc != CVM_OK) {
            fprintf(stderr, "cvm: args: %s\n", cvm_strerror(rc));
            cvm_destroy(vm);
            return 1;
        }
    }
    rc = cvm_run(vm);
    if (rc != CVM_OK) {
        fprintf(stderr, "cvm: runtime: %s (ip=%zu)\n", cvm_strerror(rc), vm->ip);
        cvm_destroy(vm);
        return 1;
    }
    int64_t ec = cvm_exit_code(vm);
    if (cfg.trace_enabled)
        fprintf(stderr, "cvm: %lu instructions\n", (unsigned long)cvm_instruction_count(vm));
    cvm_destroy(vm);
    return (int)ec;
}
#endif
