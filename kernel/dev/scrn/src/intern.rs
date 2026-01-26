use core::result::Result;
use kstd::err::ErrorKind::DisplayFramebufferInvalid;
use limine::{request::FramebufferRequest, response::FramebufferResponse};

pub const DEFAULT_RED: u8 = 17;
pub const DEFAULT_GREEN: u8 = 17;
pub const DEFAULT_BLUE: u8 = 27;

static mut DISPLAY_FRAMEBUFFER: *const FramebufferResponse = core::ptr::null();

#[allow(unsafe_op_in_unsafe_fn)]
pub unsafe fn initialize_display(
  framebuffer_request: &FramebufferRequest,
) -> Result<(), kstd::err::ErrorKind> {
  if framebuffer_request.get_response().is_none() {
    return Err(DisplayFramebufferInvalid);
  }

  let response = match framebuffer_request.get_response() {
    Some(res) => res,
    None => return Err(DisplayFramebufferInvalid),
  };

  if response.framebuffers().count() < 1 {
    return Err(DisplayFramebufferInvalid);
  }

  DISPLAY_FRAMEBUFFER = response;
  if DISPLAY_FRAMEBUFFER.is_null() {
    return Err(DisplayFramebufferInvalid);
  }

  clear_screen();
  Ok(())
}

pub fn draw_pixel(x: u64, y: u64, r: u8, g: u8, b: u8) {
  unsafe {
    let framebuffer = match (*DISPLAY_FRAMEBUFFER).framebuffers().nth(0) {
      Some(frame) => frame,
      None => return,
    };

    let bytes_per_pixel: u8 = (framebuffer.bpp() / 8) as u8;
    let row: *mut u8 = ((framebuffer.addr() as u64) + y * framebuffer.pitch()) as *mut u8;
    let p: *mut u8 = ((row as u64) + x * (bytes_per_pixel as u64)) as *mut u8;

    let mut color: u32 = 0;
    color |= ((r as u32) >> (8 - framebuffer.red_mask_size())) << framebuffer.red_mask_shift();
    color |= ((g as u32) >> (8 - framebuffer.green_mask_size())) << framebuffer.green_mask_shift();
    color |= ((b as u32) >> (8 - framebuffer.blue_mask_size())) << framebuffer.blue_mask_shift();

    match bytes_per_pixel {
      4 => {
        (*(p as *mut u32)) = color;
      }
      3 => {
        (*p) = (color & 0xFF) as u8;
        (*p.add(1)) = ((color >> 8) & 0xFF) as u8;
        (*p.add(2)) = ((color >> 16) & 0xFF) as u8;
      }
      2 => *(p as *mut u16) = (color & 0xFFFF) as u16,
      _ => {
        for i in 0..bytes_per_pixel {
          (*p.add(i as usize)) = ((color >> (8 * i as usize)) & 0xFF) as u8;
        }
      }
    }
  }
}

pub fn clear_screen() {
  unsafe {
    let framebuffer = match (*DISPLAY_FRAMEBUFFER).framebuffers().nth(0) {
      Some(frame) => frame,
      None => return,
    };

    for y in 0..framebuffer.height() {
      for x in 0..framebuffer.width() {
        draw_pixel(x, y, DEFAULT_RED, DEFAULT_GREEN, DEFAULT_BLUE);
      }
    }
  }
}
