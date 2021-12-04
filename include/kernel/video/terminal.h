//
// Created by omri on 01/12/2021.
//

#ifndef OSDEV_TERMINAL_H
#include <exceptions.h>

error_t terminal_initalize();

error_t terminal_write_cstring(const char *string);


#define OSDEV_TERMINAL_H

#endif //OSDEV_TERMINAL_H
