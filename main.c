#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

int main() {
    int n, m, c;
    fscanf(stdin, "%d %d\n", &n, &m);

    int** matriz = malloc(sizeof(int*) * n);
    for (int i = 0; i < m; i++) {
        matriz[i] = malloc(sizeof(int) * m);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(stdin, "%d", &c);
            matriz[i][j] = c;
        }
    }

    // imprimirMatriz(matriz, n, m);

    FILE* inputFile = fopen("SATinput.txt", "w"); 
    if (inputFile == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(0);
    }
    
    // generateSAT(inputFile, matriz, n, m);

    FILE* outputFile = fopen("SAToutput.txt", "r");
    if (outputFile == NULL) {
        fprintf(stderr, "Failed to read file SAToutput.txt\n");
    } else {
        convertSATtoArray(outputFile, matriz, n, m);
        imprimirMatriz(matriz, n, m);
        fclose(outputFile);
    }

    fclose(inputFile);

    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}