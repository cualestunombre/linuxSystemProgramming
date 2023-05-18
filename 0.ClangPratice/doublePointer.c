#include <stdio.h>
#include <stdlib.h>

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", (*(matrix+i)+j));
        }
        printf("\n");
    }
}

void fillMatrix(int* matrix[], int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = i * cols + j;
        }
    }
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int rows = 3;
    int cols = 4;
   

    // 이중 포인터로 이차원 배열 생성
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }

    // 이차원 배열 초기화
    fillMatrix(matrix, rows, cols);

    // 이차원 배열 출력
    printMatrix(matrix, rows, cols);

    // 이차원 배열 메모리 해제
    freeMatrix(matrix, rows);

    return 0;
}