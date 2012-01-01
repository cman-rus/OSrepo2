#include "monitor.h"
#include "descriptor_tables.h"

int main(struct multiboot *mboot_ptr)
{
    init_descriptor_tables();
    monitor_clear();
    monitor_write("Hello, world!\n");

    asm volatile("int $0x0");
    asm volatile("int $0x0");
    asm volatile("int $0x3");
    asm volatile("int $0x4");
    asm volatile("int $0x5");
    asm volatile("int $0x6");

    asm ("iret");

    return 0;
}
