#define __FILE_ID__ 2
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
    CHECK_AND_RETHROW(screen_write(row, col * sizeof ega_char, &ega_char, sizeof ega_char));
    cleanup:
    return err;
}

error_t vga_fill_screen(uint8_t color) {
    error_t err = SUCCESS;
    size_t i = 0;
    size_t j = 0;
    screen_settings_t settings = {0};
    ega_char_t ega_char = {' ', color};
    CHECK_AND_RETHROW(screen_read_settings(&settings));

    for (i = 0; i < settings.height; i++) {
        for (j = 0; j < settings.width; j += sizeof ega_char) {
            CHECK_AND_RETHROW(screen_write(i, j, &ega_char, sizeof ega_char));
        }
    }
    cleanup:
    return err;
}
char_settings_t vga_char_settings = {2, 1};
