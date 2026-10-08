# cvm2: cvm_jit

*Community 2 | 5 files | cohesion 0.40*

## Definition

This community groups 5 file(s) rooted at `cvm2` with dominant language c (cohesion 0.40). Central symbols: `CVM_DIS_LINE_MAX`, `CVM_OPS_H`, `CVM_VAL_MAX_ARGS`, `CVM_VAL_MAX_CODE`, `CVM_VAL_MAX_FUNCS`, `CVM_VAL_MAX_GLOBALS`, `CVM_VAL_MAX_LOCALS`, `CVM_VAL_MAX_NATIVES`. Core file: `cvm2/cvm_jit.c` (37 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `cvm2/cvm_dis.c` | c | utility | 9 | no |
| `cvm2/cvm_jit.c` | c | utility | 37 | no |
| `cvm2/cvm_ops.c` | c | utility | 7 | no |
| `cvm2/cvm_ops.h` | h | utility | 9 | no |
| `cvm2/cvm_val_main.c` | c | utility | 25 | no |

## Key Symbols

- `CVM_DIS_LINE_MAX` (macro, `cvm2/cvm_dis.c:11`) `#define CVM_DIS_LINE_MAX`
- `putc_str` (function, `cvm2/cvm_dis.c:13`) `static void putc_str(char *buf, size_t cap, size_t *n, char c)`
- `puts_str` (function, `cvm2/cvm_dis.c:17`) `static void puts_str(char *buf, size_t cap, size_t *n, const char *s)`
- `put_hex` (function, `cvm2/cvm_dis.c:21`) `static void put_hex(char *buf, size_t cap, size_t *n, uint64_t v, int digits)`
- `put_dec` (function, `cvm2/cvm_dis.c:35`) `static void put_dec(char *buf, size_t cap, size_t *n, int64_t v)`
- `pad_name` (function, `cvm2/cvm_dis.c:49`) `static void pad_name(char *buf, size_t cap, size_t *n, const char *name)`
- `cvm_dis_line` (function, `cvm2/cvm_dis.c:56`) `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end,`
- `cvm_dis_function` (function, `cvm2/cvm_dis.c:153`) `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end,`
- `cvm_dis_module` (function, `cvm2/cvm_dis.c:173`) `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx)`
- `JIT_STATE` (macro, `cvm2/cvm_jit.c:30`) `#define JIT_STATE(vm)`
- `cvm_jit_create` (function, `cvm2/cvm_jit.c:36`) `CvmJitState *cvm_jit_create(void)`
- `cvm_jit_destroy` (function, `cvm2/cvm_jit.c:48`) `void cvm_jit_destroy(CvmJitState *jit)`
- `ip_map_clear` (function, `cvm2/cvm_jit.c:58`) `static void ip_map_clear(CvmJitState *jit)`
- `ip_map_add` (function, `cvm2/cvm_jit.c:62`) `static void ip_map_add(CvmJitState *jit, size_t bc_ip, size_t native_off)`
- `ip_map_lookup` (function, `cvm2/cvm_jit.c:69`) `static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip)`
- `func_cache_find` (function, `cvm2/cvm_jit.c:81`) `static JitFuncEntry *func_cache_find(CvmJitState *jit, uint32_t func_idx)`
- `func_cache_add` (function, `cvm2/cvm_jit.c:88`) `static JitFuncEntry *func_cache_add(CvmJitState *jit, uint32_t func_idx,`
- `opcode_total_size` (function, `cvm2/cvm_jit.c:105`) `static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip`
- `emit_stack_push` (function, `cvm2/cvm_jit.c:117`) `static void emit_stack_push(JitBuf *b)` - /* ------------------------------------------------------------------ static size_t opcode_total_siz
- `emit_stack_pop` (function, `cvm2/cvm_jit.c:124`) `static void emit_stack_pop(JitBuf *b)` - } /* ------------------------------------------------------------------ /*  Emit helpers: operand st
- `emit_stack_pop_into` (function, `cvm2/cvm_jit.c:130`) `static void emit_stack_pop_into(JitBuf *b, int dst)` - /* Push rax onto the operand stack: slots[sp] = rax; sp++ static void emit_stack_push(JitBuf *b) { /
- `emit_stack_push_reg` (function, `cvm2/cvm_jit.c:136`) `static void emit_stack_push_reg(JitBuf *b, int reg)` - /* Pop from operand stack into rax: sp--; rax = slots[sp] static void emit_stack_pop(JitBuf *b) { em
- `emit_call1` (function, `cvm2/cvm_jit.c:146`) `static void emit_call1(JitBuf *b, void *fn, int arg)` - emit_mov_reg_sib(b, dst, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Push a register onto the operand stack
- `emit_call2` (function, `cvm2/cvm_jit.c:152`) `static void emit_call2(JitBuf *b, void *fn, int a1, int a2)` - emit_inc_reg(b, JIT_REG_SP); } /* ------------------------------------------------------------------
- `emit_call3` (function, `cvm2/cvm_jit.c:159`) `static void emit_call3(JitBuf *b, void *fn, int a1, int a2, int a3)` - /* Call a C function with 1 arg (rdi).  Clobbers rax, rcx, rdx, rsi, rdi, r8-r11. static void emit_c
- `emit_prologue` (function, `cvm2/cvm_jit.c:170`) `static void emit_prologue(JitBuf *b)`
- `emit_epilogue` (function, `cvm2/cvm_jit.c:232`) `static void emit_epilogue(JitBuf *b)`
- `emit_save_sp` (function, `cvm2/cvm_jit.c:252`) `static void emit_save_sp(JitBuf *b)` - emit_pop(b, JIT_REG_SP);      /* r13 emit_pop(b, JIT_REG_SLOTS);   /* r12 emit_pop(b, JIT_REG_FRAME)
- `emit_restore_sp` (function, `cvm2/cvm_jit.c:258`) `static void emit_restore_sp(JitBuf *b)` - emit_ret(b); } /* ------------------------------------------------------------------ /*  Emit: save/
- `error` (function, `cvm2/cvm_jit.c:267`) `* keeps executing dead code after the stop: error() -> exit() returns  * into th`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 4
- Cross-boundary resolved imports (EXTRACTED): 5

## Connections

- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: cvm2/cvm_dbg_main.c imports cvm2/cvm_ops.h.
- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: cvm2/cvm_jit.c imports cvm2/cvm_jit.h.
- [INFERRED] bridges community 2 <-> 0 (strength 0.5): Inferred cross-community bridge: cvm2/cvm_dis.c reaches cvm2/cvm_jit_x86.c in 5 hops.
- [INFERRED] bridges community 0 <-> 2 (strength 0.5): Inferred cross-community bridge: cvm2/cvm_jit_x86.c reaches cvm2/cvm_val_main.c in 5 hops.

## Risks

- [dataflow DEAD_STORE] `cvm2/cvm_jit.c:1299` `cvm_jit_compile_func` `instr_start_native`: `instr_start_native` assigned at line 1299 but never read afterwards.

## Open Questions

- Why do 5 file(s) lack file-level docs (e.g. `cvm2/cvm_dis.c`)? What purpose do they serve?
- What would break if the most connected file in cvm2: cvm_jit changed?
- Should cvm2: cvm_jit be split, given cohesion 0.40?

## Sources

- `cvm2/cvm_dis.c`
- `cvm2/cvm_jit.c`
- `cvm2/cvm_ops.c`
- `cvm2/cvm_ops.h`
- `cvm2/cvm_val_main.c`
