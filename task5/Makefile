cc1 = /usr/bin/env nasm
cc2 = /usr/bin/env gcc

src1 = second.asm 
src2 = second.c

att1 = -f macho
att2 = -arch i386

target = task5

tempfile = /tmp/1.out

all:
	$(cc1) $(att1) $(src1) -o $(tempfile)
	$(cc2) $(att2) -o $(target) $(tempfile) $(src2)
	rm $(tempfile)
