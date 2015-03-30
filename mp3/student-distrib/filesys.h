#ifndef _FILESYS_H
#define _FILESYS_H

#include "types.h"
#include "multiboot.h"

/* start address of file system */
#define DIR_ENTRIES_OFFSET 16
#define TYPE_OFFSET 8
#define INODE_OFFSET 9
#define NUM_INODES_OFFSET 1
#define NUM_DATA_OFFSET 2
#define BLOCK_OFFSET 1024
#define BLOCK_SIZE 4096 
#define EOF -1

typedef struct 
{
	uint8_t name[32];
	uint32_t type;
	uint32_t inode;
	uint8_t reserved[24];

} dentry_t;

typedef struct 
{
	uint32_t length;
	uint32_t inode_data_blocks[1023];
} inode_t;

typedef struct 
{
	uint32_t file_op_pointer;
	uint32_t inode_ptr;
	uint32_t file_pos;
	uint32_t flags;
} fd_t;

void filesys_init(uint32_t mod_start);
int32_t read_dentry_by_name (const uint8_t* fname, dentry_t* dentry);
int32_t read_dentry_by_index (const uint8_t index, dentry_t* dentry);
int32_t read_data (uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length);

int32_t file_open (const uint8_t* filename);


int32_t file_close (int32_t fd);

int32_t file_read (uint32_t fd, void* buf, int32_t nbytes);

int32_t file_write(void);

int32_t dir_open (const uint8_t* filename);

int32_t dir_close (int32_t fd);

int32_t dir_read (uint32_t fd, void* buf, int32_t nbytes);

int32_t dir_write(void);


#endif /* _FILESYS_H */
