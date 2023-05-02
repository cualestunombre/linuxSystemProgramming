#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct person{
        char name[20];
        int age;
};

static int write_to_file(void){
        FILE* fp=NULL;
        struct person kim = {
                .name="kim",
                .age=30
        };
        struct person woo = {
                .name="woo",
                .age=26
        };
        if(!(fp=fopen("persons","w"))){
            perror("fopen failed");
            return -1;
        }
        if (fwrite(&kim,sizeof(struct person),1,fp)!=1){
            goto err;
        }
        if (fwrite(&woo,sizeof(struct person),1,fp)!=1){
            goto err;
        }
        fclose(fp);
        return 0;
err:
    if(fp){
        fclose(fp);
        perror("error occured");
    }
}
static int read_from_file(void){
        FILE* fp=NULL;
        struct person  persons[2];
         if(!(fp=fopen("persons","r"))){
                return -1;
        }
        if (fread(persons, sizeof(struct person),2,fp)!=2){
                goto err;
        }
        printf("%s %d %s %d",
        persons[0].name,persons[0].age,persons[1].name,persons[1].age);
        
        
        fclose(fp);
        return 0;
err:
        if(fp){
                fclose(fp);
        }
        perror("error occured");
}

int main(int agrc, char** argv){
    write_to_file();
    read_from_file();
    return 0;
}


/*
밑에 두개 모두 바이트 스트림임(바이트 단위로 쓰고 읽는 다는 뜻) -- 텍스트 데이터가 아니라 바이너리
size_t fwrite(const void* ptr, size_t size, size_t nmemb, FILE* stream);
size_t fread(const void* ptr, size_t size, size_t nmemb, FILE* stream);

*/