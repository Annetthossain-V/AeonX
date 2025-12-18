#include "memory.h"


bool memory::init_memory(volatile struct limine_memmap_request *memmap_req) 
{
  if (memmap_req == nullptr) return false;

  return true;
}
