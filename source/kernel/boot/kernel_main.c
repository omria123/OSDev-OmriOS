#include <stdint.h>

#include "kernel/video/screen.h"
#include "kernel/video/terminal.h"
#include "kernel/multiboot2.h"


static error_t initalize_modules(uint32_t multiboot_info) {
    error_t err = SUCCESS;
    CHECK_AND_RETHROW(screen_initalize(multiboot_info));
    CHECK_AND_RETHROW(terminal_initalize(multiboot_info));
cleanup:
    return err;
}


void kernel_main(uint32_t magic, uint32_t multiboot_info) {
    if (magic != MULTIBOOT2_HEADER_MAGIC) {
        return;
    }
    if (IS_FAILED(initalize_modules(multiboot_info))) {
        return;
    }

    terminal_write_cstring("Hello, kernel World!\n");

}

