#!/usr/bin/perl
unless($ARGV[0])
{
	print "Use: 1.pl <filename> \n";
	exit;
}

$\='';
eval("use String::CRC32;");
die ("no String::CRC32 module was found. Please install it.") if $@;

open F, "<", $ARGV[0] or die("Can't open: $!");
binmode F;
$/=\0;
$l=0;
$file = <F>;
$l=length($file);
close F or die("can't close: $!");

$crc = crc32($file);
print "Length: ", $l, "\n";
printf("%02x\n", $l);
print "CRC32: 0x";
printf("%02x\n", $crc);

if($l > 512 * 32)
{
	print "ERROR!! big file! \n";
	exit;
}

$asm = '

        org     0x7C00


	cli
        jmp     0x0:start
start:
        push    cs
        pop     es
        push    cs
        pop     ds
        push    cs
        pop     ss

        mov     sp, 0xffff
        sti

        mov     ah, 2
        mov     al, ' . ($l%512==0?(int $l/512 ):(int ($l/512) + 1)) . '
        mov     cx, 4
        mov     bx, buf
        int     0x13

        jc      @err

;--------i8086,i286------------
	pushf
	pop	ax
	and	ax, 0F000h
	cmp	ax, 0
	je	ok322
	cmp	ax, 0F000h
	je	ok322
;------i386---------------------
        mov     cx, sp
        sub     cx, 4
        pushfd
        cmp     cx,sp
        je      ok32
        popfd
n32:    mov     bp,not32str
        mov     bx,4
        mov     ah,3
        int     0x10
        mov     cx,18
        mov     ax,0x1301
        int     0x10
        jmp     @a
ok32:
        popfd
ok322:
        mov     ecx, 0
        xor     di, di
_tab:
        mov     eax, ecx
        push    cx
        mov     cx, 8
_mktab:
        shr     eax, 1
        jnc     mktabend
        xor     eax, 0xEDB88320
mktabend:
        loop    _mktab
        mov     [crctab+di], eax
        add     di, 4
        pop     cx

        inc     cx
        cmp     cx,0xff
        jbe     _tab

        mov     eax, 0xFFFFFFFF
        mov     ecx, [len]
        xor     esi, esi
calc:
        mov     edx, eax
        shr     edx, 8
        mov     ebx, eax
        xor     bl, [buf+esi]
        inc     esi
        and     ebx, 0xff
        shl     ebx, 2
        mov     ebx, [ebx+crctab]
        xor     ebx, edx
        mov     eax, ebx
        loop    calc
        xor     eax, 0xFFFFFFFF


        cmp     eax, [crc]
        je      crcok
        mov     bp, failstr
        mov     bx, 4
        mov     ah, 3
        int     0x10
        mov     cx, 15
        mov     ax, 0x1301
        int     0x10
@err:
        mov     bp, errstr
        mov     bx, 4
        mov     ah, 3
        int     0x10
        mov     cx,24
        mov     ax,0x1301

@a:
        cli
        hlt
        jmp     @a
crcok:
;        mov     si,buf
;        mov     ecx,[len]
fileout:
;        mov     ah,0xe
;        lodsb
;        int     0x10
;        dec     ecx
;        test    ecx,ecx
;        jnz     fileout
	jmp	0x0:buf
        jmp     @a

failstr:        db      \'CRC not equal! \'
errstr: db      \'Error. Execution stopped.\'
not32str:       db      \'Error. Not 32-bit.\'
len:    dd      ' . $l . '
crc:    dd      ' . $crc . '
        times   510-($-$$) db 0
        db      0x55
        db      0xaa
crctab: times   256 dd 0
buf:
';

open F, ">tmp.asm" or die("can't open: $!");
print F $asm or die("can't write: $!");
close F or die("can't close: $!");

system("nasm tmp.asm") == 0 or die("can't execute nasm: $!");
system("cat tmp $ARGV[0] > load") == 0 or die("can't execute cat: $!");

$l2 = $l %512;
$l2 = 512 if $l2==0;

$z = chr(0) x (512-$l2);
open F, ">>load" or die("can't open: $!");
binmode F;
print F $z or die("can't write: $!");
close F or die("can't close: $!");
