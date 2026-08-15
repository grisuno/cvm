/*
 * cvm.h — C Virtual Machine
 * Minimal stack-based VM for a C subset (inspired by miniGCC / lazyc).
 * Format: .cvm modules (header + tables + bytecode + string pool)
 */

#ifndef CVM_H
#define CVM_H

#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <sys/mman.h>

/* ------------------------------------------------------------------ */
/*  Magic & version                                                   */
/* ------------------------------------------------------------------ */
#define CVM_MAGIC   0x314D5643u   /* 'CVM1' little-endian */
#define CVM_VERSION 1

/* ------------------------------------------------------------------ */
/*  Opcodes (1 byte)                                                  */
/* ------------------------------------------------------------------ */
enum {
    /* Constants / stack */
    OP_NOP          = 0x00,
    OP_PUSH_I8      = 0x01,   /* int8  → i64 */
    OP_PUSH_I32     = 0x02,   /* int32 → i64 */
    OP_PUSH_I64     = 0x03,   /* int64 */
    OP_PUSH_F64     = 0x04,   /* double (as bits) */
    OP_DUP          = 0x05,
    OP_POP          = 0x06,
    OP_SWAP         = 0x07,

    /* Locals (frame relative, signed 16-bit offset from frame base) */
    OP_LOAD_LOCAL   = 0x10,   /* i16 offset */
    OP_STORE_LOCAL  = 0x11,
    OP_LEA_LOCAL    = 0x12,   /* address of local */

    /* Globals (module-relative index) */
    OP_LOAD_GLOBAL  = 0x18,   /* u16 index */
    OP_STORE_GLOBAL = 0x19,
    OP_LEA_GLOBAL   = 0x1A,

    /* Pointers / memory */
    OP_LOAD8        = 0x20,   /* (addr) → i8  sign-extend */
    OP_LOAD32       = 0x21,
    OP_LOAD64       = 0x22,
    OP_STORE8       = 0x23,
    OP_STORE32      = 0x24,
    OP_STORE64      = 0x25,
    OP_LOAD_PTR     = 0x26,   /* synonym of LOAD64 */
    OP_STORE_PTR    = 0x27,

    /* Arithmetic */
    OP_ADD          = 0x40,
    OP_SUB          = 0x41,
    OP_MUL          = 0x42,
    OP_DIV          = 0x43,
    OP_MOD          = 0x44,
    OP_NEG          = 0x45,
    OP_AND          = 0x46,
    OP_OR           = 0x47,
    OP_XOR          = 0x48,
    OP_NOT          = 0x49,
    OP_SHL          = 0x4A,
    OP_SHR          = 0x4B,   /* arithmetic */
    OP_USHR         = 0x4C,   /* logical */

    /* Comparison → 0/1 */
    OP_CMP_EQ       = 0x50,
    OP_CMP_NE       = 0x51,
    OP_CMP_LT       = 0x52,
    OP_CMP_LE       = 0x53,
    OP_CMP_GT       = 0x54,
    OP_CMP_GE       = 0x55,

    /* Control flow (relative signed 32-bit from after the operand) */
    OP_JMP          = 0x60,
    OP_JZ           = 0x61,
    OP_JNZ          = 0x62,

    /* Calls */
    OP_CALL         = 0x70,   /* u16 func_index, u8 argc */
    OP_CALL_NATIVE  = 0x71,   /* u16 native_index, u8 argc */
    OP_RET          = 0x72,
    OP_RET_VOID     = 0x73,

    /* Heap */
    OP_ALLOC        = 0x80,   /* size on stack → ptr */
    OP_FREE         = 0x81,

    /* Syscalls / misc */
    OP_SYSCALL      = 0x90,   /* nr, arg0..arg5 on stack (Linux x86-64 style) */
    OP_PRINT_I64    = 0x91,   /* debug helper */
    OP_HALT         = 0xFF
};

