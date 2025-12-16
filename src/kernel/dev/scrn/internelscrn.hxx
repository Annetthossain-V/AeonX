#pragma once
#include <limine.h>
#include <stdbool.h>


#ifdef __cplusplus
namespace scrn {
extern "C" {
#endif

bool save_screen_request(volatile struct limine_framebuffer_request* screen_frame_request);
volatile struct limine_framebuffer* get_screen();

#ifdef __cplusplus
} }
#endif
