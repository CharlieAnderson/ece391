#include "keyboard.h"
#include "lib.h"
#include "terminal.h"

static char keys[4][KEY_SIZE] = {
	/* No caps/shift */
	{ '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
	  '\0', '\0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']',
	  '\0', '\0', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`',
	  '\0', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', '\0', '*',
	  '\0', ' ', '\0'},
	/* Caps lock */
	{ '\0', '\0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=',
	  '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']',
	  '\0', '\0', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',
	  '\0', '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '\0', '*',
	  '\0', ' ', '\0'},
	/* Shift */
	{ '\0', '\0', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
	  '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '{', '}',
	  '\0', '\0', 'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', '"', '~',
	  '\0', '|', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', '<', '>', '?', '\0', '*',
	  '\0', ' ', '\0'},
	/* Caps and shift */
	{ '\0', '\0', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+',
	  '\0', '\0', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}',
	  '\0', '\0', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ':', '"', '~',
	  '\0', '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '<', '>', '?', '\0', '*',
	  '\0', ' ', '\0'}
};

static unsigned char buffer_info[BUFFER_SIZE];
static unsigned char key_buffer[BUFFER_SIZE];
static int buffer_index = 0;
static unsigned char capsshift = 0;		// 0 = regular, 1 = caps, 2 = shift, 3 = both
static unsigned char ctrl = 0;		// 0 = not pressed, 1 = pressed
static int file_open = 0;
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
	switch (c) {
		case LCTRL_PRESS: 
			ctrl = 1;
			break;
		case LCTRL_RELEASE:
			ctrl = 0;
			break;
		case ENTER_PRESS:
			if (buffer_index < BUFFER_SIZE) {
				key_buffer[buffer_index] = '\n';
			}
			terminal_read(buffer_info, 0);
			break;
		case BACKSPACE_PRESS:
			if (buffer_index > 0) {
				backspace();
				buffer_index -= 1;
			}
			break;
		case LSHIFT_PRESS:
			if (capsshift == 0) {
				capsshift = 2;
			} else if (capsshift == 1) {
				capsshift = 3;
			}
			break;
		case LSHIFT_RELEASE:
			if (capsshift == 2) {
				capsshift = 0;
			} else if (capsshift == 3) {
				capsshift = 1;
			}
			break;
		case RSHIFT_PRESS:
			if (capsshift == 0) {
				capsshift = 2;
			} else if (capsshift == 1) {
				capsshift = 3;
			}
			break;
		case RSHIFT_RELEASE:
			if (capsshift == 2) {
				capsshift = 0;
			} else if (capsshift == 3) {
				capsshift = 1;
			}
			break;
		case CAPS_PRESS:
			if (capsshift == 0) {
				capsshift = 1;
			} else if (capsshift == 1) {
				capsshift = 0;
			} else if (capsshift == 2) {
				capsshift = 3;
			} else if (capsshift == 3) {
				capsshift = 2;
			}
			break;
		case CAPS_RELEASE:
			break;
		default:
			key_echo(c, capsshift);
			break;
	}

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

void key_echo(unsigned char key, unsigned char capsshift)
{
	if (key == 0x26 && ctrl == 1) {
		clear();
		clear_buffer();
		return;
	}
	
	if ((key < (KEY_SIZE - 1)) && (buffer_index < BUFFER_SIZE)) {
		char c = keys[capsshift][key];
		key_buffer[buffer_index] = c;
		buffer_index++;
		printf("%c", c);
	}
	return;
}

void clear_buffer() {
	int i = 0;
	for (i = 0; i <= BUFFER_SIZE; i++) {
		key_buffer[i] = '\0';
	}
	buffer_index = 0;
}


int keyboard_open(void)
{	
	keyboard_init();
	file_open = 1;

	return 0;
}

int keyboard_close(void)
{
	file_open = 0;

	return 0;
}