set(CMAKE_ASM_NASM_LINK_EXECUTABLE "ld <FLAGS> <CMAKE_ASM_NASM_LINK_FLAGS> <LINK_FLAGS> <OBJECTS>  -o <TARGET> <LINK_LIBRARIES>")

set(KERNEL_ENTRY_SOURCE entry.S)

set_source_files_properties(entry.S PROPERTIES LANGUAGE ASM_NASM)

add_executable(kernel_elf ${KERNEL_ENTRY_SOURCE})
set_target_properties(kernel_elf PROPERTIES NASM_OBJ_FORMAT elf64)

