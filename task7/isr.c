#include "common.h"
#include "isr.h"
#include "monitor.h"
int z = 0;

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
