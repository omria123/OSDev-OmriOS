#ifndef OSDEV_PALLOC_H
#define OSDEV_PALLOC_H

#include <stdint.h>

#include "kernel/exceptions.h"

error_t alloc_page(void **pointer);
error_t physical_allocator_initialize(uint32_t multiboot2_header);

#endif //OSDEV_PALLOC_H
