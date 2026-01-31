#pragma once
#include <limine.h>

#ifdef __cplusplus
extern "C" {
#endif

void _main(volatile struct limine_framebuffer_request *framebuffer_req,
           volatile struct limine_memmap_request *memmap_req,
           volatile struct limine_mp_request *mp_req);

void hcf() __attribute__((noreturn));
void panic(const char *msg) __attribute__((noreturn));

#ifdef __cplusplus
}
#endif
