/**
 * @file cvm_dbg_main.c
 * @brief Host front-end: cvmdbg <module.cvm> — a gdb-style debugger for
 *        CVM modules: disassembly, breakpoints, single stepping, frame
 *        backtraces and instruction profiling. Scriptable over stdin:
 *        every command is one line, so test suites drive it with pipes.
 * @license GPL-2.0-or-later
 */
#include "cvm.h"
#include "cvm_view.h"
#include "cvm_dis.h"
#include "cvm_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define DBG_LINE_MAX 256
#define DBG_PROFILE_TOP 10

static CvmState *g_vm;
static CvmModuleView g_view;
static uint8_t *g_buf;
static size_t g_buf_sz;
static int g_started;
static int g_interactive;
static int g_quit;

static int emit_stdout(void *ctx, const char *line) {
    FILE *f = (FILE *)ctx;
    fputs(line, f);
    fputc('\n', f);
    return 0;
}

static const char *func_display(uint32_t fi, char *fb, size_t cap) {
    return cvm_view_func_name(&g_view, fi, fb, cap);
}

static int func_of_ip(size_t ip) {
    for (uint32_t i = 0; i < g_view.num_functions; i++) {
        const CvmFuncEntry *fe = cvm_view_func(&g_view, i);
        if (!fe) continue;
        size_t begin = 0, end = 0;
        if (cvm_view_func_region(&g_view, i, &begin, &end) != CVM_OK) continue;
        if (ip >= begin && ip < end) return (int)i;
    }
    return -1;
}

static int parse_u32(const char *s, uint32_t *out) {
    char *end = NULL;
    unsigned long v = strtoul(s, &end, 0);
    if (!end || *end != 0) return -1;
    *out = (uint32_t)v;
    return 0;
}

static void report_run(int rc) {
    if (rc == CVM_BREAK) {
        printf("breakpoint at 0x%04zx\n", g_vm->ip);
    } else if (rc == CVM_OK) {
        printf("program exited: %lld (%llu instructions)\n",
               (long long)cvm_exit_code(g_vm),
               (unsigned long long)cvm_instruction_count(g_vm));
    } else {
        printf("runtime error: %s (ip=0x%04zx)\n", cvm_strerror(rc), g_vm->ip);
    }
}

static void cmd_list(char *arg) {
    uint32_t fi;
    if (arg && arg[0]) {
        if (parse_u32(arg, &fi) != 0 || fi >= g_view.num_functions) {
            printf("no such function\n");
            return;
        }
    } else {
        int cur = func_of_ip(g_vm->ip);
        if (cur < 0) {
            printf("not running\n");
            return;
        }
        fi = (uint32_t)cur;
    }
    const CvmFuncEntry *fe = cvm_view_func(&g_view, fi);
    size_t begin = 0, end = 0;
    if (!fe || cvm_view_func_region(&g_view, fi, &begin, &end) != CVM_OK) {
        printf("cannot list function\n");
        return;
    }
    char fb[64];
    printf("; Function %u: %s (locals=%u, argc=%u)\n",
           fi, func_display(fi, fb, sizeof(fb)), fe->num_locals, fe->argc);
    cvm_dis_function(&g_view, begin, end, emit_stdout, stdout);
}

static void cmd_break(char *arg) {
    if (!arg || !arg[0]) {
        printf("usage: break <func|0xADDR>\n");
        return;
    }
    size_t ip = (size_t)-1;
    if (arg[0] == '0' && (arg[1] == 'x' || arg[1] == 'X')) {
        uint32_t a;
        if (parse_u32(arg, &a) == 0) ip = (size_t)a;
    } else {
        uint32_t fi;
        if (parse_u32(arg, &fi) == 0 && fi < g_view.num_functions)
            ip = cvm_view_func(&g_view, fi)->code_off;
        else {
            for (uint32_t i = 0; i < g_view.num_functions; i++) {
                char fb[64];
                if (strcmp(func_display(i, fb, sizeof(fb)), arg) == 0) {
                    ip = cvm_view_func(&g_view, i)->code_off;
                    break;
                }
            }
        }
    }
    if (ip == (size_t)-1 || ip >= g_view.code_size) {
        printf("cannot resolve breakpoint\n");
        return;
    }
    int rc = cvm_break_set(g_vm, ip);
    if (rc != CVM_OK) {
        printf("cannot set breakpoint: %s\n", cvm_strerror(rc));
        return;
    }
    printf("breakpoint at 0x%04zx\n", ip);
}

static void cmd_delete(char *arg) {
    if (arg && strcmp(arg, "all") == 0) {
        cvm_break_clear_all(g_vm);
        printf("all breakpoints cleared\n");
        return;
    }
    size_t ip = (size_t)-1;
    if (arg && arg[0]) {
        uint32_t a;
        if (parse_u32(arg, &a) == 0) ip = (size_t)a;
    }
    if (ip == (size_t)-1) {
        printf("usage: delete <0xADDR|all>\n");
        return;
    }
    int rc = cvm_break_clear(g_vm, ip);
    printf(rc == CVM_OK ? "breakpoint cleared\n" : "no such breakpoint\n");
}

