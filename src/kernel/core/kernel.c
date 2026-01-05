#include <limine.h>
#include <stddef.h>
#include <stdint.h>
#include <dev/scrn/scrn.h>
#include "kernel.h"
#include <core/kern64.h>
#include <dev/cpu/gdt.h>
#include <dev/scrn/internelscrn.h>
#include <dev/memory/pmm/phy_ mem.h>


void _main(volatile struct limine_framebuffer_request* framebuffer_req, volatile struct limine_memmap_request* memmap_req)
{
  if (!init_memory(memmap_req)) asm("jmp hcf");
  if (!screen_init(framebuffer_req)) asm("jmp hcf");

  _soft_kernel_reboot();
  return;
}
