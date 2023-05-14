#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include  <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>


int main(int argc , char** argv){
    struct stat statbuf;
    int* arr;
    if(argc<2){
        printf("usage: %s filename\n",argv[0]);
        return -1;
    }
    if (stat(argv[1],&statbuf)){
        printf("stat() fail\n");
    }
    printf("filename: %s\n",argv[0]);
    printf("size %d\n",(int)statbuf.st_size);
    if(S_ISDIR(statbuf.st_mode)){
        printf("this is a direcotry");
    }else{
        printf("this is not a directory");
    }
    
    return 0;
}