#include <dev/scrn/scrn.h>
#include <dev/scrn/internelscrn.hxx>
#include <limine.h>
#include <string.h>
#include <type.h>

extern "C" BOOL scrn::screen_init(volatile struct limine_framebuffer_request* frame_buffer) {
  if (frame_buffer == NULL) return FALSE;

  // save screen buffer
  if (!scrn::save_screen_request(frame_buffer)) return FALSE;



  return TRUE;
}
