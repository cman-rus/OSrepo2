#include "common.h"
#include "int.h"

extern void default_handler();

struct idt_record int_idt[256];
struct idt_pointer int_pointer;
long int_pic_mask;

void int_init(){
	asm("cli");
	int i;
	for (i = 0 ;i<256;i++)
		int_set(i, default_handler, TRAP_GATE|BITS_32|ABSENT|RING_0);

	int_pointer.size=(256*8)-1;
	int_pointer.offset=(unsigned long)int_idt;
	
	asm("lidt %0" : "=m" (int_pointer));
	int_pic_mask = 0xFFFF;
	int_picInit();
	asm("sti");
}


void int_set(int id, void (*pointer)(), unsigned char control)
{
	union
	{
		void (*function)();
		struct addr function_addr;
	} interrupt;

	interrupt.function = pointer;
	int_idt[id].selector = 0x8;
	int_idt[id].dword_count = 0;
	int_idt[id].type = control;
	int_idt[id].offset1 = interrupt.function_addr.offset;
	int_idt[id].offset2 = interrupt.function_addr.base;
}

void int_picInit()
{
	outb(PIC1_COMMAND, ICW1_INIT+ICW1_ICW4);  // starts the initialization sequence
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT+ICW1_ICW4);
	io_wait();
	
	outb(PIC1_DATA, PIC1_VEC);                 // define the PIC vectors
	io_wait();
	outb(PIC2_DATA, PIC2_VEC);
	io_wait();
	
	outb(PIC1_DATA, 4);                       // continue initialization sequence
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();
 
	outb(PIC1_DATA, ICW4_8086);
	io_wait();
	outb(PIC2_DATA, ICW4_8086);
	io_wait();

	int_picSetMask();
}

void int_picSetMask(){
	outb(PIC1_DATA, int_pic_mask & 0xff);
	io_wait();
	outb(PIC2_DATA, (int_pic_mask >> 8) & 0xff);
	io_wait();
}

void int_enableIrq(unsigned short x, void (*handler)(), unsigned char control){
	int_pic_mask &= ~(1<<x);
	if (x>=8){
		int_pic_mask &= ~(1<<2);
		int_set(x + PIC2_VEC - 8, handler, control);
	}
	else
		int_set(x + PIC1_VEC, handler, control);
	int_picSetMask();
}

void int_disableIrq(unsigned short x){
	int_pic_mask |= (1 << x);
	if(x >= 8){
		int_pic_mask |= (1 << 2);
		int_set(x + PIC2_VEC - 8, default_handler, INT_GATE|BITS_32|ABSENT|RING_3);
	}
	else
		int_set(x + PIC1_VEC, default_handler, INT_GATE|BITS_32|ABSENT|RING_3);
	int_picSetMask();
}
