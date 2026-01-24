#pragma once
#include <stdint.h>

void atomic_move(uint64_t *atom, uint64_t value);
void atomic_add(uint64_t *atom, uint64_t value);
void atomic_sub(uint64_t *atom, uint64_t value);
void atomic_mul(uint64_t *atom, uint64_t value);
void atomic_div(uint64_t *atom, uint64_t value);
uint32_t atomic_compare(uint64_t *atom,
                        uint64_t value); // 0 if true or 1 if false
