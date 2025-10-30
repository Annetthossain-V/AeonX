#pragma once
#include <stdint.h>
#include <stddef.h>

#ifndef NULL
#define NULL (void*)0
#endif

void* memcpy(void *restrict dest, const void *restrict src, size_t n);
void* memset(void* s, int c, size_t n);
void* memmove(void* dest, const void* src, size_t n);
int memcmp(const void* s1, const void* s2, size_t n);

unsigned long strlen(const char* s);
int strcmp(const char* s1, const char* s2);
char* strchr(const char* s, int c);
char* strcpy(char* dest, const char* src);
