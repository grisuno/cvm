# Recipe: Fix a Security Finding

- `cvm2/cvm.c:372` [high] C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead
  Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.

Verify: `readmenator . --audit && grep -c 'CRITICAL\|HIGH' readmenator-agent/SECURITY.md`
