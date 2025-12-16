#include <dev/cpu/gdt.h>
#include <stdint.h>

#define NUM_GDT_ENTRIES 5

static uint64_t gdt_entries[NUM_GDT_ENTRIES];

struct GDTR {
  uint16_t limit;
  uint64_t base;
} __attribute__((packed));

static struct GDTR gdtr = {
  .limit = sizeof(gdt_entries) - 1,
  .base = (uint64_t)gdt_entries,
};

static inline uint64_t make_gdt_entry(uint8_t access, uint8_t flags)
{
  // base = 0, limit = 0 for 64-bit flat segments;
  // place access at bits 40..47, flags at bits 52..55
  return ((uint64_t)access << 40) | ((uint64_t)flags << 52);
}

void cpu::set_gdt(void)
{
  // null descriptor
  gdt_entries[0] = 0;

  // access bytes
  const uint8_t KCODE_ACC = 0x9A; // P=1, DPL=0, S=1, type=0xA (exec/read)
  const uint8_t KDATA_ACC = 0x92; // P=1, DPL=0, S=1, type=0x2 (data/write)
  const uint8_t UCODE_ACC = 0xFA; // KCODE_ACC | (3 << 5)
  const uint8_t UDATA_ACC = 0xF2; // KDATA_ACC | (3 << 5)

  // flags nibble (G, D/B, L, AVL)
  const uint8_t CODE_FLAGS = 0xA; // 1 0 1 0 -> G=1, D/B=0, L=1, AVL=0
  const uint8_t DATA_FLAGS = 0x8; // 1 0 0 0 0> G=1, D/B=0, L=0, AVL=0

  gdt_entries[1] = make_gdt_entry(KCODE_ACC, CODE_FLAGS);
  gdt_entries[2] = make_gdt_entry(KDATA_ACC, DATA_FLAGS);
  gdt_entries[3] = make_gdt_entry(UCODE_ACC, CODE_FLAGS);
  gdt_entries[4] = make_gdt_entry(UDATA_ACC, DATA_FLAGS);

  asm volatile
  (
    "lgdt %0 \n"
    "push qword ptr 0x08 \n"
    "lea rax, [rip + 1f] \n"
    "push rax \n"
    "retfq \n"

    "1: \n"
    "mov ax, 0x10 \n"
    "mov ds, ax \n"
    "mov es, ax \n"
    "mov fs, ax \n"
    "mov gs, ax \n"
    "mov ss, ax \n"
    :
    : "m"(gdtr)
    : "rax", "ax", "memory"
  );

  return;
}
