#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include "types.h"
#include "lib.h"
#include "i8259.h"

/* Ports that each PIC sits on */
#define INDEX_RTC_PORT 	0x70
#define SLAVE_RTC_PORT  0x71
#define KEYBOARD_DATA	0x60

/* Initialize the keyboard */
void keyboard_init(void);

/* handle keyboard interrupts */
extern void keyboard_handler(void);

void key_echo(unsigned char key);

#endif /* _KEYBOARD_H */
