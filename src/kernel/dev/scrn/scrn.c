#include <core/kern64.h>
#include <dev/scrn/internelscrn.h>
#include <dev/scrn/scrn.h>
#include <limine.h>
#include <stddef.h>
#include <string.h>

// pixel is implemented in scrn.s

// puts safety over performance
// TODO: make this faster
void Pixel(volatile struct limine_framebuffer *fb, uint64_t x, uint64_t y,
           uint8_t r, uint8_t g, uint8_t b) {
  if (!fb || x >= fb->width || y >= fb->height)
    return;

  uint8_t bytes_per_pixel = fb->bpp / 8;
  uint8_t *row = (uint8_t *)fb->address + y * fb->pitch;
  uint8_t *p = row + x * bytes_per_pixel;

  uint32_t color = 0;
  if (fb->red_mask_size)
    color |= ((uint32_t)r >> (8 - fb->red_mask_size)) << fb->red_mask_shift;
  if (fb->green_mask_size)
    color |= ((uint32_t)g >> (8 - fb->green_mask_size)) << fb->green_mask_shift;
  if (fb->blue_mask_size)
    color |= ((uint32_t)b >> (8 - fb->blue_mask_size)) << fb->blue_mask_shift;

  switch (bytes_per_pixel) {
  case 4:
    *(volatile uint32_t *)p = color;
    break;
  case 3: // little endian
    p[0] = color & 0xFF;
    p[1] = (color >> 8) & 0xFF;
    p[2] = (color >> 16) & 0xFF;
    break;
  case 2:
    *(volatile uint16_t *)p = (uint16_t)(color & 0xFFFF);
    break;
  default:
    for (unsigned i = 0; i < bytes_per_pixel; ++i)
      p[i] = (color >> (8 * i)) & 0xFF;
    break;
  }
}

void clear_screen(void) {
  volatile struct limine_framebuffer *screen = get_screen();
  for (volatile uint64_t y = 0; y < screen->height; ++y) {
    for (volatile uint64_t x = 0; x < screen->width; ++x) {
      Pixel(screen, x, y, DEFAULT_RED, DEFAULT_GREEN, DEFAULT_BLUE);
    }
  }
}

int screen_init(volatile struct limine_framebuffer_request *frame_buffer) {
  if (frame_buffer == NULL)
    return 1;

  // save screen buffer
  if (save_screen_request(frame_buffer) != 0)
    return 1;

  clear_screen();
  return 0;
}
