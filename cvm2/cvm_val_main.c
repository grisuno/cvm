/**
 * @file cvm_val_main.c
 * @brief Host front-end: cvm-validate <module.cvm> statically verifies a
 *        module before it is allowed to run. Fail-closed: every section
 *        extent, index, jump target and stack effect is checked, and any
 *        violation is a hard error with a diagnostic.
 * @license GPL-2.0-or-later
 */
#include "cvm_view.h"
#include "cvm_ops.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CVM_VAL_MAX_FUNCS   8192
#define CVM_VAL_MAX_GLOBALS 65536
#define CVM_VAL_MAX_NATIVES 512
#define CVM_VAL_MAX_CODE    (64U * 1024U * 1024U)
#define CVM_VAL_MAX_LOCALS  512
#define CVM_VAL_MAX_ARGS    16
/* Saturation bound for the [lo,hi] stack-depth intervals: every pop
 * needs at most CVM_VAL_MAX_ARGS items, so depths beyond this bound
 * carry no further information, and saturating here makes loop-carried
 * interval growth converge in a bounded number of passes. */
#define CVM_VAL_STACK_CAP   256
/* Widening bound: depths beyond it are widened straight to the cap,
 * because no pop ever needs more than CVM_VAL_MAX_ARGS items. This
 * makes loop-carried interval growth converge in a bounded number of
 * worklist passes. */
#define CVM_VAL_WIDEN_BOUND 32
#define CVM_VAL_MAX_SARGS   6

typedef struct {
    int32_t lo;
    int32_t hi;
} DepthRange;

typedef struct {
    CvmModuleView *v;
    const char    *path;
    int            verbose;
    int            errors;
} ValCtx;

typedef struct {
    ValCtx    *ctx;
    uint32_t   fi;
    size_t     begin, end;
    uint8_t   *starts;
    uint8_t   *in_queue;
    size_t    *queue;
    size_t     q_head, q_tail;
    DepthRange *states;
} FuncCtx;

static void val_err(ValCtx *ctx, const char *what) {
    ctx->errors++;
    fprintf(stderr, "%s: error: %s\n", ctx->path, what);
}

static void val_fun_err(FuncCtx *fc, const char *what) {
    fc->ctx->errors++;
    char name[64];
    const char *fn = cvm_view_func_name(fc->ctx->v, fc->fi, name, sizeof(name));
    fprintf(stderr, "%s: error: function %s: %s\n", fc->ctx->path, fn, what);
}

static const uint8_t *code_of(const CvmModuleView *v) {
    return v->data + v->code_off;
}

static void q_push(FuncCtx *fc, size_t off) {
    size_t i = off - fc->begin;
    if (!fc->in_queue[i]) {
        fc->in_queue[i] = 1;
        fc->queue[fc->q_tail] = off;
        fc->q_tail = (fc->q_tail + 1) % (fc->end - fc->begin + 1);
    }
}

static size_t q_pop(FuncCtx *fc) {
    size_t off = fc->queue[fc->q_head];
    fc->in_queue[off - fc->begin] = 0;
    fc->q_head = (fc->q_head + 1) % (fc->end - fc->begin + 1);
    return off;
}

static int dr_merge(DepthRange *d, int32_t lo2, int32_t hi2) {
    int changed = 0;
    if (lo2 < d->lo) { d->lo = lo2; changed = 1; }
    if (hi2 > d->hi) { d->hi = hi2; changed = 1; }
    return changed;
}

/* Stack effect of one instruction on the interval [lo,hi]:
 * required pops, then the net deltas. */
typedef struct {
    int32_t need;
    int32_t dlo;
    int32_t dhi;
} StackEffect;

