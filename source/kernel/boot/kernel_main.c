#define __FILE_ID__ 1
#include <stdint.h>

#include "kernel/video/screen.h"
#include "kernel/video/terminal.h"
#include "kernel/boot/bootmem.h"
#include "kernel/multiboot2.h"
#include "stdlib/string.h"

error_t boot_status = SUCCESS;
enum video_mode mode = -5;
screen_settings_t settings = {0};
size_t row = -1;
size_t col = -1;
uint8_t color = 0;
char *fb = NULL;

static error_t initalize_boot_modules(uint32_t multiboot_info) {
    error_t err = SUCCESS;
    CHECK_AND_RETHROW(screen_initalize(multiboot_info));
    CHECK_AND_RETHROW(terminal_initalize(multiboot_info));
    CHECK_AND_RETHROW(bootmem_initialize(multiboot_info));
cleanup:
    return err;
}


void kernel_main(uint32_t magic, uint32_t multiboot_info) {
    error_t err = SUCCESS;
    CHECK_CODE(magic == MULTIBOOT2_BOOTLOADER_MAGIC, ERROR_NOT_IMPLEMENTED);
    CHECK_AND_RETHROW(initalize_boot_modules(multiboot_info));


    // Add state for debug
    CHECK_AND_RETHROW(screen_mode(&mode));
    memcpy(&boot_status, &err, sizeof(err));
    CHECK_AND_RETHROW(screen_read_settings(&settings));
    CHECK_AND_RETHROW(terminal_get_pos(&row, &col));
    CHECK_AND_RETHROW(terminal_get_color(&color));
    cleanup:
    return;
}

