#include "common.h"
#include "isr.h"
#include "monitor.h"
#include "keyboard.h"
int z = 0;
int r = 1;
int z1 = 0;
int r1 = 1;

int k = 0;


void isr_handler(registers_t regs)
{
    monitor_write_dec(z);
    monitor_put('-');
    monitor_write("recieved interrupt: ");
    monitor_write_dec(regs.int_no);
    monitor_write(", add: ");
    monitor_write_hex(regs.cs);
    monitor_put(':');
    monitor_write_hex(regs.eip);
    monitor_put('\n');
    ++z;
}

void default_handler(){
	asm("cli");
	outb(0x20, 0x20);
	monitor_write_dec1(0,0,z);	
	if(r)
	{
		++z;
	}

        monitor_write_dec1(0,1,z1);
        if(r1)
        {
                ++z1;
        }

	asm("sti");
	asm("leave\niret");	
}

void startstop()
{
	r = r ^ 1;
}

void startstop1()
{
        r1 = r1 ^ 1;
}

extern void int_keyboard()
{
        asm("cli");
        monitor_write_dec1(0,3,k);
        ++k;
       	key_interrupt();
        asm("sti");
        asm("leave\niret");
}
