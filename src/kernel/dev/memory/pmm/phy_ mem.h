#pragma once
#include <limine.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int init_memory(volatile struct limine_memmap_request *memmap_req);
