# Security Findings

## HIGH (1)

- `cvm2/cvm.c:372` (in `native_strcpy`) -- Buffer overflow risk: strcpy — use strncpy or snprintf instead [CWE-121]
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
