set(STDLIB_SOURCES string.c)
set(STDLIB_COMPILE_FLAGS -ffreestanding -O3 -m32)
set(STDLIB_LINK_FLAGS -nostdlib -m32)



add_library(stdlib SHARED ${STDLIB_SOURCES})
add_library(stdlib_static STATIC ${STDLIB_SOURCES})



set_target_properties(stdlib PROPERTIES VERSION  1.0.0)
target_compile_options(stdlib PRIVATE ${STDLIB_COMPILE_FLAGS})
target_link_options(stdlib PRIVATE ${STDLIB_LINK_FLAGS})

set_target_properties(stdlib_static PROPERTIES VERSION 1.0.0)
target_compile_options(stdlib_static PRIVATE ${STDLIB_COMPILE_FLAGS})
target_link_options(stdlib_static PRIVATE ${STDLIB_LINK_FLAGS})

target_include_directories(stdlib BEFORE PRIVATE ../../include/stdlib)