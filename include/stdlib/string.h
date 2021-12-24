//
// Created by omri on 01/12/2021.
//

#ifndef OSDEV_STRING_H
#define OSDEV_STRING_H

#include "stdbool.h"
#include "stddef.h"
#include "stdint.h"



size_t strlen(const char* str);
int isspace(char c);

void *
memcpy(void *dest, const void *src, size_t len);

#endif //OSDEV_STRING_H
