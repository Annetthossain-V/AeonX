#include "kernel.h"
#include <core/kern64.h>
#include <dev/cpu/gdt.h>
#include <dev/cpu/mp.h>
#include <dev/memory/pmm/phy_mem.h>
#include <dev/scrn/internelscrn.h>
#include <dev/scrn/scrn.h>
#include <limine.h>
#include <stddef.h>
#include <stdint.h>

// screen must be initialized for this function to work
void panic(const char *msg) {
  // TODO:
  __asm__("nop");
  hcf();
}

void _main(volatile struct limine_framebuffer_request *framebuffer_req,
           volatile struct limine_memmap_request *memmap_req,
           volatile struct limine_mp_request *mp_req) {

  if (memory_init(memmap_req) != 0)
    hcf();
  if (screen_init(framebuffer_req) != 0)
    hcf();
  write_text("Screen initialized!\n");

  return;
}
