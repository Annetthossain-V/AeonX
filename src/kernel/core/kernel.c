#include <limine.h>
#include <stddef.h>
#include <stdint.h>
#include <dev/scrn/scrn.h>
#include "kernel.h"
#include <core/kern64.h>
#include <dev/cpu/gdt.h>
#include <dev/scrn/internelscrn.hxx>

void _main(volatile struct limine_framebuffer_request* framebuffer_req, volatile struct limine_memmap_request* memmap_req)
{
  set_gdt();
  set_tss();

  if (!screen_init(framebuffer_req)) goto hang;

hang:
  hcf();
}
