#include "rtc.h"
#include "lib.h"

/* Initialize the rtc */
void
rtc_init(void) {
	cli();
	outb(0x0B, INDEX_RTC_PORT);
	uint8_t prev = inb(DATA_RTC_PORT);
	outb(0x0B, INDEX_RTC_PORT);
	outb(prev | 0x40, DATA_RTC_PORT);
	sti();
	enable_irq(8);

	printf("rtc is init \n");
}

void
rtc_handler(void) {
	cli();
	outb(0x0C,0x70);
	inb(0x71);
	send_eoi(8);
	printf("RTC sent EOI \n");
	sti();
	//test_interrupts();
}
