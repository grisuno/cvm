/**
 * @file cvm_dis.c
 * @brief Disassembler core: manual formatting, no stdio, so the same
 *        code can be built inside the OS by the miniGCC-to-ld chain.
 * @license GPL-2.0-or-later
 */
#include "cvm_dis.h"
#include "cvm_ops.h"
#include <string.h>

#define CVM_DIS_LINE_MAX 160

static void putc_str(char *buf, size_t cap, size_t *n, char c) {
    if (*n + 1 < cap) buf[(*n)++] = c;
}

static void puts_str(char *buf, size_t cap, size_t *n, const char *s) {
    while (*s) putc_str(buf, cap, n, *s++);
}

static void put_hex(char *buf, size_t cap, size_t *n, uint64_t v, int digits) {
    char tmp[20];
    int i = 19;
    tmp[i--] = 0;
    if (v == 0) tmp[i--] = '0';
    while (v) {
        int d = (int)(v & 0xF);
        tmp[i--] = (char)(d < 10 ? '0' + d : 'a' + d - 10);
        v >>= 4;
    }
    while (19 - i <= digits) tmp[i--] = '0';
    puts_str(buf, cap, n, tmp + i + 1);
}

static void put_dec(char *buf, size_t cap, size_t *n, int64_t v) {
    char tmp[24];
    int i = 23;
    tmp[i--] = 0;
    uint64_t m = v < 0 ? (uint64_t)(-(v + 1)) + 1 : (uint64_t)v;
    if (m == 0) tmp[i--] = '0';
    while (m) {
        tmp[i--] = (char)('0' + (m % 10));
        m /= 10;
    }
    if (v < 0) tmp[i--] = '-';
    puts_str(buf, cap, n, tmp + i + 1);
}

static void pad_name(char *buf, size_t cap, size_t *n, const char *name) {
    size_t len = 0;
    while (name[len]) len++;
    puts_str(buf, cap, n, name);
    while (len < 12) { putc_str(buf, cap, n, ' '); len++; }
}

int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end,
                 char *buf, size_t cap) {
    size_t n = 0;
    buf[0] = 0;
    if (off >= end || off >= v->code_size) return -1;
    const uint8_t *code = v->data + v->code_off;
    uint8_t op = code[off];
    const CvmOpInfo *info = cvm_op_info(op);
    if (!info) return -1;
    if ((size_t)info->size > end - off || (size_t)info->size > v->code_size - off)
        return -1;

    put_hex(buf, cap, &n, (uint64_t)off, 4);
    puts_str(buf, cap, &n, "  ");
    pad_name(buf, cap, &n, info->name);

    switch (info->kind) {
    case CVM_OPK_NONE:
        break;
    case CVM_OPK_I8: {
        int32_t v8 = (int32_t)(int8_t)code[off + 1];
        put_dec(buf, cap, &n, v8);
        break;
    }
    case CVM_OPK_I32: {
        int32_t v32 = cvm_ops_ri32(code, v->code_size, off + 1);
        put_dec(buf, cap, &n, v32);
        break;
    }
    case CVM_OPK_I64: {
        int64_t v64 = cvm_ops_ri64(code, v->code_size, off + 1);
        put_dec(buf, cap, &n, v64);
        break;
    }
    case CVM_OPK_U32: {
        uint32_t u = cvm_ops_ru32(code, v->code_size, off + 1);
        put_dec(buf, cap, &n, (int64_t)u);
        break;
    }
    case CVM_OPK_U32U8: {
        uint32_t u = cvm_ops_ru32(code, v->code_size, off + 1);
        uint8_t na = code[off + 5];
        put_dec(buf, cap, &n, (int64_t)u);
        putc_str(buf, cap, &n, ' ');
        put_dec(buf, cap, &n, (int64_t)na);
        if (op == OP_CALL && u < v->num_functions) {
            char fb[CVM_DIS_LINE_MAX / 2];
            const char *name = cvm_view_func_name(v, u, fb, sizeof(fb));
            puts_str(buf, cap, &n, "  ; ");
            puts_str(buf, cap, &n, name);
        } else if (op == OP_CALL_NATIVE && v->string_pool_size &&
                   u < v->num_natives) {
            const uint8_t *ne = v->data + v->native_off +
                                (size_t)u * CVM_NATIVE_ENTRY_SIZE;
            uint32_t name_off = (uint32_t)ne[0] | ((uint32_t)ne[1] << 8) |
                                ((uint32_t)ne[2] << 16) | ((uint32_t)ne[3] << 24);
            const char *name = cvm_view_string(v, name_off);
            if (name) {
                puts_str(buf, cap, &n, "  ; ");
                puts_str(buf, cap, &n, name);
            }
        }
        break;
    }
    case CVM_OPK_REL: {
        int32_t rel = cvm_ops_ri32(code, v->code_size, off + 1);
        int64_t target = (int64_t)(off + (size_t)info->size) + rel;
        if (target >= 0 && (uint64_t)target <= v->code_size) {
            put_hex(buf, cap, &n, (uint64_t)target, 4);
            for (uint32_t i = 0; i < v->num_functions; i++) {
                const CvmFuncEntry *fe = cvm_view_func(v, i);
                if (fe && (size_t)fe->code_off == (size_t)target) {
                    char fb[CVM_DIS_LINE_MAX / 2];
                    const char *name = cvm_view_func_name(v, i, fb, sizeof(fb));
                    puts_str(buf, cap, &n, "  ; ");
                    puts_str(buf, cap, &n, name);
                    break;
                }
            }
        } else {
            puts_str(buf, cap, &n, "<out of range>");
        }
        break;
    }
    case CVM_OPK_U8U8: {
        uint8_t sn = code[off + 1];
        uint8_t na = code[off + 2];
        put_dec(buf, cap, &n, (int64_t)sn);
        putc_str(buf, cap, &n, ' ');
        put_dec(buf, cap, &n, (int64_t)na);
        break;
    }
    }
    buf[n] = 0;
    return info->size;
}

