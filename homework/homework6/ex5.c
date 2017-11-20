#include <stdio.h>
#include <limits.h>
#include <time.h>

#define SIZE SHRT_MAX

int main() {
    static int arr1[2048];
    double start = clock();
    for (int i = 0; i < SIZE * SIZE / 2048; ++i) {
        for (int j = 0; j < 2048; ++j) {
            arr1[j] = i * j;
        }
    }
    double end = clock();
    printf("No thrashing: %lfs\n", (end - start) / CLOCKS_PER_SEC );
    
    static int arr2[SIZE][SIZE];
    start = clock();
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            arr2[i][j] = i * j;
        }
    }
    end = clock();
    printf("Thrashing: %lfs\n", (end - start) / CLOCKS_PER_SEC );
    return 0;
}
