#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
int dirCount=0;
#define TYPE2STR(x) \
    ((x) == DT_BLK ? "block device" : \
    (x) == DT_CHR ? "character device" : \
    (x) == DT_DIR ? "directory" : \
    (x) == DT_FIFO ? "named pipe" : \
    (x) == DT_LNK ? "symbolic link" : \
    (x) == DT_REG ? "regular file" : \
    (x) == DT_SOCK ? "socket file" : \
    "unknown")

typedef struct {
    int depth;
    long capacity;
    int fileCnt;
    char* path;
} Node;

typedef struct {
    long capacity;
    int fileCnt; // 디렉토리 제외
} Dts; // Data Transfer Struct

typedef struct {
    Node* array;
    int current;
} ResultSet;

int openDir(const char* path, DIR** dp) {
    *dp = opendir(path);
    if (*dp == NULL) {
        perror("Failed to open the directory");
        return -1;
      
    }
    return 0;
}

Dts* dfsTraverse(Node* node, ResultSet* resultSet) {
    dirCount+=1;
    int ret;
    DIR* dp;
    Dts* sendDts = malloc(sizeof(Dts));
    Dts* getDts;

    struct dirent* dir;

    node->capacity = 0L;
    node->fileCnt = 0;

    ret = openDir(node->path, &dp);
    if(ret==-1){
        sendDts->capacity = node->capacity;
        sendDts->fileCnt = node->fileCnt;
        return sendDts; 
    }
    while ((dir = readdir(dp)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        char* type = TYPE2STR(dir->d_type);
        if (strcmp("directory", type) == 0) {
            Node* newNode = malloc(sizeof(Node));
            newNode->depth = node->depth + 1;
            newNode->path = malloc(strlen(node->path) + strlen(dir->d_name) + 2);
            strcpy(newNode->path, node->path);
            if (strcmp(node->path, "/") != 0)
                strcat(newNode->path, "/");
            strcat(newNode->path, dir->d_name);
            getDts = dfsTraverse(newNode, resultSet);
            node->capacity += getDts->capacity;
            node->fileCnt += getDts->fileCnt;
            free(newNode->path);
            free(newNode);
            free(getDts);
        } else {
            char* path = malloc(strlen(node->path) + strlen(dir->d_name) + 2);
            strcpy(path, node->path);
            strcat(path, "/");
            strcat(path, dir->d_name);

            struct stat statbuf;
            ret = lstat(path, &statbuf);
            if (ret == 0) {
                node->fileCnt += 1;
                node->capacity += (long)(statbuf.st_size);
            }

            free(path);
        }
    }
    closedir(dp);

    printf("디렉토리명: %s 파일크기: %ld 파일수: %d 깊이: %d\n", node->path, node->capacity, node->fileCnt, node->depth);
    sendDts->capacity = node->capacity;
    sendDts->fileCnt = node->fileCnt;
    return sendDts;
}





int main(int argc,char** argv){
    Node nodes[100000];
    ResultSet resultSet;
    int ret;
    resultSet.array=nodes;
    resultSet.current=0;

    Node node;
    node.depth=0;
    node.path="/";

    dfsTraverse(&node,&resultSet);
    printf("디렉토리 개수: %d",dirCount);

    

}