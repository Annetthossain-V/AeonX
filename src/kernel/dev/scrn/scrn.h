#pragma once
#include <limine.h>
#include <stdbool.h>

#define DEFAULT_RED 17
#define DEFAULT_GREEN 17
#define DEFAULT_BLUE 27

#define DRAWBLK_MAX_HEIGTH 1
#define DRAWBLK_MAX_WIDTH 1

#ifdef __cplusplus
extern "C" {
#endif

int screen_init(volatile struct limine_framebuffer_request *frame_buffer);
void Pixel(volatile struct limine_framebuffer *fb, uint64_t x, uint64_t y,
           uint8_t r, uint8_t g, uint8_t b);
int pixel(uint64_t x, uint64_t y, uint8_t r, uint8_t g, uint8_t b);
void clear_screen(void);

int drawblk(uint64_t x, uint64_t y); // return number of pixels written

#ifdef __cplusplus
}
#endif
