#include "kernel/video/pixel.h"
#include "kernel/video/terminal.h"

static error_t initalize_modules() {
    error_t err = SUCCESS;
    CHECK_AND_RETHROW(pixel_initalize());
    CHECK_AND_RETHROW(terminal_initalize());
cleanup:
    return err;
}


void kernel_main(void) {
    if (IS_FAILED(initalize_modules())) {
        return;
    }

    terminal_write_cstring("Hello, kernel World!\n");

}

