# Project Memory

> Cross-session context for agents. Sections 1-6 are regenerated from the source tree with zero LLM tokens: declared rules are quoted verbatim with `file:line`, measured baselines come from the scan. Section 7 is written by agents and humans and is preserved across rebuilds.

Generated from 26 files at commit `f135009afaf5`. Read this first, then `readmenator-wiki/index.md`, then `readmenator . ask "<question>"` for anything specific.

## 1. Purpose and domain

- What it is: A stack-based bytecode virtual machine for a C language subset, designed as an alternative execution backend for the [miniGCC](https://github.com/grisuno/miniGCC) and [LazyC](https://github.com/grisuno/LazyC) compilers. (`README.md:3`)
- Domain vocabulary (term, files): `cvm` (23), `cvm2` (22), `size` (12), `code` (12), `func` (11), `emit` (10), `module` (10), `native` (9), `stack` (9), `function` (9), `push` (9), `uint8` (9), `const` (9), `void` (8), `call` (8)
- Subsystem `cvm2: cvm`: 12 files, core `cvm2/cvm.c`: Vout: static int64_t native_atol(void *vm, int ac, uint64_t *av) { (void)vm; if (ac < 1) return...
- Subsystem `cvm2: cvm_dbg_main`: 5 files, core `cvm2/cvm_dbg_main.c`
- Subsystem `cvm2: cvm_jit`: 5 files, core `cvm2/cvm_jit.c`: emit_stack_pop_into: /* Push rax onto the operand stack: slots[sp] = rax; sp++ static void...
- Business rules that the code cannot show live in section 7: record them there.

## 2. Workflow

Detected commands:
- `python -m pytest -q` (tests/ layout)
- `make all` (Makefile)
- `make cvm` (Makefile)
- `make gen_fib_cvm` (Makefile)
- `make test` (Makefile)
- `make clean` (Makefile)
- `CI workflow github-actions-demo.yml` (workflows/github-actions-demo.yml)

Session protocol:
1. Start: read this file, then `readmenator . fresh` (exit 1 means run `readmenator . --rebuild`).
2. Orient: `readmenator-wiki/index.md`; for a question use `readmenator . ask "<question>"` (local = entities + sources, `--global` = community reports).
3. Before editing a file: `grep -n '<file>' readmenator-agent/GOTCHAS.md readmenator-agent/SECURITY.md`.
4. After the change: run the tests above, then `readmenator . --rebuild` so the maps, wiki, and this file stay true.
5. End: record decisions, business rules, and gotchas with `readmenator . remember "<note>" --kind decision`.

## 3. Rules and constraints

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- Security findings at medium or above: 0 (see `readmenator-agent/SECURITY.md`); do not add new ones.
- Dependency cycles: 0; layer violations: 0 (see `readmenator-agent/GOTCHAS.md`).

## 4. Style norms

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- c: 14 files, 345 symbols; docstrings on 10% of symbols; functions snake_case (100%); types PascalCase (100%); median file 259 lines, max 1514.
- h: 8 files, 216 symbols; docstrings on 44% of symbols; functions snake_case (100%); types PascalCase (73%); median file 159 lines, max 296.
- sh: 3 files, 2 symbols; docstrings on 0% of symbols; functions snake_case (100%); median file 14 lines, max 81.
- py: 1 files, 2 symbols; docstrings on 0% of symbols; functions snake_case (100%); median file 79 lines, max 79.
- Tests: 1 files under cvm2; follow the existing naming (e.g. `gen_test.py`).

## 5. Minimum deliverables

Declared:
- none declared in instruction files (add them to AGENTS.md or record them in section 7)

Measured baseline:
- Tests pass: `python -m pytest -q`.
- Docstring coverage stays at or above 23%.
- No new security findings at medium or above (current: 0).
- No new dependency cycles (current: 0).
- Files stay under 300 lines where possible (`readmenator . lint`).
- Docs refreshed: `readmenator . --rebuild`, and decisions recorded in section 7.

## 6. Risks to respect

- God nodes (changes ripple widely): `cvm.h`, `cvm2/cvm.h`, `cvm2/cvm_jit.h`, `cvm2/cvm.c`, `cvm2/cvm_view.h`
- Hotspots (complex and central): `cvm.h`, `cvm2/cvm.c`, `cvm2/cvm.h`, `cvm2/cvm_dbg_main.c`, `cvm2/cvm_jit_x86.c`
- Full blast radius: `readmenator-agent/GOTCHAS.md`; findings: `readmenator-agent/SECURITY.md`.

## 7. Session log (preserved across rebuilds)

Append with `readmenator . remember "<note>" --kind <kind>` (kinds: business, decision, rule, workflow, style, deliverable, gotcha, todo, note) or the MCP tool `readmenator.remember`. Record business rules, decisions and their reasons, workflow changes, and anything the next session must not rediscover.

<!-- readmenator:memory:notes:begin -->
<!-- readmenator:memory:notes:end -->
