#include "terminal.h"
#include "lib.h"
#include "keyboard.h"

int terminal_open() {
	return 0;
}

int terminal_read(uint8_t * buffer, uint32_t length) {
	int i = 0;
	while ((key_buffer[i] != '\n') && (i < BUFFER_SIZE)) {
		buffer[i] = key_buffer[i];
		i++;
	}
	buffer[i] = '\n';
	enter();
	clear_buffer();
	return i;
}

int terminal_write(uint8_t * buffer, uint32_t length) {
	int i = 0;
	enter();
	clear_buffer();
	while (i < length) {
		printf("%c", buffer[i]);
		i++;
	}
	enter();
	clear_buffer();
	return i;
}

int terminal_close() {
	return 0;
}
