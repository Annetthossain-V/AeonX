#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <limine.h>
#include <stddef.h>

#define USABLE_MEMORY_SIZE 4096

struct memory_base {
  uint64_t base;
  uint64_t length;
} __attribute__((packed));


bool init_memory(volatile struct limine_memmap_request* memmap_req);

volatile void* get_memory_buffer(size_t* length);
