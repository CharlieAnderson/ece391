#include "lib.h"
#include "paging.h"
#include "types.h"

void page(){
	int i;

	for(i = 0; i < 1024; i++){
		page_directory[i] = 0x00000002;
	}

	for(i = 0; i<1024; i++){
		page_table[i] = 0x00000002;
	}

	page_table[184] = (VIDEO<<12) | 0x1;

	page_directory[0] = ((unsigned int)page_table) | 1;
	page_directory[1] = 0x00400000 | 0x181;

	lpagedir(&page_directory);

	enablePaging();
}

void lpagedir(uint32_t* page_dir_ptr)
{
	asm volatile("                  \n\
			movw    %0, %%eax	     \n\
			movw    %%eax, %%cr3      \n\
			"
			:
			: "a"(page_dir_ptr)
			: "eax"
			);
}

void enablePaging()
{
	asm volatile("                  \n\
			movw    %%cr0, %%eax	     \n\
			or $0x80000001, %%eax	\n\
			movw    %%eax, %%cr0      \n\
			"
			:
			:
			: "eax"
			);
}