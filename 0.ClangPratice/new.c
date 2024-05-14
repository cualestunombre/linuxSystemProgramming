#include <stdio.h>
#include <stdlib.h>

int* returnArray(){
    int* ptr = (int *) malloc(100);
    ptr[0] = 5;
    ptr[1] = 2;
    return ptr;
    
}

int main(void){
    while(1){
        int *ptr = returnArray();
        free(ptr);
    }

}