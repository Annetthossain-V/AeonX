#include "kernel.h"
#include <core/kern64.h>
#include <limine.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

__attribute__((used, section(".limine_requests"))) static volatile uint64_t
    limine_base_revision[] = LIMINE_BASE_REVISION(4);

__attribute__((
    used,
    section(
        ".limine_requests"))) static volatile struct limine_framebuffer_request
    framebuffer_request = {.id = LIMINE_FRAMEBUFFER_REQUEST_ID, .revision = 0};

__attribute__((
    used,
    section(".limine_requests"))) static volatile struct limine_memmap_request
    memmap_request = {.id = LIMINE_MEMMAP_REQUEST_ID, .revision = 0};

__attribute__((
    used, section(".limine_requests"))) static volatile struct limine_mp_request
    mp_request = {.id = LIMINE_MP_REQUEST_ID, .revision = 0};

__attribute__((
    used,
    section(".limine_requests_"
            "start"))) static volatile uint64_t limine_request_start_marker[] =
    LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end"))) static volatile uint64_t
    limine_request_end_marker[] = LIMINE_REQUESTS_END_MARKER;

void start_c(void) {
  if (LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false)
    hcf();
  if (framebuffer_request.response == NULL ||
      framebuffer_request.response->framebuffer_count < 1)
    hcf();
  if (memmap_request.response == NULL)
    hcf();

  _main(&framebuffer_request, &memmap_request, &mp_request);
}
