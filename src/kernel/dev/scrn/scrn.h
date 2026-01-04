#pragma once
#include <limine.h>
#include <stdbool.h>

bool screen_init(volatile struct limine_framebuffer_request* frame_buffer);
void Pixel(volatile struct limine_framebuffer* fb, uint64_t x, uint64_t y, uint8_t r, uint8_t g, uint8_t b);
void pixel(int64_t x, uint64_t y, uint8_t r, uint8_t g, uint8_t b);
void clear_screen(void);
