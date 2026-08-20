/**
 * @file cvm.h
 * @brief CVM - C Virtual Machine. Stack-based bytecode interpreter.
 * @license GPL-2.0-or-later
 *
 * Module format v2 (little-endian):
 *   off  0: magic      'C','V','M',0x02
 *   off  4: version    u16 major, u16 minor
 *   off  8: num_functions u32
 *   off 12: num_globals   u32
 *   off 16: num_natives   u32
 *   off 20: num_strings   u32
 *   off 24: code_size     u32
 *   off 28: string_pool_size u32
 *   off 32: data_size      u32
 *   off 36: entry_func     u32
 *   off 40: CvmFuncEntry[num_functions]    (20 bytes each)
 *           CvmGlobalEntry[num_globals]    (8 bytes each)
 *           CvmNativeEntry[num_natives]    (4 bytes each)
 *           CvmStringEntry[num_strings]    (8 bytes each)
 *           code[code_size]
 *           data (RLE-compressed, expands to data_size bytes:
 *                 tag 0..253  -> tag+1 zero bytes
 *                 tag 254     -> next byte n, then n literal bytes)
 *           string_pool[string_pool_size]  (last section in the file)
 */
#ifndef CVM_H
#define CVM_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CVM_MAGIC_0 0x43
#define CVM_MAGIC_1 0x56
#define CVM_MAGIC_2 0x4D
#define CVM_MAGIC_3 0x04
#define CVM_VERSION_MAJOR 1
#define CVM_VERSION_MINOR 0
#define CVM_MODULE_HEADER_SIZE 40
#define CVM_FUNC_ENTRY_SIZE 20
#define CVM_GLOBAL_ENTRY_SIZE 8
#define CVM_NATIVE_ENTRY_SIZE 4
#define CVM_STRING_ENTRY_SIZE 8

#define CVM_MAX_NARGS 16
#define CVM_MAX_SARGS 6
#define CVM_SHIFT_MASK 63
#define CVM_SYS_READ 0
#define CVM_SYS_WRITE 1
#define CVM_SYS_EXIT 60

#define CVM_DATA_ARGC        0
#define CVM_DATA_ARGV        8
#define CVM_DATA_RSP         16
#define CVM_DATA_RBP         24
#define CVM_DATA_ARGS        32
#define CVM_DATA_RET         80
#define CVM_DATA_STACK_SIZE  88
#define CVM_DATA_STACK_BASE  96

typedef enum {
    OP_NOP          = 0x00,
    OP_PUSH_IMM64   = 0x01,
    OP_PUSH_IMM32   = 0x02,
    OP_PUSH_IMM8    = 0x03,
    OP_PUSH_ZERO    = 0x04,
    OP_PUSH_ONE     = 0x05,
    OP_PUSH_LOCAL   = 0x10,
    OP_STORE_LOCAL  = 0x11,
    OP_PUSH_GLOBAL  = 0x12,
    OP_STORE_GLOBAL = 0x13,
    OP_ADD          = 0x20,
    OP_SUB          = 0x21,
    OP_MUL          = 0x22,
    OP_DIV          = 0x23,
    OP_MOD          = 0x24,
    OP_NEG          = 0x25,
    OP_AND          = 0x30,
    OP_OR           = 0x31,
    OP_XOR          = 0x32,
    OP_NOT          = 0x33,
    OP_SHL          = 0x34,
    OP_SHR          = 0x35,
    OP_USHR         = 0x36,
    OP_CMP_EQ       = 0x40,
    OP_CMP_NE       = 0x41,
    OP_CMP_LT       = 0x42,
    OP_CMP_LE       = 0x43,
    OP_CMP_GT       = 0x44,
    OP_CMP_GE       = 0x45,
    OP_LNOT         = 0x46,
    OP_CMP_ULT      = 0x47,
    OP_CMP_ULE      = 0x48,
    OP_CMP_UGT      = 0x49,
    OP_CMP_UGE      = 0x4A,
    OP_JMP          = 0x50,
    OP_JZ           = 0x51,
    OP_JNZ          = 0x52,
    OP_CALL         = 0x60,
    OP_RET          = 0x61,
    OP_CALL_NATIVE  = 0x62,
    OP_LOAD16       = 0x6F,
    OP_STORE16      = 0x6E,
    OP_LOAD8        = 0x70,
    OP_LOAD32       = 0x71,
    OP_LOAD64       = 0x72,
    OP_STORE8       = 0x73,
    OP_STORE32      = 0x74,
    OP_STORE64      = 0x75,
    OP_LEA_LOCAL    = 0x76,
    OP_LEA_GLOBAL   = 0x77,
    OP_ALLOC        = 0x80,
    OP_FREE         = 0x81,
    OP_LEA_DATA     = 0x82,
    OP_SYSCALL      = 0x90,
    OP_HALT         = 0xFF
} CvmOpcode;

