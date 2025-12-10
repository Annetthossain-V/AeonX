#pragma once
#include <limine.h>
#include <type.h>

#ifdef __cplusplus
namespace scrn {
extern "C" {
#endif

BOOL screen_init(volatile struct limine_framebuffer_request* frame_buffer);

#ifdef __cplusplus
} }
#endif
