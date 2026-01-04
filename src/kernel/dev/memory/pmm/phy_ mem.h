#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limine.h>
#include <stddef.h>

bool init_memory(volatile struct limine_memmap_request* memmap_req);
