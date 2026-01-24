#[unsafe(no_mangle)]
pub unsafe extern "C" fn atomic_move(atom: *mut u64, value: u64) {
  todo!();
}

#[allow(unused)]
#[unsafe(no_mangle)]
pub unsafe extern "C" fn atomic_add(atom: *mut u64, value: u64) {
  todo!();
}

struct AtomicU64 {
  pub atom: u64,
}

impl AtomicU64 {
  pub fn new() -> Self {
    Self { atom: 0 }
  }
}
