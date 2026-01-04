#include <limine.h>
#include "phy_ mem.h"
#include <stdint.h>
#include <core/kern64.h>
#include <stddef.h>

bool init_memory(volatile struct limine_memmap_request *memmap_req)
{
  if (memmap_req == NULL) return false;
  if (memmap_req->response == NULL) return false;
  if (memmap_req->response->entries == NULL) return false;



  return true;
}
