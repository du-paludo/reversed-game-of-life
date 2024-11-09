#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include <time.h>

#define RANDOM 1

int main() {
    int n, m;
    fscanf(stdin, "%d %d", &n, &m);

    int** arr = malloc(sizeof(int*) * n);
    for (int i = 0; i < m; i++) {
        arr[i] = malloc(sizeof(int) * m);
    }

    srand(time(NULL));

    if (RANDOM) {
        for (int j = 0; j < m; j++) {
            arr[0][j] = rand() % 2;
            arr[n-1][j] = rand() % 2;
        }
        for (int i = 1; i < n-1; i++) {
            arr[i][0] = rand() % 2;
            arr[i][m-1] = rand() % 2;
        }
        for (int i = 1; i < n-1; i++) {
            for (int j = 1; j < m-1; j++) {
                arr[i][j] = rand() % 2;
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fscanf(stdin, "%d", &arr[i][j]);
            }
        }
    }

    int** extendedArray = extendArray(arr, n, m);

    printf("\n");

    FILE* inputFile = fopen("SATinput.txt", "w"); 
    if (inputFile == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(0);
    }
    
    generateSAT(inputFile, extendedArray, n+2, m+2);

    fclose(inputFile);

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}