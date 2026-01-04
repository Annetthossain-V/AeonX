#pragma once

#define DEBUG_QEMU_PORT 0xE9

void hcf();

static inline void outb(unsigned short port, unsigned char byte) {
  __asm__ volatile ("out %1, %0" :: "a"(byte), "Nd"(port));
}


