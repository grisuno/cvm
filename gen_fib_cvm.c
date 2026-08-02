/**
 * @file gen_fib_cvm.c
 * @brief Generate a .cvm module that computes fib(n) and verifies the result.
 * @license GPL-2.0-or-later
 */
#include "cvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIB_N 10
#define EXPECTED_FIB10 55

static uint8_t *code_buf;
static size_t code_cap;
static size_t code_len;

static void emit_byte(uint8_t b) {
    if (code_len + 1 > code_cap) {
        code_cap = code_cap ? code_cap * 2 : 256;
        code_buf = realloc(code_buf, code_cap);
        if (!code_buf) { fprintf(stderr, "oom\n"); exit(1); }
    }
    code_buf[code_len++] = b;
}

static void emit_u32(uint32_t v) {
    emit_byte((uint8_t)(v & 0xFF));
    emit_byte((uint8_t)((v >> 8) & 0xFF));
    emit_byte((uint8_t)((v >> 16) & 0xFF));
    emit_byte((uint8_t)((v >> 24) & 0xFF));
}

static void emit_i32(int32_t v) { emit_u32((uint32_t)v); }

static void patch_i32(size_t pos, int32_t val) {
    code_buf[pos]     = (uint8_t)(val & 0xFF);
    code_buf[pos + 1] = (uint8_t)((val >> 8) & 0xFF);
    code_buf[pos + 2] = (uint8_t)((val >> 16) & 0xFF);
    code_buf[pos + 3] = (uint8_t)((val >> 24) & 0xFF);
}

static void write_le32(uint8_t *p, uint32_t v) {
    p[0] = (uint8_t)(v & 0xFF);
    p[1] = (uint8_t)((v >> 8) & 0xFF);
    p[2] = (uint8_t)((v >> 16) & 0xFF);
    p[3] = (uint8_t)((v >> 24) & 0xFF);
}

int main(void) {
    code_buf = NULL;
    code_cap = 0;
    code_len = 0;

    /* === fib starts at code_off = 0 === */
    uint32_t fib_code_off = 0;

    emit_byte(OP_PUSH_LOCAL); emit_u32(0);
    emit_byte(OP_PUSH_ONE);
    emit_byte(OP_CMP_LE);
    emit_byte(OP_JZ);
    size_t jz_patch = code_len;
    emit_i32(0);

    emit_byte(OP_PUSH_LOCAL); emit_u32(0);
    emit_byte(OP_RET);

    int32_t l_recurse = (int32_t)code_len;
    patch_i32(jz_patch, l_recurse - (int32_t)(jz_patch + 4));

    emit_byte(OP_PUSH_LOCAL); emit_u32(0);
    emit_byte(OP_PUSH_ONE);
    emit_byte(OP_SUB);
    emit_byte(OP_CALL); emit_u32(0); emit_byte(1);

    emit_byte(OP_PUSH_LOCAL); emit_u32(0);
    emit_byte(OP_PUSH_IMM8); emit_byte(2);
    emit_byte(OP_SUB);
    emit_byte(OP_CALL); emit_u32(0); emit_byte(1);

    emit_byte(OP_ADD);
    emit_byte(OP_RET);

    /* === main starts here === */
    uint32_t main_code_off = (uint32_t)code_len;

    emit_byte(OP_PUSH_IMM8); emit_byte(FIB_N);
    emit_byte(OP_CALL); emit_u32(0); emit_byte(1);
    emit_byte(OP_HALT);

    /* === Build .cvm module === */
    uint32_t num_functions = 2;
    uint32_t num_globals = 0;
    uint32_t num_natives = 0;
    uint32_t num_strings = 0;
    uint32_t code_size = (uint32_t)code_len;
    uint32_t string_pool_size = 0;
    uint32_t entry_func = 1;

    size_t func_table_size = (size_t)num_functions * CVM_FUNC_ENTRY_SIZE;
    size_t total = CVM_MODULE_HEADER_SIZE + func_table_size + code_size;

    uint8_t *module = calloc(1, total);
    if (!module) { fprintf(stderr, "oom\n"); return 1; }

    module[0] = CVM_MAGIC_0; module[1] = CVM_MAGIC_1;
    module[2] = CVM_MAGIC_2; module[3] = CVM_MAGIC_3;
    module[4] = CVM_VERSION_MAJOR; module[5] = CVM_VERSION_MINOR;
    write_le32(module + 8, num_functions);
    write_le32(module + 12, num_globals);
    write_le32(module + 16, num_natives);
    write_le32(module + 20, num_strings);
    write_le32(module + 24, code_size);
    write_le32(module + 28, string_pool_size);
    write_le32(module + 32, entry_func);

    size_t ft_off = CVM_MODULE_HEADER_SIZE;
    write_le32(module + ft_off + 0, 0);
    write_le32(module + ft_off + 4, fib_code_off);
    write_le32(module + ft_off + 8, 4);
    write_le32(module + ft_off + 12, 1);
    write_le32(module + ft_off + 16, 0);

    write_le32(module + ft_off + 20, 0);
    write_le32(module + ft_off + 24, main_code_off);
    write_le32(module + ft_off + 28, 4);
    write_le32(module + ft_off + 32, 0);
    write_le32(module + ft_off + 36, 1);

    memcpy(module + CVM_MODULE_HEADER_SIZE + func_table_size, code_buf, code_len);

    FILE *f = fopen("fib.cvm", "wb");
    if (!f) { perror("fib.cvm"); free(module); free(code_buf); return 1; }
    fwrite(module, 1, total, f);
    fclose(f);
    printf("Generated fib.cvm (%zu bytes total, %zu bytes code)\n", total, code_len);

    CvmConfig cfg = cvm_config_default();
    CvmState *vm = cvm_create(&cfg);
    int rc = cvm_load_module(vm, module, total);
    if (rc != CVM_OK) {
        fprintf(stderr, "load failed: %s\n", cvm_strerror(rc));
        cvm_destroy(vm); free(module); free(code_buf); return 1;
    }
    rc = cvm_run(vm);
    if (rc != CVM_OK) {
        fprintf(stderr, "run failed: %s (ip=%zu)\n", cvm_strerror(rc), vm->ip);
        cvm_destroy(vm); free(module); free(code_buf); return 1;
    }
    int64_t result = cvm_exit_code(vm);
    printf("fib(%d) = %lld (expected %d)\n", FIB_N, (long long)result, EXPECTED_FIB10);
    printf("instructions: %lu\n", (unsigned long)cvm_instruction_count(vm));
    int ok = (result == EXPECTED_FIB10);
    printf("STATUS: %s\n", ok ? "PASS" : "FAIL");

    cvm_destroy(vm); free(module); free(code_buf);
    return ok ? 0 : 1;
}