//
// Created by omri on 04/12/2021.
//

#ifndef OSDEV_SCREEN_H
#define OSDEV_SCREEN_H

#include <stddef.h>
#include <stdint.h>

#include <exceptions.h>

enum video_mode {
    IND = 0,
    RGB = 1,
    EGA = 2,
};


error_t screen_write(size_t row, size_t col, void *buf, size_t);
error_t screen_read(size_t row, size_t col, void *buf, size_t);
error_t screen_initalize(uint32_t multiboot_header);
error_t screen_mode(enum video_mode *mode );

#endif //OSDEV_SCREEN_H
