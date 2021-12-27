#define __FILE_ID__ 8
#include "kernel/memory/palloc.h"

#include <stdbool.h>
#include "kernel/exceptions.h"

struct {
    bool is_initialized;
} g_state = {0};


error_t alloc_page(void **pointer) {
    error_t err = SUCCESS;

    cleanup:
    return err;
}

error_t physical_allocator_initialize(uint32_t multiboot2_header) {
    error_t err = SUCCESS;
    CHECK(g_state.is_initialized);
    g_state.is_initialized = 1;
    cleanup:
    return err;
}
