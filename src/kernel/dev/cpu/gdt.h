#pragma once
#include <stdbool.h>

#ifdef __cplusplus
namespace cpu {
extern "C" {
#endif

bool set_gdt();

#ifdef __cplusplus
} }
#endif
