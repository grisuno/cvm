# `cvm2/cvm_jit_help.c`

> Source: [cvm2/cvm_jit_help.c:1](../../cvm2/cvm_jit_help.c#L1) | language `c` | coverage 66.7% | [API index](../index.md)

## Contents

- **Functions:** [`cvm_jit_offsets_init`](#cvm_jit_offsets_init), [`cvm_jit_func_enter`](#cvm_jit_func_enter), [`cvm_jit_func_leave`](#cvm_jit_func_leave), [`cvm_jit_call`](#cvm_jit_call), [`cvm_jit_ret`](#cvm_jit_ret), [`cvm_jit_call_native`](#cvm_jit_call_native), [`cvm_jit_memcheck`](#cvm_jit_memcheck), [`cvm_jit_alloc`](#cvm_jit_alloc), [`cvm_jit_syscall`](#cvm_jit_syscall), [`cvm_jit_error`](#cvm_jit_error)
- **Macros:** [`CVM_HEAP_ALIGN`](#cvm_heap_align)

## Functions

<a id="cvm_jit_offsets_init"></a>

### `cvm_jit_offsets_init`

`function` | [cvm2/cvm_jit_help.c:22](../../cvm2/cvm_jit_help.c#L22)

```c
void cvm_jit_offsets_init(CvmJitOffsets *o)
```

Compute and cache all field offsets.

Must be called once before any JIT compilation begins.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `o` | `CvmJitOffsets *` |  |  |

> **Inherited:** Documentation from [`cvm_jit_offsets_init`](#cvm_jit_offsets_init) (cvm2/cvm_jit_help.h:44).

---

<a id="cvm_jit_func_enter"></a>

### `cvm_jit_func_enter`

`function` | [cvm2/cvm_jit_help.c:136](../../cvm2/cvm_jit_help.c#L136)

```c
uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx)
```

Called at JIT function entry to sync interpreter state.

Returns the code pointer for the function.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `func_idx` | `uint32_t` |  |  |

**Returns:** `uint8_t *`

> **Inherited:** Documentation from [`cvm_jit_func_enter`](#cvm_jit_func_enter) (cvm2/cvm_jit_help.h:52).

---

<a id="cvm_jit_func_leave"></a>

### `cvm_jit_func_leave`

`function` | [cvm2/cvm_jit_help.c:145](../../cvm2/cvm_jit_help.c#L145)

```c
void cvm_jit_func_leave(CvmState *vm)
```

Called at JIT function exit to sync interpreter state back.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |

> **Inherited:** Documentation from [`cvm_jit_func_leave`](#cvm_jit_func_leave) (cvm2/cvm_jit_help.h:55).

---

<a id="cvm_jit_call"></a>

### `cvm_jit_call`

`function` | [cvm2/cvm_jit_help.c:155](../../cvm2/cvm_jit_help.c#L155)

```c
int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc)
```

Execute OP_CALL: push a new frame, copy arguments from the operand stack into the new frame's locals, and set vm->ip to the callee.

Returns 0 on success, non-zero error code on failure. On success, the JIT must jump to vm->ip (the callee's code). On failure, vm->running is set to 0 and vm->exit_code is set.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `func_idx` | `uint32_t` |  |  |
| `argc` | `uint8_t` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`cvm_jit_call`](#cvm_jit_call) (cvm2/cvm_jit_help.h:66).

---

<a id="cvm_jit_ret"></a>

### `cvm_jit_ret`

`function` | [cvm2/cvm_jit_help.c:176](../../cvm2/cvm_jit_help.c#L176)

```c
int cvm_jit_ret(CvmState *vm, uint64_t retval)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `retval` | `uint64_t` |  |  |

**Returns:** `int`

---

<a id="cvm_jit_call_native"></a>

### `cvm_jit_call_native`

`function` | [cvm2/cvm_jit_help.c:193](../../cvm2/cvm_jit_help.c#L193)

```c
int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc)
```

Execute OP_CALL_NATIVE: resolve the native function by index, pop arguments from the operand stack, call the host function, and push the result.

Returns 0 on success.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `native_idx` | `uint32_t` |  |  |
| `argc` | `uint8_t` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`cvm_jit_call_native`](#cvm_jit_call_native) (cvm2/cvm_jit_help.h:77).

---

<a id="cvm_jit_memcheck"></a>

### `cvm_jit_memcheck`

`function` | [cvm2/cvm_jit_help.c:213](../../cvm2/cvm_jit_help.c#L213)

```c
int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `addr` | `uint64_t` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `int`

---

<a id="cvm_jit_alloc"></a>

### `cvm_jit_alloc`

`function` | [cvm2/cvm_jit_help.c:221](../../cvm2/cvm_jit_help.c#L221)

```c
uint64_t cvm_jit_alloc(CvmState *vm, size_t size)
```

Bump-allocate 'size' bytes from the CVM heap.

Returns the heap pointer on success, 0 on exhaustion.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `uint64_t`

> **Inherited:** Documentation from [`cvm_jit_alloc`](#cvm_jit_alloc) (cvm2/cvm_jit_help.h:94).

---

<a id="cvm_jit_syscall"></a>

### `cvm_jit_syscall`

`function` | [cvm2/cvm_jit_help.c:229](../../cvm2/cvm_jit_help.c#L229)

```c
int cvm_jit_syscall(CvmState *vm, uint8_t sn, uint8_t argc)
```

Execute a Linux-style syscall.

Pops 'argc' arguments from the operand stack, dispatches by syscall number, and pushes the result. Returns 0 on success.  On exit syscall, vm->running is set to 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `sn` | `uint8_t` |  |  |
| `argc` | `uint8_t` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`cvm_jit_syscall`](#cvm_jit_syscall) (cvm2/cvm_jit_help.h:103).

---

<a id="cvm_jit_error"></a>

### `cvm_jit_error`

`function` | [cvm2/cvm_jit_help.c:256](../../cvm2/cvm_jit_help.c#L256)

```c
void cvm_jit_error(CvmState *vm, int error_code)
```

Set an error code and terminate the VM.

This is called when a JIT-compiled function detects an unrecoverable error (bad address, stack overflow, etc.).  Sets vm->running = 0 and vm->exit_code.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `error_code` | `int` |  |  |

> **Inherited:** Documentation from [`cvm_jit_error`](#cvm_jit_error) (cvm2/cvm_jit_help.h:112).

---

## Macros

<a id="cvm_heap_align"></a>

### `CVM_HEAP_ALIGN`

`macro` | [cvm2/cvm_jit_help.c:16](../../cvm2/cvm_jit_help.c#L16)

```c
#define CVM_HEAP_ALIGN
```

---
