if(${CUSTOM_BOOTLOADER})
    add_subdirectory(custom)
else()  # ${CUSTOM_BOOTLOADER}
    add_subdirectory(grub)
endif()  # ${CUSTOM_BOOTLOADER}

set(BOOTLOADER_PACKER ${BOOTLOADER_PACKER} PARENT_SCOPE)