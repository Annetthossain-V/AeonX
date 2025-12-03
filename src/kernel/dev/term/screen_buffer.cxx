#include "screen_buffer.h"
#include <string.h>

static uint32_t screen_index[2] = {0, 0}; // 1 = current_index, 2 = max_index
static uint16_t** screen_buffer = NULL;

extern "C" uint32_t* term::get_screen_index() { return screen_index; }
