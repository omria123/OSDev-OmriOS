//
// Created by omri on 01/12/2021.
//
#include "stdlib/string.h"

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}
