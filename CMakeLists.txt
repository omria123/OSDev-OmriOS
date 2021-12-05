cmake_minimum_required(VERSION 3.16)

project(osdev
        VERSION 1.0.0
        DESCRIPTION "OS development"
        LANGUAGES C ASM_NASM)

# Languages configuration
enable_language(C ASM_NASM)
set(CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS "${CMAKE_ASM_NASM_SOURCE_FILE_EXTENSIONS};asm;nasm;S")
set(CMAKE_CXX_STANDARD 14)

# Build process configuration
set(CMAKE_VERBOSE_MAKEFILE TRUE)

# OS global configuration
set(OS_NAME OmriOS)

# Include subdirectories
include_directories(BEFORE include)
add_subdirectory(source)




