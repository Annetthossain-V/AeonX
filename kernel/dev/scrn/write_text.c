#include <dev/scrn/scrn.h>
#include <stddef.h>
#include <stdint.h>

extern const unsigned char *GetBitmap(unsigned char ch);

static struct DisplayTextInformation DisplayInformation = {0};

static inline void newline(void);

static inline void scroll(void);

static void write_char_at(unsigned char ch, uint64_t x, uint64_t y, uint8_t r,
                          uint8_t g, uint8_t b) {

  const unsigned char *glyph = GetBitmap(ch);
  if (glyph == NULL)
    return;

  for (int row = 0; row < 16; row++) {
    for (int col = 0; col < 8; col++) {
      if (glyph[row] & (1 << col)) {
        Pixel(x + col, y + row, r, g, b);
      } else {
        Pixel(x + col, y + row, DEFAULT_RED, DEFAULT_GREEN, DEFAULT_BLUE);
      }
    }
  }
}

static void write_char(void);

void change_color(void);

void write_text_n(const char *text, size_t n) {
  // nothing for now
  return;
}

void write_text(const char *text) {
  if (text == NULL)
    return;

  write_char_at('A', 0, 0, DEFAULT_TEXT_RED, DEFAULT_TEXT_GREEN,
                DEFAULT_TEXT_BLUE);
  return;
}

void write_text_init(uint64_t x, uint64_t y) {
  DisplayInformation.DisplayWidth = x;
  DisplayInformation.DisplayHeigth = y;
  DisplayInformation.CursorX = 0;
  DisplayInformation.CursorY = 0;
  return;
}