int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end,
                     CvmDisEmit emit, void *ctx) {
    char line[CVM_DIS_LINE_MAX];
    size_t off = begin;
    while (off < end) {
        int sz = cvm_dis_line(v, off, end, line, sizeof(line));
        if (sz < 0) {
            size_t n = 0;
            put_hex(line, sizeof(line), &n, (uint64_t)off, 4);
            puts_str(line, sizeof(line), &n, "  ??? (bad opcode)");
            line[n] = 0;
            emit(ctx, line);
            return -1;
        }
        emit(ctx, line);
        off += (size_t)sz;
    }
    return 0;
}

int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx) {
    char line[CVM_DIS_LINE_MAX];
    size_t n = 0;
    line[0] = 0;
    puts_str(line, sizeof(line), &n, "; CVM module: version ");
    put_dec(line, sizeof(line), &n, (int64_t)v->ver_major);
    putc_str(line, sizeof(line), &n, '.');
    put_dec(line, sizeof(line), &n, (int64_t)v->ver_minor);
    line[n] = 0;
    emit(ctx, line);

    n = 0;
    puts_str(line, sizeof(line), &n, "; functions=");
    put_dec(line, sizeof(line), &n, (int64_t)v->num_functions);
    puts_str(line, sizeof(line), &n, " globals=");
    put_dec(line, sizeof(line), &n, (int64_t)v->num_globals);
    puts_str(line, sizeof(line), &n, " natives=");
    put_dec(line, sizeof(line), &n, (int64_t)v->num_natives);
    puts_str(line, sizeof(line), &n, " strings=");
    put_dec(line, sizeof(line), &n, (int64_t)v->num_strings);
    line[n] = 0;
    emit(ctx, line);

    n = 0;
    puts_str(line, sizeof(line), &n, "; code=");
    put_dec(line, sizeof(line), &n, (int64_t)v->code_size);
    puts_str(line, sizeof(line), &n, " bytes data=");
    put_dec(line, sizeof(line), &n, (int64_t)v->data_size);
    puts_str(line, sizeof(line), &n, " pool=");
    put_dec(line, sizeof(line), &n, (int64_t)v->string_pool_size);
    puts_str(line, sizeof(line), &n, " entry=");
    put_dec(line, sizeof(line), &n, (int64_t)v->entry_func);
    line[n] = 0;
    emit(ctx, line);

    for (uint32_t i = 0; i < v->num_functions; i++) {
        const CvmFuncEntry *fe = cvm_view_func(v, i);
        if (!fe) return CVM_ERR_BAD_FUNC;
        size_t begin = 0, end = 0;
        if (cvm_view_func_region(v, i, &begin, &end) != CVM_OK)
            return CVM_ERR_BAD_MODULE;
        char fb[CVM_DIS_LINE_MAX / 2];
        const char *name = cvm_view_func_name(v, i, fb, sizeof(fb));
        n = 0;
        puts_str(line, sizeof(line), &n, "; Function ");
        put_dec(line, sizeof(line), &n, (int64_t)i);
        puts_str(line, sizeof(line), &n, ": ");
        puts_str(line, sizeof(line), &n, name);
        puts_str(line, sizeof(line), &n, " (locals=");
        put_dec(line, sizeof(line), &n, (int64_t)fe->num_locals);
        puts_str(line, sizeof(line), &n, ", argc=");
        put_dec(line, sizeof(line), &n, (int64_t)fe->argc);
        puts_str(line, sizeof(line), &n, ", code=0x");
        put_hex(line, sizeof(line), &n, (uint64_t)fe->code_off, 4);
        putc_str(line, sizeof(line), &n, ')');
        line[n] = 0;
        emit(ctx, line);
        if (cvm_dis_function(v, begin, end, emit, ctx) != 0)
            return CVM_ERR_BAD_MODULE;
    }
    return CVM_OK;
}
