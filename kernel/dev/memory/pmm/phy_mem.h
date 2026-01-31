#pragma once
#include <limine.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int memory_init(volatile struct limine_memmap_request *memmap_req);

#ifdef __cplusplus
}
#endif
