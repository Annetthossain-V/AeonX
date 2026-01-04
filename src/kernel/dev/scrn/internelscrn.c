#include <dev/scrn/internelscrn.h>
#include <limine.h>
#include <stddef.h>
#include <stdbool.h>

// we're only gonna be using frame-buffer[0]
volatile static struct limine_framebuffer_request* SCREEN_FRAME_REQUEST = NULL;

bool save_screen_request(volatile struct limine_framebuffer_request* screen_frame_request)
{
  if (screen_frame_request == NULL) return false;
  if (screen_frame_request->response == NULL) return false;

  SCREEN_FRAME_REQUEST = screen_frame_request;
  return true;
}

volatile struct limine_framebuffer* get_screen(void)
{
  if (SCREEN_FRAME_REQUEST->response->framebuffer_count < 1) return NULL;
  return SCREEN_FRAME_REQUEST->response->framebuffers[0];
}
