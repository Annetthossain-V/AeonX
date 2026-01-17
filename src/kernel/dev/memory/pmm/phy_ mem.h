#pragma once
#include <limine.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

struct memory_base {
  uint64_t base;
  uint64_t length;
  uint16_t type;
} __attribute__((packed));
typedef struct memory_base memory_base_t;

#ifdef __cplusplus
extern "C" {
#endif

int memory_init(volatile struct limine_memmap_request *memmap_req);

memory_base_t get_memory_base(int type, int index);

#ifdef __cplusplus
}
#endif
