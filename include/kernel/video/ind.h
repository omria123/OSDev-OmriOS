#ifndef OSDEV_IND_H
#define OSDEV_IND_H

#include <stdint.h>

#include "kernel/exceptions.h"
#include "kernel/video/screen.h"

error_t ind_putchar(uint32_t row, uint32_t col, uint8_t c, uint8_t color);

extern char_settings_t ind_char_settings;

#endif //OSDEV_IND_H
