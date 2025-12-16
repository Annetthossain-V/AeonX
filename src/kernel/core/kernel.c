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
  if (!set_gdt()) goto hang;
  if (!screen_init(framebuffer_req)) goto hang;

  volatile struct limine_framebuffer* screen = get_screen();
  while (true) {
    for (volatile uint64_t y = 0; y < screen->height; ++y) {
      for (volatile uint64_t x = 0; x < screen->width; ++x) {
        Pixel(screen, x, y, 255, 0, 0);
      }
    }
    for (volatile uint64_t y = 0; y < screen->height; ++y) {
      for (volatile uint64_t x = 0; x < screen->width; ++x) {
        Pixel(screen, x, y, 0, 255, 0);
      }
    }
    for (volatile uint64_t y = 0; y < screen->height; ++y) {
      for (volatile uint64_t x = 0; x < screen->width; ++x) {
        Pixel(screen, x, y, 0, 0, 255);
      }
    }
  }

hang:
  hcf();
}
