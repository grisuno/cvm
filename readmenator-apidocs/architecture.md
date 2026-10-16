# cvm Architecture and Execution Flows

[Back to index](index.md)

## Architecture Overview

4 components stacked in 3 dependency tiers (weighted Eades-Lin-Smyth ordering: arrows point from dependent to dependency, top to bottom). Labels are import counts, thick arrows the top quartile; 1 transitively implied edges are omitted. Dashed red arrows are upward dependencies: the smallest set of imports that closes every cycle and breaks the layering. Cyan components hold entry points. Interactive version: `readmenator-apidocs/index.html#/flows`.

Upward dependencies to fix first: `cvm2: cvm_dbg_main` -> `cvm2: cvm_jit` (1 imports)

```mermaid
flowchart TB
    classDef cycle fill:#1f1530,stroke:#f472b6,color:#fce7f3,stroke-width:2px;
    classDef default fill:#111827,stroke:#38bdf8,color:#e5e7eb;
    subgraph lane_0["Tier 1 - entry / orchestration"]
        direction LR
        n_c2["cvm2: cvm_jit<br/>5 files, 87 symbols<br/>Core / utility"]:::cycle
        n_d_cvm2["cvm2<br/>1 files, 0 symbols<br/>Core / utility"]:::default
    end
    subgraph lane_1["Tier 2"]
        direction LR
        n_c1["cvm2: cvm_dbg_main<br/>5 files, 44 symbols<br/>Core / utility"]:::cycle
    end
    subgraph lane_2["Tier 3 - foundation"]
        direction LR
        n_c0["cvm2: cvm<br/>12 files, 430 symbols<br/>Core / utility"]:::default
    end
    n_c1 ==>|"2"| n_c0
    n_c2 ==>|"2"| n_c1
    n_c2 <-.-|"1 upward"| n_c1
    linkStyle 2 stroke:#f87171,stroke-width:2px;
    n_c2 ~~~ n_c1
    n_c1 ~~~ n_c0
```

---

## Execution Flows

Entry points are scored from `__main__` guards, `main` functions, entry-style names and files, and call-graph sources. Each flow walks resolved calls in call-site order (depth <= 4, <= 40 steps); numbers give the call order, dashed arrows revisit an already expanded callee, red arrows are recursion. Interactive version with zoom and per-node docs: `readmenator-apidocs/index.html#/flows`.

### `cvm.main`

`cvm.c:775`, score 11: `main` in a compiled-language file; entry-style name `main`.

Call tree:

