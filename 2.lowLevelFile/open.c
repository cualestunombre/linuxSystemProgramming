#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int trunc_file(void){
    int fd;//파일 디스크립터
    fd = open("datafile",O_WRONLY|O_CREAT|O_APPEND);
    if (fd==-1){
        perror("file open failed!!\n");
        return -1;
    }

    dprintf(fd, "hahahaha\n");

    close(fd);
    return 0;
}

static int write_file(void){
    int fd;//파일 디스크립터
    fd = open("datafile",O_WRONLY|O_CREAT|O_TRUNC,S_IRWXU|S_IRWXO|S_IRWXG);
    if (fd==-1){
        perror("file open failed!!\n");
        return -1;
    }
    
    dprintf(fd, "hello world\n");

    close(fd);
    return 0;
}

int main(int argc, char** argv){
    write_file();
    trunc_file();
    return 0; 
}