#include "kernel/video/ind.h"
#include <stdint.h>

#include "kernel/exceptions.h"
#include "kernel/video/screen.h"

error_t ind_putchar(uint32_t row, uint32_t col, uint8_t c, uint8_t color) {
    error_t err = SUCCESS;
    CHECK_FAILED_CODE(ERROR_NOT_IMPLEMENTED);
    cleanup:
    return err;
}


char_settings_t ind_char_settings = { 0 };
