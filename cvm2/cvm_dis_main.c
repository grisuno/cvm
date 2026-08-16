/**
 * @file cvm_dis_main.c
 * @brief Host front-end: cvm-dis <module.cvm> renders the module as text.
 * @license GPL-2.0-or-later
 */
#include "cvm_view.h"
#include "cvm_dis.h"
#include <stdio.h>
#include <stdlib.h>

static int print_line(void *ctx, const char *line) {
    FILE *f = (FILE *)ctx;
    fputs(line, f);
    fputc('\n', f);
    return 0;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <module.cvm>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "rb");
    if (!f) {
        fprintf(stderr, "cvm-dis: cannot open %s\n", argv[1]);
        return 1;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    rewind(f);
    if (sz < 0) {
        fprintf(stderr, "cvm-dis: cannot size %s\n", argv[1]);
        fclose(f);
        return 1;
    }
    uint8_t *buf = (uint8_t *)malloc((size_t)sz ? (size_t)sz : 1);
    if (!buf) {
        fprintf(stderr, "cvm-dis: out of memory\n");
        fclose(f);
        return 1;
    }
    if (fread(buf, 1, (size_t)sz, f) != (size_t)sz) {
        fprintf(stderr, "cvm-dis: read error\n");
        free(buf);
        fclose(f);
        return 1;
    }
    fclose(f);

    CvmModuleView v;
    int rc = cvm_view_open(&v, buf, (size_t)sz);
    if (rc != CVM_OK) {
        fprintf(stderr, "cvm-dis: %s: %s\n", argv[1], cvm_view_strerror(rc));
        free(buf);
        return 1;
    }
    rc = cvm_dis_module(&v, print_line, stdout);
    free(buf);
    if (rc != CVM_OK) {
        fprintf(stderr, "cvm-dis: %s: %s\n", argv[1], cvm_view_strerror(rc));
        return 1;
    }
    return 0;
}
