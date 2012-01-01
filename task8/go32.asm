	org	0x8200

	cli

	lgdt	[limit]
	
	mov	eax, cr0
	or	eax, 1
	mov	cr0, eax
	
	jmp	0x08:sta2

sta2:
	BITS	32

	mov	ax, 0x10 
   	mov	ds, ax 
   	mov	es, ax
   	mov	fs, ax
   	mov	gs, ax
   	mov	ss, ax

	sti
	call	0x9000

	cli
	hlt

end:
t1:
	dd 	0x0
	dd	0x0
	dd	0x0000ffff
	dd	0x004f9a00

	dd	0x0000ffff
	dd	0x004f9200
	
limit	dw	24
base	dd	t1

	times	3584-($-$$) db 0

e:
