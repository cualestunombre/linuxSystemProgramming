#include <stdio.h>
#include <string.h>

int write_to_file(void){
        FILE* fp;
        fp = fopen("dummy","w");
        if (fp==NULL){
                perror("fopen error\n"); //표준에러 메세지 출력
                return -1;
        }
        fputs("hello world..",fp);

        return 0;
        
}

/*
fopen - FILE *fopen(const char* pathname, const char* mode)
반환값 : 
성공시 열린 파일 포인터 
실패시 NULL
*/

int read_from_file(void){
    FILE* fp;
    char buf[1024];
    fp=fopen("dummy","r");
    if (fp==NULL){
            perror("fopen error\n");
            return -1;
    }
    memset(buf,0,sizeof(buf));
    fgets(buf,sizeof(buf),fp);
    fclose(fp);
    printf("%s\n",buf);
    return 0;
}


int main(int argc, char** argv){
    write_to_file();
    read_from_file();
    return 0;
}