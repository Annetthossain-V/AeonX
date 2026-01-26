#![no_std]
#![allow(internal_features)]
#![feature(core_intrinsics)]
#![no_main]

use core::arch::asm;
use core::intrinsics::unreachable;
use core::panic::PanicInfo;
use core::result::Result;
use kstd::err::ErrorKind;

#[allow(unused_imports)]
use boot::__boot_kernel;

mod boot;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
  loop {}
}

#[unsafe(no_mangle)]
unsafe extern "C" fn hcf() -> ! {
  unsafe {
    #[rustfmt::skip]
    asm!
    (
      "2:",
      "cli",
      "hlt",
      "jmp 2b"
    );
    unreachable();
  }
}

#[allow(unsafe_op_in_unsafe_fn)]
#[unsafe(no_mangle)]
unsafe fn __rust_start(
  framebuffer_request: &limine::request::FramebufferRequest,
  memmap_request: &limine::request::MemoryMapRequest,
) -> Result<(), ErrorKind> {
  cpu::gdt::set_gdt();
  cpu::gdt::set_tss();

  memory::initialize_memory(memmap_request)?;
  scrn::intern::initialize_display(framebuffer_request)?;

  Ok(())
}
