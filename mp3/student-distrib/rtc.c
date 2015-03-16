#include "rtc.h"

/* Initialize the rtc */
void
rtc_init(void)
{
	enable_irq(8);
	cli();  //disable interrupts
	outb(0x0B, INDEX_RTC_PORT); // set index to B
	uint8_t prev = inb(DATA_RTC_PORT); // read value of B
	outb(0x0B, INDEX_RTC_PORT); //set index back to B
	outb(prev | 0x40, DATA_RTC_PORT); //  (prev or with 0x40) will turn on bit 6 of B
	sti();
	printf("rtc is init");
}


void
rtc_handler(void)
{
	cli();
	send_eoi(8);
	outb(0x0C,0x70);	// select register C
	inb(0x71);
	printf("a");
	sti();
}
