# `cvm2/cvm_ops.h`

> Source: [cvm2/cvm_ops.h:1](../../cvm2/cvm_ops.h#L1) | language `h` | coverage 37.5% | [API index](../index.md)

## Contents

- **Structs:** [`CvmOpInfo`](#cvmopinfo)
- **Functions:** [`cvm_op_info`](#cvm_op_info), [`cvm_op_name`](#cvm_op_name), [`cvm_ops_ri32`](#cvm_ops_ri32), [`cvm_ops_ri64`](#cvm_ops_ri64), [`cvm_ops_ru32`](#cvm_ops_ru32), [`cvm_ops_r8`](#cvm_ops_r8)
- **Variables:** [`CvmOpKind`](#cvmopkind)

## Structs

<a id="cvmopinfo"></a>

### `CvmOpInfo`

`struct` | [cvm2/cvm_ops.h:30](../../cvm2/cvm_ops.h#L30)

```c
typedef struct
```

---

## Functions

<a id="cvm_op_info"></a>

### `cvm_op_info`

`function` `const` | [cvm2/cvm_ops.h:38](../../cvm2/cvm_ops.h#L38)

```c
const CvmOpInfo *cvm_op_info(uint8_t opcode);
```

Metadata for one opcode, or NULL when the opcode is not defined.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `opcode` | `uint8_t` |  |  |

**Returns:** `CvmOpInfo *`

*Called by:* [`cvm_dis_line`](cvm2.cvm_dis.c.md#cvm_dis_line)

---

<a id="cvm_op_name"></a>

### `cvm_op_name`

`function` `const` | [cvm2/cvm_ops.h:41](../../cvm2/cvm_ops.h#L41)

```c
const char *cvm_op_name(uint8_t opcode);
```

Mnemonic for one opcode, or NULL when the opcode is not defined.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `opcode` | `uint8_t` |  |  |

**Returns:** `char *`

---

<a id="cvm_ops_ri32"></a>

### `cvm_ops_ri32`

`function` | [cvm2/cvm_ops.h:44](../../cvm2/cvm_ops.h#L44)

```c
int32_t cvm_ops_ri32(const uint8_t *code, size_t size, size_t off);
```

Decode helpers over a code buffer, little-endian as stored.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `code` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |
| `off` | `size_t` |  |  |

**Returns:** `int32_t`

*Called by:* [`cvm_dis_line`](cvm2.cvm_dis.c.md#cvm_dis_line)

---

<a id="cvm_ops_ri64"></a>

### `cvm_ops_ri64`

`function` | [cvm2/cvm_ops.h:45](../../cvm2/cvm_ops.h#L45)

```c
int64_t cvm_ops_ri64(const uint8_t *code, size_t size, size_t off);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `code` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |
| `off` | `size_t` |  |  |

**Returns:** `int64_t`

*Called by:* [`cvm_dis_line`](cvm2.cvm_dis.c.md#cvm_dis_line)

---

<a id="cvm_ops_ru32"></a>

### `cvm_ops_ru32`

`function` | [cvm2/cvm_ops.h:46](../../cvm2/cvm_ops.h#L46)

```c
uint32_t cvm_ops_ru32(const uint8_t *code, size_t size, size_t off);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `code` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |
| `off` | `size_t` |  |  |

**Returns:** `uint32_t`

*Called by:* [`cvm_dis_line`](cvm2.cvm_dis.c.md#cvm_dis_line)

---

<a id="cvm_ops_r8"></a>

### `cvm_ops_r8`

`function` | [cvm2/cvm_ops.h:47](../../cvm2/cvm_ops.h#L47)

```c
int cvm_ops_r8(const uint8_t *code, size_t size, size_t off, uint8_t *out);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `code` | `uint8_t *` |  |  |
| `size` | `size_t` |  |  |
| `off` | `size_t` |  |  |
| `out` | `uint8_t *` |  |  |

**Returns:** `int`

---

## Variables

<a id="cvmopkind"></a>

### `CvmOpKind`

`variable` `extern` | [cvm2/cvm_ops.h:16](../../cvm2/cvm_ops.h#L16)

```c
extern "C" { #endif typedef enum { CVM_OPK_NONE = 0, CVM_OPK_I8 = 1, CVM_OPK_I32 = 2, CVM_OPK_I64 = 3, CVM_OPK_U32 = 4, CVM_OPK_U32U8 = 5, CVM_OPK_REL = 6, CVM_OPK_U8U8 = 7 } CvmOpKind;
```

ifdef __cplusplus

---
