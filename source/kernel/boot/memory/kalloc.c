#define __FILE_ID__ 7 // LAST_FILE
#include "kernel/memory/kalloc.h"
#include "kernel/exceptions.h"



error_t kalloc(void **pointer, size_t size) {
    error_t err = SUCCESS;
    CHECK_CODE(pointer, ERROR_NULL_DEREF);
    CHECK(size);

    cleanup:
    return err;
}


error_t page_alloc(void **pointer) {
    error_t err = SUCCESS;
    CHECK_CODE(pointer, ERROR_NULL_DEREF);

    cleanup:
    return err;
}


error_t memory_init() {
    error_t err = SUCCESS;

cleanup:
    return err;
}