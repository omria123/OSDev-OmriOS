set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <FLAGS> <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")

set(KERNEL_ENTRY_SOURCE entry.S)
set(KERNEL_SOURCES kernel_main.c video/terminal.c ../../include/kernel/video/terminal.h ../../include/exceptions.h ../stdlib/string.c ../../include/stdlib/string.h video/pixel.c ../../include/kernel/video/pixel.h ../../include/cond_utils.h memory/kalloc.c ../../include/kernel/memory/kalloc.h)

set_source_files_properties(entry.S PROPERTIES LANGUAGE ASM_NASM)

add_executable(kernel_elf ${KERNEL_ENTRY_SOURCE} ${KERNEL_SOURCES})
set_target_properties(kernel_elf PROPERTIES NASM_OBJ_FORMAT elf64)

