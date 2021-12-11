#include "kernel/video/terminal.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "stdlib/string.h"
#include "kernel/video/screen.h"
#include "kernel/video/vga.h"
#include "kernel/video/rgb.h"
#include "kernel/video/ind.h"


static struct {
    size_t row;
    size_t colum;
    uint8_t color;
    enum video_mode mode;
    char_settings_t char_settings;
    bool is_initialized;
    bool is_initializing;
} g_state;


static void terminal_advance_pos(char c) {
    switch (c) {
        case '\n':
            g_state.row++;
        case '\r':
            g_state.colum = 0;
        default:
            g_state.colum++;
    }
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

static error_t terminal_putchar__impl(char c) {
    error_t err = SUCCESS;
    enum video_mode mode = 0;
    bool screen_full = false;

    CHECK_AND_RETHROW(screen_mode(&mode));

    switch (mode) {
        case IND:
            ind_putchar(g_state.row, g_state.colum, c, g_state.color);
            break;
        case RGB:
            rgb_putchar(g_state.row, g_state.colum, c, g_state.color);
            break;
        case EGA:
            vga_putchar(g_state.row, g_state.colum, c, g_state.color);
            break;
        default:
            CHECK_FAILED();
    }
    terminal_advance_pos(c);

    CHECK_AND_RETHROW(screen_is_valid_access(g_state.row, g_state.colum, 1, &screen_full));
    if (screen_full) {
        CHECK_AND_RETHROW(terminal_roll());
    }

    cleanup:
    return err;

}
// Put a char into the terminal
error_t terminal_putchar(char c) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK_AND_RETHROW(terminal_putchar__impl(c));
    cleanup:
    return err;
}

// Resets the terminal to clean state
error_t terminal_reset() {
    error_t err = SUCCESS;
    enum video_mode mode = 0;
    screen_settings_t settings = {0};
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t rows = 0;
    uint32_t cols = 0;
    CHECK_CODE(g_state.is_initialized || g_state.is_initializing, ERROR_UNINITIALIZED);
    CHECK_AND_RETHROW(screen_mode(&mode));
    CHECK_AND_RETHROW(screen_read_settings(&settings));
    CHECK_AND_RETHROW(terminal_set_pos(0, 0));
    rows = settings.height / g_state.char_settings.height;
    cols = settings.width / g_state.char_settings.width;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j ++) {
            CHECK_AND_RETHROW(terminal_putchar__impl(' '));
        }
    }
    CHECK_AND_RETHROW(terminal_set_pos(0, 0));
cleanup:
    return err;
}

// Get the color of the terminal
error_t terminal_get_color(uint8_t *color) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    enum video_mode mode = 0;
    CHECK_AND_RETHROW(screen_mode(&mode));

    *color = g_state.color;
    cleanup:
    return err;
}

// Set the color of the terminal
error_t terminal_set_color(uint8_t color) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    g_state.color = color;

    cleanup:
    CHECK(color);
    return err;
}

// Write data to the terminal
error_t terminal_write(const char *data, size_t size) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK(data);

    for (size_t i = 0; i < size; i++)
        CHECK_AND_RETHROW(terminal_putchar(data[i]));
    cleanup:
    return err;
}

// Write cstring to the terminal
error_t terminal_write_cstring(const char *string) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK(string);
    CHECK_AND_RETHROW(terminal_write(string, strlen(string)));
    CHECK_AND_RETHROW(terminal_reset());
    cleanup:
    return err;
}

// Set the pos of the terminal
error_t terminal_set_pos(const size_t row, const size_t col) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized || g_state.is_initializing, ERROR_UNINITIALIZED);
    g_state.row = row;
    g_state.colum = col;
    cleanup:
    return err;
}


// Initalize terminal
error_t terminal_initalize(uint32_t multiboot2_header) {
    error_t err = SUCCESS;
    CHECK(!g_state.is_initialized);
    g_state.row = 0;
    g_state.colum = 0;
    g_state.is_initializing = 1;
    g_state.color = vga_entry_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    CHECK_AND_RETHROW(screen_mode(&g_state.mode));
    switch(g_state.mode) {
        case IND:
            memcpy(&g_state.char_settings, &ind_char_settings, sizeof g_state.char_settings);
            break;
        case EGA:
            memcpy(&g_state.char_settings, &vga_char_settings, sizeof g_state.char_settings);
            break;
        case RGB:
            memcpy(&g_state.char_settings, &rgb_char_settings, sizeof g_state.char_settings);
            break;
    }
    g_state.is_initialized = 1;
    cleanup:
    g_state.is_initializing = 0;
    return err;
}

