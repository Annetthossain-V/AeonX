#pragma once
#include <limine.h>
#include <type.h>



#ifdef __cplusplus
namespace term {
extern "C" {
#endif

BOOL init_terminal_screen(volatile struct limine_framebuffer_request* frame_buffer);

#ifdef __cplusplus
} }
#endif
