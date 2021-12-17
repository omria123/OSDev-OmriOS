#define __FILE_ID__ 4
#include "kernel/video/screen.h"

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>

#include "kernel/multiboot2.h"
#include "kernel/exceptions.h"
#include "cond_utils.h"
#include "stdlib/string.h"

static struct {
    bool is_initialized;
    size_t width;
    size_t height;
    size_t bpp;
    size_t pitch;
    void *framebuffer;
    enum video_mode mode;
} g_state = {0};


// Verify that write is within screen limits.
error_t screen_is_valid_access(size_t row, size_t col, size_t size, bool *result) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK(result);
    *result = true;
    *result = col + g_state.pitch * row + size < (g_state.height * g_state.width * g_state.bpp  >> 3);
cleanup:
    return err;

}

error_t screen_read_settings(screen_settings_t *settings) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    settings->width = g_state.width;
    settings->height = g_state.height;
    settings->bpp = g_state.bpp;
    settings->pitch = g_state.pitch;
    cleanup:
    return err;
}


error_t screen_mode(enum video_mode *mode) {
    error_t err = SUCCESS;

    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK(mode);

    *mode = g_state.mode;
    cleanup:
    return err;
}

error_t screen_read(size_t row, size_t col, void *buf, size_t size) {
    error_t err = SUCCESS;
    bool valid = true;

    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    IN_RANGE(0, row, g_state.height);
    IN_RANGE(0, col, g_state.width);
    CHECK(buf);
    CHECK_AND_RETHROW(screen_is_valid_access(row, col, size, &valid));
    CHECK(valid);
    CHECK_FAILED_CODE(ERROR_NOT_IMPLEMENTED);

    cleanup:
    return err;
}


error_t screen_write(size_t row, size_t col, void *buf, size_t size) {
    error_t err = SUCCESS;
    bool valid = true;
    size_t i = 0;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK(IN_RANGE(0, row, g_state.height));
    CHECK(IN_RANGE(0, col, g_state.width));
    CHECK_AND_RETHROW(screen_is_valid_access(row, col, size, &valid));
    CHECK(valid);
    CHECK(buf);
    memcpy(g_state.framebuffer + row * g_state.pitch + col, buf, size);
    cleanup:
    return err;
}

error_t screen_initalize(uint32_t multiboot_header) {
    error_t err = SUCCESS;
    struct multiboot_tag_framebuffer *framebuffer_info = NULL;
    struct multiboot_tag_framebuffer_common *framebuffer_common_info = NULL;

    CHECK(!g_state.is_initialized);
    framebuffer_info = (struct multiboot_tag_framebuffer *) multiboot_find_tag(multiboot_header,
                                                                               MULTIBOOT_TAG_TYPE_FRAMEBUFFER);
    CHECK(framebuffer_info->common.type == MULTIBOOT_TAG_TYPE_FRAMEBUFFER);
    framebuffer_common_info = &framebuffer_info->common;

    g_state.framebuffer = (void *) (uint32_t) framebuffer_common_info->framebuffer_addr;
    g_state.height = framebuffer_common_info->framebuffer_height;
    g_state.width = framebuffer_common_info->framebuffer_width;
    g_state.mode = framebuffer_common_info->framebuffer_type;
    g_state.bpp = framebuffer_common_info->framebuffer_bpp;
    g_state.pitch = framebuffer_common_info->framebuffer_pitch;
    g_state.is_initialized = true;

    cleanup:
    return err;
}
void* get_framebuffer() {
    return g_state.framebuffer;
}