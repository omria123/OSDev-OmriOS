#include "kernel/video/screen.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "kernel/multiboot2.h"
#include "exceptions.h"
#include "cond_utils.h"

static struct {
    bool is_initialized;
    size_t width;
    size_t height;
    size_t bpp;
    void *framebuffer;
    enum video_mode mode;
} g_state = { 0 };


// Verify that write is within screen limits.
bool is_valid_access(size_t row, size_t col, size_t size) {
    return 1; // TODO: CHANGE
}

error_t screen_mode(enum video_mode *mode) {
    error_t err = SUCCESS;
    CHECK(g_state.is_initialized);
    CHECK(mode);
    *mode = g_state.mode;
cleanup:
    return err;
}

error_t screen_read(size_t row, size_t col, void *buf, size_t size) {
    error_t err = SUCCESS;
    CHECK(g_state.is_initialized);
    IN_RANGE(0, row, g_state.height);
    IN_RANGE(0 , col, g_state.width);
    CHECK(buf);
    CHECK(is_valid_access(row, col, size));
    CHECK_FAILED_CODE(ERROR_NOT_IMPLEMENTED);

cleanup:
    return err;
}


error_t screen_write(size_t row, size_t col, void *buf, size_t size) {
    error_t err = SUCCESS;
    CHECK(g_state.is_initialized);
    CHECK(IN_RANGE(0, row, g_state.height));
    CHECK(IN_RANGE(0 , col, g_state.width));
    CHECK(is_valid_access(row, col, size));
    CHECK(buf);


cleanup:
    return err;
}


error_t screen_initalize(uint32_t multiboot_header) {
    error_t err = SUCCESS;
    struct multiboot_tag_framebuffer *framebuffer_info = NULL;
    struct multiboot_tag_framebuffer_common *framebuffer_common_info = NULL;

    CHECK(!g_state.is_initialized);
    framebuffer_info = (struct multiboot_tag_framebuffer *) multiboot_find_tag(multiboot_header, MULTIBOOT_TAG_TYPE_FRAMEBUFFER);
    CHECK(framebuffer_info->common.type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER);
    framebuffer_common_info = &framebuffer_info->common;

    g_state.framebuffer = (void *) framebuffer_common_info->framebuffer_addr;
    g_state.height = framebuffer_common_info->framebuffer_height;
    g_state.width = framebuffer_common_info->framebuffer_width;
    g_state.mode = framebuffer_common_info->framebuffer_type;
    g_state.bpp = framebuffer_common_info->framebuffer_bpp;

    g_state.is_initialized = true;
cleanup:
    return err;
}
