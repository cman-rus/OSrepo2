#include "monitor.h"
#include "descriptor_tables.h"
#include "int.h"
#include "keyboard.h"


extern void int_keyboard();
extern void default_handler();

int main(struct multiboot *mboot_ptr)
{
//    init_descriptor_tables();
    monitor_clear();
    monitor_write("      Hello, world!\n");
    int_init();
    key_init();

    int_enableIrq(1, int_keyboard, INT_GATE|BITS_32|PRESENT|RING_0);
    int_enableIrq(0, default_handler, INT_GATE|BITS_32|PRESENT|RING_0);


    while(1){
	asm("cli");
        while (key_isEmpty()==0){
            char k = key_get();
            if(k == 'p' )
            {
                startstop();
            }

            if(k == 'P' )
            {
                startstop1();
            }

            monitor_put(k);
        }
        asm("sti");
    }
//    asm volatile("int $0x0");
//    asm volatile("int $0x0");
//    asm volatile("int $0x3");
//    asm volatile("int $0x4");
//    asm volatile("int $0x5");
//    asm volatile("int $0x6");

    return 0;
}
