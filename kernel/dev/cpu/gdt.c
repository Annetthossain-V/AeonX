#include <dev/cpu/gdt.h>
#include <stddef.h>
#include <stdint.h>

#define NUM_GDT_ENTRIES 7

static uint64_t gdt_entries[NUM_GDT_ENTRIES];

struct GDTR {
  uint16_t limit;
  uint64_t base;
} __attribute__((packed));

static struct GDTR gdtr = {
    .limit = sizeof(gdt_entries) - 1,
    .base = (uint64_t)gdt_entries,
};

struct __attribute__((packed)) tss64 {
  uint32_t reserved0;
  uint64_t rsp0;
  uint64_t rsp1;
  uint64_t rsp2;
  uint64_t reserved1;
  uint64_t ist1;
  uint64_t ist2;
  uint64_t ist3;
  uint64_t ist4;
  uint64_t ist5;
  uint64_t ist6;
  uint64_t ist7;
  uint64_t reserved2;
  uint16_t reserved3;
  uint16_t iomap_base; // offset to IO bitmap; set to sizof(tss) to disable
};

static struct tss64 tss __attribute__((aligned(16)));

static uint8_t df_stack[8192] __attribute__((aligned(16)));
static uint8_t irq_stack[4096] __attribute__((aligned(16)));

static inline uint64_t make_gdt_entry(uint8_t access, uint8_t flags) {
  // base = 0, limit = 0 for 64-bit flat segments;
  // place access at bits 40..47, flags at bits 52..55
  return ((uint64_t)access << 40) | ((uint64_t)flags << 52);
}

static void make_tss_descriptor(uint64_t *gdt, int index, void *tss_ptr,
                                uint32_t tss_size) {
  uint64_t base = (uint64_t)tss_ptr;
  uint32_t limit = tss_size - 1;

  // Access byte: 0x89 = P=1, DPL=0, S=0 (system), Type=0x9 (available 64-bit
  // TSS)
  const uint8_t access = 0x89;

  // Flags nibble: (G << 3) | (DB << 2) | (L << 1) | AVL
  // For TSS: G=0, DB=0, L=0, AVL=0 (so flags = 0)
  const uint8_t flags = 0x0;

  // conpose low 8 bytes
  uint64_t low = 0;
  low |= (uint64_t)(limit & 0xFFFF);            // limit[15:0]
  low |= (uint64_t)(base & 0xFFFFFF) << 16;     // base[23:0] -> bits 16..39
  low |= (uint64_t)access << 40;                // access byte -> bits 48..47
  low |= (uint64_t)((limit >> 16) & 0xF) << 48; // limit[19:16] -> bits 40..51
  low |= (uint64_t)(flags & 0xF) << 52;         // flags nibble -> bits 52..55
  low |= (uint64_t)((base >> 24) & 0xFF) << 56; // base[31:24] -? bits 56..63

  uint64_t high = 0;
  high |= (uint64_t)((base >> 32) & 0xFFFFFFFF);

  gdt[index] = low;
  gdt[index + 1] = high;
}

void set_tss(void) {
  for (size_t i = 0; i < sizeof(tss); ++i)
    ((uint8_t *)&tss)[i] = 0;

  extern uint8_t kstack_top;
  tss.rsp0 = (uint64_t)kstack_top;

  tss.ist1 =
      (uint64_t)(df_stack + sizeof(df_stack)); // IST1 -> double-fault stack
  tss.ist2 =
      (uint64_t)(irq_stack + sizeof(irq_stack)); // IST2 -> example IRQ stack

  tss.iomap_base = sizeof(tss);

  const int tss_gdt_index = 5;
  make_tss_descriptor(gdt_entries, tss_gdt_index, &tss, sizeof(tss));

  // shouldn't be needed
  gdtr.limit = sizeof(gdt_entries) - 1;
  gdtr.base = (uint64_t)gdt_entries;

  __asm__ volatile("lgdt %0 \n" ::"m"(gdtr) : "memory");

  uint16_t tss_selector = (uint16_t)(tss_gdt_index << 3);

  __asm__ volatile("mov ax, %0 \n"
                   "ltr ax \n"
                   : // no outputs
                   : "r"(tss_selector)
                   : "ax", "memory");

  return;
}

void set_gdt(void) {
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

  __asm__ volatile("lgdt %0 \n"
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
                   : "rax", "ax", "memory");

  return;
}
