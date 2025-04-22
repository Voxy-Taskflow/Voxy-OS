#include "filesystem.h"
#include "strings.h"
#include "print.h"

Block blocks[MAX_BLOCKS];
Inode inodes[MAX_INODES];
Directory root_dir;
Superblock superblock;

void init_filesystem() {
    print_set_color(PRINT_COLOR_LIGHT_CYAN, PRINT_COLOR_BLACK);
    print_str("FileSystem Initialised");
    superblock.total_blocks = MAX_BLOCKS;
    superblock.used_blocks = 0;
    superblock.total_inodes = MAX_INODES;
    superblock.used_inodes = 0;

    for (int i = 0; i < MAX_INODES; i++) {
        inodes[i].name[0] = '\0';
        inodes[i].size = 0;
        inodes[i].is_directory = 0;
        for (int j = 0; j < 8; j++) {
            inodes[i].blocks[j] = -1;
        }
    }

    root_dir.file_count = 0;
}

int find_free_inode() {
    for (int i = 0; i < MAX_INODES; i++) {
        if (inodes[i].name[0] == '\0') {
            return i;
        }
    }
    return -1;
}

int find_file(const char* name) {
    for (int i = 0; i < root_dir.file_count; i++) {
        int idx = root_dir.inode_indexes[i];
        if (strings_equal(inodes[idx].name, name)) {
            print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
            print_str("\nFile found at index: ");
            // Convert index to string and print
            char idx_str[3] = {0};
            int temp = idx;
            int pos = 0;
            do {
                idx_str[pos++] = '0' + (temp % 10);
                temp /= 10;
            } while (temp > 0);
            // Print in reverse
            while (pos > 0) {
                print_char(idx_str[--pos]);
            }
            print_str("\n");
            return idx;
        }
    }
    print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLACK);
    print_str("\nFile not found!\n");
    return -1;
}

void create_file(const char* name) {
    if (find_file(name) != -1) {
        print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLACK);
        print_str("\nError: File already exists!\n");
        return;
    }

    int inode_index = find_free_inode();
    if (inode_index == -1) {
        print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLACK);
        print_str("\nError: No free inodes available!\n");
        return;
    }

    Inode* node = &inodes[inode_index];
    int i = 0;
    while (name[i] && i < MAX_FILENAME_LEN - 1) {
        node->name[i] = name[i];
        i++;
    }
    node->name[i] = '\0';
    node->size = 0;
    node->is_directory = 0;

    root_dir.inode_indexes[root_dir.file_count++] = inode_index;
    superblock.used_inodes++;

    print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
    print_str("\nFile created successfully at index: ");
    char idx_str[3] = {0};
    int temp = inode_index;
    int pos = 0;
    do {
        idx_str[pos++] = '0' + (temp % 10);
        temp /= 10;
    } while (temp > 0);
    while (pos > 0) {
        print_char(idx_str[--pos]);
    }
    print_str("\n");
}

void delete_file(const char* name) {
    int inode_index = find_file(name);
    if (inode_index == -1) return;

    Inode* node = &inodes[inode_index];
    node->name[0] = '\0';
    node->size = 0;
    for (int i = 0; i < 8; i++) {
        node->blocks[i] = -1;
    }

    for (int i = 0; i < root_dir.file_count; i++) {
        if (root_dir.inode_indexes[i] == inode_index) {
            for (int j = i; j < root_dir.file_count - 1; j++) {
                root_dir.inode_indexes[j] = root_dir.inode_indexes[j + 1];
            }
            root_dir.file_count--;
            break;
        }
    }
    superblock.used_inodes--;
}

void create_folder(const char* name) {
    int inode_index = find_free_inode();
    if (inode_index == -1) return;

    Inode* node = &inodes[inode_index];
    int i = 0;
    while (name[i] && i < MAX_FILENAME_LEN - 1) {
        node->name[i] = name[i];
        i++;
    }
    node->name[i] = '\0';
    node->size = 0;
    node->is_directory = 1;

    root_dir.inode_indexes[root_dir.file_count++] = inode_index;
    superblock.used_inodes++;
}

void delete_folder(const char* name) {
    delete_file(name); // for now, same logic
}

void list_directories() {
    print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_BLACK);
    print_str("\nDirectory Listing:\n");
    print_str("----------------\n");
    
    if (root_dir.file_count == 0) {
        print_str("No files or directories.\n");
        return;
    }

    for (int i = 0; i < root_dir.file_count; i++) {
        Inode* node = &inodes[root_dir.inode_indexes[i]];
        if (node->is_directory) {
            print_set_color(PRINT_COLOR_BLUE, PRINT_COLOR_BLACK);
            print_str("[DIR] ");
        } else {
            print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
            print_str("[FILE] ");
        }
        print_str(node->name);
        print_str("\n");
    }
}

void find_folder(const char* name) {
    int idx = find_file(name);
    if (idx != -1 && inodes[idx].is_directory) {
        print_set_color(PRINT_COLOR_GREEN, PRINT_COLOR_BLACK);
        print_str("Found directory at index: ");
        // Print index number
        char idx_str[3] = {0};
        int temp = idx;
        int pos = 0;
        do {
            idx_str[pos++] = '0' + (temp % 10);
            temp /= 10;
        } while (temp > 0);
        while (pos > 0) {
            print_char(idx_str[--pos]);
        }
        print_str("\n");
    } else {
        print_set_color(PRINT_COLOR_RED, PRINT_COLOR_BLACK);
        print_str("Directory not found!\n");
    }
}
