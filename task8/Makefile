SOURCES=f.o main.o monitor.o common.o descriptor_tables.o isr.o interrupt.o gdt.o int.o keyboard.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -march=i386 
LDFLAGS=--oformat elf32-i386 -m elf_i386 -Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel load go32 b.out load2 tmp*

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)
	objcopy -O binary kernel b.out
	nasm go32.asm 
	cat go32 b.out  > load2
	perl 1.pl load2

.s.o:
	nasm $(ASFLAGS) $<
