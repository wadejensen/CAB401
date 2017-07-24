//
// Created by w on 24/07/17.
//

#include <stdio.h>
#include <stdlib.h>
#include <chrono>

#define N 500

int** A;
int** B;
int** C;

int main(int argc, char *argv[]) {

    A = (int**) malloc(sizeof(int*)*N);
    B = (int**) malloc(sizeof(int*)*N);
    C = (int**) malloc(sizeof(int*)*N);

    for (int i=0; i<N; i++) {
        A[i] = (int*)malloc(sizeof(int*)*N);
        B[i] = (int*)malloc(sizeof(int*)*N);
        C[i] = (int*)malloc(sizeof(int*)*N);
    }

    srand(0);

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            A[i][j] = rand();
            B[i][j] = rand();
        }
    }

    auto start = std::chrono::high_resolution_clock::now();

    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            C[i][j]=0;
            for (int k = 0; k<N; k++) {
               C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();

    FILE* fp = fopen("results.data","wb");
    fwrite(C, sizeof(int), N*N, fp);
    fclose(fp);

    for(int i=0; i<N;i++)
    {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }

    free(A);
    free(B);
    free(C);

    std::chrono::duration<double> diff = end - start;
    printf("Duration: %f seconds\n", diff.count());

}