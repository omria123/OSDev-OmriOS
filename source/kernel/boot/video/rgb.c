#include "kernel/video/rgb.h"

#include <stdint.h>

#include "kernel/exceptions.h"
#include "kernel/video/screen.h"


error_t rgb_putchar(uint32_t row, uint32_t col, uint8_t c, uint8_t color) {
    error_t err = SUCCESS;
    CHECK_FAILED_CODE(ERROR_NOT_IMPLEMENTED);
    cleanup:
    return err;
}


char_settings_t rgb_char_settings = { 0 };