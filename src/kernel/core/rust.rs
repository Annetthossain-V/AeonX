#![no_std]
#![no_main]
#![allow(unused)]
use core::panic::PanicInfo;

#[path = "../libkrn/bindings.rs"]
mod bindings;

#[path = "../dev/dev.rs"]
mod dev;

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
  unsafe {
    bindings::hcf();
  }
}
