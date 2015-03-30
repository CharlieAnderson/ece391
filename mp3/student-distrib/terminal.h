#ifndef _TERMINAL_H
#define _TERMINAL_H

#include "types.h"
#include "lib.h"
#include "i8259.h"
#include "keyboard.h"

static unsigned char key_buffer[BUFFER_SIZE];

int terminal_open();
int terminal_read(uint8_t * buffer, uint32_t length);
int terminal_write(uint8_t * buffer, uint32_t length);
int terminal_close();

#endif /* _TERMINAL_H */
