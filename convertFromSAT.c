#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "convertFromSAT.h"

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
    printf("Number of 1s: %d\n", count);
    return 1;
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
            printArray2(arr, n, m);
        }
        fclose(outputFile);
    }

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
}

// Function to print a 2D array
void printArray2(int** A, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }
}

// Function to combine the subarrays into the final array
void combineSubarrays(int** A, int** sub1, int** sub2, int** sub3, int** sub4, int n, int m) {
    int midRow = n / 2;
    int midCol = m / 2;

    // Combine subarray 1 (Top-left)
    for (int i = 0; i <= midRow; i++) {
        for (int j = 0; j <= midCol; j++) {
            A[i][j] = sub1[i][j];
        }
    }

    // Combine subarray 2 (Top-right)
    for (int i = 0; i <= midRow; i++) {
        for (int j = 1; j <= m - midCol; j++) {
            A[i][midCol + j - 1] = sub2[i][j];
        }
    }

    // Combine subarray 3 (Bottom-left)
    for (int i = 1; i <= n - midRow; i++) {
        for (int j = 0; j <= midCol; j++) {
            A[midRow + i - 1][j] = sub3[i][j];
        }
    }

    // Combine subarray 4 (Bottom-right)
    for (int i = 1; i <= n - midRow; i++) {
        for (int j = 1; j <= m - midCol; j++) {
            A[midRow + i - 1][midCol + j - 1] = sub4[i][j];
        }
    }
}

// Function to read and combine SAT outputs
void readAndCombineOutputs(int n, int m) {
    // Allocate the final array
    int **finalArray = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        finalArray[i] = malloc(sizeof(int) * m);
    }

    // Allocate subarrays
    int midRow = n / 2 + 1, midCol = m / 2 + 1;
    int **sub1 = malloc(sizeof(int*) * midRow);
    int **sub2 = malloc(sizeof(int*) * midRow);
    int **sub3 = malloc(sizeof(int*) * midRow);
    int **sub4 = malloc(sizeof(int*) * midRow);
    for (int i = 0; i < midRow; i++) {
        sub1[i] = malloc(sizeof(int) * midCol);
        sub2[i] = malloc(sizeof(int) * midCol);
        sub3[i] = malloc(sizeof(int) * midCol);
        sub4[i] = malloc(sizeof(int) * midCol);
    }

    // Read SAT outputs for each subarray
    FILE* fileTL = fopen("SAToutputTL.txt", "r");
    FILE* fileTR = fopen("SAToutputTR.txt", "r");
    FILE* fileBL = fopen("SAToutputBL.txt", "r");
    FILE* fileBR = fopen("SAToutputBR.txt", "r");

    printf("%d %d\n", midRow, midCol);

    if (fileTL) convertSATtoArray(fileTL, sub1, midRow, midCol);
    if (fileTR) convertSATtoArray(fileTR, sub2, midRow, midCol);
    if (fileBL) convertSATtoArray(fileBL, sub3, midRow, midCol);
    if (fileBR) convertSATtoArray(fileBR, sub4, midRow, midCol);

    fclose(fileTL);
    fclose(fileTR);
    fclose(fileBL);
    fclose(fileBR);

    // Combine subarrays
    combineSubarrays(finalArray, sub1, sub2, sub3, sub4, n, m);

    // Print the combined result
    printf("Final Combined Array:\n");
    printArray2(finalArray, n, m);

    // Free memory
    for (int i = 0; i < midRow; i++) {
        free(sub1[i]);
        free(sub2[i]);
        free(sub3[i]);
        free(sub4[i]);
    }
    free(sub1);
    free(sub2);
    free(sub3);
    free(sub4);

    for (int i = 0; i < n; i++) {
        free(finalArray[i]);
    }
    free(finalArray);
}