#!/usr/bin/env python3
"""Generate a minimal .cvm that pushes 42 and halts. No function calls."""
import struct, sys, subprocess

code = bytearray()

def emit_byte(b):
    code.append(b & 0xFF)

def emit_u32(v):
    code.extend(struct.pack('<I', v))

# func 0 (unused, but entry expects it):
# PUSH_IMM8 0; RET
emit_byte(0x02); emit_byte(0)   # PUSH_IMM8 0
emit_byte(0x10)                  # RET

# func 1 (entry): PUSH_IMM8 42; HALT
func1_off = len(code)
emit_byte(0x02); emit_byte(42)  # PUSH_IMM8 42
emit_byte(0xFF)                  # HALT

code_size = len(code)
num_funcs = 2
num_globals = 1
ft_size = num_funcs * 20
gt_size = num_globals * 8
header_size = 40
total = header_size + ft_size + gt_size + code_size

module = bytearray(total)
# Header
module[0:4] = b'CVM\x02'
module[4] = 2; module[5] = 0  # version
struct.pack_into('<I', module, 8, num_funcs)
struct.pack_into('<I', module, 12, num_globals)
struct.pack_into('<I', module, 16, 0)  # num_natives
struct.pack_into('<I', module, 20, 0)  # num_strings
struct.pack_into('<I', module, 24, code_size)
struct.pack_into('<I', module, 28, 0)  # string_pool_size
struct.pack_into('<I', module, 32, 0)
struct.pack_into('<I', module, 36, 1)  # entry_func = 1

# Function table
ft_off = header_size
# func 0: args=0, code_off=0, locals=1, globals=0
struct.pack_into('<I', module, ft_off + 0, 0)
struct.pack_into('<I', module, ft_off + 4, 0)
struct.pack_into('<I', module, ft_off + 8, 1)
struct.pack_into('<I', module, ft_off + 12, 0)
struct.pack_into('<I', module, ft_off + 16, 0)
# func 1: args=0, code_off=func1_off, locals=1, globals=0
struct.pack_into('<I', module, ft_off + 20, 0)
struct.pack_into('<I', module, ft_off + 24, func1_off)
struct.pack_into('<I', module, ft_off + 28, 1)
struct.pack_into('<I', module, ft_off + 32, 0)
struct.pack_into('<I', module, ft_off + 36, 0)

# Global table
gt_off = ft_off + ft_size
struct.pack_into('<I', module, gt_off + 0, 0)
struct.pack_into('<I', module, gt_off + 4, 8)

# Code
module[header_size + ft_size + gt_size:] = code

with open('minimal.cvm', 'wb') as f:
    f.write(module)

print(f"Generated minimal.cvm ({total} bytes, func1_off={func1_off})")
print(f"Bytecode: {[hex(b) for b in code]}")

# Test interpreter
r = subprocess.run(['./cvm', 'minimal.cvm'], capture_output=True, text=True, timeout=5)
print(f"Interpreter: exit={r.returncode} stderr={r.stderr.strip()}")

# Test JIT
r = subprocess.run(['./cvm', 'minimal.cvm', '--jit'], capture_output=True, text=True, timeout=5)
print(f"JIT: exit={r.returncode} stderr={r.stderr.strip()}")
