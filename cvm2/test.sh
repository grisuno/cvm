#!/bin/bash
make all
gcc -std=c99 -D_GNU_SOURCE -Wall -Wextra -Wpedantic -O2 -DCVM_STANDALONE -o cvm cvm.c -ldl
gcc -std=c99 -D_GNU_SOURCE -Wall -Wextra -Wpedantic -O2 -DCVM_NO_MAIN -o gen_fib_cvm gen_fib_cvm.c cvm.c -ldl

./gen_fib_cvm


./cvm fib.cvm > fib.cvm.log
echo $?

./cvm fib.cvm --trace > fib.cvm.trace.log

echo $?
