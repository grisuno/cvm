#!/bin/bash
# CVM v2 toolchain suite: interpreter, disassembler, validator (including
# corrupted-module rejections) and the scripted debugger. Every check is
# a hard failure: a rejected module that validates, or a corrupted module
# that passes, fails the suite.
set -u

cd "$(dirname "$0")" || exit 1

PASS=0
FAIL=0

check() {
    local what="$1"; shift
    if "$@" > /dev/null 2>&1; then
        echo "    PASS  $what"
        PASS=$((PASS + 1))
    else
        echo "    FAIL  $what"
        FAIL=$((FAIL + 1))
    fi
}

reject() {
    local what="$1"; shift
    if "$@" > /dev/null 2>&1; then
        echo "    FAIL  $what (accepted a bad module)"
        FAIL=$((FAIL + 1))
    else
        echo "    PASS  $what"
        PASS=$((PASS + 1))
    fi
}

echo "--- cvm toolchain suite"
make all > /dev/null

./gen_fib_cvm > /dev/null
./cvm fib.cvm > /dev/null
check "interpreter: fib(10) exit 55" test $? -eq 55

./cvm-dis fib.cvm > fib.dis
check "disassembler: header summary" grep -q "; functions=2 globals=1" fib.dis
check "disassembler: function listing" grep -q "; Function 1: func1" fib.dis
check "disassembler: local access" grep -q "PUSH_LOCAL  0" fib.dis
check "disassembler: resolved jump target" grep -q "JZ          002a" fib.dis
check "disassembler: resolved call target" grep -q "CALL        0 1  ; func0" fib.dis

./cvm-validate fib.cvm > /dev/null
check "validator: fib.cvm valid" test $? -eq 0
check "validator: verbose balance" sh -c './cvm-validate -v fib.cvm | grep -q "stack balanced"'

cp fib.cvm bad_magic.cvm
printf '\x00' | dd of=bad_magic.cvm bs=1 seek=0 conv=notrunc 2>/dev/null
reject "validator: bad magic rejected" ./cvm-validate bad_magic.cvm

cp fib.cvm bad_jump.cvm
printf '\x01\x00\x00\x00' | dd of=bad_jump.cvm bs=1 seek=96 conv=notrunc 2>/dev/null
reject "validator: mid-instruction jump rejected" ./cvm-validate bad_jump.cvm

cp fib.cvm bad_stack.cvm
printf '\x20' | dd of=bad_stack.cvm bs=1 seek=159 conv=notrunc 2>/dev/null
reject "validator: entry underflow rejected" ./cvm-validate bad_stack.cvm

head -c 60 fib.cvm > trunc.cvm
reject "validator: truncated module rejected" ./cvm-validate trunc.cvm

printf 'run\nquit\n' | ./cvmdbg fib.cvm > fib.dbg
check "debugger: scripted run to exit" grep -q "program exited: 55" fib.dbg

printf 'break 0x0005\nrun\nbt\nquit\n' | ./cvmdbg fib.cvm > fib.dbg
check "debugger: breakpoint hit" grep -q "breakpoint at 0x0005" fib.dbg
check "debugger: backtrace frames" grep -q "#0 func0" fib.dbg

printf 'profile run\nprofile show\nquit\n' | ./cvmdbg fib.cvm > fib.dbg
check "debugger: profile counts fib calls" grep -q "0x0000 func0: 177" fib.dbg

rm -f fib.dis fib.dbg bad_magic.cvm bad_jump.cvm bad_stack.cvm trunc.cvm

echo "--- cvm toolchain suite: $PASS passed, $FAIL failed"
test "$FAIL" -eq 0
