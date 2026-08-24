/**
 * Minimal test: func0 pushes 42 and returns it. func1 calls func0, pushes result, halts.
 * Expected: exit code = 42.
 */
#include "cvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static uint8_t *code_buf;
static size_t code_cap;
static size_t code_len;

static void emit_byte(uint8_t b) {
    if (code_len + 1 > code_cap) {
        code_cap = code_cap ? code_cap * 2 : 256;
        code_buf = realloc(code_buf, code_cap);
    }
    code_buf[code_len++] = b;
}
static void emit_u32(uint32_t v) {
    emit_byte(v & 0xFF); emit_byte((v >> 8) & 0xFF);
    emit_byte((v >> 16) & 0xFF); emit_byte((v >> 24) & 0xFF);
}
static void write_le32(uint8_t *p, uint32_t v) {
    p[0] = v & 0xFF; p[1] = (v >> 8) & 0xFF;
    p[2] = (v >> 16) & 0xFF; p[3] = (v >> 24) & 0xFF;
}

int main(void) {
    code_buf = NULL; code_cap = 0; code_len = 0;

    /* func0: push_imm8 42; ret */
    uint32_t func0_off = 0;
    emit_byte(0x02); emit_byte(42);          /* PUSH_IMM8 42 */
    emit_byte(0x10);                          /* RET */

    /* func1: push_imm8 42; call func0, 1 arg; push result; halt */
    uint32_t func1_off = (uint32_t)code_len;
    emit_byte(0x02); emit_byte(42);          /* PUSH_IMM8 42 */
    emit_byte(0x0E); emit_u32(0); emit_byte(1); /* CALL func0, 1 arg */
    emit_byte(0x12); emit_u32(1);            /* STORE_LOCAL 1 */
    emit_byte(0x11); emit_u32(1);            /* PUSH_LOCAL 1 */
    emit_byte(0xFF);                          /* HALT */

    uint32_t code_size = (uint32_t)code_len;
    uint32_t ft = 2 * 20;  /* 2 functions, 20 bytes each */
    uint32_t gt = 1 * 8;   /* 1 global */
    size_t total = 40 + ft + gt + code_size;

    uint8_t *module = calloc(1, total);
    module[0] = 'C'; module[1] = 'V'; module[2] = 'M'; module[3] = 2;
    module[4] = 2; module[5] = 0;  /* version 2.0 */
    write_le32(module + 8, 2);    /* num_functions */
    write_le32(module + 12, 1);   /* num_globals */
    write_le32(module + 16, 0);   /* num_natives */
    write_le32(module + 20, 0);   /* num_strings */
    write_le32(module + 24, code_size);
    write_le32(module + 28, 0);   /* string_pool_size */
    write_le32(module + 32, 0);
    write_le32(module + 36, 1);   /* entry_func = 1 */

    size_t ft_off = 40;
    /* func0: num_args=0, code_off=func0_off, num_locals=1, num_globals=0, unused=0 */
    write_le32(module + ft_off + 0, 0);
    write_le32(module + ft_off + 4, func0_off);
    write_le32(module + ft_off + 8, 1);
    write_le32(module + ft_off + 12, 0);
    write_le32(module + ft_off + 16, 0);
    /* func1: num_args=0, code_off=func1_off, num_locals=2, num_globals=0, unused=0 */
    write_le32(module + ft_off + 20, 0);
    write_le32(module + ft_off + 24, func1_off);
    write_le32(module + ft_off + 28, 2);
    write_le32(module + ft_off + 32, 0);
    write_le32(module + ft_off + 36, 0);

    /* 1 global */
    write_le32(module + ft_off + ft + 0, 0);
    write_le32(module + ft_off + ft + 4, 8);

    memcpy(module + 40 + ft + gt, code_buf, code_size);

    FILE *f = fopen("minimal.cvm", "wb");
    fwrite(module, 1, total, f);
    fclose(f);
    printf("Generated minimal.cvm (%zu bytes)\n", total);

    CvmConfig cfg = cvm_config_default();
    CvmState *vm = cvm_create(&cfg);
    int rc = cvm_load_module(vm, module, total);
    if (rc) { fprintf(stderr, "load failed: %s\n", cvm_strerror(rc)); return 1; }
    rc = cvm_run(vm);
    if (rc) { fprintf(stderr, "run failed: %s\n", cvm_strerror(rc)); return 1; }
    printf("Interpreter exit code: %lld\n", (long long)cvm_exit_code(vm));

    /* Now test with JIT */
    CvmState *vm2 = cvm_create(&cfg);
    rc = cvm_load_module(vm2, module, total);
    if (rc) { fprintf(stderr, "load2 failed: %s\n", cvm_strerror(rc)); return 1; }
    vm2->jit_enabled = 1;  /* enable JIT */
    rc = cvm_run(vm2);
    if (rc) { fprintf(stderr, "run2 failed: %s\n", cvm_strerror(rc)); return 1; }
    printf("JIT exit code: %lld\n", (long long)cvm_exit_code(vm2));

    cvm_destroy(vm);
    cvm_destroy(vm2);
    free(module);
    free(code_buf);
    return 0;
}
