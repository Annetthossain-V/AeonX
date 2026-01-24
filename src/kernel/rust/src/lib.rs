#![no_std]
#![allow(unused_imports)]

use core::panic::PanicInfo;
use cpu::atomic::*;

unsafe extern "C" {
  fn hcf() -> !;
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
  unsafe {
    hcf();
  }
}
