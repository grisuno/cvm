# Architecture

## Internal Dependencies

- `cvm.c` -> `cvm.h`
- `cvm2/cvm.c` -> `cvm2/cvm.h`
- `cvm2/cvm.c` -> `cvm2/cvm_jit.h`
- `cvm2/cvm_dbg_main.c` -> `cvm2/cvm.h`
- `cvm2/cvm_dbg_main.c` -> `cvm2/cvm_dis.h`
- `cvm2/cvm_dbg_main.c` -> `cvm2/cvm_ops.h`
- `cvm2/cvm_dbg_main.c` -> `cvm2/cvm_view.h`
- `cvm2/cvm_dis.c` -> `cvm2/cvm_dis.h`
- `cvm2/cvm_dis.c` -> `cvm2/cvm_ops.h`
- `cvm2/cvm_dis.h` -> `cvm2/cvm_view.h`
- `cvm2/cvm_dis_main.c` -> `cvm2/cvm_dis.h`
- `cvm2/cvm_dis_main.c` -> `cvm2/cvm_view.h`
- `cvm2/cvm_jit.c` -> `cvm2/cvm_jit.h`
- `cvm2/cvm_jit.c` -> `cvm2/cvm_ops.h`
- `cvm2/cvm_jit.h` -> `cvm2/cvm.h`
- `cvm2/cvm_jit.h` -> `cvm2/cvm_jit_help.h`
- `cvm2/cvm_jit.h` -> `cvm2/cvm_jit_x86.h`
- `cvm2/cvm_jit_help.c` -> `cvm2/cvm_jit.h`
- `cvm2/cvm_jit_help.c` -> `cvm2/cvm_jit_help.h`
- `cvm2/cvm_jit_help.h` -> `cvm2/cvm.h`
- `cvm2/cvm_jit_x86.c` -> `cvm2/cvm_jit_x86.h`
- `cvm2/cvm_ops.c` -> `cvm2/cvm.h`
- `cvm2/cvm_ops.c` -> `cvm2/cvm_ops.h`
- `cvm2/cvm_val_main.c` -> `cvm2/cvm_ops.h`
- `cvm2/cvm_val_main.c` -> `cvm2/cvm_view.h`
- `cvm2/cvm_view.c` -> `cvm2/cvm_view.h`
- `cvm2/cvm_view.h` -> `cvm2/cvm.h`
- `cvm2/gen_fib_cvm.c` -> `cvm2/cvm.h`
- `cvm2/gen_fib_cvm.c` -> `cvm2/cvm_jit.h`
- `cvm2/gen_minimal.c` -> `cvm2/cvm.h`
- `gen_fib_cvm.c` -> `cvm.h`

## External Imports

- `cvm.c` -> errno.h, stdarg.h
- `cvm.h` -> dlfcn.h, stddef.h, stdint.h, stdio.h, stdlib.h, string.h, sys/mman.h, unistd.h
- `cvm2/cvm.c` -> stdio.h, stdlib.h, string.h, unistd.h
- `cvm2/cvm.h` -> stddef.h, stdint.h, stdio.h, stdlib.h, string.h, unistd.h
- `cvm2/cvm_dbg_main.c` -> stdio.h, stdlib.h, string.h, unistd.h
- `cvm2/cvm_dis.c` -> string.h
- `cvm2/cvm_dis.h` -> stddef.h, stdint.h
- `cvm2/cvm_dis_main.c` -> stdio.h, stdlib.h
- `cvm2/cvm_jit.c` -> stdio.h, stdlib.h, string.h
- `cvm2/cvm_jit_help.c` -> stdlib.h, string.h, unistd.h
- `cvm2/cvm_jit_x86.c` -> stdlib.h, string.h, sys/mman.h
- `cvm2/cvm_jit_x86.h` -> stddef.h, stdint.h
- `cvm2/cvm_ops.h` -> stddef.h, stdint.h
- `cvm2/cvm_val_main.c` -> stdio.h, stdlib.h, string.h
- `cvm2/cvm_view.c` -> string.h
- `cvm2/cvm_view.h` -> stddef.h, stdint.h
- `cvm2/gen_fib_cvm.c` -> stdio.h, stdlib.h, string.h
- `cvm2/gen_minimal.c` -> stdio.h, stdlib.h, string.h
- `cvm2/gen_test.py` -> struct, subprocess, sys
- `gen_fib_cvm.c` -> stdio.h, stdlib.h, string.h
