# Fix CMake shitty implementation of nasm usage
set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <FLAGS> <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")
set(CMAKE_ASM_NASM_COMPILE_OBJECT "<CMAKE_ASM_NASM_COMPILER> <INCLUDES> <FLAGS> -o <OBJECT> <SOURCE>")
add_compile_options(
        "$<$<COMPILE_LANGUAGE:ASM_NASM>:-f $<IF:$<BOOL:$<TARGET_PROPERTY:NASM_OBJ_FORMAT>>, \
    $<TARGET_PROPERTY:NASM_OBJ_FORMAT>, ${CMAKE_ASM_NASM_OBJECT_FORMAT}>>"
)


set(KERNEL_ENTRY_SOURCE boot/entry.S)
set(KERNEL_SOURCES boot/kernel_main.c boot/video/terminal.c boot/video/screen.c boot/memory/kalloc.c boot/multiboot_utils.c boot/video/vga.c boot/video/indexed.c boot/video/rgb.c)
set(KERNEL_COMPILE_FLAGS -ffreestanding -O2 -m32)
set(KERNEL_LINK_FLAGS -nostdlib -m32)
set(KERNEL_LIBS stdlib)


set_source_files_properties(boot/entry.S PROPERTIES LANGUAGE ASM_NASM)

add_library(kernel_entry OBJECT ${KERNEL_ENTRY_SOURCE})
set_target_properties(kernel_entry PROPERTIES NASM_OBJ_FORMAT elf32)


add_executable(kernel_elf $<TARGET_OBJECTS:kernel_entry> ${KERNEL_SOURCES})
target_compile_options(kernel_elf PRIVATE ${KERNEL_COMPILE_FLAGS})
target_link_options(kernel_elf PRIVATE ${KERNEL_LINK_FLAGS})
target_link_libraries(kernel_elf ${KERNEL_LIBS})
