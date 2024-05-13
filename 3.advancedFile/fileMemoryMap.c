#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

struct person{
        char name[20];
        int age;
};

static int byte_write(){
    struct person parr[2]={{.age=20,.name="seok"},{.age=25,.name="lydia"}};

    int fd;
    fd = open("dummy",O_RDWR|O_CREAT|O_TRUNC,0777);
    
    if(fd==-1){
        perror("file open failed");
        return -1;
    }

    write(fd,parr,sizeof(parr));
    return fd;
}
static int map_file(int descriptor){
    char* addr;
    addr=mmap(NULL, sizeof(struct person)*2,PROT_READ|PROT_WRITE,MAP_SHARED,descriptor,0);
    addr[0]='p';
    struct person* temp = (struct person*)addr;
    printf("%s %d",temp->name,temp->age);
    temp = (struct person*)(addr+24);
    printf("%s %d",temp->name,temp->age);
    munmap(addr,sizeof(struct person)*2);
    close(descriptor);
    
    return 1;
}

int main(int argc, char**argv){
    int descriptor = byte_write();
    map_file(descriptor);

}