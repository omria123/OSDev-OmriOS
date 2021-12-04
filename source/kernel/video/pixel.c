#include <kernel/video/pixel.h>
#include <stddef.h>
#include <stdbool.h>

#include <exceptions.h>
#include <cond_utils.h>

static struct {
    bool is_initialized;
    size_t width;
    size_t height;
    void *framebuffer;
    enum video_mode mode;
} g_state = { 0 };


error_t pixel_mode() {
    error_t err = SUCCESS;
    CHECK(g_state.is_initialized);
cleanup:
    return err;
}



error_t pixel_read(size_t row, size_t col, void *buf) {
    error_t err = SUCCESS;
    CHECK(g_state.is_initialized);
    IN_RANGE(0, row, g_state.height);
    IN_RANGE(0 , col, g_state.width);
    CHECK(buf);
cleanup:
    return err;
}


error_t pixel_write(size_t row, size_t col, void *buf) {
    error_t err = SUCCESS;
    CHECK(g_state.is_initialized);
    IN_RANGE(0, row, g_state.height);
    IN_RANGE(0 , col, g_state.width);
    CHECK(buf);

cleanup:
    return err;
}


error_t pixel_initalize() {
    error_t err = SUCCESS;
    CHECK(!g_state.is_initialized);

    g_state.is_initialized = true;
cleanup:
    return err;
}
