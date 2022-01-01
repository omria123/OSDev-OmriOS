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

void *
memset(char *dest, char c, size_t size) {
    register size_t n = (size + 7) / 8;
    register char *p = dest;
    switch (size % 8) {
        case 0:
            do {
                *p++ = c;
                case 7:
                    *p++ = c;
                case 6:
                    *p++ = c;
                case 5:
                    *p++ = c;
                case 4:
                    *p++ = c;
                case 3:
                    *p++ = c;
                case 2:
                    *p++ = c;
                case 1:
                    *p++ = c;
            } while (--n > 0);
    }
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
