#![no_std]
mod phy_memory;
use core::result::Result;
use kstd::err::ErrorKind;
use limine::request::MemoryMapRequest;

pub fn initialize_memory(memory_map_request: &MemoryMapRequest) -> Result<(), ErrorKind> {
  Ok(())
}
