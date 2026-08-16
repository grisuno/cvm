/**
 * @file cvm_view.h
 * @brief Read-only, bounds-checked view of a .cvm module on disk, shared
 *        by the disassembler, the validator and the debugger. All extent
 *        arithmetic is overflow checked before use.
 * @license GPL-2.0-or-later
 */
#ifndef CVM_VIEW_H
#define CVM_VIEW_H

#include <stdint.h>
#include <stddef.h>
#include "cvm.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    const uint8_t *data;
    size_t         size;
    uint32_t       ver_major;
    uint32_t       ver_minor;
    uint32_t       num_functions;
    uint32_t       num_globals;
    uint32_t       num_natives;
    uint32_t       num_strings;
    uint32_t       code_size;
    uint32_t       string_pool_size;
    uint32_t       data_size;
    uint32_t       entry_func;
    size_t         func_off;
    size_t         global_off;
    size_t         native_off;
    size_t         string_off;
    size_t         code_off;
    size_t         pool_off;
} CvmModuleView;

/* Parse and validate the header plus all section extents. */
int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size);

/* Message for an error code returned by cvm_view_open. */
const char *cvm_view_strerror(int error_code);

const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i);

/* String from the pool, or NULL when the offset is outside it. The
 * pointer is only valid while the module data lives. */
const char *cvm_view_string(const CvmModuleView *v, uint32_t off);

/* Function name from the pool; falls back to "func<N>" in fallback. */
const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,
                               char *fallback, size_t cap);

/* Code region of a function: [*begin, *end) where *end is the next
 * function's code offset or the end of the code section. */
int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,
                         size_t *begin, size_t *end);

#ifdef __cplusplus
}
#endif

#endif /* CVM_VIEW_H */
