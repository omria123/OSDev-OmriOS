ALIGNMENT equ (1<<0)
MEMINFO equ (1<<1)
KERNEL_ELF_FLAGS equ (ALIGNMENT | MEMINFO)
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC) + (KERNEL_ELF_FLAGS)
MULTIBOOT2_HEADER_MAGIC equ
GRUB_MULTIBOOT_ARCHITECTURE_I386 equ

; Multiboot header containing the magic, flags and checksum.
section .multiboot align=4
dd MAGIC
dd KERNEL_ELF_FLAGS
dd CHECKSUM

; Define stack as NOBITS to make the kernel executable smaller
section .bss align=16
stack_bottom:
BSS_STACK resb 1<<14
stack_top:


section .text
global _start:function (_start.END - _start)
;The bootloader should load us into this location with the following settings:
; 1. 32-bit protected mode.
; 2. Paging is off.
; 3. Interrupts are disabled.
; 4. Processor state is described as the multiboot standard defines.
; 5. Floating point instruction and extended IS are not initalized.
; Good place for assembly initialization
start:
_start:
    jmp multiboot_entry
    align 8
multiboot_header:
    dd MULTIBOOT2_HEADER_MAGIC
    dd GRUB_MULTIBOOT_ARCHITECTURE_I386
    dd multiboot_header_end - multiboot_header
    dd -(MULTIBOOT2_HEADER_MAGIC + GRUB_MULTIBOOT_ARCHITECTURE_I386 + (multiboot_header_end - multiboot_header))


multiboot_entry:
    mov esp, stack_top
    xor edx, edx
    push edx
    popf


    push ebx
    push eax
    call kernel_main

; Lock the computer
    cli
.HLT:
    hlt
    jmp .HLT
.END:
kernel_main: