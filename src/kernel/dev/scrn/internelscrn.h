#pragma once
#include <limine.h>
#include <stdbool.h>

bool save_screen_request(volatile struct limine_framebuffer_request* screen_frame_request);
volatile struct limine_framebuffer* get_screen(void);
