

pub export fn __alloc_mem_(size: u32) ?*void {
  _ = size;
  return null;
}

pub export fn __free_mem_(ptr: ?*void) void {
  _ = ptr;
  return;
}
