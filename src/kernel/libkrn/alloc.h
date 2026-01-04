#include <dev/memory/memintern.h>
#include <stdint.h>

static inline void* kmalloc(uint32_t size) {
  return __alloc_mem_(size);
}

static inline void kfree(void* mem) {
  return __free_mem_(mem);
}
