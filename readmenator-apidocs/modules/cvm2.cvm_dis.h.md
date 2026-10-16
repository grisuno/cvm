# `cvm2/cvm_dis.h`

> Source: [cvm2/cvm_dis.h:1](../../cvm2/cvm_dis.h#L1) | language `h` | coverage 75.0% | [API index](../index.md)

## Contents

- **Functions:** [`cvm_dis_module`](#cvm_dis_module), [`cvm_dis_function`](#cvm_dis_function), [`cvm_dis_line`](#cvm_dis_line)

## Functions

<a id="cvm_dis_module"></a>

### `cvm_dis_module`

`function` | [cvm2/cvm_dis.h:23](../../cvm2/cvm_dis.h#L23)

```c
int cvm_dis_module(const CvmModuleView *v, CvmDisEmit emit, void *ctx);
```

Whole module: header summary plus every function region.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `CvmModuleView *` |  |  |
| `emit` | `CvmDisEmit` |  |  |
| `ctx` | `void *` |  |  |

**Returns:** `int`

*Called by:* [`main`](cvm2.cvm_dis_main.c.md#main)

---

<a id="cvm_dis_function"></a>

### `cvm_dis_function`

`function` | [cvm2/cvm_dis.h:26](../../cvm2/cvm_dis.h#L26)

```c
int cvm_dis_function(const CvmModuleView *v, size_t begin, size_t end, CvmDisEmit emit, void *ctx);
```

One function region from begin up to end.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `CvmModuleView *` |  |  |
| `begin` | `size_t` |  |  |
| `end` | `size_t` |  |  |
| `emit` | `CvmDisEmit` |  |  |
| `ctx` | `void *` |  |  |

**Returns:** `int`

---

<a id="cvm_dis_line"></a>

### `cvm_dis_line`

`function` | [cvm2/cvm_dis.h:31](../../cvm2/cvm_dis.h#L31)

```c
int cvm_dis_line(const CvmModuleView *v, size_t off, size_t end, char *buf, size_t cap);
```

One instruction at code offset off (within [begin,end)).

Returns the instruction size, or -1 when it does not decode inside the region.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `CvmModuleView *` |  |  |
| `off` | `size_t` |  |  |
| `end` | `size_t` |  |  |
| `buf` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `int`

---
