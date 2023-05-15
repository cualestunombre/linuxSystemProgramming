#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>

#define TYPE2STR(x) \
    ((x) == DT_BLK ? "block device" : \
    (x) == DT_CHR ? "character device" : \
    (x) == DT_DIR ? "directory" : \
    (x) == DT_FIFO ? "named pipe" : \
    (x) == DT_LNK ? "symbolic link" : \
    (x) == DT_REG ? "regular file" : \
    (x) == DT_SOCK ? "socket file" : \
    "unknown")

int main(int argc, char **argv){
    DIR* dp;

    dp = opendir(".");
    if(dp==NULL){
        printf("fail to load the directory");
        return -1;
    }
    struct dirent* dir; 

    while((dir=readdir(dp))!=NULL){
        printf("inode : %llu\n",dir->d_ino);
        printf("type:%s name:%s\n",TYPE2STR(dir->d_type),dir->d_name);

    }


    closedir(dp);
    return 0;
}