static int stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        StackEffect *ef) {
    const uint8_t *code = code_of(v);
    switch (op) {
    case OP_NOP:
    case OP_NEG:
    case OP_NOT:
    case OP_LNOT:
        ef->need = 0; ef->dlo = 0; ef->dhi = 0;
        return 0;
    case OP_PUSH_IMM64:
    case OP_PUSH_IMM32:
    case OP_PUSH_IMM8:
    case OP_PUSH_ZERO:
    case OP_PUSH_ONE:
    case OP_PUSH_LOCAL:
    case OP_PUSH_GLOBAL:
    case OP_LEA_LOCAL:
    case OP_LEA_GLOBAL:
    case OP_LEA_DATA:
        ef->need = 0; ef->dlo = 1; ef->dhi = 1;
        return 0;
    case OP_STORE_LOCAL:
    case OP_STORE_GLOBAL:
    case OP_FREE:
        ef->need = 1; ef->dlo = -1; ef->dhi = -1;
        return 0;
    case OP_ADD: case OP_SUB: case OP_MUL: case OP_DIV: case OP_MOD:
    case OP_AND: case OP_OR:  case OP_XOR: case OP_SHL: case OP_SHR:
    case OP_USHR:
    case OP_CMP_EQ: case OP_CMP_NE: case OP_CMP_LT: case OP_CMP_LE:
    case OP_CMP_GT: case OP_CMP_GE:
    case OP_CMP_ULT: case OP_CMP_ULE: case OP_CMP_UGT: case OP_CMP_UGE:
        ef->need = 1; ef->dlo = -1; ef->dhi = -1;
        return 0;
    case OP_JMP:
        ef->need = 0; ef->dlo = 0; ef->dhi = 0;
        return 0;
    case OP_JZ: case OP_JNZ:
        ef->need = 1; ef->dlo = -1; ef->dhi = -1;
        return 0;
    case OP_CALL: case OP_CALL_NATIVE: {
        uint8_t na = code[off + 5];
        ef->need = (int32_t)na;
        ef->dlo = -(int32_t)na + 1;
        ef->dhi = -(int32_t)na + 1;
        return 0;
    }
    case OP_RET:
        ef->need = 0;
        ef->dlo = -1; ef->dhi = -1;
        return 1; /* pops only when non-empty */
    case OP_LOAD8: case OP_LOAD16: case OP_LOAD32: case OP_LOAD64:
    case OP_ALLOC:
        ef->need = 1; ef->dlo = 0; ef->dhi = 0;
        return 0;
    case OP_STORE8: case OP_STORE16: case OP_STORE32: case OP_STORE64:
        ef->need = 2; ef->dlo = -2; ef->dhi = -2;
        return 0;
    case OP_SYSCALL: {
        uint8_t na = code[off + 2];
        ef->need = (int32_t)na;
        ef->dlo = -(int32_t)na;
        ef->dhi = -(int32_t)na + 1;
        return 0;
    }
    case OP_HALT:
        ef->need = 0; ef->dlo = 0; ef->dhi = 0;
        return 2; /* terminal */
    default:
        return -1;
    }
}

