#include "phy_ mem.h"
#include <core/kern64.h>
#include <limine.h>
#include <stddef.h>
#include <stdint.h>

extern "C" int init_memory(volatile struct limine_memmap_request *memmap_req) {
  if (memmap_req == NULL)
    return 1;
  if (memmap_req->response == NULL)
    return 1;
  if (memmap_req->response->entries == NULL)
    return 1;

  return 0;
}
