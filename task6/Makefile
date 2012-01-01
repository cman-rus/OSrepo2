SOURCES=t.o

CFLAGS=-c -m32 -march=i386 -std=c99
LDFLAGS=--oformat elf32-i386 -m elf_i386 -Ttmp

all: $(SOURCES) link

clean:
	-rm t.o a.out b.out first

link:
	ld $(LDFLAGS) $(SOURCES)
	objcopy -O binary a.out b.out
	nasm first.asm 
	cat first b.out  > load


.c.o:
	gcc $(CFLAGS) $<
