#include <stddef.h>
#include "../include/string.h"

int strcmp(const char *lhs, const char *rhs) {
    const unsigned char *lh = (const unsigned char *)lhs;
    const unsigned char *rh = (const unsigned char *)rhs;
    int i = 0;
    while (lh[i] == rh[i]) {
        if (lh[i] == '\0') return 0;
        i++;
    }
    return lh[i] - rh[i];
}

size_t strlen(const char *str) {
    size_t count = 0;
    while (*str) { count++; str++; }
    return count;
}

void *memset(void *dest, int ch, size_t count) {
    unsigned char *ptr = (unsigned char *)dest;
    for (size_t i = 0; i < count; i++)
        ptr[i] = (unsigned char)ch;
    return dest;
}

void *memcpy(void *dest, const void *src, size_t count) {
    unsigned char *ptr = (unsigned char *)dest;
    const unsigned char *s = (const unsigned char *)src;
    for (size_t i = 0; i < count; i++)
        ptr[i] = s[i];
    return dest;
}
