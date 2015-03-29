#define ASM     1

#include "x86_desc.h"

.text

.globl irq_keyboard
.globl irq_rtc

.align 4

irq_keyboard:
	pushal
	call keyboard_handler 
	popal
	iret

irq_rtc:
	pushal
	call rtc_handler
	popal
	iret

.end
