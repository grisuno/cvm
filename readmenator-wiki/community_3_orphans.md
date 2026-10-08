# orphans

*Community 3 | 4 files | cohesion 0.00*

## Definition

This community groups 4 file(s) rooted at `cvm2` with dominant language sh (cohesion 0.00). Central symbols: `check`, `emit_byte`, `emit_u32`, `reject`. Core file: `cvm2/gen_test.py` (2 symbols). Documented purpose: Generate a minimal .cvm that pushes 42 and halts. No function calls..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `cvm2/deepseek_bash_20260808_653f26.sh` | sh | utility | 0 | no |
| `cvm2/gen_test.py` | py | testing | 2 | yes |
| `cvm2/test.sh` | sh | testing | 2 | yes |
| `test.sh` | sh | testing | 0 | no |

## Key Symbols

- `emit_byte` (function, `cvm2/gen_test.py:7`) `def emit_byte(b)`
- `emit_u32` (function, `cvm2/gen_test.py:10`) `def emit_u32(v)`
- `check` (function, `cvm2/test.sh:13`)
- `reject` (function, `cvm2/test.sh:24`)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 0
- Cross-boundary resolved imports (EXTRACTED): 0

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- [taint high] `cvm2/gen_test.py` -> `cvm2/gen_test.py` via `subprocess` (0 hops)

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `cvm2/deepseek_bash_20260808_653f26.sh`)? What purpose do they serve?
- Is the dangerous import `subprocess` in `cvm2/gen_test.py` still required, or can it be isolated?
- What would break if the most connected file in orphans changed?
- Should orphans be split, given cohesion 0.00?

## Sources

- `cvm2/deepseek_bash_20260808_653f26.sh`
- `cvm2/gen_test.py`
- `cvm2/test.sh`
- `test.sh`