```mermaid
flowchart LR
    classDef default fill:#111827,stroke:#38bdf8,color:#e5e7eb;
    classDef entry fill:#0e7490,stroke:#22d3ee,color:#ecfeff,stroke-width:2px;
    n_cvm_c__main["cvm.main<br/>void cvm_emit_i32(uint8_t **buf, size_t *cap,...<br/>cvm.c:775"]:::entry
    n_cvm_c__cvm_create["cvm.cvm_create<br/>(void)fd#59; (void)buf#59; (void)len#59; } push(vm, 0)...<br/>cvm.c:227"]:::default
    n_cvm_c__cvm_load_module["cvm.cvm_load_module<br/>cvm.c:337"]:::default
    n_cvm_c__cvm_load_module_mem["cvm.cvm_load_module_mem<br/>free(m-#gt;natives)#59; free(m-#gt;code)#59; free(m-#gt;stri...<br/>cvm.c:267"]:::default
    n_cvm_c__cvm_destroy["cvm.cvm_destroy<br/>cvm.c:244"]:::default
    n_cvm_c__cvm_run["cvm.cvm_run<br/>vm-#gt;running = 0#59; break#59; default: cvm_error(vm...<br/>cvm.c:700"]:::default
    n_cvm_c__push_frame["cvm.push_frame<br/>cvm_error(vm, #quot;operand stack underflow#quot;)#59; ret...<br/>cvm.c:102"]:::default
    n_cvm_c__cvm_error["cvm.cvm_error<br/>cvm.c — C Virtual Machine interpreter #35;includ...<br/>cvm.c:12"]:::default
    n_cvm_c__pop["cvm.pop<br/>cvm.c:86"]:::default
    n_cvm_c__interpret["cvm.interpret<br/>if (!buf || fread(buf, 1, (size_t)sz, f) != (...<br/>cvm.c:361"]:::default
    n_cvm_c__op_name["cvm.op_name<br/>cvm.c:22"]:::default
    n_cvm_c__push["cvm.push<br/>case OP_RET: return #quot;RET#quot;#59; case OP_RET_VOID:...<br/>cvm.c:78"]:::default
    n_cvm_c__peek["cvm.peek<br/>cvm.c:94"]:::default
    n_cvm_c__call_native["cvm.call_native<br/>if (has_retval) push(vm, ret)#59; vm-#gt;running =...<br/>cvm.c:175"]:::default
    n_cvm_c__pop_frame["cvm.pop_frame<br/>cvm.c:142"]:::default
    n_cvm_c__main -.->|"recursion"| n_cvm_c__main
    n_cvm_c__main -->|"1"| n_cvm_c__cvm_create
    n_cvm_c__cvm_create -.->|"recursion"| n_cvm_c__cvm_create
    n_cvm_c__main -->|"2"| n_cvm_c__cvm_load_module
    n_cvm_c__cvm_load_module -.->|"recursion"| n_cvm_c__cvm_load_module
    n_cvm_c__cvm_load_module -->|"1"| n_cvm_c__cvm_load_module_mem
    n_cvm_c__cvm_load_module_mem -.->|"recursion"| n_cvm_c__cvm_load_module_mem
    n_cvm_c__main -->|"3"| n_cvm_c__cvm_destroy
    n_cvm_c__cvm_destroy -.->|"recursion"| n_cvm_c__cvm_destroy
    n_cvm_c__main -->|"4"| n_cvm_c__cvm_run
    n_cvm_c__cvm_run -.->|"recursion"| n_cvm_c__cvm_run
    n_cvm_c__cvm_run -->|"1"| n_cvm_c__push_frame
    n_cvm_c__push_frame -->|"1"| n_cvm_c__cvm_error
    n_cvm_c__push_frame -->|"2"| n_cvm_c__pop
    n_cvm_c__pop -.-> n_cvm_c__cvm_error
    n_cvm_c__cvm_run -->|"2"| n_cvm_c__interpret
    n_cvm_c__interpret -.-> n_cvm_c__cvm_error
    n_cvm_c__interpret -->|"1"| n_cvm_c__op_name
    n_cvm_c__interpret -->|"2"| n_cvm_c__push
    n_cvm_c__push -.-> n_cvm_c__cvm_error
    n_cvm_c__interpret -->|"3"| n_cvm_c__peek
    n_cvm_c__interpret -.-> n_cvm_c__pop
    n_cvm_c__interpret -.-> n_cvm_c__push_frame
    n_cvm_c__interpret -->|"4"| n_cvm_c__call_native
    n_cvm_c__call_native -.-> n_cvm_c__cvm_error
    n_cvm_c__call_native -.-> n_cvm_c__pop
    n_cvm_c__call_native -.-> n_cvm_c__push
    n_cvm_c__interpret -->|"5"| n_cvm_c__pop_frame
    n_cvm_c__pop_frame -.-> n_cvm_c__pop
    n_cvm_c__pop_frame -.-> n_cvm_c__push
    linkStyle 0,2,4,6,8,10 stroke:#f87171,stroke-width:2px;
```

### `cvm.main`

`cvm2/cvm.c:1355`, score 11: `main` in a compiled-language file; entry-style name `main`.

Call tree:

