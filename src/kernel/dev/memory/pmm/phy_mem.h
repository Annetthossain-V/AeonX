#pragma once
#include <limine.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int memory_init(volatile struct limine_memmap_request *memmap_req);

uint64_t get_usable_ram(uint64_t *size);

#ifdef __cplusplus
}
#endif
