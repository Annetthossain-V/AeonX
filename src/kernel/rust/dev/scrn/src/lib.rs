#![no_std]
use core::ffi::c_void;

pub const DRAWBLK_MAX_HEIGTH: u64 = 256;
pub const DRWABLK_MAX_WIDTH: u64 = 512;

unsafe extern "C" {
  pub fn drawblk(x: u64, y: u64, r: u8, g: u8, b: u8) -> c_void;
  pub fn clear_screen() -> c_void;
}
