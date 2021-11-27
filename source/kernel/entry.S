ALIGNMENT equ (1<<0)
MEMINFO equ (1<<1)
KERNEL_ELF_FLAGS equ (ALIGNMENT | MEMINFO)
MAGIC equ 0x1BADB002
CHECKSUM equ -(MAGIC) + (KERNEL_ELF_FLAGS)

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
global _start:function
;The bootloader should load us into this location with the following settings:
; 1. 32-bit protected mode.
; 2. Paging is off.
; 3. Interrupts are disabled.
; 4. Processor state is described as the multiboot standard defines.
; 5. Floating point instruction and extended IS are not initalized.

_start:
    mov esp, stack_top
