#ifndef OSDEV_KALLOC_H
#define OSDEV_KALLOC_H

#include <stddef.h>

#include "exceptions.h"




error_t kalloc(size_t);

error_t memory_initialize(size_t);


#endif //OSDEV_KALLOC_H



