#ifndef PAGING_H_
#define PAGING_H_

	uint32_t page_directory __attribute__((aligned(4096)));

	uint32_t page_table[1024] __attribute__((aligned(4096)));

	void page();

	void lpagedir(uint32_t* page_dir_ptr);

	void enablePaging();
	
#endif PAGING_H_
