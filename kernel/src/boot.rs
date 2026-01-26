use core::arch::global_asm;

#[used]
#[unsafe(link_section = ".limine_requests")]
static LIMINE_BASE_REVISION: limine::BaseRevision = limine::BaseRevision::new();

#[used]
#[unsafe(link_section = ".limine_requests")]
static FRAMEBUFFER_REQUEST: limine::request::FramebufferRequest =
  limine::request::FramebufferRequest::new();

#[used]
#[unsafe(link_section = ".limine_requests")]
static MEMMAP_REQUEST: limine::request::MemoryMapRequest = limine::request::MemoryMapRequest::new();

#[used]
#[unsafe(link_section = ".limine_requests")]
static CPU_MP_REQUEST: limine::request::MpRequest = limine::request::MpRequest::new();

#[used]
#[unsafe(link_section = ".limine_requests_start")]
static LIMINE_REQUEST_START_MARKER: [u64; 2] = [0xf6b8f4b39de7d1ae, 0xfab91a6940fcb9cf];

// Request end marker
#[used]
#[unsafe(link_section = ".limine_requests_end")]
static LIMINE_REQUEST_END_MARKER: [u64; 2] = [0x4f9c170638d9e6ec, 0xf50a6fa2c068768];

#[unsafe(no_mangle)]
pub extern "C" fn __boot_kernel() -> ! {
  unsafe {
    if !LIMINE_BASE_REVISION.is_supported() {
      crate::hcf();
    }
    if FRAMEBUFFER_REQUEST.get_response().is_none() {
      crate::hcf();
    }
    if MEMMAP_REQUEST.get_response().is_none() {
      crate::hcf();
    }

    match crate::__rust_start(&FRAMEBUFFER_REQUEST, &MEMMAP_REQUEST) {
      Ok(_) => {}
      Err(_) => {}
    };
    crate::hcf();
  }
}

#[rustfmt::skip]
global_asm!
(
  ".section .bss",
  ".align 16",
  ".skip 8388608", // 8 MiB
  ".globl kstack_top",
  "kstack_top:",

  ".section .text",
  ".globl _start",
  ".type _start, @function",
  "_start:",
    "lea rsp, kstack_top[rip]",
    "mov rbp, rsp",
    "call __enable_sse",
    "jmp __boot_kernel",

  ".globl __enable_sse",
  ".type __enable_sse, @function",
  "__enable_sse:",
    "push rbp",
    "mov rbp, rsp",
    
    "mov eax, 0x1",
    "cpuid",
    "test edx, 1<<25",
    "jz hcf", // sse support not found
    
    "mov rax, cr0",
    "and ax, 0xFFFB",
    "or ax, 0x2",

    "mov cr0, rax",
    "mov rax, cr4",

    "or ax, 3<<9",
    "mov cr4, rax",

    "pxor xmm0, xmm0",
    "pop rbp",
    "ret"
);
