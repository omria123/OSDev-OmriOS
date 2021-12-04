//
// Created by omri on 04/12/2021.
//

#ifndef OSDEV_PIXEL_H
#define OSDEV_PIXEL_H

#include <stddef.h>

#include <exceptions.h>

enum video_mode {
    INV_MODE = 0,
     = 1,
    EGA = 2,
};


error_t pixel_write(size_t row, size_t col, void *buf);
error_t pixel_read(size_t row, size_t col, void *buf);
error_t pixel_initalize();
error_t pixel_mode();

#endif //OSDEV_PIXEL_H
