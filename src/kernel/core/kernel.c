#include "kernel.h"
#include <core/kern64.h>
#include <dev/cpu/gdt.h>
#include <dev/cpu/mp.h>
#include <dev/memory/pmm/phy_ mem.h>
#include <dev/scrn/internelscrn.h>
#include <dev/scrn/scrn.h>
#include <limine.h>
#include <stddef.h>
#include <stdint.h>

// screen must be initialized for this function to work
void panic(const char *msg) {
  // TODO
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
  if (mp_init(mp_req) != 0)
    panic("Unable to initialize MP");

  for (size_t x = 0; x < 582; ++x)
    for (size_t y = 0; y < 324; ++y)
      pixel(x, y, 23, 43, 93);

  return;
}
