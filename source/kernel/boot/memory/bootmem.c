#define __FILE_ID__ 9 // LAST_FILE

#include "kernel/boot/bootmem.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "kernel/exceptions.h"
#include "stdlib/string.h"

static struct {
    bootmem_data bdata[BOOTMEM_MAX_ZONES];
    node_layout layout[BOOTMEM_MAX_ZONES];
    uint8_t zones;
    bool is_initialized;
} g_state = {0};

static error_t __alloc_bootmem() {
    error_t err = SUCCESS;

    cleanup:
    return err;
}


static error_t resolve_memory_layout(uint32_t mb_info) {
    error_t err = SUCCESS;

    cleanup:
    return err;
}

static error_t initialize_zone_bdata(node_layout *layout, bootmem_data *bdata) {
    uint32_t bitmap_size = 0;
    error_t err = SUCCESS;
    // This function is only for initializing this module.
    // The memory sections must be resolved first
    CHECK(!g_state.is_initialized);
    CHECK_CODE(layout->is_initialized, ERROR_UNINITIALIZED);
    bdata->node_boot_start = layout->start_pfn << PAGE_SHIFT;
    bdata->node_low_pfn = layout->max_low_pfn;
    bdata->node_bootmem_map = (void *) (layout->min_low_pfn << PAGE_SHIFT);
    bdata->last_offset = 0;
    bdata->last_pos = 0;
    bdata->last_success = 0;
    bitmap_size = (layout->max_low_pfn - layout->start_pfn + 7) / 8;
    bitmap_size = (bitmap_size + sizeof(long) - 1) & ~(sizeof(long) - 1); // Align the bitmap size to long
    bdata->bitmap_size = bitmap_size;
    memset(bdata->node_bootmem_map, (char) 0xff, bitmap_size);
    bdata->is_initialized = 1;
    cleanup:
    return err;
}


static error_t initialize_bdata() {
    error_t err = SUCCESS;
    uint8_t zone_index = 0;

    CHECK(!g_state.is_initialized);
    // This function is only for initializing this module.
    for (zone_index = 0; zone_index < g_state.zones; zone_index++) {
        CHECK_AND_RETHROW(initialize_zone_bdata(&g_state.layout[zone_index], &g_state.bdata[zone_index]));
    }
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

error_t bootmem_reserve(void **pointer, size_t size) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK_CODE(pointer != NULL, ERROR_NULL_DEREF);

    cleanup:
    return err;
}

error_t bootmem_free(void *pointer) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK_CODE(pointer != NULL, ERROR_NULL_DEREF);
    cleanup:
    return err;
}

error_t bootmem_alloc_low(void **pointer, size_t size) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK_CODE(pointer != NULL, ERROR_NULL_DEREF);

    cleanup:
    return err;
}

error_t bootmem_alloc(void **pointer, size_t size) {
    error_t err = SUCCESS;
    CHECK_CODE(g_state.is_initialized, ERROR_UNINITIALIZED);
    CHECK_CODE(pointer != NULL, ERROR_NULL_DEREF);

    cleanup:
    return err;
}


error_t bootmem_initialize(uint32_t multiboot_info) {
    error_t err = SUCCESS;
    CHECK(!g_state.is_initialized);
    CHECK_AND_RETHROW(resolve_memory_layout(multiboot_info));
    CHECK_AND_RETHROW(initialize_bdata());
    CHECK_AND_RETHROW(bitmap_initialize(multiboot_info));
    g_state.is_initialized = 1;
    cleanup:
    return err;
}
