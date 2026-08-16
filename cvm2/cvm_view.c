/**
 * @file cvm_view.c
 * @brief Module view parsing with fail-closed extent validation.
 * @license GPL-2.0-or-later
 */
#include "cvm_view.h"
#include <string.h>

static uint32_t rl32(const uint8_t *p) {
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8)
         | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
}

static uint32_t rl16(const uint8_t *p) {
    return (uint32_t)p[0] | ((uint32_t)p[1] << 8);
}

const char *cvm_view_strerror(int error_code) {
    switch (error_code) {
        case CVM_OK:              return "success";
        case CVM_ERR_BAD_MODULE:  return "malformed module";
        case CVM_ERR_BAD_MAGIC:   return "invalid module magic";
        case CVM_ERR_BAD_VERSION: return "unsupported module version";
        case CVM_ERR_BAD_FUNC:    return "invalid function index";
        default:                  return "unknown error";
    }
}

int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size) {
    memset(v, 0, sizeof(*v));
    v->data = data;
    v->size = size;
    if (size < CVM_MODULE_HEADER_SIZE) return CVM_ERR_BAD_MODULE;
    if (data[0] != CVM_MAGIC_0 || data[1] != CVM_MAGIC_1 ||
        data[2] != CVM_MAGIC_2 || data[3] != CVM_MAGIC_3)
        return CVM_ERR_BAD_MAGIC;
    v->ver_major = rl16(data + 4);
    v->ver_minor = rl16(data + 6);
    if (v->ver_major != CVM_VERSION_MAJOR) return CVM_ERR_BAD_VERSION;
    if (v->ver_minor > CVM_VERSION_MINOR) return CVM_ERR_BAD_VERSION;

    v->num_functions   = rl32(data + 8);
    v->num_globals     = rl32(data + 12);
    v->num_natives     = rl32(data + 16);
    v->num_strings     = rl32(data + 20);
    v->code_size       = rl32(data + 24);
    v->string_pool_size = rl32(data + 28);
    v->data_size       = rl32(data + 32);
    v->entry_func      = rl32(data + 36);

    size_t off = CVM_MODULE_HEADER_SIZE;
    size_t rem = size - off;
    size_t ft = (size_t)v->num_functions * CVM_FUNC_ENTRY_SIZE;
    size_t gt = (size_t)v->num_globals * CVM_GLOBAL_ENTRY_SIZE;
    size_t nt = (size_t)v->num_natives * CVM_NATIVE_ENTRY_SIZE;
    size_t st = (size_t)v->num_strings * CVM_STRING_ENTRY_SIZE;
    if (ft > rem || gt > rem - ft || nt > rem - ft - gt ||
        st > rem - ft - gt - nt)
        return CVM_ERR_BAD_MODULE;
    v->func_off   = off; off += ft;
    v->global_off = off; off += gt;
    v->native_off = off; off += nt;
    v->string_off = off; off += st;
    v->code_off   = off;
    if ((size_t)v->code_size > size - v->code_off) return CVM_ERR_BAD_MODULE;
    v->pool_off = size - v->string_pool_size;
    if (v->pool_off < v->code_off + v->code_size || v->pool_off > size)
        return CVM_ERR_BAD_MODULE;
    return CVM_OK;
}

const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i) {
    if (i >= v->num_functions) return NULL;
    return (const CvmFuncEntry *)(v->data + v->func_off +
                                  (size_t)i * CVM_FUNC_ENTRY_SIZE);
}

const char *cvm_view_string(const CvmModuleView *v, uint32_t off) {
    if (v->string_pool_size == 0 || off >= v->string_pool_size) return NULL;
    const char *s = (const char *)(v->data + v->pool_off + off);
    size_t maxlen = v->string_pool_size - off;
    for (size_t i = 0; i < maxlen; i++)
        if (s[i] == 0) return s;
    return NULL;
}

const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,
                               char *fallback, size_t cap) {
    const CvmFuncEntry *fe = cvm_view_func(v, fi);
    if (fe) {
        const char *name = cvm_view_string(v, fe->name_off);
        if (name && name[0]) return name;
    }
    size_t n = 0;
    const char *pfx = "func";
    while (pfx[n] && n + 1 < cap) { fallback[n] = pfx[n]; n++; }
    char tmp[12];
    int t = 11;
    tmp[t--] = 0;
    uint32_t u = fi;
    if (u == 0) tmp[t--] = '0';
    while (u) { tmp[t--] = (char)('0' + (u % 10)); u /= 10; }
    for (int i = t + 1; i < 11 && n + 1 < cap; i++) fallback[n++] = tmp[i];
    fallback[n] = 0;
    return fallback;
}

int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,
                         size_t *begin, size_t *end) {
    const CvmFuncEntry *fe = cvm_view_func(v, fi);
    if (!fe) return CVM_ERR_BAD_FUNC;
    *begin = fe->code_off;
    *end = v->code_size;
    for (uint32_t i = 0; i < v->num_functions; i++) {
        const CvmFuncEntry *o = cvm_view_func(v, i);
        if (!o) continue;
        if (o->code_off > *begin && o->code_off < *end) *end = o->code_off;
    }
    return CVM_OK;
}
