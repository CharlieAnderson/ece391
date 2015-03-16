/* Error codes for IDT initialization */

#include "lib.h"
#include "x86_desc.h"
#include "idt_init.h"

void divide_error() {
    printf("Exception in: Divide Error (idt[0])\n");
	while(1) {}
}

void debug_exception() {
	printf("Exception in: Debug Exception (idt[1])\n");
	while(1) {}
}

void nmi_interrupt() {
	printf("Exception in: NMI Interrupt (idt[2])\n");
	while(1) {}
}

void breakpoint() {
	printf("Exception in: Breakpoint (idt[3])\n");
	while(1) {}
}

void overflow() {
	printf("Exception in: Overflow (idt[4])\n");
	while(1) {}
}

void bound_range_exceeded() {
	printf("Exception in: BOUND Range Exceeded (idt[5])\n");
	while(1) {}
}

void invalid_opcode() {
	printf("Exception in: Invalid Opcode (idt[6])\n");
	while(1) {}
}

void device_not_available() {
	printf("Exception in: Device Not Available (idt[7])\n");
	while(1) {}
}

void double_fault() {
	printf("Exception in: Double Fault (idt[8])\n");
	while(1) {}
}

void coprocessor_segment_overrun() {
	printf("Exception in: Coprocessor Segment Overrun (idt[9])\n");
	while(1) {}
}

void invalid_tss() {
	printf("Exception in: Invalid TSS (idt[10])\n");
	while(1) {}
}

void segment_not_present() {
	printf("Exception in: Segment Not Present (idt[11])\n");
	while(1) {}
}

void stack_fault() {
	printf("Exception in: Stack Fault (idt[12])\n");
	while(1) {}
}

void general_protection() {
	printf("Exception in: General Protection (idt[13])\n");
	while(1) {}
}

void page_fault() {
	printf("Exception in: Page Fault (idt[14])\n");
	while(1) {}
}

void floating_point_error() {
	printf("Exception in: Floating-Point Error (idt[16])\n");
	while(1) {}
}

void alignment_check() {
	printf("Exception in: Alignment Check (idt[17])\n");
	while(1) {}
}

void machine_check() {
	printf("Exception in: Machine Check (idt[18])\n");
	while(1) {}
}

void simd_floating_point_exception() {

	printf("Exception in: SIMD Floating-Point Exception (idt[19])\n");
	while(1) {}
}

void common_exception() {

	printf("Exception in: Common\n");
	while(1) {}
}

void test_keyboard() {
	printf("test keyboard is here");
}

void test_rtc() {
	printf("test rtc here");
}

void test_sys() {
	printf("test sys here");
}

void idt_init() {
	idt_desc_t idt_interrupt;
    idt_interrupt.seg_selector = KERNEL_CS;
    idt_interrupt.reserved4 = 0x0;
    idt_interrupt.reserved3 = 0x0;
    idt_interrupt.reserved2 = 0x1;
    idt_interrupt.reserved1 = 0x1;
    idt_interrupt.reserved0 = 0x0;
	idt_interrupt.size = 0x1;
    idt_interrupt.dpl = 0x0;
    idt_interrupt.present = 0x1;
	
	idt_desc_t idt_exception = idt_interrupt;
	idt_exception.reserved3 = 1;
	
	idt_desc_t idt_syscall = idt_interrupt;
	idt_syscall.dpl = 3;

	int i;
	for (i = 0; i < 32; i++) {
		idt[i]= idt_exception;
	}
	for (i = 32; i < 256; i++) {
		idt[i] = idt_interrupt;
	}
	idt[0x80] = idt_syscall;

	SET_IDT_ENTRY(idt[0], &divide_error);
	SET_IDT_ENTRY(idt[1], &debug_exception);
	SET_IDT_ENTRY(idt[2], &nmi_interrupt);
	SET_IDT_ENTRY(idt[3], &breakpoint);
	SET_IDT_ENTRY(idt[4], &overflow);
	SET_IDT_ENTRY(idt[5], &bound_range_exceeded);
	SET_IDT_ENTRY(idt[6], &invalid_opcode);
	SET_IDT_ENTRY(idt[7], &device_not_available);
	SET_IDT_ENTRY(idt[8], &double_fault);
	SET_IDT_ENTRY(idt[9], &coprocessor_segment_overrun);
	SET_IDT_ENTRY(idt[10], &invalid_tss);
	SET_IDT_ENTRY(idt[11], &segment_not_present);
	SET_IDT_ENTRY(idt[12], &stack_fault);
	SET_IDT_ENTRY(idt[13], &general_protection);
	SET_IDT_ENTRY(idt[14], &page_fault);
	SET_IDT_ENTRY(idt[15], &common_exception);
	SET_IDT_ENTRY(idt[16], &floating_point_error);
	SET_IDT_ENTRY(idt[17], &alignment_check);
	SET_IDT_ENTRY(idt[18], &machine_check);
	SET_IDT_ENTRY(idt[19], &simd_floating_point_exception);
}
