/* i8259.c - Functions to interact with the 8259 interrupt controller
 * vim:ts=4 noexpandtab
 */

#include "i8259.h"
#include "lib.h"

/* Interrupt masks to determine which interrupts
 * are enabled and disabled */
uint8_t master_mask; /* IRQs 0-7 */
uint8_t slave_mask; /* IRQs 8-15 */

uint8_t master_data = (MASTER_8259_PORT+1);
uint8_t slave_data = (SLAVE_8259_PORT+1);

/* Initialize the 8259 PIC */
void
i8259_init(void)
{												//based off of wiki.osdev.org ===============================================================================================================================>

	uint16_t mask1 = inb(master_data);
	uint16_t mask2 = inb(slave_data);

														
	outb( ICW1, MASTER_8259_PORT);  
	outb( ICW1, SLAVE_8259_PORT);



	outb( ICW2_MASTER, master_data);                 
	outb( ICW2_SLAVE, slave_data);                 


	outb( ICW3_MASTER, master_data);                       
	outb( ICW3_SLAVE, slave_data);                      
 

	outb( ICW4, master_data);
	outb( ICW4, slave_data);
 

	outb( mask1, master_data);  
	outb( mask2, slave_data);



}

/* Enable (unmask) the specified IRQ */
void
enable_irq(uint32_t irq_num)
{
	uint16_t port;
    uint8_t value;
 
    if(irq_num < 8) {
        port = master_data;
    } else {
        port = slave_data;
        irq_num -= 8;
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
        port = master_data;
    } else {
        port = slave_data;
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
uint8_t irq_cmd = irq_num | EOI;

	if(irq_num >= 8)
		outb( irq_cmd, SLAVE_8259_PORT);
 
	outb(irq_cmd, MASTER_8259_PORT); 

}

