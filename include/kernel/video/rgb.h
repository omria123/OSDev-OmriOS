#ifndef OSDEV_RGB_H
#define OSDEV_RGB_H

#include <stdint.h>

#include "kernel/exceptions.h"
#include "kernel/video/screen.h"


error_t rgb_putchar(uint32_t row, uint32_t col, uint8_t c, uint8_t color);

extern char_settings_t rgb_char_settings;

#endif //OSDEV_RGB_H
