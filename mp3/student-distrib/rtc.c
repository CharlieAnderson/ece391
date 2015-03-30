#include "rtc.h"
#include "lib.h"

static int int_flag=0;


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
	int_flag = 1; //interrupt has occurred
	//printf("RTC sent EOI \n");
	sti();
	//test_interrupts();
}


/*
You will need to write the open, read, write, and close functions for the real-time clock (RTC) and demonstrate
that you can change the clock frequency. You will need to do some research on how the RTC works and what the
device driver needs to do to communicate with it. Virtualizing the RTC is not required, but does make testing easier
when you run multiple programs with the RTC open. Again, see Appendix B for how each function should work.
*/


/*
Note that some system calls need to synchronize with interrupt handlers. 
For example, the read system call made on the RTC device should wait 
until the next RTC interrupt has occurred before it returns. 
Use simple volatile flag vari- ables to do this synchronization 
(e.g., something like int rtc interrupt occurred;) when possible
 (try some- thing more complicated only after everything works!), 
and small critical sections with cli/sti. 
For example, writing to the RTC should block interrupts to interact with the device. 
Writing to the terminal also probably needs to block interrupts, if only briefly, 
to update screen data when printing (keyboard input is also printed to 
the screen from the interrupt handler).
*/



/*
3. int32 t read (int32 t fd, void* buf, int32 t nbytes);
4. int32 t write (int32 t fd, const void* buf, int32 t nbytes); 
5. int32 t open (const uint8 t* filename);
6. int32 t close (int32 t fd);
*/




/*write
In the case of the RTC, the system call should always accept 
only a 4-byte integer specifying the interrupt rate in Hz,
 and should set the rate of periodic interrupts accordingly. */
int rtc_write(int rate)
{
	

	if(rate < 6)
		rate = 6; //caps freq at 1024hz by default (rate of 6), otherwise rate must be greater than 2 (freq at most 8192hz)

	if(rate > 15) //lowest freq will b 2hz (rate of 15)
		rate = 15;

	long freq = 32768 >> (rate-1);

	//check rate for power of 2
	if (!((freq != 0) && !(freq & (freq - 1))))
		return -1; 



	//rate &= 0x0F;			// rate must be above 2 and not over 15
	cli();
	outb(0x0A, 0x70);		//set index to register A, disable NMI
	char prev = inb(0x71);	//get initial value of register A
	outb(0x0A, 0x70);		//reset index to A
	outb(((prev & 0xF0) | rate), 0x71); //write only our rate to A. Note, rate is the bottom 4 bits.
	sti();

	return 0;
}

int rtc_read(void)
{

    //wait for interrupt
	while(int_flag == 0){}

	int_flag = 0;

	return 0;
}

int rtc_open(void)
{	rtc_init();
	rtc_write(15); //default rtc rate is 2hz (rate of 15)
	return 0;
}


int rtc_close(void)
{


	return 0;
}


void rtc_test(int new_rate)
{
int flag;
// set RTC speed
flag = rtc_write(new_rate);

if(flag<0)
	return;
long freq = 32768 >> (new_rate-1);
clear();
int counter = 0;
while(1) {
	// read the rtc
	if (rtc_read()==0)
		counter++;
	
	if (counter % 10 == 0) {
		printf("rate: %d frequency: %dhz count: %d cycles \n", new_rate, freq, counter); 
	}

}
}

