#include "phy_ mem.h"
#include <stdint.h>

extern memory_base __xqz_usable_memory_base[USABLE_MEMORY_SIZE];
extern uint32_t __xqz_usable_memory_count;

extern "C" volatile void* memory::get_memory_buffer(size_t* length)
{
  return (void*)0;
}
