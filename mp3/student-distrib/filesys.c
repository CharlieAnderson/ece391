#include "filesys.h"
#include "lib.h"

static uint32_t* start;
static uint32_t num_entries;
static uint32_t num_inodes; 
static uint32_t num_data;
static dentry_t* dirs;
static uint8_t* data_blocks;
static inode_t* inode_ptr;
static fd_t fd_array[8];

void filesys_init(uint32_t mod_start)
{clear();
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

	inode_ptr = (inode_t*)(start + BLOCK_OFFSET);
	printf("inode_ptr %x end\n", inode_ptr);

	data_blocks = (uint8_t*)(start + BLOCK_OFFSET + num_inodes*BLOCK_OFFSET);
	//data_blocks = (uint32_t*)(start+(num_inodes+1)*BLOCK_OFFSET);
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
	uint32_t i, count_offset;
	inode_t curr_inode = inode_ptr[inode];
	uint32_t data_length;
	uint32_t data_block_index = curr_inode.inode_data_blocks[offset/BLOCK_SIZE];
	//uint32_t* data_block_0 = data_blocks[data_block_index];
	uint32_t inode_idx = offset/BLOCK_SIZE;

	uint8_t* start_addr = (uint8_t*)(data_blocks + BLOCK_SIZE*data_block_index + offset % BLOCK_SIZE);

	printf("data_block_index %d end\n", data_block_index);

	printf("inode_ptr[inode] %x end\n", &inode_ptr[inode]);
	printf("inode %d end\n", inode);
	printf("data_block_index %d end\n", data_block_index);
	printf("inode_idx %d end\n", inode_idx);
	printf("start_addr %x end\n", start_addr);
	data_length = curr_inode.length;
	printf("data_length %d end\n", data_length);
	if(start_addr == NULL)
		return -1;

	if(inode > num_inodes)
		return -1;

	// if(length + offset > data_length)
	// 	return -1;

	count_offset = offset % BLOCK_SIZE;
	for(i = 0; i < length; i++)
	{
		/*check if we need a new block*/
		if (count_offset >= BLOCK_SIZE){
			count_offset = 0;
			inode_idx++;
			data_block_index = curr_inode.inode_data_blocks[inode_idx];

			if(data_block_index >= num_data)
				return -1;

			start_addr = (uint8_t*)(data_blocks+ BLOCK_SIZE*data_block_index);

		}

		/*read data*/
		buf[i] = *start_addr;
		count_offset++;
		start_addr++;
		if (*((int8_t*)start_addr) == EOF)
			return 0;

	}
	return length; 
}

int32_t file_open (const uint8_t* filename)
{
	dentry_t* dentry;
	if (-1 == read_dentry_by_name(filename, dentry))
		return -1;
	int i;
	for (i=0; i<8; i++){
		if (fd_array[i].flags == 0){
			fd_array[i].inode_ptr = dentry->inode;
			fd_array[i].flags = 1;
			fd_array[i].file_pos = 0;
			return i;
		}
	}
	return -1;
}

int32_t file_close (int32_t fd)
{
	if (fd > 7)
		return -1;
	fd_array[fd].flags = 0;
	return 0;
}

int32_t file_read (uint32_t fd, void* buf, int32_t nbytes)
{
	int32_t ret = read_data(fd_array[fd].inode_ptr, fd_array[fd].file_pos, buf, nbytes);
	if (ret != 0)
		fd_array[fd].file_pos += ret;
	else if (ret == -1)
		return -1;
	return 0;
}

int32_t file_write(void)
{

	return -1;
}

int32_t dir_open (const uint8_t* filename)
{
	int i;
	for (i=0; i<8; i++){
		if (fd_array[i].flags == 0){
			fd_array[i].flags = 1;
			fd_array[i].file_pos = 0;
			return i;
		}
	}
	return -1;
}

int32_t dir_close (int32_t fd)
{
	if (fd > 7)
		return -1;
	fd_array[fd].flags = 0;
	return 0;
}

int32_t dir_read (uint32_t fd, void* buf, int32_t nbytes)
{
	if (fd_array[fd].file_pos >= num_entries)
		return 0;
	dentry_t* dentry;
	int32_t ret = read_dentry_by_index(fd_array[fd].file_pos, dentry);
	fd_array[fd].file_pos++;
	buf = dentry->name;
	return 0;
}

int32_t dir_write(void)
{
	return -1;
}