/* ------------------------------------------------------------------ */
/*  Module format (on disk / in memory)                               */
/* ------------------------------------------------------------------ */
#pragma pack(push, 1)
typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t num_functions;
    uint32_t num_globals;
    uint32_t num_strings;
    uint32_t num_natives;
    uint32_t code_size;       /* bytes of bytecode */
    uint32_t string_pool_size;
    /* followed by:
     *   CVM_FuncEntry[num_functions]
     *   CVM_GlobalEntry[num_globals]
     *   CVM_StringEntry[num_strings]
     *   CVM_NativeEntry[num_natives]
     *   uint8_t code[code_size]
     *   char string_pool[string_pool_size]
     */
} CVM_Header;

typedef struct {
    uint32_t name_off;        /* offset into string pool */
    uint32_t code_off;        /* offset into code section */
    uint16_t max_locals;      /* number of local slots (64-bit) */
    uint16_t max_stack;       /* max operand stack depth (hint) */
    uint8_t  argc;            /* number of parameters */
    uint8_t  is_main;
    uint16_t reserved;
} CVM_FuncEntry;

typedef struct {
    uint32_t name_off;
    uint32_t size;            /* in bytes (usually 8) */
    uint64_t init_value;
} CVM_GlobalEntry;

typedef struct {
    uint32_t offset;          /* into string pool */
    uint32_t length;
} CVM_StringEntry;

typedef struct {
    uint32_t name_off;        /* "printf", "write", ... */
} CVM_NativeEntry;
#pragma pack(pop)

/* ------------------------------------------------------------------ */
/*  Runtime structures                                                */
/* ------------------------------------------------------------------ */
#define CVM_STACK_SIZE     (64 * 1024)   /* 64k slots */
#define CVM_FRAME_DEPTH    256
#define CVM_HEAP_SIZE      (16 * 1024 * 1024)
#define CVM_MAX_MODULES    32
#define CVM_MAX_NATIVES    256

typedef struct {
    uint64_t *locals;         /* base of this frame's locals */
    uint32_t  return_ip;
    uint16_t  func_idx;
    uint16_t  num_locals;
    uint32_t  stack_base;     /* operand stack pointer when frame was entered */
} CVM_Frame;

typedef struct CVM_Module {
    CVM_Header      hdr;
    CVM_FuncEntry  *funcs;
    CVM_GlobalEntry*globals;
    CVM_StringEntry*strings;
    CVM_NativeEntry*natives;
    uint8_t        *code;
    char           *string_pool;
    uint64_t       *global_mem;   /* runtime storage for globals */
    void           *native_ptrs[CVM_MAX_NATIVES];
    char            name[64];
} CVM_Module;

typedef struct {
    /* Operand stack */
    uint64_t   *stack;
    int32_t     sp;               /* next free slot */

    /* Frames */
    CVM_Frame   frames[CVM_FRAME_DEPTH];
    int32_t     fp;               /* current frame index (-1 = none) */

    /* Code */
    uint8_t    *code;
    uint32_t    ip;
    uint32_t    code_size;

    /* Modules */
    CVM_Module *modules[CVM_MAX_MODULES];
    int         num_modules;
    CVM_Module *current;          /* module of current function */

    /* Heap (bump allocator for simplicity) */
    uint8_t    *heap;
    size_t      heap_used;
    size_t      heap_size;

    /* Stats / debug */
    uint64_t    instr_count;
    int         running;
    int         trace;
} CVM;

/* ------------------------------------------------------------------ */
/*  Public API                                                        */
/* ------------------------------------------------------------------ */
CVM        *cvm_create(void);
void        cvm_destroy(CVM *vm);
int         cvm_load_module(CVM *vm, const char *path);
int         cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);
int         cvm_run(CVM *vm, const char *entry_name);
int         cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);

/* Helpers used by the backend emitter */
void        cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);
void        cvm_emit_i16 (uint8_t **buf, size_t *cap, size_t *len, int16_t v);
void        cvm_emit_i32 (uint8_t **buf, size_t *cap, size_t *len, int32_t v);
void        cvm_emit_i64 (uint8_t **buf, size_t *cap, size_t *len, int64_t v);
void        cvm_emit_u16 (uint8_t **buf, size_t *cap, size_t *len, uint16_t v);

#endif /* CVM_H */
