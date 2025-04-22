#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define MAX_BLOCKS 1024
#define MAX_INODES 64
#define MAX_FILENAME_LEN 32
#define MAX_FILES_PER_DIR 64
#define BLOCK_SIZE 512

typedef struct{
    char data[BLOCK_SIZE];
}Block;

typedef struct{
    char name[MAX_FILENAME_LEN];
    int size;
    int blocks[8];
    int is_directory;
}Inode;

typedef struct{
    int inode_indexes[MAX_FILES_PER_DIR];
    int file_count;
}Directory;

typedef struct{
    int total_blocks;
    int used_blocks;
    int total_inodes;
    int used_inodes;
}Superblock;




void init_filesystem();
void delete_folder(const char* name);
void create_folder(const char* name);
void delete_file(const char* name);
void create_file(const char* name);
void list_directories();
int find_file(const char* name);

#endif