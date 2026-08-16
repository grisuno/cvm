/**
 * @file cvm_dis.h
 * @brief Textual disassembler for .cvm modules: reads the code section
 *        through the shared opcode table and renders one line per
 *        instruction. The core is stdio-free so it can be embedded in
 *        the OS tools later.
 * @license GPL-2.0-or-later
 */
#ifndef CVM_DIS_H
#define CVM_DIS_H

#include <stddef.h>
#include <stdint.h>
#include "cvm_view.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*CvmDisEmit)(void *ctx, const char *line);

/* Whole module: header summary plus every function region. */
int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx);

/* One function region from begin up to end. */
int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end,
                     CvmDisEmit emit, void *ctx);

/* One instruction at code offset off (within [begin,end)). Returns the
 * instruction size, or -1 when it does not decode inside the region. */
int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end,
                 char *buf, size_t cap);

#ifdef __cplusplus
}
#endif

#endif /* CVM_DIS_H */
