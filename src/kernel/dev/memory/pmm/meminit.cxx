#include <limine.h>
#include "phy_ mem.h"
#include <stdint.h>

static volatile struct limine_memmap_request *limine_memmap_req = nullptr;

static memory_base usable_memory_base[4096] __attribute__((aligned(16)));
static uint32_t usable_memory_count = 0;

bool memory::init_memory(volatile struct limine_memmap_request *memmap_req)
{
  if (memmap_req == nullptr) return false;
  if (memmap_req->response == nullptr) return false;
  if (memmap_req->response->entries == nullptr) return false;
  if (memmap_req->response->entry_count < 1) return false;

  limine_memmap_req = memmap_req;

  for (volatile uint64_t i = 0; i < memmap_req->response->entry_count; ++i)
  {
    if (memmap_req->response->entries[i]->type == LIMINE_MEMMAP_USABLE)
    {
      usable_memory_base[usable_memory_count].base = memmap_req->response->entries[i]->base;
      usable_memory_base[usable_memory_count].length = memmap_req->response->entries[i]->length;
      ++usable_memory_count;
    }
  }

  return true;
}

volatile struct limine_memmap_request* memory::get_limine_memory_map() { return limine_memmap_req; }
