#pragma once

#define DEBUG_QEMU_PORT 0xE9

#ifdef __cplusplus
extern "C" {
#endif

void hcf();

static inline void outb(unsigned short port, unsigned char byte) {
  __asm__ volatile ("out %1, %0" :: "a"(byte), "Nd"(port)); 
}

#ifdef __cplusplus
}
#endif
