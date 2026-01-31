#pragma once
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void *__alloc_mem_(uint32_t size);
void __free_mem_(void *mem);

#ifdef __cplusplus
}
#endif
