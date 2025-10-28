#include <limine.h>
#include <stddef.h>
#include <stdint.h>
#include "kernel.h"
#include "../asm/x86_64.h"


void _main(volatile struct limine_framebuffer_request* framebuffer_req, 
           volatile struct limine_memmap_request* memmap_req) {
  
  struct limine_framebuffer* framebuff = framebuffer_req->response->framebuffers[0];
  for (size_t i = 0; i < 250; i++) {
    volatile uint32_t* fp_ptr = framebuff->address;
    fp_ptr[i * (framebuff->pitch / 4) + i] = 0xffffff;
  }

  halt();
}

