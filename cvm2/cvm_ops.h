/**
 * @file cvm_ops.h
 * @brief Shared opcode metadata for the CVM toolchain: one table of
 *        names, sizes and operand encodings used by the disassembler,
 *        the validator and the debugger so they can never disagree
 *        about the bytecode format.
 * @license GPL-2.0-or-later
 */
#ifndef CVM_OPS_H
#define CVM_OPS_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CVM_OPK_NONE  = 0,
    CVM_OPK_I8    = 1,
    CVM_OPK_I32   = 2,
    CVM_OPK_I64   = 3,
    CVM_OPK_U32   = 4,
    CVM_OPK_U32U8 = 5,
    CVM_OPK_REL   = 6,
    CVM_OPK_U8U8  = 7
} CvmOpKind;

typedef struct {
    uint8_t     opcode;
    uint8_t     kind;
    uint8_t     size;
    const char *name;
} CvmOpInfo;

/* Metadata for one opcode, or NULL when the opcode is not defined. */
const CvmOpInfo *cvm_op_info(uint8_t opcode);

/* Mnemonic for one opcode, or NULL when the opcode is not defined. */
const char *cvm_op_name(uint8_t opcode);

/* Decode helpers over a code buffer, little-endian as stored. */
int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off);
int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off);
uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off);
int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out);

#ifdef __cplusplus
}
#endif

#endif /* CVM_OPS_H */
