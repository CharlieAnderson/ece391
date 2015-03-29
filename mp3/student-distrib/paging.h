#ifndef PAGING_H_
#define PAGING_H_

#include "lib.h"
#include "paging.h"
#include "types.h"

/*Values for working with Paging*/
#define VIDEO 0xB8000
#define KERNEL 0x00400000
#define BLANK 0x00000002
#define DIR_FLAGS 0x83

void page();

void enablePaging();
	
#endif /* PAGING_H_ */
