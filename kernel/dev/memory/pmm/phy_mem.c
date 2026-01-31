#include "phy_mem.h"
#include <core/kern64.h>
#include <limine.h>
#include <stddef.h>
#include <stdint.h>

int memory_init(volatile struct limine_memmap_request *memmap_req) {
  if (memmap_req == NULL)
    return 1;

  return 0;
}
