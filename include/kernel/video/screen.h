#ifndef OSDEV_SCREEN_H
#define OSDEV_SCREEN_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "kernel/exceptions.h"

enum video_mode {
    IND = 0,
    RGB = 1,
    EGA = 2,
};

typedef struct {
    uint8_t width;
    uint8_t height;
} char_settings_t;

typedef struct {
    size_t width;
    size_t height;
    size_t bpp;
    size_t pitch;
} screen_settings_t;

error_t screen_is_valid_access(size_t row, size_t col, size_t size, bool *result);

error_t screen_write(size_t row, size_t col, void *buf, size_t);

error_t screen_read(size_t row, size_t col, void *buf, size_t);

error_t screen_initalize(uint32_t multiboot_header);

error_t screen_mode(enum video_mode *mode);

error_t screen_read_settings(screen_settings_t *settings);

#endif //OSDEV_SCREEN_H
