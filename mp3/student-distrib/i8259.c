/* i8259.c - Functions to interact with the 8259 interrupt controller
 * vim:ts=4 noexpandtab
 */

#include "i8259.h"
#include "lib.h"

/* Interrupt masks to determine which interrupts
 * are enabled and disabled */
uint8_t master_mask; /* IRQs 0-7 */
uint8_t slave_mask; /* IRQs 8-15 */



/* Initialize the 8259 PIC */
void
i8259_init(void)
{												//based off of wiki.osdev.org ===============================================================================================================================>
	uint32_t flags;
	cli_and_save(flags);
	
	outb( ICW1, MASTER_8259_PORT);  
	outb( ICW1, SLAVE_8259_PORT);

	outb( ICW2_MASTER, MASTER_8259_DATA);
	outb( ICW2_SLAVE, SLAVE_8259_DATA);

	outb( ICW3_MASTER, MASTER_8259_DATA);
	outb( ICW3_SLAVE, SLAVE_8259_DATA);
 
	outb( ICW4, MASTER_8259_DATA);
	outb( ICW4, SLAVE_8259_DATA);

	outb(0xff,MASTER_8259_DATA);
	outb(0xff,SLAVE_8259_DATA);
	
	restore_flags(flags);
}

/* Enable (unmask) the specified IRQ */
void
enable_irq(uint32_t irq_num)
{
	uint16_t port;
    uint8_t value;
 
    if(irq_num < 8) {
        port = MASTER_8259_DATA;
    } else {
        port = SLAVE_8259_DATA;
        irq_num -= 8;
		value = inb(MASTER_8259_DATA) & ~(1 << 2);
		outb(value, MASTER_8259_DATA);
    }
    value = inb(port) & ~(1 << irq_num);
    outb( value, port);
}

/* Disable (mask) the specified IRQ */
void
disable_irq(uint32_t irq_num)
{
	uint16_t port;
    uint8_t value;
 
    if(irq_num < 8) {
        port = MASTER_8259_DATA;
    } else {
        port = SLAVE_8259_DATA;
        irq_num -= 8;
    }
    value = inb(port) | (1 << irq_num);
    outb(value, port );
}

/* Send end-of-interrupt signal for the specified IRQ */
void
send_eoi(uint32_t irq_num)
{

	//OR EOI with irq num and send it out to PIC
	/*uint32_t irq_cmd = (irq_num | EOI);

	printf("end of interrupt %d \n", irq_num);
	printf("end of interrupt %d \n", EOI);
	printf("end of interrupt %d \n", irq_cmd);*/

	if(irq_num >= 8)
		outb( 0x20, SLAVE_8259_PORT);
 												//works if i use 0x20 (nonspecific eoi) instead of specific eoi
	outb(0x20, MASTER_8259_PORT); 

}
