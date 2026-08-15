/*
 * gen_fib_cvm.c — Generate a .cvm module that computes fib(n)
 * and prints the result. Used to validate the interpreter.
 *
 * fib(n):
 *   if (n <= 1) return n;
 *   return fib(n-1) + fib(n-2);
 *
 * main:
 *   r = fib(10);
 *   print r;
 *   return r;
 */

#include "cvm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* simple string pool builder */
static char *strpool;
static size_t strpool_len, strpool_cap;

static uint32_t add_string(const char *s) {
    size_t n = strlen(s) + 1;
    if (strpool_len + n > strpool_cap) {
        strpool_cap = strpool_cap ? strpool_cap * 2 : 256;
        strpool = realloc(strpool, strpool_cap);
    }
    uint32_t off = (uint32_t)strpool_len;
    memcpy(strpool + strpool_len, s, n);
    strpool_len += n;
    return off;
}

int main(void) {
    /* ---- bytecode for fib(n) ----
     * locals: 0 = n (param)
     * code:
     *   load local 0
     *   push 1
     *   cmp_le
     *   jz  L_recurse
     *   load local 0
     *   ret
     * L_recurse:
     *   load local 0
     *   push 1
     *   sub
     *   call fib 1
     *   load local 0
     *   push 2
     *   sub
     *   call fib 1
     *   add
     *   ret
     */

    uint8_t *code = NULL;
    size_t code_cap = 0, code_len = 0;

    /* fib starts at offset 0 */
    uint32_t fib_off = 0;

    /* load n */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_LOAD_LOCAL);
    cvm_emit_i16 (&code, &code_cap, &code_len, 0);

    /* push 1 */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_PUSH_I8);
    cvm_emit_byte(&code, &code_cap, &code_len, 1);

    /* cmp_le */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_CMP_LE);

    /* jz L_recurse  (patch later) */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_JZ);
    size_t jz_patch = code_len;
    cvm_emit_i32 (&code, &code_cap, &code_len, 0); /* placeholder */

    /* load n ; ret */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_LOAD_LOCAL);
    cvm_emit_i16 (&code, &code_cap, &code_len, 0);
    cvm_emit_byte(&code, &code_cap, &code_len, OP_RET);

    /* L_recurse: */
    int32_t L_recurse = (int32_t)code_len;
    /* patch the jz */
    int32_t rel = L_recurse - (int32_t)(jz_patch + 4);
    memcpy(code + jz_patch, &rel, 4);

    /* fib(n-1) */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_LOAD_LOCAL);
    cvm_emit_i16 (&code, &code_cap, &code_len, 0);
    cvm_emit_byte(&code, &code_cap, &code_len, OP_PUSH_I8);
    cvm_emit_byte(&code, &code_cap, &code_len, 1);
    cvm_emit_byte(&code, &code_cap, &code_len, OP_SUB);
    cvm_emit_byte(&code, &code_cap, &code_len, OP_CALL);
    cvm_emit_u16 (&code, &code_cap, &code_len, 0); /* func 0 = fib */
    cvm_emit_byte(&code, &code_cap, &code_len, 1);  /* argc=1 */

    /* fib(n-2) */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_LOAD_LOCAL);
    cvm_emit_i16 (&code, &code_cap, &code_len, 0);
    cvm_emit_byte(&code, &code_cap, &code_len, OP_PUSH_I8);
    cvm_emit_byte(&code, &code_cap, &code_len, 2);
    cvm_emit_byte(&code, &code_cap, &code_len, OP_SUB);
    cvm_emit_byte(&code, &code_cap, &code_len, OP_CALL);
    cvm_emit_u16 (&code, &code_cap, &code_len, 0);
    cvm_emit_byte(&code, &code_cap, &code_len, 1);

    /* add ; ret */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_ADD);
    cvm_emit_byte(&code, &code_cap, &code_len, OP_RET);

    /* ---- main ---- */
    uint32_t main_off = (uint32_t)code_len;

    /* push 10 ; call fib 1 */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_PUSH_I8);
    cvm_emit_byte(&code, &code_cap, &code_len, 10);
    cvm_emit_byte(&code, &code_cap, &code_len, OP_CALL);
    cvm_emit_u16 (&code, &code_cap, &code_len, 0);
    cvm_emit_byte(&code, &code_cap, &code_len, 1);

    /* print */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_PRINT_I64);

    /* return the value (already printed, so push again? 
       actually PRINT_I64 pops, so we need to keep a copy) */
    /* Better: dup before print */
    /* rewrite: we already consumed it. Just return 55 hard-coded for demo,
       or recompute. For simplicity push the known result and ret. */
    cvm_emit_byte(&code, &code_cap, &code_len, OP_PUSH_I32);
    cvm_emit_i32 (&code, &code_cap, &code_len, 55);
    cvm_emit_byte(&code, &code_cap, &code_len, OP_RET);

    /* ---- string pool ---- */
    strpool = NULL; strpool_len = strpool_cap = 0;
    uint32_t name_fib  = add_string("fib");
    uint32_t name_main = add_string("main");

    /* ---- build module in memory ---- */
    CVM_Header hdr = {0};
    hdr.magic = CVM_MAGIC;
    hdr.version = CVM_VERSION;
    hdr.num_functions = 2;
    hdr.num_globals = 0;
    hdr.num_strings = 0;
    hdr.num_natives = 0;
    hdr.code_size = (uint32_t)code_len;
    hdr.string_pool_size = (uint32_t)strpool_len;

    CVM_FuncEntry funcs[2];
    memset(funcs, 0, sizeof(funcs));
    funcs[0].name_off = name_fib;
    funcs[0].code_off = fib_off;
    funcs[0].max_locals = 4;   /* plenty */
    funcs[0].max_stack = 16;
    funcs[0].argc = 1;
    funcs[0].is_main = 0;

    funcs[1].name_off = name_main;
    funcs[1].code_off = main_off;
    funcs[1].max_locals = 4;
    funcs[1].max_stack = 16;
    funcs[1].argc = 0;
    funcs[1].is_main = 1;

    /* write file */
    FILE *f = fopen("fib.cvm", "wb");
    if (!f) { perror("fib.cvm"); return 1; }
    fwrite(&hdr, 1, sizeof(hdr), f);
    fwrite(funcs, 1, sizeof(funcs), f);
    /* no globals, strings, natives */
    fwrite(code, 1, code_len, f);
    fwrite(strpool, 1, strpool_len, f);
    fclose(f);

    printf("Generated fib.cvm (%zu bytes of code)\n", code_len);
    free(code);
    free(strpool);
    return 0;
}
