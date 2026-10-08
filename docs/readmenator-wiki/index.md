# Second Brain

*Last synthesized: 2026-10-07 | 26 files | 4 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `cvm.h`, `cvm2/cvm.h`, `cvm_jit.h`. Architecturally it is 3 layers, dominant utility (21 files) across 4 import-based communities. Recorded risk surface: 0 security findings and 0 dependency cycles.

Surprising tissue lives between cvm2: cvm, cvm2: cvm_dbg_main, cvm2: cvm_jit: 3 extracted cross-community imports and 5 inferred bridges. Follow `connections.json` sorted by strength before refactoring.

Open work clusters around documentation (8% file coverage), 0 security findings, 1 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 26 |
| Symbols | 565 |
| Resolved imports | 31 |
| Languages | c, h, py, sh |
| Communities | 4 |
| Doc coverage | 8% (2/26 files) |
| Security findings | 0 |
| Estimated read cost | ~14288 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target readmenator_cvm_xob4stib
```

## Concept Wiki

- [cvm2: cvm (12 files, cohesion 0.73)](./community_0_cvm2_cvm.md)
- [cvm2: cvm_dbg_main (5 files, cohesion 0.46)](./community_1_cvm2_cvm_dbg_main.md)
- [cvm2: cvm_jit (5 files, cohesion 0.40)](./community_2_cvm2_cvm_jit.md)
- [orphans (4 files, cohesion 0.00)](./community_3_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `cvm.h` | 22.8 |
| `cvm2/cvm.h` | 21.6 |
| `cvm2/cvm_jit.h` | 18.6 |
| `cvm2/cvm.c` | 16.4 |
| `cvm2/cvm_view.h` | 14.9 |

## Strongest Connections

- 1 -> 0: depends_on (strength 0.9, EXTRACTED)
- 1 -> 2: depends_on (strength 0.9, EXTRACTED)
- 2 -> 0: depends_on (strength 0.9, EXTRACTED)
- 2 -> 0: bridges (strength 0.5, INFERRED)
- 1 -> 0: bridges (strength 0.5, INFERRED)
- 1 -> 0: bridges (strength 0.5, INFERRED)
- 0 -> 2: bridges (strength 0.5, INFERRED)
- 0 -> 1: bridges (strength 0.5, INFERRED)

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
