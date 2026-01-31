#include <dev/scrn/internelscrn.h>
#include <limine.h>
#include <stdbool.h>
#include <stddef.h>

// we're only gonna be using frame-buffer[0]
static volatile struct limine_framebuffer_request *SCREEN_FRAME_REQUEST = NULL;

int save_screen_request(
    volatile struct limine_framebuffer_request *screen_frame_request) {
  if (screen_frame_request == NULL)
    return 1;
  if (screen_frame_request->response == NULL)
    return 1;

  SCREEN_FRAME_REQUEST = screen_frame_request;
  return 0;
}

volatile struct limine_framebuffer *get_screen(void) {
  if (SCREEN_FRAME_REQUEST->response->framebuffer_count < 1)
    return NULL;
  return SCREEN_FRAME_REQUEST->response->framebuffers[0];
}
