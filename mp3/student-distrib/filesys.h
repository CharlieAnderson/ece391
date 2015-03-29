#ifndef _FILESYS_H
#define _FILESYS_H

#include "types.h"
#include "multiboot.h"

/* start address of file system */
#define DIR_ENTRIES_OFFSET 16
#define TYPE_OFFSET 8
#define INODE_OFFSET 9
//#define DATA_OFFSET 4
#define NUM_INODES_OFFSET 1
#define NUM_DATA_OFFSET 2
//#define NAME_BYTES 32

typedef struct 
{
	uint8_t name[32];
	uint32_t type;
	uint32_t inode;
	uint8_t reserved[24];

} dentry_t;

/*
typedef struct 
{
	dentry_t dirs[DIR_ENTRIES];
	uint8_t* dir_entries;
	uint32_t num_entries;
	uint32_t num_inodes;
	uint32_t* start;

} filesys_t;
*/

void filesys_init(uint32_t mod_start);
int32_t read_dentry_by_name (const uint8_t* fname, dentry_t* dentry);
int32_t read_dentry_by_index (const uint8_t index, dentry_t* dentry);
int32_t read_data (uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length);

#endif /* _FILESYS_H */