static void cmd_step(void) {
    if (!g_started) {
        printf("not started: run first\n");
        return;
    }
    int rc = cvm_step(g_vm);
    if (rc == CVM_OK) {
        printf("ip=0x%04zx sp=%zu fr=%zu\n", g_vm->ip, g_vm->sp,
               g_vm->frame_count);
    } else {
        report_run(rc);
    }
}

static void cmd_next(void) {
    if (!g_started) {
        printf("not started: run first\n");
        return;
    }
    size_t depth = g_vm->frame_count;
    int rc = CVM_OK;
    while (g_vm->running && g_vm->frame_count > depth) {
        rc = cvm_step(g_vm);
        if (rc) break;
    }
    if (rc == CVM_OK)
        printf("ip=0x%04zx sp=%zu fr=%zu\n", g_vm->ip, g_vm->sp,
               g_vm->frame_count);
    else
        report_run(rc);
}

static void cmd_run(void) {
    if (!g_started) {
        int rc = cvm_run(g_vm);
        g_started = 1;
        report_run(rc);
        return;
    }
    report_run(cvm_continue(g_vm));
}

static void cmd_bt(void) {
    printf("frames (innermost first):\n");
    for (size_t i = g_vm->frame_count; i > 0; i--) {
        CvmFrame *f = &g_vm->frames[i - 1];
        char fb[64];
        printf("  #%zu %s return=0x%04zx locals=%zu\n",
               g_vm->frame_count - i, func_display(f->func_idx, fb, sizeof(fb)),
               f->return_ip, f->capacity);
    }
    if (g_vm->frame_count == 0) printf("  (none)\n");
}

static void cmd_stack(void) {
    printf("operand stack (depth %zu):\n", g_vm->sp);
    for (size_t i = g_vm->sp; i > 0; i--)
        printf("  [%zu] 0x%016llx\n", g_vm->sp - i,
               (unsigned long long)g_vm->slots[i - 1]);
}

static void cmd_locals(void) {
    if (g_vm->frame_count == 0) {
        printf("no frame\n");
        return;
    }
    CvmFrame *f = &g_vm->frames[g_vm->frame_count - 1];
    char fb[64];
    printf("locals of %s:\n", func_display(f->func_idx, fb, sizeof(fb)));
    for (size_t i = 0; i < f->capacity; i++)
        printf("  [%zu] 0x%016llx\n", i, (unsigned long long)f->slots[i]);
}

static void cmd_info(void) {
    printf("functions=%u globals=%u natives=%u code=%u bytes\n",
           g_view.num_functions, g_view.num_globals, g_view.num_natives,
           g_view.code_size);
    printf("ip=0x%04zx sp=%zu frames=%zu instructions=%llu\n", g_vm->ip,
           g_vm->sp, g_vm->frame_count,
           (unsigned long long)cvm_instruction_count(g_vm));
    if (g_vm->num_breakpoints == 0) {
        printf("breakpoints: none\n");
        return;
    }
    printf("breakpoints:\n");
    for (size_t i = 0; i < g_vm->num_breakpoints; i++)
        printf("  %zu: 0x%04zx\n", i, g_vm->breakpoints[i].ip);
}

static void cmd_profile(char *arg) {
    if (!arg || !arg[0] || strcmp(arg, "show") == 0) {
        if (!g_vm->ip_counts) {
            printf("no profile data: run 'profile run' first\n");
            return;
        }
        printf("hottest code paths (%u instructions):\n",
               (unsigned)DBG_PROFILE_TOP);
        size_t top_ip[DBG_PROFILE_TOP];
        uint32_t top_cnt[DBG_PROFILE_TOP];
        size_t top_n = 0;
        for (size_t i = 0; i < g_vm->code_size; i++) {
            uint32_t c = g_vm->ip_counts[i];
            if (c == 0) continue;
            size_t slot = top_n;
            if (top_n >= DBG_PROFILE_TOP) {
                size_t min_i = 0;
                for (size_t k = 1; k < top_n; k++)
                    if (top_cnt[k] < top_cnt[min_i]) min_i = k;
                if (c <= top_cnt[min_i]) continue;
                slot = min_i;
            }
            top_ip[slot] = i;
            top_cnt[slot] = c;
            if (top_n < DBG_PROFILE_TOP) top_n++;
        }
        for (size_t a = 0; a < top_n; a++) {
            size_t min_i = a;
            for (size_t b = a + 1; b < top_n; b++)
                if (top_cnt[b] > top_cnt[min_i]) min_i = b;
            size_t ti = top_ip[min_i];
            top_ip[min_i] = top_ip[a];
            top_cnt[min_i] = top_cnt[a];
            char fb[64];
            const char *name = "";
            int fi = func_of_ip(ti);
            if (fi >= 0) name = func_display((uint32_t)fi, fb, sizeof(fb));
            printf("  0x%04zx %s: %u\n", ti, name, top_cnt[a]);
        }
        printf("opcode histogram:\n");
        for (int op = 0; op < 256; op++) {
            uint32_t c = g_vm->op_counts[op];
            if (c == 0) continue;
            const char *name = cvm_op_name((uint8_t)op);
            if (!name) name = "???";
            printf("  %-14s %u\n", name, c);
        }
        return;
    }
    if (strcmp(arg, "run") == 0) {
        int rc = cvm_profile_begin(g_vm);
        if (rc != CVM_OK) {
            printf("cannot profile: %s\n", cvm_strerror(rc));
            return;
        }
        int r2 = g_started ? cvm_continue(g_vm) : (g_started = 1, cvm_run(g_vm));
        cvm_profile_end(g_vm);
        report_run(r2);
        return;
    }
    printf("usage: profile [run|show]\n");
}

