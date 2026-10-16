# `cvm2/cvm_jit_help.h`

> Source: [cvm2/cvm_jit_help.h:1](../../cvm2/cvm_jit_help.h#L1) | language `h` | coverage 75.0% | [API index](../index.md)

## Contents

- **Structs:** [`CvmJitOffsets`](#cvmjitoffsets)
- **Functions:** [`cvm_jit_offsets_init`](#cvm_jit_offsets_init), [`cvm_jit_func_enter`](#cvm_jit_func_enter), [`cvm_jit_func_leave`](#cvm_jit_func_leave), [`cvm_jit_call`](#cvm_jit_call), [`to`](#to), [`cvm_jit_call_native`](#cvm_jit_call_native), [`region`](#region), [`cvm_jit_alloc`](#cvm_jit_alloc), [`cvm_jit_syscall`](#cvm_jit_syscall), [`cvm_jit_error`](#cvm_jit_error)
- **Variables:** [`slots`](#slots)

## Structs

<a id="cvmjitoffsets"></a>

### `CvmJitOffsets`

`struct` | [cvm2/cvm_jit_help.h:22](../../cvm2/cvm_jit_help.h#L22)

```c
typedef struct
```

Register offsets into CvmState, used by JIT-compiled code for direct field access.

These are computed once at JIT init time.

---

## Functions

<a id="cvm_jit_offsets_init"></a>

### `cvm_jit_offsets_init`

`function` | [cvm2/cvm_jit_help.h:44](../../cvm2/cvm_jit_help.h#L44)

```c
void cvm_jit_offsets_init(CvmJitOffsets *off);
```

Compute and cache all field offsets.

Must be called once before any JIT compilation begins.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `off` | `CvmJitOffsets *` |  |  |

---

<a id="cvm_jit_func_enter"></a>

### `cvm_jit_func_enter`

`function` | [cvm2/cvm_jit_help.h:52](../../cvm2/cvm_jit_help.h#L52)

```c
uint8_t *cvm_jit_func_enter(CvmState *vm, uint32_t func_idx);
```

Called at JIT function entry to sync interpreter state.

Returns the code pointer for the function.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `func_idx` | `uint32_t` |  |  |

**Returns:** `uint8_t *`

---

<a id="cvm_jit_func_leave"></a>

### `cvm_jit_func_leave`

`function` | [cvm2/cvm_jit_help.h:55](../../cvm2/cvm_jit_help.h#L55)

```c
void cvm_jit_func_leave(CvmState *vm);
```

Called at JIT function exit to sync interpreter state back.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |

---

<a id="cvm_jit_call"></a>

### `cvm_jit_call`

`function` | [cvm2/cvm_jit_help.h:66](../../cvm2/cvm_jit_help.h#L66)

```c
int cvm_jit_call(CvmState *vm, uint32_t func_idx, uint8_t argc);
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

---

<a id="to"></a>

### `to`

`function` | [cvm2/cvm_jit_help.h:70](../../cvm2/cvm_jit_help.h#L70)

```c
* Returns 0 if there is a caller to return to (vm->ip is set). * Returns 1 if this was the entry frame (vm->running = 0, done). */ int cvm_jit_ret(CvmState *vm, uint64_t retval);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `set` | `vm->ip is` |  |  |

**Returns:** `* Returns 0 if there is a caller`

---

<a id="cvm_jit_call_native"></a>

### `cvm_jit_call_native`

`function` | [cvm2/cvm_jit_help.h:77](../../cvm2/cvm_jit_help.h#L77)

```c
int cvm_jit_call_native(CvmState *vm, uint32_t native_idx, uint8_t argc);
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

---

<a id="region"></a>

### `region`

`function` | [cvm2/cvm_jit_help.h:84](../../cvm2/cvm_jit_help.h#L84)

```c
* region (heap, globals, string pool, or any frame's locals). * Returns 1 if valid, 0 if invalid. */ int cvm_jit_memcheck(const CvmState *vm, uint64_t addr, size_t size);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pool` | `string` |  |  |
| `locals` | `or any frame's` |  |  |

**Returns:** `*`

---

<a id="cvm_jit_alloc"></a>

### `cvm_jit_alloc`

`function` | [cvm2/cvm_jit_help.h:94](../../cvm2/cvm_jit_help.h#L94)

```c
uint64_t cvm_jit_alloc(CvmState *vm, size_t size);
```

Bump-allocate 'size' bytes from the CVM heap.

Returns the heap pointer on success, 0 on exhaustion.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `size` | `size_t` |  |  |

**Returns:** `uint64_t`

---

<a id="cvm_jit_syscall"></a>

### `cvm_jit_syscall`

`function` | [cvm2/cvm_jit_help.h:103](../../cvm2/cvm_jit_help.h#L103)

```c
int cvm_jit_syscall(CvmState *vm, uint8_t syscall_nr, uint8_t argc);
```

Execute a Linux-style syscall.

Pops 'argc' arguments from the operand stack, dispatches by syscall number, and pushes the result. Returns 0 on success.  On exit syscall, vm->running is set to 0.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `syscall_nr` | `uint8_t` |  |  |
| `argc` | `uint8_t` |  |  |

**Returns:** `int`

---

<a id="cvm_jit_error"></a>

### `cvm_jit_error`

`function` | [cvm2/cvm_jit_help.h:112](../../cvm2/cvm_jit_help.h#L112)

```c
void cvm_jit_error(CvmState *vm, int error_code);
```

Set an error code and terminate the VM.

This is called when a JIT-compiled function detects an unrecoverable error (bad address, stack overflow, etc.).  Sets vm->running = 0 and vm->exit_code.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vm` | `CvmState *` |  |  |
| `error_code` | `int` |  |  |

---

## Variables

<a id="slots"></a>

### `slots`

`variable` `extern` | [cvm2/cvm_jit_help.h:17](../../cvm2/cvm_jit_help.h#L17)

```c
extern "C" { #endif /* Register offsets into CvmState, used by JIT-compiled code for * direct field access. These are computed once at JIT init time. */ typedef struct { size_t slots;
```

ifdef __cplusplus

---
