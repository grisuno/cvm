# cvm2: cvm_dbg_main

*Community 1 | 5 files | cohesion 0.46*

## Definition

This community groups 5 file(s) rooted at `cvm2` with dominant language c (cohesion 0.46). Central symbols: `CVM_DIS_H`, `CVM_VIEW_H`, `CvmModuleView`, `DBG_LINE_MAX`, `DBG_PROFILE_TOP`, `cmd_break`, `cmd_bt`, `cmd_delete`. Core file: `cvm2/cvm_dbg_main.c` (21 symbols).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `cvm2/cvm_dbg_main.c` | c | utility | 21 | no |
| `cvm2/cvm_dis.h` | h | utility | 4 | no |
| `cvm2/cvm_dis_main.c` | c | utility | 2 | no |
| `cvm2/cvm_view.c` | c | presentation | 8 | no |
| `cvm2/cvm_view.h` | h | presentation | 9 | no |

## Key Symbols

- `DBG_LINE_MAX` (macro, `cvm2/cvm_dbg_main.c:18`) `#define DBG_LINE_MAX`
- `DBG_PROFILE_TOP` (macro, `cvm2/cvm_dbg_main.c:19`) `#define DBG_PROFILE_TOP`
- `emit_stdout` (function, `cvm2/cvm_dbg_main.c:29`) `static int emit_stdout(void *ctx, const char *line)`
- `func_display` (function, `cvm2/cvm_dbg_main.c:36`) `static const char *func_display(uint32_t fi, char *fb, size_t cap)`
- `func_of_ip` (function, `cvm2/cvm_dbg_main.c:40`) `static int func_of_ip(size_t ip)`
- `parse_u32` (function, `cvm2/cvm_dbg_main.c:51`) `static int parse_u32(const char *s, uint32_t *out)`
- `report_run` (function, `cvm2/cvm_dbg_main.c:59`) `static void report_run(int rc)`
- `cmd_list` (function, `cvm2/cvm_dbg_main.c:71`) `static void cmd_list(char *arg)`
- `cmd_break` (function, `cvm2/cvm_dbg_main.c:98`) `static void cmd_break(char *arg)`
- `cmd_delete` (function, `cvm2/cvm_dbg_main.c:133`) `static void cmd_delete(char *arg)`
- `cmd_step` (function, `cvm2/cvm_dbg_main.c:152`) `static void cmd_step(void)`
- `cmd_next` (function, `cvm2/cvm_dbg_main.c:166`) `static void cmd_next(void)`
- `cmd_run` (function, `cvm2/cvm_dbg_main.c:184`) `static void cmd_run(void)`
- `cmd_bt` (function, `cvm2/cvm_dbg_main.c:194`) `static void cmd_bt(void)`
- `cmd_stack` (function, `cvm2/cvm_dbg_main.c:206`) `static void cmd_stack(void)`
- `cmd_locals` (function, `cvm2/cvm_dbg_main.c:213`) `static void cmd_locals(void)`
- `cmd_info` (function, `cvm2/cvm_dbg_main.c:225`) `static void cmd_info(void)`
- `cmd_profile` (function, `cvm2/cvm_dbg_main.c:241`) `static void cmd_profile(char *arg)`
- `cmd_help` (function, `cvm2/cvm_dbg_main.c:304`) `static void cmd_help(void)`
- `dispatch` (function, `cvm2/cvm_dbg_main.c:310`) `static void dispatch(char *line)`
- `main` (function, `cvm2/cvm_dbg_main.c:337`) `int main(int argc, char **argv)`
- `CVM_DIS_H` (macro, `cvm2/cvm_dis.h:10`) `#define CVM_DIS_H`
- `cvm_dis_module` (function, `cvm2/cvm_dis.h:23`) `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx);` - #ifndef CVM_DIS_H #define CVM_DIS_H #include <stddef.h> #include <stdint.h> #include "cvm_view.h" #i
- `cvm_dis_function` (function, `cvm2/cvm_dis.h:26`) `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end, CvmDisEmi` - #include <stddef.h> #include <stdint.h> #include "cvm_view.h" #ifdef __cplusplus extern "C" { #endif
- `cvm_dis_line` (function, `cvm2/cvm_dis.h:31`) `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end, char *buf, size` - One instruction at code offset off (within [begin,end)). Returns the * instruction size, or -1 when
- `print_line` (function, `cvm2/cvm_dis_main.c:11`) `static int print_line(void *ctx, const char *line)`
- `main` (function, `cvm2/cvm_dis_main.c:18`) `int main(int argc, char **argv)`
- `rl32` (function, `cvm2/cvm_view.c:9`) `static uint32_t rl32(const uint8_t *p)`
- `rl16` (function, `cvm2/cvm_view.c:14`) `static uint32_t rl16(const uint8_t *p)`
- `cvm_view_strerror` (function, `cvm2/cvm_view.c:18`) `const char *cvm_view_strerror(int error_code)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 6
- Cross-boundary resolved imports (EXTRACTED): 5

## Connections

- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: cvm2/cvm_dbg_main.c imports cvm2/cvm.h.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: cvm2/cvm_dbg_main.c imports cvm2/cvm_ops.h.
- [INFERRED] bridges community 1 <-> 0 (strength 0.5): Inferred cross-community bridge: cvm2/cvm_dis.h reaches cvm2/cvm_jit_x86.c in 5 hops.
- [INFERRED] bridges community 1 <-> 0 (strength 0.5): Inferred cross-community bridge: cvm2/cvm_dis_main.c reaches cvm2/cvm_jit_x86.c in 5 hops.
- [INFERRED] bridges community 0 <-> 1 (strength 0.5): Inferred cross-community bridge: cvm2/cvm_jit_x86.c reaches cvm2/cvm_view.c in 5 hops.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 5 file(s) lack file-level docs (e.g. `cvm2/cvm_dbg_main.c`)? What purpose do they serve?
- What would break if the most connected file in cvm2: cvm_dbg_main changed?
- Should cvm2: cvm_dbg_main be split, given cohesion 0.46?

## Sources

- `cvm2/cvm_dbg_main.c`
- `cvm2/cvm_dis.h`
- `cvm2/cvm_dis_main.c`
- `cvm2/cvm_view.c`
- `cvm2/cvm_view.h`
