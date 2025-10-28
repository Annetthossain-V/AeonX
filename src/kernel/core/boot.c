#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include "kernel.h"
#include "../asm/x86_64.h"

__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(4);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

void _start(void) {
  if (LIMINE_BASE_REVISION_SUPPORTED == false) 
    halt();

  if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1)
    halt();

  struct limine_framebuffer* framebuffer = framebuffer_request.response->framebuffers[0];
  for (size_t i = 0; i < 100; i++) {
    volatile uint32_t* fb_ptr = framebuffer->address;
    fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xffffff;
  }

  _main();
}
