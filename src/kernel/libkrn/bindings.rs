#[path = "type.rs"]
pub mod rstype;

unsafe extern "C" {
  pub fn hcf() -> !;
}