static int check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip) {
    const CvmModuleView *v = fc->ctx->v;
    const uint8_t *code = code_of(v);
    const CvmFuncEntry *fe = cvm_view_func(v, fc->fi);
    switch (op) {
    case OP_PUSH_LOCAL: case OP_STORE_LOCAL: case OP_LEA_LOCAL: {
        uint32_t i = cvm_ops_ru32(code, v->code_size, off + 1);
        uint32_t cap = fe->num_locals > 0 ? fe->num_locals : 16;
        if (i >= cap) {
            char msg[96];
            snprintf(msg, sizeof(msg),
                     "local index %u out of range (locals=%u) at 0x%04zx",
                     i, cap, off);
            val_fun_err(fc, msg);
            return -1;
        }
        break;
    }
    case OP_PUSH_GLOBAL: case OP_STORE_GLOBAL: case OP_LEA_GLOBAL: {
        uint32_t i = cvm_ops_ru32(code, v->code_size, off + 1);
        uint64_t need = (uint64_t)i * 8 + 8;
        if (need > v->data_size) {
            char msg[96];
            snprintf(msg, sizeof(msg),
                     "global index %u out of range (data=%u) at 0x%04zx",
                     i, v->data_size, off);
            val_fun_err(fc, msg);
            return -1;
        }
        break;
    }
    case OP_LEA_DATA: {
        uint32_t o = cvm_ops_ru32(code, v->code_size, off + 1);
        if (o > v->data_size) {
            char msg[96];
            snprintf(msg, sizeof(msg),
                     "data offset %u out of range (data=%u) at 0x%04zx",
                     o, v->data_size, off);
            val_fun_err(fc, msg);
            return -1;
        }
        break;
    }
    case OP_CALL: {
        uint32_t fi = cvm_ops_ru32(code, v->code_size, off + 1);
        uint8_t na = code[off + 5];
        if (fi >= v->num_functions) {
            char msg[96];
            snprintf(msg, sizeof(msg),
                     "call target %u out of range (functions=%u) at 0x%04zx",
                     fi, v->num_functions, off);
            val_fun_err(fc, msg);
            return -1;
        }
        if (na > CVM_VAL_MAX_ARGS) {
            char msg[96];
            snprintf(msg, sizeof(msg), "too many call arguments (%u) at 0x%04zx",
                     na, off);
            val_fun_err(fc, msg);
            return -1;
        }
        break;
    }
    case OP_CALL_NATIVE: {
        uint32_t ni = cvm_ops_ru32(code, v->code_size, off + 1);
        uint8_t na = code[off + 5];
        if (ni >= v->num_natives) {
            char msg[96];
            snprintf(msg, sizeof(msg),
                     "native index %u out of range (natives=%u) at 0x%04zx",
                     ni, v->num_natives, off);
            val_fun_err(fc, msg);
            return -1;
        }
        if (na > CVM_VAL_MAX_ARGS) {
            char msg[96];
            snprintf(msg, sizeof(msg), "too many native arguments (%u) at 0x%04zx",
                     na, off);
            val_fun_err(fc, msg);
            return -1;
        }
        break;
    }
    case OP_JMP: case OP_JZ: case OP_JNZ: {
        int32_t rel = cvm_ops_ri32(code, v->code_size, off + 1);
        int64_t target = (int64_t)next_ip + rel;
        if (target < (int64_t)fc->begin || target >= (int64_t)fc->end) {
            char msg[96];
            snprintf(msg, sizeof(msg), "jump target 0x%llx out of bounds at 0x%04zx",
                     (unsigned long long)target, off);
            val_fun_err(fc, msg);
            return -1;
        }
        /* A jump may tail-call another function: land on its code
         * offset, which is a legal instruction start outside this
         * function's own start set. */
        int tail_call = 0;
        for (uint32_t i = 0; i < v->num_functions; i++) {
            const CvmFuncEntry *ofe = cvm_view_func(v, i);
            if (ofe && (size_t)ofe->code_off == (size_t)target) {
                tail_call = 1;
                break;
            }
        }
        if (!tail_call && !fc->starts[(size_t)target - fc->begin]) {
            char msg[96];
            snprintf(msg, sizeof(msg),
                     "jump target 0x%llx is not an instruction start at 0x%04zx",
                     (unsigned long long)target, off);
            val_fun_err(fc, msg);
            return -1;
        }
        break;
    }
    case OP_SYSCALL: {
        uint8_t na = code[off + 2];
        if (na > CVM_VAL_MAX_SARGS) {
            char msg[96];
            snprintf(msg, sizeof(msg), "too many syscall arguments (%u) at 0x%04zx",
                     na, off);
            val_fun_err(fc, msg);
            return -1;
        }
        break;
    }
    default:
        break;
    }
    return 0;
}

/* Linear sweep of one function region: every byte must decode as a
 * whole instruction inside the region (pass one records instruction
 * starts, pass two checks operand ranges against the full start set). */
