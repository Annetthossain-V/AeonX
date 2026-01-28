use crate::intern::SCREEN_LOCK;
use noto_sans_mono_bitmap;

pub fn write_char(c: char) {
  let lock = SCREEN_LOCK.lock();

  drop(lock);
}
