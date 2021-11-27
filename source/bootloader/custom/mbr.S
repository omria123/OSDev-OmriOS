org 0x7c00
bits 16

start:
	cli
	mov ax, 0x7c0

	mov ds, ax
	mov es, ax

	add ax, 88
	mov ss, ax
	mov sp, 0x2000
	sti 
 
	mov cx, end - message - 1
	mov bp, message - $$ 

	call print_string

	call load_second_level	
	jmp ax


print_string:
	mov al, 1
	
	mov bh, 0
	mov bl, 0011_1011b ; white on black
 
	mov ah, 0x13
	int 10h
	
	ret


load_second_level:
	


message db "Welcome to OSdev",0
end:


times 510 - ($-$$) db 0x90
dw 0xaa55
