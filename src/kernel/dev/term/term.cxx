#include "term.h"
#include <limine.h>
#include <string.h>
#include <type.h>

static struct limine_framebuffer_request* global_scrn = NULL;

extern "C" BOOL term::init_terminal_screen(volatile struct limine_framebuffer_request* frame_buffer) {
  if (frame_buffer == NULL)
    return FALSE;

  return TRUE;
}
