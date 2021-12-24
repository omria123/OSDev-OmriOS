//
// Created by omri on 01/12/2021.
//
#include "stdlib/string.h"

size_t strlen(const char *str) {
    size_t len = 0;
    while (str[++len]);
    return len;
}


void *
memcpy(void *dest, const void *src, size_t len) {
    char *d = dest;
    const char *s = src;
    while (len--)
        *d++ = *s++;
    return dest;
}


int isspace(char c) {
    switch (c) {
        case ' ':
        case '\t':
        case '\v':
        case '\f':
        case '\r':
        case '\b':
        case '\n':
            break;
        default:
            return 0;
    }
    return 1;
}
