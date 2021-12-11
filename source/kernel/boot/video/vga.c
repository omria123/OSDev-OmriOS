#include <stdint.h>

#include "kernel/exceptions.h"
#include "kernel/video/screen.h"

typedef struct {
    char c;
    uint8_t color;
} ega_char_t;


error_t vga_putchar(uint32_t row, uint32_t col, char c, uint8_t color) {
    ega_char_t ega_char = {0};
    error_t err = SUCCESS;
    ega_char.c = c;
    ega_char.color = color;
    CHECK_AND_RETHROW(screen_write(row, col, &ega_char, sizeof ega_char));

    cleanup:
    return err;
}
char_settings_t vga_char_settings = {2, 1};