```mermaid
flowchart LR
    classDef default fill:#111827,stroke:#38bdf8,color:#e5e7eb;
    classDef entry fill:#0e7490,stroke:#22d3ee,color:#ecfeff,stroke-width:2px;
    classDef external fill:#1a1530,stroke:#a78bfa,color:#ede9fe;
    n_cvm2_cvm_c__main["cvm.main<br/>if defined(CVM_STANDALONE) && !defined(CVM_NO...<br/>cvm.c:1355"]:::entry
    n_cvm2_cvm_c__cvm_config_default["cvm.cvm_config_default<br/>cvm.c:40"]:::default
    n_cvm2_cvm_c__cvm_create["cvm.cvm_create<br/>cvm.c:55"]:::default
    n_cvm2_cvm_c__xcal["cvm.xcal<br/>cvm.c:34"]:::default
    n_cvm2_cvm_jit_h__cvm_jit_create["cvm_jit.cvm_jit_create<br/>/* IP-to-native mapping (shared across all fu...<br/>cvm_jit.h:120"]:::external
    n_cvm2_cvm_c__cvm_destroy["cvm.cvm_destroy<br/>cvm.c:94"]:::default
    n_cvm2_cvm_jit_h__cvm_jit_destroy["cvm_jit.cvm_jit_destroy<br/>/* Profile counters for tier-up uint32_t hot_...<br/>cvm_jit.h:123"]:::external
    n_cvm2_cvm_c__cvm_load_module_file["cvm.cvm_load_module_file<br/>cvm.c:923"]:::default
    n_cvm2_cvm_c__xmal["cvm.xmal<br/>cvm.c:28"]:::default
    n_cvm2_cvm_c__cvm_load_module["cvm.cvm_load_module<br/>cvm.c:830"]:::default
    n_cvm2_cvm_c__cvm_free_module["cvm.cvm_free_module<br/>cvm.c:815"]:::default
    n_cvm2_cvm_c__register_defaults["cvm.register_defaults<br/>cvm.c:736"]:::default
    n_cvm2_cvm_c__cvm_register_native["cvm.cvm_register_native<br/>cvm.c:283"]:::default
    n_cvm2_cvm_c__rl32["cvm.rl32<br/>cvm_register_native(vm, #quot;fputc#quot;, native_fputc...<br/>cvm.c:788"]:::default
    n_cvm2_cvm_c__decompress_rle["cvm.decompress_rle<br/>cvm.c:793"]:::default
    n_cvm2_cvm_c__find_native["cvm.find_native<br/>cvm.c:294"]:::default
    n_cvm2_cvm_c__cvm_strerror["cvm.cvm_strerror<br/>cvm.c:113"]:::default
    n_cvm2_cvm_c__cvm_set_args["cvm.cvm_set_args<br/>cvm.c:250"]:::default
    n_cvm2_cvm_c__data_r64["cvm.data_r64<br/>cvm.c:244"]:::default
    n_cvm2_cvm_c__heap_alloc["cvm.heap_alloc<br/>cvm.c:227"]:::default
    n_cvm2_cvm_c__data_w64["cvm.data_w64<br/>cvm.c:239"]:::default
    n_cvm2_cvm_jit_h__cvm_jit_run["cvm_jit.cvm_jit_run<br/>Execute using the JIT.<br/>cvm_jit.h:142"]:::external
    n_cvm2_cvm_c__cvm_run["cvm.cvm_run<br/>cvm.c:952"]:::default
    n_cvm2_cvm_c__pop_frame["cvm.pop_frame<br/>cvm.c:196"]:::default
    n_cvm2_cvm_c__push_frame["cvm.push_frame<br/>cvm.c:183"]:::default
    n_cvm2_cvm_c__main -.->|"recursion"| n_cvm2_cvm_c__main
    n_cvm2_cvm_c__main -->|"1"| n_cvm2_cvm_c__cvm_config_default
    n_cvm2_cvm_c__cvm_config_default -.->|"recursion"| n_cvm2_cvm_c__cvm_config_default
    n_cvm2_cvm_c__main -->|"2"| n_cvm2_cvm_c__cvm_create
    n_cvm2_cvm_c__cvm_create -.->|"recursion"| n_cvm2_cvm_c__cvm_create
    n_cvm2_cvm_c__cvm_create -.-> n_cvm2_cvm_c__cvm_config_default
    n_cvm2_cvm_c__cvm_create -->|"1"| n_cvm2_cvm_c__xcal
    n_cvm2_cvm_c__main -->|"3"| n_cvm2_cvm_jit_h__cvm_jit_create
    n_cvm2_cvm_jit_h__cvm_jit_create -.->|"recursion"| n_cvm2_cvm_jit_h__cvm_jit_create
    n_cvm2_cvm_c__main -->|"4"| n_cvm2_cvm_c__cvm_destroy
    n_cvm2_cvm_c__cvm_destroy -.->|"recursion"| n_cvm2_cvm_c__cvm_destroy
    n_cvm2_cvm_c__cvm_destroy -->|"1"| n_cvm2_cvm_jit_h__cvm_jit_destroy
    n_cvm2_cvm_jit_h__cvm_jit_destroy -.->|"recursion"| n_cvm2_cvm_jit_h__cvm_jit_destroy
    n_cvm2_cvm_c__main -->|"5"| n_cvm2_cvm_c__cvm_load_module_file
    n_cvm2_cvm_c__cvm_load_module_file -.->|"recursion"| n_cvm2_cvm_c__cvm_load_module_file
    n_cvm2_cvm_c__cvm_load_module_file -->|"1"| n_cvm2_cvm_c__xmal
    n_cvm2_cvm_c__cvm_load_module_file -->|"2"| n_cvm2_cvm_c__cvm_load_module
    n_cvm2_cvm_c__cvm_load_module -.->|"recursion"| n_cvm2_cvm_c__cvm_load_module
    n_cvm2_cvm_c__cvm_load_module -->|"1"| n_cvm2_cvm_c__cvm_free_module
    n_cvm2_cvm_c__cvm_load_module -->|"2"| n_cvm2_cvm_c__register_defaults
    n_cvm2_cvm_c__register_defaults -->|"1"| n_cvm2_cvm_c__cvm_register_native
    n_cvm2_cvm_c__cvm_load_module -->|"3"| n_cvm2_cvm_c__rl32
    n_cvm2_cvm_c__cvm_load_module -.-> n_cvm2_cvm_c__xcal
    n_cvm2_cvm_c__cvm_load_module -->|"4"| n_cvm2_cvm_c__decompress_rle
    n_cvm2_cvm_c__cvm_load_module -.-> n_cvm2_cvm_c__xmal
    n_cvm2_cvm_c__cvm_load_module -->|"5"| n_cvm2_cvm_c__find_native
    n_cvm2_cvm_c__main -->|"6"| n_cvm2_cvm_c__cvm_strerror
    n_cvm2_cvm_c__cvm_strerror -.->|"recursion"| n_cvm2_cvm_c__cvm_strerror
    n_cvm2_cvm_c__main -->|"7"| n_cvm2_cvm_c__cvm_set_args
    n_cvm2_cvm_c__cvm_set_args -.->|"recursion"| n_cvm2_cvm_c__cvm_set_args
    n_cvm2_cvm_c__cvm_set_args -->|"1"| n_cvm2_cvm_c__data_r64
    n_cvm2_cvm_c__cvm_set_args -->|"2"| n_cvm2_cvm_c__heap_alloc
    n_cvm2_cvm_c__cvm_set_args -->|"3"| n_cvm2_cvm_c__data_w64
    n_cvm2_cvm_c__main -->|"8"| n_cvm2_cvm_jit_h__cvm_jit_run
    n_cvm2_cvm_jit_h__cvm_jit_run -.->|"recursion"| n_cvm2_cvm_jit_h__cvm_jit_run
    n_cvm2_cvm_c__main -->|"9"| n_cvm2_cvm_c__cvm_run
    n_cvm2_cvm_c__cvm_run -.->|"recursion"| n_cvm2_cvm_c__cvm_run
    n_cvm2_cvm_c__cvm_run -.-> n_cvm2_cvm_c__register_defaults
    n_cvm2_cvm_c__cvm_run -->|"1"| n_cvm2_cvm_c__pop_frame
    n_cvm2_cvm_c__cvm_run -->|"2"| n_cvm2_cvm_c__push_frame
    linkStyle 0,2,4,8,10,12,14,17,27,29,34,36 stroke:#f87171,stroke-width:2px;
```

