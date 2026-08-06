#ifndef STRING_H
#define STRING_H

#include <stddef.h>

int strcmp(const char *lhs, const char *rhs);
size_t strlen(const char *str);
void *memset(void *dest, int ch, size_t count);
void *memcpy(void *dest, const void *src, size_t count);

#endif