typedef enum {
    CVM_OK              =  0,
    CVM_ERR_ALLOC       = -1,
    CVM_ERR_STACK_OVER  = -2,
    CVM_ERR_STACK_UNDER = -3,
    CVM_ERR_BAD_OPCODE  = -4,
    CVM_ERR_BAD_MODULE  = -5,
    CVM_ERR_BAD_MAGIC   = -6,
    CVM_ERR_BAD_VERSION = -7,
    CVM_ERR_DIV_ZERO    = -8,
    CVM_ERR_BAD_FUNC    = -9,
    CVM_ERR_BAD_NATIVE  = -10,
    CVM_ERR_BAD_ADDR    = -11,
    CVM_ERR_FRAME_OVER  = -12,
    CVM_ERR_HEAP_OVER   = -13,
    CVM_ERR_IO          = -14,
    CVM_ERR_BOUNDS      = -15,
    CVM_ERR_NOMATCH     = -16,
    CVM_BREAK           =  17
} CvmError;

typedef struct {
    uint32_t name_off;
    uint32_t code_off;
    uint32_t num_locals;
    uint32_t argc;
    uint32_t flags;
} CvmFuncEntry;

typedef struct {
    uint32_t name_off;
    uint32_t size;
} CvmGlobalEntry;

typedef struct {
    uint32_t name_off;
} CvmNativeEntry;

typedef struct {
    uint32_t offset;
    uint32_t length;
} CvmStringEntry;

typedef struct {
    size_t stack_capacity;
    size_t max_frames;
    size_t max_locals_per_frame;
    size_t heap_size;
    size_t max_globals;
    size_t max_functions;
    size_t max_natives;
    size_t max_code_size;
    size_t max_profile_code;
    int    trace_enabled;
} CvmConfig;

typedef struct {
    uint64_t *slots;
    size_t    capacity;
    size_t    return_ip;
    uint32_t  func_idx;
} CvmFrame;

typedef int64_t (*CvmNativeFn)(void *vm, int argc, uint64_t *argv);

typedef struct {
    char        name[40];
    CvmNativeFn fn;
} CvmNative;

#define CVM_MAX_BREAKPOINTS 64

typedef struct {
    size_t ip;
} CvmBreakpoint;

typedef struct {
    uint64_t     *slots;
    size_t        capacity;
    size_t        sp;
    CvmFrame     *frames;
    size_t        frame_count;
    size_t        max_frames;
    uint8_t      *globals;
    size_t        globals_size;
    size_t        num_globals;
    uint8_t      *heap;
    size_t        heap_size;
    size_t        heap_used;
    uint8_t      *code;
    size_t        code_size;
    size_t        ip;
    int           running;
    int64_t       exit_code;
    uint64_t      instr_count;
    CvmConfig     config;
    CvmNative    *natives;
    size_t        num_natives;
    int32_t      *native_map;
    size_t        num_module_natives;
    char         *string_pool;
    size_t        string_pool_size;
    CvmFuncEntry *funcs;
    size_t        num_funcs;
    uint32_t      entry_func;
    CvmBreakpoint breakpoints[CVM_MAX_BREAKPOINTS];
    size_t        num_breakpoints;
    uint32_t     *ip_counts;
    uint32_t      op_counts[256];
    int           profile_enabled;
} CvmState;

CvmConfig   cvm_config_default(void);
CvmState   *cvm_create(const CvmConfig *config);
void        cvm_destroy(CvmState *vm);
int         cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);
int         cvm_load_module_file(CvmState *vm, const char *path);
int         cvm_run(CvmState *vm);
int         cvm_continue(CvmState *vm);
int         cvm_step(CvmState *vm);
int64_t     cvm_exit_code(const CvmState *vm);
uint64_t    cvm_instruction_count(const CvmState *vm);
const char *cvm_strerror(int error_code);

int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn);
int cvm_set_args(CvmState *vm, int argc, char **argv);
void *cvm_heap_alloc(CvmState *vm, size_t size);

int cvm_break_set(CvmState *vm, size_t ip);
int cvm_break_clear(CvmState *vm, size_t ip);
void cvm_break_clear_all(CvmState *vm);
int cvm_break_hit(const CvmState *vm);
int cvm_profile_begin(CvmState *vm);
void cvm_profile_end(CvmState *vm);

#ifdef __cplusplus
}
#endif
#endif
