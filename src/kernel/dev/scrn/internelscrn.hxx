#pragma once
#include <limine.h>
#include <type.h>
#include <stdint.h>

#ifdef __cplusplus
namespace scrn {
extern "C" {

extern volatile struct limine_framebuffer_request* SCREEN_FRAME_REQUEST;

BOOL save_screen_request(volatile struct limine_framebuffer_request* screen_frame_request);
void get_screen(uint16_t n);

#endif

#ifdef __cplusplus
} }
#endif
