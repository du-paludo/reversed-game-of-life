#include <stdio.h>
#include <stdlib.h>

void imprimirMatriz(int** A, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m-1; j++) {
            printf("%d ", A[i][j]);
        }
        printf("%d\n", A[i][m-1]);
    }
}

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

    imprimirMatriz(matriz, n, m);

    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}