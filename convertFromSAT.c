#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void printExtendedArray(int** A, int n, int m) {
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-2; j++) {
            printf("%d ", A[i][j]);
        }
        printf("%d\n", A[i][m-2]);
    }
}

int convertSATtoArray(FILE* file, int** A, int n, int m) {
    char line[10000];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        // Check if the line is "s UNSATISFIABLE"
        if (strncmp(line, "s UNSATISFIABLE", 15) == 0) {
            printf("The problem is UNSATISFIABLE.\n");
            return 0;
        }
        // Check if the line starts with 'v'
        if (line[0] == 'v' && line[1] == ' ') {
            char *token = strtok(line + 2, " "); // Skip the "v "
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (!token) {
                        fprintf(stderr, "Error: Not enough values for the array.\n");
                        fclose(file);
                        return 0;
                    }
                    if (atoi(token) < 0) {
                        A[i][j] = 0;
                    } else {
                        A[i][j] = 1;
                        count++;
                    }
                    token = strtok(NULL, " ");
                }
            }
            break;
        }
    }
    return 1;
    // printf("Number of 1s: %d\n", count);
}

void readOutputFile(int n, int m) {
    n += 2;
    m += 2;

    int **arr = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(sizeof(int) * m);
    }

    FILE* outputFile = fopen("SAToutput.txt", "r");
    if (outputFile == NULL) {
        fprintf(stderr, "Failed to read file SAToutput.txt\n");
    } else {
        if (convertSATtoArray(outputFile, arr, n, m)) {
            printExtendedArray(arr, n, m);
        }
        fclose(outputFile);
    }

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}