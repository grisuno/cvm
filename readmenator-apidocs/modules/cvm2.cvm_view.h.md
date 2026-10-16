# `cvm2/cvm_view.h`

> Source: [cvm2/cvm_view.h:1](../../cvm2/cvm_view.h#L1) | language `h` | coverage 62.5% | [API index](../index.md)

## Contents

- **Structs:** [`CvmModuleView`](#cvmmoduleview)
- **Functions:** [`cvm_view_open`](#cvm_view_open), [`cvm_view_strerror`](#cvm_view_strerror), [`cvm_view_func`](#cvm_view_func), [`cvm_view_string`](#cvm_view_string), [`cvm_view_func_name`](#cvm_view_func_name), [`cvm_view_func_region`](#cvm_view_func_region)
- **Variables:** [`data`](#data)

## Structs

<a id="cvmmoduleview"></a>

### `CvmModuleView`

`struct` | [cvm2/cvm_view.h:19](../../cvm2/cvm_view.h#L19)

```c
typedef struct
```

---

## Functions

<a id="cvm_view_open"></a>

### `cvm_view_open`

`function` | [cvm2/cvm_view.h:41](../../cvm2/cvm_view.h#L41)

```c
int cvm_view_open(CvmModuleView *v, const uint8_t *data, size_t size);
```

Parse and validate the header plus all section extents.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `CvmModuleView *` |  |  |
| `data` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

*Called by:* [`main`](cvm2.cvm_dbg_main.c.md#main), [`main`](cvm2.cvm_dis_main.c.md#main), [`main`](cvm2.cvm_val_main.c.md#main)

---

<a id="cvm_view_strerror"></a>

### `cvm_view_strerror`

`function` `const` | [cvm2/cvm_view.h:44](../../cvm2/cvm_view.h#L44)

```c
const char *cvm_view_strerror(int error_code);
```

Message for an error code returned by cvm_view_open.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `error_code` | `int` |  |  |

**Returns:** `char *`

*Called by:* [`main`](cvm2.cvm_dis_main.c.md#main), [`main`](cvm2.cvm_val_main.c.md#main)

---

<a id="cvm_view_func"></a>

### `cvm_view_func`

`function` `const` | [cvm2/cvm_view.h:46](../../cvm2/cvm_view.h#L46)

```c
const CvmFuncEntry *cvm_view_func(const CvmModuleView *v, uint32_t i);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `CvmModuleView *` |  |  |
| `i` | `uint32_t` |  |  |

**Returns:** `CvmFuncEntry *`

*Called by:* [`main`](cvm2.cvm_val_main.c.md#main)

---

<a id="cvm_view_string"></a>

### `cvm_view_string`

`function` `const` | [cvm2/cvm_view.h:50](../../cvm2/cvm_view.h#L50)

```c
const char *cvm_view_string(const CvmModuleView *v, uint32_t off);
```

String from the pool, or NULL when the offset is outside it.

The pointer is only valid while the module data lives.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `CvmModuleView *` |  |  |
| `off` | `uint32_t` |  |  |

**Returns:** `char *`

---

<a id="cvm_view_func_name"></a>

### `cvm_view_func_name`

`function` `const` | [cvm2/cvm_view.h:53](../../cvm2/cvm_view.h#L53)

```c
const char *cvm_view_func_name(const CvmModuleView *v, uint32_t fi, char *fallback, size_t cap);
```

Function name from the pool; falls back to "func<N>" in fallback.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `CvmModuleView *` |  |  |
| `fi` | `uint32_t` |  |  |
| `fallback` | `char *` |  |  |
| `cap` | `size_t` |  |  |

**Returns:** `char *`

*Called by:* [`main`](cvm2.cvm_val_main.c.md#main)

---

<a id="cvm_view_func_region"></a>

### `cvm_view_func_region`

`function` | [cvm2/cvm_view.h:58](../../cvm2/cvm_view.h#L58)

```c
int cvm_view_func_region(const CvmModuleView *v, uint32_t fi, size_t *begin, size_t *end);
```

Code region of a function: [*begin, *end) where *end is the next function's code offset or the end of the code section.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `CvmModuleView *` |  |  |
| `fi` | `uint32_t` |  |  |
| `begin` | `size_t *` |  |  |
| `end` | `size_t *` |  |  |

**Returns:** `int`

*Called by:* [`main`](cvm2.cvm_val_main.c.md#main)

---

## Variables

<a id="data"></a>

### `data`

`variable` `extern` | [cvm2/cvm_view.h:16](../../cvm2/cvm_view.h#L16)

```c
extern "C" { #endif typedef struct { const uint8_t *data;
```

ifdef __cplusplus

---
