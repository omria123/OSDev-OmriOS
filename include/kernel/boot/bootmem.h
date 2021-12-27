#ifndef OSDEV_BOOTMEM_H
#define OSDEV_BOOTMEM_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "kernel/exceptions.h"

error_t bootmem_free(void *pointer);

error_t bootmem_alloc_low(void ** pointer, size_t size);

error_t bootmem_alloc(void ** pointer, size_t size);

error_t bootmem_initalize(uint32_t multiboot_info);


#endif //OSDEV_BOOTMEM_H