Cross-file sequence:

```mermaid
sequenceDiagram
    autonumber
    participant p_cvm2_cvm_c as cvm.c
    participant p_cvm2_cvm_jit_h as cvm_jit.h
    p_cvm2_cvm_c->>p_cvm2_cvm_jit_h: cvm_jit_create()
    p_cvm2_cvm_c->>p_cvm2_cvm_jit_h: cvm_jit_destroy()
    p_cvm2_cvm_c->>p_cvm2_cvm_jit_h: cvm_jit_run()
```

### `cvm_dbg_main.main`

`cvm2/cvm_dbg_main.c:337`, score 11: `main` in a compiled-language file; entry-style name `main`.

Call tree:

```mermaid
flowchart LR
    classDef default fill:#111827,stroke:#38bdf8,color:#e5e7eb;
    classDef entry fill:#0e7490,stroke:#22d3ee,color:#ecfeff,stroke-width:2px;
    classDef external fill:#1a1530,stroke:#a78bfa,color:#ede9fe;
    n_cvm2_cvm_dbg_main_c__main["cvm_dbg_main.main<br/>cvm_dbg_main.c:337"]:::entry
    n_cvm2_cvm_view_h__cvm_view_open["cvm_view.cvm_view_open<br/>uint32_t num_strings#59; uint32_t code_size#59; uin...<br/>cvm_view.h:41"]:::external
    n_cvm2_cvm_h__cvm_strerror["cvm.cvm_strerror<br/>cvm.h:256"]:::external
    n_cvm2_cvm_c__cvm_config_default["cvm.cvm_config_default<br/>cvm.c:40"]:::external
    n_cvm2_cvm_h__cvm_create["cvm.cvm_create<br/>cvm.h:247"]:::external
    n_cvm2_cvm_h__cvm_load_module["cvm.cvm_load_module<br/>cvm.h:249"]:::external
    n_cvm2_cvm_h__cvm_destroy["cvm.cvm_destroy<br/>cvm.h:248"]:::external
    n_cvm2_cvm_dbg_main_c__dispatch["cvm_dbg_main.dispatch<br/>cvm_dbg_main.c:310"]:::default
    n_cvm2_cvm_dbg_main_c__cmd_list["cvm_dbg_main.cmd_list<br/>cvm_dbg_main.c:71"]:::default
    n_cvm2_cvm_dbg_main_c__parse_u32["cvm_dbg_main.parse_u32<br/>cvm_dbg_main.c:51"]:::default
    n_cvm2_cvm_dbg_main_c__func_of_ip["cvm_dbg_main.func_of_ip<br/>cvm_dbg_main.c:40"]:::default
    n_cvm2_cvm_view_h__cvm_view_func["cvm_view.cvm_view_func<br/>cvm_view.h:46"]:::external
    n_cvm2_cvm_view_h__cvm_view_func_region["cvm_view.cvm_view_func_region<br/>Code region of a function: [*begin, *end) whe...<br/>cvm_view.h:58"]:::external
    n_cvm2_cvm_dbg_main_c__func_display["cvm_dbg_main.func_display<br/>cvm_dbg_main.c:36"]:::default
    n_cvm2_cvm_view_h__cvm_view_func_name["cvm_view.cvm_view_func_name<br/>String from the pool, or NULL when the offset...<br/>cvm_view.h:53"]:::external
    n_cvm2_cvm_dis_h__cvm_dis_function["cvm_dis.cvm_dis_function<br/>#35;include #lt;stddef.h#gt; #35;include #lt;stdint.h#gt; #35;incl...<br/>cvm_dis.h:26"]:::external
    n_cvm2_cvm_dbg_main_c__cmd_break["cvm_dbg_main.cmd_break<br/>cvm_dbg_main.c:98"]:::default
    n_cvm2_cvm_h__cvm_break_set["cvm.cvm_break_set<br/>cvm.h:262"]:::external
    n_cvm2_cvm_dbg_main_c__cmd_delete["cvm_dbg_main.cmd_delete<br/>cvm_dbg_main.c:133"]:::default
    n_cvm2_cvm_h__cvm_break_clear_all["cvm.cvm_break_clear_all<br/>cvm.h:264"]:::external
    n_cvm2_cvm_h__cvm_break_clear["cvm.cvm_break_clear<br/>cvm.h:263"]:::external
    n_cvm2_cvm_dbg_main_c__main -.->|"recursion"| n_cvm2_cvm_dbg_main_c__main
    n_cvm2_cvm_dbg_main_c__main -->|"1"| n_cvm2_cvm_view_h__cvm_view_open
    n_cvm2_cvm_view_h__cvm_view_open -.->|"recursion"| n_cvm2_cvm_view_h__cvm_view_open
    n_cvm2_cvm_dbg_main_c__main -->|"2"| n_cvm2_cvm_h__cvm_strerror
    n_cvm2_cvm_h__cvm_strerror -.->|"recursion"| n_cvm2_cvm_h__cvm_strerror
    n_cvm2_cvm_dbg_main_c__main -->|"3"| n_cvm2_cvm_c__cvm_config_default
    n_cvm2_cvm_c__cvm_config_default -.->|"recursion"| n_cvm2_cvm_c__cvm_config_default
    n_cvm2_cvm_dbg_main_c__main -->|"4"| n_cvm2_cvm_h__cvm_create
    n_cvm2_cvm_h__cvm_create -.->|"recursion"| n_cvm2_cvm_h__cvm_create
    n_cvm2_cvm_dbg_main_c__main -->|"5"| n_cvm2_cvm_h__cvm_load_module
    n_cvm2_cvm_h__cvm_load_module -.->|"recursion"| n_cvm2_cvm_h__cvm_load_module
    n_cvm2_cvm_dbg_main_c__main -->|"6"| n_cvm2_cvm_h__cvm_destroy
    n_cvm2_cvm_h__cvm_destroy -.->|"recursion"| n_cvm2_cvm_h__cvm_destroy
    n_cvm2_cvm_dbg_main_c__main -->|"7"| n_cvm2_cvm_dbg_main_c__dispatch
    n_cvm2_cvm_dbg_main_c__dispatch -->|"1"| n_cvm2_cvm_dbg_main_c__cmd_list
    n_cvm2_cvm_dbg_main_c__cmd_list -->|"1"| n_cvm2_cvm_dbg_main_c__parse_u32
    n_cvm2_cvm_dbg_main_c__cmd_list -->|"2"| n_cvm2_cvm_dbg_main_c__func_of_ip
    n_cvm2_cvm_dbg_main_c__func_of_ip -->|"1"| n_cvm2_cvm_view_h__cvm_view_func
    n_cvm2_cvm_dbg_main_c__func_of_ip -->|"2"| n_cvm2_cvm_view_h__cvm_view_func_region
    n_cvm2_cvm_dbg_main_c__cmd_list -->|"3"| n_cvm2_cvm_view_h__cvm_view_func
    n_cvm2_cvm_view_h__cvm_view_func -.->|"recursion"| n_cvm2_cvm_view_h__cvm_view_func
    n_cvm2_cvm_dbg_main_c__cmd_list -->|"4"| n_cvm2_cvm_view_h__cvm_view_func_region
    n_cvm2_cvm_view_h__cvm_view_func_region -.->|"recursion"| n_cvm2_cvm_view_h__cvm_view_func_region
    n_cvm2_cvm_dbg_main_c__cmd_list -->|"5"| n_cvm2_cvm_dbg_main_c__func_display
    n_cvm2_cvm_dbg_main_c__func_display -->|"1"| n_cvm2_cvm_view_h__cvm_view_func_name
    n_cvm2_cvm_dbg_main_c__cmd_list -->|"6"| n_cvm2_cvm_dis_h__cvm_dis_function
    n_cvm2_cvm_dis_h__cvm_dis_function -.->|"recursion"| n_cvm2_cvm_dis_h__cvm_dis_function
    n_cvm2_cvm_dbg_main_c__dispatch -->|"2"| n_cvm2_cvm_dbg_main_c__cmd_break
    n_cvm2_cvm_dbg_main_c__cmd_break -.-> n_cvm2_cvm_dbg_main_c__parse_u32
    n_cvm2_cvm_dbg_main_c__cmd_break -.-> n_cvm2_cvm_view_h__cvm_view_func
    n_cvm2_cvm_dbg_main_c__cmd_break -.-> n_cvm2_cvm_dbg_main_c__func_display
    n_cvm2_cvm_dbg_main_c__cmd_break -->|"1"| n_cvm2_cvm_h__cvm_break_set
    n_cvm2_cvm_h__cvm_break_set -.->|"recursion"| n_cvm2_cvm_h__cvm_break_set
    n_cvm2_cvm_dbg_main_c__cmd_break -.-> n_cvm2_cvm_h__cvm_strerror
    n_cvm2_cvm_dbg_main_c__dispatch -->|"3"| n_cvm2_cvm_dbg_main_c__cmd_delete
    n_cvm2_cvm_dbg_main_c__cmd_delete -->|"1"| n_cvm2_cvm_h__cvm_break_clear_all
    n_cvm2_cvm_h__cvm_break_clear_all -.->|"recursion"| n_cvm2_cvm_h__cvm_break_clear_all
    n_cvm2_cvm_dbg_main_c__cmd_delete -.-> n_cvm2_cvm_dbg_main_c__parse_u32
    n_cvm2_cvm_dbg_main_c__cmd_delete -->|"2"| n_cvm2_cvm_h__cvm_break_clear
    n_cvm2_cvm_h__cvm_break_clear -.->|"recursion"| n_cvm2_cvm_h__cvm_break_clear
    linkStyle 0,2,4,6,8,10,12,20,22,26,32,36,39 stroke:#f87171,stroke-width:2px;
```

Cross-file sequence:

```mermaid
sequenceDiagram
    autonumber
    participant p_cvm2_cvm_dbg_main_c as cvm_dbg_main.c
    participant p_cvm2_cvm_view_h as cvm_view.h
    participant p_cvm2_cvm_h as cvm.h
    participant p_cvm2_cvm_c as cvm.c
    participant p_cvm2_cvm_dis_h as cvm_dis.h
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_view_h: cvm_view_open()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_h: cvm_strerror()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_c: cvm_config_default()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_h: cvm_create()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_h: cvm_load_module()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_h: cvm_destroy()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_view_h: cvm_view_func()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_view_h: cvm_view_func_region()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_view_h: cvm_view_func()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_view_h: cvm_view_func_region()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_view_h: cvm_view_func_name()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_dis_h: cvm_dis_function()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_h: cvm_break_set()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_h: cvm_break_clear_all()
    p_cvm2_cvm_dbg_main_c->>p_cvm2_cvm_h: cvm_break_clear()
```

---
