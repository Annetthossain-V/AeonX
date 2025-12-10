#include <limine.h>
#include <stddef.h>
#include <stdint.h>
#include <dev/scrn/scrn.h>
#include "kernel.h"


void _main(volatile struct limine_framebuffer_request* framebuffer_req, volatile struct limine_memmap_request* memmap_req)
{
  if (!screen_init(framebuffer_req)) {
    __asm__("hlt");
    __asm__("jmp .");
  }

  // debug draw
  struct limine_framebuffer* framebuff = framebuffer_req->response->framebuffers[0];
  for (size_t i = 0; i < 500; i++) {
    volatile uint32_t* fp_ptr = framebuff->address;
    fp_ptr[i * (framebuff->pitch / 4) + i] = 0xffffff;
  }

  __asm__("hlt");
  __asm__("jmp .");
}
