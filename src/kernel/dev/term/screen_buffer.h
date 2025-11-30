#pragma once
#include <stdint.h>
#include <type.h>

#ifdef __cplusplus
namespace term {
extern "C" {
#endif

uint32_t* get_screen_index();
BOOL clear_screen();

#ifdef __cplusplus
} }
#endif
