# Define packer for building the whole iso with this bootloader
set(BOOTLOADER_PACKER ${CMAKE_CURRENT_SOURCE_DIR}/generate_iso.sh PARENT_SCOPE)

# Adjustment for compiling the bootloader with nasm and using cmake
set(CMAKE_ASM_NASM_COMPILE_OBJECT "cat <SOURCE> ><OBJECT>")

# Define bootloader sources
set(MBR_SOURCES mbr.S)

# Define the mbr sources as nasm
set_source_files_properties(${MBR_SOURCES} PROPERTIES LANGUAGE ASM_NASM)

# Defining the target bootloader binary to prodcue.
add_executable(MBR ${MBR_SOURCES})
set_target_properties(MBR PROPERTIES
        SUFFIX .bin)
