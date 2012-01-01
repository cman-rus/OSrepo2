	org	0x7C00


	cli
	jmp	0x0:start
start:
	push	cs
	pop	es
	push	cs
	pop	ds
	sti
	lgdt	[limit]
	
	mov	eax, cr0
	or	eax, 1
	mov	cr0, eax
	
	
	jmp	0x08:sta2

sta2:
	BITS	32
	mov	ax, 16
	mov	ds, ax

	mov	word [0xb8000], 0x3070
	cli
	hlt

	sti
;	mov	ah, 0x13
;	mov	al, 0 
;	mov	bh, 0
;	mov	bl, 0x07
;		
;	mov	cx, (end - str1)
;	xor	dx, dx
;	mov	bp, str1
;	sti
;	int	0x10
str1:
	db 	"Welcome!!!"
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

	times	510-($-$$) db 0
	db	0x55, 0xAA
str2:
        db      "Welcome2!!!"
end2:
	times	1024- ($-$$) db 0

