#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "types.h"
#include "lib.h"
#include "i8259.h"

/* Ports that each PIC sits on */
#define INDEX_RTC_PORT 	0x70
#define SLAVE_RTC_PORT  0x71
#define KEYBOARD_DATA	0x60

/* Release adds 0x80 to the value */
#define	LCTRL_PRESS		0x1D
#define	LCTRL_RELEASE	0x9D
#define	LSHIFT_PRESS	0x2A
#define	LSHIFT_RELEASE	0xAA
#define RSHIFT_PRESS	0x36
#define RSHIFT_RELEASE	0xB6
#define CAPS_PRESS		0x3A
#define CAPS_RELEASE	0xBA
#define	ENTER_PRESS		0x1C
#define BACKSPACE_PRESS	0x0E

#define BUFFER_SIZE		128
#define KEY_SIZE		60

/* Initialize the keyboard */
void keyboard_init(void);

/* handle keyboard interrupts */
extern void keyboard_handler(void);

void key_echo(unsigned char key, unsigned char capsshift);

void clear_buffer();

int keyboard_open(void);
int keyboard_close(void);

#endif /* _KEYBOARD_H */
