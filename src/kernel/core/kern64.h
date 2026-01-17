#pragma once

#define DEBUG_QEMU_PORT 0xE9

#ifdef __cplusplus
extern "C" {
#endif

void hcf() __attribute__((noreturn));
void panic(const char *msg) __attribute__((noreturn));

static inline void outb(unsigned short port, unsigned char byte) {
  __asm__ volatile("out %1, %0" ::"a"(byte), "Nd"(port));
}

void _soft_kernel_reboot(void);

#ifdef __cplusplus
}
#endif
