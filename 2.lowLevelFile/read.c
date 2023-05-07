#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
static int byte_write(const char* buf){
    int fd;
    fd = open("dummy",O_WRONLY|O_CREAT|O_TRUNC,0777);
    if(fd==-1){
        perror("file open failed");
        return -1;
    }
    write(fd,buf,strlen(buf));
    close(fd);
    return 0;
}

static int byte_read(){
    int fd;
    char buf[100];

    fd = open("dummy",O_RDONLY);
    if(fd==-1){
        perror("file open failed");
        return -1;
    }

    read(fd,buf,sizeof(buf));
    printf("%s\n",buf);
    close(fd);
    return 0;

}

static int dtop(){
    int fd;
    char buf[100];

    fd=open("dummy",O_RDONLY);
    if(fd==-1){
        perror("open failed");
        return -1;
    }
    read(fd,buf,sizeof(buf));
    
    FILE* fp = fdopen(fd,"r");
    long cur = ftell(fp);
    printf("%d",cur);
    fclose(fp);
    return 0;

}


int main(int argc, char** argv){
    char buf[1000];
    scanf("%s",buf);
    byte_write(buf);
    byte_read();
    dtop();
    return 0;
}