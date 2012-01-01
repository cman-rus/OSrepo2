SOURCES=f.o main.o monitor.o common.o descriptor_tables.o isr.o interrupt.o gdt.o go32.o

CFLAGS=-c -nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -march=i386 
LDFLAGS=--oformat elf32-i386 -m elf_i386 -Tlink.ld
ASFLAGS=-felf

all: $(SOURCES) link

clean:
	-rm *.o kernel load b.out tmp*

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)
	objcopy -O binary kernel b.out
	perl 1.pl b.out

.s.o:
	nasm $(ASFLAGS) $<


.c.o:
	gcc $(CFLAGS) $<
