# Project flags:
# Whether to use grub bootloader or my own custom bootloader
set(CUSTOM_BOOTLOADER FALSE)

# Adding subdirectories:
add_subdirectory(kernel)
add_subdirectory(bootloader)

# Total target

set(OS_IMG ${CMAKE_BINARY_DIR}/${OS_NAME}.img)



add_subdirectory(stdlib)

add_custom_command(
        OUTPUT
            ${OS_IMG}
        COMMAND
            ${BOOTLOADER_PACKER} ${OS_NAME} ${OS_IMG} $<TARGET_FILE:kernel_elf>
        DEPENDS
            kernel_elf
)
add_custom_target(
        os_image ALL
        DEPENDS
            ${OS_IMG}
)

