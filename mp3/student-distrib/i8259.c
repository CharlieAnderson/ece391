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

												//not usr eif io_wait() is needed
	uint16_t mask1 = inb(master_data);
	uint16_t mask2 = inb(slave_data);

														//THESE MIGHT ALL BE REVERESED, like ICW then port... due to different syntax GAS
	outb(MASTER_8259_PORT, ICW1);  
	io_wait();
	outb(SLAVE_8259_PORT, ICW1);
	io_wait();


	outb(PIC1_DATA, ICW2_MASTER);                 
	io_wait();
	outb(PIC2_DATA, ICW2_SLAVE);                 
	io_wait();


	outb(master_data, ICW3_MASTER);                       
	io_wait();
	outb(slave_data, ICW3_SLAVE);                      
	io_wait();
 

	outb(master_data, ICW4);
	io_wait();
	outb(slave_data, ICW4);
	io_wait();
 

	outb(master_data, mask1);  
	outb(slave_data, mask2);



}

/* Enable (unmask) the specified IRQ */
void
enable_irq(uint32_t irq_num)
{
	uint16_t port;
    uint8_t value;
 
    if(irq_num < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq_num -= 8;
    }
    value = inb(port) & ~(1 << irq_num);
    outb(port, value)
}

/* Disable (mask) the specified IRQ */
void
disable_irq(uint32_t irq_num)
{
	uint16_t port;
    uint8_t value;
 
    if(irq_num < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq_num -= 8;
    }
    value = inb(port) | (1 << irq_num);
    outb(port, value)
}

/* Send end-of-interrupt signal for the specified IRQ */
void
send_eoi(uint32_t irq_num)
{

//OR EOI with irq num and send it out to PIC
uint8_t irq_cmd = irq_num | EOI;

	if(irq_num >= 8)
		outb(SLAVE_8259_PORT, irq_cmd);
 
	outb(MASTER_8259_PORT,irq_cmd); //might change second param for both, it should be the command to send

}

