#include "paging.h"

static uint32_t page_directory[1024] __attribute__((aligned(4096)));

static uint32_t page_table[1024] __attribute__((aligned(4096)));

/*
void page()
	input: none
	output: none
	description: Initializes paging
	side effect: 4k pages enabled
*/
void page(){
	int i;

	for(i = 0; i < 1024; i++){			//create a page directory and fill it with nothing
		page_directory[i] = BLANK;
	}

	for(i = 0; i<1024; i++){
		page_table[i] = BLANK;			// create a page directory and fill with nothing
	}

	page_table[184] = VIDEO | 0x3;		// map entry 185 to video memory and set proper flags

	page_directory[0] = ((unsigned int)page_table) | 3;		// load page table into page directory
	page_directory[1] = KERNEL | DIR_FLAGS;					// load kernel into page directory

	enablePaging();
}

/*
void enablePaging()
	input: none
	output: none
	description: sets proper registers for enabling paging
	side effect:none
*/
void enablePaging()
{
	asm volatile("                  \n\
			movl 	$page_directory, %%eax \n\
			movl 	%%eax, %%cr3 \n\
			movl	%%cr4, %%eax	\n\
			orl $0x00000010, %%eax	\n\
			movl 	%%eax, %%cr4	\n\
			movl    %%cr0, %%eax	     \n\
			orl $0x80000000, %%eax	\n\
			movl    %%eax, %%cr0      \n\
			"
			:
			:
			: "eax", "cc"
			);
}
