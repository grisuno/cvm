# `cvm2/cvm_jit_x86.h`

> Source: [cvm2/cvm_jit_x86.h:1](../../cvm2/cvm_jit_x86.h#L1) | language `h` | coverage 84.5% | [API index](../index.md)

## Contents

- **Structs:** [`JitBuf`](#jitbuf), [`JitPatch`](#jitpatch), [`JitPatches`](#jitpatches)
- **Functions:** [`jit_buf_init`](#jit_buf_init), [`jit_buf_free`](#jit_buf_free), [`jit_buf_reset`](#jit_buf_reset), [`jit_buf_failed`](#jit_buf_failed), [`emit8`](#emit8), [`emit16`](#emit16), [`emit32`](#emit32), [`emit64`](#emit64), [`emit_bytes`](#emit_bytes), [`reg_needs_rex`](#reg_needs_rex), [`reg_high3`](#reg_high3), [`emit_mov_reg_imm64`](#emit_mov_reg_imm64), [`emit_mov_reg_imm32`](#emit_mov_reg_imm32), [`emit_mov_reg_reg`](#emit_mov_reg_reg), [`emit_mov_reg_mem`](#emit_mov_reg_mem), [`emit_mov_mem_reg`](#emit_mov_mem_reg), [`emit_movzx_reg_mem8`](#emit_movzx_reg_mem8), [`emit_movzx_reg_mem16`](#emit_movzx_reg_mem16), [`emit_movsx_reg_mem32`](#emit_movsx_reg_mem32), [`emit_mov32_reg_mem`](#emit_mov32_reg_mem), [`emit_mov32_mem_reg`](#emit_mov32_mem_reg), [`emit_lea_sib`](#emit_lea_sib), [`emit_mov_reg_sib`](#emit_mov_reg_sib), [`emit_mov_sib_reg`](#emit_mov_sib_reg), [`emit_push`](#emit_push), [`emit_pop`](#emit_pop), [`emit_add_reg_reg`](#emit_add_reg_reg), [`emit_add_reg_imm32`](#emit_add_reg_imm32), [`emit_sub_reg_reg`](#emit_sub_reg_reg), [`emit_sub_reg_imm32`](#emit_sub_reg_imm32), [`emit_imul_reg_reg`](#emit_imul_reg_reg), [`emit_idiv_reg`](#emit_idiv_reg), [`emit_div_reg`](#emit_div_reg), [`emit_cqo`](#emit_cqo), [`emit_neg_reg`](#emit_neg_reg), [`emit_inc_reg`](#emit_inc_reg), [`emit_dec_reg`](#emit_dec_reg), [`emit_and_reg_reg`](#emit_and_reg_reg), [`emit_or_reg_reg`](#emit_or_reg_reg), [`emit_xor_reg_reg`](#emit_xor_reg_reg), [`emit_not_reg`](#emit_not_reg), [`emit_shl_reg_cl`](#emit_shl_reg_cl), [`emit_shr_reg_cl`](#emit_shr_reg_cl), [`emit_sar_reg_cl`](#emit_sar_reg_cl), [`emit_xor_reg_self`](#emit_xor_reg_self), [`emit_cmp_reg_reg`](#emit_cmp_reg_reg), [`emit_test_reg_reg`](#emit_test_reg_reg), [`emit_setcc`](#emit_setcc), [`emit_jmp_rel32`](#emit_jmp_rel32), [`emit_jcc_rel32`](#emit_jcc_rel32), [`emit_jmp_buf`](#emit_jmp_buf), [`emit_jcc_buf`](#emit_jcc_buf), [`jit_apply_patches`](#jit_apply_patches), [`emit_call_rel32`](#emit_call_rel32), [`emit_call_reg`](#emit_call_reg), [`emit_ret`](#emit_ret), [`emit_syscall`](#emit_syscall), [`emit_int3`](#emit_int3), [`emit_nop`](#emit_nop), [`emit_call_abs`](#emit_call_abs), [`emit_and_reg_imm32`](#emit_and_reg_imm32), [`emit_movzx_reg_reg8`](#emit_movzx_reg_reg8), [`emit_rex`](#emit_rex), [`emit_modrm`](#emit_modrm), [`emit_mov_mem_imm8`](#emit_mov_mem_imm8), [`emit_mov_mem_imm32`](#emit_mov_mem_imm32)
- **Macros:** [`JIT_MAX_PATCHES`](#jit_max_patches)

## Type Diagram

```mermaid
classDiagram
    direction LR
    class JitBuf
    <<struct>> JitBuf
    class JitPatch
    <<struct>> JitPatch
    class JitPatches
    <<struct>> JitPatches
```

## Structs

<a id="jitbuf"></a>

### `JitBuf`

`struct` | [cvm2/cvm_jit_x86.h:40](../../cvm2/cvm_jit_x86.h#L40)

```c
typedef struct
```

Growable code buffer backed by mmap'd RWX memory

---

<a id="jitpatch"></a>

### `JitPatch`

`struct` | [cvm2/cvm_jit_x86.h:48](../../cvm2/cvm_jit_x86.h#L48)

```c
typedef struct
```

Forward patch entry for unresolved jumps

---

<a id="jitpatches"></a>

### `JitPatches`

`struct` | [cvm2/cvm_jit_x86.h:55](../../cvm2/cvm_jit_x86.h#L55)

```c
typedef struct
```

---

## Functions

<a id="jit_buf_init"></a>

### `jit_buf_init`

`function` | [cvm2/cvm_jit_x86.h:63](../../cvm2/cvm_jit_x86.h#L63)

```c
void jit_buf_init(JitBuf *b, size_t initial_cap);
```

size_t patch_off;    /* offset in buf->code where rel32 lives size_t target;       /* absolute target offset in the same buffer } JitPatch; #define JIT_MAX_PATCHES 8192 typedef struct { JitPatch patches[JIT_MAX_PATCHES]; size_t   count; } JitPatches; /* ------------------------------------------------------------------ /*  Buffer lifecycle /* ------------------------------------------------------------------

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `initial_cap` | `size_t` |  |  |

---

<a id="jit_buf_free"></a>

### `jit_buf_free`

`function` | [cvm2/cvm_jit_x86.h:64](../../cvm2/cvm_jit_x86.h#L64)

```c
void jit_buf_free(JitBuf *b);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |

---

<a id="jit_buf_reset"></a>

### `jit_buf_reset`

`function` | [cvm2/cvm_jit_x86.h:65](../../cvm2/cvm_jit_x86.h#L65)

```c
void jit_buf_reset(JitBuf *b);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |

---

<a id="jit_buf_failed"></a>

### `jit_buf_failed`

`function` | [cvm2/cvm_jit_x86.h:66](../../cvm2/cvm_jit_x86.h#L66)

```c
int jit_buf_failed(const JitBuf *b);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |

**Returns:** `int`

---

<a id="emit8"></a>

### `emit8`

`function` | [cvm2/cvm_jit_x86.h:71](../../cvm2/cvm_jit_x86.h#L71)

```c
void emit8(JitBuf *b, uint8_t v);
```

size_t   count; } JitPatches; /* ------------------------------------------------------------------ /*  Buffer lifecycle /* ------------------------------------------------------------------ void  jit_buf_init(JitBuf *b, size_t initial_cap); void  jit_buf_free(JitBuf *b); void  jit_buf_reset(JitBuf *b); int   jit_buf_failed(const JitBuf *b); /* ------------------------------------------------------------------ /*  Byte emission (little-endian) /* ------------------------------------------------------------------

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `v` | `uint8_t` |  |  |

---

<a id="emit16"></a>

### `emit16`

`function` | [cvm2/cvm_jit_x86.h:72](../../cvm2/cvm_jit_x86.h#L72)

```c
void emit16(JitBuf *b, uint16_t v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `v` | `uint16_t` |  |  |

---

<a id="emit32"></a>

### `emit32`

`function` | [cvm2/cvm_jit_x86.h:73](../../cvm2/cvm_jit_x86.h#L73)

```c
void emit32(JitBuf *b, uint32_t v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `v` | `uint32_t` |  |  |

---

<a id="emit64"></a>

### `emit64`

`function` | [cvm2/cvm_jit_x86.h:74](../../cvm2/cvm_jit_x86.h#L74)

```c
void emit64(JitBuf *b, uint64_t v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `v` | `uint64_t` |  |  |

---

<a id="emit_bytes"></a>

### `emit_bytes`

`function` | [cvm2/cvm_jit_x86.h:75](../../cvm2/cvm_jit_x86.h#L75)

```c
void emit_bytes(JitBuf *b, const void *data, size_t len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `data` | `void *` |  |  |
| `len` | `size_t` |  |  |

---

<a id="reg_needs_rex"></a>

### `reg_needs_rex`

`function` `inline` `static` | [cvm2/cvm_jit_x86.h:80](../../cvm2/cvm_jit_x86.h#L80)

```c
static inline int reg_needs_rex(int r)
```

int   jit_buf_failed(const JitBuf *b); /* ------------------------------------------------------------------ /*  Byte emission (little-endian) /* ------------------------------------------------------------------ void  emit8(JitBuf *b, uint8_t v); void  emit16(JitBuf *b, uint16_t v); void  emit32(JitBuf *b, uint32_t v); void  emit64(JitBuf *b, uint64_t v); void  emit_bytes(JitBuf *b, const void *data, size_t len); /* ------------------------------------------------------------------ /*  Register checks /* ------------------------------------------------------------------

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `int` |  |  |

**Returns:** `int`

*Called by:* [`emit_call_reg`](cvm2.cvm_jit_x86.c.md#emit_call_reg), [`emit_pop`](cvm2.cvm_jit_x86.c.md#emit_pop), [`emit_push`](cvm2.cvm_jit_x86.c.md#emit_push), [`emit_setcc`](cvm2.cvm_jit_x86.c.md#emit_setcc)

---

<a id="reg_high3"></a>

### `reg_high3`

`function` `inline` `static` | [cvm2/cvm_jit_x86.h:81](../../cvm2/cvm_jit_x86.h#L81)

```c
static inline int reg_high3(int r)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `r` | `int` |  |  |

**Returns:** `int`

*Called by:* [`emit_add_reg_imm32`](cvm2.cvm_jit_x86.c.md#emit_add_reg_imm32), [`emit_and_reg_imm32`](cvm2.cvm_jit_x86.c.md#emit_and_reg_imm32), [`emit_dec_reg`](cvm2.cvm_jit_x86.c.md#emit_dec_reg), [`emit_div_reg`](cvm2.cvm_jit_x86.c.md#emit_div_reg), [`emit_idiv_reg`](cvm2.cvm_jit_x86.c.md#emit_idiv_reg), [`emit_imul_reg_reg`](cvm2.cvm_jit_x86.c.md#emit_imul_reg_reg), [`emit_inc_reg`](cvm2.cvm_jit_x86.c.md#emit_inc_reg), [`emit_lea_sib`](cvm2.cvm_jit_x86.c.md#emit_lea_sib), [`emit_mov32_mem_reg`](cvm2.cvm_jit_x86.c.md#emit_mov32_mem_reg), [`emit_mov32_reg_mem`](cvm2.cvm_jit_x86.c.md#emit_mov32_reg_mem), [`emit_mov_mem_imm32`](cvm2.cvm_jit_x86.c.md#emit_mov_mem_imm32), [`emit_mov_mem_imm8`](cvm2.cvm_jit_x86.c.md#emit_mov_mem_imm8) and 16 more

---

<a id="emit_mov_reg_imm64"></a>

### `emit_mov_reg_imm64`

`function` | [cvm2/cvm_jit_x86.h:88](../../cvm2/cvm_jit_x86.h#L88)

```c
void emit_mov_reg_imm64(JitBuf *b, int dst, uint64_t imm);
```

MOV r64, imm64  (10 bytes: REX.W B8+rd imm64)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `imm` | `uint64_t` |  |  |

---

<a id="emit_mov_reg_imm32"></a>

### `emit_mov_reg_imm32`

`function` | [cvm2/cvm_jit_x86.h:91](../../cvm2/cvm_jit_x86.h#L91)

```c
void emit_mov_reg_imm32(JitBuf *b, int dst, int32_t imm);
```

MOV r64, imm32  (sign-extended, 7 bytes: REX.W C7 /0 r/m imm32)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `imm` | `int32_t` |  |  |

---

<a id="emit_mov_reg_reg"></a>

### `emit_mov_reg_reg`

`function` | [cvm2/cvm_jit_x86.h:94](../../cvm2/cvm_jit_x86.h#L94)

```c
void emit_mov_reg_reg(JitBuf *b, int dst, int src);
```

MOV r64, r64  (3 bytes: REX.W 89 /r)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_mov_reg_mem"></a>

### `emit_mov_reg_mem`

`function` | [cvm2/cvm_jit_x86.h:97](../../cvm2/cvm_jit_x86.h#L97)

```c
void emit_mov_reg_mem(JitBuf *b, int dst, int base, int32_t disp);
```

MOV r64, [base + disp32]  (7 bytes: REX.W 8B /r mod=10)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `base` | `int` |  |  |
| `disp` | `int32_t` |  |  |

---

<a id="emit_mov_mem_reg"></a>

### `emit_mov_mem_reg`

`function` | [cvm2/cvm_jit_x86.h:100](../../cvm2/cvm_jit_x86.h#L100)

```c
void emit_mov_mem_reg(JitBuf *b, int base, int32_t disp, int src);
```

MOV [base + disp32], r64  (7 bytes: REX.W 89 /r mod=10)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `base` | `int` |  |  |
| `disp` | `int32_t` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_movzx_reg_mem8"></a>

### `emit_movzx_reg_mem8`

`function` | [cvm2/cvm_jit_x86.h:103](../../cvm2/cvm_jit_x86.h#L103)

```c
void emit_movzx_reg_mem8(JitBuf *b, int dst, int base, int32_t disp);
```

MOVZX r64, byte [base + disp32]  (4 bytes: REX.W 0F B6 /r mod=10)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `base` | `int` |  |  |
| `disp` | `int32_t` |  |  |

---

<a id="emit_movzx_reg_mem16"></a>

### `emit_movzx_reg_mem16`

`function` | [cvm2/cvm_jit_x86.h:106](../../cvm2/cvm_jit_x86.h#L106)

```c
void emit_movzx_reg_mem16(JitBuf *b, int dst, int base, int32_t disp);
```

MOVZX r64, word [base + disp32]  (4 bytes: REX.W 0F B7 /r mod=10)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `base` | `int` |  |  |
| `disp` | `int32_t` |  |  |

---

<a id="emit_movsx_reg_mem32"></a>

### `emit_movsx_reg_mem32`

`function` | [cvm2/cvm_jit_x86.h:109](../../cvm2/cvm_jit_x86.h#L109)

```c
void emit_movsx_reg_mem32(JitBuf *b, int dst, int base, int32_t disp);
```

MOVSX r64, dword [base + disp32]  (4 bytes: REX.W 63 /r mod=10)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `base` | `int` |  |  |
| `disp` | `int32_t` |  |  |

---

<a id="emit_mov32_reg_mem"></a>

### `emit_mov32_reg_mem`

`function` | [cvm2/cvm_jit_x86.h:112](../../cvm2/cvm_jit_x86.h#L112)

```c
void emit_mov32_reg_mem(JitBuf *b, int dst, int base, int32_t disp);
```

MOV r32, [base + disp32]  (zero-extends to r64, 6 bytes: 8B /r mod=10)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `base` | `int` |  |  |
| `disp` | `int32_t` |  |  |

---

<a id="emit_mov32_mem_reg"></a>

### `emit_mov32_mem_reg`

`function` | [cvm2/cvm_jit_x86.h:115](../../cvm2/cvm_jit_x86.h#L115)

```c
void emit_mov32_mem_reg(JitBuf *b, int base, int32_t disp, int src);
```

MOV [base + disp32], r32  (6 bytes: 89 /r mod=10)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `base` | `int` |  |  |
| `disp` | `int32_t` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_lea_sib"></a>

### `emit_lea_sib`

`function` | [cvm2/cvm_jit_x86.h:121](../../cvm2/cvm_jit_x86.h#L121)

```c
void emit_lea_sib(JitBuf *b, int dst, int base, int index, int scale, int32_t disp);
```

LEA r64, [base + index*scale + disp] scale: 0=1, 1=2, 2=4, 3=8 If index == -1, encodes [base + disp] only.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `base` | `int` |  |  |
| `index` | `int` |  |  |
| `scale` | `int` |  |  |
| `disp` | `int32_t` |  |  |

---

<a id="emit_mov_reg_sib"></a>

### `emit_mov_reg_sib`

`function` | [cvm2/cvm_jit_x86.h:126](../../cvm2/cvm_jit_x86.h#L126)

```c
void emit_mov_reg_sib(JitBuf *b, int dst, int base, int index, int scale);
```

MOV r64, [base + index*scale]  (no displacement) scale: 0=1, 1=2, 2=4, 3=8

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `base` | `int` |  |  |
| `index` | `int` |  |  |
| `scale` | `int` |  |  |

---

<a id="emit_mov_sib_reg"></a>

### `emit_mov_sib_reg`

`function` | [cvm2/cvm_jit_x86.h:129](../../cvm2/cvm_jit_x86.h#L129)

```c
void emit_mov_sib_reg(JitBuf *b, int base, int index, int scale, int src);
```

MOV [base + index*scale], r64  (no displacement)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `base` | `int` |  |  |
| `index` | `int` |  |  |
| `scale` | `int` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_push"></a>

### `emit_push`

`function` | [cvm2/cvm_jit_x86.h:136](../../cvm2/cvm_jit_x86.h#L136)

```c
void emit_push(JitBuf *b, int reg);
```

PUSH r64 (1 or 2 bytes depending on register)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_pop"></a>

### `emit_pop`

`function` | [cvm2/cvm_jit_x86.h:139](../../cvm2/cvm_jit_x86.h#L139)

```c
void emit_pop(JitBuf *b, int reg);
```

POP r64

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_add_reg_reg"></a>

### `emit_add_reg_reg`

`function` | [cvm2/cvm_jit_x86.h:146](../../cvm2/cvm_jit_x86.h#L146)

```c
void emit_add_reg_reg(JitBuf *b, int dst, int src);
```

ADD r64, r64  (REX.W 01 /r)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_add_reg_imm32"></a>

### `emit_add_reg_imm32`

`function` | [cvm2/cvm_jit_x86.h:149](../../cvm2/cvm_jit_x86.h#L149)

```c
void emit_add_reg_imm32(JitBuf *b, int dst, int32_t imm);
```

ADD r64, imm32  (sign-extended)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `imm` | `int32_t` |  |  |

---

<a id="emit_sub_reg_reg"></a>

### `emit_sub_reg_reg`

`function` | [cvm2/cvm_jit_x86.h:152](../../cvm2/cvm_jit_x86.h#L152)

```c
void emit_sub_reg_reg(JitBuf *b, int dst, int src);
```

SUB r64, r64  (REX.W 29 /r)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_sub_reg_imm32"></a>

### `emit_sub_reg_imm32`

`function` | [cvm2/cvm_jit_x86.h:155](../../cvm2/cvm_jit_x86.h#L155)

```c
void emit_sub_reg_imm32(JitBuf *b, int dst, int32_t imm);
```

SUB r64, imm32

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `imm` | `int32_t` |  |  |

---

<a id="emit_imul_reg_reg"></a>

### `emit_imul_reg_reg`

`function` | [cvm2/cvm_jit_x86.h:158](../../cvm2/cvm_jit_x86.h#L158)

```c
void emit_imul_reg_reg(JitBuf *b, int dst, int src);
```

IMUL r64, r64  (REX.W 0F AF /r)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_idiv_reg"></a>

### `emit_idiv_reg`

`function` | [cvm2/cvm_jit_x86.h:162](../../cvm2/cvm_jit_x86.h#L162)

```c
void emit_idiv_reg(JitBuf *b, int divisor);
```

IDIV r64  (divides RDX:RAX by r64, quotient in RAX, remainder in RDX) Requires RDX=0 before unsigned, or use CQO for signed.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `divisor` | `int` |  |  |

---

<a id="emit_div_reg"></a>

### `emit_div_reg`

`function` | [cvm2/cvm_jit_x86.h:166](../../cvm2/cvm_jit_x86.h#L166)

```c
void emit_div_reg(JitBuf *b, int divisor);
```

DIV r64  (divides RDX:RAX by r64, unsigned; quotient RAX, remainder RDX) Requires RDX=0 before (xor edx,edx).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `divisor` | `int` |  |  |

---

<a id="emit_cqo"></a>

### `emit_cqo`

`function` | [cvm2/cvm_jit_x86.h:169](../../cvm2/cvm_jit_x86.h#L169)

```c
void emit_cqo(JitBuf *b);
```

CQO  (sign-extend RAX into RDX:RAX)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |

---

<a id="emit_neg_reg"></a>

### `emit_neg_reg`

`function` | [cvm2/cvm_jit_x86.h:172](../../cvm2/cvm_jit_x86.h#L172)

```c
void emit_neg_reg(JitBuf *b, int reg);
```

NEG r64  (REX.W F7 /3)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_inc_reg"></a>

### `emit_inc_reg`

`function` | [cvm2/cvm_jit_x86.h:175](../../cvm2/cvm_jit_x86.h#L175)

```c
void emit_inc_reg(JitBuf *b, int reg);
```

INC r64  (REX.W FF /0) -- 3 bytes, or use add reg,1 (7 bytes but avoids false dependencies)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_dec_reg"></a>

### `emit_dec_reg`

`function` | [cvm2/cvm_jit_x86.h:178](../../cvm2/cvm_jit_x86.h#L178)

```c
void emit_dec_reg(JitBuf *b, int reg);
```

DEC r64

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_and_reg_reg"></a>

### `emit_and_reg_reg`

`function` | [cvm2/cvm_jit_x86.h:185](../../cvm2/cvm_jit_x86.h#L185)

```c
void emit_and_reg_reg(JitBuf *b, int dst, int src);
```

AND r64, r64

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_or_reg_reg"></a>

### `emit_or_reg_reg`

`function` | [cvm2/cvm_jit_x86.h:188](../../cvm2/cvm_jit_x86.h#L188)

```c
void emit_or_reg_reg(JitBuf *b, int dst, int src);
```

OR r64, r64

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_xor_reg_reg"></a>

### `emit_xor_reg_reg`

`function` | [cvm2/cvm_jit_x86.h:191](../../cvm2/cvm_jit_x86.h#L191)

```c
void emit_xor_reg_reg(JitBuf *b, int dst, int src);
```

XOR r64, r64

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_not_reg"></a>

### `emit_not_reg`

`function` | [cvm2/cvm_jit_x86.h:194](../../cvm2/cvm_jit_x86.h#L194)

```c
void emit_not_reg(JitBuf *b, int reg);
```

NOT r64

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_shl_reg_cl"></a>

### `emit_shl_reg_cl`

`function` | [cvm2/cvm_jit_x86.h:197](../../cvm2/cvm_jit_x86.h#L197)

```c
void emit_shl_reg_cl(JitBuf *b, int reg);
```

SHL r64, CL  (shift left by CL)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_shr_reg_cl"></a>

### `emit_shr_reg_cl`

`function` | [cvm2/cvm_jit_x86.h:200](../../cvm2/cvm_jit_x86.h#L200)

```c
void emit_shr_reg_cl(JitBuf *b, int reg);
```

SHR r64, CL  (logical shift right)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_sar_reg_cl"></a>

### `emit_sar_reg_cl`

`function` | [cvm2/cvm_jit_x86.h:203](../../cvm2/cvm_jit_x86.h#L203)

```c
void emit_sar_reg_cl(JitBuf *b, int reg);
```

SAR r64, CL  (arithmetic shift right)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_xor_reg_self"></a>

### `emit_xor_reg_self`

`function` | [cvm2/cvm_jit_x86.h:206](../../cvm2/cvm_jit_x86.h#L206)

```c
void emit_xor_reg_self(JitBuf *b, int reg);
```

XOR reg, reg (zero-idiom, 3 bytes)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_cmp_reg_reg"></a>

### `emit_cmp_reg_reg`

`function` | [cvm2/cvm_jit_x86.h:213](../../cvm2/cvm_jit_x86.h#L213)

```c
void emit_cmp_reg_reg(JitBuf *buf, int a, int breg);
```

CMP r64, r64  (REX.W 39 /r)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `JitBuf *` |  |  |
| `a` | `int` |  |  |
| `breg` | `int` |  |  |

---

<a id="emit_test_reg_reg"></a>

### `emit_test_reg_reg`

`function` | [cvm2/cvm_jit_x86.h:216](../../cvm2/cvm_jit_x86.h#L216)

```c
void emit_test_reg_reg(JitBuf *buf, int a, int breg);
```

TEST r64, r64  (REX.W 85 /r)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `JitBuf *` |  |  |
| `a` | `int` |  |  |
| `breg` | `int` |  |  |

---

<a id="emit_setcc"></a>

### `emit_setcc`

`function` | [cvm2/cvm_jit_x86.h:219](../../cvm2/cvm_jit_x86.h#L219)

```c
void emit_setcc(JitBuf *b, int cc, int dst);
```

SETcc r/m8  (0F 9x /0)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `cc` | `int` |  |  |
| `dst` | `int` |  |  |

---

<a id="emit_jmp_rel32"></a>

### `emit_jmp_rel32`

`function` | [cvm2/cvm_jit_x86.h:226](../../cvm2/cvm_jit_x86.h#L226)

```c
size_t emit_jmp_rel32(JitBuf *b, int32_t rel);
```

JMP rel32  (E9 imm32) -- returns offset of the rel32 for patching

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `rel` | `int32_t` |  |  |

**Returns:** `size_t`

---

<a id="emit_jcc_rel32"></a>

### `emit_jcc_rel32`

`function` | [cvm2/cvm_jit_x86.h:229](../../cvm2/cvm_jit_x86.h#L229)

```c
size_t emit_jcc_rel32(JitBuf *b, int cc, int32_t rel);
```

Jcc rel32  (0F 8x imm32) -- returns offset of the rel32 for patching

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `cc` | `int` |  |  |
| `rel` | `int32_t` |  |  |

**Returns:** `size_t`

---

<a id="emit_jmp_buf"></a>

### `emit_jmp_buf`

`function` | [cvm2/cvm_jit_x86.h:232](../../cvm2/cvm_jit_x86.h#L232)

```c
void emit_jmp_buf(JitBuf *b, size_t target, JitPatches *p);
```

JMP to absolute offset within the buffer (emits rel32, records patch)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `target` | `size_t` |  |  |
| `p` | `JitPatches *` |  |  |

---

<a id="emit_jcc_buf"></a>

### `emit_jcc_buf`

`function` | [cvm2/cvm_jit_x86.h:235](../../cvm2/cvm_jit_x86.h#L235)

```c
void emit_jcc_buf(JitBuf *b, int cc, size_t target, JitPatches *p);
```

Jcc to absolute offset within the buffer

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `cc` | `int` |  |  |
| `target` | `size_t` |  |  |
| `p` | `JitPatches *` |  |  |

---

<a id="jit_apply_patches"></a>

### `jit_apply_patches`

`function` | [cvm2/cvm_jit_x86.h:238](../../cvm2/cvm_jit_x86.h#L238)

```c
void jit_apply_patches(JitBuf *b, const JitPatches *p);
```

Apply all patches: for each patch, compute rel32 = target - (patch_off + 4)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `p` | `JitPatches *` |  |  |

---

<a id="emit_call_rel32"></a>

### `emit_call_rel32`

`function` | [cvm2/cvm_jit_x86.h:241](../../cvm2/cvm_jit_x86.h#L241)

```c
size_t emit_call_rel32(JitBuf *b, int32_t rel);
```

CALL rel32  (E8 imm32)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `rel` | `int32_t` |  |  |

**Returns:** `size_t`

---

<a id="emit_call_reg"></a>

### `emit_call_reg`

`function` | [cvm2/cvm_jit_x86.h:244](../../cvm2/cvm_jit_x86.h#L244)

```c
void emit_call_reg(JitBuf *b, int reg);
```

CALL r/m64  (FF /2, 2 bytes)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `reg` | `int` |  |  |

---

<a id="emit_ret"></a>

### `emit_ret`

`function` | [cvm2/cvm_jit_x86.h:247](../../cvm2/cvm_jit_x86.h#L247)

```c
void emit_ret(JitBuf *b);
```

RET  (C3)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |

---

<a id="emit_syscall"></a>

### `emit_syscall`

`function` | [cvm2/cvm_jit_x86.h:254](../../cvm2/cvm_jit_x86.h#L254)

```c
void emit_syscall(JitBuf *b);
```

SYSCALL  (0F 05)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |

---

<a id="emit_int3"></a>

### `emit_int3`

`function` | [cvm2/cvm_jit_x86.h:257](../../cvm2/cvm_jit_x86.h#L257)

```c
void emit_int3(JitBuf *b);
```

INT3  (CC) -- debug breakpoint

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |

---

<a id="emit_nop"></a>

### `emit_nop`

`function` | [cvm2/cvm_jit_x86.h:260](../../cvm2/cvm_jit_x86.h#L260)

```c
void emit_nop(JitBuf *b);
```

NOP  (90)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |

---

<a id="emit_call_abs"></a>

### `emit_call_abs`

`function` | [cvm2/cvm_jit_x86.h:269](../../cvm2/cvm_jit_x86.h#L269)

```c
void emit_call_abs(JitBuf *b, void *func, int scratch);
```

Emit a CALL to a C function pointer (trampoline-free, uses absolute call).

Loads the function address into a scratch register and calls it. Clobbers: the scratch register used.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `func` | `void *` |  |  |
| `scratch` | `int` |  |  |

---

<a id="emit_and_reg_imm32"></a>

### `emit_and_reg_imm32`

`function` | [cvm2/cvm_jit_x86.h:272](../../cvm2/cvm_jit_x86.h#L272)

```c
void emit_and_reg_imm32(JitBuf *buf, int dst, int32_t imm);
```

AND r64, imm32

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `imm` | `int32_t` |  |  |

---

<a id="emit_movzx_reg_reg8"></a>

### `emit_movzx_reg_reg8`

`function` | [cvm2/cvm_jit_x86.h:275](../../cvm2/cvm_jit_x86.h#L275)

```c
void emit_movzx_reg_reg8(JitBuf *buf, int dst, int src);
```

MOVZX r64, r/m8  (REX.W 0F B6 /r) -- used for SETcc zero-extension

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `JitBuf *` |  |  |
| `dst` | `int` |  |  |
| `src` | `int` |  |  |

---

<a id="emit_rex"></a>

### `emit_rex`

`function` | [cvm2/cvm_jit_x86.h:278](../../cvm2/cvm_jit_x86.h#L278)

```c
void emit_rex(JitBuf *buf, int w, int r, int x, int rex_b);
```

REX prefix: exposed for inline asm emission

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `JitBuf *` |  |  |
| `w` | `int` |  |  |
| `r` | `int` |  |  |
| `x` | `int` |  |  |
| `rex_b` | `int` |  |  |

---

<a id="emit_modrm"></a>

### `emit_modrm`

`function` | [cvm2/cvm_jit_x86.h:281](../../cvm2/cvm_jit_x86.h#L281)

```c
void emit_modrm(JitBuf *buf, int mod, int reg, int rm);
```

ModRM byte: exposed for inline asm emission

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `buf` | `JitBuf *` |  |  |
| `mod` | `int` |  |  |
| `reg` | `int` |  |  |
| `rm` | `int` |  |  |

---

<a id="emit_mov_mem_imm8"></a>

### `emit_mov_mem_imm8`

`function` | [cvm2/cvm_jit_x86.h:288](../../cvm2/cvm_jit_x86.h#L288)

```c
void emit_mov_mem_imm8(JitBuf *b, int base, int32_t disp, uint8_t imm);
```

MOV byte [base + disp], imm8  (REX.C6 /0)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `base` | `int` |  |  |
| `disp` | `int32_t` |  |  |
| `imm` | `uint8_t` |  |  |

---

<a id="emit_mov_mem_imm32"></a>

### `emit_mov_mem_imm32`

`function` | [cvm2/cvm_jit_x86.h:291](../../cvm2/cvm_jit_x86.h#L291)

```c
void emit_mov_mem_imm32(JitBuf *b, int base, int32_t disp, int32_t imm);
```

MOV qword [base + disp], imm32 (sign-extended)  (REX.W C7 /0)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `b` | `JitBuf *` |  |  |
| `base` | `int` |  |  |
| `disp` | `int32_t` |  |  |
| `imm` | `int32_t` |  |  |

---

## Macros

<a id="jit_max_patches"></a>

### `JIT_MAX_PATCHES`

`macro` | [cvm2/cvm_jit_x86.h:53](../../cvm2/cvm_jit_x86.h#L53)

```c
#define JIT_MAX_PATCHES
```

---
