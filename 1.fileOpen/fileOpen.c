#include <stdio.h>
#include <string.h>


int write_to_file(void){
        FILE* fp;
        fp = fopen("dummy","w");
        if (fp==NULL){
                perror("fopen error\n"); //표준에러 메세지 출력
                return -1;
        }
        fputs("hello world",fp);
        fclose(fp);
        return 0;
}

/*
fopen - FILE *fopen(const char* pathname, const char* mode)
반환값 : 
성공시 열린 파일 포인터 
실패시 NULL
r 읽기o, 쓰기x 파일 포지션:파일 시작, 파일 존재시:성공, 파일 부재시:실패
r+ 읽기o, 쓰기x 파일 포지션: 파일 시작, 파일 존재시:성공, 파일 부재시:실패
w 읽기x, 쓰기o 파일 포지션: 파일 시작, 파일 존재시:기존 파일 제거 후 생성, 파일 부재시:생성
w+ 읽기o, 쓰기o 파일 포지션: 파일 시작, 파일 존재시:기존 파일 제거 후 생성, 파일 부재시:생성
a 읽기x, 쓰기o 파일 포지션: 파일 끝, 파일 존재시: 성공, 파일 부재시:생성
a+ 읽기o, 쓰기o 파일 포지션: 읽기- 파일 시작, 쓰기 - 파일 끝 , 파일 존재시 성공, 파일 부재시:생성
*/


int read_from_file(void){
    FILE* fp=NULL;
    char buf[1024];
    fp=fopen("dummy","r");
    if (fp==NULL){
            perror("fopen error\n");
            return -1;
    }
    memset(buf,0,sizeof(buf));
    fgets(buf,sizeof(buf),fp);
    printf("output = %s\n",buf);
    fclose(fp);
    return 0;
}

/*
fgets - char* fgets(char*s, int size, FILE* stream);
개행문자나 파일의 끝까지 문자열을 읽어 옴
성공시 캐릭터 포인터 반환
실패시 NULL 반환

fopen은 주로 fgets, fputs, fwrite, fread와 많이 씀
*/


int main(int argc, char** argv){
    write_to_file();
    read_from_file();
    return 0;
}