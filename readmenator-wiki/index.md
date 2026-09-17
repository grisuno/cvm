# Second Brain

*Last synthesized: 2026-09-17 | 26 files | 2 concept pages | offline, zero tokens*

> Raw sources -> readmenator wiki -> links (Karpathy LLM Wiki Pattern, deterministic).
> Start here, then open one community page. Prefer grep over full reads.

## Vault Overview

The codebase centres on `cvm.h`, `cvm2/cvm.h`, `cvm_jit.h`. Architecturally it is 4 layers, dominant utility (18 files) across 2 import-based communities. Recorded risk surface: 1 security findings and 0 dependency cycles.

Communities are self-contained in the resolved import graph; no cross-boundary bridges were recorded.

Open work clusters around documentation (8% file coverage), 1 security findings, 1 taint paths, and 5 suggested exploration questions in `queries.md`.

## Stats

| Metric | Value |
|--------|-------|
| Files | 26 |
| Symbols | 696 |
| Resolved imports | 31 |
| Languages | c, h, py, sh |
| Communities | 2 |
| Doc coverage | 8% (2/26 files) |
| Security findings | 1 |
| Estimated read cost | ~19653 tokens (chars/4, offline so $0) |

## Reading Order

1. Skim Stats and God Nodes below for blast radius.
2. Open the largest community page first, then follow Connections.
3. Use `queries.md` for the next question; log the answer there.

```
grep -rn '<keyword>' index.md community_*.md
readmenator query "<question>" --target cvm
```

## Concept Wiki

- [cvm2 (22 files, cohesion 1.00)](./community_0_cvm2.md)
- [orphans (4 files, cohesion 0.00)](./community_1_orphans.md)

## God Nodes

| File | Score |
|------|-------|
| `cvm.h` | 22.8 |
| `cvm2/cvm.h` | 21.8 |
| `cvm2/cvm_jit.h` | 18.6 |
| `cvm2/cvm.c` | 17.2 |
| `cvm2/cvm_view.h` | 14.9 |

## Strongest Connections

- No cross-community connections recorded.

## Navigation Tips

- Obsidian Graph View works: every community page links back here.
- `connections.json` is machine-readable for GraphRAG pipelines.
- `REPORT.md` states what was extracted vs inferred and current limits.
- Regenerate offline: `readmenator . --rebuild` (no network, no tokens).
