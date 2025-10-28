#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limine.h>
#include "kernel.h"
#include "../asm/x86_64.h"

#define MAX_CPUS 1
#define KERNEL_STACK_SIZE 0x4000

// uint8_t kernel_stacks[MAX_CPUS][KERNEL_STACK_SIZE] __attribute__((aligned(16)));


// __attribute__((used, section(".limine_requests")))
static volatile LIMINE_BASE_REVISION(4);

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
  .id = LIMINE_FRAMEBUFFER_REQUEST,
  .revision = 0
};

__attribute__((used, section(".limine_requests")))
static volatile struct limine_memmap_request memmap_request = {
  .id = LIMINE_MEMMAP_REQUEST,
  .revision = 0
};

/*
__attribute__((used, section(".limine_requests")))
static volatile struct limine_smp_request smp_request = {
  .id = LIMINE_SMP_REQUEST,
  .revision = 0
};
*/

__attribute__((used, section(".limine_requests_start")))
static volatile LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile LIMINE_REQUESTS_END_MARKER;


void _start(void) {
  /* uint64_t* stack_top = (uint64_t*)(kernel_stacks[0] + KERNEL_STACK_SIZE);
  asm volatile("mov %0, %%rsp" :: "r"(stack_top));
  asm volatile("mov %0, %%rbp" :: "r"(stack_top)); */

  if (LIMINE_BASE_REVISION_SUPPORTED == false)
    halt();

  if (framebuffer_request.response == NULL || framebuffer_request.response->framebuffer_count < 1)
    halt();

  if (memmap_request.response == NULL)
    halt();

  _main(&framebuffer_request, &memmap_request);
}
