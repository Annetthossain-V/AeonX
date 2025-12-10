#pragma once

#ifdef __cplusplus
extern "C" {
#endif

static inline void hcf()
{
  __asm__("cli");
  __asm__("hlt");
  __asm__("jmp .");
}

#ifdef __cplusplus
}
#endif
