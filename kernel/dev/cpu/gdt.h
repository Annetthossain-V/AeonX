#pragma once
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void set_gdt(void);
void set_tss(void);

#ifdef __cplusplus
}
#endif