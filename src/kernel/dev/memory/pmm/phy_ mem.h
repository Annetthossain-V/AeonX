#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limine.h>

struct memory_base {
  uint64_t base;
  uint64_t length;
} __attribute__((packed));

#ifdef __cplusplus
namespace memory {
extern "C" {
#endif

bool init_memory(volatile struct limine_memmap_request* memmap_req);

volatile struct limine_memmap_request* get_limine_memory_map();

#ifdef __cplusplus
} }
#endif
