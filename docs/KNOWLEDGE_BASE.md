# Polyglot Codebase Knowledge Graph

> Generated offline by **readmenator**. 26 files, 565 symbols, 91 imports. Supports C, C++, Python, Go, Rust, JS/TS, Java, C#, Shell, PHP, Dart, GDScript, Nim, ASM, Ruby, Swift, Kotlin, Scala, Lua, Elixir.
> No LLMs. No tokens. Pure static analysis. See more [here](https://github.com/grisuno/ReadMenator)

**Start here:** Statistics Dashboard for scope, God Nodes for blast radius, Architecture Reference for per-file API. Agents: prefer `readmenator-agent/INDEX.md` + `SYMBOLS.md`.

**Wiki:** prefer `readmenator-wiki/index.md` for progressive disclosure: one synthesis page per community, `connections.json` with EXTRACTED vs INFERRED confidence, `queries.md` log, `REPORT.md` audit.

**Confidence:** EXTRACTED = parsed from source, INFERRED = heuristic bridge, AMBIGUOUS = reported, never hidden. See `readmenator-wiki/REPORT.md`.

**Total Files Parsed:** 26 | **Total Symbols Extracted:** 565 | **Total Imports:** 91
 | **Resolved Imports:** 31

<!-- ranking_model: v1.0 | weights: {ppr:0.45,auth:0.2,test:0.15,doc:0.1,fresh:0.1} | alpha:0.85 | commit:1e0fd0b | date:2026-07-18 -->


## Table of Contents

1. [Statistics Dashboard](#statistics-dashboard)
2. [Architectural Layers](#architectural-layers)
3. [Ranked Context](#ranked-context)
4. [God Nodes](#god-nodes)
5. [Community Analysis](#community-analysis)
6. [Surprising Connections](#surprising-connections)
7. [Suggested Questions](#suggested-questions)
8. [Taint Propagation Map](#taint-propagation-map)
9. [Hotspot Analysis](#hotspot-analysis)
10. [Change Impact Analysis](#change-impact-analysis)
11. [Suggested Linting Rules](#suggested-linting-rules)
12. [Dataflow Analysis](#dataflow-analysis)
13. [Concept Graph](#concept-graph)
14. [Orphans](#orphans)
15. [Query Recipes](#query-recipes)
16. [Structural Knowledge Map](#structural-knowledge-map)
17. [UML Class Diagram](#uml-class-diagram)
18. [Code Property Graph](#code-property-graph)
19. [Architecture Reference](#architecture-reference)
    - [C (14 files)](#c-14-files)
    - [H (8 files)](#h-8-files)
    - [PY (1 files)](#py-1-files)
    - [SH (3 files)](#sh-3-files)

---

## Statistics Dashboard

| Metric | Value |
|--------|-------|
| Total Files | 26 |
| Total Symbols | 565 |
| Total Imports | 91 |
| Call Edges | 3 |
| Inheritance Edges | 0 |
| Languages | 4 |
| Avg Symbols/File | 21.7 |
| Avg Imports/File | 3.5 |
| Resolved Imports | 31 |

### Top Files by Import Count (Fan-Out)

| File | Imports | Symbols | Language |
|------|---------|---------|----------|
| `cvm.h` | 8 | 28 | h |
| `cvm_dbg_main.c` | 8 | 21 | c |
| `cvm.c` | 6 | 104 | c |
| `cvm.h` | 6 | 56 | h |
| `cvm_jit.c` | 5 | 37 | c |
| `cvm_jit_help.c` | 5 | 22 | c |
| `cvm_val_main.c` | 5 | 25 | c |
| `gen_fib_cvm.c` | 5 | 10 | c |
| `cvm_dis_main.c` | 4 | 2 | c |
| `cvm_jit_x86.c` | 4 | 73 | c |

### Top Files by Imported-By Count (Fan-In)

| File | Imported By | Symbols | Language |
|------|-------------|---------|----------|
| `cvm.h` | 10 | 28 | h |

---

## Architectural Layers

Auto-detected from path patterns, naming conventions, and imported frameworks.

| Layer | Files |
|-------|-------|
| utility | 21 |
| testing | 3 |
| presentation | 2 |

### utility

- `cvm.c` (c, 20 symbols)
- `cvm.h` (h, 28 symbols)
- `cvm.c` (c, 104 symbols)
- `cvm.h` (h, 56 symbols)
- `cvm_dbg_main.c` (c, 21 symbols)
- `cvm_dis.c` (c, 9 symbols)
- `cvm_dis.h` (h, 4 symbols)
- `cvm_dis_main.c` (c, 2 symbols)
- `cvm_jit.c` (c, 37 symbols)
- `cvm_jit.h` (h, 26 symbols)
- `cvm_jit_help.c` (c, 22 symbols)
- `cvm_jit_help.h` (h, 13 symbols)
- `cvm_jit_x86.c` (c, 73 symbols)
- `cvm_jit_x86.h` (h, 71 symbols)
- `cvm_ops.c` (c, 7 symbols)
- *... and 6 more*

### presentation

- `cvm_view.c` (c, 8 symbols)
- `cvm_view.h` (h, 9 symbols)

### testing

- `gen_test.py` (py, 2 symbols)
- `test.sh` (sh, 2 symbols)
- `test.sh` (sh, 0 symbols)

---

## Ranked Context

Files ranked by composite score for the current query context. The ranking combines Personalized PageRank (query relevance), global authority, test coverage, documentation coverage, and code freshness. Model: v1.0.

| Rank | File | Composite | PPR | Authority | Test | Doc |
|------|------|-----------|-----|-----------|------|-----|
| 1 | `cvm_view.h` | 0.1357 | 0.1061 | 0.1061 | 0.00 | 0.67 |
| 2 | `cvm.h` | 0.1225 | 0.1720 | 0.1720 | 0.00 | 0.11 |
| 3 | `cvm_jit_x86.h` | 0.1201 | 0.0547 | 0.0547 | 0.00 | 0.85 |
| 4 | `cvm_jit_help.h` | 0.1061 | 0.0449 | 0.0449 | 0.00 | 0.77 |
| 5 | `cvm_dis.h` | 0.1054 | 0.0467 | 0.0467 | 0.00 | 0.75 |
| 6 | `cvm.h` | 0.0880 | 0.1326 | 0.1326 | 0.00 | 0.02 |
| 7 | `cvm_ops.h` | 0.0855 | 0.0631 | 0.0631 | 0.00 | 0.44 |
| 8 | `cvm_jit.h` | 0.0710 | 0.0559 | 0.0559 | 0.00 | 0.35 |
| 9 | `cvm.c` | 0.0650 | 0.0231 | 0.0231 | 0.00 | 0.50 |
| 10 | `gen_test.py` | 0.0500 | 0.0000 | 0.0000 | 0.00 | 0.50 |

---

## God Nodes

Most architecturally central files ranked by combined import/export degree and symbol richness.

| File | Score | Connections | PageRank |
|------|-------|-------------|----------|
| `cvm.h` | 22.8 | | 0.1720 |
| `cvm.h` | 21.6 | | 0.1326 |
| `cvm_jit.h` | 18.6 | | 0.0559 |
| `cvm.c` | 16.4 | | 0.0000 |
| `cvm_view.h` | 14.9 | | 0.1061 |
| `cvm_dbg_main.c` | 12.1 | | 0.0000 |
| `cvm_jit_x86.h` | 11.1 | | 0.0547 |
| `cvm_ops.h` | 10.9 | | 0.0631 |
| `cvm_jit_help.h` | 9.3 | | 0.0449 |
| `cvm_jit_x86.c` | 9.3 | | 0.0000 |

---

## Community Analysis

Files grouped by import-based community detection. Cohesion measures how tightly connected each community is internally.

### cvm2: cvm (Cohesion: 0.73)

**12 files** in this community:

- `cvm.c` (c, 20 symbols)
- `cvm.h` (h, 28 symbols)
- `cvm.c` (c, 104 symbols)
- `cvm.h` (h, 56 symbols)
- `cvm_jit.h` (h, 26 symbols)
- `cvm_jit_help.c` (c, 22 symbols)
- `cvm_jit_help.h` (h, 13 symbols)
- `cvm_jit_x86.c` (c, 73 symbols)
- `cvm_jit_x86.h` (h, 71 symbols)
- `gen_fib_cvm.c` (c, 10 symbols)
- `gen_minimal.c` (c, 4 symbols)
- `gen_fib_cvm.c` (c, 3 symbols)

### cvm2: cvm_dbg_main (Cohesion: 0.46)

**5 files** in this community:

- `cvm_dbg_main.c` (c, 21 symbols)
- `cvm_dis.h` (h, 4 symbols)
- `cvm_dis_main.c` (c, 2 symbols)
- `cvm_view.c` (c, 8 symbols)
- `cvm_view.h` (h, 9 symbols)

### cvm2: cvm_jit (Cohesion: 0.40)

**5 files** in this community:

- `cvm_dis.c` (c, 9 symbols)
- `cvm_jit.c` (c, 37 symbols)
- `cvm_ops.c` (c, 7 symbols)
- `cvm_ops.h` (h, 9 symbols)
- `cvm_val_main.c` (c, 25 symbols)

---

## Surprising Connections

Files in different communities connected through 3+ indirect hops.

- `cvm_dis.c` <-> `cvm_jit_x86.c` (5 hops, across 2 communities)
- `cvm_dis.h` <-> `cvm_jit_x86.c` (5 hops, across 2 communities)
- `cvm_dis_main.c` <-> `cvm_jit_x86.c` (5 hops, across 2 communities)
- `cvm_jit_x86.c` <-> `cvm_val_main.c` (5 hops, across 3 communities)
- `cvm_jit_x86.c` <-> `cvm_view.c` (5 hops, across 2 communities)

---

## Suggested Questions

Auto-generated exploration prompts based on graph structure:

- What does cvm.h depend on, and what depends on it? (10 connections)
- What does cvm.h depend on, and what depends on it? (8 connections)
- What does cvm_jit.h depend on, and what depends on it? (8 connections)
- How are the 12 files in 'cvm2: cvm' related to each other?
- Why are cvm_dis.c and cvm_jit_x86.c connected through 5 hops across 2 communities?

---

## Taint Propagation Map

Taint analysis traces how dangerous imports propagate through the codebase via transitive dependencies. Source files import dangerous modules directly; sink files receive the danger indirectly.

**Taint Sources:** 1 | **Taint Sinks:** 1 | **Propagation Paths:** 1

- `gen_test.py` imports `subprocess` (0 hop to `gen_test.py`) [high]
  Path: gen_test.py

---

## Hotspot Analysis

Files ranked by combined complexity (symbol count) and centrality (connection count). High-scoring files are architecturally critical and may need refactoring attention.

| File | Complexity | Centrality | Combined | Symbols | Connections |
|------|-----------|------------|----------|---------|-------------|
| `cvm_view.h` | 0.086 | 0.450 | 0.305 | 9 | 9 |
| `cvm.h` | 0.269 | 1.000 | 0.708 | 28 | 20 |
| `cvm_jit_x86.h` | 0.683 | 0.200 | 0.393 | 71 | 4 |
| `cvm_jit_help.h` | 0.125 | 0.200 | 0.170 | 13 | 4 |
| `cvm_dis.h` | 0.038 | 0.350 | 0.225 | 4 | 7 |
| `cvm.h` | 0.538 | 0.700 | 0.635 | 56 | 14 |
| `cvm_ops.h` | 0.086 | 0.350 | 0.245 | 9 | 7 |
| `cvm_jit.h` | 0.250 | 0.500 | 0.400 | 26 | 10 |
| `cvm.c` | 0.192 | 0.200 | 0.197 | 20 | 4 |
| `gen_test.py` | 0.019 | 0.150 | 0.098 | 2 | 3 |
| `cvm.c` | 1.000 | 0.400 | 0.640 | 104 | 8 |
| `cvm_dbg_main.c` | 0.202 | 0.600 | 0.441 | 21 | 12 |
| `cvm_jit_x86.c` | 0.702 | 0.250 | 0.431 | 73 | 5 |
| `cvm_jit.c` | 0.356 | 0.350 | 0.352 | 37 | 7 |
| `cvm_val_main.c` | 0.240 | 0.350 | 0.306 | 25 | 7 |

---

## Dataflow Analysis

Procedural intra-function dataflow findings (zero tokens, regex-based heuristics, all INFERRED). Each lead is grounded at file:line for manual review.

**6 findings** (DEAD_STORE: 1, UNCHECKED_ALLOC: 5).

| File | Function | Line | Kind | Variable | Description |
|------|----------|------|------|----------|-------------|
| `cvm.c` | `cvm_emit_byte` | 746 | `UNCHECKED_ALLOC` | `buf` | Result of allocator stored in `buf` is never checked against NULL. |
| `cvm2/cvm_jit.c` | `cvm_jit_compile_func` | 1299 | `DEAD_STORE` | `instr_start_native` | `instr_start_native` assigned at line 1299 but never read afterwards. |
| `cvm2/gen_minimal.c` | `emit_byte` | 17 | `UNCHECKED_ALLOC` | `code_buf` | Result of allocator stored in `code_buf` is never checked against NULL. |
| `cvm2/gen_minimal.c` | `main` | 51 | `UNCHECKED_ALLOC` | `module` | Result of allocator stored in `module` is never checked against NULL. |
| `cvm2/gen_minimal.c` | `main` | 83 | `UNCHECKED_ALLOC` | `f` | Result of allocator stored in `f` is never checked against NULL. |
| `gen_fib_cvm.c` | `add_string` | 28 | `UNCHECKED_ALLOC` | `strpool` | Result of allocator stored in `strpool` is never checked against NULL. |

---

## Concept Graph

Semantic second-brain layer: nouns are concept nodes, verbs are edges. Each noun maps atomically to a file set (EXTRACTED); each verb aggregates structural imports, calls, and inherits into consumes, invokes, extends, depends_on, or bridges (INFERRED).

**50 concepts, 100 relations.**

| Concept | Files | Mentions |
|---------|-------|----------|
| `cvm` | 23 | 377 |
| `cvm2` | 22 | 22 |
| `size` | 12 | 100 |
| `code` | 12 | 48 |
| `func` | 11 | 47 |
| `emit` | 10 | 370 |
| `module` | 10 | 45 |
| `int` | 9 | 278 |
| `native` | 9 | 86 |
| `stack` | 9 | 51 |
| `function` | 9 | 47 |
| `push` | 9 | 32 |
| `uint8` | 9 | 31 |
| `const` | 9 | 29 |
| `void` | 8 | 201 |
| `call` | 8 | 55 |
| `pop` | 8 | 32 |
| `max` | 8 | 21 |
| `frame` | 8 | 17 |
| `mem` | 7 | 30 |
| `byte` | 7 | 25 |
| `uint32` | 7 | 23 |
| `ret` | 7 | 22 |
| `entry` | 7 | 20 |
| `run` | 7 | 16 |
| `name` | 7 | 13 |
| `alloc` | 7 | 11 |
| `ifdef` | 7 | 9 |
| `jit` | 6 | 367 |
| `data` | 6 | 34 |

### Verb Edges

| Source | Verb | Target | Strength | Evidence |
|--------|------|--------|----------|----------|
| `cvm` | `depends_on` | `size` | 1.00 | 10 |
| `cvm2` | `depends_on` | `code` | 0.97 | 10 |
| `cvm2` | `depends_on` | `cvm` | 0.97 | 10 |
| `cvm2` | `depends_on` | `size` | 0.97 | 10 |
| `cvm` | `depends_on` | `code` | 0.93 | 10 |
| `cvm` | `depends_on` | `cvm2` | 0.93 | 10 |
| `cvm2` | `depends_on` | `cplusplus` | 0.90 | 10 |
| `cvm2` | `depends_on` | `ifdef` | 0.90 | 10 |
| `cvm` | `depends_on` | `cplusplus` | 0.87 | 10 |
| `cvm` | `depends_on` | `ifdef` | 0.87 | 10 |
| `cvm` | `depends_on` | `entry` | 0.73 | 10 |
| `cvm` | `depends_on` | `func` | 0.73 | 10 |
| `cvm` | `depends_on` | `const` | 0.70 | 10 |
| `cvm` | `depends_on` | `module` | 0.70 | 10 |
| `cvm2` | `depends_on` | `all` | 0.70 | 10 |
| `cvm2` | `depends_on` | `entry` | 0.70 | 10 |
| `cvm2` | `depends_on` | `func` | 0.70 | 10 |
| `cvm` | `depends_on` | `all` | 0.67 | 10 |
| `cvm` | `depends_on` | `native` | 0.67 | 10 |
| `cvm2` | `depends_on` | `module` | 0.67 | 10 |
| `cvm2` | `depends_on` | `const` | 0.63 | 10 |
| `cvm2` | `depends_on` | `native` | 0.63 | 10 |
| `cvm` | `depends_on` | `data` | 0.53 | 10 |
| `cvm` | `depends_on` | `function` | 0.53 | 10 |
| `cvm` | `depends_on` | `int` | 0.53 | 10 |
| `cvm` | `depends_on` | `uint8` | 0.53 | 10 |
| `cvm2` | `depends_on` | `function` | 0.53 | 10 |
| `func` | `depends_on` | `code` | 0.53 | 10 |
| `func` | `depends_on` | `cvm` | 0.53 | 10 |
| `func` | `depends_on` | `cvm2` | 0.53 | 10 |

### Dialectic Prompts

- Thesis: `all` centralizes 6 files; Antithesis: `alloc` pulls 7 files with 3 shared (Jaccard 0.30); Synthesis: should they merge, split by layer, or keep `bridges` explicit?
- Thesis: `all` centralizes 6 files; Antithesis: `code` pulls 12 files with 6 shared (Jaccard 0.50); Synthesis: should they merge, split by layer, or keep `depends_on` explicit?
- Thesis: `all` centralizes 6 files; Antithesis: `const` pulls 9 files with 4 shared (Jaccard 0.36); Synthesis: should they merge, split by layer, or keep `bridges` explicit?
- Thesis: `all` centralizes 6 files; Antithesis: `count` pulls 6 files with 4 shared (Jaccard 0.50); Synthesis: should they merge, split by layer, or keep `bridges` explicit?
- Thesis: `all` centralizes 6 files; Antithesis: `cplusplus` pulls 6 files with 4 shared (Jaccard 0.50); Synthesis: should they merge, split by layer, or keep `bridges` explicit?
- Thesis: `all` centralizes 6 files; Antithesis: `create` pulls 6 files with 3 shared (Jaccard 0.33); Synthesis: should they merge, split by layer, or keep `bridges` explicit?
- Thesis: `all` centralizes 6 files; Antithesis: `data` pulls 6 files with 4 shared (Jaccard 0.50); Synthesis: should they merge, split by layer, or keep `bridges` explicit?
- Thesis: `all` centralizes 6 files; Antithesis: `destroy` pulls 6 files with 3 shared (Jaccard 0.33); Synthesis: should they merge, split by layer, or keep `bridges` explicit?
- Thesis: `all` centralizes 6 files; Antithesis: `entry` pulls 7 files with 5 shared (Jaccard 0.62); Synthesis: should they merge, split by layer, or keep `bridges` explicit?
- Thesis: `all` centralizes 6 files; Antithesis: `error` pulls 6 files with 3 shared (Jaccard 0.33); Synthesis: should they merge, split by layer, or keep `bridges` explicit?

---

## Change Impact Analysis

Files sorted by how many other files would be affected if they changed. High-impact files should be changed with caution.

| File | Direct Dependents | Transitive Dependents | Total Impact |
|------|------------------|----------------------|--------------|
| `cvm.h` | 8 | 7 | 15 |
| `cvm_jit_x86.h` | 2 | 4 | 6 |
| `cvm_view.h` | 5 | 1 | 6 |
| `cvm_jit_help.h` | 2 | 3 | 5 |
| `cvm_ops.h` | 5 | 0 | 5 |
| `cvm_jit.h` | 4 | 0 | 4 |
| `cvm_dis.h` | 3 | 0 | 3 |
| `cvm.h` | 2 | 0 | 2 |
| `cvm.c` | 0 | 0 | 0 |
| `cvm.c` | 0 | 0 | 0 |
| `cvm_dbg_main.c` | 0 | 0 | 0 |
| `cvm_dis.c` | 0 | 0 | 0 |
| `cvm_dis_main.c` | 0 | 0 | 0 |
| `cvm_jit.c` | 0 | 0 | 0 |
| `cvm_jit_help.c` | 0 | 0 | 0 |

---

## Suggested Linting Rules

Automatically suggested linting and security rules based on patterns detected in the codebase. These can be exported as Semgrep rules using the `--export-rules` flag.

| Rule ID | Severity | Description | Language | Matches |
|---------|----------|-------------|----------|---------|
| `RM001` | info | Large number of functions in c: 301 total | c | 301 |
| `RM002` | info | Large number of functions in h: 130 total | h | 130 |
| `RM003` | info | Print statement found (consider logging instead) | python | 4 |

---

## Orphans

Files with no documentation or low connectivity. These are candidates for documentation investment or cleanup.

- `cvm_dbg_main.c` (21 symbols, no doc)
- `cvm_dis.c` (9 symbols, no doc)
- `cvm_dis_main.c` (2 symbols, no doc)
- `cvm_jit_help.c` (22 symbols, no doc)
- `cvm_ops.c` (7 symbols, no doc)
- `cvm_view.c` (8 symbols, no doc)
- `deepseek_bash_20260808_653f26.sh` (0 symbols, no doc)
- `gen_fib_cvm.c` (10 symbols, no doc)
- `gen_minimal.c` (4 symbols, no doc)
- `gen_fib_cvm.c` (3 symbols, no doc)
- `test.sh` (0 symbols, no doc)

---

## Query Recipes

Example queries you can run against this knowledge base using the ranking engine:

```
# Find files most relevant to a concept
readmenator query "Where is the import resolver implemented?"

# Rank files by relevance to a topic
readmenator query "How does documentation generation work?"

# Explain why a file ranks highly
readmenator query "explain readmenator/_documentation.py"

# Trace dependency paths with ranked context
readmenator query "path from CLI to exporter"
```

The ranking model uses the following signals:

- **Personalized PageRank** (45% weight): query-specific relevance via seed propagation
- **Global Authority** (20% weight): structural importance via standard PageRank
- **Test Coverage** (15% weight): fraction of symbols referenced in test files
- **Doc Coverage** (10% weight): presence of docstrings and file-level docs
- **Freshness** (10% weight): recent modification activity

Results include score decomposition and justification paths for each ranked item.

---

## Structural Knowledge Map

```mermaid
graph TD
    classDef mod fill:#1e1e1e,stroke:#ff6666,stroke-width:2px,color:#fff;
    classDef cls fill:#2d2d2d,stroke:#4ec9b0,stroke-width:2px,color:#fff;
    classDef fn fill:#333,stroke:#dcdcaa,stroke-width:1px,color:#dcdcaa;
    classDef ext fill:#111,stroke:#666,stroke-dasharray:5 5,color:#aaa;
    subgraph community_1 ["cvm2: cvm_dbg_main"]
    cvm2_cvm_dbg_main_c["cvm_dbg_main.c (c)"]
    class cvm2_cvm_dbg_main_c mod;
    cvm2_cvm_dbg_main_c_emit_stdout["emit_stdout"]
    class cvm2_cvm_dbg_main_c_emit_stdout fn;
    cvm2_cvm_dbg_main_c --> cvm2_cvm_dbg_main_c_emit_stdout
    cvm2_cvm_dbg_main_c_func_display["func_display"]
    class cvm2_cvm_dbg_main_c_func_display fn;
    cvm2_cvm_dbg_main_c --> cvm2_cvm_dbg_main_c_func_display
    cvm2_cvm_dbg_main_c_func_of_ip["func_of_ip"]
    class cvm2_cvm_dbg_main_c_func_of_ip fn;
    cvm2_cvm_dbg_main_c --> cvm2_cvm_dbg_main_c_func_of_ip
    cvm2_cvm_dbg_main_c_parse_u32["parse_u32"]
    class cvm2_cvm_dbg_main_c_parse_u32 fn;
    cvm2_cvm_dbg_main_c --> cvm2_cvm_dbg_main_c_parse_u32
    cvm2_cvm_dbg_main_c_report_run["report_run"]
    class cvm2_cvm_dbg_main_c_report_run fn;
    cvm2_cvm_dbg_main_c --> cvm2_cvm_dbg_main_c_report_run
    end
    subgraph community_0 ["cvm2: cvm"]
    cvm2_cvm_c["cvm.c (c)"]
    class cvm2_cvm_c mod;
    cvm_h["cvm.h (h)"]
    class cvm_h mod;
    end
    subgraph community_2 ["cvm2: cvm_jit"]
    cvm2_cvm_jit_c["cvm_jit.c (c)"]
    class cvm2_cvm_jit_c mod;
    cvm2_cvm_val_main_c["cvm_val_main.c (c)"]
    class cvm2_cvm_val_main_c mod;
    cvm2_cvm_jit_help_c["cvm_jit_help.c (c)"]
    class cvm2_cvm_jit_help_c mod;
    cvm2_gen_fib_cvm_c["gen_fib_cvm.c (c)"]
    class cvm2_gen_fib_cvm_c mod;
    cvm2_cvm_h["cvm.h (h)"]
    class cvm2_cvm_h mod;
    cvm2_cvm_jit_h["cvm_jit.h (h)"]
    class cvm2_cvm_jit_h mod;
    cvm2_cvm_dis_main_c["cvm_dis_main.c (c)"]
    class cvm2_cvm_dis_main_c mod;
    cvm2_cvm_jit_x86_c["cvm_jit_x86.c (c)"]
    class cvm2_cvm_jit_x86_c mod;
    cvm2_cvm_dis_c["cvm_dis.c (c)"]
    class cvm2_cvm_dis_c mod;
    cvm2_gen_minimal_c["gen_minimal.c (c)"]
    class cvm2_gen_minimal_c mod;
    gen_fib_cvm_c["gen_fib_cvm.c (c)"]
    class gen_fib_cvm_c mod;
    cvm_c["cvm.c (c)"]
    class cvm_c mod;
    cvm2_cvm_view_h["cvm_view.h (h)"]
    class cvm2_cvm_view_h mod;
    cvm2_cvm_ops_c["cvm_ops.c (c)"]
    class cvm2_cvm_ops_c mod;
    cvm2_cvm_dis_h["cvm_dis.h (h)"]
    class cvm2_cvm_dis_h mod;
    cvm2_cvm_view_c["cvm_view.c (c)"]
    class cvm2_cvm_view_c mod;
    cvm2_gen_test_py["gen_test.py (py)"]
    class cvm2_gen_test_py mod;
    cvm2_cvm_jit_x86_h["cvm_jit_x86.h (h)"]
    class cvm2_cvm_jit_x86_h mod;
    cvm2_cvm_jit_help_h["cvm_jit_help.h (h)"]
    class cvm2_cvm_jit_help_h mod;
    cvm2_cvm_ops_h["cvm_ops.h (h)"]
    class cvm2_cvm_ops_h mod;
    cvm2_test_sh["test.sh (sh)"]
    class cvm2_test_sh mod;
    cvm2_deepseek_bash_20260808_653f26_sh["deepseek_bash_20260808_653f26.sh (sh)"]
    class cvm2_deepseek_bash_20260808_653f26_sh mod;
    test_sh["test.sh (sh)"]
    class test_sh mod;
    end
    cvm_c -- resolved_imports --> cvm_h
    cvm2_cvm_c -- resolved_imports --> cvm2_cvm_h
    cvm2_cvm_c -- resolved_imports --> cvm2_cvm_jit_h
    cvm2_cvm_dbg_main_c -- resolved_imports --> cvm2_cvm_h
    cvm2_cvm_dbg_main_c -- resolved_imports --> cvm2_cvm_view_h
    cvm2_cvm_dbg_main_c -- resolved_imports --> cvm2_cvm_dis_h
    cvm2_cvm_dbg_main_c -- resolved_imports --> cvm2_cvm_ops_h
    cvm2_cvm_dis_c -- resolved_imports --> cvm2_cvm_dis_h
    cvm2_cvm_dis_c -- resolved_imports --> cvm2_cvm_ops_h
    cvm2_cvm_dis_h -- resolved_imports --> cvm2_cvm_view_h
    cvm2_cvm_dis_main_c -- resolved_imports --> cvm2_cvm_view_h
    cvm2_cvm_dis_main_c -- resolved_imports --> cvm2_cvm_dis_h
    cvm2_cvm_jit_c -- resolved_imports --> cvm2_cvm_jit_h
    cvm2_cvm_jit_c -- resolved_imports --> cvm2_cvm_ops_h
    cvm2_cvm_jit_h -- resolved_imports --> cvm2_cvm_h
    cvm2_cvm_jit_h -- resolved_imports --> cvm2_cvm_jit_x86_h
    cvm2_cvm_jit_h -- resolved_imports --> cvm2_cvm_jit_help_h
    cvm2_cvm_jit_help_c -- resolved_imports --> cvm2_cvm_jit_help_h
    cvm2_cvm_jit_help_c -- resolved_imports --> cvm2_cvm_jit_h
    cvm2_cvm_jit_help_h -- resolved_imports --> cvm2_cvm_h
    cvm2_cvm_jit_x86_c -- resolved_imports --> cvm2_cvm_jit_x86_h
    cvm2_cvm_ops_c -- resolved_imports --> cvm2_cvm_ops_h
    cvm2_cvm_ops_c -- resolved_imports --> cvm2_cvm_h
    cvm2_cvm_val_main_c -- resolved_imports --> cvm2_cvm_view_h
    cvm2_cvm_val_main_c -- resolved_imports --> cvm2_cvm_ops_h
    cvm2_cvm_view_c -- resolved_imports --> cvm2_cvm_view_h
    cvm2_cvm_view_h -- resolved_imports --> cvm2_cvm_h
    cvm2_gen_fib_cvm_c -- resolved_imports --> cvm2_cvm_h
    cvm2_gen_fib_cvm_c -- resolved_imports --> cvm2_cvm_jit_h
    cvm2_gen_minimal_c -- resolved_imports --> cvm2_cvm_h
    gen_fib_cvm_c -- resolved_imports --> cvm_h
    ext_cvm_h["cvm.h"]
    class ext_cvm_h ext;
    cvm_c -.->|imports| ext_cvm_h
    ext_stdarg_h["stdarg.h"]
    class ext_stdarg_h ext;
    cvm_c -.->|imports| ext_stdarg_h
    ext_errno_h["errno.h"]
    class ext_errno_h ext;
    cvm_c -.->|imports| ext_errno_h
    ext_stdint_h["stdint.h"]
    class ext_stdint_h ext;
    cvm_h -.->|imports| ext_stdint_h
    ext_stddef_h["stddef.h"]
    class ext_stddef_h ext;
    cvm_h -.->|imports| ext_stddef_h
    ext_stdio_h["stdio.h"]
    class ext_stdio_h ext;
    cvm_h -.->|imports| ext_stdio_h
    ext_stdlib_h["stdlib.h"]
    class ext_stdlib_h ext;
    cvm_h -.->|imports| ext_stdlib_h
    ext_string_h["string.h"]
    class ext_string_h ext;
    cvm_h -.->|imports| ext_string_h
    ext_dlfcn_h["dlfcn.h"]
    class ext_dlfcn_h ext;
    cvm_h -.->|imports| ext_dlfcn_h
    ext_unistd_h["unistd.h"]
    class ext_unistd_h ext;
    cvm_h -.->|imports| ext_unistd_h
    ext_sys_mman_h["mman.h"]
    class ext_sys_mman_h ext;
    cvm_h -.->|imports| ext_sys_mman_h
    cvm2_cvm_c -.->|imports| ext_cvm_h
    ext_cvm_jit_h["cvm_jit.h"]
    class ext_cvm_jit_h ext;
    cvm2_cvm_c -.->|imports| ext_cvm_jit_h
    cvm2_cvm_c -.->|imports| ext_stdio_h
    cvm2_cvm_c -.->|imports| ext_stdlib_h
    cvm2_cvm_c -.->|imports| ext_string_h
    cvm2_cvm_c -.->|imports| ext_unistd_h
    cvm2_cvm_h -.->|imports| ext_stdint_h
    cvm2_cvm_h -.->|imports| ext_stddef_h
    cvm2_cvm_h -.->|imports| ext_stdio_h
    cvm2_cvm_h -.->|imports| ext_stdlib_h
    cvm2_cvm_h -.->|imports| ext_string_h
    cvm2_cvm_h -.->|imports| ext_unistd_h
    cvm2_cvm_dbg_main_c -.->|imports| ext_cvm_h
    ext_cvm_view_h["cvm_view.h"]
    class ext_cvm_view_h ext;
    cvm2_cvm_dbg_main_c -.->|imports| ext_cvm_view_h
    ext_cvm_dis_h["cvm_dis.h"]
    class ext_cvm_dis_h ext;
    cvm2_cvm_dbg_main_c -.->|imports| ext_cvm_dis_h
    ext_cvm_ops_h["cvm_ops.h"]
    class ext_cvm_ops_h ext;
    cvm2_cvm_dbg_main_c -.->|imports| ext_cvm_ops_h
    cvm2_cvm_dbg_main_c -.->|imports| ext_stdio_h
    cvm2_cvm_dbg_main_c -.->|imports| ext_stdlib_h
    cvm2_cvm_dbg_main_c -.->|imports| ext_string_h
    cvm2_cvm_dbg_main_c -.->|imports| ext_unistd_h
    cvm2_cvm_dis_c -.->|imports| ext_cvm_dis_h
    cvm2_cvm_dis_c -.->|imports| ext_cvm_ops_h
    cvm2_cvm_dis_c -.->|imports| ext_string_h
    cvm2_cvm_dis_h -.->|imports| ext_stddef_h
    cvm2_cvm_dis_h -.->|imports| ext_stdint_h
    cvm2_cvm_dis_h -.->|imports| ext_cvm_view_h
    cvm2_cvm_dis_main_c -.->|imports| ext_cvm_view_h
    cvm2_cvm_dis_main_c -.->|imports| ext_cvm_dis_h
    cvm2_cvm_dis_main_c -.->|imports| ext_stdio_h
    cvm2_cvm_dis_main_c -.->|imports| ext_stdlib_h
    cvm2_cvm_jit_c -.->|imports| ext_cvm_jit_h
    cvm2_cvm_jit_c -.->|imports| ext_cvm_ops_h
    cvm2_cvm_jit_c -.->|imports| ext_stdio_h
    cvm2_cvm_jit_c -.->|imports| ext_stdlib_h
    cvm2_cvm_jit_c -.->|imports| ext_string_h
    cvm2_cvm_jit_h -.->|imports| ext_cvm_h
    ext_cvm_jit_x86_h["cvm_jit_x86.h"]
    class ext_cvm_jit_x86_h ext;
    cvm2_cvm_jit_h -.->|imports| ext_cvm_jit_x86_h
    ext_cvm_jit_help_h["cvm_jit_help.h"]
    class ext_cvm_jit_help_h ext;
    cvm2_cvm_jit_h -.->|imports| ext_cvm_jit_help_h
    cvm2_cvm_jit_help_c -.->|imports| ext_cvm_jit_help_h
    cvm2_cvm_jit_help_c -.->|imports| ext_cvm_jit_h
    cvm2_cvm_jit_help_c -.->|imports| ext_stdlib_h
    cvm2_cvm_jit_help_c -.->|imports| ext_string_h
    cvm2_cvm_jit_help_c -.->|imports| ext_unistd_h
    cvm2_cvm_jit_help_h -.->|imports| ext_cvm_h
    cvm2_cvm_jit_x86_c -.->|imports| ext_cvm_jit_x86_h
    cvm2_cvm_jit_x86_c -.->|imports| ext_stdlib_h
    cvm2_cvm_jit_x86_c -.->|imports| ext_string_h
    cvm2_cvm_jit_x86_c -.->|imports| ext_sys_mman_h
    cvm2_cvm_jit_x86_h -.->|imports| ext_stdint_h
    cvm2_cvm_jit_x86_h -.->|imports| ext_stddef_h
    cvm2_cvm_ops_c -.->|imports| ext_cvm_ops_h
    cvm2_cvm_ops_c -.->|imports| ext_cvm_h
    cvm2_cvm_ops_h -.->|imports| ext_stdint_h
    cvm2_cvm_ops_h -.->|imports| ext_stddef_h
    cvm2_cvm_val_main_c -.->|imports| ext_cvm_view_h
    cvm2_cvm_val_main_c -.->|imports| ext_cvm_ops_h
    cvm2_cvm_val_main_c -.->|imports| ext_stdio_h
    cvm2_cvm_val_main_c -.->|imports| ext_stdlib_h
    cvm2_cvm_val_main_c -.->|imports| ext_string_h
    cvm2_cvm_view_c -.->|imports| ext_cvm_view_h
    cvm2_cvm_view_c -.->|imports| ext_string_h
    cvm2_cvm_view_h -.->|imports| ext_stdint_h
    cvm2_cvm_view_h -.->|imports| ext_stddef_h
    cvm2_cvm_view_h -.->|imports| ext_cvm_h
    cvm2_gen_fib_cvm_c -.->|imports| ext_cvm_h
    cvm2_gen_fib_cvm_c -.->|imports| ext_cvm_jit_h
    cvm2_gen_fib_cvm_c -.->|imports| ext_stdio_h
    cvm2_gen_fib_cvm_c -.->|imports| ext_stdlib_h
    cvm2_gen_fib_cvm_c -.->|imports| ext_string_h
    cvm2_gen_minimal_c -.->|imports| ext_cvm_h
    cvm2_gen_minimal_c -.->|imports| ext_stdio_h
    cvm2_gen_minimal_c -.->|imports| ext_stdlib_h
    cvm2_gen_minimal_c -.->|imports| ext_string_h
    ext_struct["struct"]
    class ext_struct ext;
    cvm2_gen_test_py -.->|imports| ext_struct
    ext_sys["sys"]
    class ext_sys ext;
    cvm2_gen_test_py -.->|imports| ext_sys
    ext_subprocess["subprocess"]
    class ext_subprocess ext;
    cvm2_gen_test_py -.->|imports| ext_subprocess
    gen_fib_cvm_c -.->|imports| ext_cvm_h
    gen_fib_cvm_c -.->|imports| ext_stdio_h
    gen_fib_cvm_c -.->|imports| ext_stdlib_h
    gen_fib_cvm_c -.->|imports| ext_string_h
```

---

## UML Class Diagram

Auto-generated Mermaid class diagram from parsed class-level symbols. Shows classes, structs, interfaces, traits, and their methods with inheritance and dependency relationships.

```mermaid
classDiagram
  class cvm_h_CVM_Module {
    <<struct>>
    +cvm_create(void);
    +cvm_destroy(CVM *vm);
    +cvm_load_module(CVM *vm, const char *path);
    +cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);
    +cvm_run(CVM *vm, const char *entry_name);
    +cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);
    +cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);
    +cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v);
    +cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v);
    +cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v);
  }
  class cvm_h_CVM_Header {
    <<struct>>
    +cvm_create(void);
    +cvm_destroy(CVM *vm);
    +cvm_load_module(CVM *vm, const char *path);
    +cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);
    +cvm_run(CVM *vm, const char *entry_name);
    +cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);
    +cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);
    +cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v);
    +cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v);
    +cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v);
  }
  class cvm_h_CVM_FuncEntry {
    <<struct>>
    +cvm_create(void);
    +cvm_destroy(CVM *vm);
    +cvm_load_module(CVM *vm, const char *path);
    +cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);
    +cvm_run(CVM *vm, const char *entry_name);
    +cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);
    +cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);
    +cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v);
    +cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v);
    +cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v);
  }
  class cvm_h_CVM_GlobalEntry {
    <<struct>>
    +cvm_create(void);
    +cvm_destroy(CVM *vm);
    +cvm_load_module(CVM *vm, const char *path);
    +cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);
    +cvm_run(CVM *vm, const char *entry_name);
    +cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);
    +cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);
    +cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v);
    +cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v);
    +cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v);
  }
  class cvm_h_CVM_StringEntry {
    <<struct>>
    +cvm_create(void);
    +cvm_destroy(CVM *vm);
    +cvm_load_module(CVM *vm, const char *path);
    +cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);
    +cvm_run(CVM *vm, const char *entry_name);
    +cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);
    +cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);
    +cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v);
    +cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v);
    +cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v);
  }
  class cvm_h_CVM_NativeEntry {
    <<struct>>
    +cvm_create(void);
    +cvm_destroy(CVM *vm);
    +cvm_load_module(CVM *vm, const char *path);
    +cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);
    +cvm_run(CVM *vm, const char *entry_name);
    +cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);
    +cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);
    +cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v);
    +cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v);
    +cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v);
  }
  class cvm_h_CVM_Frame {
    <<struct>>
    +cvm_create(void);
    +cvm_destroy(CVM *vm);
    +cvm_load_module(CVM *vm, const char *path);
    +cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);
    +cvm_run(CVM *vm, const char *entry_name);
    +cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);
    +cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);
    +cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v);
    +cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v);
    +cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v);
  }
  class cvm_h_CVM {
    <<struct>>
    +cvm_create(void);
    +cvm_destroy(CVM *vm);
    +cvm_load_module(CVM *vm, const char *path);
    +cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);
    +cvm_run(CVM *vm, const char *entry_name);
    +cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);
    +cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);
    +cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v);
    +cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v);
    +cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v);
  }
  class cvm_c_Vout {
    <<struct>>
    +xmal(size_t s)
    +xcal(size_t n, size_t s)
    +cvm_config_default(void)
    +cvm_create(const CvmConfig *config)
    +cvm_destroy(CvmState *vm)
    +cvm_strerror(int e)
    +vp(CvmState *vm, uint64_t v)
    +vo(CvmState *vm, uint64_t *v)
    +r8(CvmState *vm, uint8_t *o)
    +r32(CvmState *vm, uint32_t *o)
  }
  class cvm_h_CvmFuncEntry {
    <<struct>>
    +cvm_create(const CvmConfig *config);
    +cvm_destroy(CvmState *vm);
    +cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);
    +cvm_load_module_file(CvmState *vm, const char *path);
    +cvm_run(CvmState *vm);
    +cvm_continue(CvmState *vm);
    +cvm_step(CvmState *vm);
    +cvm_exit_code(const CvmState *vm);
    +cvm_instruction_count(const CvmState *vm);
    +cvm_strerror(int error_code);
  }
  class cvm_h_CvmGlobalEntry {
    <<struct>>
    +cvm_create(const CvmConfig *config);
    +cvm_destroy(CvmState *vm);
    +cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);
    +cvm_load_module_file(CvmState *vm, const char *path);
    +cvm_run(CvmState *vm);
    +cvm_continue(CvmState *vm);
    +cvm_step(CvmState *vm);
    +cvm_exit_code(const CvmState *vm);
    +cvm_instruction_count(const CvmState *vm);
    +cvm_strerror(int error_code);
  }
  class cvm_h_CvmNativeEntry {
    <<struct>>
    +cvm_create(const CvmConfig *config);
    +cvm_destroy(CvmState *vm);
    +cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);
    +cvm_load_module_file(CvmState *vm, const char *path);
    +cvm_run(CvmState *vm);
    +cvm_continue(CvmState *vm);
    +cvm_step(CvmState *vm);
    +cvm_exit_code(const CvmState *vm);
    +cvm_instruction_count(const CvmState *vm);
    +cvm_strerror(int error_code);
  }
  class cvm_h_CvmStringEntry {
    <<struct>>
    +cvm_create(const CvmConfig *config);
    +cvm_destroy(CvmState *vm);
    +cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);
    +cvm_load_module_file(CvmState *vm, const char *path);
    +cvm_run(CvmState *vm);
    +cvm_continue(CvmState *vm);
    +cvm_step(CvmState *vm);
    +cvm_exit_code(const CvmState *vm);
    +cvm_instruction_count(const CvmState *vm);
    +cvm_strerror(int error_code);
  }
  class cvm_h_CvmConfig {
    <<struct>>
    +cvm_create(const CvmConfig *config);
    +cvm_destroy(CvmState *vm);
    +cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);
    +cvm_load_module_file(CvmState *vm, const char *path);
    +cvm_run(CvmState *vm);
    +cvm_continue(CvmState *vm);
    +cvm_step(CvmState *vm);
    +cvm_exit_code(const CvmState *vm);
    +cvm_instruction_count(const CvmState *vm);
    +cvm_strerror(int error_code);
  }
  class cvm_h_CvmFrame {
    <<struct>>
    +cvm_create(const CvmConfig *config);
    +cvm_destroy(CvmState *vm);
    +cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);
    +cvm_load_module_file(CvmState *vm, const char *path);
    +cvm_run(CvmState *vm);
    +cvm_continue(CvmState *vm);
    +cvm_step(CvmState *vm);
    +cvm_exit_code(const CvmState *vm);
    +cvm_instruction_count(const CvmState *vm);
    +cvm_strerror(int error_code);
  }
  class cvm_h_CvmNative {
    <<struct>>
    +cvm_create(const CvmConfig *config);
    +cvm_destroy(CvmState *vm);
    +cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);
    +cvm_load_module_file(CvmState *vm, const char *path);
    +cvm_run(CvmState *vm);
    +cvm_continue(CvmState *vm);
    +cvm_step(CvmState *vm);
    +cvm_exit_code(const CvmState *vm);
    +cvm_instruction_count(const CvmState *vm);
    +cvm_strerror(int error_code);
  }
  class cvm_h_CvmBreakpoint {
    <<struct>>
    +cvm_create(const CvmConfig *config);
    +cvm_destroy(CvmState *vm);
    +cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);
    +cvm_load_module_file(CvmState *vm, const char *path);
    +cvm_run(CvmState *vm);
    +cvm_continue(CvmState *vm);
    +cvm_step(CvmState *vm);
    +cvm_exit_code(const CvmState *vm);
    +cvm_instruction_count(const CvmState *vm);
    +cvm_strerror(int error_code);
  }
  class cvm_h_CvmState {
    <<struct>>
    +cvm_create(const CvmConfig *config);
    +cvm_destroy(CvmState *vm);
    +cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);
    +cvm_load_module_file(CvmState *vm, const char *path);
    +cvm_run(CvmState *vm);
    +cvm_continue(CvmState *vm);
    +cvm_step(CvmState *vm);
    +cvm_exit_code(const CvmState *vm);
    +cvm_instruction_count(const CvmState *vm);
    +cvm_strerror(int error_code);
  }
  class cvm_jit_c_JitCtx {
    <<struct>>
    +cvm_jit_create(void)
    +cvm_jit_destroy(CvmJitState *jit)
    +ip_map_clear(CvmJitState *jit)
    +ip_map_add(CvmJitState *jit, size_t bc_ip, size_t native_off)
    +ip_map_lookup(const CvmJitState *jit, size_t bc_ip)
    +func_cache_find(CvmJitState *jit, uint32_t func_idx)
    +func_cache_add(CvmJitState *jit, uint32_t func_idx,
                        ...
    +opcode_total_size(const uint8_t *code, size_t code_size, size_t ip)
    +emit_stack_push(JitBuf *b)
    +emit_stack_pop(JitBuf *b)
  }
  class cvm_jit_h_JitFuncEntry {
    <<struct>>
    +cvm_jit_create(void);
    +cvm_jit_destroy(CvmJitState *jit);
    +cvm_jit_compile_module(CvmState *vm);
    +cvm_jit_compile_func(CvmState *vm, uint32_t func_idx);
    +cvm_jit_lookup(CvmState *vm, uint32_t func_idx);
    +cvm_jit_run(CvmState *vm);
    +returns(via RET) or encounters an error. */ void cvm_jit_exec_one(CvmState *vm);
    +cvm_jit_stats(const CvmState *vm);
    +cvm_jit_dump(const CvmState *vm);
  }
  class cvm_jit_h_JitIpMap {
    <<struct>>
    +cvm_jit_create(void);
    +cvm_jit_destroy(CvmJitState *jit);
    +cvm_jit_compile_module(CvmState *vm);
    +cvm_jit_compile_func(CvmState *vm, uint32_t func_idx);
    +cvm_jit_lookup(CvmState *vm, uint32_t func_idx);
    +cvm_jit_run(CvmState *vm);
    +returns(via RET) or encounters an error. */ void cvm_jit_exec_one(CvmState *vm);
    +cvm_jit_stats(const CvmState *vm);
    +cvm_jit_dump(const CvmState *vm);
  }
  class cvm_jit_h_CvmJitState {
    <<struct>>
    +cvm_jit_create(void);
    +cvm_jit_destroy(CvmJitState *jit);
    +cvm_jit_compile_module(CvmState *vm);
    +cvm_jit_compile_func(CvmState *vm, uint32_t func_idx);
    +cvm_jit_lookup(CvmState *vm, uint32_t func_idx);
    +cvm_jit_run(CvmState *vm);
    +returns(via RET) or encounters an error. */ void cvm_jit_exec_one(CvmState *vm);
    +cvm_jit_stats(const CvmState *vm);
    +cvm_jit_dump(const CvmState *vm);
  }
  class cvm_jit_help_h_CvmJitOffsets {
    <<struct>>
    +cvm_jit_offsets_init(CvmJitOffsets *off);
    +cvm_jit_func_enter(CvmState *vm, uint32_t func_idx);
    +cvm_jit_func_leave(CvmState *vm);
    +cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc);
    +to(vm->ip is set). * Returns 1 if this was the entry frame (vm->running = 0, done). */ int cvm_jit_ret(CvmState *vm, uint64_t retval);
    +cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc);
    +region(heap, globals, string pool, or any frame's locals). * Returns 1 if valid, 0 if invalid. */ int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size);
    +cvm_jit_alloc(CvmState *vm, size_t size);
    +cvm_jit_syscall(CvmState *vm, uint8_t syscall_nr, uint8_t argc);
    +cvm_jit_error(CvmState *vm, int error_code);
  }
  class cvm_jit_x86_h_JitBuf {
    <<struct>>
    +reg_needs_rex(int r)
    +reg_high3(int r)
    +jit_buf_init(JitBuf *b, size_t initial_cap);
    +jit_buf_free(JitBuf *b);
    +jit_buf_reset(JitBuf *b);
    +jit_buf_failed(const JitBuf *b);
    +emit8(JitBuf *b, uint8_t v);
    +emit16(JitBuf *b, uint16_t v);
    +emit32(JitBuf *b, uint32_t v);
    +emit64(JitBuf *b, uint64_t v);
  }
  class cvm_jit_x86_h_JitPatch {
    <<struct>>
    +reg_needs_rex(int r)
    +reg_high3(int r)
    +jit_buf_init(JitBuf *b, size_t initial_cap);
    +jit_buf_free(JitBuf *b);
    +jit_buf_reset(JitBuf *b);
    +jit_buf_failed(const JitBuf *b);
    +emit8(JitBuf *b, uint8_t v);
    +emit16(JitBuf *b, uint16_t v);
    +emit32(JitBuf *b, uint32_t v);
    +emit64(JitBuf *b, uint64_t v);
  }
  class cvm_jit_x86_h_JitPatches {
    <<struct>>
    +reg_needs_rex(int r)
    +reg_high3(int r)
    +jit_buf_init(JitBuf *b, size_t initial_cap);
    +jit_buf_free(JitBuf *b);
    +jit_buf_reset(JitBuf *b);
    +jit_buf_failed(const JitBuf *b);
    +emit8(JitBuf *b, uint8_t v);
    +emit16(JitBuf *b, uint16_t v);
    +emit32(JitBuf *b, uint32_t v);
    +emit64(JitBuf *b, uint64_t v);
  }
  class cvm_ops_h_CvmOpInfo {
    <<struct>>
    +cvm_op_info(uint8_t opcode);
    +cvm_op_name(uint8_t opcode);
    +cvm_ops_ri32(const uint8_t *code, size_t size, size_t off);
    +cvm_ops_ri64(const uint8_t *code, size_t size, size_t off);
    +cvm_ops_ru32(const uint8_t *code, size_t size, size_t off);
    +cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out);
  }
  class cvm_val_main_c_DepthRange {
    <<struct>>
    +val_err(ValCtx *ctx, const char *what)
    +val_fun_err(FuncCtx *fc, const char *what)
    +code_of(const CvmModuleView *v)
    +q_push(FuncCtx *fc, size_t off)
    +q_pop(FuncCtx *fc)
    +dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)
    +stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...
    +check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)
    +analyze_stack(FuncCtx *fc)
    +check_function(FuncCtx *fc, size_t *insn_count)
  }
  class cvm_val_main_c_ValCtx {
    <<struct>>
    +val_err(ValCtx *ctx, const char *what)
    +val_fun_err(FuncCtx *fc, const char *what)
    +code_of(const CvmModuleView *v)
    +q_push(FuncCtx *fc, size_t off)
    +q_pop(FuncCtx *fc)
    +dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)
    +stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...
    +check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)
    +analyze_stack(FuncCtx *fc)
    +check_function(FuncCtx *fc, size_t *insn_count)
  }
  class cvm_val_main_c_FuncCtx {
    <<struct>>
    +val_err(ValCtx *ctx, const char *what)
    +val_fun_err(FuncCtx *fc, const char *what)
    +code_of(const CvmModuleView *v)
    +q_push(FuncCtx *fc, size_t off)
    +q_pop(FuncCtx *fc)
    +dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)
    +stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...
    +check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)
    +analyze_stack(FuncCtx *fc)
    +check_function(FuncCtx *fc, size_t *insn_count)
  }
  class cvm_val_main_c_StackEffect {
    <<struct>>
    +val_err(ValCtx *ctx, const char *what)
    +val_fun_err(FuncCtx *fc, const char *what)
    +code_of(const CvmModuleView *v)
    +q_push(FuncCtx *fc, size_t off)
    +q_pop(FuncCtx *fc)
    +dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)
    +stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...
    +check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)
    +analyze_stack(FuncCtx *fc)
    +check_function(FuncCtx *fc, size_t *insn_count)
  }
  class cvm_view_h_CvmModuleView {
    <<struct>>
    +cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size);
    +cvm_view_strerror(int error_code);
    +cvm_view_func(const CvmModuleView *v, uint32_t i);
    +cvm_view_string(const CvmModuleView *v, uint32_t off);
    +cvm_view_func_name(const CvmModuleView *v, uint32_t fi, char *fallback, size_t cap);
    +cvm_view_func_region(const CvmModuleView *v, uint32_t fi, size_t *begin, size_t *end);
  }
  cvm_c_Vout --> cvm_h_CVM : uses
  cvm_c_Vout --> cvm_h_CVM_Frame : uses
  cvm_c_Vout --> cvm_h_CVM_FuncEntry : uses
  cvm_c_Vout --> cvm_h_CVM_GlobalEntry : uses
  cvm_c_Vout --> cvm_h_CVM_Header : uses
  cvm_c_Vout --> cvm_h_CVM_Module : uses
  cvm_c_Vout --> cvm_h_CVM_NativeEntry : uses
  cvm_c_Vout --> cvm_h_CVM_StringEntry : uses
  cvm_jit_h_CvmJitState --> cvm_h_CVM : uses
  cvm_jit_h_CvmJitState --> cvm_h_CVM_Frame : uses
  cvm_jit_h_CvmJitState --> cvm_h_CVM_FuncEntry : uses
  cvm_jit_h_CvmJitState --> cvm_h_CVM_GlobalEntry : uses
  cvm_jit_h_CvmJitState --> cvm_h_CVM_Header : uses
  cvm_jit_h_CvmJitState --> cvm_h_CVM_Module : uses
  cvm_jit_h_CvmJitState --> cvm_h_CVM_NativeEntry : uses
  cvm_jit_h_CvmJitState --> cvm_h_CVM_StringEntry : uses
  cvm_jit_h_JitFuncEntry --> cvm_h_CVM : uses
  cvm_jit_h_JitFuncEntry --> cvm_h_CVM_Frame : uses
  cvm_jit_h_JitFuncEntry --> cvm_h_CVM_FuncEntry : uses
  cvm_jit_h_JitFuncEntry --> cvm_h_CVM_GlobalEntry : uses
  cvm_jit_h_JitFuncEntry --> cvm_h_CVM_Header : uses
  cvm_jit_h_JitFuncEntry --> cvm_h_CVM_Module : uses
  cvm_jit_h_JitFuncEntry --> cvm_h_CVM_NativeEntry : uses
  cvm_jit_h_JitFuncEntry --> cvm_h_CVM_StringEntry : uses
  cvm_jit_h_JitIpMap --> cvm_h_CVM : uses
  cvm_jit_h_JitIpMap --> cvm_h_CVM_Frame : uses
  cvm_jit_h_JitIpMap --> cvm_h_CVM_FuncEntry : uses
  cvm_jit_h_JitIpMap --> cvm_h_CVM_GlobalEntry : uses
  cvm_jit_h_JitIpMap --> cvm_h_CVM_Header : uses
  cvm_jit_h_JitIpMap --> cvm_h_CVM_Module : uses
  cvm_jit_h_JitIpMap --> cvm_h_CVM_NativeEntry : uses
  cvm_jit_h_JitIpMap --> cvm_h_CVM_StringEntry : uses
  cvm_jit_help_h_CvmJitOffsets --> cvm_h_CVM : uses
  cvm_jit_help_h_CvmJitOffsets --> cvm_h_CVM_Frame : uses
  cvm_jit_help_h_CvmJitOffsets --> cvm_h_CVM_FuncEntry : uses
  cvm_jit_help_h_CvmJitOffsets --> cvm_h_CVM_GlobalEntry : uses
  cvm_jit_help_h_CvmJitOffsets --> cvm_h_CVM_Header : uses
  cvm_jit_help_h_CvmJitOffsets --> cvm_h_CVM_Module : uses
  cvm_jit_help_h_CvmJitOffsets --> cvm_h_CVM_NativeEntry : uses
  cvm_jit_help_h_CvmJitOffsets --> cvm_h_CVM_StringEntry : uses
  cvm_view_h_CvmModuleView --> cvm_h_CVM : uses
  cvm_view_h_CvmModuleView --> cvm_h_CVM_Frame : uses
  cvm_view_h_CvmModuleView --> cvm_h_CVM_FuncEntry : uses
  cvm_view_h_CvmModuleView --> cvm_h_CVM_GlobalEntry : uses
  cvm_view_h_CvmModuleView --> cvm_h_CVM_Header : uses
  cvm_view_h_CvmModuleView --> cvm_h_CVM_Module : uses
  cvm_view_h_CvmModuleView --> cvm_h_CVM_NativeEntry : uses
  cvm_view_h_CvmModuleView --> cvm_h_CVM_StringEntry : uses
```

---

## Code Property Graph

Machine-readable Code Property Graph (CPG) in JSON-LD format. This block allows AI agents to parse the full structural graph without additional file reads. Compatible with GraphRAG pipelines.

```json
{"@context": "https://schema.org", "analysis": {"communities": [{"cohesion": 0.731, "id": 0, "label": "cvm2: cvm", "size": 12}, {"cohesion": 0.462, "id": 1, "label": "cvm2: cvm_dbg_main", "size": 5}, {"cohesion": 0.4, "id": 2, "label": "cvm2: cvm_jit", "size": 5}], "god_nodes": [{"node_id": "cvm.h", "score": 22.8}, {"node_id": "cvm2/cvm.h", "score": 21.6}, {"node_id": "cvm2/cvm_jit.h", "score": 18.6}, {"node_id": "cvm2/cvm.c", "score": 16.4}, {"node_id": "cvm2/cvm_view.h", "score": 14.9}, {"node_id": "cvm2/cvm_dbg_main.c", "score": 12.1}, {"node_id": "cvm2/cvm_jit_x86.h", "score": 11.1}, {"node_id": "cvm2/cvm_ops.h", "score": 10.9}, {"node_id": "cvm2/cvm_jit_help.h", "score": 9.3}, {"node_id": "cvm2/cvm_jit_x86.c", "score": 9.3}], "surprising_connections": [{"hops": 5, "source": "cvm2/cvm_dis.c", "target": "cvm2/cvm_jit_x86.c"}, {"hops": 5, "source": "cvm2/cvm_dis.h", "target": "cvm2/cvm_jit_x86.c"}, {"hops": 5, "source": "cvm2/cvm_dis_main.c", "target": "cvm2/cvm_jit_x86.c"}, {"hops": 5, "source": "cvm2/cvm_jit_x86.c", "target": "cvm2/cvm_val_main.c"}, {"hops": 5, "source": "cvm2/cvm_jit_x86.c", "target": "cvm2/cvm_view.c"}]}, "edges": [{"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.c", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.c", "target": "stdarg.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.c", "target": "errno.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.h", "target": "stdint.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.h", "target": "stddef.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.h", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.h", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.h", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.h", "target": "dlfcn.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.h", "target": "unistd.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm.h", "target": "sys/mman.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.c", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.c", "target": "cvm_jit.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.c", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.c", "target": "unistd.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.h", "target": "stdint.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.h", "target": "stddef.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.h", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.h", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.h", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm.h", "target": "unistd.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dbg_main.c", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dbg_main.c", "target": "cvm_view.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dbg_main.c", "target": "cvm_dis.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dbg_main.c", "target": "cvm_ops.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dbg_main.c", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dbg_main.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dbg_main.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dbg_main.c", "target": "unistd.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dis.c", "target": "cvm_dis.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dis.c", "target": "cvm_ops.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dis.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dis.h", "target": "stddef.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dis.h", "target": "stdint.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dis.h", "target": "cvm_view.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dis_main.c", "target": "cvm_view.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dis_main.c", "target": "cvm_dis.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dis_main.c", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_dis_main.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit.c", "target": "cvm_jit.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit.c", "target": "cvm_ops.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit.c", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit.h", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit.h", "target": "cvm_jit_x86.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit.h", "target": "cvm_jit_help.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_help.c", "target": "cvm_jit_help.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_help.c", "target": "cvm_jit.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_help.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_help.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_help.c", "target": "unistd.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_help.h", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_x86.c", "target": "cvm_jit_x86.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_x86.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_x86.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_x86.c", "target": "sys/mman.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_x86.h", "target": "stdint.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_jit_x86.h", "target": "stddef.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_ops.c", "target": "cvm_ops.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_ops.c", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_ops.h", "target": "stdint.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_ops.h", "target": "stddef.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_val_main.c", "target": "cvm_view.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_val_main.c", "target": "cvm_ops.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_val_main.c", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_val_main.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_val_main.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_view.c", "target": "cvm_view.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_view.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_view.h", "target": "stdint.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_view.h", "target": "stddef.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/cvm_view.h", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_fib_cvm.c", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_fib_cvm.c", "target": "cvm_jit.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_fib_cvm.c", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_fib_cvm.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_fib_cvm.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_minimal.c", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_minimal.c", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_minimal.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_minimal.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_test.py", "target": "struct"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_test.py", "target": "sys"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "cvm2/gen_test.py", "target": "subprocess"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "gen_fib_cvm.c", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "gen_fib_cvm.c", "target": "stdio.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "gen_fib_cvm.c", "target": "stdlib.h"}, {"confidence": "EXTRACTED", "relation": "imports", "source": "gen_fib_cvm.c", "target": "string.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm.c", "target": "cvm.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm.c", "target": "cvm2/cvm.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm.c", "target": "cvm2/cvm_jit.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_dbg_main.c", "target": "cvm2/cvm.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_dbg_main.c", "target": "cvm2/cvm_view.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_dbg_main.c", "target": "cvm2/cvm_dis.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_dbg_main.c", "target": "cvm2/cvm_ops.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_dis.c", "target": "cvm2/cvm_dis.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_dis.c", "target": "cvm2/cvm_ops.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_dis.h", "target": "cvm2/cvm_view.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_dis_main.c", "target": "cvm2/cvm_view.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_dis_main.c", "target": "cvm2/cvm_dis.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_jit.c", "target": "cvm2/cvm_jit.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_jit.c", "target": "cvm2/cvm_ops.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_jit.h", "target": "cvm2/cvm.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_jit.h", "target": "cvm2/cvm_jit_x86.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_jit.h", "target": "cvm2/cvm_jit_help.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_jit_help.c", "target": "cvm2/cvm_jit_help.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_jit_help.c", "target": "cvm2/cvm_jit.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_jit_help.h", "target": "cvm2/cvm.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_jit_x86.c", "target": "cvm2/cvm_jit_x86.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_ops.c", "target": "cvm2/cvm_ops.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_ops.c", "target": "cvm2/cvm.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_val_main.c", "target": "cvm2/cvm_view.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_val_main.c", "target": "cvm2/cvm_ops.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_view.c", "target": "cvm2/cvm_view.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/cvm_view.h", "target": "cvm2/cvm.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/gen_fib_cvm.c", "target": "cvm2/cvm.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/gen_fib_cvm.c", "target": "cvm2/cvm_jit.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "cvm2/gen_minimal.c", "target": "cvm2/cvm.h"}, {"confidence": "EXTRACTED", "relation": "resolved_imports", "source": "gen_fib_cvm.c", "target": "cvm.h"}], "generator": "readmenator", "metadata": {"edge_count": 125, "file_count": 26, "language_count": 4, "symbol_count": 565}, "nodes": [{"id": "cvm.c", "kind": "module", "label": "cvm.c", "language": "c", "sha256": "4863b9627ae07b1a", "symbol_count": 20, "symbols": [{"doc": "cvm.c — C Virtual Machine interpreter  #include \"cvm.h\" #include <stdarg.h> #include <errno.h> /* ------------------------------------------------------------------ /*  Debug helpers /* ------------------------------------------------------------------", "kind": "function", "line": 12, "name": "cvm_error", "signature": "static void cvm_error(CVM *vm, const char *fmt, ...)"}, {"kind": "function", "line": 22, "name": "op_name", "signature": "static const char *op_name(uint8_t op)"}, {"doc": "case OP_RET: return \"RET\"; case OP_RET_VOID: return \"RET_VOID\"; case OP_ALLOC: return \"ALLOC\"; case OP_FREE: return \"FREE\"; case OP_SYSCALL: return \"SYSCALL\"; case OP_PRINT_I64: return \"PRINT_I64\"; case OP_HALT: return \"HALT\"; default: return \"???\"; } } /* ------------------------------------------------------------------ /*  Stack helpers /* ------------------------------------------------------------------", "kind": "function", "line": 78, "name": "push", "signature": "static inline void push(CVM *vm, uint64_t v)"}, {"kind": "function", "line": 86, "name": "pop", "signature": "static inline uint64_t pop(CVM *vm)"}, {"kind": "function", "line": 94, "name": "peek", "signature": "static inline uint64_t peek(CVM *vm)"}, {"doc": "cvm_error(vm, \"operand stack underflow\"); return 0; } return vm->stack[--vm->sp]; } static inline uint64_t peek(CVM *vm) { if (vm->sp <= 0) return 0; return vm->stack[vm->sp - 1]; } /* ------------------------------------------------------------------ /*  Frame helpers /* ------------------------------------------------------------------", "kind": "function", "line": 102, "name": "push_frame", "signature": "static int push_frame(CVM *vm, CVM_Module *mod, uint16_t func_idx, int argc)"}, {"kind": "function", "line": 142, "name": "pop_frame", "signature": "static void pop_frame(CVM *vm, int has_retval)"}, {"doc": "if (has_retval) push(vm, ret); vm->running = 0; return; } /* restore previous module / code pointer if needed /* (for multi-module we would look up the previous frame's module) vm->ip = ret_ip; if (has_retval) push(vm, ret); } /* ------------------------------------------------------------------ /*  Native call (very limited – only a few for the tests) /* ------------------------------------------------------------------", "kind": "function", "line": 175, "name": "call_native", "signature": "static void call_native(CVM *vm, uint16_t idx, uint8_t argc)"}, {"doc": "(void)fd; (void)buf; (void)len; } push(vm, 0); return; } /* generic: just pop args and push 0 for (int i = 0; i < argc; i++) pop(vm); push(vm, 0); } /* ------------------------------------------------------------------ /*  Create / destroy /* ------------------------------------------------------------------", "kind": "function", "line": 227, "name": "cvm_create", "signature": "CVM *cvm_create(void)"}, {"kind": "function", "line": 244, "name": "cvm_destroy", "signature": "void cvm_destroy(CVM *vm)"}, {"doc": "free(m->natives); free(m->code); free(m->string_pool); free(m->global_mem); free(m); } free(vm->stack); free(vm->heap); free(vm); } /* ------------------------------------------------------------------ /*  Load module from memory /* ------------------------------------------------------------------", "kind": "function", "line": 267, "name": "cvm_load_module_mem", "signature": "int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name)"}, {"kind": "function", "line": 337, "name": "cvm_load_module", "signature": "int cvm_load_module(CVM *vm, const char *path)"}, {"doc": "if (!buf || fread(buf, 1, (size_t)sz, f) != (size_t)sz) { free(buf); fclose(f); return -1; } fclose(f); int r = cvm_load_module_mem(vm, buf, (size_t)sz, path); free(buf); return r; } /* ------------------------------------------------------------------ /*  Main interpreter loop /* ------------------------------------------------------------------", "kind": "function", "line": 361, "name": "interpret", "signature": "static int interpret(CVM *vm)"}, {"doc": "vm->running = 0; break; default: cvm_error(vm, \"unknown opcode 0x%02x at ip=%u\", op, vm->ip - 1); break; } } return 0; } /* ------------------------------------------------------------------ /*  Public run /* ------------------------------------------------------------------", "kind": "function", "line": 700, "name": "cvm_run", "signature": "int cvm_run(CVM *vm, const char *entry_name)"}, {"doc": "if (vm->trace) fprintf(stderr, \"Finished. instructions = %llu\\n\", (unsigned long long)vm->instr_count); /* if there is a return value left on the stack, return it as exit code if (vm->sp > 0) return (int)(int64_t)vm->stack[vm->sp - 1]; return 0; } /* ------------------------------------------------------------------ /*  Emitter helpers (used by the backend) /* ------------------------------------------------------------------", "kind": "function", "line": 743, "name": "cvm_emit_byte", "signature": "void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b)"}, {"kind": "function", "line": 751, "name": "cvm_emit_i16", "signature": "void cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v)"}, {"kind": "function", "line": 756, "name": "cvm_emit_u16", "signature": "void cvm_emit_u16(uint8_t **buf, size_t *cap, size_t *len, uint16_t v)"}, {"kind": "function", "line": 761, "name": "cvm_emit_i32", "signature": "void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v)"}, {"kind": "function", "line": 766, "name": "cvm_emit_i64", "signature": "void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v)"}, {"doc": "void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v) { for (int i = 0; i < 4; i++) cvm_emit_byte(buf, cap, len, (uint8_t)((v >> (i * 8)) & 0xff)); } void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v) { for (int i = 0; i < 8; i++) cvm_emit_byte(buf, cap, len, (uint8_t)((v >> (i * 8)) & 0xff)); } /* ------------------------------------------------------------------ /*  Main (standalone runner) /* ------------------------------------------------------------------ ifdef CVM_STANDALONE", "kind": "function", "line": 775, "name": "main", "signature": "int main(int argc, char **argv)"}]}, {"id": "cvm.h", "kind": "module", "label": "cvm.h", "language": "h", "sha256": "a1457356fd067b9a", "symbol_count": 28, "symbols": [{"kind": "struct", "line": 169, "name": "CVM_Module"}, {"doc": "/* Heap OP_ALLOC        = 0x80,   /* size on stack → ptr OP_FREE         = 0x81, /* Syscalls / misc OP_SYSCALL      = 0x90,   /* nr, arg0..arg5 on stack (Linux x86-64 style) OP_PRINT_I64    = 0x91,   /* debug helper OP_HALT         = 0xFF }; /* ------------------------------------------------------------------ /*  Module format (on disk / in memory) /* ------------------------------------------------------------------ pragma pack(push, 1)", "kind": "struct", "line": 107, "name": "CVM_Header"}, {"kind": "struct", "line": 126, "name": "CVM_FuncEntry"}, {"kind": "struct", "line": 136, "name": "CVM_GlobalEntry"}, {"kind": "struct", "line": 142, "name": "CVM_StringEntry"}, {"kind": "struct", "line": 147, "name": "CVM_NativeEntry"}, {"kind": "struct", "line": 161, "name": "CVM_Frame"}, {"kind": "struct", "line": 182, "name": "CVM"}, {"kind": "type_alias", "line": 168, "name": "hdr", "signature": "typedef struct CVM_Module { CVM_Header hdr;"}, {"doc": "/* Heap (bump allocator for simplicity) uint8_t    *heap; size_t      heap_used; size_t      heap_size; /* Stats / debug uint64_t    instr_count; int         running; int         trace; } CVM; /* ------------------------------------------------------------------ /*  Public API /* ------------------------------------------------------------------", "kind": "function", "line": 215, "name": "cvm_create", "signature": "CVM *cvm_create(void);"}, {"kind": "function", "line": 216, "name": "cvm_destroy", "signature": "void cvm_destroy(CVM *vm);"}, {"kind": "function", "line": 217, "name": "cvm_load_module", "signature": "int cvm_load_module(CVM *vm, const char *path);"}, {"kind": "function", "line": 218, "name": "cvm_load_module_mem", "signature": "int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);"}, {"kind": "function", "line": 219, "name": "cvm_run", "signature": "int cvm_run(CVM *vm, const char *entry_name);"}, {"kind": "function", "line": 220, "name": "cvm_call", "signature": "int cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);"}, {"doc": "int         trace; } CVM; /* ------------------------------------------------------------------ /*  Public API /* ------------------------------------------------------------------ CVM        *cvm_create(void); void        cvm_destroy(CVM *vm); int         cvm_load_module(CVM *vm, const char *path); int         cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name); int         cvm_run(CVM *vm, const char *entry_name); int         cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args); /* Helpers used by the backend emitter", "kind": "function", "line": 223, "name": "cvm_emit_byte", "signature": "void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);"}, {"kind": "function", "line": 224, "name": "cvm_emit_i16", "signature": "void cvm_emit_i16 (uint8_t **buf, size_t *cap, size_t *len, int16_t v);"}, {"kind": "function", "line": 225, "name": "cvm_emit_i32", "signature": "void cvm_emit_i32 (uint8_t **buf, size_t *cap, size_t *len, int32_t v);"}, {"kind": "function", "line": 226, "name": "cvm_emit_i64", "signature": "void cvm_emit_i64 (uint8_t **buf, size_t *cap, size_t *len, int64_t v);"}, {"kind": "function", "line": 227, "name": "cvm_emit_u16", "signature": "void cvm_emit_u16 (uint8_t **buf, size_t *cap, size_t *len, uint16_t v);"}, {"kind": "macro", "line": 8, "name": "CVM_H", "signature": "#define CVM_H"}, {"kind": "macro", "line": 22, "name": "CVM_MAGIC", "signature": "#define CVM_MAGIC"}, {"kind": "macro", "line": 23, "name": "CVM_VERSION", "signature": "#define CVM_VERSION"}, {"kind": "macro", "line": 155, "name": "CVM_STACK_SIZE", "signature": "#define CVM_STACK_SIZE"}, {"kind": "macro", "line": 156, "name": "CVM_FRAME_DEPTH", "signature": "#define CVM_FRAME_DEPTH"}, {"kind": "macro", "line": 157, "name": "CVM_HEAP_SIZE", "signature": "#define CVM_HEAP_SIZE"}, {"kind": "macro", "line": 158, "name": "CVM_MAX_MODULES", "signature": "#define CVM_MAX_MODULES"}, {"kind": "macro", "line": 159, "name": "CVM_MAX_NATIVES", "signature": "#define CVM_MAX_NATIVES"}]}, {"id": "cvm2/cvm.c", "kind": "module", "label": "cvm.c", "language": "c", "sha256": "9137452c631f3f75", "symbol_count": 104, "symbols": [{"doc": "static int64_t native_atol(void *vm, int ac, uint64_t *av) { (void)vm; if (ac < 1) return 0; return (int64_t)strtol((const char *)(uintptr_t)av[0], NULL, 10); } static int64_t native_strtol(void *vm, int ac, uint64_t *av) { (void)vm; if (ac < 1) return 0; int base = ac > 1 ? (int)av[1] : 10; return (int64_t)strtol((const char *)(uintptr_t)av[0], NULL, base); } /* ---- mini printf engine ----", "kind": "struct", "line": 465, "name": "Vout"}, {"kind": "function", "line": 28, "name": "xmal", "signature": "static void *xmal(size_t s)"}, {"kind": "function", "line": 34, "name": "xcal", "signature": "static void *xcal(size_t n, size_t s)"}, {"kind": "function", "line": 40, "name": "cvm_config_default", "signature": "CvmConfig cvm_config_default(void)"}, {"kind": "function", "line": 55, "name": "cvm_create", "signature": "CvmState *cvm_create(const CvmConfig *config)"}, {"kind": "function", "line": 94, "name": "cvm_destroy", "signature": "void cvm_destroy(CvmState *vm)"}, {"kind": "function", "line": 113, "name": "cvm_strerror", "signature": "const char *cvm_strerror(int e)"}, {"kind": "function", "line": 137, "name": "vp", "signature": "static int vp(CvmState *vm, uint64_t v)"}, {"kind": "function", "line": 143, "name": "vo", "signature": "static int vo(CvmState *vm, uint64_t *v)"}, {"kind": "function", "line": 149, "name": "r8", "signature": "static int r8(CvmState *vm, uint8_t *o)"}, {"kind": "function", "line": 155, "name": "r32", "signature": "static int r32(CvmState *vm, uint32_t *o)"}, {"kind": "function", "line": 165, "name": "ri32", "signature": "static int ri32(CvmState *vm, int32_t *o)"}, {"kind": "function", "line": 173, "name": "r64", "signature": "static int r64(CvmState *vm, uint64_t *o)"}, {"kind": "function", "line": 183, "name": "push_frame", "signature": "static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,\n                      ..."}, {"kind": "function", "line": 196, "name": "pop_frame", "signature": "static void pop_frame(CvmState *vm)"}, {"kind": "function", "line": 203, "name": "cur_frame", "signature": "static CvmFrame *cur_frame(CvmState *vm)"}, {"kind": "function", "line": 207, "name": "range_valid", "signature": "static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)"}, {"kind": "function", "line": 215, "name": "mem_valid", "signature": "static int mem_valid(CvmState *vm, uint64_t a, size_t s)"}, {"kind": "function", "line": 227, "name": "heap_alloc", "signature": "static uint64_t heap_alloc(CvmState *vm, size_t s)"}, {"kind": "function", "line": 235, "name": "cvm_heap_alloc", "signature": "void *cvm_heap_alloc(CvmState *vm, size_t size)"}, {"kind": "function", "line": 239, "name": "data_w64", "signature": "static void data_w64(CvmState *vm, size_t off, uint64_t v)"}, {"kind": "function", "line": 244, "name": "data_r64", "signature": "static uint64_t data_r64(CvmState *vm, size_t off)"}, {"kind": "function", "line": 250, "name": "cvm_set_args", "signature": "int cvm_set_args(CvmState *vm, int argc, char **argv)"}, {"kind": "function", "line": 283, "name": "cvm_register_native", "signature": "int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn)"}, {"kind": "function", "line": 294, "name": "find_native", "signature": "static int find_native(CvmState *vm, const char *name)"}, {"kind": "function", "line": 305, "name": "native_write", "signature": "static int64_t native_write(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 311, "name": "native_read", "signature": "static int64_t native_read(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 317, "name": "native_exit", "signature": "static int64_t native_exit(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 324, "name": "native_abort", "signature": "static int64_t native_abort(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 329, "name": "native_putchar", "signature": "static int64_t native_putchar(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 336, "name": "native_puts", "signature": "static int64_t native_puts(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 350, "name": "native_strlen", "signature": "static int64_t native_strlen(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 356, "name": "native_strcmp", "signature": "static int64_t native_strcmp(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 362, "name": "native_strncmp", "signature": "static int64_t native_strncmp(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 369, "name": "native_strcpy", "signature": "static int64_t native_strcpy(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 375, "name": "native_strncpy", "signature": "static int64_t native_strncpy(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 382, "name": "native_strchr", "signature": "static int64_t native_strchr(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 388, "name": "native_strstr", "signature": "static int64_t native_strstr(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 395, "name": "native_memcpy", "signature": "static int64_t native_memcpy(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 402, "name": "native_memmove", "signature": "static int64_t native_memmove(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 409, "name": "native_memset", "signature": "static int64_t native_memset(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 415, "name": "native_memcmp", "signature": "static int64_t native_memcmp(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 422, "name": "native_malloc", "signature": "static int64_t native_malloc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 428, "name": "native_free", "signature": "static int64_t native_free(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 433, "name": "native_calloc", "signature": "static int64_t native_calloc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 442, "name": "native_realloc", "signature": "static int64_t native_realloc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 451, "name": "native_atol", "signature": "static int64_t native_atol(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 457, "name": "native_strtol", "signature": "static int64_t native_strtol(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 472, "name": "vout_write", "signature": "static void vout_write(Vout *vo, const char *s, size_t n)"}, {"kind": "function", "line": 484, "name": "vout_char", "signature": "static void vout_char(Vout *vo, char c)"}, {"kind": "function", "line": 486, "name": "vout_uint", "signature": "static void vout_uint(Vout *vo, uint64_t v, int base, int upper)"}, {"kind": "function", "line": 499, "name": "vformat", "signature": "static void vformat(Vout *vo, const char *fmt, uint64_t *argv, int argc)"}, {"kind": "function", "line": 583, "name": "native_fprintf", "signature": "static int64_t native_fprintf(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 593, "name": "native_printf", "signature": "static int64_t native_printf(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 602, "name": "native_sprintf", "signature": "static int64_t native_sprintf(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 613, "name": "native_snprintf", "signature": "static int64_t native_snprintf(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 625, "name": "native_fopen", "signature": "static int64_t native_fopen(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 632, "name": "native_fclose", "signature": "static int64_t native_fclose(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 638, "name": "native_fread", "signature": "static int64_t native_fread(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 645, "name": "native_fwrite", "signature": "static int64_t native_fwrite(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 652, "name": "native_fseek", "signature": "static int64_t native_fseek(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 658, "name": "native_ftell", "signature": "static int64_t native_ftell(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 664, "name": "native_rewind", "signature": "static int64_t native_rewind(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 671, "name": "native_fputs", "signature": "static int64_t native_fputs(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 677, "name": "native_fputc", "signature": "static int64_t native_fputc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 683, "name": "native_fgetc", "signature": "static int64_t native_fgetc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 689, "name": "native_ungetc", "signature": "static int64_t native_ungetc(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 695, "name": "native_fflush", "signature": "static int64_t native_fflush(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 701, "name": "native_perror", "signature": "static int64_t native_perror(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 712, "name": "native_stderr_addr", "signature": "static int64_t native_stderr_addr(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 717, "name": "native_stdout_addr", "signature": "static int64_t native_stdout_addr(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 722, "name": "native_stdin_addr", "signature": "static int64_t native_stdin_addr(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 729, "name": "native_exit_core", "signature": "static int64_t native_exit_core(void *vm, int ac, uint64_t *av)"}, {"kind": "function", "line": 736, "name": "register_defaults", "signature": "static void register_defaults(CvmState *vm)"}, {"doc": "cvm_register_native(vm, \"fputc\", native_fputc); cvm_register_native(vm, \"fgetc\", native_fgetc); cvm_register_native(vm, \"ungetc\", native_ungetc); cvm_register_native(vm, \"fflush\", native_fflush); cvm_register_native(vm, \"perror\", native_perror); cvm_register_native(vm, \"stderr_addr\", native_stderr_addr); cvm_register_native(vm, \"stdout_addr\", native_stdout_addr); cvm_register_native(vm, \"stdin_addr\", native_stdin_addr); #endif } /* ------------------------------------------------------------------ /*  Module loader /* ------------------------------------------------------------------", "kind": "function", "line": 788, "name": "rl32", "signature": "static uint32_t rl32(const uint8_t *p)"}, {"kind": "function", "line": 793, "name": "decompress_rle", "signature": "static int decompress_rle(uint8_t *dst, size_t dsz, const uint8_t *src, size_t ssz)"}, {"kind": "function", "line": 815, "name": "cvm_free_module", "signature": "static void cvm_free_module(CvmState *vm)"}, {"kind": "function", "line": 830, "name": "cvm_load_module", "signature": "int cvm_load_module(CvmState *vm, const uint8_t *d, size_t sz)"}, {"kind": "function", "line": 923, "name": "cvm_load_module_file", "signature": "int cvm_load_module_file(CvmState *vm, const char *path)"}, {"doc": "if (sz < 0) { fclose(f); return CVM_ERR_IO; } rewind(f); uint8_t *buf = (uint8_t *)xmal((size_t)sz); size_t rd = fread(buf, 1, (size_t)sz, f); fclose(f); if (rd != (size_t)sz) { free(buf); return CVM_ERR_IO; } int rc = cvm_load_module(vm, buf, (size_t)sz); free(buf); return rc; } /* ------------------------------------------------------------------ /*  Interpreter /* ------------------------------------------------------------------", "kind": "function", "line": 942, "name": "cvm_run_loop", "signature": "static int cvm_run_loop(CvmState *vm)"}, {"kind": "function", "line": 952, "name": "cvm_run", "signature": "int cvm_run(CvmState *vm)"}, {"doc": "rsp = top - 8; (uint64_t *)(uintptr_t)(top - 8) = 0; data_w64(vm, CVM_DATA_RSP, rsp); data_w64(vm, CVM_DATA_RBP, rsp); data_w64(vm, CVM_DATA_ARGC, 0); data_w64(vm, CVM_DATA_ARGV, 0); } } } return cvm_run_loop(vm); } /* Run after a breakpoint: same loop, no state reset.", "kind": "function", "line": 990, "name": "cvm_continue", "signature": "int cvm_continue(CvmState *vm)"}, {"kind": "function", "line": 994, "name": "cvm_break_set", "signature": "int cvm_break_set(CvmState *vm, size_t ip)"}, {"kind": "function", "line": 1003, "name": "cvm_break_clear", "signature": "int cvm_break_clear(CvmState *vm, size_t ip)"}, {"kind": "function", "line": 1014, "name": "cvm_break_clear_all", "signature": "void cvm_break_clear_all(CvmState *vm)"}, {"kind": "function", "line": 1018, "name": "cvm_break_hit", "signature": "int cvm_break_hit(const CvmState *vm)"}, {"kind": "function", "line": 1024, "name": "cvm_profile_begin", "signature": "int cvm_profile_begin(CvmState *vm)"}, {"kind": "function", "line": 1034, "name": "cvm_profile_end", "signature": "void cvm_profile_end(CvmState *vm)"}, {"doc": "if (vm->code_size > vm->config.max_profile_code) return CVM_ERR_BOUNDS; if (!vm->ip_counts) vm->ip_counts = (uint32_t *)xcal(vm->code_size > 0 ? vm->code_size : 1, sizeof(uint32_t)); memset(vm->op_counts, 0, sizeof(vm->op_counts)); vm->profile_enabled = 1; return CVM_OK; } void cvm_profile_end(CvmState *vm) { vm->profile_enabled = 0; } /* Execute exactly one instruction at vm->ip.", "kind": "function", "line": 1039, "name": "cvm_step", "signature": "int cvm_step(CvmState *vm)"}, {"kind": "function", "line": 1351, "name": "cvm_exit_code", "signature": "int64_t cvm_exit_code(const CvmState *vm)"}, {"kind": "function", "line": 1352, "name": "cvm_instruction_count", "signature": "uint64_t cvm_instruction_count(const CvmState *vm)"}, {"doc": "if defined(CVM_STANDALONE) && !defined(CVM_NO_MAIN)", "kind": "function", "line": 1355, "name": "main", "signature": "int main(int argc, char *argv[])"}, {"kind": "macro", "line": 15, "name": "CVM_DEF_STACK", "signature": "#define CVM_DEF_STACK"}, {"kind": "macro", "line": 16, "name": "CVM_DEF_FRAMES", "signature": "#define CVM_DEF_FRAMES"}, {"kind": "macro", "line": 17, "name": "CVM_DEF_LOCALS", "signature": "#define CVM_DEF_LOCALS"}, {"kind": "macro", "line": 18, "name": "CVM_DEF_HEAP", "signature": "#define CVM_DEF_HEAP"}, {"kind": "macro", "line": 19, "name": "CVM_DEF_GLOBALS", "signature": "#define CVM_DEF_GLOBALS"}, {"kind": "macro", "line": 20, "name": "CVM_DEF_FUNCS", "signature": "#define CVM_DEF_FUNCS"}, {"kind": "macro", "line": 21, "name": "CVM_DEF_NATIVES", "signature": "#define CVM_DEF_NATIVES"}, {"kind": "macro", "line": 22, "name": "CVM_DEF_CODE", "signature": "#define CVM_DEF_CODE"}, {"kind": "macro", "line": 23, "name": "CVM_DEF_PROFILE", "signature": "#define CVM_DEF_PROFILE"}, {"kind": "macro", "line": 24, "name": "CVM_HEAP_ALIGN", "signature": "#define CVM_HEAP_ALIGN"}, {"kind": "macro", "line": 25, "name": "CVM_MAX_NARGS", "signature": "#define CVM_MAX_NARGS"}, {"kind": "macro", "line": 26, "name": "CVM_MAX_SARGS", "signature": "#define CVM_MAX_SARGS"}]}, {"id": "cvm2/cvm.h", "kind": "module", "label": "cvm.h", "language": "h", "sha256": "97f01f56a02461b1", "symbol_count": 56, "symbols": [{"kind": "struct", "line": 154, "name": "CvmFuncEntry"}, {"kind": "struct", "line": 162, "name": "CvmGlobalEntry"}, {"kind": "struct", "line": 167, "name": "CvmNativeEntry"}, {"kind": "struct", "line": 171, "name": "CvmStringEntry"}, {"kind": "struct", "line": 176, "name": "CvmConfig"}, {"kind": "struct", "line": 189, "name": "CvmFrame"}, {"kind": "struct", "line": 198, "name": "CvmNative"}, {"kind": "struct", "line": 205, "name": "CvmBreakpoint"}, {"kind": "struct", "line": 209, "name": "CvmState"}, {"kind": "function", "line": 247, "name": "cvm_create", "signature": "CvmState *cvm_create(const CvmConfig *config);"}, {"kind": "function", "line": 248, "name": "cvm_destroy", "signature": "void cvm_destroy(CvmState *vm);"}, {"kind": "function", "line": 249, "name": "cvm_load_module", "signature": "int cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);"}, {"kind": "function", "line": 250, "name": "cvm_load_module_file", "signature": "int cvm_load_module_file(CvmState *vm, const char *path);"}, {"kind": "function", "line": 251, "name": "cvm_run", "signature": "int cvm_run(CvmState *vm);"}, {"kind": "function", "line": 252, "name": "cvm_continue", "signature": "int cvm_continue(CvmState *vm);"}, {"kind": "function", "line": 253, "name": "cvm_step", "signature": "int cvm_step(CvmState *vm);"}, {"kind": "function", "line": 254, "name": "cvm_exit_code", "signature": "int64_t cvm_exit_code(const CvmState *vm);"}, {"kind": "function", "line": 255, "name": "cvm_instruction_count", "signature": "uint64_t cvm_instruction_count(const CvmState *vm);"}, {"kind": "function", "line": 256, "name": "cvm_strerror", "signature": "const char *cvm_strerror(int error_code);"}, {"kind": "function", "line": 258, "name": "cvm_register_native", "signature": "int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn);"}, {"kind": "function", "line": 259, "name": "cvm_set_args", "signature": "int cvm_set_args(CvmState *vm, int argc, char **argv);"}, {"kind": "function", "line": 260, "name": "cvm_heap_alloc", "signature": "void *cvm_heap_alloc(CvmState *vm, size_t size);"}, {"kind": "function", "line": 262, "name": "cvm_break_set", "signature": "int cvm_break_set(CvmState *vm, size_t ip);"}, {"kind": "function", "line": 263, "name": "cvm_break_clear", "signature": "int cvm_break_clear(CvmState *vm, size_t ip);"}, {"kind": "function", "line": 264, "name": "cvm_break_clear_all", "signature": "void cvm_break_clear_all(CvmState *vm);"}, {"kind": "function", "line": 265, "name": "cvm_break_hit", "signature": "int cvm_break_hit(const CvmState *vm);"}, {"kind": "function", "line": 266, "name": "cvm_profile_begin", "signature": "int cvm_profile_begin(CvmState *vm);"}, {"kind": "function", "line": 267, "name": "cvm_profile_end", "signature": "void cvm_profile_end(CvmState *vm);"}, {"doc": "ifdef __cplusplus", "kind": "variable", "line": 38, "name": "CvmOpcode", "signature": "extern \"C\" { #endif #define CVM_MAGIC_0 0x43 #define CVM_MAGIC_1 0x56 #define CVM_MAGIC_2 0x4D #define CVM_MAGIC_3 0x04 #define CVM_VERSION_MAJOR 1 #define CVM_VERSION_MINOR 0 #define CVM_MODULE_HEADE"}, {"kind": "macro", "line": 28, "name": "CVM_H", "signature": "#define CVM_H"}, {"kind": "macro", "line": 41, "name": "CVM_MAGIC_0", "signature": "#define CVM_MAGIC_0"}, {"kind": "macro", "line": 42, "name": "CVM_MAGIC_1", "signature": "#define CVM_MAGIC_1"}, {"kind": "macro", "line": 43, "name": "CVM_MAGIC_2", "signature": "#define CVM_MAGIC_2"}, {"kind": "macro", "line": 44, "name": "CVM_MAGIC_3", "signature": "#define CVM_MAGIC_3"}, {"kind": "macro", "line": 45, "name": "CVM_VERSION_MAJOR", "signature": "#define CVM_VERSION_MAJOR"}, {"kind": "macro", "line": 46, "name": "CVM_VERSION_MINOR", "signature": "#define CVM_VERSION_MINOR"}, {"kind": "macro", "line": 47, "name": "CVM_MODULE_HEADER_SIZE", "signature": "#define CVM_MODULE_HEADER_SIZE"}, {"kind": "macro", "line": 48, "name": "CVM_FUNC_ENTRY_SIZE", "signature": "#define CVM_FUNC_ENTRY_SIZE"}, {"kind": "macro", "line": 49, "name": "CVM_GLOBAL_ENTRY_SIZE", "signature": "#define CVM_GLOBAL_ENTRY_SIZE"}, {"kind": "macro", "line": 50, "name": "CVM_NATIVE_ENTRY_SIZE", "signature": "#define CVM_NATIVE_ENTRY_SIZE"}, {"kind": "macro", "line": 51, "name": "CVM_STRING_ENTRY_SIZE", "signature": "#define CVM_STRING_ENTRY_SIZE"}, {"kind": "macro", "line": 53, "name": "CVM_MAX_NARGS", "signature": "#define CVM_MAX_NARGS"}, {"kind": "macro", "line": 54, "name": "CVM_MAX_SARGS", "signature": "#define CVM_MAX_SARGS"}, {"kind": "macro", "line": 55, "name": "CVM_SHIFT_MASK", "signature": "#define CVM_SHIFT_MASK"}, {"kind": "macro", "line": 56, "name": "CVM_SYS_READ", "signature": "#define CVM_SYS_READ"}, {"kind": "macro", "line": 57, "name": "CVM_SYS_WRITE", "signature": "#define CVM_SYS_WRITE"}, {"kind": "macro", "line": 58, "name": "CVM_SYS_EXIT", "signature": "#define CVM_SYS_EXIT"}, {"kind": "macro", "line": 60, "name": "CVM_DATA_ARGC", "signature": "#define CVM_DATA_ARGC"}, {"kind": "macro", "line": 61, "name": "CVM_DATA_ARGV", "signature": "#define CVM_DATA_ARGV"}, {"kind": "macro", "line": 62, "name": "CVM_DATA_RSP", "signature": "#define CVM_DATA_RSP"}, {"kind": "macro", "line": 63, "name": "CVM_DATA_RBP", "signature": "#define CVM_DATA_RBP"}, {"kind": "macro", "line": 64, "name": "CVM_DATA_ARGS", "signature": "#define CVM_DATA_ARGS"}, {"kind": "macro", "line": 65, "name": "CVM_DATA_RET", "signature": "#define CVM_DATA_RET"}, {"kind": "macro", "line": 66, "name": "CVM_DATA_STACK_SIZE", "signature": "#define CVM_DATA_STACK_SIZE"}, {"kind": "macro", "line": 70, "name": "CVM_DATA_STACK_BASE", "signature": "#define CVM_DATA_STACK_BASE"}, {"kind": "macro", "line": 203, "name": "CVM_MAX_BREAKPOINTS", "signature": "#define CVM_MAX_BREAKPOINTS"}]}, {"id": "cvm2/cvm_dbg_main.c", "kind": "module", "label": "cvm_dbg_main.c", "language": "c", "sha256": "854fe3897adcb2f2", "symbol_count": 21, "symbols": [{"kind": "function", "line": 29, "name": "emit_stdout", "signature": "static int emit_stdout(void *ctx, const char *line)"}, {"kind": "function", "line": 36, "name": "func_display", "signature": "static const char *func_display(uint32_t fi, char *fb, size_t cap)"}, {"kind": "function", "line": 40, "name": "func_of_ip", "signature": "static int func_of_ip(size_t ip)"}, {"kind": "function", "line": 51, "name": "parse_u32", "signature": "static int parse_u32(const char *s, uint32_t *out)"}, {"kind": "function", "line": 59, "name": "report_run", "signature": "static void report_run(int rc)"}, {"kind": "function", "line": 71, "name": "cmd_list", "signature": "static void cmd_list(char *arg)"}, {"kind": "function", "line": 98, "name": "cmd_break", "signature": "static void cmd_break(char *arg)"}, {"kind": "function", "line": 133, "name": "cmd_delete", "signature": "static void cmd_delete(char *arg)"}, {"kind": "function", "line": 152, "name": "cmd_step", "signature": "static void cmd_step(void)"}, {"kind": "function", "line": 166, "name": "cmd_next", "signature": "static void cmd_next(void)"}, {"kind": "function", "line": 184, "name": "cmd_run", "signature": "static void cmd_run(void)"}, {"kind": "function", "line": 194, "name": "cmd_bt", "signature": "static void cmd_bt(void)"}, {"kind": "function", "line": 206, "name": "cmd_stack", "signature": "static void cmd_stack(void)"}, {"kind": "function", "line": 213, "name": "cmd_locals", "signature": "static void cmd_locals(void)"}, {"kind": "function", "line": 225, "name": "cmd_info", "signature": "static void cmd_info(void)"}, {"kind": "function", "line": 241, "name": "cmd_profile", "signature": "static void cmd_profile(char *arg)"}, {"kind": "function", "line": 304, "name": "cmd_help", "signature": "static void cmd_help(void)"}, {"kind": "function", "line": 310, "name": "dispatch", "signature": "static void dispatch(char *line)"}, {"kind": "function", "line": 337, "name": "main", "signature": "int main(int argc, char **argv)"}, {"kind": "macro", "line": 18, "name": "DBG_LINE_MAX", "signature": "#define DBG_LINE_MAX"}, {"kind": "macro", "line": 19, "name": "DBG_PROFILE_TOP", "signature": "#define DBG_PROFILE_TOP"}]}, {"id": "cvm2/cvm_dis.c", "kind": "module", "label": "cvm_dis.c", "language": "c", "sha256": "f850b91583d6d1e7", "symbol_count": 9, "symbols": [{"kind": "function", "line": 13, "name": "putc_str", "signature": "static void putc_str(char *buf, size_t cap, size_t *n, char c)"}, {"kind": "function", "line": 17, "name": "puts_str", "signature": "static void puts_str(char *buf, size_t cap, size_t *n, const char *s)"}, {"kind": "function", "line": 21, "name": "put_hex", "signature": "static void put_hex(char *buf, size_t cap, size_t *n, uint64_t v, int digits)"}, {"kind": "function", "line": 35, "name": "put_dec", "signature": "static void put_dec(char *buf, size_t cap, size_t *n, int64_t v)"}, {"kind": "function", "line": 49, "name": "pad_name", "signature": "static void pad_name(char *buf, size_t cap, size_t *n, const char *name)"}, {"kind": "function", "line": 56, "name": "cvm_dis_line", "signature": "int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end,\n                 char *buf, size..."}, {"kind": "function", "line": 153, "name": "cvm_dis_function", "signature": "int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end,\n                     CvmDi..."}, {"kind": "function", "line": 173, "name": "cvm_dis_module", "signature": "int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx)"}, {"kind": "macro", "line": 11, "name": "CVM_DIS_LINE_MAX", "signature": "#define CVM_DIS_LINE_MAX"}]}, {"id": "cvm2/cvm_dis.h", "kind": "module", "label": "cvm_dis.h", "language": "h", "sha256": "5c9738ed1e9dd3d7", "symbol_count": 4, "symbols": [{"doc": "#ifndef CVM_DIS_H #define CVM_DIS_H #include <stddef.h> #include <stdint.h> #include \"cvm_view.h\" #ifdef __cplusplus extern \"C\" { #endif typedef int (*CvmDisEmit)(void *ctx, const char *line); /* Whole module: header summary plus every function region.", "kind": "function", "line": 23, "name": "cvm_dis_module", "signature": "int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx);"}, {"doc": "#include <stddef.h> #include <stdint.h> #include \"cvm_view.h\" #ifdef __cplusplus extern \"C\" { #endif typedef int (*CvmDisEmit)(void *ctx, const char *line); /* Whole module: header summary plus every function region. int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx); /* One function region from begin up to end.", "kind": "function", "line": 26, "name": "cvm_dis_function", "signature": "int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end, CvmDisEmit emit, void *ctx);"}, {"doc": "One instruction at code offset off (within [begin,end)). Returns the * instruction size, or -1 when it does not decode inside the region.", "kind": "function", "line": 31, "name": "cvm_dis_line", "signature": "int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end, char *buf, size_t cap);"}, {"kind": "macro", "line": 10, "name": "CVM_DIS_H", "signature": "#define CVM_DIS_H"}]}, {"id": "cvm2/cvm_dis_main.c", "kind": "module", "label": "cvm_dis_main.c", "language": "c", "sha256": "72eb7d1976abe984", "symbol_count": 2, "symbols": [{"kind": "function", "line": 11, "name": "print_line", "signature": "static int print_line(void *ctx, const char *line)"}, {"kind": "function", "line": 18, "name": "main", "signature": "int main(int argc, char **argv)"}]}, {"id": "cvm2/cvm_jit.c", "kind": "module", "label": "cvm_jit.c", "language": "c", "sha256": "8df3f204e8f72b00", "symbol_count": 37, "symbols": [{"kind": "struct", "line": 288, "name": "JitCtx"}, {"kind": "function", "line": 36, "name": "cvm_jit_create", "signature": "CvmJitState *cvm_jit_create(void)"}, {"kind": "function", "line": 48, "name": "cvm_jit_destroy", "signature": "void cvm_jit_destroy(CvmJitState *jit)"}, {"kind": "function", "line": 58, "name": "ip_map_clear", "signature": "static void ip_map_clear(CvmJitState *jit)"}, {"kind": "function", "line": 62, "name": "ip_map_add", "signature": "static void ip_map_add(CvmJitState *jit, size_t bc_ip, size_t native_off)"}, {"kind": "function", "line": 69, "name": "ip_map_lookup", "signature": "static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip)"}, {"kind": "function", "line": 81, "name": "func_cache_find", "signature": "static JitFuncEntry *func_cache_find(CvmJitState *jit, uint32_t func_idx)"}, {"kind": "function", "line": 88, "name": "func_cache_add", "signature": "static JitFuncEntry *func_cache_add(CvmJitState *jit, uint32_t func_idx,\n                        ..."}, {"kind": "function", "line": 105, "name": "opcode_total_size", "signature": "static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip)"}, {"doc": "/* ------------------------------------------------------------------ static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip) { if (ip >= code_size) return 0; const CvmOpInfo *info = cvm_op_info(code[ip]); if (!info) return 1; return info->size; } /* ------------------------------------------------------------------ /*  Emit helpers: operand stack operations /* ------------------------------------------------------------------ /* Push rax onto the operand stack: slots[sp] = rax; sp++", "kind": "function", "line": 117, "name": "emit_stack_push", "signature": "static void emit_stack_push(JitBuf *b)"}, {"doc": "} /* ------------------------------------------------------------------ /*  Emit helpers: operand stack operations /* ------------------------------------------------------------------ /* Push rax onto the operand stack: slots[sp] = rax; sp++ static void emit_stack_push(JitBuf *b) { /* mov [r12 + r13*8], rax; inc r13 emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1); emit_inc_reg(b, JIT_REG_SP); } /* Pop from operand stack into rax: sp--; rax = slots[sp]", "kind": "function", "line": 124, "name": "emit_stack_pop", "signature": "static void emit_stack_pop(JitBuf *b)"}, {"doc": "/* Push rax onto the operand stack: slots[sp] = rax; sp++ static void emit_stack_push(JitBuf *b) { /* mov [r12 + r13*8], rax; inc r13 emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1); emit_inc_reg(b, JIT_REG_SP); } /* Pop from operand stack into rax: sp--; rax = slots[sp] static void emit_stack_pop(JitBuf *b) { emit_dec_reg(b, JIT_REG_SP); emit_mov_reg_sib(b, JIT_SCRATCH1, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Pop from operand stack into dst", "kind": "function", "line": 130, "name": "emit_stack_pop_into", "signature": "static void emit_stack_pop_into(JitBuf *b, int dst)"}, {"doc": "/* Pop from operand stack into rax: sp--; rax = slots[sp] static void emit_stack_pop(JitBuf *b) { emit_dec_reg(b, JIT_REG_SP); emit_mov_reg_sib(b, JIT_SCRATCH1, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Pop from operand stack into dst static void emit_stack_pop_into(JitBuf *b, int dst) { emit_dec_reg(b, JIT_REG_SP); emit_mov_reg_sib(b, dst, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Push a register onto the operand stack", "kind": "function", "line": 136, "name": "emit_stack_push_reg", "signature": "static void emit_stack_push_reg(JitBuf *b, int reg)"}, {"doc": "emit_mov_reg_sib(b, dst, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Push a register onto the operand stack static void emit_stack_push_reg(JitBuf *b, int reg) { emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, reg); emit_inc_reg(b, JIT_REG_SP); } /* ------------------------------------------------------------------ /*  Emit helpers: C function calls /* ------------------------------------------------------------------ /* Call a C function with 1 arg (rdi).  Clobbers rax, rcx, rdx, rsi, rdi, r8-r11.", "kind": "function", "line": 146, "name": "emit_call1", "signature": "static void emit_call1(JitBuf *b, void *fn, int arg)"}, {"doc": "emit_inc_reg(b, JIT_REG_SP); } /* ------------------------------------------------------------------ /*  Emit helpers: C function calls /* ------------------------------------------------------------------ /* Call a C function with 1 arg (rdi).  Clobbers rax, rcx, rdx, rsi, rdi, r8-r11. static void emit_call1(JitBuf *b, void *fn, int arg) { if (arg != XDI) emit_mov_reg_reg(b, XDI, arg); emit_call_abs(b, fn, X10); } /* Call a C function with 2 args (rdi, rsi).", "kind": "function", "line": 152, "name": "emit_call2", "signature": "static void emit_call2(JitBuf *b, void *fn, int a1, int a2)"}, {"doc": "/* Call a C function with 1 arg (rdi).  Clobbers rax, rcx, rdx, rsi, rdi, r8-r11. static void emit_call1(JitBuf *b, void *fn, int arg) { if (arg != XDI) emit_mov_reg_reg(b, XDI, arg); emit_call_abs(b, fn, X10); } /* Call a C function with 2 args (rdi, rsi). static void emit_call2(JitBuf *b, void *fn, int a1, int a2) { if (a1 != XDI) emit_mov_reg_reg(b, XDI, a1); if (a2 != XSI) emit_mov_reg_reg(b, XSI, a2); emit_call_abs(b, fn, X10); } /* Call a C function with 3 args (rdi, rsi, rdx).", "kind": "function", "line": 159, "name": "emit_call3", "signature": "static void emit_call3(JitBuf *b, void *fn, int a1, int a2, int a3)"}, {"kind": "function", "line": 170, "name": "emit_prologue", "signature": "static void emit_prologue(JitBuf *b)"}, {"kind": "function", "line": 232, "name": "emit_epilogue", "signature": "static void emit_epilogue(JitBuf *b)"}, {"doc": "emit_pop(b, JIT_REG_SP);      /* r13 emit_pop(b, JIT_REG_SLOTS);   /* r12 emit_pop(b, JIT_REG_FRAME);   /* rbx emit_pop(b, XBP);             /* rbp /* xor eax, eax (return 0) emit_xor_reg_self(b, XAX); emit_ret(b); } /* ------------------------------------------------------------------ /*  Emit: save/restore VM state (for C calls) /* ------------------------------------------------------------------ /* Save vm->sp from r13 back to vm (before calling a C helper).", "kind": "function", "line": 252, "name": "emit_save_sp", "signature": "static void emit_save_sp(JitBuf *b)"}, {"doc": "emit_ret(b); } /* ------------------------------------------------------------------ /*  Emit: save/restore VM state (for C calls) /* ------------------------------------------------------------------ /* Save vm->sp from r13 back to vm (before calling a C helper). static void emit_save_sp(JitBuf *b) { emit_mov32_mem_reg(b, JIT_REG_VM, (int32_t)offsetof(CvmState, sp), JIT_REG_SP); } /* Restore vm->sp into r13 (after calling a C helper).", "kind": "function", "line": 258, "name": "emit_restore_sp", "signature": "static void emit_restore_sp(JitBuf *b)"}, {"kind": "function", "line": 267, "name": "error", "signature": "* keeps executing dead code after the stop: error() -> exit() returns\n * into the middle of the f..."}, {"kind": "function", "line": 302, "name": "emit_opcode", "signature": "static int emit_opcode(JitCtx *ctx, size_t bc_ip)"}, {"kind": "function", "line": 1235, "name": "jit_apply_patches_local", "signature": "static void jit_apply_patches_local(JitBuf *b, const JitPatches *p)"}, {"kind": "function", "line": 1253, "name": "cvm_jit_compile_func", "signature": "void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx)"}, {"kind": "function", "line": 1360, "name": "cvm_jit_compile_module", "signature": "int cvm_jit_compile_module(CvmState *vm)"}, {"kind": "function", "line": 1376, "name": "cvm_jit_lookup", "signature": "void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx)"}, {"doc": "/* ------------------------------------------------------------------ void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx) { if (!vm->jit) return NULL; JitFuncEntry *e = func_cache_find(vm->jit, func_idx); if (!e) return NULL; return JIT_STATE(vm)->buf.code + e->native_offset; } /* ------------------------------------------------------------------ /*  Execution /* ------------------------------------------------------------------ /* Find which function contains vm->ip", "kind": "function", "line": 1388, "name": "find_func_for_ip", "signature": "static uint32_t find_func_for_ip(const CvmState *vm)"}, {"kind": "function", "line": 1397, "name": "cvm_jit_exec_one", "signature": "void cvm_jit_exec_one(CvmState *vm)"}, {"kind": "function", "line": 1427, "name": "cvm_jit_run", "signature": "int cvm_jit_run(CvmState *vm)"}, {"kind": "function", "line": 1488, "name": "cvm_jit_stats", "signature": "void cvm_jit_stats(const CvmState *vm)"}, {"kind": "function", "line": 1499, "name": "cvm_jit_dump", "signature": "void cvm_jit_dump(const CvmState *vm)"}, {"doc": "Fall back: interpret this function's bytecodes. We run the interpreter until ip leaves this function or * vm->running becomes 0. uint32_t start_func = func; while (vm->running) { uint32_t cur = find_func_for_ip(vm); if (cur != start_func) break;  /* left this function /* Execute one instruction via the step function", "kind": "function", "line": 1420, "name": "cvm_step", "signature": "extern int cvm_step(CvmState *);"}, {"doc": "while (vm->running) { uint32_t cur = find_func_for_ip(vm); if (cur != start_func) break;  /* left this function /* Execute one instruction via the step function extern int cvm_step(CvmState *); int rc = cvm_step(vm); if (rc) break; } } } int cvm_jit_run(CvmState *vm) { if (!vm->jit || !JIT_STATE(vm)->enabled) { /* Should not be called without JIT; fall back to interpreter", "kind": "function", "line": 1430, "name": "cvm_run", "signature": "extern int cvm_run(CvmState *);"}, {"kind": "macro", "line": 30, "name": "JIT_STATE", "signature": "#define JIT_STATE(vm)"}, {"kind": "macro", "line": 603, "name": "EMIT_CMP", "signature": "#define EMIT_CMP(cc_signed)"}, {"kind": "macro", "line": 624, "name": "EMIT_CMP_SIGNED", "signature": "#define EMIT_CMP_SIGNED(cc)"}, {"kind": "macro", "line": 636, "name": "EMIT_CMP_UNSIGNED", "signature": "#define EMIT_CMP_UNSIGNED(cc)"}]}, {"id": "cvm2/cvm_jit.h", "kind": "module", "label": "cvm_jit.h", "language": "h", "sha256": "1b5b7a03fc5ca02e", "symbol_count": 26, "symbols": [{"kind": "struct", "line": 72, "name": "JitFuncEntry"}, {"kind": "struct", "line": 84, "name": "JitIpMap"}, {"kind": "struct", "line": 96, "name": "CvmJitState"}, {"doc": "/* IP-to-native mapping (shared across all functions) JitIpMap        ip_map[JIT_IP_MAP_SIZE]; size_t          ip_map_count; /* Profile counters for tier-up uint32_t        hot_threshold;          /* tier-up threshold uint32_t        warm_threshold;         /* tier-1 threshold } CvmJitState; /* ------------------------------------------------------------------ /*  JIT lifecycle /* ------------------------------------------------------------------ /* Create JIT state.  Call after cvm_create().", "kind": "function", "line": 120, "name": "cvm_jit_create", "signature": "CvmJitState *cvm_jit_create(void);"}, {"doc": "/* Profile counters for tier-up uint32_t        hot_threshold;          /* tier-up threshold uint32_t        warm_threshold;         /* tier-1 threshold } CvmJitState; /* ------------------------------------------------------------------ /*  JIT lifecycle /* ------------------------------------------------------------------ /* Create JIT state.  Call after cvm_create(). CvmJitState *cvm_jit_create(void); /* Destroy JIT state.  Call before cvm_destroy().", "kind": "function", "line": 123, "name": "cvm_jit_destroy", "signature": "void cvm_jit_destroy(CvmJitState *jit);"}, {"doc": "Compile all functions in a loaded module to native code. * Returns CVM_OK on success.", "kind": "function", "line": 127, "name": "cvm_jit_compile_module", "signature": "int cvm_jit_compile_module(CvmState *vm);"}, {"doc": "Compile all functions in a loaded module to native code. * Returns CVM_OK on success. int cvm_jit_compile_module(CvmState *vm); /* Compile a single function.  Returns pointer to native code, or NULL.", "kind": "function", "line": 130, "name": "cvm_jit_compile_func", "signature": "void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx);"}, {"doc": "Compile all functions in a loaded module to native code. * Returns CVM_OK on success. int cvm_jit_compile_module(CvmState *vm); /* Compile a single function.  Returns pointer to native code, or NULL. void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx); /* Look up native code for a function.  Returns pointer or NULL.", "kind": "function", "line": 133, "name": "cvm_jit_lookup", "signature": "void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx);"}, {"doc": "Execute using the JIT.  Compiles all functions first, then dispatches to compiled code.  Falls back to interpreter for uncompiled functions. * Returns CVM_OK on success.", "kind": "function", "line": 142, "name": "cvm_jit_run", "signature": "int cvm_jit_run(CvmState *vm);"}, {"kind": "function", "line": 145, "name": "returns", "signature": "* returns (via RET) or encounters an error. */ void cvm_jit_exec_one(CvmState *vm);"}, {"doc": "Execute one compiled function at vm->ip.  Returns when the function * returns (via RET) or encounters an error. void cvm_jit_exec_one(CvmState *vm); /* ------------------------------------------------------------------ /*  Statistics /* ------------------------------------------------------------------ /* Print JIT compilation statistics to stderr.", "kind": "function", "line": 153, "name": "cvm_jit_stats", "signature": "void cvm_jit_stats(const CvmState *vm);"}, {"doc": "returns (via RET) or encounters an error. void cvm_jit_exec_one(CvmState *vm); /* ------------------------------------------------------------------ /*  Statistics /* ------------------------------------------------------------------ /* Print JIT compilation statistics to stderr. void cvm_jit_stats(const CvmState *vm); #ifdef __cplusplus } #endif #endif /* CVM_JIT_H", "kind": "function", "line": 159, "name": "cvm_jit_dump", "signature": "void cvm_jit_dump(const CvmState *vm);"}, {"doc": "ifdef __cplusplus", "kind": "variable", "line": 22, "name": "JitTier", "signature": "extern \"C\" { #endif /* ------------------------------------------------------------------ */ /* Register assignment for JIT-compiled code */ /* --------------------------------------------------------"}, {"kind": "macro", "line": 15, "name": "CVM_JIT_H", "signature": "#define CVM_JIT_H"}, {"kind": "macro", "line": 45, "name": "JIT_REG_VM", "signature": "#define JIT_REG_VM"}, {"kind": "macro", "line": 46, "name": "JIT_REG_SLOTS", "signature": "#define JIT_REG_SLOTS"}, {"kind": "macro", "line": 47, "name": "JIT_REG_SP", "signature": "#define JIT_REG_SP"}, {"kind": "macro", "line": 48, "name": "JIT_REG_FRAMES", "signature": "#define JIT_REG_FRAMES"}, {"kind": "macro", "line": 49, "name": "JIT_REG_FRAME", "signature": "#define JIT_REG_FRAME"}, {"kind": "macro", "line": 52, "name": "JIT_SCRATCH1", "signature": "#define JIT_SCRATCH1"}, {"kind": "macro", "line": 53, "name": "JIT_SCRATCH2", "signature": "#define JIT_SCRATCH2"}, {"kind": "macro", "line": 54, "name": "JIT_SCRATCH3", "signature": "#define JIT_SCRATCH3"}, {"kind": "macro", "line": 55, "name": "JIT_SCRATCH4", "signature": "#define JIT_SCRATCH4"}, {"kind": "macro", "line": 56, "name": "JIT_SCRATCH5", "signature": "#define JIT_SCRATCH5"}, {"kind": "macro", "line": 93, "name": "JIT_MAX_FUNCS", "signature": "#define JIT_MAX_FUNCS"}, {"kind": "macro", "line": 94, "name": "JIT_IP_MAP_SIZE", "signature": "#define JIT_IP_MAP_SIZE"}]}, {"id": "cvm2/cvm_jit_help.c", "kind": "module", "label": "cvm_jit_help.c", "language": "c", "sha256": "e888df408951aa97", "symbol_count": 22, "symbols": [{"kind": "function", "line": 22, "name": "cvm_jit_offsets_init", "signature": "void cvm_jit_offsets_init(CvmJitOffsets *o)"}, {"kind": "function", "line": 46, "name": "xmal", "signature": "static void *xmal(size_t s)"}, {"kind": "function", "line": 52, "name": "xcal", "signature": "static void *xcal(size_t n, size_t s)"}, {"kind": "function", "line": 58, "name": "push_frame", "signature": "static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,\n                      ..."}, {"kind": "function", "line": 71, "name": "pop_frame", "signature": "static void pop_frame(CvmState *vm)"}, {"kind": "function", "line": 78, "name": "cur_frame", "signature": "static CvmFrame *cur_frame(CvmState *vm)"}, {"kind": "function", "line": 82, "name": "range_valid", "signature": "static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)"}, {"kind": "function", "line": 90, "name": "mem_valid", "signature": "static int mem_valid(const CvmState *vm, uint64_t a, size_t s)"}, {"kind": "function", "line": 102, "name": "heap_alloc", "signature": "static uint64_t heap_alloc(CvmState *vm, size_t s)"}, {"kind": "function", "line": 110, "name": "find_native", "signature": "static int find_native(const CvmState *vm, const char *name)"}, {"kind": "function", "line": 120, "name": "jit_vp", "signature": "static int jit_vp(CvmState *vm, uint64_t v)"}, {"kind": "function", "line": 126, "name": "jit_vo", "signature": "static int jit_vo(CvmState *vm, uint64_t *v)"}, {"kind": "function", "line": 136, "name": "cvm_jit_func_enter", "signature": "uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx)"}, {"kind": "function", "line": 145, "name": "cvm_jit_func_leave", "signature": "void cvm_jit_func_leave(CvmState *vm)"}, {"kind": "function", "line": 155, "name": "cvm_jit_call", "signature": "int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc)"}, {"kind": "function", "line": 176, "name": "cvm_jit_ret", "signature": "int cvm_jit_ret(CvmState *vm, uint64_t retval)"}, {"kind": "function", "line": 193, "name": "cvm_jit_call_native", "signature": "int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc)"}, {"kind": "function", "line": 213, "name": "cvm_jit_memcheck", "signature": "int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size)"}, {"kind": "function", "line": 221, "name": "cvm_jit_alloc", "signature": "uint64_t cvm_jit_alloc(CvmState *vm, size_t size)"}, {"kind": "function", "line": 229, "name": "cvm_jit_syscall", "signature": "int cvm_jit_syscall(CvmState *vm, uint8_t sn, uint8_t argc)"}, {"kind": "function", "line": 256, "name": "cvm_jit_error", "signature": "void cvm_jit_error(CvmState *vm, int error_code)"}, {"kind": "macro", "line": 16, "name": "CVM_HEAP_ALIGN", "signature": "#define CVM_HEAP_ALIGN"}]}, {"id": "cvm2/cvm_jit_help.h", "kind": "module", "label": "cvm_jit_help.h", "language": "h", "sha256": "6b8fc7ac79c22296", "symbol_count": 13, "symbols": [{"doc": "Register offsets into CvmState, used by JIT-compiled code for * direct field access.  These are computed once at JIT init time.", "kind": "struct", "line": 22, "name": "CvmJitOffsets"}, {"doc": "Compute and cache all field offsets.  Must be called once before * any JIT compilation begins.", "kind": "function", "line": 44, "name": "cvm_jit_offsets_init", "signature": "void cvm_jit_offsets_init(CvmJitOffsets *off);"}, {"doc": "Called at JIT function entry to sync interpreter state. * Returns the code pointer for the function.", "kind": "function", "line": 52, "name": "cvm_jit_func_enter", "signature": "uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx);"}, {"doc": "Called at JIT function entry to sync interpreter state. * Returns the code pointer for the function. uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx); /* Called at JIT function exit to sync interpreter state back.", "kind": "function", "line": 55, "name": "cvm_jit_func_leave", "signature": "void cvm_jit_func_leave(CvmState *vm);"}, {"doc": "Execute OP_CALL: push a new frame, copy arguments from the operand stack into the new frame's locals, and set vm->ip to the callee. Returns 0 on success, non-zero error code on failure. On success, the JIT must jump to vm->ip (the callee's code). * On failure, vm->running is set to 0 and vm->exit_code is set.", "kind": "function", "line": 66, "name": "cvm_jit_call", "signature": "int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc);"}, {"kind": "function", "line": 70, "name": "to", "signature": "* Returns 0 if there is a caller to return to (vm->ip is set). * Returns 1 if this was the entry frame (vm->running = 0, done). */ int cvm_jit_ret(CvmState *vm, uint64_t retval);"}, {"doc": "Execute OP_CALL_NATIVE: resolve the native function by index, pop arguments from the operand stack, call the host function, * and push the result.  Returns 0 on success.", "kind": "function", "line": 77, "name": "cvm_jit_call_native", "signature": "int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc);"}, {"kind": "function", "line": 84, "name": "region", "signature": "* region (heap, globals, string pool, or any frame's locals). * Returns 1 if valid, 0 if invalid. */ int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size);"}, {"doc": "Bump-allocate 'size' bytes from the CVM heap. * Returns the heap pointer on success, 0 on exhaustion.", "kind": "function", "line": 94, "name": "cvm_jit_alloc", "signature": "uint64_t cvm_jit_alloc(CvmState *vm, size_t size);"}, {"doc": "Execute a Linux-style syscall.  Pops 'argc' arguments from the operand stack, dispatches by syscall number, and pushes the result. * Returns 0 on success.  On exit syscall, vm->running is set to 0.", "kind": "function", "line": 103, "name": "cvm_jit_syscall", "signature": "int cvm_jit_syscall(CvmState *vm, uint8_t syscall_nr, uint8_t argc);"}, {"doc": "Set an error code and terminate the VM.  This is called when a JIT-compiled function detects an unrecoverable error (bad address, * stack overflow, etc.).  Sets vm->running = 0 and vm->exit_code.", "kind": "function", "line": 112, "name": "cvm_jit_error", "signature": "void cvm_jit_error(CvmState *vm, int error_code);"}, {"doc": "ifdef __cplusplus", "kind": "variable", "line": 17, "name": "slots", "signature": "extern \"C\" { #endif /* Register offsets into CvmState, used by JIT-compiled code for * direct field access. These are computed once at JIT init time. */ typedef struct { size_t slots;"}, {"kind": "macro", "line": 12, "name": "CVM_JIT_HELP_H", "signature": "#define CVM_JIT_HELP_H"}]}, {"id": "cvm2/cvm_jit_x86.c", "kind": "module", "label": "cvm_jit_x86.c", "language": "c", "sha256": "e36a0984bf6ea53b", "symbol_count": 73, "symbols": [{"kind": "function", "line": 35, "name": "jit_buf_init", "signature": "void jit_buf_init(JitBuf *b, size_t cap)"}, {"kind": "function", "line": 48, "name": "jit_buf_free", "signature": "void jit_buf_free(JitBuf *b)"}, {"kind": "function", "line": 56, "name": "jit_buf_reset", "signature": "void jit_buf_reset(JitBuf *b)"}, {"kind": "function", "line": 61, "name": "jit_buf_failed", "signature": "int jit_buf_failed(const JitBuf *b)"}, {"kind": "function", "line": 67, "name": "emit_grow", "signature": "static void emit_grow(JitBuf *b, size_t need)"}, {"kind": "function", "line": 84, "name": "emit8", "signature": "void emit8(JitBuf *b, uint8_t v)"}, {"kind": "function", "line": 89, "name": "emit16", "signature": "void emit16(JitBuf *b, uint16_t v)"}, {"kind": "function", "line": 94, "name": "emit32", "signature": "void emit32(JitBuf *b, uint32_t v)"}, {"kind": "function", "line": 99, "name": "emit64", "signature": "void emit64(JitBuf *b, uint64_t v)"}, {"kind": "function", "line": 104, "name": "emit_bytes", "signature": "void emit_bytes(JitBuf *b, const void *data, size_t len)"}, {"doc": "emit_grow(b, 8); if (!b->failed) { memcpy(b->code + b->size, &v, 8); b->size += 8; } } void emit_bytes(JitBuf *b, const void *data, size_t len) { emit_grow(b, len); if (!b->failed) { memcpy(b->code + b->size, data, len); b->size += len; } } /* ------------------------------------------------------------------ /*  Internal encoding helpers /* ------------------------------------------------------------------ /* REX prefix: 0100 WRXB", "kind": "function", "line": 114, "name": "emit_rex", "signature": "void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b)"}, {"doc": "emit_grow(b, len); if (!b->failed) { memcpy(b->code + b->size, data, len); b->size += len; } } /* ------------------------------------------------------------------ /*  Internal encoding helpers /* ------------------------------------------------------------------ /* REX prefix: 0100 WRXB void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b) { emit8(buf, (uint8_t)(0x40 | (w << 3) | (r << 2) | (x << 1) | rex_b)); } /* ModRM byte", "kind": "function", "line": 119, "name": "emit_modrm", "signature": "void emit_modrm(JitBuf *b, int mod, int reg, int rm)"}, {"doc": "/*  Internal encoding helpers /* ------------------------------------------------------------------ /* REX prefix: 0100 WRXB void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b) { emit8(buf, (uint8_t)(0x40 | (w << 3) | (r << 2) | (x << 1) | rex_b)); } /* ModRM byte void emit_modrm(JitBuf *b, int mod, int reg, int rm) { emit8(b, (uint8_t)((mod << 6) | ((reg & 7) << 3) | (rm & 7))); } /* ModRM + disp32", "kind": "function", "line": 124, "name": "emit_modrm_disp32", "signature": "static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp)"}, {"doc": "} /* ModRM byte void emit_modrm(JitBuf *b, int mod, int reg, int rm) { emit8(b, (uint8_t)((mod << 6) | ((reg & 7) << 3) | (rm & 7))); } /* ModRM + disp32 static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp) { emit_modrm(b, 2, reg, rm); emit32(b, (uint32_t)disp); } /* REX.W + opcode + ModRM(reg, r/m) -- 3-byte core for reg,reg ops", "kind": "function", "line": 130, "name": "emit_rex_op_modrm", "signature": "static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm)"}, {"doc": "/* ModRM + disp32 static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp) { emit_modrm(b, 2, reg, rm); emit32(b, (uint32_t)disp); } /* REX.W + opcode + ModRM(reg, r/m) -- 3-byte core for reg,reg ops static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm) { emit_rex(b, 1, reg_high3(reg), 0, reg_high3(rm)); emit8(b, opc); emit_modrm(b, 3, reg, rm); } /* SIB byte", "kind": "function", "line": 137, "name": "emit_sib", "signature": "static void emit_sib(JitBuf *b, int scale, int index, int base)"}, {"kind": "function", "line": 145, "name": "emit_mov_reg_imm64", "signature": "void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm)"}, {"kind": "function", "line": 152, "name": "emit_mov_reg_imm32", "signature": "void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm)"}, {"kind": "function", "line": 165, "name": "emit_mov_reg_reg", "signature": "void emit_mov_reg_reg(JitBuf *b, int dst, int src)"}, {"kind": "function", "line": 171, "name": "emit_mov_reg_mem", "signature": "void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp)"}, {"kind": "function", "line": 178, "name": "emit_mov_mem_reg", "signature": "void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src)"}, {"kind": "function", "line": 185, "name": "emit_movzx_reg_mem8", "signature": "void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp)"}, {"kind": "function", "line": 192, "name": "emit_movzx_reg_mem16", "signature": "void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp)"}, {"kind": "function", "line": 199, "name": "emit_movsx_reg_mem32", "signature": "void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp)"}, {"kind": "function", "line": 206, "name": "emit_mov32_reg_mem", "signature": "void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp)"}, {"kind": "function", "line": 214, "name": "emit_mov32_mem_reg", "signature": "void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src)"}, {"kind": "function", "line": 222, "name": "emit_lea_sib", "signature": "void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp)"}, {"kind": "function", "line": 259, "name": "emit_mov_reg_sib", "signature": "void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale)"}, {"kind": "function", "line": 267, "name": "emit_mov_sib_reg", "signature": "void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src)"}, {"kind": "function", "line": 279, "name": "emit_push", "signature": "void emit_push(JitBuf *b, int reg)"}, {"kind": "function", "line": 285, "name": "emit_pop", "signature": "void emit_pop(JitBuf *b, int reg)"}, {"kind": "function", "line": 295, "name": "emit_add_reg_reg", "signature": "void emit_add_reg_reg(JitBuf *b, int dst, int src)"}, {"kind": "function", "line": 299, "name": "emit_add_reg_imm32", "signature": "void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm)"}, {"kind": "function", "line": 308, "name": "emit_sub_reg_reg", "signature": "void emit_sub_reg_reg(JitBuf *b, int dst, int src)"}, {"kind": "function", "line": 312, "name": "emit_sub_reg_imm32", "signature": "void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm)"}, {"kind": "function", "line": 320, "name": "emit_imul_reg_reg", "signature": "void emit_imul_reg_reg(JitBuf *b, int dst, int src)"}, {"kind": "function", "line": 327, "name": "emit_idiv_reg", "signature": "void emit_idiv_reg(JitBuf *b, int divisor)"}, {"kind": "function", "line": 334, "name": "emit_div_reg", "signature": "void emit_div_reg(JitBuf *b, int divisor)"}, {"kind": "function", "line": 341, "name": "emit_cqo", "signature": "void emit_cqo(JitBuf *b)"}, {"kind": "function", "line": 347, "name": "emit_neg_reg", "signature": "void emit_neg_reg(JitBuf *b, int reg)"}, {"kind": "function", "line": 354, "name": "emit_inc_reg", "signature": "void emit_inc_reg(JitBuf *b, int reg)"}, {"kind": "function", "line": 361, "name": "emit_dec_reg", "signature": "void emit_dec_reg(JitBuf *b, int reg)"}, {"kind": "function", "line": 372, "name": "emit_and_reg_imm32", "signature": "void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm)"}, {"kind": "function", "line": 380, "name": "emit_and_reg_reg", "signature": "void emit_and_reg_reg(JitBuf *b, int dst, int src)"}, {"kind": "function", "line": 384, "name": "emit_or_reg_reg", "signature": "void emit_or_reg_reg(JitBuf *b, int dst, int src)"}, {"kind": "function", "line": 388, "name": "emit_xor_reg_reg", "signature": "void emit_xor_reg_reg(JitBuf *b, int dst, int src)"}, {"kind": "function", "line": 392, "name": "emit_not_reg", "signature": "void emit_not_reg(JitBuf *b, int reg)"}, {"kind": "function", "line": 399, "name": "emit_shl_reg_cl", "signature": "void emit_shl_reg_cl(JitBuf *b, int reg)"}, {"kind": "function", "line": 406, "name": "emit_shr_reg_cl", "signature": "void emit_shr_reg_cl(JitBuf *b, int reg)"}, {"kind": "function", "line": 413, "name": "emit_sar_reg_cl", "signature": "void emit_sar_reg_cl(JitBuf *b, int reg)"}, {"kind": "function", "line": 420, "name": "emit_xor_reg_self", "signature": "void emit_xor_reg_self(JitBuf *b, int reg)"}, {"kind": "function", "line": 430, "name": "emit_cmp_reg_reg", "signature": "void emit_cmp_reg_reg(JitBuf *buf, int a, int breg)"}, {"kind": "function", "line": 435, "name": "emit_test_reg_reg", "signature": "void emit_test_reg_reg(JitBuf *buf, int a, int breg)"}, {"kind": "function", "line": 440, "name": "emit_setcc", "signature": "void emit_setcc(JitBuf *b, int cc, int dst)"}, {"kind": "function", "line": 449, "name": "emit_movzx_reg_reg8", "signature": "void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src)"}, {"kind": "function", "line": 460, "name": "emit_jmp_rel32", "signature": "size_t emit_jmp_rel32(JitBuf *b, int32_t rel)"}, {"kind": "function", "line": 467, "name": "emit_jcc_rel32", "signature": "size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel)"}, {"kind": "function", "line": 475, "name": "emit_jmp_buf", "signature": "void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p)"}, {"kind": "function", "line": 487, "name": "emit_jcc_buf", "signature": "void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p)"}, {"kind": "function", "line": 500, "name": "jit_apply_patches", "signature": "void jit_apply_patches(JitBuf *b, const JitPatches *p)"}, {"kind": "function", "line": 512, "name": "emit_call_rel32", "signature": "size_t emit_call_rel32(JitBuf *b, int32_t rel)"}, {"kind": "function", "line": 519, "name": "emit_call_reg", "signature": "void emit_call_reg(JitBuf *b, int reg)"}, {"kind": "function", "line": 527, "name": "emit_ret", "signature": "void emit_ret(JitBuf *b)"}, {"kind": "function", "line": 535, "name": "emit_syscall", "signature": "void emit_syscall(JitBuf *b)"}, {"kind": "function", "line": 540, "name": "emit_int3", "signature": "void emit_int3(JitBuf *b)"}, {"kind": "function", "line": 544, "name": "emit_nop", "signature": "void emit_nop(JitBuf *b)"}, {"kind": "function", "line": 552, "name": "emit_call_abs", "signature": "void emit_call_abs(JitBuf *b, void *func, int scratch)"}, {"kind": "function", "line": 561, "name": "emit_mov_mem_imm8", "signature": "void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm)"}, {"kind": "function", "line": 569, "name": "emit_mov_mem_imm32", "signature": "void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm)"}, {"kind": "macro", "line": 26, "name": "JIT_BUF_ALLOC", "signature": "#define JIT_BUF_ALLOC(sz)"}, {"kind": "macro", "line": 27, "name": "JIT_BUF_FREE", "signature": "#define JIT_BUF_FREE(p, sz)"}, {"kind": "macro", "line": 29, "name": "JIT_BUF_ALLOC", "signature": "#define JIT_BUF_ALLOC(sz)"}, {"kind": "macro", "line": 31, "name": "JIT_BUF_FREE", "signature": "#define JIT_BUF_FREE(p, sz)"}, {"kind": "macro", "line": 32, "name": "JIT_BUF_FAILED", "signature": "#define JIT_BUF_FAILED"}]}, {"id": "cvm2/cvm_jit_x86.h", "kind": "module", "label": "cvm_jit_x86.h", "language": "h", "sha256": "003d21170704ec1e", "symbol_count": 71, "symbols": [{"doc": "/* Condition codes for Jcc / SETcc enum { CC_O   = 0x0, CC_NO  = 0x1, CC_B   = 0x2, CC_AE  = 0x3, CC_E   = 0x4, CC_NE  = 0x5, CC_BE  = 0x6, CC_A   = 0x7, CC_S   = 0x8, CC_NS  = 0x9, CC_P   = 0xA, CC_NP  = 0xB, CC_L   = 0xC, CC_GE  = 0xD, CC_LE  = 0xE, CC_G   = 0xF }; /* Growable code buffer backed by mmap'd RWX memory", "kind": "struct", "line": 40, "name": "JitBuf"}, {"doc": "CC_P   = 0xA, CC_NP  = 0xB, CC_L   = 0xC, CC_GE  = 0xD, CC_LE  = 0xE, CC_G   = 0xF }; /* Growable code buffer backed by mmap'd RWX memory typedef struct { uint8_t *code; size_t   size;       /* current write offset size_t   capacity;   /* allocated size int      failed;     /* set on OOM or overflow } JitBuf; /* Forward patch entry for unresolved jumps", "kind": "struct", "line": 48, "name": "JitPatch"}, {"kind": "struct", "line": 55, "name": "JitPatches"}, {"doc": "int   jit_buf_failed(const JitBuf *b); /* ------------------------------------------------------------------ /*  Byte emission (little-endian) /* ------------------------------------------------------------------ void  emit8(JitBuf *b, uint8_t v); void  emit16(JitBuf *b, uint16_t v); void  emit32(JitBuf *b, uint32_t v); void  emit64(JitBuf *b, uint64_t v); void  emit_bytes(JitBuf *b, const void *data, size_t len); /* ------------------------------------------------------------------ /*  Register checks /* ------------------------------------------------------------------", "kind": "function", "line": 80, "name": "reg_needs_rex", "signature": "static inline int reg_needs_rex(int r)"}, {"kind": "function", "line": 81, "name": "reg_high3", "signature": "static inline int reg_high3(int r)"}, {"doc": "size_t patch_off;    /* offset in buf->code where rel32 lives size_t target;       /* absolute target offset in the same buffer } JitPatch; #define JIT_MAX_PATCHES 8192 typedef struct { JitPatch patches[JIT_MAX_PATCHES]; size_t   count; } JitPatches; /* ------------------------------------------------------------------ /*  Buffer lifecycle /* ------------------------------------------------------------------", "kind": "function", "line": 63, "name": "jit_buf_init", "signature": "void jit_buf_init(JitBuf *b, size_t initial_cap);"}, {"kind": "function", "line": 64, "name": "jit_buf_free", "signature": "void jit_buf_free(JitBuf *b);"}, {"kind": "function", "line": 65, "name": "jit_buf_reset", "signature": "void jit_buf_reset(JitBuf *b);"}, {"kind": "function", "line": 66, "name": "jit_buf_failed", "signature": "int jit_buf_failed(const JitBuf *b);"}, {"doc": "size_t   count; } JitPatches; /* ------------------------------------------------------------------ /*  Buffer lifecycle /* ------------------------------------------------------------------ void  jit_buf_init(JitBuf *b, size_t initial_cap); void  jit_buf_free(JitBuf *b); void  jit_buf_reset(JitBuf *b); int   jit_buf_failed(const JitBuf *b); /* ------------------------------------------------------------------ /*  Byte emission (little-endian) /* ------------------------------------------------------------------", "kind": "function", "line": 71, "name": "emit8", "signature": "void emit8(JitBuf *b, uint8_t v);"}, {"kind": "function", "line": 72, "name": "emit16", "signature": "void emit16(JitBuf *b, uint16_t v);"}, {"kind": "function", "line": 73, "name": "emit32", "signature": "void emit32(JitBuf *b, uint32_t v);"}, {"kind": "function", "line": 74, "name": "emit64", "signature": "void emit64(JitBuf *b, uint64_t v);"}, {"kind": "function", "line": 75, "name": "emit_bytes", "signature": "void emit_bytes(JitBuf *b, const void *data, size_t len);"}, {"doc": "void  emit64(JitBuf *b, uint64_t v); void  emit_bytes(JitBuf *b, const void *data, size_t len); /* ------------------------------------------------------------------ /*  Register checks /* ------------------------------------------------------------------ static inline int reg_needs_rex(int r) { return r >= X8; } static inline int reg_high3(int r) { return (r >> 3) & 1; } /* ------------------------------------------------------------------ /*  Data movement /* ------------------------------------------------------------------ /* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64)", "kind": "function", "line": 88, "name": "emit_mov_reg_imm64", "signature": "void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm);"}, {"doc": "/* ------------------------------------------------------------------ /*  Register checks /* ------------------------------------------------------------------ static inline int reg_needs_rex(int r) { return r >= X8; } static inline int reg_high3(int r) { return (r >> 3) & 1; } /* ------------------------------------------------------------------ /*  Data movement /* ------------------------------------------------------------------ /* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64) void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm); /* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32)", "kind": "function", "line": 91, "name": "emit_mov_reg_imm32", "signature": "void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm);"}, {"doc": "static inline int reg_needs_rex(int r) { return r >= X8; } static inline int reg_high3(int r) { return (r >> 3) & 1; } /* ------------------------------------------------------------------ /*  Data movement /* ------------------------------------------------------------------ /* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64) void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm); /* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32) void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm); /* MOV r64, r64  (3 bytes: REX.W 89 /r)", "kind": "function", "line": 94, "name": "emit_mov_reg_reg", "signature": "void emit_mov_reg_reg(JitBuf *b, int dst, int src);"}, {"doc": "/* ------------------------------------------------------------------ /*  Data movement /* ------------------------------------------------------------------ /* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64) void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm); /* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32) void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm); /* MOV r64, r64  (3 bytes: REX.W 89 /r) void emit_mov_reg_reg(JitBuf *b, int dst, int src); /* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10)", "kind": "function", "line": 97, "name": "emit_mov_reg_mem", "signature": "void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp);"}, {"doc": "/* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64) void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm); /* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32) void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm); /* MOV r64, r64  (3 bytes: REX.W 89 /r) void emit_mov_reg_reg(JitBuf *b, int dst, int src); /* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10) void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp); /* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10)", "kind": "function", "line": 100, "name": "emit_mov_mem_reg", "signature": "void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src);"}, {"doc": "/* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32) void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm); /* MOV r64, r64  (3 bytes: REX.W 89 /r) void emit_mov_reg_reg(JitBuf *b, int dst, int src); /* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10) void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp); /* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10) void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src); /* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10)", "kind": "function", "line": 103, "name": "emit_movzx_reg_mem8", "signature": "void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp);"}, {"doc": "/* MOV r64, r64  (3 bytes: REX.W 89 /r) void emit_mov_reg_reg(JitBuf *b, int dst, int src); /* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10) void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp); /* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10) void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src); /* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10) void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp); /* MOVZX r64, word [base + disp32]  (4 bytes: REX.W 0F B7 /r mod=10)", "kind": "function", "line": 106, "name": "emit_movzx_reg_mem16", "signature": "void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp);"}, {"doc": "/* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10) void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp); /* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10) void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src); /* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10) void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp); /* MOVZX r64, word [base + disp32]  (4 bytes: REX.W 0F B7 /r mod=10) void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp); /* MOVSX r64, dword [base + disp32]  (4 bytes: REX.W 63 /r mod=10)", "kind": "function", "line": 109, "name": "emit_movsx_reg_mem32", "signature": "void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp);"}, {"doc": "/* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10) void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src); /* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10) void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp); /* MOVZX r64, word [base + disp32]  (4 bytes: REX.W 0F B7 /r mod=10) void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp); /* MOVSX r64, dword [base + disp32]  (4 bytes: REX.W 63 /r mod=10) void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp); /* MOV r32, [base + disp32]  (zero-extends to r64, 6 bytes: 8B /r mod=10)", "kind": "function", "line": 112, "name": "emit_mov32_reg_mem", "signature": "void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp);"}, {"doc": "/* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10) void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp); /* MOVZX r64, word [base + disp32]  (4 bytes: REX.W 0F B7 /r mod=10) void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp); /* MOVSX r64, dword [base + disp32]  (4 bytes: REX.W 63 /r mod=10) void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp); /* MOV r32, [base + disp32]  (zero-extends to r64, 6 bytes: 8B /r mod=10) void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp); /* MOV [base + disp32], r32  (6 bytes: 89 /r mod=10)", "kind": "function", "line": 115, "name": "emit_mov32_mem_reg", "signature": "void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src);"}, {"doc": "LEA r64, [base + index*scale + disp] scale: 0=1, 1=2, 2=4, 3=8 If index == -1, encodes [base + disp] only.", "kind": "function", "line": 121, "name": "emit_lea_sib", "signature": "void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp);"}, {"doc": "MOV r64, [base + index*scale]  (no displacement) scale: 0=1, 1=2, 2=4, 3=8", "kind": "function", "line": 126, "name": "emit_mov_reg_sib", "signature": "void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale);"}, {"doc": "MOV r64, [base + index*scale]  (no displacement) scale: 0=1, 1=2, 2=4, 3=8  void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale); /* MOV [base + index*scale], r64  (no displacement)", "kind": "function", "line": 129, "name": "emit_mov_sib_reg", "signature": "void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src);"}, {"doc": "MOV r64, [base + index*scale]  (no displacement) scale: 0=1, 1=2, 2=4, 3=8  void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale); /* MOV [base + index*scale], r64  (no displacement) void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src); /* ------------------------------------------------------------------ /*  Stack operations /* ------------------------------------------------------------------ /* PUSH r64 (1 or 2 bytes depending on register)", "kind": "function", "line": 136, "name": "emit_push", "signature": "void emit_push(JitBuf *b, int reg);"}, {"doc": "void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale); /* MOV [base + index*scale], r64  (no displacement) void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src); /* ------------------------------------------------------------------ /*  Stack operations /* ------------------------------------------------------------------ /* PUSH r64 (1 or 2 bytes depending on register) void emit_push(JitBuf *b, int reg); /* POP r64", "kind": "function", "line": 139, "name": "emit_pop", "signature": "void emit_pop(JitBuf *b, int reg);"}, {"doc": "/*  Stack operations /* ------------------------------------------------------------------ /* PUSH r64 (1 or 2 bytes depending on register) void emit_push(JitBuf *b, int reg); /* POP r64 void emit_pop(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Arithmetic /* ------------------------------------------------------------------ /* ADD r64, r64  (REX.W 01 /r)", "kind": "function", "line": 146, "name": "emit_add_reg_reg", "signature": "void emit_add_reg_reg(JitBuf *b, int dst, int src);"}, {"doc": "/* PUSH r64 (1 or 2 bytes depending on register) void emit_push(JitBuf *b, int reg); /* POP r64 void emit_pop(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Arithmetic /* ------------------------------------------------------------------ /* ADD r64, r64  (REX.W 01 /r) void emit_add_reg_reg(JitBuf *b, int dst, int src); /* ADD r64, imm32  (sign-extended)", "kind": "function", "line": 149, "name": "emit_add_reg_imm32", "signature": "void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm);"}, {"doc": "/* POP r64 void emit_pop(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Arithmetic /* ------------------------------------------------------------------ /* ADD r64, r64  (REX.W 01 /r) void emit_add_reg_reg(JitBuf *b, int dst, int src); /* ADD r64, imm32  (sign-extended) void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm); /* SUB r64, r64  (REX.W 29 /r)", "kind": "function", "line": 152, "name": "emit_sub_reg_reg", "signature": "void emit_sub_reg_reg(JitBuf *b, int dst, int src);"}, {"doc": "/* ------------------------------------------------------------------ /*  Arithmetic /* ------------------------------------------------------------------ /* ADD r64, r64  (REX.W 01 /r) void emit_add_reg_reg(JitBuf *b, int dst, int src); /* ADD r64, imm32  (sign-extended) void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm); /* SUB r64, r64  (REX.W 29 /r) void emit_sub_reg_reg(JitBuf *b, int dst, int src); /* SUB r64, imm32", "kind": "function", "line": 155, "name": "emit_sub_reg_imm32", "signature": "void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm);"}, {"doc": "/* ADD r64, r64  (REX.W 01 /r) void emit_add_reg_reg(JitBuf *b, int dst, int src); /* ADD r64, imm32  (sign-extended) void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm); /* SUB r64, r64  (REX.W 29 /r) void emit_sub_reg_reg(JitBuf *b, int dst, int src); /* SUB r64, imm32 void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm); /* IMUL r64, r64  (REX.W 0F AF /r)", "kind": "function", "line": 158, "name": "emit_imul_reg_reg", "signature": "void emit_imul_reg_reg(JitBuf *b, int dst, int src);"}, {"doc": "IDIV r64  (divides RDX:RAX by r64, quotient in RAX, remainder in RDX) * Requires RDX=0 before unsigned, or use CQO for signed.", "kind": "function", "line": 162, "name": "emit_idiv_reg", "signature": "void emit_idiv_reg(JitBuf *b, int divisor);"}, {"doc": "DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx).", "kind": "function", "line": 166, "name": "emit_div_reg", "signature": "void emit_div_reg(JitBuf *b, int divisor);"}, {"doc": "DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emit_div_reg(JitBuf *b, int divisor); /* CQO  (sign-extend RAX into RDX:RAX)", "kind": "function", "line": 169, "name": "emit_cqo", "signature": "void emit_cqo(JitBuf *b);"}, {"doc": "DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emit_div_reg(JitBuf *b, int divisor); /* CQO  (sign-extend RAX into RDX:RAX) void emit_cqo(JitBuf *b); /* NEG r64  (REX.W F7 /3)", "kind": "function", "line": 172, "name": "emit_neg_reg", "signature": "void emit_neg_reg(JitBuf *b, int reg);"}, {"doc": "DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emit_div_reg(JitBuf *b, int divisor); /* CQO  (sign-extend RAX into RDX:RAX) void emit_cqo(JitBuf *b); /* NEG r64  (REX.W F7 /3) void emit_neg_reg(JitBuf *b, int reg); /* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies)", "kind": "function", "line": 175, "name": "emit_inc_reg", "signature": "void emit_inc_reg(JitBuf *b, int reg);"}, {"doc": "DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emit_div_reg(JitBuf *b, int divisor); /* CQO  (sign-extend RAX into RDX:RAX) void emit_cqo(JitBuf *b); /* NEG r64  (REX.W F7 /3) void emit_neg_reg(JitBuf *b, int reg); /* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies) void emit_inc_reg(JitBuf *b, int reg); /* DEC r64", "kind": "function", "line": 178, "name": "emit_dec_reg", "signature": "void emit_dec_reg(JitBuf *b, int reg);"}, {"doc": "/* NEG r64  (REX.W F7 /3) void emit_neg_reg(JitBuf *b, int reg); /* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies) void emit_inc_reg(JitBuf *b, int reg); /* DEC r64 void emit_dec_reg(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Bitwise /* ------------------------------------------------------------------ /* AND r64, r64", "kind": "function", "line": 185, "name": "emit_and_reg_reg", "signature": "void emit_and_reg_reg(JitBuf *b, int dst, int src);"}, {"doc": "/* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies) void emit_inc_reg(JitBuf *b, int reg); /* DEC r64 void emit_dec_reg(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Bitwise /* ------------------------------------------------------------------ /* AND r64, r64 void emit_and_reg_reg(JitBuf *b, int dst, int src); /* OR r64, r64", "kind": "function", "line": 188, "name": "emit_or_reg_reg", "signature": "void emit_or_reg_reg(JitBuf *b, int dst, int src);"}, {"doc": "/* DEC r64 void emit_dec_reg(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Bitwise /* ------------------------------------------------------------------ /* AND r64, r64 void emit_and_reg_reg(JitBuf *b, int dst, int src); /* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int dst, int src); /* XOR r64, r64", "kind": "function", "line": 191, "name": "emit_xor_reg_reg", "signature": "void emit_xor_reg_reg(JitBuf *b, int dst, int src);"}, {"doc": "/* ------------------------------------------------------------------ /*  Bitwise /* ------------------------------------------------------------------ /* AND r64, r64 void emit_and_reg_reg(JitBuf *b, int dst, int src); /* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int dst, int src); /* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int dst, int src); /* NOT r64", "kind": "function", "line": 194, "name": "emit_not_reg", "signature": "void emit_not_reg(JitBuf *b, int reg);"}, {"doc": "/* AND r64, r64 void emit_and_reg_reg(JitBuf *b, int dst, int src); /* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int dst, int src); /* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int dst, int src); /* NOT r64 void emit_not_reg(JitBuf *b, int reg); /* SHL r64, CL  (shift left by CL)", "kind": "function", "line": 197, "name": "emit_shl_reg_cl", "signature": "void emit_shl_reg_cl(JitBuf *b, int reg);"}, {"doc": "/* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int dst, int src); /* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int dst, int src); /* NOT r64 void emit_not_reg(JitBuf *b, int reg); /* SHL r64, CL  (shift left by CL) void emit_shl_reg_cl(JitBuf *b, int reg); /* SHR r64, CL  (logical shift right)", "kind": "function", "line": 200, "name": "emit_shr_reg_cl", "signature": "void emit_shr_reg_cl(JitBuf *b, int reg);"}, {"doc": "/* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int dst, int src); /* NOT r64 void emit_not_reg(JitBuf *b, int reg); /* SHL r64, CL  (shift left by CL) void emit_shl_reg_cl(JitBuf *b, int reg); /* SHR r64, CL  (logical shift right) void emit_shr_reg_cl(JitBuf *b, int reg); /* SAR r64, CL  (arithmetic shift right)", "kind": "function", "line": 203, "name": "emit_sar_reg_cl", "signature": "void emit_sar_reg_cl(JitBuf *b, int reg);"}, {"doc": "/* NOT r64 void emit_not_reg(JitBuf *b, int reg); /* SHL r64, CL  (shift left by CL) void emit_shl_reg_cl(JitBuf *b, int reg); /* SHR r64, CL  (logical shift right) void emit_shr_reg_cl(JitBuf *b, int reg); /* SAR r64, CL  (arithmetic shift right) void emit_sar_reg_cl(JitBuf *b, int reg); /* XOR reg, reg (zero-idiom, 3 bytes)", "kind": "function", "line": 206, "name": "emit_xor_reg_self", "signature": "void emit_xor_reg_self(JitBuf *b, int reg);"}, {"doc": "/* SHR r64, CL  (logical shift right) void emit_shr_reg_cl(JitBuf *b, int reg); /* SAR r64, CL  (arithmetic shift right) void emit_sar_reg_cl(JitBuf *b, int reg); /* XOR reg, reg (zero-idiom, 3 bytes) void emit_xor_reg_self(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Comparison /* ------------------------------------------------------------------ /* CMP r64, r64  (REX.W 39 /r)", "kind": "function", "line": 213, "name": "emit_cmp_reg_reg", "signature": "void emit_cmp_reg_reg(JitBuf *buf, int a, int breg);"}, {"doc": "/* SAR r64, CL  (arithmetic shift right) void emit_sar_reg_cl(JitBuf *b, int reg); /* XOR reg, reg (zero-idiom, 3 bytes) void emit_xor_reg_self(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Comparison /* ------------------------------------------------------------------ /* CMP r64, r64  (REX.W 39 /r) void emit_cmp_reg_reg(JitBuf *buf, int a, int breg); /* TEST r64, r64  (REX.W 85 /r)", "kind": "function", "line": 216, "name": "emit_test_reg_reg", "signature": "void emit_test_reg_reg(JitBuf *buf, int a, int breg);"}, {"doc": "/* XOR reg, reg (zero-idiom, 3 bytes) void emit_xor_reg_self(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Comparison /* ------------------------------------------------------------------ /* CMP r64, r64  (REX.W 39 /r) void emit_cmp_reg_reg(JitBuf *buf, int a, int breg); /* TEST r64, r64  (REX.W 85 /r) void emit_test_reg_reg(JitBuf *buf, int a, int breg); /* SETcc r/m8  (0F 9x /0)", "kind": "function", "line": 219, "name": "emit_setcc", "signature": "void emit_setcc(JitBuf *b, int cc, int dst);"}, {"doc": "/* CMP r64, r64  (REX.W 39 /r) void emit_cmp_reg_reg(JitBuf *buf, int a, int breg); /* TEST r64, r64  (REX.W 85 /r) void emit_test_reg_reg(JitBuf *buf, int a, int breg); /* SETcc r/m8  (0F 9x /0) void emit_setcc(JitBuf *b, int cc, int dst); /* ------------------------------------------------------------------ /*  Control flow /* ------------------------------------------------------------------ /* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching", "kind": "function", "line": 226, "name": "emit_jmp_rel32", "signature": "size_t emit_jmp_rel32(JitBuf *b, int32_t rel);"}, {"doc": "/* TEST r64, r64  (REX.W 85 /r) void emit_test_reg_reg(JitBuf *buf, int a, int breg); /* SETcc r/m8  (0F 9x /0) void emit_setcc(JitBuf *b, int cc, int dst); /* ------------------------------------------------------------------ /*  Control flow /* ------------------------------------------------------------------ /* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching size_t emit_jmp_rel32(JitBuf *b, int32_t rel); /* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching", "kind": "function", "line": 229, "name": "emit_jcc_rel32", "signature": "size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel);"}, {"doc": "/* SETcc r/m8  (0F 9x /0) void emit_setcc(JitBuf *b, int cc, int dst); /* ------------------------------------------------------------------ /*  Control flow /* ------------------------------------------------------------------ /* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching size_t emit_jmp_rel32(JitBuf *b, int32_t rel); /* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel); /* JMP to absolute offset within the buffer (emits rel32, records patch)", "kind": "function", "line": 232, "name": "emit_jmp_buf", "signature": "void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p);"}, {"doc": "/* ------------------------------------------------------------------ /*  Control flow /* ------------------------------------------------------------------ /* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching size_t emit_jmp_rel32(JitBuf *b, int32_t rel); /* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel); /* JMP to absolute offset within the buffer (emits rel32, records patch) void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p); /* Jcc to absolute offset within the buffer", "kind": "function", "line": 235, "name": "emit_jcc_buf", "signature": "void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p);"}, {"doc": "/* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching size_t emit_jmp_rel32(JitBuf *b, int32_t rel); /* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel); /* JMP to absolute offset within the buffer (emits rel32, records patch) void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p); /* Jcc to absolute offset within the buffer void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p); /* Apply all patches: for each patch, compute rel32 = target - (patch_off + 4)", "kind": "function", "line": 238, "name": "jit_apply_patches", "signature": "void jit_apply_patches(JitBuf *b, const JitPatches *p);"}, {"doc": "/* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel); /* JMP to absolute offset within the buffer (emits rel32, records patch) void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p); /* Jcc to absolute offset within the buffer void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p); /* Apply all patches: for each patch, compute rel32 = target - (patch_off + 4) void jit_apply_patches(JitBuf *b, const JitPatches *p); /* CALL rel32  (E8 imm32)", "kind": "function", "line": 241, "name": "emit_call_rel32", "signature": "size_t emit_call_rel32(JitBuf *b, int32_t rel);"}, {"doc": "/* JMP to absolute offset within the buffer (emits rel32, records patch) void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p); /* Jcc to absolute offset within the buffer void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p); /* Apply all patches: for each patch, compute rel32 = target - (patch_off + 4) void jit_apply_patches(JitBuf *b, const JitPatches *p); /* CALL rel32  (E8 imm32) size_t emit_call_rel32(JitBuf *b, int32_t rel); /* CALL r/m64  (FF /2, 2 bytes)", "kind": "function", "line": 244, "name": "emit_call_reg", "signature": "void emit_call_reg(JitBuf *b, int reg);"}, {"doc": "/* Jcc to absolute offset within the buffer void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p); /* Apply all patches: for each patch, compute rel32 = target - (patch_off + 4) void jit_apply_patches(JitBuf *b, const JitPatches *p); /* CALL rel32  (E8 imm32) size_t emit_call_rel32(JitBuf *b, int32_t rel); /* CALL r/m64  (FF /2, 2 bytes) void emit_call_reg(JitBuf *b, int reg); /* RET  (C3)", "kind": "function", "line": 247, "name": "emit_ret", "signature": "void emit_ret(JitBuf *b);"}, {"doc": "/* CALL rel32  (E8 imm32) size_t emit_call_rel32(JitBuf *b, int32_t rel); /* CALL r/m64  (FF /2, 2 bytes) void emit_call_reg(JitBuf *b, int reg); /* RET  (C3) void emit_ret(JitBuf *b); /* ------------------------------------------------------------------ /*  System /* ------------------------------------------------------------------ /* SYSCALL  (0F 05)", "kind": "function", "line": 254, "name": "emit_syscall", "signature": "void emit_syscall(JitBuf *b);"}, {"doc": "/* CALL r/m64  (FF /2, 2 bytes) void emit_call_reg(JitBuf *b, int reg); /* RET  (C3) void emit_ret(JitBuf *b); /* ------------------------------------------------------------------ /*  System /* ------------------------------------------------------------------ /* SYSCALL  (0F 05) void emit_syscall(JitBuf *b); /* INT3  (CC) -- debug breakpoint", "kind": "function", "line": 257, "name": "emit_int3", "signature": "void emit_int3(JitBuf *b);"}, {"doc": "/* RET  (C3) void emit_ret(JitBuf *b); /* ------------------------------------------------------------------ /*  System /* ------------------------------------------------------------------ /* SYSCALL  (0F 05) void emit_syscall(JitBuf *b); /* INT3  (CC) -- debug breakpoint void emit_int3(JitBuf *b); /* NOP  (90)", "kind": "function", "line": 260, "name": "emit_nop", "signature": "void emit_nop(JitBuf *b);"}, {"doc": "Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used.", "kind": "function", "line": 269, "name": "emit_call_abs", "signature": "void emit_call_abs(JitBuf *b, void *func, int scratch);"}, {"doc": "Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used. void emit_call_abs(JitBuf *b, void *func, int scratch); /* AND r64, imm32", "kind": "function", "line": 272, "name": "emit_and_reg_imm32", "signature": "void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm);"}, {"doc": "Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used. void emit_call_abs(JitBuf *b, void *func, int scratch); /* AND r64, imm32 void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm); /* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension", "kind": "function", "line": 275, "name": "emit_movzx_reg_reg8", "signature": "void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src);"}, {"doc": "Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used. void emit_call_abs(JitBuf *b, void *func, int scratch); /* AND r64, imm32 void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm); /* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src); /* REX prefix: exposed for inline asm emission", "kind": "function", "line": 278, "name": "emit_rex", "signature": "void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b);"}, {"doc": "Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used. void emit_call_abs(JitBuf *b, void *func, int scratch); /* AND r64, imm32 void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm); /* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src); /* REX prefix: exposed for inline asm emission void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b); /* ModRM byte: exposed for inline asm emission", "kind": "function", "line": 281, "name": "emit_modrm", "signature": "void emit_modrm(JitBuf *buf, int mod, int reg, int rm);"}, {"doc": "/* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src); /* REX prefix: exposed for inline asm emission void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b); /* ModRM byte: exposed for inline asm emission void emit_modrm(JitBuf *buf, int mod, int reg, int rm); /* ------------------------------------------------------------------ /*  Misc /* ------------------------------------------------------------------ /* MOV byte [base + disp], imm8  (REX.C6 /0)", "kind": "function", "line": 288, "name": "emit_mov_mem_imm8", "signature": "void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm);"}, {"doc": "/* REX prefix: exposed for inline asm emission void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b); /* ModRM byte: exposed for inline asm emission void emit_modrm(JitBuf *buf, int mod, int reg, int rm); /* ------------------------------------------------------------------ /*  Misc /* ------------------------------------------------------------------ /* MOV byte [base + disp], imm8  (REX.C6 /0) void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm); /* MOV qword [base + disp], imm32 (sign-extended)  (REX.W C7 /0)", "kind": "function", "line": 291, "name": "emit_mov_mem_imm32", "signature": "void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm);"}, {"kind": "macro", "line": 10, "name": "CVM_JIT_X86_H", "signature": "#define CVM_JIT_X86_H"}, {"kind": "macro", "line": 53, "name": "JIT_MAX_PATCHES", "signature": "#define JIT_MAX_PATCHES"}]}, {"id": "cvm2/cvm_ops.c", "kind": "module", "label": "cvm_ops.c", "language": "c", "sha256": "74ddad050b2137ab", "symbol_count": 7, "symbols": [{"kind": "function", "line": 72, "name": "cvm_op_info", "signature": "const CvmOpInfo *cvm_op_info(uint8_t opcode)"}, {"kind": "function", "line": 78, "name": "cvm_op_name", "signature": "const char *cvm_op_name(uint8_t opcode)"}, {"kind": "function", "line": 83, "name": "cvm_ops_r8", "signature": "int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out)"}, {"kind": "function", "line": 89, "name": "cvm_ops_ru32", "signature": "uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off)"}, {"kind": "function", "line": 97, "name": "cvm_ops_ri32", "signature": "int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off)"}, {"kind": "function", "line": 101, "name": "cvm_ops_ri64", "signature": "int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off)"}, {"kind": "macro", "line": 70, "name": "OP_INFOS_LEN", "signature": "#define OP_INFOS_LEN"}]}, {"id": "cvm2/cvm_ops.h", "kind": "module", "label": "cvm_ops.h", "language": "h", "sha256": "3fa3a499b21d6b06", "symbol_count": 9, "symbols": [{"kind": "struct", "line": 30, "name": "CvmOpInfo"}, {"doc": "CVM_OPK_U32   = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL   = 6, CVM_OPK_U8U8  = 7 } CvmOpKind; typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for one opcode, or NULL when the opcode is not defined.", "kind": "function", "line": 38, "name": "cvm_op_info", "signature": "const CvmOpInfo *cvm_op_info(uint8_t opcode);"}, {"doc": "CVM_OPK_U8U8  = 7 } CvmOpKind; typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for one opcode, or NULL when the opcode is not defined. const CvmOpInfo *cvm_op_info(uint8_t opcode); /* Mnemonic for one opcode, or NULL when the opcode is not defined.", "kind": "function", "line": 41, "name": "cvm_op_name", "signature": "const char *cvm_op_name(uint8_t opcode);"}, {"doc": "typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for one opcode, or NULL when the opcode is not defined. const CvmOpInfo *cvm_op_info(uint8_t opcode); /* Mnemonic for one opcode, or NULL when the opcode is not defined. const char *cvm_op_name(uint8_t opcode); /* Decode helpers over a code buffer, little-endian as stored.", "kind": "function", "line": 44, "name": "cvm_ops_ri32", "signature": "int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off);"}, {"kind": "function", "line": 45, "name": "cvm_ops_ri64", "signature": "int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off);"}, {"kind": "function", "line": 46, "name": "cvm_ops_ru32", "signature": "uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off);"}, {"kind": "function", "line": 47, "name": "cvm_ops_r8", "signature": "int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out);"}, {"doc": "ifdef __cplusplus", "kind": "variable", "line": 16, "name": "CvmOpKind", "signature": "extern \"C\" { #endif typedef enum { CVM_OPK_NONE = 0, CVM_OPK_I8 = 1, CVM_OPK_I32 = 2, CVM_OPK_I64 = 3, CVM_OPK_U32 = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL = 6, CVM_OPK_U8U8 = 7 } CvmOpKind;"}, {"kind": "macro", "line": 10, "name": "CVM_OPS_H", "signature": "#define CVM_OPS_H"}]}, {"id": "cvm2/cvm_val_main.c", "kind": "module", "label": "cvm_val_main.c", "language": "c", "sha256": "dd38d83e660e152f", "symbol_count": 25, "symbols": [{"kind": "struct", "line": 33, "name": "DepthRange"}, {"kind": "struct", "line": 38, "name": "ValCtx"}, {"kind": "struct", "line": 45, "name": "FuncCtx"}, {"doc": "Stack effect of one instruction on the interval [lo,hi]: * required pops, then the net deltas.", "kind": "struct", "line": 97, "name": "StackEffect"}, {"kind": "function", "line": 56, "name": "val_err", "signature": "static void val_err(ValCtx *ctx, const char *what)"}, {"kind": "function", "line": 61, "name": "val_fun_err", "signature": "static void val_fun_err(FuncCtx *fc, const char *what)"}, {"kind": "function", "line": 68, "name": "code_of", "signature": "static const uint8_t *code_of(const CvmModuleView *v)"}, {"kind": "function", "line": 72, "name": "q_push", "signature": "static void q_push(FuncCtx *fc, size_t off)"}, {"kind": "function", "line": 81, "name": "q_pop", "signature": "static size_t q_pop(FuncCtx *fc)"}, {"kind": "function", "line": 88, "name": "dr_merge", "signature": "static int dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)"}, {"kind": "function", "line": 103, "name": "stack_effect", "signature": "static int stack_effect(const CvmModuleView *v, size_t off, uint8_t op,\n                        S..."}, {"kind": "function", "line": 181, "name": "check_static", "signature": "static int check_static(FuncCtx *fc, size_t off, uint8_t op,\n                        size_t next_ip)"}, {"doc": "Abstract-interpretation stack balance: each instruction start carries a [lo,hi] interval of possible stack depths; a required pop with lo==0 * is an underflow. Hi saturates at the stack capacity.", "kind": "function", "line": 361, "name": "analyze_stack", "signature": "static int analyze_stack(FuncCtx *fc)"}, {"kind": "function", "line": 435, "name": "check_function", "signature": "static int check_function(FuncCtx *fc, size_t *insn_count)"}, {"kind": "function", "line": 450, "name": "cmp_func", "signature": "static int cmp_func(const void *a, const void *b)"}, {"kind": "function", "line": 456, "name": "main", "signature": "int main(int argc, char **argv)"}, {"kind": "macro", "line": 15, "name": "CVM_VAL_MAX_FUNCS", "signature": "#define CVM_VAL_MAX_FUNCS"}, {"kind": "macro", "line": 16, "name": "CVM_VAL_MAX_GLOBALS", "signature": "#define CVM_VAL_MAX_GLOBALS"}, {"kind": "macro", "line": 17, "name": "CVM_VAL_MAX_NATIVES", "signature": "#define CVM_VAL_MAX_NATIVES"}, {"kind": "macro", "line": 18, "name": "CVM_VAL_MAX_CODE", "signature": "#define CVM_VAL_MAX_CODE"}, {"kind": "macro", "line": 19, "name": "CVM_VAL_MAX_LOCALS", "signature": "#define CVM_VAL_MAX_LOCALS"}, {"kind": "macro", "line": 20, "name": "CVM_VAL_MAX_ARGS", "signature": "#define CVM_VAL_MAX_ARGS"}, {"kind": "macro", "line": 25, "name": "CVM_VAL_STACK_CAP", "signature": "#define CVM_VAL_STACK_CAP"}, {"kind": "macro", "line": 30, "name": "CVM_VAL_WIDEN_BOUND", "signature": "#define CVM_VAL_WIDEN_BOUND"}, {"kind": "macro", "line": 31, "name": "CVM_VAL_MAX_SARGS", "signature": "#define CVM_VAL_MAX_SARGS"}]}, {"id": "cvm2/cvm_view.c", "kind": "module", "label": "cvm_view.c", "language": "c", "sha256": "f997129310cb1a61", "symbol_count": 8, "symbols": [{"kind": "function", "line": 9, "name": "rl32", "signature": "static uint32_t rl32(const uint8_t *p)"}, {"kind": "function", "line": 14, "name": "rl16", "signature": "static uint32_t rl16(const uint8_t *p)"}, {"kind": "function", "line": 18, "name": "cvm_view_strerror", "signature": "const char *cvm_view_strerror(int error_code)"}, {"kind": "function", "line": 29, "name": "cvm_view_open", "signature": "int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size)"}, {"kind": "function", "line": 72, "name": "cvm_view_func", "signature": "const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i)"}, {"kind": "function", "line": 78, "name": "cvm_view_string", "signature": "const char *cvm_view_string(const CvmModuleView *v, uint32_t off)"}, {"kind": "function", "line": 87, "name": "cvm_view_func_name", "signature": "const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,\n                             ..."}, {"kind": "function", "line": 108, "name": "cvm_view_func_region", "signature": "int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,\n                         size_t *be..."}]}, {"id": "cvm2/cvm_view.h", "kind": "module", "label": "cvm_view.h", "language": "h", "sha256": "07170a5861277a0a", "symbol_count": 9, "symbols": [{"kind": "struct", "line": 19, "name": "CvmModuleView"}, {"doc": "uint32_t       num_strings; uint32_t       code_size; uint32_t       string_pool_size; uint32_t       data_size; uint32_t       entry_func; size_t         func_off; size_t         global_off; size_t         native_off; size_t         string_off; size_t         code_off; size_t         pool_off; } CvmModuleView; /* Parse and validate the header plus all section extents.", "kind": "function", "line": 41, "name": "cvm_view_open", "signature": "int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size);"}, {"doc": "uint32_t       data_size; uint32_t       entry_func; size_t         func_off; size_t         global_off; size_t         native_off; size_t         string_off; size_t         code_off; size_t         pool_off; } CvmModuleView; /* Parse and validate the header plus all section extents. int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size); /* Message for an error code returned by cvm_view_open.", "kind": "function", "line": 44, "name": "cvm_view_strerror", "signature": "const char *cvm_view_strerror(int error_code);"}, {"kind": "function", "line": 46, "name": "cvm_view_func", "signature": "const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i);"}, {"doc": "String from the pool, or NULL when the offset is outside it. The * pointer is only valid while the module data lives.", "kind": "function", "line": 50, "name": "cvm_view_string", "signature": "const char *cvm_view_string(const CvmModuleView *v, uint32_t off);"}, {"doc": "String from the pool, or NULL when the offset is outside it. The * pointer is only valid while the module data lives. const char *cvm_view_string(const CvmModuleView *v, uint32_t off); /* Function name from the pool; falls back to \"func<N>\" in fallback.", "kind": "function", "line": 53, "name": "cvm_view_func_name", "signature": "const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi, char *fallback, size_t cap);"}, {"doc": "Code region of a function: [*begin, *end) where *end is the next * function's code offset or the end of the code section.", "kind": "function", "line": 58, "name": "cvm_view_func_region", "signature": "int cvm_view_func_region(const CvmModuleView *v, uint32_t fi, size_t *begin, size_t *end);"}, {"doc": "ifdef __cplusplus", "kind": "variable", "line": 16, "name": "data", "signature": "extern \"C\" { #endif typedef struct { const uint8_t *data;"}, {"kind": "macro", "line": 9, "name": "CVM_VIEW_H", "signature": "#define CVM_VIEW_H"}]}, {"id": "cvm2/deepseek_bash_20260808_653f26.sh", "kind": "module", "label": "deepseek_bash_20260808_653f26.sh", "language": "sh", "sha256": "9add9b001461e70a", "symbol_count": 0, "symbols": []}, {"id": "cvm2/gen_fib_cvm.c", "kind": "module", "label": "gen_fib_cvm.c", "language": "c", "sha256": "f2f4cdae3455d79b", "symbol_count": 10, "symbols": [{"kind": "function", "line": 21, "name": "emit_byte", "signature": "static void emit_byte(uint8_t b)"}, {"kind": "function", "line": 30, "name": "emit_u32", "signature": "static void emit_u32(uint32_t v)"}, {"kind": "function", "line": 37, "name": "emit_i32", "signature": "static void emit_i32(int32_t v)"}, {"kind": "function", "line": 39, "name": "patch_i32", "signature": "static void patch_i32(size_t pos, int32_t val)"}, {"kind": "function", "line": 46, "name": "write_le32", "signature": "static void write_le32(uint8_t *p, uint32_t v)"}, {"kind": "function", "line": 53, "name": "emit_global_inc", "signature": "static void emit_global_inc(void)"}, {"kind": "function", "line": 64, "name": "main", "signature": "int main(int argc, char *argv[])"}, {"kind": "macro", "line": 13, "name": "FIB_N", "signature": "#define FIB_N"}, {"kind": "macro", "line": 14, "name": "EXPECTED_FIB10", "signature": "#define EXPECTED_FIB10"}, {"kind": "macro", "line": 15, "name": "EXPECTED_CALLS", "signature": "#define EXPECTED_CALLS"}]}, {"id": "cvm2/gen_minimal.c", "kind": "module", "label": "gen_minimal.c", "language": "c", "sha256": "94dc061856c57b9e", "symbol_count": 4, "symbols": [{"kind": "function", "line": 14, "name": "emit_byte", "signature": "static void emit_byte(uint8_t b)"}, {"kind": "function", "line": 21, "name": "emit_u32", "signature": "static void emit_u32(uint32_t v)"}, {"kind": "function", "line": 25, "name": "write_le32", "signature": "static void write_le32(uint8_t *p, uint32_t v)"}, {"kind": "function", "line": 30, "name": "main", "signature": "int main(void)"}]}, {"doc": "Generate a minimal .cvm that pushes 42 and halts. No function calls.", "id": "cvm2/gen_test.py", "kind": "module", "label": "gen_test.py", "language": "py", "sha256": "5ed3f2c9d4cd2444", "symbol_count": 2, "symbols": [{"kind": "function", "line": 7, "name": "emit_byte", "signature": "def emit_byte(b)"}, {"kind": "function", "line": 10, "name": "emit_u32", "signature": "def emit_u32(v)"}]}, {"doc": "CVM v2 toolchain suite: interpreter, disassembler, validator (including corrupted-module rejections) and the scripted debugger. Every check is a hard failure: a rejected module that validates, or a corrupted module that passes, fails the suite.", "id": "cvm2/test.sh", "kind": "module", "label": "test.sh", "language": "sh", "sha256": "70b6ff5f24232650", "symbol_count": 2, "symbols": [{"kind": "function", "line": 13, "name": "check"}, {"kind": "function", "line": 24, "name": "reject"}]}, {"id": "gen_fib_cvm.c", "kind": "module", "label": "gen_fib_cvm.c", "language": "c", "sha256": "dd99af8714fb454e", "symbol_count": 3, "symbols": [{"kind": "function", "line": 24, "name": "add_string", "signature": "static uint32_t add_string(const char *s)"}, {"kind": "function", "line": 36, "name": "main", "signature": "int main(void)"}, {"kind": "function", "line": 7, "name": "fib", "signature": "* return fib(n-1) + fib(n-2);"}]}, {"id": "test.sh", "kind": "module", "label": "test.sh", "language": "sh", "sha256": "2a5a4539c1bfb714", "symbol_count": 0, "symbols": []}], "type": "CodePropertyGraph", "version": "1.0"}
```

---

## Architecture Reference

### C (14 files)

#### `cvm.c`
**Path:** `cvm.c`

**Functions:**
- `cvm_error` (line 12) `static void cvm_error(CVM *vm, const char *fmt, ...)` - *cvm.c — C Virtual Machine interpreter  #include "cvm.h" #include <stdarg.h> #include <errno.h> /* ------------------------------------------------------------------ /*  Debug helpers /* ------------------------------------------------------------------*
- `op_name` (line 22) `static const char *op_name(uint8_t op)`
- `push` (line 78) `static inline void push(CVM *vm, uint64_t v)` - *case OP_RET: return "RET"; case OP_RET_VOID: return "RET_VOID"; case OP_ALLOC: return "ALLOC"; case OP_FREE: return "FREE"; case OP_SYSCALL: return "SYSCALL"; case OP_PRINT_I64: return "PRINT_I64"; case OP_HALT: return "HALT"; default: return "???"; } } /* ------------------------------------------------------------------ /*  Stack helpers /* ------------------------------------------------------------------*
- `pop` (line 86) `static inline uint64_t pop(CVM *vm)`
- `peek` (line 94) `static inline uint64_t peek(CVM *vm)`
- `push_frame` (line 102) `static int push_frame(CVM *vm, CVM_Module *mod, uint16_t func_idx, int argc)` - *cvm_error(vm, "operand stack underflow"); return 0; } return vm->stack[--vm->sp]; } static inline uint64_t peek(CVM *vm) { if (vm->sp <= 0) return 0; return vm->stack[vm->sp - 1]; } /* ------------------------------------------------------------------ /*  Frame helpers /* ------------------------------------------------------------------*
- `pop_frame` (line 142) `static void pop_frame(CVM *vm, int has_retval)`
- `call_native` (line 175) `static void call_native(CVM *vm, uint16_t idx, uint8_t argc)` - *if (has_retval) push(vm, ret); vm->running = 0; return; } /* restore previous module / code pointer if needed /* (for multi-module we would look up the previous frame's module) vm->ip = ret_ip; if (has_retval) push(vm, ret); } /* ------------------------------------------------------------------ /*  Native call (very limited – only a few for the tests) /* ------------------------------------------------------------------*
- `cvm_create` (line 227) `CVM *cvm_create(void)` - *(void)fd; (void)buf; (void)len; } push(vm, 0); return; } /* generic: just pop args and push 0 for (int i = 0; i < argc; i++) pop(vm); push(vm, 0); } /* ------------------------------------------------------------------ /*  Create / destroy /* ------------------------------------------------------------------*
- `cvm_destroy` (line 244) `void cvm_destroy(CVM *vm)`
- `cvm_load_module_mem` (line 267) `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name)` - *free(m->natives); free(m->code); free(m->string_pool); free(m->global_mem); free(m); } free(vm->stack); free(vm->heap); free(vm); } /* ------------------------------------------------------------------ /*  Load module from memory /* ------------------------------------------------------------------*
- `cvm_load_module` (line 337) `int cvm_load_module(CVM *vm, const char *path)`
- `interpret` (line 361) `static int interpret(CVM *vm)` - *if (!buf || fread(buf, 1, (size_t)sz, f) != (size_t)sz) { free(buf); fclose(f); return -1; } fclose(f); int r = cvm_load_module_mem(vm, buf, (size_t)sz, path); free(buf); return r; } /* ------------------------------------------------------------------ /*  Main interpreter loop /* ------------------------------------------------------------------*
- `cvm_run` (line 700) `int cvm_run(CVM *vm, const char *entry_name)` - *vm->running = 0; break; default: cvm_error(vm, "unknown opcode 0x%02x at ip=%u", op, vm->ip - 1); break; } } return 0; } /* ------------------------------------------------------------------ /*  Public run /* ------------------------------------------------------------------*
- `cvm_emit_byte` (line 743) `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b)` - *if (vm->trace) fprintf(stderr, "Finished. instructions = %llu\n", (unsigned long long)vm->instr_count); /* if there is a return value left on the stack, return it as exit code if (vm->sp > 0) return (int)(int64_t)vm->stack[vm->sp - 1]; return 0; } /* ------------------------------------------------------------------ /*  Emitter helpers (used by the backend) /* ------------------------------------------------------------------*
- `cvm_emit_i16` (line 751) `void cvm_emit_i16(uint8_t **buf, size_t *cap, size_t *len, int16_t v)`
- `cvm_emit_u16` (line 756) `void cvm_emit_u16(uint8_t **buf, size_t *cap, size_t *len, uint16_t v)`
- `cvm_emit_i32` (line 761) `void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v)`
- `cvm_emit_i64` (line 766) `void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v)`
- `main` (line 775) `int main(int argc, char **argv)` - *void cvm_emit_i32(uint8_t **buf, size_t *cap, size_t *len, int32_t v) { for (int i = 0; i < 4; i++) cvm_emit_byte(buf, cap, len, (uint8_t)((v >> (i * 8)) & 0xff)); } void cvm_emit_i64(uint8_t **buf, size_t *cap, size_t *len, int64_t v) { for (int i = 0; i < 8; i++) cvm_emit_byte(buf, cap, len, (uint8_t)((v >> (i * 8)) & 0xff)); } /* ------------------------------------------------------------------ /*  Main (standalone runner) /* ------------------------------------------------------------------ ifdef CVM_STANDALONE*

#### `cvm.c`
**Path:** `cvm2/cvm.c`

**Functions:**
- `xmal` (line 28) `static void *xmal(size_t s)`
- `xcal` (line 34) `static void *xcal(size_t n, size_t s)`
- `cvm_config_default` (line 40) `CvmConfig cvm_config_default(void)`
- `cvm_create` (line 55) `CvmState *cvm_create(const CvmConfig *config)`
- `cvm_destroy` (line 94) `void cvm_destroy(CvmState *vm)`
- `cvm_strerror` (line 113) `const char *cvm_strerror(int e)`
- `vp` (line 137) `static int vp(CvmState *vm, uint64_t v)`
- `vo` (line 143) `static int vo(CvmState *vm, uint64_t *v)`
- `r8` (line 149) `static int r8(CvmState *vm, uint8_t *o)`
- `r32` (line 155) `static int r32(CvmState *vm, uint32_t *o)`
- `ri32` (line 165) `static int ri32(CvmState *vm, int32_t *o)`
- `r64` (line 173) `static int r64(CvmState *vm, uint64_t *o)`
- `push_frame` (line 183) `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...`
- `pop_frame` (line 196) `static void pop_frame(CvmState *vm)`
- `cur_frame` (line 203) `static CvmFrame *cur_frame(CvmState *vm)`
- `range_valid` (line 207) `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)`
- `mem_valid` (line 215) `static int mem_valid(CvmState *vm, uint64_t a, size_t s)`
- `heap_alloc` (line 227) `static uint64_t heap_alloc(CvmState *vm, size_t s)`
- `cvm_heap_alloc` (line 235) `void *cvm_heap_alloc(CvmState *vm, size_t size)`
- `data_w64` (line 239) `static void data_w64(CvmState *vm, size_t off, uint64_t v)`
- `data_r64` (line 244) `static uint64_t data_r64(CvmState *vm, size_t off)`
- `cvm_set_args` (line 250) `int cvm_set_args(CvmState *vm, int argc, char **argv)`
- `cvm_register_native` (line 283) `int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn)`
- `find_native` (line 294) `static int find_native(CvmState *vm, const char *name)`
- `native_write` (line 305) `static int64_t native_write(void *vm, int ac, uint64_t *av)`
- `native_read` (line 311) `static int64_t native_read(void *vm, int ac, uint64_t *av)`
- `native_exit` (line 317) `static int64_t native_exit(void *vm, int ac, uint64_t *av)`
- `native_abort` (line 324) `static int64_t native_abort(void *vm, int ac, uint64_t *av)`
- `native_putchar` (line 329) `static int64_t native_putchar(void *vm, int ac, uint64_t *av)`
- `native_puts` (line 336) `static int64_t native_puts(void *vm, int ac, uint64_t *av)`
- `native_strlen` (line 350) `static int64_t native_strlen(void *vm, int ac, uint64_t *av)`
- `native_strcmp` (line 356) `static int64_t native_strcmp(void *vm, int ac, uint64_t *av)`
- `native_strncmp` (line 362) `static int64_t native_strncmp(void *vm, int ac, uint64_t *av)`
- `native_strcpy` (line 369) `static int64_t native_strcpy(void *vm, int ac, uint64_t *av)`
- `native_strncpy` (line 375) `static int64_t native_strncpy(void *vm, int ac, uint64_t *av)`
- `native_strchr` (line 382) `static int64_t native_strchr(void *vm, int ac, uint64_t *av)`
- `native_strstr` (line 388) `static int64_t native_strstr(void *vm, int ac, uint64_t *av)`
- `native_memcpy` (line 395) `static int64_t native_memcpy(void *vm, int ac, uint64_t *av)`
- `native_memmove` (line 402) `static int64_t native_memmove(void *vm, int ac, uint64_t *av)`
- `native_memset` (line 409) `static int64_t native_memset(void *vm, int ac, uint64_t *av)`
- `native_memcmp` (line 415) `static int64_t native_memcmp(void *vm, int ac, uint64_t *av)`
- `native_malloc` (line 422) `static int64_t native_malloc(void *vm, int ac, uint64_t *av)`
- `native_free` (line 428) `static int64_t native_free(void *vm, int ac, uint64_t *av)`
- `native_calloc` (line 433) `static int64_t native_calloc(void *vm, int ac, uint64_t *av)`
- `native_realloc` (line 442) `static int64_t native_realloc(void *vm, int ac, uint64_t *av)`
- `native_atol` (line 451) `static int64_t native_atol(void *vm, int ac, uint64_t *av)`
- `native_strtol` (line 457) `static int64_t native_strtol(void *vm, int ac, uint64_t *av)`
- `vout_write` (line 472) `static void vout_write(Vout *vo, const char *s, size_t n)`
- `vout_char` (line 484) `static void vout_char(Vout *vo, char c)`
- `vout_uint` (line 486) `static void vout_uint(Vout *vo, uint64_t v, int base, int upper)`
- `vformat` (line 499) `static void vformat(Vout *vo, const char *fmt, uint64_t *argv, int argc)`
- `native_fprintf` (line 583) `static int64_t native_fprintf(void *vm, int ac, uint64_t *av)`
- `native_printf` (line 593) `static int64_t native_printf(void *vm, int ac, uint64_t *av)`
- `native_sprintf` (line 602) `static int64_t native_sprintf(void *vm, int ac, uint64_t *av)`
- `native_snprintf` (line 613) `static int64_t native_snprintf(void *vm, int ac, uint64_t *av)`
- `native_fopen` (line 625) `static int64_t native_fopen(void *vm, int ac, uint64_t *av)`
- `native_fclose` (line 632) `static int64_t native_fclose(void *vm, int ac, uint64_t *av)`
- `native_fread` (line 638) `static int64_t native_fread(void *vm, int ac, uint64_t *av)`
- `native_fwrite` (line 645) `static int64_t native_fwrite(void *vm, int ac, uint64_t *av)`
- `native_fseek` (line 652) `static int64_t native_fseek(void *vm, int ac, uint64_t *av)`
- `native_ftell` (line 658) `static int64_t native_ftell(void *vm, int ac, uint64_t *av)`
- `native_rewind` (line 664) `static int64_t native_rewind(void *vm, int ac, uint64_t *av)`
- `native_fputs` (line 671) `static int64_t native_fputs(void *vm, int ac, uint64_t *av)`
- `native_fputc` (line 677) `static int64_t native_fputc(void *vm, int ac, uint64_t *av)`
- `native_fgetc` (line 683) `static int64_t native_fgetc(void *vm, int ac, uint64_t *av)`
- `native_ungetc` (line 689) `static int64_t native_ungetc(void *vm, int ac, uint64_t *av)`
- `native_fflush` (line 695) `static int64_t native_fflush(void *vm, int ac, uint64_t *av)`
- `native_perror` (line 701) `static int64_t native_perror(void *vm, int ac, uint64_t *av)`
- `native_stderr_addr` (line 712) `static int64_t native_stderr_addr(void *vm, int ac, uint64_t *av)`
- `native_stdout_addr` (line 717) `static int64_t native_stdout_addr(void *vm, int ac, uint64_t *av)`
- `native_stdin_addr` (line 722) `static int64_t native_stdin_addr(void *vm, int ac, uint64_t *av)`
- `native_exit_core` (line 729) `static int64_t native_exit_core(void *vm, int ac, uint64_t *av)`
- `register_defaults` (line 736) `static void register_defaults(CvmState *vm)`
- `rl32` (line 788) `static uint32_t rl32(const uint8_t *p)` - *cvm_register_native(vm, "fputc", native_fputc); cvm_register_native(vm, "fgetc", native_fgetc); cvm_register_native(vm, "ungetc", native_ungetc); cvm_register_native(vm, "fflush", native_fflush); cvm_register_native(vm, "perror", native_perror); cvm_register_native(vm, "stderr_addr", native_stderr_addr); cvm_register_native(vm, "stdout_addr", native_stdout_addr); cvm_register_native(vm, "stdin_addr", native_stdin_addr); #endif } /* ------------------------------------------------------------------ /*  Module loader /* ------------------------------------------------------------------*
- `decompress_rle` (line 793) `static int decompress_rle(uint8_t *dst, size_t dsz, const uint8_t *src, size_t ssz)`
- `cvm_free_module` (line 815) `static void cvm_free_module(CvmState *vm)`
- `cvm_load_module` (line 830) `int cvm_load_module(CvmState *vm, const uint8_t *d, size_t sz)`
- `cvm_load_module_file` (line 923) `int cvm_load_module_file(CvmState *vm, const char *path)`
- `cvm_run_loop` (line 942) `static int cvm_run_loop(CvmState *vm)` - *if (sz < 0) { fclose(f); return CVM_ERR_IO; } rewind(f); uint8_t *buf = (uint8_t *)xmal((size_t)sz); size_t rd = fread(buf, 1, (size_t)sz, f); fclose(f); if (rd != (size_t)sz) { free(buf); return CVM_ERR_IO; } int rc = cvm_load_module(vm, buf, (size_t)sz); free(buf); return rc; } /* ------------------------------------------------------------------ /*  Interpreter /* ------------------------------------------------------------------*
- `cvm_run` (line 952) `int cvm_run(CvmState *vm)`
- `cvm_continue` (line 990) `int cvm_continue(CvmState *vm)` - *rsp = top - 8; (uint64_t *)(uintptr_t)(top - 8) = 0; data_w64(vm, CVM_DATA_RSP, rsp); data_w64(vm, CVM_DATA_RBP, rsp); data_w64(vm, CVM_DATA_ARGC, 0); data_w64(vm, CVM_DATA_ARGV, 0); } } } return cvm_run_loop(vm); } /* Run after a breakpoint: same loop, no state reset.*
- `cvm_break_set` (line 994) `int cvm_break_set(CvmState *vm, size_t ip)`
- `cvm_break_clear` (line 1003) `int cvm_break_clear(CvmState *vm, size_t ip)`
- `cvm_break_clear_all` (line 1014) `void cvm_break_clear_all(CvmState *vm)`
- `cvm_break_hit` (line 1018) `int cvm_break_hit(const CvmState *vm)`
- `cvm_profile_begin` (line 1024) `int cvm_profile_begin(CvmState *vm)`
- `cvm_profile_end` (line 1034) `void cvm_profile_end(CvmState *vm)`
- `cvm_step` (line 1039) `int cvm_step(CvmState *vm)` - *if (vm->code_size > vm->config.max_profile_code) return CVM_ERR_BOUNDS; if (!vm->ip_counts) vm->ip_counts = (uint32_t *)xcal(vm->code_size > 0 ? vm->code_size : 1, sizeof(uint32_t)); memset(vm->op_counts, 0, sizeof(vm->op_counts)); vm->profile_enabled = 1; return CVM_OK; } void cvm_profile_end(CvmState *vm) { vm->profile_enabled = 0; } /* Execute exactly one instruction at vm->ip.*
- `cvm_exit_code` (line 1351) `int64_t cvm_exit_code(const CvmState *vm)`
- `cvm_instruction_count` (line 1352) `uint64_t cvm_instruction_count(const CvmState *vm)`
- `main` (line 1355) `int main(int argc, char *argv[])` - *if defined(CVM_STANDALONE) && !defined(CVM_NO_MAIN)*

**Macros:**
- `CVM_DEF_STACK` (line 15) `#define CVM_DEF_STACK`
- `CVM_DEF_FRAMES` (line 16) `#define CVM_DEF_FRAMES`
- `CVM_DEF_LOCALS` (line 17) `#define CVM_DEF_LOCALS`
- `CVM_DEF_HEAP` (line 18) `#define CVM_DEF_HEAP`
- `CVM_DEF_GLOBALS` (line 19) `#define CVM_DEF_GLOBALS`
- `CVM_DEF_FUNCS` (line 20) `#define CVM_DEF_FUNCS`
- `CVM_DEF_NATIVES` (line 21) `#define CVM_DEF_NATIVES`
- `CVM_DEF_CODE` (line 22) `#define CVM_DEF_CODE`
- `CVM_DEF_PROFILE` (line 23) `#define CVM_DEF_PROFILE`
- `CVM_HEAP_ALIGN` (line 24) `#define CVM_HEAP_ALIGN`
- `CVM_MAX_NARGS` (line 25) `#define CVM_MAX_NARGS`
- `CVM_MAX_SARGS` (line 26) `#define CVM_MAX_SARGS`

**Structs:**
- `Vout` (line 465) - *static int64_t native_atol(void *vm, int ac, uint64_t *av) { (void)vm; if (ac < 1) return 0; return (int64_t)strtol((const char *)(uintptr_t)av[0], NULL, 10); } static int64_t native_strtol(void *vm, int ac, uint64_t *av) { (void)vm; if (ac < 1) return 0; int base = ac > 1 ? (int)av[1] : 10; return (int64_t)strtol((const char *)(uintptr_t)av[0], NULL, base); } /* ---- mini printf engine ----*

#### `cvm_dbg_main.c`
**Path:** `cvm2/cvm_dbg_main.c`

**Functions:**
- `emit_stdout` (line 29) `static int emit_stdout(void *ctx, const char *line)`
- `func_display` (line 36) `static const char *func_display(uint32_t fi, char *fb, size_t cap)`
- `func_of_ip` (line 40) `static int func_of_ip(size_t ip)`
- `parse_u32` (line 51) `static int parse_u32(const char *s, uint32_t *out)`
- `report_run` (line 59) `static void report_run(int rc)`
- `cmd_list` (line 71) `static void cmd_list(char *arg)`
- `cmd_break` (line 98) `static void cmd_break(char *arg)`
- `cmd_delete` (line 133) `static void cmd_delete(char *arg)`
- `cmd_step` (line 152) `static void cmd_step(void)`
- `cmd_next` (line 166) `static void cmd_next(void)`
- `cmd_run` (line 184) `static void cmd_run(void)`
- `cmd_bt` (line 194) `static void cmd_bt(void)`
- `cmd_stack` (line 206) `static void cmd_stack(void)`
- `cmd_locals` (line 213) `static void cmd_locals(void)`
- `cmd_info` (line 225) `static void cmd_info(void)`
- `cmd_profile` (line 241) `static void cmd_profile(char *arg)`
- `cmd_help` (line 304) `static void cmd_help(void)`
- `dispatch` (line 310) `static void dispatch(char *line)`
- `main` (line 337) `int main(int argc, char **argv)`

**Macros:**
- `DBG_LINE_MAX` (line 18) `#define DBG_LINE_MAX`
- `DBG_PROFILE_TOP` (line 19) `#define DBG_PROFILE_TOP`

#### `cvm_dis.c`
**Path:** `cvm2/cvm_dis.c`

**Functions:**
- `putc_str` (line 13) `static void putc_str(char *buf, size_t cap, size_t *n, char c)`
- `puts_str` (line 17) `static void puts_str(char *buf, size_t cap, size_t *n, const char *s)`
- `put_hex` (line 21) `static void put_hex(char *buf, size_t cap, size_t *n, uint64_t v, int digits)`
- `put_dec` (line 35) `static void put_dec(char *buf, size_t cap, size_t *n, int64_t v)`
- `pad_name` (line 49) `static void pad_name(char *buf, size_t cap, size_t *n, const char *name)`
- `cvm_dis_line` (line 56) `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end,
                 char *buf, size...`
- `cvm_dis_function` (line 153) `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end,
                     CvmDi...`
- `cvm_dis_module` (line 173) `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx)`

**Macros:**
- `CVM_DIS_LINE_MAX` (line 11) `#define CVM_DIS_LINE_MAX`

#### `cvm_dis_main.c`
**Path:** `cvm2/cvm_dis_main.c`

**Functions:**
- `print_line` (line 11) `static int print_line(void *ctx, const char *line)`
- `main` (line 18) `int main(int argc, char **argv)`

#### `cvm_jit.c`
**Path:** `cvm2/cvm_jit.c`

**Functions:**
- `cvm_jit_create` (line 36) `CvmJitState *cvm_jit_create(void)`
- `cvm_jit_destroy` (line 48) `void cvm_jit_destroy(CvmJitState *jit)`
- `ip_map_clear` (line 58) `static void ip_map_clear(CvmJitState *jit)`
- `ip_map_add` (line 62) `static void ip_map_add(CvmJitState *jit, size_t bc_ip, size_t native_off)`
- `ip_map_lookup` (line 69) `static size_t ip_map_lookup(const CvmJitState *jit, size_t bc_ip)`
- `func_cache_find` (line 81) `static JitFuncEntry *func_cache_find(CvmJitState *jit, uint32_t func_idx)`
- `func_cache_add` (line 88) `static JitFuncEntry *func_cache_add(CvmJitState *jit, uint32_t func_idx,
                        ...`
- `opcode_total_size` (line 105) `static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip)`
- `emit_stack_push` (line 117) `static void emit_stack_push(JitBuf *b)` - */* ------------------------------------------------------------------ static size_t opcode_total_size(const uint8_t *code, size_t code_size, size_t ip) { if (ip >= code_size) return 0; const CvmOpInfo *info = cvm_op_info(code[ip]); if (!info) return 1; return info->size; } /* ------------------------------------------------------------------ /*  Emit helpers: operand stack operations /* ------------------------------------------------------------------ /* Push rax onto the operand stack: slots[sp] = rax; sp++*
- `emit_stack_pop` (line 124) `static void emit_stack_pop(JitBuf *b)` - *} /* ------------------------------------------------------------------ /*  Emit helpers: operand stack operations /* ------------------------------------------------------------------ /* Push rax onto the operand stack: slots[sp] = rax; sp++ static void emit_stack_push(JitBuf *b) { /* mov [r12 + r13*8], rax; inc r13 emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1); emit_inc_reg(b, JIT_REG_SP); } /* Pop from operand stack into rax: sp--; rax = slots[sp]*
- `emit_stack_pop_into` (line 130) `static void emit_stack_pop_into(JitBuf *b, int dst)` - */* Push rax onto the operand stack: slots[sp] = rax; sp++ static void emit_stack_push(JitBuf *b) { /* mov [r12 + r13*8], rax; inc r13 emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, JIT_SCRATCH1); emit_inc_reg(b, JIT_REG_SP); } /* Pop from operand stack into rax: sp--; rax = slots[sp] static void emit_stack_pop(JitBuf *b) { emit_dec_reg(b, JIT_REG_SP); emit_mov_reg_sib(b, JIT_SCRATCH1, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Pop from operand stack into dst*
- `emit_stack_push_reg` (line 136) `static void emit_stack_push_reg(JitBuf *b, int reg)` - */* Pop from operand stack into rax: sp--; rax = slots[sp] static void emit_stack_pop(JitBuf *b) { emit_dec_reg(b, JIT_REG_SP); emit_mov_reg_sib(b, JIT_SCRATCH1, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Pop from operand stack into dst static void emit_stack_pop_into(JitBuf *b, int dst) { emit_dec_reg(b, JIT_REG_SP); emit_mov_reg_sib(b, dst, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Push a register onto the operand stack*
- `emit_call1` (line 146) `static void emit_call1(JitBuf *b, void *fn, int arg)` - *emit_mov_reg_sib(b, dst, JIT_REG_SLOTS, JIT_REG_SP, 3); } /* Push a register onto the operand stack static void emit_stack_push_reg(JitBuf *b, int reg) { emit_mov_sib_reg(b, JIT_REG_SLOTS, JIT_REG_SP, 3, reg); emit_inc_reg(b, JIT_REG_SP); } /* ------------------------------------------------------------------ /*  Emit helpers: C function calls /* ------------------------------------------------------------------ /* Call a C function with 1 arg (rdi).  Clobbers rax, rcx, rdx, rsi, rdi, r8-r11.*
- `emit_call2` (line 152) `static void emit_call2(JitBuf *b, void *fn, int a1, int a2)` - *emit_inc_reg(b, JIT_REG_SP); } /* ------------------------------------------------------------------ /*  Emit helpers: C function calls /* ------------------------------------------------------------------ /* Call a C function with 1 arg (rdi).  Clobbers rax, rcx, rdx, rsi, rdi, r8-r11. static void emit_call1(JitBuf *b, void *fn, int arg) { if (arg != XDI) emit_mov_reg_reg(b, XDI, arg); emit_call_abs(b, fn, X10); } /* Call a C function with 2 args (rdi, rsi).*
- `emit_call3` (line 159) `static void emit_call3(JitBuf *b, void *fn, int a1, int a2, int a3)` - */* Call a C function with 1 arg (rdi).  Clobbers rax, rcx, rdx, rsi, rdi, r8-r11. static void emit_call1(JitBuf *b, void *fn, int arg) { if (arg != XDI) emit_mov_reg_reg(b, XDI, arg); emit_call_abs(b, fn, X10); } /* Call a C function with 2 args (rdi, rsi). static void emit_call2(JitBuf *b, void *fn, int a1, int a2) { if (a1 != XDI) emit_mov_reg_reg(b, XDI, a1); if (a2 != XSI) emit_mov_reg_reg(b, XSI, a2); emit_call_abs(b, fn, X10); } /* Call a C function with 3 args (rdi, rsi, rdx).*
- `emit_prologue` (line 170) `static void emit_prologue(JitBuf *b)`
- `emit_epilogue` (line 232) `static void emit_epilogue(JitBuf *b)`
- `emit_save_sp` (line 252) `static void emit_save_sp(JitBuf *b)` - *emit_pop(b, JIT_REG_SP);      /* r13 emit_pop(b, JIT_REG_SLOTS);   /* r12 emit_pop(b, JIT_REG_FRAME);   /* rbx emit_pop(b, XBP);             /* rbp /* xor eax, eax (return 0) emit_xor_reg_self(b, XAX); emit_ret(b); } /* ------------------------------------------------------------------ /*  Emit: save/restore VM state (for C calls) /* ------------------------------------------------------------------ /* Save vm->sp from r13 back to vm (before calling a C helper).*
- `emit_restore_sp` (line 258) `static void emit_restore_sp(JitBuf *b)` - *emit_ret(b); } /* ------------------------------------------------------------------ /*  Emit: save/restore VM state (for C calls) /* ------------------------------------------------------------------ /* Save vm->sp from r13 back to vm (before calling a C helper). static void emit_save_sp(JitBuf *b) { emit_mov32_mem_reg(b, JIT_REG_VM, (int32_t)offsetof(CvmState, sp), JIT_REG_SP); } /* Restore vm->sp into r13 (after calling a C helper).*
- `error` (line 267) `* keeps executing dead code after the stop: error() -> exit() returns
 * into the middle of the f...`
- `emit_opcode` (line 302) `static int emit_opcode(JitCtx *ctx, size_t bc_ip)`
- `jit_apply_patches_local` (line 1235) `static void jit_apply_patches_local(JitBuf *b, const JitPatches *p)`
- `cvm_jit_compile_func` (line 1253) `void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx)`
- `cvm_jit_compile_module` (line 1360) `int cvm_jit_compile_module(CvmState *vm)`
- `cvm_jit_lookup` (line 1376) `void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx)`
- `find_func_for_ip` (line 1388) `static uint32_t find_func_for_ip(const CvmState *vm)` - */* ------------------------------------------------------------------ void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx) { if (!vm->jit) return NULL; JitFuncEntry *e = func_cache_find(vm->jit, func_idx); if (!e) return NULL; return JIT_STATE(vm)->buf.code + e->native_offset; } /* ------------------------------------------------------------------ /*  Execution /* ------------------------------------------------------------------ /* Find which function contains vm->ip*
- `cvm_jit_exec_one` (line 1397) `void cvm_jit_exec_one(CvmState *vm)`
- `cvm_jit_run` (line 1427) `int cvm_jit_run(CvmState *vm)`
- `cvm_jit_stats` (line 1488) `void cvm_jit_stats(const CvmState *vm)`
- `cvm_jit_dump` (line 1499) `void cvm_jit_dump(const CvmState *vm)`
- `cvm_step` (line 1420) `extern int cvm_step(CvmState *);` - *Fall back: interpret this function's bytecodes. We run the interpreter until ip leaves this function or * vm->running becomes 0. uint32_t start_func = func; while (vm->running) { uint32_t cur = find_func_for_ip(vm); if (cur != start_func) break;  /* left this function /* Execute one instruction via the step function*
- `cvm_run` (line 1430) `extern int cvm_run(CvmState *);` - *while (vm->running) { uint32_t cur = find_func_for_ip(vm); if (cur != start_func) break;  /* left this function /* Execute one instruction via the step function extern int cvm_step(CvmState *); int rc = cvm_step(vm); if (rc) break; } } } int cvm_jit_run(CvmState *vm) { if (!vm->jit || !JIT_STATE(vm)->enabled) { /* Should not be called without JIT; fall back to interpreter*

**Macros:**
- `JIT_STATE` (line 30) `#define JIT_STATE(vm)`
- `EMIT_CMP` (line 603) `#define EMIT_CMP(cc_signed)`
- `EMIT_CMP_SIGNED` (line 624) `#define EMIT_CMP_SIGNED(cc)`
- `EMIT_CMP_UNSIGNED` (line 636) `#define EMIT_CMP_UNSIGNED(cc)`

**Structs:**
- `JitCtx` (line 288)

#### `cvm_jit_help.c`
**Path:** `cvm2/cvm_jit_help.c`

**Functions:**
- `cvm_jit_offsets_init` (line 22) `void cvm_jit_offsets_init(CvmJitOffsets *o)`
- `xmal` (line 46) `static void *xmal(size_t s)`
- `xcal` (line 52) `static void *xcal(size_t n, size_t s)`
- `push_frame` (line 58) `static int push_frame(CvmState *vm, uint32_t num_locals, size_t return_ip,
                      ...`
- `pop_frame` (line 71) `static void pop_frame(CvmState *vm)`
- `cur_frame` (line 78) `static CvmFrame *cur_frame(CvmState *vm)`
- `range_valid` (line 82) `static int range_valid(uint64_t a, size_t s, const uint8_t *base, size_t len)`
- `mem_valid` (line 90) `static int mem_valid(const CvmState *vm, uint64_t a, size_t s)`
- `heap_alloc` (line 102) `static uint64_t heap_alloc(CvmState *vm, size_t s)`
- `find_native` (line 110) `static int find_native(const CvmState *vm, const char *name)`
- `jit_vp` (line 120) `static int jit_vp(CvmState *vm, uint64_t v)`
- `jit_vo` (line 126) `static int jit_vo(CvmState *vm, uint64_t *v)`
- `cvm_jit_func_enter` (line 136) `uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx)`
- `cvm_jit_func_leave` (line 145) `void cvm_jit_func_leave(CvmState *vm)`
- `cvm_jit_call` (line 155) `int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc)`
- `cvm_jit_ret` (line 176) `int cvm_jit_ret(CvmState *vm, uint64_t retval)`
- `cvm_jit_call_native` (line 193) `int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc)`
- `cvm_jit_memcheck` (line 213) `int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size)`
- `cvm_jit_alloc` (line 221) `uint64_t cvm_jit_alloc(CvmState *vm, size_t size)`
- `cvm_jit_syscall` (line 229) `int cvm_jit_syscall(CvmState *vm, uint8_t sn, uint8_t argc)`
- `cvm_jit_error` (line 256) `void cvm_jit_error(CvmState *vm, int error_code)`

**Macros:**
- `CVM_HEAP_ALIGN` (line 16) `#define CVM_HEAP_ALIGN`

#### `cvm_jit_x86.c`
**Path:** `cvm2/cvm_jit_x86.c`

**Functions:**
- `jit_buf_init` (line 35) `void jit_buf_init(JitBuf *b, size_t cap)`
- `jit_buf_free` (line 48) `void jit_buf_free(JitBuf *b)`
- `jit_buf_reset` (line 56) `void jit_buf_reset(JitBuf *b)`
- `jit_buf_failed` (line 61) `int jit_buf_failed(const JitBuf *b)`
- `emit_grow` (line 67) `static void emit_grow(JitBuf *b, size_t need)`
- `emit8` (line 84) `void emit8(JitBuf *b, uint8_t v)`
- `emit16` (line 89) `void emit16(JitBuf *b, uint16_t v)`
- `emit32` (line 94) `void emit32(JitBuf *b, uint32_t v)`
- `emit64` (line 99) `void emit64(JitBuf *b, uint64_t v)`
- `emit_bytes` (line 104) `void emit_bytes(JitBuf *b, const void *data, size_t len)`
- `emit_rex` (line 114) `void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b)` - *emit_grow(b, 8); if (!b->failed) { memcpy(b->code + b->size, &v, 8); b->size += 8; } } void emit_bytes(JitBuf *b, const void *data, size_t len) { emit_grow(b, len); if (!b->failed) { memcpy(b->code + b->size, data, len); b->size += len; } } /* ------------------------------------------------------------------ /*  Internal encoding helpers /* ------------------------------------------------------------------ /* REX prefix: 0100 WRXB*
- `emit_modrm` (line 119) `void emit_modrm(JitBuf *b, int mod, int reg, int rm)` - *emit_grow(b, len); if (!b->failed) { memcpy(b->code + b->size, data, len); b->size += len; } } /* ------------------------------------------------------------------ /*  Internal encoding helpers /* ------------------------------------------------------------------ /* REX prefix: 0100 WRXB void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b) { emit8(buf, (uint8_t)(0x40 | (w << 3) | (r << 2) | (x << 1) | rex_b)); } /* ModRM byte*
- `emit_modrm_disp32` (line 124) `static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp)` - */*  Internal encoding helpers /* ------------------------------------------------------------------ /* REX prefix: 0100 WRXB void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b) { emit8(buf, (uint8_t)(0x40 | (w << 3) | (r << 2) | (x << 1) | rex_b)); } /* ModRM byte void emit_modrm(JitBuf *b, int mod, int reg, int rm) { emit8(b, (uint8_t)((mod << 6) | ((reg & 7) << 3) | (rm & 7))); } /* ModRM + disp32*
- `emit_rex_op_modrm` (line 130) `static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm)` - *} /* ModRM byte void emit_modrm(JitBuf *b, int mod, int reg, int rm) { emit8(b, (uint8_t)((mod << 6) | ((reg & 7) << 3) | (rm & 7))); } /* ModRM + disp32 static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp) { emit_modrm(b, 2, reg, rm); emit32(b, (uint32_t)disp); } /* REX.W + opcode + ModRM(reg, r/m) -- 3-byte core for reg,reg ops*
- `emit_sib` (line 137) `static void emit_sib(JitBuf *b, int scale, int index, int base)` - */* ModRM + disp32 static void emit_modrm_disp32(JitBuf *b, int reg, int rm, int32_t disp) { emit_modrm(b, 2, reg, rm); emit32(b, (uint32_t)disp); } /* REX.W + opcode + ModRM(reg, r/m) -- 3-byte core for reg,reg ops static void emit_rex_op_modrm(JitBuf *b, uint8_t opc, int reg, int rm) { emit_rex(b, 1, reg_high3(reg), 0, reg_high3(rm)); emit8(b, opc); emit_modrm(b, 3, reg, rm); } /* SIB byte*
- `emit_mov_reg_imm64` (line 145) `void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm)`
- `emit_mov_reg_imm32` (line 152) `void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- `emit_mov_reg_reg` (line 165) `void emit_mov_reg_reg(JitBuf *b, int dst, int src)`
- `emit_mov_reg_mem` (line 171) `void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp)`
- `emit_mov_mem_reg` (line 178) `void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src)`
- `emit_movzx_reg_mem8` (line 185) `void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp)`
- `emit_movzx_reg_mem16` (line 192) `void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp)`
- `emit_movsx_reg_mem32` (line 199) `void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp)`
- `emit_mov32_reg_mem` (line 206) `void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp)`
- `emit_mov32_mem_reg` (line 214) `void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src)`
- `emit_lea_sib` (line 222) `void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp)`
- `emit_mov_reg_sib` (line 259) `void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale)`
- `emit_mov_sib_reg` (line 267) `void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src)`
- `emit_push` (line 279) `void emit_push(JitBuf *b, int reg)`
- `emit_pop` (line 285) `void emit_pop(JitBuf *b, int reg)`
- `emit_add_reg_reg` (line 295) `void emit_add_reg_reg(JitBuf *b, int dst, int src)`
- `emit_add_reg_imm32` (line 299) `void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- `emit_sub_reg_reg` (line 308) `void emit_sub_reg_reg(JitBuf *b, int dst, int src)`
- `emit_sub_reg_imm32` (line 312) `void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm)`
- `emit_imul_reg_reg` (line 320) `void emit_imul_reg_reg(JitBuf *b, int dst, int src)`
- `emit_idiv_reg` (line 327) `void emit_idiv_reg(JitBuf *b, int divisor)`
- `emit_div_reg` (line 334) `void emit_div_reg(JitBuf *b, int divisor)`
- `emit_cqo` (line 341) `void emit_cqo(JitBuf *b)`
- `emit_neg_reg` (line 347) `void emit_neg_reg(JitBuf *b, int reg)`
- `emit_inc_reg` (line 354) `void emit_inc_reg(JitBuf *b, int reg)`
- `emit_dec_reg` (line 361) `void emit_dec_reg(JitBuf *b, int reg)`
- `emit_and_reg_imm32` (line 372) `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm)`
- `emit_and_reg_reg` (line 380) `void emit_and_reg_reg(JitBuf *b, int dst, int src)`
- `emit_or_reg_reg` (line 384) `void emit_or_reg_reg(JitBuf *b, int dst, int src)`
- `emit_xor_reg_reg` (line 388) `void emit_xor_reg_reg(JitBuf *b, int dst, int src)`
- `emit_not_reg` (line 392) `void emit_not_reg(JitBuf *b, int reg)`
- `emit_shl_reg_cl` (line 399) `void emit_shl_reg_cl(JitBuf *b, int reg)`
- `emit_shr_reg_cl` (line 406) `void emit_shr_reg_cl(JitBuf *b, int reg)`
- `emit_sar_reg_cl` (line 413) `void emit_sar_reg_cl(JitBuf *b, int reg)`
- `emit_xor_reg_self` (line 420) `void emit_xor_reg_self(JitBuf *b, int reg)`
- `emit_cmp_reg_reg` (line 430) `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg)`
- `emit_test_reg_reg` (line 435) `void emit_test_reg_reg(JitBuf *buf, int a, int breg)`
- `emit_setcc` (line 440) `void emit_setcc(JitBuf *b, int cc, int dst)`
- `emit_movzx_reg_reg8` (line 449) `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src)`
- `emit_jmp_rel32` (line 460) `size_t emit_jmp_rel32(JitBuf *b, int32_t rel)`
- `emit_jcc_rel32` (line 467) `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel)`
- `emit_jmp_buf` (line 475) `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p)`
- `emit_jcc_buf` (line 487) `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p)`
- `jit_apply_patches` (line 500) `void jit_apply_patches(JitBuf *b, const JitPatches *p)`
- `emit_call_rel32` (line 512) `size_t emit_call_rel32(JitBuf *b, int32_t rel)`
- `emit_call_reg` (line 519) `void emit_call_reg(JitBuf *b, int reg)`
- `emit_ret` (line 527) `void emit_ret(JitBuf *b)`
- `emit_syscall` (line 535) `void emit_syscall(JitBuf *b)`
- `emit_int3` (line 540) `void emit_int3(JitBuf *b)`
- `emit_nop` (line 544) `void emit_nop(JitBuf *b)`
- `emit_call_abs` (line 552) `void emit_call_abs(JitBuf *b, void *func, int scratch)`
- `emit_mov_mem_imm8` (line 561) `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm)`
- `emit_mov_mem_imm32` (line 569) `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm)`

**Macros:**
- `JIT_BUF_ALLOC` (line 26) `#define JIT_BUF_ALLOC(sz)`
- `JIT_BUF_FREE` (line 27) `#define JIT_BUF_FREE(p, sz)`
- `JIT_BUF_ALLOC` (line 29) `#define JIT_BUF_ALLOC(sz)`
- `JIT_BUF_FREE` (line 31) `#define JIT_BUF_FREE(p, sz)`
- `JIT_BUF_FAILED` (line 32) `#define JIT_BUF_FAILED`

#### `cvm_ops.c`
**Path:** `cvm2/cvm_ops.c`

**Functions:**
- `cvm_op_info` (line 72) `const CvmOpInfo *cvm_op_info(uint8_t opcode)`
- `cvm_op_name` (line 78) `const char *cvm_op_name(uint8_t opcode)`
- `cvm_ops_r8` (line 83) `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out)`
- `cvm_ops_ru32` (line 89) `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off)`
- `cvm_ops_ri32` (line 97) `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off)`
- `cvm_ops_ri64` (line 101) `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off)`

**Macros:**
- `OP_INFOS_LEN` (line 70) `#define OP_INFOS_LEN`

#### `cvm_val_main.c`
**Path:** `cvm2/cvm_val_main.c`

**Functions:**
- `val_err` (line 56) `static void val_err(ValCtx *ctx, const char *what)`
- `val_fun_err` (line 61) `static void val_fun_err(FuncCtx *fc, const char *what)`
- `code_of` (line 68) `static const uint8_t *code_of(const CvmModuleView *v)`
- `q_push` (line 72) `static void q_push(FuncCtx *fc, size_t off)`
- `q_pop` (line 81) `static size_t q_pop(FuncCtx *fc)`
- `dr_merge` (line 88) `static int dr_merge(DepthRange *d, int32_t lo2, int32_t hi2)`
- `stack_effect` (line 103) `static int stack_effect(const CvmModuleView *v, size_t off, uint8_t op,
                        S...`
- `check_static` (line 181) `static int check_static(FuncCtx *fc, size_t off, uint8_t op,
                        size_t next_ip)`
- `analyze_stack` (line 361) `static int analyze_stack(FuncCtx *fc)` - *Abstract-interpretation stack balance: each instruction start carries a [lo,hi] interval of possible stack depths; a required pop with lo==0 * is an underflow. Hi saturates at the stack capacity.*
- `check_function` (line 435) `static int check_function(FuncCtx *fc, size_t *insn_count)`
- `cmp_func` (line 450) `static int cmp_func(const void *a, const void *b)`
- `main` (line 456) `int main(int argc, char **argv)`

**Macros:**
- `CVM_VAL_MAX_FUNCS` (line 15) `#define CVM_VAL_MAX_FUNCS`
- `CVM_VAL_MAX_GLOBALS` (line 16) `#define CVM_VAL_MAX_GLOBALS`
- `CVM_VAL_MAX_NATIVES` (line 17) `#define CVM_VAL_MAX_NATIVES`
- `CVM_VAL_MAX_CODE` (line 18) `#define CVM_VAL_MAX_CODE`
- `CVM_VAL_MAX_LOCALS` (line 19) `#define CVM_VAL_MAX_LOCALS`
- `CVM_VAL_MAX_ARGS` (line 20) `#define CVM_VAL_MAX_ARGS`
- `CVM_VAL_STACK_CAP` (line 25) `#define CVM_VAL_STACK_CAP`
- `CVM_VAL_WIDEN_BOUND` (line 30) `#define CVM_VAL_WIDEN_BOUND`
- `CVM_VAL_MAX_SARGS` (line 31) `#define CVM_VAL_MAX_SARGS`

**Structs:**
- `DepthRange` (line 33)
- `ValCtx` (line 38)
- `FuncCtx` (line 45)
- `StackEffect` (line 97) - *Stack effect of one instruction on the interval [lo,hi]: * required pops, then the net deltas.*

#### `cvm_view.c`
**Path:** `cvm2/cvm_view.c`

**Functions:**
- `rl32` (line 9) `static uint32_t rl32(const uint8_t *p)`
- `rl16` (line 14) `static uint32_t rl16(const uint8_t *p)`
- `cvm_view_strerror` (line 18) `const char *cvm_view_strerror(int error_code)`
- `cvm_view_open` (line 29) `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size)`
- `cvm_view_func` (line 72) `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i)`
- `cvm_view_string` (line 78) `const char *cvm_view_string(const CvmModuleView *v, uint32_t off)`
- `cvm_view_func_name` (line 87) `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi,
                             ...`
- `cvm_view_func_region` (line 108) `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi,
                         size_t *be...`

#### `gen_fib_cvm.c`
**Path:** `cvm2/gen_fib_cvm.c`

**Functions:**
- `emit_byte` (line 21) `static void emit_byte(uint8_t b)`
- `emit_u32` (line 30) `static void emit_u32(uint32_t v)`
- `emit_i32` (line 37) `static void emit_i32(int32_t v)`
- `patch_i32` (line 39) `static void patch_i32(size_t pos, int32_t val)`
- `write_le32` (line 46) `static void write_le32(uint8_t *p, uint32_t v)`
- `emit_global_inc` (line 53) `static void emit_global_inc(void)`
- `main` (line 64) `int main(int argc, char *argv[])`

**Macros:**
- `FIB_N` (line 13) `#define FIB_N`
- `EXPECTED_FIB10` (line 14) `#define EXPECTED_FIB10`
- `EXPECTED_CALLS` (line 15) `#define EXPECTED_CALLS`

#### `gen_minimal.c`
**Path:** `cvm2/gen_minimal.c`

**Functions:**
- `emit_byte` (line 14) `static void emit_byte(uint8_t b)`
- `emit_u32` (line 21) `static void emit_u32(uint32_t v)`
- `write_le32` (line 25) `static void write_le32(uint8_t *p, uint32_t v)`
- `main` (line 30) `int main(void)`

#### `gen_fib_cvm.c`
**Path:** `gen_fib_cvm.c`

**Functions:**
- `add_string` (line 24) `static uint32_t add_string(const char *s)`
- `main` (line 36) `int main(void)`
- `fib` (line 7) `* return fib(n-1) + fib(n-2);`

### H (8 files)

#### `cvm.h`
**Path:** `cvm.h`

**Imported by:** `cvm.c`, `cvm_dbg_main.c`, `cvm_jit.h`, `cvm_jit_help.h`

**Functions:**
- `cvm_create` (line 215) `CVM *cvm_create(void);` - */* Heap (bump allocator for simplicity) uint8_t    *heap; size_t      heap_used; size_t      heap_size; /* Stats / debug uint64_t    instr_count; int         running; int         trace; } CVM; /* ------------------------------------------------------------------ /*  Public API /* ------------------------------------------------------------------*
- `cvm_destroy` (line 216) `void cvm_destroy(CVM *vm);`
- `cvm_load_module` (line 217) `int cvm_load_module(CVM *vm, const char *path);`
- `cvm_load_module_mem` (line 218) `int cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name);`
- `cvm_run` (line 219) `int cvm_run(CVM *vm, const char *entry_name);`
- `cvm_call` (line 220) `int cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args);`
- `cvm_emit_byte` (line 223) `void cvm_emit_byte(uint8_t **buf, size_t *cap, size_t *len, uint8_t b);` - *int         trace; } CVM; /* ------------------------------------------------------------------ /*  Public API /* ------------------------------------------------------------------ CVM        *cvm_create(void); void        cvm_destroy(CVM *vm); int         cvm_load_module(CVM *vm, const char *path); int         cvm_load_module_mem(CVM *vm, const uint8_t *data, size_t size, const char *name); int         cvm_run(CVM *vm, const char *entry_name); int         cvm_call(CVM *vm, int module_idx, int func_idx, int argc, uint64_t *args); /* Helpers used by the backend emitter*
- `cvm_emit_i16` (line 224) `void cvm_emit_i16 (uint8_t **buf, size_t *cap, size_t *len, int16_t v);`
- `cvm_emit_i32` (line 225) `void cvm_emit_i32 (uint8_t **buf, size_t *cap, size_t *len, int32_t v);`
- `cvm_emit_i64` (line 226) `void cvm_emit_i64 (uint8_t **buf, size_t *cap, size_t *len, int64_t v);`
- `cvm_emit_u16` (line 227) `void cvm_emit_u16 (uint8_t **buf, size_t *cap, size_t *len, uint16_t v);`

**Macros:**
- `CVM_H` (line 8) `#define CVM_H`
- `CVM_MAGIC` (line 22) `#define CVM_MAGIC`
- `CVM_VERSION` (line 23) `#define CVM_VERSION`
- `CVM_STACK_SIZE` (line 155) `#define CVM_STACK_SIZE`
- `CVM_FRAME_DEPTH` (line 156) `#define CVM_FRAME_DEPTH`
- `CVM_HEAP_SIZE` (line 157) `#define CVM_HEAP_SIZE`
- `CVM_MAX_MODULES` (line 158) `#define CVM_MAX_MODULES`
- `CVM_MAX_NATIVES` (line 159) `#define CVM_MAX_NATIVES`

**Structs:**
- `CVM_Module` (line 169)
- `CVM_Header` (line 107) - */* Heap OP_ALLOC        = 0x80,   /* size on stack → ptr OP_FREE         = 0x81, /* Syscalls / misc OP_SYSCALL      = 0x90,   /* nr, arg0..arg5 on stack (Linux x86-64 style) OP_PRINT_I64    = 0x91,   /* debug helper OP_HALT         = 0xFF }; /* ------------------------------------------------------------------ /*  Module format (on disk / in memory) /* ------------------------------------------------------------------ pragma pack(push, 1)*
- `CVM_FuncEntry` (line 126)
- `CVM_GlobalEntry` (line 136)
- `CVM_StringEntry` (line 142)
- `CVM_NativeEntry` (line 147)
- `CVM_Frame` (line 161)
- `CVM` (line 182)

**Type_Aliases:**
- `hdr` (line 168) `typedef struct CVM_Module { CVM_Header hdr;`

#### `cvm.h`
**Path:** `cvm2/cvm.h`

**Functions:**
- `cvm_create` (line 247) `CvmState *cvm_create(const CvmConfig *config);`
- `cvm_destroy` (line 248) `void cvm_destroy(CvmState *vm);`
- `cvm_load_module` (line 249) `int cvm_load_module(CvmState *vm, const uint8_t *data, size_t size);`
- `cvm_load_module_file` (line 250) `int cvm_load_module_file(CvmState *vm, const char *path);`
- `cvm_run` (line 251) `int cvm_run(CvmState *vm);`
- `cvm_continue` (line 252) `int cvm_continue(CvmState *vm);`
- `cvm_step` (line 253) `int cvm_step(CvmState *vm);`
- `cvm_exit_code` (line 254) `int64_t cvm_exit_code(const CvmState *vm);`
- `cvm_instruction_count` (line 255) `uint64_t cvm_instruction_count(const CvmState *vm);`
- `cvm_strerror` (line 256) `const char *cvm_strerror(int error_code);`
- `cvm_register_native` (line 258) `int cvm_register_native(CvmState *vm, const char *name, CvmNativeFn fn);`
- `cvm_set_args` (line 259) `int cvm_set_args(CvmState *vm, int argc, char **argv);`
- `cvm_heap_alloc` (line 260) `void *cvm_heap_alloc(CvmState *vm, size_t size);`
- `cvm_break_set` (line 262) `int cvm_break_set(CvmState *vm, size_t ip);`
- `cvm_break_clear` (line 263) `int cvm_break_clear(CvmState *vm, size_t ip);`
- `cvm_break_clear_all` (line 264) `void cvm_break_clear_all(CvmState *vm);`
- `cvm_break_hit` (line 265) `int cvm_break_hit(const CvmState *vm);`
- `cvm_profile_begin` (line 266) `int cvm_profile_begin(CvmState *vm);`
- `cvm_profile_end` (line 267) `void cvm_profile_end(CvmState *vm);`

**Macros:**
- `CVM_H` (line 28) `#define CVM_H`
- `CVM_MAGIC_0` (line 41) `#define CVM_MAGIC_0`
- `CVM_MAGIC_1` (line 42) `#define CVM_MAGIC_1`
- `CVM_MAGIC_2` (line 43) `#define CVM_MAGIC_2`
- `CVM_MAGIC_3` (line 44) `#define CVM_MAGIC_3`
- `CVM_VERSION_MAJOR` (line 45) `#define CVM_VERSION_MAJOR`
- `CVM_VERSION_MINOR` (line 46) `#define CVM_VERSION_MINOR`
- `CVM_MODULE_HEADER_SIZE` (line 47) `#define CVM_MODULE_HEADER_SIZE`
- `CVM_FUNC_ENTRY_SIZE` (line 48) `#define CVM_FUNC_ENTRY_SIZE`
- `CVM_GLOBAL_ENTRY_SIZE` (line 49) `#define CVM_GLOBAL_ENTRY_SIZE`
- `CVM_NATIVE_ENTRY_SIZE` (line 50) `#define CVM_NATIVE_ENTRY_SIZE`
- `CVM_STRING_ENTRY_SIZE` (line 51) `#define CVM_STRING_ENTRY_SIZE`
- `CVM_MAX_NARGS` (line 53) `#define CVM_MAX_NARGS`
- `CVM_MAX_SARGS` (line 54) `#define CVM_MAX_SARGS`
- `CVM_SHIFT_MASK` (line 55) `#define CVM_SHIFT_MASK`
- `CVM_SYS_READ` (line 56) `#define CVM_SYS_READ`
- `CVM_SYS_WRITE` (line 57) `#define CVM_SYS_WRITE`
- `CVM_SYS_EXIT` (line 58) `#define CVM_SYS_EXIT`
- `CVM_DATA_ARGC` (line 60) `#define CVM_DATA_ARGC`
- `CVM_DATA_ARGV` (line 61) `#define CVM_DATA_ARGV`
- `CVM_DATA_RSP` (line 62) `#define CVM_DATA_RSP`
- `CVM_DATA_RBP` (line 63) `#define CVM_DATA_RBP`
- `CVM_DATA_ARGS` (line 64) `#define CVM_DATA_ARGS`
- `CVM_DATA_RET` (line 65) `#define CVM_DATA_RET`
- `CVM_DATA_STACK_SIZE` (line 66) `#define CVM_DATA_STACK_SIZE`
- `CVM_DATA_STACK_BASE` (line 70) `#define CVM_DATA_STACK_BASE`
- `CVM_MAX_BREAKPOINTS` (line 203) `#define CVM_MAX_BREAKPOINTS`

**Structs:**
- `CvmFuncEntry` (line 154)
- `CvmGlobalEntry` (line 162)
- `CvmNativeEntry` (line 167)
- `CvmStringEntry` (line 171)
- `CvmConfig` (line 176)
- `CvmFrame` (line 189)
- `CvmNative` (line 198)
- `CvmBreakpoint` (line 205)
- `CvmState` (line 209)

**Variables:**
- `CvmOpcode` (line 38) `extern "C" { #endif #define CVM_MAGIC_0 0x43 #define CVM_MAGIC_1 0x56 #define CVM_MAGIC_2 0x4D #define CVM_MAGIC_3 0x04 #define CVM_VERSION_MAJOR 1 #define CVM_VERSION_MINOR 0 #define CVM_MODULE_HEADE` - *ifdef __cplusplus*

#### `cvm_dis.h`
**Path:** `cvm2/cvm_dis.h`

**Functions:**
- `cvm_dis_module` (line 23) `int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx);` - *#ifndef CVM_DIS_H #define CVM_DIS_H #include <stddef.h> #include <stdint.h> #include "cvm_view.h" #ifdef __cplusplus extern "C" { #endif typedef int (*CvmDisEmit)(void *ctx, const char *line); /* Whole module: header summary plus every function region.*
- `cvm_dis_function` (line 26) `int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end, CvmDisEmit emit, void *ctx);` - *#include <stddef.h> #include <stdint.h> #include "cvm_view.h" #ifdef __cplusplus extern "C" { #endif typedef int (*CvmDisEmit)(void *ctx, const char *line); /* Whole module: header summary plus every function region. int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx); /* One function region from begin up to end.*
- `cvm_dis_line` (line 31) `int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end, char *buf, size_t cap);` - *One instruction at code offset off (within [begin,end)). Returns the * instruction size, or -1 when it does not decode inside the region.*

**Macros:**
- `CVM_DIS_H` (line 10) `#define CVM_DIS_H`

#### `cvm_jit.h`
**Path:** `cvm2/cvm_jit.h`

**Functions:**
- `cvm_jit_create` (line 120) `CvmJitState *cvm_jit_create(void);` - */* IP-to-native mapping (shared across all functions) JitIpMap        ip_map[JIT_IP_MAP_SIZE]; size_t          ip_map_count; /* Profile counters for tier-up uint32_t        hot_threshold;          /* tier-up threshold uint32_t        warm_threshold;         /* tier-1 threshold } CvmJitState; /* ------------------------------------------------------------------ /*  JIT lifecycle /* ------------------------------------------------------------------ /* Create JIT state.  Call after cvm_create().*
- `cvm_jit_destroy` (line 123) `void cvm_jit_destroy(CvmJitState *jit);` - */* Profile counters for tier-up uint32_t        hot_threshold;          /* tier-up threshold uint32_t        warm_threshold;         /* tier-1 threshold } CvmJitState; /* ------------------------------------------------------------------ /*  JIT lifecycle /* ------------------------------------------------------------------ /* Create JIT state.  Call after cvm_create(). CvmJitState *cvm_jit_create(void); /* Destroy JIT state.  Call before cvm_destroy().*
- `cvm_jit_compile_module` (line 127) `int cvm_jit_compile_module(CvmState *vm);` - *Compile all functions in a loaded module to native code. * Returns CVM_OK on success.*
- `cvm_jit_compile_func` (line 130) `void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx);` - *Compile all functions in a loaded module to native code. * Returns CVM_OK on success. int cvm_jit_compile_module(CvmState *vm); /* Compile a single function.  Returns pointer to native code, or NULL.*
- `cvm_jit_lookup` (line 133) `void *cvm_jit_lookup(CvmState *vm, uint32_t func_idx);` - *Compile all functions in a loaded module to native code. * Returns CVM_OK on success. int cvm_jit_compile_module(CvmState *vm); /* Compile a single function.  Returns pointer to native code, or NULL. void *cvm_jit_compile_func(CvmState *vm, uint32_t func_idx); /* Look up native code for a function.  Returns pointer or NULL.*
- `cvm_jit_run` (line 142) `int cvm_jit_run(CvmState *vm);` - *Execute using the JIT.  Compiles all functions first, then dispatches to compiled code.  Falls back to interpreter for uncompiled functions. * Returns CVM_OK on success.*
- `returns` (line 145) `* returns (via RET) or encounters an error. */ void cvm_jit_exec_one(CvmState *vm);`
- `cvm_jit_stats` (line 153) `void cvm_jit_stats(const CvmState *vm);` - *Execute one compiled function at vm->ip.  Returns when the function * returns (via RET) or encounters an error. void cvm_jit_exec_one(CvmState *vm); /* ------------------------------------------------------------------ /*  Statistics /* ------------------------------------------------------------------ /* Print JIT compilation statistics to stderr.*
- `cvm_jit_dump` (line 159) `void cvm_jit_dump(const CvmState *vm);` - *returns (via RET) or encounters an error. void cvm_jit_exec_one(CvmState *vm); /* ------------------------------------------------------------------ /*  Statistics /* ------------------------------------------------------------------ /* Print JIT compilation statistics to stderr. void cvm_jit_stats(const CvmState *vm); #ifdef __cplusplus } #endif #endif /* CVM_JIT_H*

**Macros:**
- `CVM_JIT_H` (line 15) `#define CVM_JIT_H`
- `JIT_REG_VM` (line 45) `#define JIT_REG_VM`
- `JIT_REG_SLOTS` (line 46) `#define JIT_REG_SLOTS`
- `JIT_REG_SP` (line 47) `#define JIT_REG_SP`
- `JIT_REG_FRAMES` (line 48) `#define JIT_REG_FRAMES`
- `JIT_REG_FRAME` (line 49) `#define JIT_REG_FRAME`
- `JIT_SCRATCH1` (line 52) `#define JIT_SCRATCH1`
- `JIT_SCRATCH2` (line 53) `#define JIT_SCRATCH2`
- `JIT_SCRATCH3` (line 54) `#define JIT_SCRATCH3`
- `JIT_SCRATCH4` (line 55) `#define JIT_SCRATCH4`
- `JIT_SCRATCH5` (line 56) `#define JIT_SCRATCH5`
- `JIT_MAX_FUNCS` (line 93) `#define JIT_MAX_FUNCS`
- `JIT_IP_MAP_SIZE` (line 94) `#define JIT_IP_MAP_SIZE`

**Structs:**
- `JitFuncEntry` (line 72)
- `JitIpMap` (line 84)
- `CvmJitState` (line 96)

**Variables:**
- `JitTier` (line 22) `extern "C" { #endif /* ------------------------------------------------------------------ */ /* Register assignment for JIT-compiled code */ /* --------------------------------------------------------` - *ifdef __cplusplus*

#### `cvm_jit_help.h`
**Path:** `cvm2/cvm_jit_help.h`

**Functions:**
- `cvm_jit_offsets_init` (line 44) `void cvm_jit_offsets_init(CvmJitOffsets *off);` - *Compute and cache all field offsets.  Must be called once before * any JIT compilation begins.*
- `cvm_jit_func_enter` (line 52) `uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx);` - *Called at JIT function entry to sync interpreter state. * Returns the code pointer for the function.*
- `cvm_jit_func_leave` (line 55) `void cvm_jit_func_leave(CvmState *vm);` - *Called at JIT function entry to sync interpreter state. * Returns the code pointer for the function. uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx); /* Called at JIT function exit to sync interpreter state back.*
- `cvm_jit_call` (line 66) `int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc);` - *Execute OP_CALL: push a new frame, copy arguments from the operand stack into the new frame's locals, and set vm->ip to the callee. Returns 0 on success, non-zero error code on failure. On success, the JIT must jump to vm->ip (the callee's code). * On failure, vm->running is set to 0 and vm->exit_code is set.*
- `to` (line 70) `* Returns 0 if there is a caller to return to (vm->ip is set). * Returns 1 if this was the entry frame (vm->running = 0, done). */ int cvm_jit_ret(CvmState *vm, uint64_t retval);`
- `cvm_jit_call_native` (line 77) `int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc);` - *Execute OP_CALL_NATIVE: resolve the native function by index, pop arguments from the operand stack, call the host function, * and push the result.  Returns 0 on success.*
- `region` (line 84) `* region (heap, globals, string pool, or any frame's locals). * Returns 1 if valid, 0 if invalid. */ int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size);`
- `cvm_jit_alloc` (line 94) `uint64_t cvm_jit_alloc(CvmState *vm, size_t size);` - *Bump-allocate 'size' bytes from the CVM heap. * Returns the heap pointer on success, 0 on exhaustion.*
- `cvm_jit_syscall` (line 103) `int cvm_jit_syscall(CvmState *vm, uint8_t syscall_nr, uint8_t argc);` - *Execute a Linux-style syscall.  Pops 'argc' arguments from the operand stack, dispatches by syscall number, and pushes the result. * Returns 0 on success.  On exit syscall, vm->running is set to 0.*
- `cvm_jit_error` (line 112) `void cvm_jit_error(CvmState *vm, int error_code);` - *Set an error code and terminate the VM.  This is called when a JIT-compiled function detects an unrecoverable error (bad address, * stack overflow, etc.).  Sets vm->running = 0 and vm->exit_code.*

**Macros:**
- `CVM_JIT_HELP_H` (line 12) `#define CVM_JIT_HELP_H`

**Structs:**
- `CvmJitOffsets` (line 22) - *Register offsets into CvmState, used by JIT-compiled code for * direct field access.  These are computed once at JIT init time.*

**Variables:**
- `slots` (line 17) `extern "C" { #endif /* Register offsets into CvmState, used by JIT-compiled code for * direct field access. These are computed once at JIT init time. */ typedef struct { size_t slots;` - *ifdef __cplusplus*

#### `cvm_jit_x86.h`
**Path:** `cvm2/cvm_jit_x86.h`

**Functions:**
- `reg_needs_rex` (line 80) `static inline int reg_needs_rex(int r)` - *int   jit_buf_failed(const JitBuf *b); /* ------------------------------------------------------------------ /*  Byte emission (little-endian) /* ------------------------------------------------------------------ void  emit8(JitBuf *b, uint8_t v); void  emit16(JitBuf *b, uint16_t v); void  emit32(JitBuf *b, uint32_t v); void  emit64(JitBuf *b, uint64_t v); void  emit_bytes(JitBuf *b, const void *data, size_t len); /* ------------------------------------------------------------------ /*  Register checks /* ------------------------------------------------------------------*
- `reg_high3` (line 81) `static inline int reg_high3(int r)`
- `jit_buf_init` (line 63) `void jit_buf_init(JitBuf *b, size_t initial_cap);` - *size_t patch_off;    /* offset in buf->code where rel32 lives size_t target;       /* absolute target offset in the same buffer } JitPatch; #define JIT_MAX_PATCHES 8192 typedef struct { JitPatch patches[JIT_MAX_PATCHES]; size_t   count; } JitPatches; /* ------------------------------------------------------------------ /*  Buffer lifecycle /* ------------------------------------------------------------------*
- `jit_buf_free` (line 64) `void jit_buf_free(JitBuf *b);`
- `jit_buf_reset` (line 65) `void jit_buf_reset(JitBuf *b);`
- `jit_buf_failed` (line 66) `int jit_buf_failed(const JitBuf *b);`
- `emit8` (line 71) `void emit8(JitBuf *b, uint8_t v);` - *size_t   count; } JitPatches; /* ------------------------------------------------------------------ /*  Buffer lifecycle /* ------------------------------------------------------------------ void  jit_buf_init(JitBuf *b, size_t initial_cap); void  jit_buf_free(JitBuf *b); void  jit_buf_reset(JitBuf *b); int   jit_buf_failed(const JitBuf *b); /* ------------------------------------------------------------------ /*  Byte emission (little-endian) /* ------------------------------------------------------------------*
- `emit16` (line 72) `void emit16(JitBuf *b, uint16_t v);`
- `emit32` (line 73) `void emit32(JitBuf *b, uint32_t v);`
- `emit64` (line 74) `void emit64(JitBuf *b, uint64_t v);`
- `emit_bytes` (line 75) `void emit_bytes(JitBuf *b, const void *data, size_t len);`
- `emit_mov_reg_imm64` (line 88) `void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm);` - *void  emit64(JitBuf *b, uint64_t v); void  emit_bytes(JitBuf *b, const void *data, size_t len); /* ------------------------------------------------------------------ /*  Register checks /* ------------------------------------------------------------------ static inline int reg_needs_rex(int r) { return r >= X8; } static inline int reg_high3(int r) { return (r >> 3) & 1; } /* ------------------------------------------------------------------ /*  Data movement /* ------------------------------------------------------------------ /* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64)*
- `emit_mov_reg_imm32` (line 91) `void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm);` - */* ------------------------------------------------------------------ /*  Register checks /* ------------------------------------------------------------------ static inline int reg_needs_rex(int r) { return r >= X8; } static inline int reg_high3(int r) { return (r >> 3) & 1; } /* ------------------------------------------------------------------ /*  Data movement /* ------------------------------------------------------------------ /* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64) void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm); /* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32)*
- `emit_mov_reg_reg` (line 94) `void emit_mov_reg_reg(JitBuf *b, int dst, int src);` - *static inline int reg_needs_rex(int r) { return r >= X8; } static inline int reg_high3(int r) { return (r >> 3) & 1; } /* ------------------------------------------------------------------ /*  Data movement /* ------------------------------------------------------------------ /* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64) void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm); /* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32) void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm); /* MOV r64, r64  (3 bytes: REX.W 89 /r)*
- `emit_mov_reg_mem` (line 97) `void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp);` - */* ------------------------------------------------------------------ /*  Data movement /* ------------------------------------------------------------------ /* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64) void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm); /* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32) void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm); /* MOV r64, r64  (3 bytes: REX.W 89 /r) void emit_mov_reg_reg(JitBuf *b, int dst, int src); /* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10)*
- `emit_mov_mem_reg` (line 100) `void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src);` - */* MOV r64, imm64  (10 bytes: REX.W B8+rd imm64) void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm); /* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32) void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm); /* MOV r64, r64  (3 bytes: REX.W 89 /r) void emit_mov_reg_reg(JitBuf *b, int dst, int src); /* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10) void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp); /* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10)*
- `emit_movzx_reg_mem8` (line 103) `void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp);` - */* MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32) void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm); /* MOV r64, r64  (3 bytes: REX.W 89 /r) void emit_mov_reg_reg(JitBuf *b, int dst, int src); /* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10) void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp); /* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10) void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src); /* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10)*
- `emit_movzx_reg_mem16` (line 106) `void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp);` - */* MOV r64, r64  (3 bytes: REX.W 89 /r) void emit_mov_reg_reg(JitBuf *b, int dst, int src); /* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10) void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp); /* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10) void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src); /* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10) void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp); /* MOVZX r64, word [base + disp32]  (4 bytes: REX.W 0F B7 /r mod=10)*
- `emit_movsx_reg_mem32` (line 109) `void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp);` - */* MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10) void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp); /* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10) void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src); /* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10) void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp); /* MOVZX r64, word [base + disp32]  (4 bytes: REX.W 0F B7 /r mod=10) void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp); /* MOVSX r64, dword [base + disp32]  (4 bytes: REX.W 63 /r mod=10)*
- `emit_mov32_reg_mem` (line 112) `void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp);` - */* MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10) void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src); /* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10) void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp); /* MOVZX r64, word [base + disp32]  (4 bytes: REX.W 0F B7 /r mod=10) void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp); /* MOVSX r64, dword [base + disp32]  (4 bytes: REX.W 63 /r mod=10) void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp); /* MOV r32, [base + disp32]  (zero-extends to r64, 6 bytes: 8B /r mod=10)*
- `emit_mov32_mem_reg` (line 115) `void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src);` - */* MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10) void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp); /* MOVZX r64, word [base + disp32]  (4 bytes: REX.W 0F B7 /r mod=10) void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp); /* MOVSX r64, dword [base + disp32]  (4 bytes: REX.W 63 /r mod=10) void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp); /* MOV r32, [base + disp32]  (zero-extends to r64, 6 bytes: 8B /r mod=10) void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp); /* MOV [base + disp32], r32  (6 bytes: 89 /r mod=10)*
- `emit_lea_sib` (line 121) `void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp);` - *LEA r64, [base + index*scale + disp] scale: 0=1, 1=2, 2=4, 3=8 If index == -1, encodes [base + disp] only.*
- `emit_mov_reg_sib` (line 126) `void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale);` - *MOV r64, [base + index*scale]  (no displacement) scale: 0=1, 1=2, 2=4, 3=8*
- `emit_mov_sib_reg` (line 129) `void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src);` - *MOV r64, [base + index*scale]  (no displacement) scale: 0=1, 1=2, 2=4, 3=8  void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale); /* MOV [base + index*scale], r64  (no displacement)*
- `emit_push` (line 136) `void emit_push(JitBuf *b, int reg);` - *MOV r64, [base + index*scale]  (no displacement) scale: 0=1, 1=2, 2=4, 3=8  void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale); /* MOV [base + index*scale], r64  (no displacement) void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src); /* ------------------------------------------------------------------ /*  Stack operations /* ------------------------------------------------------------------ /* PUSH r64 (1 or 2 bytes depending on register)*
- `emit_pop` (line 139) `void emit_pop(JitBuf *b, int reg);` - *void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale); /* MOV [base + index*scale], r64  (no displacement) void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src); /* ------------------------------------------------------------------ /*  Stack operations /* ------------------------------------------------------------------ /* PUSH r64 (1 or 2 bytes depending on register) void emit_push(JitBuf *b, int reg); /* POP r64*
- `emit_add_reg_reg` (line 146) `void emit_add_reg_reg(JitBuf *b, int dst, int src);` - */*  Stack operations /* ------------------------------------------------------------------ /* PUSH r64 (1 or 2 bytes depending on register) void emit_push(JitBuf *b, int reg); /* POP r64 void emit_pop(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Arithmetic /* ------------------------------------------------------------------ /* ADD r64, r64  (REX.W 01 /r)*
- `emit_add_reg_imm32` (line 149) `void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm);` - */* PUSH r64 (1 or 2 bytes depending on register) void emit_push(JitBuf *b, int reg); /* POP r64 void emit_pop(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Arithmetic /* ------------------------------------------------------------------ /* ADD r64, r64  (REX.W 01 /r) void emit_add_reg_reg(JitBuf *b, int dst, int src); /* ADD r64, imm32  (sign-extended)*
- `emit_sub_reg_reg` (line 152) `void emit_sub_reg_reg(JitBuf *b, int dst, int src);` - */* POP r64 void emit_pop(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Arithmetic /* ------------------------------------------------------------------ /* ADD r64, r64  (REX.W 01 /r) void emit_add_reg_reg(JitBuf *b, int dst, int src); /* ADD r64, imm32  (sign-extended) void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm); /* SUB r64, r64  (REX.W 29 /r)*
- `emit_sub_reg_imm32` (line 155) `void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm);` - */* ------------------------------------------------------------------ /*  Arithmetic /* ------------------------------------------------------------------ /* ADD r64, r64  (REX.W 01 /r) void emit_add_reg_reg(JitBuf *b, int dst, int src); /* ADD r64, imm32  (sign-extended) void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm); /* SUB r64, r64  (REX.W 29 /r) void emit_sub_reg_reg(JitBuf *b, int dst, int src); /* SUB r64, imm32*
- `emit_imul_reg_reg` (line 158) `void emit_imul_reg_reg(JitBuf *b, int dst, int src);` - */* ADD r64, r64  (REX.W 01 /r) void emit_add_reg_reg(JitBuf *b, int dst, int src); /* ADD r64, imm32  (sign-extended) void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm); /* SUB r64, r64  (REX.W 29 /r) void emit_sub_reg_reg(JitBuf *b, int dst, int src); /* SUB r64, imm32 void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm); /* IMUL r64, r64  (REX.W 0F AF /r)*
- `emit_idiv_reg` (line 162) `void emit_idiv_reg(JitBuf *b, int divisor);` - *IDIV r64  (divides RDX:RAX by r64, quotient in RAX, remainder in RDX) * Requires RDX=0 before unsigned, or use CQO for signed.*
- `emit_div_reg` (line 166) `void emit_div_reg(JitBuf *b, int divisor);` - *DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx).*
- `emit_cqo` (line 169) `void emit_cqo(JitBuf *b);` - *DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emit_div_reg(JitBuf *b, int divisor); /* CQO  (sign-extend RAX into RDX:RAX)*
- `emit_neg_reg` (line 172) `void emit_neg_reg(JitBuf *b, int reg);` - *DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emit_div_reg(JitBuf *b, int divisor); /* CQO  (sign-extend RAX into RDX:RAX) void emit_cqo(JitBuf *b); /* NEG r64  (REX.W F7 /3)*
- `emit_inc_reg` (line 175) `void emit_inc_reg(JitBuf *b, int reg);` - *DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emit_div_reg(JitBuf *b, int divisor); /* CQO  (sign-extend RAX into RDX:RAX) void emit_cqo(JitBuf *b); /* NEG r64  (REX.W F7 /3) void emit_neg_reg(JitBuf *b, int reg); /* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies)*
- `emit_dec_reg` (line 178) `void emit_dec_reg(JitBuf *b, int reg);` - *DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) * Requires RDX=0 before (xor edx,edx). void emit_div_reg(JitBuf *b, int divisor); /* CQO  (sign-extend RAX into RDX:RAX) void emit_cqo(JitBuf *b); /* NEG r64  (REX.W F7 /3) void emit_neg_reg(JitBuf *b, int reg); /* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies) void emit_inc_reg(JitBuf *b, int reg); /* DEC r64*
- `emit_and_reg_reg` (line 185) `void emit_and_reg_reg(JitBuf *b, int dst, int src);` - */* NEG r64  (REX.W F7 /3) void emit_neg_reg(JitBuf *b, int reg); /* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies) void emit_inc_reg(JitBuf *b, int reg); /* DEC r64 void emit_dec_reg(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Bitwise /* ------------------------------------------------------------------ /* AND r64, r64*
- `emit_or_reg_reg` (line 188) `void emit_or_reg_reg(JitBuf *b, int dst, int src);` - */* INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies) void emit_inc_reg(JitBuf *b, int reg); /* DEC r64 void emit_dec_reg(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Bitwise /* ------------------------------------------------------------------ /* AND r64, r64 void emit_and_reg_reg(JitBuf *b, int dst, int src); /* OR r64, r64*
- `emit_xor_reg_reg` (line 191) `void emit_xor_reg_reg(JitBuf *b, int dst, int src);` - */* DEC r64 void emit_dec_reg(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Bitwise /* ------------------------------------------------------------------ /* AND r64, r64 void emit_and_reg_reg(JitBuf *b, int dst, int src); /* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int dst, int src); /* XOR r64, r64*
- `emit_not_reg` (line 194) `void emit_not_reg(JitBuf *b, int reg);` - */* ------------------------------------------------------------------ /*  Bitwise /* ------------------------------------------------------------------ /* AND r64, r64 void emit_and_reg_reg(JitBuf *b, int dst, int src); /* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int dst, int src); /* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int dst, int src); /* NOT r64*
- `emit_shl_reg_cl` (line 197) `void emit_shl_reg_cl(JitBuf *b, int reg);` - */* AND r64, r64 void emit_and_reg_reg(JitBuf *b, int dst, int src); /* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int dst, int src); /* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int dst, int src); /* NOT r64 void emit_not_reg(JitBuf *b, int reg); /* SHL r64, CL  (shift left by CL)*
- `emit_shr_reg_cl` (line 200) `void emit_shr_reg_cl(JitBuf *b, int reg);` - */* OR r64, r64 void emit_or_reg_reg(JitBuf *b, int dst, int src); /* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int dst, int src); /* NOT r64 void emit_not_reg(JitBuf *b, int reg); /* SHL r64, CL  (shift left by CL) void emit_shl_reg_cl(JitBuf *b, int reg); /* SHR r64, CL  (logical shift right)*
- `emit_sar_reg_cl` (line 203) `void emit_sar_reg_cl(JitBuf *b, int reg);` - */* XOR r64, r64 void emit_xor_reg_reg(JitBuf *b, int dst, int src); /* NOT r64 void emit_not_reg(JitBuf *b, int reg); /* SHL r64, CL  (shift left by CL) void emit_shl_reg_cl(JitBuf *b, int reg); /* SHR r64, CL  (logical shift right) void emit_shr_reg_cl(JitBuf *b, int reg); /* SAR r64, CL  (arithmetic shift right)*
- `emit_xor_reg_self` (line 206) `void emit_xor_reg_self(JitBuf *b, int reg);` - */* NOT r64 void emit_not_reg(JitBuf *b, int reg); /* SHL r64, CL  (shift left by CL) void emit_shl_reg_cl(JitBuf *b, int reg); /* SHR r64, CL  (logical shift right) void emit_shr_reg_cl(JitBuf *b, int reg); /* SAR r64, CL  (arithmetic shift right) void emit_sar_reg_cl(JitBuf *b, int reg); /* XOR reg, reg (zero-idiom, 3 bytes)*
- `emit_cmp_reg_reg` (line 213) `void emit_cmp_reg_reg(JitBuf *buf, int a, int breg);` - */* SHR r64, CL  (logical shift right) void emit_shr_reg_cl(JitBuf *b, int reg); /* SAR r64, CL  (arithmetic shift right) void emit_sar_reg_cl(JitBuf *b, int reg); /* XOR reg, reg (zero-idiom, 3 bytes) void emit_xor_reg_self(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Comparison /* ------------------------------------------------------------------ /* CMP r64, r64  (REX.W 39 /r)*
- `emit_test_reg_reg` (line 216) `void emit_test_reg_reg(JitBuf *buf, int a, int breg);` - */* SAR r64, CL  (arithmetic shift right) void emit_sar_reg_cl(JitBuf *b, int reg); /* XOR reg, reg (zero-idiom, 3 bytes) void emit_xor_reg_self(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Comparison /* ------------------------------------------------------------------ /* CMP r64, r64  (REX.W 39 /r) void emit_cmp_reg_reg(JitBuf *buf, int a, int breg); /* TEST r64, r64  (REX.W 85 /r)*
- `emit_setcc` (line 219) `void emit_setcc(JitBuf *b, int cc, int dst);` - */* XOR reg, reg (zero-idiom, 3 bytes) void emit_xor_reg_self(JitBuf *b, int reg); /* ------------------------------------------------------------------ /*  Comparison /* ------------------------------------------------------------------ /* CMP r64, r64  (REX.W 39 /r) void emit_cmp_reg_reg(JitBuf *buf, int a, int breg); /* TEST r64, r64  (REX.W 85 /r) void emit_test_reg_reg(JitBuf *buf, int a, int breg); /* SETcc r/m8  (0F 9x /0)*
- `emit_jmp_rel32` (line 226) `size_t emit_jmp_rel32(JitBuf *b, int32_t rel);` - */* CMP r64, r64  (REX.W 39 /r) void emit_cmp_reg_reg(JitBuf *buf, int a, int breg); /* TEST r64, r64  (REX.W 85 /r) void emit_test_reg_reg(JitBuf *buf, int a, int breg); /* SETcc r/m8  (0F 9x /0) void emit_setcc(JitBuf *b, int cc, int dst); /* ------------------------------------------------------------------ /*  Control flow /* ------------------------------------------------------------------ /* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching*
- `emit_jcc_rel32` (line 229) `size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel);` - */* TEST r64, r64  (REX.W 85 /r) void emit_test_reg_reg(JitBuf *buf, int a, int breg); /* SETcc r/m8  (0F 9x /0) void emit_setcc(JitBuf *b, int cc, int dst); /* ------------------------------------------------------------------ /*  Control flow /* ------------------------------------------------------------------ /* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching size_t emit_jmp_rel32(JitBuf *b, int32_t rel); /* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching*
- `emit_jmp_buf` (line 232) `void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p);` - */* SETcc r/m8  (0F 9x /0) void emit_setcc(JitBuf *b, int cc, int dst); /* ------------------------------------------------------------------ /*  Control flow /* ------------------------------------------------------------------ /* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching size_t emit_jmp_rel32(JitBuf *b, int32_t rel); /* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel); /* JMP to absolute offset within the buffer (emits rel32, records patch)*
- `emit_jcc_buf` (line 235) `void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p);` - */* ------------------------------------------------------------------ /*  Control flow /* ------------------------------------------------------------------ /* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching size_t emit_jmp_rel32(JitBuf *b, int32_t rel); /* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel); /* JMP to absolute offset within the buffer (emits rel32, records patch) void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p); /* Jcc to absolute offset within the buffer*
- `jit_apply_patches` (line 238) `void jit_apply_patches(JitBuf *b, const JitPatches *p);` - */* JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching size_t emit_jmp_rel32(JitBuf *b, int32_t rel); /* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel); /* JMP to absolute offset within the buffer (emits rel32, records patch) void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p); /* Jcc to absolute offset within the buffer void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p); /* Apply all patches: for each patch, compute rel32 = target - (patch_off + 4)*
- `emit_call_rel32` (line 241) `size_t emit_call_rel32(JitBuf *b, int32_t rel);` - */* Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel); /* JMP to absolute offset within the buffer (emits rel32, records patch) void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p); /* Jcc to absolute offset within the buffer void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p); /* Apply all patches: for each patch, compute rel32 = target - (patch_off + 4) void jit_apply_patches(JitBuf *b, const JitPatches *p); /* CALL rel32  (E8 imm32)*
- `emit_call_reg` (line 244) `void emit_call_reg(JitBuf *b, int reg);` - */* JMP to absolute offset within the buffer (emits rel32, records patch) void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p); /* Jcc to absolute offset within the buffer void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p); /* Apply all patches: for each patch, compute rel32 = target - (patch_off + 4) void jit_apply_patches(JitBuf *b, const JitPatches *p); /* CALL rel32  (E8 imm32) size_t emit_call_rel32(JitBuf *b, int32_t rel); /* CALL r/m64  (FF /2, 2 bytes)*
- `emit_ret` (line 247) `void emit_ret(JitBuf *b);` - */* Jcc to absolute offset within the buffer void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p); /* Apply all patches: for each patch, compute rel32 = target - (patch_off + 4) void jit_apply_patches(JitBuf *b, const JitPatches *p); /* CALL rel32  (E8 imm32) size_t emit_call_rel32(JitBuf *b, int32_t rel); /* CALL r/m64  (FF /2, 2 bytes) void emit_call_reg(JitBuf *b, int reg); /* RET  (C3)*
- `emit_syscall` (line 254) `void emit_syscall(JitBuf *b);` - */* CALL rel32  (E8 imm32) size_t emit_call_rel32(JitBuf *b, int32_t rel); /* CALL r/m64  (FF /2, 2 bytes) void emit_call_reg(JitBuf *b, int reg); /* RET  (C3) void emit_ret(JitBuf *b); /* ------------------------------------------------------------------ /*  System /* ------------------------------------------------------------------ /* SYSCALL  (0F 05)*
- `emit_int3` (line 257) `void emit_int3(JitBuf *b);` - */* CALL r/m64  (FF /2, 2 bytes) void emit_call_reg(JitBuf *b, int reg); /* RET  (C3) void emit_ret(JitBuf *b); /* ------------------------------------------------------------------ /*  System /* ------------------------------------------------------------------ /* SYSCALL  (0F 05) void emit_syscall(JitBuf *b); /* INT3  (CC) -- debug breakpoint*
- `emit_nop` (line 260) `void emit_nop(JitBuf *b);` - */* RET  (C3) void emit_ret(JitBuf *b); /* ------------------------------------------------------------------ /*  System /* ------------------------------------------------------------------ /* SYSCALL  (0F 05) void emit_syscall(JitBuf *b); /* INT3  (CC) -- debug breakpoint void emit_int3(JitBuf *b); /* NOP  (90)*
- `emit_call_abs` (line 269) `void emit_call_abs(JitBuf *b, void *func, int scratch);` - *Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used.*
- `emit_and_reg_imm32` (line 272) `void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm);` - *Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used. void emit_call_abs(JitBuf *b, void *func, int scratch); /* AND r64, imm32*
- `emit_movzx_reg_reg8` (line 275) `void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src);` - *Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used. void emit_call_abs(JitBuf *b, void *func, int scratch); /* AND r64, imm32 void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm); /* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension*
- `emit_rex` (line 278) `void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b);` - *Emit a CALL to a C function pointer (trampoline-free, uses absolute call). Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used. void emit_call_abs(JitBuf *b, void *func, int scratch); /* AND r64, imm32 void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm); /* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src); /* REX prefix: exposed for inline asm emission*
- `emit_modrm` (line 281) `void emit_modrm(JitBuf *buf, int mod, int reg, int rm);` - *Loads the function address into a scratch register and calls it. * Clobbers: the scratch register used. void emit_call_abs(JitBuf *b, void *func, int scratch); /* AND r64, imm32 void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm); /* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src); /* REX prefix: exposed for inline asm emission void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b); /* ModRM byte: exposed for inline asm emission*
- `emit_mov_mem_imm8` (line 288) `void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm);` - */* MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src); /* REX prefix: exposed for inline asm emission void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b); /* ModRM byte: exposed for inline asm emission void emit_modrm(JitBuf *buf, int mod, int reg, int rm); /* ------------------------------------------------------------------ /*  Misc /* ------------------------------------------------------------------ /* MOV byte [base + disp], imm8  (REX.C6 /0)*
- `emit_mov_mem_imm32` (line 291) `void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm);` - */* REX prefix: exposed for inline asm emission void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b); /* ModRM byte: exposed for inline asm emission void emit_modrm(JitBuf *buf, int mod, int reg, int rm); /* ------------------------------------------------------------------ /*  Misc /* ------------------------------------------------------------------ /* MOV byte [base + disp], imm8  (REX.C6 /0) void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm); /* MOV qword [base + disp], imm32 (sign-extended)  (REX.W C7 /0)*

**Macros:**
- `CVM_JIT_X86_H` (line 10) `#define CVM_JIT_X86_H`
- `JIT_MAX_PATCHES` (line 53) `#define JIT_MAX_PATCHES`

**Structs:**
- `JitBuf` (line 40) - */* Condition codes for Jcc / SETcc enum { CC_O   = 0x0, CC_NO  = 0x1, CC_B   = 0x2, CC_AE  = 0x3, CC_E   = 0x4, CC_NE  = 0x5, CC_BE  = 0x6, CC_A   = 0x7, CC_S   = 0x8, CC_NS  = 0x9, CC_P   = 0xA, CC_NP  = 0xB, CC_L   = 0xC, CC_GE  = 0xD, CC_LE  = 0xE, CC_G   = 0xF }; /* Growable code buffer backed by mmap'd RWX memory*
- `JitPatch` (line 48) - *CC_P   = 0xA, CC_NP  = 0xB, CC_L   = 0xC, CC_GE  = 0xD, CC_LE  = 0xE, CC_G   = 0xF }; /* Growable code buffer backed by mmap'd RWX memory typedef struct { uint8_t *code; size_t   size;       /* current write offset size_t   capacity;   /* allocated size int      failed;     /* set on OOM or overflow } JitBuf; /* Forward patch entry for unresolved jumps*
- `JitPatches` (line 55)

#### `cvm_ops.h`
**Path:** `cvm2/cvm_ops.h`

**Functions:**
- `cvm_op_info` (line 38) `const CvmOpInfo *cvm_op_info(uint8_t opcode);` - *CVM_OPK_U32   = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL   = 6, CVM_OPK_U8U8  = 7 } CvmOpKind; typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for one opcode, or NULL when the opcode is not defined.*
- `cvm_op_name` (line 41) `const char *cvm_op_name(uint8_t opcode);` - *CVM_OPK_U8U8  = 7 } CvmOpKind; typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for one opcode, or NULL when the opcode is not defined. const CvmOpInfo *cvm_op_info(uint8_t opcode); /* Mnemonic for one opcode, or NULL when the opcode is not defined.*
- `cvm_ops_ri32` (line 44) `int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off);` - *typedef struct { uint8_t     opcode; uint8_t     kind; uint8_t     size; const char *name; } CvmOpInfo; /* Metadata for one opcode, or NULL when the opcode is not defined. const CvmOpInfo *cvm_op_info(uint8_t opcode); /* Mnemonic for one opcode, or NULL when the opcode is not defined. const char *cvm_op_name(uint8_t opcode); /* Decode helpers over a code buffer, little-endian as stored.*
- `cvm_ops_ri64` (line 45) `int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off);`
- `cvm_ops_ru32` (line 46) `uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off);`
- `cvm_ops_r8` (line 47) `int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out);`

**Macros:**
- `CVM_OPS_H` (line 10) `#define CVM_OPS_H`

**Structs:**
- `CvmOpInfo` (line 30)

**Variables:**
- `CvmOpKind` (line 16) `extern "C" { #endif typedef enum { CVM_OPK_NONE = 0, CVM_OPK_I8 = 1, CVM_OPK_I32 = 2, CVM_OPK_I64 = 3, CVM_OPK_U32 = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL = 6, CVM_OPK_U8U8 = 7 } CvmOpKind;` - *ifdef __cplusplus*

#### `cvm_view.h`
**Path:** `cvm2/cvm_view.h`

**Functions:**
- `cvm_view_open` (line 41) `int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size);` - *uint32_t       num_strings; uint32_t       code_size; uint32_t       string_pool_size; uint32_t       data_size; uint32_t       entry_func; size_t         func_off; size_t         global_off; size_t         native_off; size_t         string_off; size_t         code_off; size_t         pool_off; } CvmModuleView; /* Parse and validate the header plus all section extents.*
- `cvm_view_strerror` (line 44) `const char *cvm_view_strerror(int error_code);` - *uint32_t       data_size; uint32_t       entry_func; size_t         func_off; size_t         global_off; size_t         native_off; size_t         string_off; size_t         code_off; size_t         pool_off; } CvmModuleView; /* Parse and validate the header plus all section extents. int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size); /* Message for an error code returned by cvm_view_open.*
- `cvm_view_func` (line 46) `const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i);`
- `cvm_view_string` (line 50) `const char *cvm_view_string(const CvmModuleView *v, uint32_t off);` - *String from the pool, or NULL when the offset is outside it. The * pointer is only valid while the module data lives.*
- `cvm_view_func_name` (line 53) `const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi, char *fallback, size_t cap);` - *String from the pool, or NULL when the offset is outside it. The * pointer is only valid while the module data lives. const char *cvm_view_string(const CvmModuleView *v, uint32_t off); /* Function name from the pool; falls back to "func<N>" in fallback.*
- `cvm_view_func_region` (line 58) `int cvm_view_func_region(const CvmModuleView *v, uint32_t fi, size_t *begin, size_t *end);` - *Code region of a function: [*begin, *end) where *end is the next * function's code offset or the end of the code section.*

**Macros:**
- `CVM_VIEW_H` (line 9) `#define CVM_VIEW_H`

**Structs:**
- `CvmModuleView` (line 19)

**Variables:**
- `data` (line 16) `extern "C" { #endif typedef struct { const uint8_t *data;` - *ifdef __cplusplus*

### PY (1 files)

#### `gen_test.py`
**Path:** `cvm2/gen_test.py`
**File Doc:** *Generate a minimal .cvm that pushes 42 and halts. No function calls.*

**Functions:**
- `emit_byte` (line 7) `def emit_byte(b)`
- `emit_u32` (line 10) `def emit_u32(v)`

### SH (3 files)

#### `deepseek_bash_20260808_653f26.sh`
**Path:** `cvm2/deepseek_bash_20260808_653f26.sh`

*No symbols extracted*

#### `test.sh`
**Path:** `cvm2/test.sh`
**File Doc:** *CVM v2 toolchain suite: interpreter, disassembler, validator (including corrupted-module rejections) and the scripted debugger. Every check is a hard failure: a rejected module that validates, or a corrupted module that passes, fails the suite.*

**Functions:**
- `check` (line 13)
- `reject` (line 24)

#### `test.sh`
**Path:** `test.sh`

*No symbols extracted*