static void cmd_help(void) {
    printf("commands: list [func] break <func|0xADDR> delete <0xADDR|all>\n");
    printf("          run step next bt stack locals info\n");
    printf("          profile [run|show] quit\n");
}

static void dispatch(char *line) {
    char *arg = line;
    while (*arg == ' ' || *arg == '\t') arg++;
    char *cmd = arg;
    while (*arg && *arg != ' ' && *arg != '\t') arg++;
    if (*arg) {
        *arg++ = 0;
        while (*arg == ' ' || *arg == '\t') arg++;
    }
    if (cmd[0] == 0) return;
    if (strcmp(cmd, "list") == 0) cmd_list(arg);
    else if (strcmp(cmd, "break") == 0 || strcmp(cmd, "b") == 0) cmd_break(arg);
    else if (strcmp(cmd, "delete") == 0 || strcmp(cmd, "d") == 0) cmd_delete(arg);
    else if (strcmp(cmd, "run") == 0) cmd_run();
    else if (strcmp(cmd, "continue") == 0 || strcmp(cmd, "c") == 0) cmd_run();
    else if (strcmp(cmd, "step") == 0 || strcmp(cmd, "s") == 0) cmd_step();
    else if (strcmp(cmd, "next") == 0 || strcmp(cmd, "n") == 0) cmd_next();
    else if (strcmp(cmd, "bt") == 0 || strcmp(cmd, "backtrace") == 0) cmd_bt();
    else if (strcmp(cmd, "stack") == 0) cmd_stack();
    else if (strcmp(cmd, "locals") == 0) cmd_locals();
    else if (strcmp(cmd, "info") == 0) cmd_info();
    else if (strcmp(cmd, "profile") == 0) cmd_profile(arg);
    else if (strcmp(cmd, "help") == 0 || strcmp(cmd, "h") == 0) cmd_help();
    else if (strcmp(cmd, "quit") == 0 || strcmp(cmd, "q") == 0) g_quit = 1;
    else printf("unknown command: %s\n", cmd);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <module.cvm>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        fprintf(stderr, "cvmdbg: cannot open %s\n", argv[1]);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);
    if (sz < 0) {
        fprintf(stderr, "cvmdbg: cannot size %s\n", argv[1]);
        fclose(f);
        return 1;
    }
    g_buf = (uint8_t *)malloc((size_t)sz ? (size_t)sz : 1);
    if (!g_buf) {
        fprintf(stderr, "cvmdbg: out of memory\n");
        fclose(f);
        return 1;
    }
    g_buf_sz = (size_t)sz;
    if (fread(g_buf, 1, g_buf_sz, f) != g_buf_sz) {
        fprintf(stderr, "cvmdbg: read error\n");
        free(g_buf);
        fclose(f);
        return 1;
    }
    fclose(f);

    int rc = cvm_view_open(&g_view, g_buf, g_buf_sz);
    if (rc != CVM_OK) {
        fprintf(stderr, "cvmdbg: %s\n", cvm_strerror(rc));
        free(g_buf);
        return 1;
    }
    CvmConfig cfg = cvm_config_default();
    g_vm = cvm_create(&cfg);
    rc = cvm_load_module(g_vm, g_buf, g_buf_sz);
    if (rc != CVM_OK) {
        fprintf(stderr, "cvmdbg: load: %s\n", cvm_strerror(rc));
        cvm_destroy(g_vm);
        free(g_buf);
        return 1;
    }
    g_started = 0;
    g_quit = 0;
    g_interactive = isatty(0);
    if (g_interactive)
        printf("cvmdbg: %s loaded, type 'help'\n", argv[1]);

    char line[DBG_LINE_MAX];
    while (!g_quit) {
        if (g_interactive) {
            printf("(cvmdbg) ");
            fflush(stdout);
        }
        if (!fgets(line, sizeof(line), stdin)) break;
        size_t n = strlen(line);
        while (n > 0 && (line[n - 1] == '\n' || line[n - 1] == '\r'))
            line[--n] = 0;
        dispatch(line);
    }
    int64_t ec = cvm_exit_code(g_vm);
    cvm_destroy(g_vm);
    free(g_buf);
    return (int)ec;
}
