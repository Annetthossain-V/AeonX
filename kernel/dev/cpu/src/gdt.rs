#![allow(static_mut_refs)]
use core::arch::asm;
use core::mem;

const NUM_GDT_ENTRIES: usize = 7;

static mut GDT_ENTRIES: [u64; NUM_GDT_ENTRIES] = [0; NUM_GDT_ENTRIES];

#[repr(C, packed)]
struct GDTR {
  limit: u16,
  base: u64,
}

static mut GDTR_INSTANCE: GDTR = GDTR {
  limit: (NUM_GDT_ENTRIES * mem::size_of::<u64>() - 1) as u16,
  base: 0, // this will be set at runtime
};

#[repr(C, packed)]
struct Tss64 {
  reserved0: u64,
  rsp0: u64,
  rsp1: u64,
  rsp2: u64,
  reserved1: u64,
  ist1: u64,
  ist2: u64,
  ist3: u64,
  ist4: u64,
  ist5: u64,
  ist6: u64,
  ist7: u64,
  reserved2: u64,
  reserved3: u16,
  iomap_base: u16,
}

#[repr(align(16))]
struct AlignedTss(Tss64);

static mut TSS: AlignedTss = AlignedTss(Tss64 {
  reserved0: 0,
  rsp0: 0,
  rsp1: 0,
  rsp2: 0,
  reserved1: 0,
  ist1: 0,
  ist2: 0,
  ist3: 0,
  ist4: 0,
  ist5: 0,
  ist6: 0,
  ist7: 0,
  reserved2: 0,
  reserved3: 0,
  iomap_base: 0,
});

#[repr(align(16))]
struct AlignedStack<const N: usize>([u8; N]);

static mut DF_STACK: AlignedStack<8192> = AlignedStack([0; 8192]);
static mut IRQ_STACK: AlignedStack<4096> = AlignedStack([0; 4096]);

#[inline]
fn make_gdt_entry(access: u8, flags: u8) -> u64 {
  // base = 0, limit = 0 for 64-bit flat segments;
  // place access at bits 40..47, flags at bit 52..55
  ((access as u64) << 40) | ((flags as u64) << 52)
}

fn make_tss_descriptor(gdt: &mut [u64], index: usize, tss_ptr: *const Tss64, tss_size: u32) {
  let base = tss_ptr as u64;
  let limit = tss_size - 1;

  // Access byte: 0x89 = P=1, DPL=0, S=0 (system), Type=0x9 (available 64-bit TSS)
  const ACCESS: u64 = 0x89;

  // Flags nibble: (G << 3) | (DB << 2) | (L << 1) | AVL
  // For TSS: G=0, DB=0, L=0, AVL=0 (so flags = 0)
  const FLAGS: u8 = 0x0;

  // compose low 8 bytes
  let mut low: u64 = 0;
  low |= (limit & 0xFFFF) as u64; // limit[15:0]
  low |= ((base & 0xFFFFFF) as u64) << 16; // base[23:0] -> bits 16..39
  low |= (ACCESS as u64) << 40; // access byte -> bits 40..47
  low |= (((limit >> 16) & 0xF) as u64) << 48; // limit[19:16] -> bits 48..51
  low |= ((FLAGS & 0xF) as u64) << 52; // flags nibble -> bits 52..55
  low |= (((base >> 24) & 0xFF) as u64) << 56; // base[31:24] -> bits 56..63

  let high: u64 = ((base >> 32) & 0xFFFFFFFF) as u64;

  gdt[index] = low;
  gdt[index + 1] = high;
}

#[allow(unsafe_op_in_unsafe_fn)]
pub unsafe fn set_tss() {
  unsafe extern "C" {
    static kstack_top: u8;
  }

  let tss_ptr = &raw mut TSS.0 as *mut Tss64 as *mut u8;
  for i in 0..mem::size_of::<Tss64>() {
    *tss_ptr.add(i) = 0;
  }

  TSS.0.rsp0 = &kstack_top as *const u8 as u64;

  // iST1 -> double-fault stack
  TSS.0.ist1 = DF_STACK.0.as_ptr() as u64 + DF_STACK.0.len() as u64;

  // IST2 -> example IRQ stack
  TSS.0.ist2 = IRQ_STACK.0.as_ptr() as u64 + IRQ_STACK.0.len() as u64;

  TSS.0.iomap_base = mem::size_of::<Tss64>() as u16;

  const TSS_GDT_INDEX: usize = 5;
  make_tss_descriptor(
    &mut GDT_ENTRIES,
    TSS_GDT_INDEX,
    &TSS.0,
    mem::size_of::<Tss64>() as u32,
  );

  // Update GDT
  #[rustfmt::skip]
  asm!
  (
    "lgdt [{}]",
    in(reg) &GDTR_INSTANCE,
    options(nostack)
  );

  let tss_selector: u16 = (TSS_GDT_INDEX << 3) as u16;

  #[rustfmt::skip]
  asm!
  (
    "mov ax, {0:x}",
    "ltr ax",
    in(reg) tss_selector,
    out("ax") _,
    options(nostack)
  );
}

#[allow(unsafe_op_in_unsafe_fn)]
pub unsafe fn set_gdt() {
  // Null descriptor
  GDT_ENTRIES[0] = 0;

  const KCODE_ACC: u8 = 0x9A; // P=1, DPL=0, S=1, type=0xA (exec/read)
  const KDATA_ACC: u8 = 0x92; // P=1, DPL=0, S=1, type=0x2 (data/write)
  const UCODE_ACC: u8 = 0xFA; // KCODE_ACC | (3 << 5)
  const UDATA_ACC: u8 = 0xF2; // KDATA_ACC | (3 << 5)

  // Flags nibble (G, D/B, L, AVL)
  const CODE_FLAGS: u8 = 0xA; // 1 0 1 0 -> G=1, D/B=0, L=1, AVL=0
  const DATA_FLAGS: u8 = 0x8; // 1 0 0 0 -> G=1, D/B=0, L=0, AVL=0

  GDT_ENTRIES[1] = make_gdt_entry(KCODE_ACC, CODE_FLAGS);
  GDT_ENTRIES[2] = make_gdt_entry(KDATA_ACC, DATA_FLAGS);
  GDT_ENTRIES[3] = make_gdt_entry(UCODE_ACC, CODE_FLAGS);
  GDT_ENTRIES[4] = make_gdt_entry(UDATA_ACC, DATA_FLAGS);

  GDTR_INSTANCE.base = GDT_ENTRIES.as_ptr() as u64;

  // Load GDT and update segment registers
  #[rustfmt::skip]
  asm!
  (
    "lgdt [{}]",
    "push 0x08",
    "lea rax, [rip + 2f]",
    "push rax",
    "retfq",
    "2:",
    "mov ax, 0x10",
    "mov ds, ax",
    "mov es, ax",
    "mov fs, ax",
    "mov gs, ax",
    "mov ss, ax",
    in(reg) &GDTR_INSTANCE,
    out("rax") _,
    options(nostack)
  );
}
