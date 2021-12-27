#define __FILE_ID__ 9 // LAST_FILE
#include "kernel/boot/bootmem.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kernel/exceptions.h"

typedef struct {
} bootmem_data;


static struct {
    uint32_t min_low_pfn;
    uint32_t max_low_pfn;
    bool is_initalized;
    unsigned long node_boot_start;
    unsigned long node_low_pfn;
    void *node_bootmem_map;
    unsigned long last_offset;
    unsigned long last_pos;
    unsigned long last_success;
} g_state = {0};

static error_t __alloc_bootmem() {
    error_t err = SUCCESS;

    cleanup:
    return err;
}
static error_t kernel_reserve() {
    error_t err = SUCCESS;

    cleanup:
    return err;
}

static error_t bitmap_reserve() {
    error_t err = SUCCESS;

    cleanup:
    return err;
}

error_t bootmem_free_all() {
    error_t err = SUCCESS;

    cleanup:
    return err;
}

error_t bootmem_reserve(void ** pointer, size_t size) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initalized, ERROR_UNINITIALIZED);
    CHECK_CODE(pointer != NULL, ERROR_NULL_DEREF);

    cleanup:
    return err;
}

error_t bootmem_free(void *pointer) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initalized, ERROR_UNINITIALIZED);
    CHECK_CODE(pointer != NULL, ERROR_NULL_DEREF);
    cleanup:
    return err;
}

error_t bootmem_alloc_low(void ** pointer, size_t size) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initalized, ERROR_UNINITIALIZED);
    CHECK_CODE(pointer != NULL, ERROR_NULL_DEREF);

    cleanup:
    return err;
}

error_t bootmem_alloc(void ** pointer, size_t size) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initalized, ERROR_UNINITIALIZED);
    CHECK_CODE(pointer != NULL, ERROR_NULL_DEREF);

    cleanup:
    return err;
}

error_t bootmem_initalize(uint32_t multiboot_info) {
    error_t err = SUCCESS;
    CHECK(!g_state.is_initalized);
    kernel_reserve();
    bitmap_reserve();
    g_state.is_initalized = 1;
    cleanup:
    return err;
}
