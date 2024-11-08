#include <stdlib.h>
#include <stdio.h>

void printArray(int** A, int n, int m) {
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-2; j++) {
            printf("%d ", A[i][j]);
        }
        printf("%d\n", A[i][m-2]);
    }
}

void convertSATtoArray(FILE* file, int** A, int n, int m) {
    char* line = malloc(sizeof(char) * 10);
    int val;
    fgets(line, 4, file);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            fscanf(file, "%d ", &val);
            if (val < 0) {
                A[i][j] = 0;
            } else {
                A[i][j] = 1;
            }
        }
    }
    free(line);
}

int main(int argc, char* argv[]) {
    int n = atoi(argv[1]) + 2;
    int m = atoi(argv[2]) + 2;
    // fscanf(stdin, "%d %d\n", &n, &m);

    int **arr = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(sizeof(int) * m);
    }

    FILE* outputFile = fopen("SAToutput.txt", "r");
    if (outputFile == NULL) {
        fprintf(stderr, "Failed to read file SAToutput.txt\n");
    } else {
        convertSATtoArray(outputFile, arr, n, m);
        printArray(arr, n, m);
        fclose(outputFile);
    }

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}