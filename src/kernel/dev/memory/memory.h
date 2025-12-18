#pragma once
#include <stdbool.h>
#include <limine.h>

#ifdef __cplusplus
namespace memory {
extern "C" {
#endif

bool init_memory(volatile struct limine_memmap_request* memmap_req);

#ifdef __cplusplus
} }
#endif
