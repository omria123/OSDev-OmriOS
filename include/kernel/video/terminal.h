#ifndef OSDEV_TERMINAL_H
#include <kernel/exceptions.h>

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

error_t terminal_initalize(uint32_t multiboot2_header);

error_t terminal_write_cstring(const char *string);
error_t terminal_write(const char *data, size_t size);

error_t terminal_set_color(uint8_t color);
error_t terminal_get_color(uint8_t *color);
error_t terminal_reset(void);
error_t terminal_putchar(char c);

error_t terminal_set_pos(size_t row, size_t col);

#define OSDEV_TERMINAL_H

#endif //OSDEV_TERMINAL_H
