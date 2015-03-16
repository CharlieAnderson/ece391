#include "keyboard.h"
#include "lib.h"

/*
void keyboard_init()
input:none
output:none
description:enable keyboard interrupt
side effect:none
*/
void keyboard_init()
{	
	enable_irq(1);
	printf("keyboard is init \n");
}

/*
void keyboard_handler()
input: none
output: none
description: echo the pressed key
side effect:none
*/
void keyboard_handler()
{
	/*send eoi to PIC*/
	cli();
	//printf("handler1");
	/*read the scan code*/
	unsigned char c = 0;
	c = inb(KEYBOARD_DATA);
	key_echo(c);

	//printf("handler2");
	send_eoi(1);
	sti();
	//test_interrupts();
}

/*
void key_echo(unsigned char key)
input:key, scan code received by CPU
output:none
description:map the scan code to actual key
side effect: print the pressed key on screen
*/

void key_echo(unsigned char key)
{
	switch (key) {
		case 2: printf("1"); break;
		case 3: printf("2"); break;
		case 4: printf("3"); break;
		case 5: printf("4"); break;
		case 6: printf("5"); break;
		case 7: printf("6"); break;
		case 8: printf("7"); break;
		case 9: printf("8"); break;
		case 10: printf("9"); break;
		case 11: printf("10"); break;
		case 16: printf("q"); break;
		case 17: printf("w"); break;
		case 18: printf("e"); break;
		case 19: printf("r"); break;
		case 20: printf("t"); break;
		case 21: printf("y"); break;
		case 22: printf("u"); break;
		case 23: printf("i"); break;
		case 24: printf("o"); break;
		case 25: printf("p"); break;
		case 30: printf("a"); break;
		case 31: printf("s"); break;
		case 32: printf("d"); break;
		case 33: printf("f"); break;
		case 34: printf("g"); break;
		case 35: printf("h"); break;
		case 36: printf("j"); break;
		case 37: printf("k"); break;
		case 38: printf("l"); break;
		case 44: printf("z"); break;
		case 45: printf("x"); break;
		case 46: printf("c"); break;
		case 47: printf("v"); break;
		case 48: printf("b"); break;
		case 49: printf("n"); break;
		case 50: printf("m"); break;
		default: break;
	}
	return;

}
