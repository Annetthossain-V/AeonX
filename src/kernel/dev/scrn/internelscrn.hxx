#pragma once
#include <limine.h>
#include <type.h>


#ifdef __cplusplus
namespace scrn {
extern "C" {

BOOL save_screen_request(volatile struct limine_framebuffer_request* screen_frame_request);
volatile struct limine_framebuffer* get_screen();

#endif

#ifdef __cplusplus
} }
#endif
