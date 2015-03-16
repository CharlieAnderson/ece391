#include "rtc.h"

/* Initialize the rtc */
void
rtc_init(void)
{
	cli();  //disable interrupts
	outb(0x0B, INDEX_RTC_PORT); // set index to B
	uint8_t prev = inb(DATA_RTC_PORT); // read value of B
	outb(0x0B, INDEX_RTC_PORT); //set index back to B
	outb(prev | 0x40, DATA_RTC_PORT); //  (prev or with 0x40) will turn on bit 6 of B
	sti();
	enable_irq(8);

	printf("rtc is init \n");
}

 
void
rtc_handler(void)
{
	cli();
	outb(0x0C,0x70);	// select register C
	inb(0x71);			//read C, to let interrupt happen again
	send_eoi(8);
	printf("RTC sent EOI \n");
	sti();
}
