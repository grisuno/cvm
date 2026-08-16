CC      := gcc
CFLAGS  := -std=c99 -D_GNU_SOURCE -Wall -Wextra -Wpedantic -O2
LDFLAGS := -ldl

ifeq ($(QUIET),1)
  Q := @
else
  Q :=
endif

.PHONY: all clean test

all: cvm gen_fib_cvm cvm-dis cvm-validate cvmdbg

cvm: cvm.c cvm.h
	$(Q)$(CC) $(CFLAGS) -DCVM_STANDALONE -o $@ cvm.c $(LDFLAGS)

gen_fib_cvm: gen_fib_cvm.c cvm.c cvm.h
	$(Q)$(CC) $(CFLAGS) -DCVM_NO_MAIN -o $@ gen_fib_cvm.c cvm.c $(LDFLAGS)

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
	$(Q)grep -q "; Function 1: main" fib.dis
	$(Q)./cvm-validate fib.cvm
	$(Q)printf 'run\nbt\nquit\n' | ./cvmdbg fib.cvm > fib.dbg
	$(Q)grep -q "program exited: 55" fib.dbg

clean:
	$(Q)rm -f cvm gen_fib_cvm cvm-dis cvm-validate cvmdbg fib.cvm *.o fib.dis fib.dbg
