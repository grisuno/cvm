CC      := gcc
CFLAGS  := -std=c99 -D_GNU_SOURCE -Wall -Wextra -Wpedantic -O2
LDFLAGS := -ldl

ifeq ($(QUIET),1)
  Q := @
else
  Q :=
endif

.PHONY: all clean test test-jit

all: cvm gen_fib_cvm cvm-dis cvm-validate cvmdbg

cvm: cvm.c cvm.h cvm_jit.c cvm_jit.h cvm_jit_x86.c cvm_jit_x86.h cvm_jit_help.c cvm_jit_help.h
	$(Q)$(CC) $(CFLAGS) -DCVM_STANDALONE -DCVM_JIT -o $@ cvm.c cvm_jit.c cvm_jit_x86.c cvm_jit_help.c $(LDFLAGS)

gen_fib_cvm: gen_fib_cvm.c cvm.c cvm.h cvm_jit.c cvm_jit.h cvm_jit_x86.c cvm_jit_x86.h cvm_jit_help.c cvm_jit_help.h
	$(Q)$(CC) $(CFLAGS) -DCVM_NO_MAIN -DCVM_JIT -o $@ gen_fib_cvm.c cvm.c cvm_jit.c cvm_jit_x86.c cvm_jit_help.c $(LDFLAGS)

cvm-dis: cvm_dis_main.c cvm_dis.c cvm_dis.h cvm_view.c cvm_view.h cvm_ops.c cvm_ops.h cvm.h
	$(Q)$(CC) $(CFLAGS) -o $@ cvm_dis_main.c cvm_dis.c cvm_view.c cvm_ops.c

cvm-validate: cvm_val_main.c cvm_view.c cvm_view.h cvm_ops.c cvm_ops.h cvm.h
	$(Q)$(CC) $(CFLAGS) -o $@ cvm_val_main.c cvm_view.c cvm_ops.c

cvmdbg: cvm_dbg_main.c cvm.c cvm.h cvm_dis.c cvm_dis.h cvm_view.c cvm_view.h cvm_ops.c cvm_ops.h
	$(Q)$(CC) $(CFLAGS) -DCVM_STANDALONE -DCVM_NO_MAIN -o $@ cvm_dbg_main.c cvm.c cvm_dis.c cvm_view.c cvm_ops.c $(LDFLAGS)

test: gen_fib_cvm cvm cvm-dis cvm-validate cvmdbg
	$(Q)./gen_fib_cvm
	$(Q)./cvm fib.cvm; test $$? -eq 55
	$(Q)./cvm-dis fib.cvm > fib.dis
	$(Q)grep -q "PUSH_LOCAL" fib.dis
	$(Q)grep -q "CALL" fib.dis
	$(Q)grep -q "; Function 1: func1" fib.dis
	$(Q)./cvm-validate fib.cvm
	$(Q)printf 'run\nbt\nquit\n' | ./cvmdbg fib.cvm > fib.dbg; test $$? -eq 55
	$(Q)grep -q "program exited: 55" fib.dbg

test-jit: gen_fib_cvm cvm
	$(Q)./gen_fib_cvm >/dev/null
	$(Q)echo "--- Interpreter ---"
	$(Q)./cvm fib.cvm; test $$? -eq 55
	$(Q)echo "--- JIT ---"
	$(Q)./cvm fib.cvm --jit; test $$? -eq 55
	$(Q)echo "--- JIT (via gen_fib_cvm) ---"
	$(Q)./gen_fib_cvm --jit | grep -q "STATUS: PASS"

clean:
	$(Q)rm -f cvm gen_fib_cvm cvm-dis cvm-validate cvmdbg fib.cvm *.o fib.dis fib.dbg
