#include "kernel.h"
#include <core/kern64.h>
#include <dev/cpu/gdt.h>
#include <dev/memory/pmm/phy_ mem.h>
#include <dev/scrn/internelscrn.h>
#include <dev/scrn/scrn.h>
#include <limine.h>
#include <stddef.h>
#include <stdint.h>

void _main(volatile struct limine_framebuffer_request *framebuffer_req,
           volatile struct limine_memmap_request *memmap_req,
           volatile struct limine_mp_request *mp_req) {

  if (init_memory(memmap_req) != 0)
    __asm__("jmp hcf");
  if (screen_init(framebuffer_req) != 0)
    __asm__("jmp hcf");

  return;
}
