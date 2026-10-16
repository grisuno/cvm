# `cvm2/cvm_dis_main.c`

> Source: [cvm2/cvm_dis_main.c:1](../../cvm2/cvm_dis_main.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`main`](#main)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_cvm2_cvm_dis_main_c__main(["main"])
    n_cvm2_cvm_dis_h__cvm_dis_module["cvm_dis.cvm_dis_module"]
    n_cvm2_cvm_view_h__cvm_view_open["cvm_view.cvm_view_open"]
    n_cvm2_cvm_view_h__cvm_view_strerror["cvm_view.cvm_view_strerror"]
    n_cvm2_cvm_dis_main_c__main -.-> n_cvm2_cvm_dis_h__cvm_dis_module
    n_cvm2_cvm_dis_main_c__main -.-> n_cvm2_cvm_view_h__cvm_view_open
    n_cvm2_cvm_dis_main_c__main -.-> n_cvm2_cvm_view_h__cvm_view_strerror
```

## Functions

<a id="main"></a>

### `main`

`function` | [cvm2/cvm_dis_main.c:18](../../cvm2/cvm_dis_main.c#L18)

```c
int main(int argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

*Calls:* [`cvm_dis_module`](cvm2.cvm_dis.h.md#cvm_dis_module), [`cvm_view_open`](cvm2.cvm_view.h.md#cvm_view_open), [`cvm_view_strerror`](cvm2.cvm_view.h.md#cvm_view_strerror)

---
