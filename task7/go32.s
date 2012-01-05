	bits	16
extern print
	
section .text

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
	call	print

	cli
	hlt

end:
t1:
	dd 	0x0
	dd	0x0
	dd	0x0000ffff
	dd	0x00cf9a00

	dd	0x0000ffff
	dd	0x00cf9200
	
limit	dw	24
base	dd	t1

