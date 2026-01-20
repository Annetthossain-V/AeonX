#pragma once
#include <limine.h>
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int save_screen_request(
    volatile struct limine_framebuffer_request *screen_frame_request);
volatile struct limine_framebuffer *get_screen(void);

int init_drawblk(uint64_t screen_height, uint64_t screen_width);

#ifdef __cplusplus
}
#endif
