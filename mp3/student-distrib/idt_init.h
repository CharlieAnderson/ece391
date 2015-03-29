#ifndef _IDT_INIT_H
#define _IDT_INIT_H

void divide_error();
void debug_exception();
void nmi_interrupt();
void breakpoint();
void overflow();
void bound_range_exceeded();
void invalid_opcode();
void device_not_available();
void double_fault();
void coprocessor_segment_overrun();
void invalid_tss();
void segment_not_present();
void stack_fault();
void general_protection();
void page_fault();
void floating_point_error();
void alignment_check();
void machine_check();
void simd_floating_point_exception();
void common_exception();

void idt_init();

#endif