static int sweep_function(FuncCtx *fc, size_t *insn_count, uint8_t *last_op) {
    const CvmModuleView *v = fc->ctx->v;
    const uint8_t *code = code_of(v);
    size_t off = fc->begin;
    size_t n = 0;
    *last_op = OP_HALT;
    while (off < fc->end) {
        uint8_t op = code[off];
        const CvmOpInfo *info = cvm_op_info(op);
        if (!info) {
            char msg[96];
            snprintf(msg, sizeof(msg), "invalid opcode 0x%02X at 0x%04zx", op, off);
            val_fun_err(fc, msg);
            return -1;
        }
        if ((size_t)info->size > fc->end - off) {
            char msg[96];
            snprintf(msg, sizeof(msg),
                     "instruction at 0x%04zx overruns the function region", off);
            val_fun_err(fc, msg);
            return -1;
        }
        fc->starts[off - fc->begin] = 1;
        off += (size_t)info->size;
        *last_op = op;
        n++;
    }
    *insn_count = n;
    off = fc->begin;
    while (off < fc->end) {
        uint8_t op = code[off];
        const CvmOpInfo *info = cvm_op_info(op);
        if (check_static(fc, off, op, off + (size_t)info->size) != 0)
            return -1;
        off += (size_t)info->size;
    }
    return 0;
}

/* Abstract-interpretation stack balance: each instruction start carries
 * a [lo,hi] interval of possible stack depths; a required pop with lo==0
 * is an underflow. Hi saturates at the stack capacity. */
static int analyze_stack(FuncCtx *fc) {
    const CvmModuleView *v = fc->ctx->v;
    const uint8_t *code = code_of(v);
    size_t span = fc->end - fc->begin;
    for (size_t i = 0; i <= span; i++) {
        fc->states[i].lo = INT32_MAX;
        fc->states[i].hi = -1;
    }
    fc->states[0].lo = 0;
    fc->states[0].hi = 0;
    q_push(fc, fc->begin);
    size_t max_passes = span * 128 + 128;
    size_t passes = 0;
    while (fc->q_head != fc->q_tail) {
        if (++passes > max_passes) {
            val_fun_err(fc, "control flow analysis did not converge");
            return -1;
        }
        size_t off = q_pop(fc);
        size_t si = off - fc->begin;
        DepthRange st = fc->states[si];
        uint8_t op = code[off];
        const CvmOpInfo *info = cvm_op_info(op);
        if (!info) return -1;
        StackEffect ef;
        int kind = stack_effect(v, off, op, &ef);
        if (kind < 0) {
            val_fun_err(fc, "cannot analyze opcode");
            return -1;
        }
        if (st.lo < ef.need || st.hi < ef.need) {
            char msg[128];
            snprintf(msg, sizeof(msg),
                     "operand stack underflow at 0x%04zx (need %d, have %d..%d)",
                     off, ef.need, st.lo, st.hi);
            val_fun_err(fc, msg);
            return -1;
        }
        int32_t lo2 = st.lo + ef.dlo;
        int32_t hi2 = st.hi + ef.dhi;
        if (kind == 1) { /* RET pops only when non-empty */
            if (st.lo > 0) lo2 = st.lo - 1;
            if (st.hi > 0) hi2 = st.hi - 1;
        }
        if (lo2 < 0) lo2 = 0;
        if (lo2 > CVM_VAL_WIDEN_BOUND) lo2 = CVM_VAL_STACK_CAP;
        if (hi2 > CVM_VAL_WIDEN_BOUND) hi2 = CVM_VAL_STACK_CAP;
        if (kind == 2) continue; /* HALT: no successors */
        size_t next = off + (size_t)info->size;
        if (op == OP_JMP) {
            int32_t rel = cvm_ops_ri32(code, v->code_size, off + 1);
            size_t target = next + (size_t)rel;
            if (target < fc->begin || target >= fc->end) continue; /* tail jump */
            if (dr_merge(&fc->states[target - fc->begin], lo2, hi2))
                q_push(fc, target);
        } else if (op == OP_JZ || op == OP_JNZ) {
            int32_t rel = cvm_ops_ri32(code, v->code_size, off + 1);
            size_t target = next + (size_t)rel;
            if (target >= fc->begin && target < fc->end) {
                if (dr_merge(&fc->states[target - fc->begin], lo2, hi2))
                    q_push(fc, target);
            }
            if (next < fc->end &&
                dr_merge(&fc->states[next - fc->begin], lo2, hi2))
                q_push(fc, next);
        } else if (op != OP_RET && op != OP_HALT) {
            if (next < fc->end &&
                dr_merge(&fc->states[next - fc->begin], lo2, hi2))
                q_push(fc, next);
        }
    }
    return 0;
}

