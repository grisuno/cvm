/**
 * @file cvm_ops.c
 * @brief Opcode metadata table and little-endian operand decoders.
 * @license GPL-2.0-or-later
 */
#include "cvm_ops.h"
#include "cvm.h"

static const CvmOpInfo op_infos[] = {
    { OP_NOP,          CVM_OPK_NONE,  1, "NOP" },
    { OP_PUSH_IMM64,   CVM_OPK_I64,   9, "PUSH_IMM64" },
    { OP_PUSH_IMM32,   CVM_OPK_I32,   5, "PUSH_IMM32" },
    { OP_PUSH_IMM8,    CVM_OPK_I8,    2, "PUSH_IMM8" },
    { OP_PUSH_ZERO,    CVM_OPK_NONE,  1, "PUSH_ZERO" },
    { OP_PUSH_ONE,     CVM_OPK_NONE,  1, "PUSH_ONE" },
    { OP_PUSH_LOCAL,   CVM_OPK_U32,   5, "PUSH_LOCAL" },
    { OP_STORE_LOCAL,  CVM_OPK_U32,   5, "STORE_LOCAL" },
    { OP_PUSH_GLOBAL,  CVM_OPK_U32,   5, "PUSH_GLOBAL" },
    { OP_STORE_GLOBAL, CVM_OPK_U32,   5, "STORE_GLOBAL" },
    { OP_ADD,          CVM_OPK_NONE,  1, "ADD" },
    { OP_SUB,          CVM_OPK_NONE,  1, "SUB" },
    { OP_MUL,          CVM_OPK_NONE,  1, "MUL" },
    { OP_DIV,          CVM_OPK_NONE,  1, "DIV" },
    { OP_MOD,          CVM_OPK_NONE,  1, "MOD" },
    { OP_NEG,          CVM_OPK_NONE,  1, "NEG" },
    { OP_AND,          CVM_OPK_NONE,  1, "AND" },
    { OP_OR,           CVM_OPK_NONE,  1, "OR" },
    { OP_XOR,          CVM_OPK_NONE,  1, "XOR" },
    { OP_NOT,          CVM_OPK_NONE,  1, "NOT" },
    { OP_SHL,          CVM_OPK_NONE,  1, "SHL" },
    { OP_SHR,          CVM_OPK_NONE,  1, "SHR" },
    { OP_USHR,         CVM_OPK_NONE,  1, "USHR" },
    { OP_CMP_EQ,       CVM_OPK_NONE,  1, "CMP_EQ" },
    { OP_CMP_NE,       CVM_OPK_NONE,  1, "CMP_NE" },
    { OP_CMP_LT,       CVM_OPK_NONE,  1, "CMP_LT" },
    { OP_CMP_LE,       CVM_OPK_NONE,  1, "CMP_LE" },
    { OP_CMP_GT,       CVM_OPK_NONE,  1, "CMP_GT" },
    { OP_CMP_GE,       CVM_OPK_NONE,  1, "CMP_GE" },
    { OP_CMP_ULT,      CVM_OPK_NONE,  1, "CMP_ULT" },
    { OP_CMP_ULE,      CVM_OPK_NONE,  1, "CMP_ULE" },
    { OP_CMP_UGT,      CVM_OPK_NONE,  1, "CMP_UGT" },
    { OP_CMP_UGE,      CVM_OPK_NONE,  1, "CMP_UGE" },
    { OP_LNOT,         CVM_OPK_NONE,  1, "LNOT" },
    { OP_JMP,          CVM_OPK_REL,   5, "JMP" },
    { OP_JZ,           CVM_OPK_REL,   5, "JZ" },
    { OP_JNZ,          CVM_OPK_REL,   5, "JNZ" },
    { OP_CALL,         CVM_OPK_U32U8, 6, "CALL" },
    { OP_RET,          CVM_OPK_NONE,  1, "RET" },
    { OP_CALL_NATIVE,  CVM_OPK_U32U8, 6, "CALL_NATIVE" },
    { OP_LOAD16,       CVM_OPK_NONE,  1, "LOAD16" },
    { OP_LOAD8,        CVM_OPK_NONE,  1, "LOAD8" },
    { OP_LOAD32,       CVM_OPK_NONE,  1, "LOAD32" },
    { OP_LOAD64,       CVM_OPK_NONE,  1, "LOAD64" },
    { OP_STORE16,      CVM_OPK_NONE,  1, "STORE16" },
    { OP_STORE8,       CVM_OPK_NONE,  1, "STORE8" },
    { OP_STORE32,      CVM_OPK_NONE,  1, "STORE32" },
    { OP_STORE64,      CVM_OPK_NONE,  1, "STORE64" },
    { OP_LEA_LOCAL,    CVM_OPK_U32,   5, "LEA_LOCAL" },
    { OP_LEA_GLOBAL,   CVM_OPK_U32,   5, "LEA_GLOBAL" },
    { OP_ALLOC,        CVM_OPK_NONE,  1, "ALLOC" },
    { OP_FREE,         CVM_OPK_NONE,  1, "FREE" },
    { OP_LEA_DATA,     CVM_OPK_U32,   5, "LEA_DATA" },
    { OP_SYSCALL,      CVM_OPK_U8U8,  3, "SYSCALL" },
    { OP_HALT,         CVM_OPK_NONE,  1, "HALT" }
};

#define OP_INFOS_LEN (sizeof(op_infos) / sizeof(op_infos[0]))

const CvmOpInfo *cvm_op_info(uint8_t opcode) {
    for (size_t i = 0; i < OP_INFOS_LEN; i++)
        if (op_infos[i].opcode == opcode) return &op_infos[i];
    return NULL;
}

const char *cvm_op_name(uint8_t opcode) {
    const CvmOpInfo *info = cvm_op_info(opcode);
    return info ? info->name : NULL;
}

int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out) {
    if (off >= size) return -1;
    *out = code[off];
    return 0;
}

uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off) {
    if (off + 4 > size) return 0;
    return (uint32_t)code[off]
         | ((uint32_t)code[off + 1] << 8)
         | ((uint32_t)code[off + 2] << 16)
         | ((uint32_t)code[off + 3] << 24);
}

int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off) {
    return (int32_t)cvm_ops_ru32(code, size, off);
}

int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off) {
    if (off + 8 > size) return 0;
    uint64_t v = 0;
    for (int i = 0; i < 8; i++)
        v |= (uint64_t)code[off + i] << (i * 8);
    return (int64_t)v;
}
