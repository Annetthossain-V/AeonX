#include <dev/scrn/internelscrn.hxx>
#include <limine.h>

extern "C" volatile struct limine_framebuffer_request* scrn::SCREEN_FRAME_REQUEST = nullptr;

extern "C" BOOL scrn::save_screen_request(volatile struct limine_framebuffer_request* screen_frame_request)
{
  return FALSE;
}
