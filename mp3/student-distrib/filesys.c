#include "filesys.h"
#include "lib.h"

static uint32_t* start;
static uint32_t num_entries;
static uint32_t num_inodes; 
static uint32_t num_data;
static dentry_t* dirs;

void filesys_init(uint32_t mod_start)
{
	start = (uint32_t*)mod_start;
	printf("start: %x end \n", start);
	num_entries = *start;
	printf("num_entries %d end \n", num_entries);
	num_inodes = *(start + NUM_INODES_OFFSET);
	printf("num_inodes %d end \n", num_inodes);
	num_data = *(start + NUM_DATA_OFFSET);
	printf("num_data %d end \n", num_data);
	dirs = (dentry_t*)(start + DIR_ENTRIES_OFFSET);
	printf("dirs: %x end \n", dirs);

	printf("file system is init \n");
}

int32_t read_dentry_by_name (const uint8_t* fname, dentry_t* dentry)
{
	uint32_t i;
	int32_t flag = -1;

	printf("%s\n", fname);

	if(dentry == NULL)
		return flag;

	/* find the file with name fname */
	for(i = 0; i < num_entries; i++)
	{
		printf("i: %d endi ", i);
		printf("name: %s endname \n", (int8_t*)(dirs[i].name));

		if(strlen((int8_t*)fname) != strlen((int8_t*)(dirs[i].name)))
			continue;

		if(strncmp((int8_t*)fname, (int8_t*)(dirs[i].name), strlen((int8_t*)fname)) == 0)
		{
			flag = 0;
			break;
		}
	}
	/* if successfully found, fill dentry */
	if(flag == 0)
	{
		strcpy((int8_t*)dentry->name, (int8_t*)fname);
		dentry->type = dirs[i].type ;
		dentry->inode = dirs[i].inode;
		printf("dentry type: %d endtype \n", dentry->type);
		printf("dentry inode: %d endinode\n", dentry->inode);

	}

	return flag;
}

int32_t read_dentry_by_index (const uint8_t index, dentry_t* dentry)
{




	if(dentry == NULL)
		return -1;



	if(index>num_entries)
		return -1;
		



	/* if successfully found, fill dentry */
	else
	{
		strcpy((int8_t*)dentry->name, (int8_t*)dirs[index].name);
		dentry->type = dirs[index].type ;
		dentry->inode = dirs[index].inode;
		printf("name: %s endname \n", (int8_t*)(dentry->name));
		printf("dentry type: %d endtype \n", dentry->type);
		printf("dentry inode: %d endinode\n", dentry->inode);

	}

	return 0;
}

int32_t read_data (uint32_t inode, uint32_t offset, uint8_t* buf, uint32_t length)
{
	/*
	uint32_t num_inodes = *((uint32_t*)(*(uint32_t*)MODULE_0 + NUM_INODES_OFFSET));
	int32_t flag = -1;
	uint32_t* curr_inode = (uint32_t*)MODULE_0 + 1 + inode;
	uint32_t data_length = *curr_inode/4;
	uint32_t* curr_data = (uint32_t*)(*curr_inode + offset);
	uint32_t i;

	if(inode > num_inodes)
		return flag;
	if(length > data_length)
		return flag;

	for(i = 0; i < length; i++)
	{
		buf[i] = *curr_data;
		curr_data += DATA_OFFSET;
	}
	flag = 0;
	return flag; */
	return -1;

}
