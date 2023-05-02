#include <stdio.h>
#include <string.h>

static int create_file(void){
        FILE* fp;

        if(!(fp=fopen("dummy","w"))){
                perror("fopen fail\n");
                return -1;
        }
        printf("after fopen() offset = %ld\n",ftell(fp));
        fputs("hello world\n",fp);
        fputs("hello world\n",fp);
        printf("before fclose() offset =%ld\n",ftell(fp));
        fclose(fp);
        return 0;
}
static int read_file(void){
    FILE* fp;
    char buf[1024];
    if(!(fp=fopen("dummy","r+"))){
        perror("fopen fail\n");
        return -1;
    }
    printf("after fopen offset=%ld\n",ftell(fp));
    memset(buf,0,sizeof(buf));

    fgets(buf,sizeof(buf),fp);
    printf("after fgets offset=%ld\n",ftell(fp));

    fseek(fp,0,SEEK_END);
    
    fputs("hello world\n",fp);
    printf("after fputs offset=%ld\n",ftell(fp));

    fclose(fp);
    return 0;
}

int main(int argc, char** argv){
    create_file();
    read_file();
    return 0;
}
/*
long ftell(FILE* stream);
성공시 파일 포지션 반환 ---- 바이트 단위 임
실패시 -1 반환

int fseek(FILE* stream, long offset, int whence)
현재 파일 포지션을 변경함
성공시 파일 포지션 반환
실패시 -1반환
*/