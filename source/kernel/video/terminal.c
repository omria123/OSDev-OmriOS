//
// Created by omri on 01/12/2021.
//
#include "kernel/video/terminal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "stdlib/string.h"
#include "kernel/video/screen.h"

static struct {
    size_t row;
    size_t colum;
    uint8_t color;
    bool is_initialized;
} g_state;


typedef struct {
    char c;
    uint8_t color;
} ega_char_t;


static error_t terminal_advance_pos() {
    error_t err = SUCCESS;

    cleanup:
    return err;
}

// The terminal roll simply restart the position of the cursor to the beginning of the frame.
static error_t terminal_roll() {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    g_state.row = 0;
    g_state.colum = 0;
cleanup:
    return err;

}

// Put a char into the terminal
error_t terminal_putchar(char c) {
    error_t err = SUCCESS;
    enum video_mode mode = 0;
    ega_char_t ega_char = {0};
    bool screen_full = false;

    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK_AND_RETHROW(screen_mode(&mode));

    switch (c) {
        case '\n':
        case '\r':
            goto advance;
        default:
            break;
    }

    switch (mode) {
        case IND:
            break;
        case RGB:
            break;
        case EGA:
            ega_char.c = c;
            ega_char.color = g_state.color;
            screen_write(g_state.row, g_state.colum, &ega_char, 2);
            break;
        default:
            CHECK_FAILED();
    }
advance:
    switch(c) {
        case '\n':
            g_state.row++;
        case '\r':
            g_state.colum = 0;
        default:
            g_state.colum++;

    }
    CHECK_AND_RETHROW(screen_is_valid_access(g_state.row, g_state.colum, 1, &screen_full));
    if (screen_full) {
        CHECK_AND_RETHROW(terminal_roll());
    }

    cleanup:
    return err;
}

error_t terminal_set_color(uint8_t *color) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK(color);
    *color = g_state.color;
    cleanup:
    return err;
}

error_t terminal_get_color(uint8_t color) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    g_state.color = color;
    cleanup:
    return err;
}


error_t terminal_write(const char *data, size_t size) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK(data);

    for (size_t i = 0; i < size; i++)
        CHECK_AND_RETHROW(terminal_putchar(data[i]));
    cleanup:
    return err;
}

error_t terminal_write_cstring(const char *string) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK(string);
    CHECK_AND_RETHROW(terminal_write(string, strlen(string)));
    cleanup:
    return err;
}

error_t terminal_set_pos(const size_t row, const size_t col) {
    error_t err = SUCCESS;
    CHECK(g_state.is_initialized);
    g_state.row = row;
    g_state.colum = col;
    cleanup:
    return err;
}

error_t terminal_initalize(__attribute__((unused)) uint32_t multiboot2_header) {
    error_t err = SUCCESS;
    CHECK(!g_state.is_initialized);
    g_state.row = 0;
    g_state.colum = 0;
    g_state.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    g_state.is_initialized = 1;
    cleanup:
    return err;
}

