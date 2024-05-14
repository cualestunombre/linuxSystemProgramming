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
/*
int open(const char* pathname, int flags);
int open(const char* pathname, int flags, mode_t mode);
- pathname : 파일경로
- flags : 접근 모드를 포함한 여러 가지 플래그
- mode : 파일 생성 시 설정할 권한

반환값
성공 시 열린 파일 디스크립터
실패 시 -1

플래그
O_RDONLY 읽기 전용
O_WRONLY 쓰기 전용
O_RDWR 읽기 + 쓰기
O_CREAT 파일이 존재하지 않으면 regular file 생성
O_NOFOLLOW 파일이 soft link인 경우 파일 열기 실패
O_TRUNC regular파일이 존재하는 경우 파일 사이즈를 0으로 만듬
O_APPEND append mode로 열기

int close(int fd);
성공시 0 
실패시 -1

주로 같이 쓰이는 함수 dprintf, write, read
*/