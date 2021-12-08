#include <stddef.h>

#include "kernel/multiboot2.h"


// Iterate over all tags until the searched one is found.
struct multiboot_tag* multiboot_find_tag(multiboot_uint32_t mbi, multiboot_uint32_t type) {
    struct multiboot_tag* tag = NULL;
    for (tag = (struct multiboot_tag *) (mbi + 8);
         tag->type != MULTIBOOT_TAG_TYPE_END;
         tag = (struct multiboot_tag *) ((multiboot_uint8_t *) tag
                                         + ((tag->size + 7) & ~7)))
    {
        if (tag->type == type) {
            return tag;
        }
    }
    return tag;
}
