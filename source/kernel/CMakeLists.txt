# Fix CMake shitty implementation of nasm usage
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <FLAGS> <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")
add_compile_options(
        "$<$<COMPILE_LANGUAGE:ASM_NASM>:-f $<IF:$<BOOL:$<TARGET_PROPERTY:NASM_OBJ_FORMAT>>, \
    $<TARGET_PROPERTY:NASM_OBJ_FORMAT>, ${CMAKE_ASM_NASM_OBJECT_FORMAT}>>"
)


set(KERNEL_ENTRY_SOURCE boot/entry.S)
set(KERNEL_LINKER_SCRIPT linker.ld)
set(KERNEL_SOURCES boot/kernel_main.c boot/video/terminal.c boot/video/screen.c boot/multiboot_utils.c boot/video/vga.c boot/video/indexed.c boot/video/rgb.c boot/memory/bootmem.c memory/palloc.c memory/kalloc.c)
set(KERNEL_COMPILE_FLAGS -ffreestanding -O2 -m32)
set(KERNEL_LINK_FLAGS -nostdlib -m32 -static -T ${KERNEL_LINKER_SCRIPT})
set(KERNEL_LIBS stdlib_static)


set_source_files_properties(boot/entry.S PROPERTIES LANGUAGE ASM_NASM)

add_library(kernel_entry OBJECT ${KERNEL_ENTRY_SOURCE})
set_target_properties(kernel_entry PROPERTIES NASM_OBJ_FORMAT elf32)


add_custom_target(kernel_linker_script ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${KERNEL_LINKER_SCRIPT})
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${KERNEL_LINKER_SCRIPT}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${KERNEL_LINKER_SCRIPT}
        ${CMAKE_CURRENT_BINARY_DIR}/${KERNEL_LINKER_SCRIPT}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${KERNEL_LINKER_SCRIPT})

add_executable(kernel_elf $<TARGET_OBJECTS:kernel_entry> ${KERNEL_SOURCES})
add_dependencies(kernel_elf kernel_linker_script)
target_compile_options(kernel_elf PRIVATE ${KERNEL_COMPILE_FLAGS})
target_link_options(kernel_elf PRIVATE ${KERNEL_LINK_FLAGS})
target_link_libraries(kernel_elf ${KERNEL_LIBS})


# Testing:
add_test(NAME MULTIBOOT2_FORMAT COMMAND grub-file --is-x86-multiboot2 $<TARGET_FILE:kernel_elf>)