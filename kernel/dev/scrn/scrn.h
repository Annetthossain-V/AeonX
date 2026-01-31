#pragma once
#include <limine.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define DEFAULT_RED 17
#define DEFAULT_GREEN 17
#define DEFAULT_BLUE 27

#define DEFAULT_TEXT_RED 249
#define DEFAULT_TEXT_GREEN 226
#define DEFAULT_TEXT_BLUE 176

struct DisplayTextInformation {
  uint64_t DisplayWidth;
  uint64_t DisplayHeigth;
  uint64_t CursorX;
  uint64_t CursorY;
} __attribute__((packed));

#ifdef __cplusplus
extern "C" {
#endif

int screen_init(volatile struct limine_framebuffer_request *frame_buffer);
void Pixel(uint64_t x, uint64_t y, uint8_t r, uint8_t g, uint8_t b);
void clear_screen(void);

void write_text_init(uint64_t x, uint64_t y);

void write_text_n(const char *text, size_t n);
void write_text(const char *text);
void change_color(void);

#ifdef __cplusplus
}
#endif
