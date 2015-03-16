/* keyboard.h
 * defines the keyboard handler and constants to be used by it
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

#define KEYBOARD_IRQ 1
#define KEYBOARD_PORT 0x60
#define SCAN_CODE_SIZE 0x67	//just big enough to span scan codes of numbers and letters

/* prints key pressed (lower case letters and numbers) */
extern void keyboard_handler();

#endif /* KEYBOARD_H */
