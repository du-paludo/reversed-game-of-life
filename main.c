#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include <time.h>

#define RANDOM 1

int main() {
    int n, m, c;
    fscanf(stdin, "%d %d\n", &n, &m);

    int** matriz = malloc(sizeof(int*) * n);
    for (int i = 0; i < m; i++) {
        matriz[i] = malloc(sizeof(int) * m);
    }

    srand(time(NULL));

    if (RANDOM) {
        for (int j = 0; j < m; j++) {
            matriz[0][j] = rand() % 2;
            matriz[n-1][j] = rand() % 2;
        }
        for (int i = 1; i < n-1; i++) {
            matriz[i][0] = rand() % 2;
            matriz[i][m-1] = rand() % 2;
        }
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                fscanf(stdin, "%d", &c);
                matriz[i][j] = c;
            }
        }
    }

    int** extendedArray = extendArray(matriz, n, m);

    printf("\n");
    imprimirMatriz(extendedArray, n+2, m+2);

    FILE* inputFile = fopen("SATinput.txt", "w"); 
    if (inputFile == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(0);
    }
    
    generateSAT(inputFile, extendedArray, n+2, m+2);

    fclose(inputFile);

    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}