static int check_function(FuncCtx *fc, size_t *insn_count) {
    uint8_t last_op = OP_HALT;
    if (sweep_function(fc, insn_count, &last_op) != 0) return -1;
    if (*insn_count == 0) {
        val_fun_err(fc, "function contains no instructions");
        return -1;
    }
    if (last_op != OP_RET && last_op != OP_HALT && last_op != OP_JMP) {
        val_fun_err(fc, "function falls off the end of its code");
        return -1;
    }
    if (analyze_stack(fc) != 0) return -1;
    return 0;
}

static int cmp_func(const void *a, const void *b) {
    const CvmFuncEntry *fa = (const CvmFuncEntry *)a;
    const CvmFuncEntry *fb = (const CvmFuncEntry *)b;
    return (fa->code_off > fb->code_off) - (fa->code_off < fb->code_off);
}

int main(int argc, char **argv) {
    int verbose = 0;
    const char *path = NULL;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-v") == 0) { verbose = 1; continue; }
        path = argv[i];
    }
    if (!path) {
        fprintf(stderr, "Usage: %s [-v] <module.cvm>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "cvm-validate: cannot open %s\n", path);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);
    if (sz < 0) {
        fprintf(stderr, "cvm-validate: cannot size %s\n", path);
        fclose(f);
        return 1;
    }
    uint8_t *buf = (uint8_t *)malloc((size_t)sz ? (size_t)sz : 1);
    if (!buf) {
        fprintf(stderr, "cvm-validate: out of memory\n");
        fclose(f);
        return 1;
    }
    if (fread(buf, 1, (size_t)sz, f) != (size_t)sz) {
        fprintf(stderr, "cvm-validate: read error\n");
        free(buf);
        fclose(f);
        return 1;
    }
    fclose(f);

    ValCtx ctx;
    ctx.v = NULL;
    ctx.path = path;
    ctx.verbose = verbose;
    ctx.errors = 0;

    CvmModuleView v;
    int rc = cvm_view_open(&v, buf, (size_t)sz);
    if (rc != CVM_OK) {
        fprintf(stderr, "%s: error: %s\n", path, cvm_view_strerror(rc));
        free(buf);
        return 1;
    }
    ctx.v = &v;

    if (v.num_functions > CVM_VAL_MAX_FUNCS) {
        val_err(&ctx, "too many functions");
        free(buf);
        return 1;
    }
    if (v.num_globals > CVM_VAL_MAX_GLOBALS) {
        val_err(&ctx, "too many globals");
        free(buf);
        return 1;
    }
    if (v.num_natives > CVM_VAL_MAX_NATIVES) {
        val_err(&ctx, "too many natives");
        free(buf);
        return 1;
    }
    if (v.code_size > CVM_VAL_MAX_CODE) {
        val_err(&ctx, "code section too large");
        free(buf);
        return 1;
    }
    if (v.entry_func >= v.num_functions) {
        val_err(&ctx, "entry function out of range");
        free(buf);
        return 1;
    }

    uint64_t data_total = 0;
    for (uint32_t i = 0; i < v.num_globals; i++) {
        const uint8_t *ge = v.data + v.global_off + (size_t)i * CVM_GLOBAL_ENTRY_SIZE;
        uint64_t gs = (uint64_t)ge[4] | ((uint64_t)ge[5] << 8) |
                      ((uint64_t)ge[6] << 16) | ((uint64_t)ge[7] << 24);
        gs = (gs + 7) & ~(uint64_t)7;
        if (gs > (uint64_t)((size_t)-1) - data_total) {
            val_err(&ctx, "global data size overflow");
            free(buf);
            return 1;
        }
        data_total += gs;
    }
    if (data_total > (uint64_t)v.data_size) v.data_size = (uint32_t)data_total;

    if (v.string_pool_size > 0) {
        for (uint32_t i = 0; i < v.num_functions; i++) {
            const CvmFuncEntry *fe = cvm_view_func(&v, i);
            if (fe && fe->name_off >= v.string_pool_size) {
                char msg[96];
                snprintf(msg, sizeof(msg),
                         "function %u name offset out of pool", i);
                val_err(&ctx, msg);
            }
        }
        for (uint32_t i = 0; i < v.num_natives; i++) {
            const uint8_t *ne = v.data + v.native_off +
                                (size_t)i * CVM_NATIVE_ENTRY_SIZE;
            uint32_t name_off = (uint32_t)ne[0] | ((uint32_t)ne[1] << 8) |
                                ((uint32_t)ne[2] << 16) | ((uint32_t)ne[3] << 24);
            if (name_off >= v.string_pool_size) {
                char msg[96];
                snprintf(msg, sizeof(msg),
                         "native %u name offset out of pool", i);
                val_err(&ctx, msg);
            }
        }
    }

    CvmFuncEntry *sorted = (CvmFuncEntry *)malloc(
        (size_t)v.num_functions * CVM_FUNC_ENTRY_SIZE);
    if (!sorted) {
        fprintf(stderr, "cvm-validate: out of memory\n");
        free(buf);
        return 1;
    }
    for (uint32_t i = 0; i < v.num_functions; i++) {
        const CvmFuncEntry *fe = cvm_view_func(&v, i);
        if (!fe) continue;
        sorted[i] = *fe;
        if (fe->code_off > v.code_size) {
            char msg[96];
            snprintf(msg, sizeof(msg), "function %u code offset out of range", i);
            val_err(&ctx, msg);
        }
        if (fe->num_locals > CVM_VAL_MAX_LOCALS) {
            char msg[96];
            snprintf(msg, sizeof(msg), "function %u has too many locals", i);
            val_err(&ctx, msg);
        }
    }
    qsort(sorted, v.num_functions, CVM_FUNC_ENTRY_SIZE, cmp_func);
    for (uint32_t i = 0; i + 1 < v.num_functions; i++) {
        if (sorted[i].code_off == sorted[i + 1].code_off) {
            val_err(&ctx, "two functions share a code offset");
        }
    }

    size_t total_insn = 0;
    if (ctx.errors == 0) {
        for (uint32_t i = 0; i < v.num_functions; i++) {
            size_t begin = 0, end = 0;
            if (cvm_view_func_region(&v, i, &begin, &end) != CVM_OK) {
                val_err(&ctx, "cannot determine function region");
                continue;
            }
            FuncCtx fc;
            fc.ctx = &ctx;
            fc.fi = i;
            fc.begin = begin;
            fc.end = end;
            size_t span = end - begin;
            fc.starts = (uint8_t *)calloc(span, 1);
            fc.in_queue = (uint8_t *)calloc(span + 1, 1);
            fc.queue = (size_t *)malloc((span + 1) * sizeof(size_t));
            fc.states = (DepthRange *)malloc((span + 1) * sizeof(DepthRange));
            if (!fc.starts || !fc.in_queue || !fc.queue || !fc.states) {
                fprintf(stderr, "cvm-validate: out of memory\n");
                free(fc.starts); free(fc.in_queue);
                free(fc.queue); free(fc.states);
                free(sorted);
                free(buf);
                return 1;
            }
            fc.q_head = fc.q_tail = 0;
            size_t insn = 0;
            if (check_function(&fc, &insn) != 0) {
                free(fc.starts); free(fc.in_queue);
                free(fc.queue); free(fc.states);
                continue;
            }
            total_insn += insn;
            if (verbose) {
                char name[64];
                const char *fn = cvm_view_func_name(&v, i, name, sizeof(name));
                printf("function %s: %zu instructions, stack balanced\n",
                       fn, insn);
            }
            free(fc.starts); free(fc.in_queue);
            free(fc.queue); free(fc.states);
        }
    }
    free(sorted);

    if (ctx.errors > 0) {
        printf("module %s: INVALID (%d error%s)\n", path, ctx.errors,
               ctx.errors == 1 ? "" : "s");
        free(buf);
        return 1;
    }
    printf("module %s: OK (functions=%u, code=%u bytes, globals=%u, "
           "instructions=%zu)\n",
           path, v.num_functions, v.code_size, v.num_globals, total_insn);
    free(buf);
    return 0;
}
