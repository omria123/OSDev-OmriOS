#ifndef OSDEV_BOOTMEM_H
#define OSDEV_BOOTMEM_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "kernel/exceptions.h"
#include "kernel/mm.h"

#define BOOTMEM_UMA true


typedef struct {
    unsigned long node_boot_start;
    unsigned long node_low_pfn;
    void *node_bootmem_map;
    unsigned long bitmap_size;
    unsigned long last_offset;
    unsigned long last_pos;
    unsigned long last_success;
    bool is_initialized;
} bootmem_data;


typedef struct {
    uint32_t start_pfn; // First page's PFN
    uint32_t max_pfn; // Last PFN in the system
    uint32_t min_low_pfn; // Lowest free page (End of the kernel)
    uint32_t max_low_pfn; // End of ZONE_NORMAL
    uint32_t highstart_pfn; // Start of ZONE_HIGHMEM (= max_low_pfn)
    uint32_t highend_pfn; // End of ZONE_HIGHMEM (= max_pfn)
    bool is_initialized;
} node_layout;


#if BOOTMEM_UMA
#define BOOTMEM_MAX_ZONES 1
#else
#define BOOTMEM_MAX_ZONES 1 // Currently NUMA is not supported
#endif


error_t bootmem_free(void *pointer);

error_t bootmem_alloc_low(void **pointer, size_t size);

error_t bootmem_alloc(void **pointer, size_t size);

error_t bootmem_initialize(uint32_t multiboot_info);


#endif //OSDEV_BOOTMEM_H
