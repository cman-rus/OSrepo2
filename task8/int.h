#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#define PIC1_VEC	0x20
#define PIC2_VEC	0x28

#define PIC1		0x20	/* IO base address for master PIC */
#define PIC2		0xA0	/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

#define ICW1_ICW4	0x01	/* ICW4 (not) needed */
#define ICW1_SINGLE	0x02	/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04	/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08	/* Level triggered (edge) mode */
#define ICW1_INIT	0x10	/* Initialization - required! */
 
#define ICW4_8086	0x01	/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02	/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08	/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C	/* Buffered mode/master */
#define ICW4_SFNM	0x10	/* Special fully nested (not) */

//

#define INT_GATE 0x06
#define TRAP_GATE 0x07

#define BITS_16 0x00
#define BITS_32 0x08

#define ABSENT 0x0
#define PRESENT 0x80

#define RING_0 0x00
#define RING_1 0x20
#define RING_2 0x40
#define RING_3 0x60

struct idt_record
{
	unsigned short offset1;
	unsigned short selector;
	unsigned char dword_count;
	unsigned char type;
	unsigned short offset2;
} __attribute ((packed));

struct idt_pointer {
	unsigned short size __attribute ((packed));
	unsigned long offset __attribute ((packed));
};

struct addr {
	unsigned short offset;
	unsigned short base;
};


void int_init();
void int_set(int id, void (*pointer)(), unsigned char control);
void int_enableIrq(unsigned short x, void (*handler)(), unsigned char control);
void int_disableIrq(unsigned short x);

#endif
