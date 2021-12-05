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
    uint16_t *buffer;
    bool is_initalized;
} g_state = {0};


error_t terminal_putchar(char c) {
    error_t err = SUCCESS;
    enum video_mode mode = 0;
    CHECK_CODE(g_state.is_initalized, ERROR_UNINITIALIZED);
    CHECK_AND_RETHROW(screen_mode(&mode));
    switch(mode) {
        case IND:
            break;
        case RGB:
            break;
        case EGA:
            break;
    }
cleanup:
    return err;
}

error_t terminal_set_color(uint8_t *color) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initalized, ERROR_UNINITIALIZED);
    CHECK(color);
    *color = g_state.color;
cleanup:
    return err;
}

error_t terminal_get_color(uint8_t color) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initalized, ERROR_UNINITIALIZED);
    g_state.color = color;
cleanup:
    return err;
}


error_t terminal_write(const char *data, size_t size) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initalized, ERROR_UNINITIALIZED);
    CHECK(data);

    for (size_t i = 0; i < size; i++)
        CHECK_AND_RETHROW(terminal_putchar(data[i]));
cleanup:
    return err;
}

error_t terminal_write_cstring(const char *string) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initalized, ERROR_UNINITIALIZED);
    CHECK(string);
    CHECK_AND_RETHROW(terminal_write(string, strlen(string)));
cleanup:
    return err;
}

error_t terminal_set_pos(const size_t row, const size_t col) {
    error_t err = SUCCESS;
    CHECK(g_state.is_initalized);
    g_state.row = row;
    g_state.colum = col;
cleanup:
    return err;
}

error_t terminal_initalize(__attribute__((unused)) uint32_t multiboot2_header) {
    error_t err = SUCCESS;
    CHECK(!g_state.is_initalized);
    g_state.is_initalized = 1;
cleanup:
    return err;
}

