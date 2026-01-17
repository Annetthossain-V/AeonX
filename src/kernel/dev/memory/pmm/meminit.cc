#include "phy_ mem.h"
#include <core/kern64.h>
#include <limine.h>
#include <stddef.h>
#include <stdint.h>

static volatile struct limine_memmap_request *memmap_request;

extern "C" int memory_init(volatile struct limine_memmap_request *memmap_req) {
  if (memmap_req == nullptr)
    return 1;
  if (memmap_req->response == nullptr)
    return 1;
  if (memmap_req->response->entries == nullptr)
    return 1;

  for (uint64_t i = 0; i < memmap_req->response->entry_count; ++i) {
    if (memmap_req->response->entries[i] == nullptr)
      return 1;
  }

  // save the ptr
  memmap_request = memmap_req;
  return 0;
}

extern "C" memory_base_t get_memory_base(int type, int index) {
  return {.base = 0, .length = 0, .type = 0};
}
