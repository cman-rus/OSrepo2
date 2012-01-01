segment	.text

global	_cosplusint
extern	_printd

_cosplusint:
	push	edi
	mov	edi, esp
	sub	esp, 8

	finit
	fld	qword [edi+8]
	fcos
	fiadd	dword [edi+16]

	fstp	qword [edi-8]
	call	_printd

	add	esp, 8
	pop	edi
	ret
