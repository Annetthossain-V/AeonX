#include <limine.h>
#include "phy_ mem.h"
#include <string.h>
#include <stdint.h>
#include <core/kern64.h>

static volatile struct limine_memmap_request *limine_memmap_req = NULL;

struct memory_base __xqz_usable_memory_base[USABLE_MEMORY_SIZE] __attribute__((aligned(16)));
uint32_t __xqz_usable_memory_count = 0;

bool init_memory(volatile struct limine_memmap_request *memmap_req)
{
  if (memmap_req == NULL) return false;
  if (memmap_req->response == NULL) return false;
  if (memmap_req->response->entries == NULL) return false;
  if (memmap_req->response->entry_count < 1) return false;

  limine_memmap_req = memmap_req;

  for (volatile uint64_t i = 0; i < memmap_req->response->entry_count; ++i)
  {
    if (memmap_req->response->entries[i]->type == LIMINE_MEMMAP_USABLE)
    {
      __xqz_usable_memory_base[__xqz_usable_memory_count].base = memmap_req->response->entries[i]->base;
      __xqz_usable_memory_base[__xqz_usable_memory_count].length = memmap_req->response->entries[i]->length;
      ++__xqz_usable_memory_count;
      if (__xqz_usable_memory_count >= USABLE_MEMORY_SIZE - 1) break;
    }
  }

  return true;
}
