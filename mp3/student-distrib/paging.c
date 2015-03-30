#include "paging.h"

static uint32_t page_directory[1024] __attribute__((aligned(4096)));

static uint32_t page_table[1024] __attribute__((aligned(4096)));

void page(){
	int i;

	for(i = 0; i < 1024; i++){
		page_directory[i] = BLANK;
	}

	for(i = 0; i<1024; i++){
		page_table[i] = BLANK;
	}

	page_table[184] = VIDEO | 0x3;

	page_directory[0] = ((unsigned int)page_table) | 3;
	page_directory[1] = KERNEL | DIR_FLAGS;

	//lpagedir(page_directory);

	enablePaging();
}

void lpagedir(uint32_t* page_dir_ptr)
{
	asm volatile("                  \n\
			movl    %%eax, %%cr3      \n\
			"
			:
			: "a"(page_dir_ptr)
			);
}

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
