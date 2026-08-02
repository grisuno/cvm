CC      := gcc
CFLAGS  := -std=c99 -D_GNU_SOURCE -Wall -Wextra -Wpedantic -O2
LDFLAGS := -ldl

ifeq ($(QUIET),1)
  Q := @
else
  Q :=
endif

.PHONY: all clean test

all: cvm gen_fib_cvm

cvm: cvm.c cvm.h
	$(Q)$(CC) $(CFLAGS) -DCVM_STANDALONE -o $@ cvm.c $(LDFLAGS)

gen_fib_cvm: gen_fib_cvm.c cvm.c cvm.h
	$(Q)$(CC) $(CFLAGS) -DCVM_NO_MAIN -o $@ gen_fib_cvm.c cvm.c $(LDFLAGS)

test: gen_fib_cvm cvm
	$(Q)./gen_fib_cvm
	$(Q)./cvm fib.cvm

clean:
	$(Q)rm -f cvm gen_fib_cvm fib.cvm *.o