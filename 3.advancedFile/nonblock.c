#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
// 파일 컨트롤 
#include <errno.h>

/*
기본적으로 세개의 fd가 열린채로 시작함
0 : stdin
1 : stdout
2 : stderr
파일을 열면 새로운 파일디스크립터가 열린다
이는 표준 입출력이 아니다
운영체제는 표준입력, 표준출력, 표준에러가
파일이 아니지만 파일과 같은 방식으로 입출력을 관리하게 한다
프로세스는 자신의 파일 디스크립터를 관리하여 파일마다 
고유한 파일디스크립터를 부여하여 입출력을 관리한다
*/

int main(int argc,char** argv){
    int fd = STDIN_FILENO;
    int ret;
    int flag;
    char buf[11];
    memset(buf,0,sizeof(buf));
    ret = read(fd, buf, sizeof(buf)-1);
    buf[10]='\0';

    if(ret==-1){
        printf("read failed");
        return -1;
    }
    printf("%s\n",buf);

    // non-blocking 모드로 전환한다
    // flag 확인
    flag = fcntl(STDIN_FILENO,F_GETFL);
    if(flag==-1){
        printf("fcntl failed");
        return -1;
    }

    // non-block 설정, flag를 통해서 현재 설정값 가져옴
    fcntl(fd,F_SETFL,flag | O_NONBLOCK);
    memset(buf,0,sizeof(buf));
    ret = read(fd,buf,sizeof(buf)-1);
    printf("ret size:%d\n",ret);
    printf("%s\n",buf);
    

    /*
    입력 버퍼 지우고 종료
    */
    while((ret=read(fd,buf,sizeof(buf)))!=-1){
    }

    perror("error");


    return 0;
}
