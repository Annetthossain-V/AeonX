#include <core/kern64.h>
#include <dev/scrn/scrn.h>
#include <limine.h>
#include <stddef.h>

static volatile struct limine_framebuffer *DISPLAY = NULL;

int screen_init(volatile struct limine_framebuffer_request *frame_buffer) {
  if (frame_buffer == NULL)
    return 1;
  if (frame_buffer->response->framebuffer_count < 1)
    return 1;

  DISPLAY = frame_buffer->response->framebuffers[0];
  clear_screen();
  return 0;
}

void Pixel(uint64_t x, uint64_t y, uint8_t r, uint8_t g, uint8_t b) {
  if (x >= DISPLAY->width || y >= DISPLAY->height)
    return;

  uint8_t bytes_per_pixel = DISPLAY->bpp / 8;
  uint8_t *row = (uint8_t *)DISPLAY->address + y * DISPLAY->pitch;
  uint8_t *p = row + x * bytes_per_pixel;

  uint32_t color = 0;

  color |= ((uint32_t)r >> (8 - DISPLAY->red_mask_size))
           << DISPLAY->red_mask_shift;
  color |= ((uint32_t)g >> (8 - DISPLAY->green_mask_size))
           << DISPLAY->green_mask_shift;
  color |= ((uint32_t)b >> (8 - DISPLAY->blue_mask_size))
           << DISPLAY->blue_mask_shift;

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
  for (volatile uint64_t y = 0; y < DISPLAY->height; ++y) {
    for (volatile uint64_t x = 0; x < DISPLAY->width; ++x) {
      Pixel(x, y, DEFAULT_RED, DEFAULT_GREEN, DEFAULT_BLUE);
    }
  }
}
