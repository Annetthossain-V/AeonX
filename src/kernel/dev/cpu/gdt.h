#pragma once
#include <stdbool.h>

#ifdef __cplusplus
namespace cpu {
extern "C" {
#endif

void set_gdt(void);

#ifdef __cplusplus
} }
#endif
