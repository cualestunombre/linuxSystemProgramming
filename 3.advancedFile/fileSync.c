#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
int openAndgetLockForParent(char* target) {
    int fd;//파일 디스크립터
    int lock;
    fd = open(target,O_WRONLY|O_CREAT);
    lock = flock(fd,LOCK_EX);
    return fd;
}

int openAndgetLockForChild(char* target) {
    int fd;//파일 디스크립터
    int lock;
    fd = open(target,O_WRONLY|O_CREAT);
    lock = flock(fd,LOCK_EX); // LOCK_NB가 있으면 blocking하지 않는다
    // if(lock==-1){
    //     printf("errono=%d error:%s",errno,strerror(errno));
    // }
    //errorno를 확인해야 한다
    return fd;
}


void closeAndReturnLock(int fd){
    int lock = flock(fd,LOCK_UN);
    close(fd);
}

int main() {
    char* target= "./dummy";
    int fd = openAndgetLockForParent(target);
    pid_t pid = fork(); // 프로세스 분기
    if (pid != 0) { //부모 프로세스
        printf("start to sleep\n");
        sleep(5);
        closeAndReturnLock(fd);
        printf("got up and returned lock\n");
    } else if (pid == 0 ) {//자식 프로세스
        printf("waiting for lock\n");
        fd = openAndgetLockForChild(target);
        closeAndReturnLock(fd);
        printf("got lock and returned");

    } 
    return 0;
}

