#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include "kernel.h"


__attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(4);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request memmap_request = {
  .id = LIMINE_MEMMAP_REQUEST,
  .revision = 0
};

/*
__attribute__((used, section(".limine_requests")))
static volatile struct limine_smp_request smp_request = {
  .id = LIMINE_SMP_REQUEST,
  .revision = 0
};
*/

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;

void _start_c(void) 
{
  if (LIMINE_BASE_REVISION_SUPPORTED == false) {
    __asm__("hlt");
    __asm__("jmp .");
  }
  if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1) {
    __asm__("hlt");
    __asm__("jmp .");
  }
  if (memmap_request.response == NULL) {
    __asm__("hlt");
    __asm__("jmp .");
  }

  _main(&framebuffer_request, &memmap_request);
}
