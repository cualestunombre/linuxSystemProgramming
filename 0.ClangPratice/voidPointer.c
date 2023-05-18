#include <stdio.h>

void foo(int num) {
    printf("foo: %d\n", num);
}

void bar(float num) {
    printf("bar: %f\n", num);
}

int toe(int num){
    return num;
}
int main() {
    // 함수 포인터 선언
    void* (*funcPtr)(void*);

    // foo 함수 포인터를 void 포인터로 전달
    funcPtr = (void (*)(void*))foo; 

    // void 포인터를 다시 foo 함수 포인터로 형변환하여 실행
    ((void (*)(int))funcPtr)(42);

    // bar 함수 포인터를 void 포인터로 전달
    funcPtr = (void (*)(void*))bar;

    // void 포인터를 다시 bar 함수 포인터로 형변환하여 실행
    ((void (*)(float))funcPtr)(3.14);

    funcPtr = (void* (*)(void *))toe;
    int ret = ((int (*)(int))funcPtr)(5);
    printf("%d",ret);

    return 0;
}

//결론: 매개 변수 부분을 void포인터로 받아서 나중에 캐스팅함에 따라 다양한 매개변수 타입을 받을 수 있다