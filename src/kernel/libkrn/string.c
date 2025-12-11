#include <stdint.h>
#include "string.h"

void* memcpy(void* /*restrict*/ dest, const void* /*restrict*/ src, size_t n)
{
  uint8_t* restrict pdest = (uint8_t* restrict)dest;
  const uint8_t* restrict psrc = (const uint8_t* restrict)src;

  for (size_t i = 0; i < n; i++) {
    pdest[i] = psrc[i];
  }

  return dest;
}

void* memset(void* s, int c, size_t n)
{
  uint8_t* p = (uint8_t*)s;
  for (size_t i = 0; i < n; i++) {
    p[i] = (uint8_t)c;
  }

  return s;
}

void* memmove(void* dest, const void* src, size_t n)
{
  uint8_t* pdest = (uint8_t*)dest;
  const uint8_t* psrc = (const uint8_t*)src;

  if (src > dest) {
    for (size_t i = 0; i < n; i++) {
      pdest[i] = psrc[i];
    }
  } else if (src < dest) {
    for (size_t i = n; i > 0; i--) {
      pdest[i-1] = psrc[i-1];
    }
  }

  return dest;
}

int memcmp(const void* s1, const void* s2, size_t n)
{
  const uint8_t* p1 = (const uint8_t*)s1;
  const uint8_t* p2 = (const uint8_t*)s2;

  for (size_t i = 0; i < n; i++) {
    if (p1[i] != p2[i]) {
      return p1[i] < p2[i] ? -1 : 1;
    }
  }

  return 0;
}

unsigned long strlen(const char* s)
{
  unsigned long len = 0;
  while (s[len] != '\0') {
    len++;
  }
  return len;
}

int strcmp(const char* s1, const char* s2)
{
  int i = 0;
  while (s1[i] == s2[i]) {
    if (s1[i] == '\0' || s2[i] == '\0') break;
    i++;
  }

  if (s1[i] == '\0' && s2[i] == '\0')
    return 0;
  else
    return s1[i] - s2[i];
}

const char* strchr(const char* s, int c)
{
  while(*s != '\0') {
    if (*s == c) return s;
    s++;
  }
  return NULL;
}

char* strcpy(char* dest, const char* src)
{
  char* _dest = dest;
  unsigned long src_len = strlen(src);

  for (unsigned long i = 0; i < src_len; i++) {
    dest[i] = src[i];
  }
  dest[src_len] = '\0';

  return _dest;
}
