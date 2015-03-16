#include "keyboard.h"
#include "i8259.h"
#include "lib.h"

/* scan code set 2 */
/* I set most things we don't need yet to null except the ascii things */
unsigned char key_table[SCAN_CODE_SIZE] =
{
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 	/* 0x00 - 0x14 */
	'q','1',									/* 0x15 - 0x16 */
	0,0,0,										/* 0x17 - 0x19 */
	'z','s','a','w','2',						/* 0x1A - 0x1E */
	0,0,										/* 0x1F - 0x20 */
	'c','x','d','e','4','3',					/* 0x21 - 0x26 */
	' ','v','f','t','r','5',					/* 0x29 - 0x2E */
	0,0,										/* 0x2F - 0x30 */
	'n','b','h','g','y','6',					/* 0x31 - 0x36 */
	0,0,0,										/* 0x37 - 0x39 */
	'm','j','u','7','8',						/* 0x3A - 0x3E */
	0,0,										/* 0x3F - 0x40 */
	',','k','i','o','0','9',					/* 0x41 - 0x46 */
	0,0,										/* 0x47 - 0x48 */
	'.','/','l',';','p','-',					/* 0x49 - 0x4E */
	0,0,0,										/* 0x4F - 0x51 */
	44,											/* 0x52 apostrophe */
	0,											/* 0x53 */
	'[','=',									/* 0x54 - 0x55 */
	0,0,0,0,									/* 0x56 - 0x59 */
	10,											/* 0x5A newline */
	']',										/* 0x5B */
	0,											/* 0x5C */
	92,											/* 0x5D backslash */
	0,0,0,0,0,0,0,0,							/* 0x5E - 0x65 */
	8											/* 0x66 backspace */

};

/*
* void keyboard_handler()
*   Inputs: none
*   Return Value: none
*   Output: print the number or letter pressed
*	Function: read scan code from keyboard and print the character
*/
void keyboard_handler()
{
	cli();
	unsigned char keyboard_scan = inb(KEYBOARD_PORT);
	unsigned char key_pressed = 0x0;

	/* if it's in range of the table */
	if(keyboard_scan < 0x67)
		key_pressed = key_table[keyboard_scan];

	printf("%x\n", key_pressed);	

	send_eoi(KEYBOARD_IRQ);
	sti();
}
