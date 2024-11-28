#include <stdio.h>
#include <stdlib.h>
#include "helper.h"
#include "convertFromSAT.h"
#include <time.h>

#define RANDOM 1

int** allocateSubarray(int rows, int cols) {
    int** subarray = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        subarray[i] = (int*)malloc(cols * sizeof(int));
    }
    return subarray;
}

// Function to divide the array into 4 overlapping parts
void divideArray(int** A, int n, int m, int*** sub1, int*** sub2, int*** sub3, int*** sub4) {
    int midRow = n / 2;
    int midCol = m / 2;

    // Allocate memory for each subarray with overlap
    *sub1 = allocateSubarray(midRow + 1, midCol + 1); // Top-left
    *sub2 = allocateSubarray(midRow + 1, m - midCol + 1); // Top-right
    *sub3 = allocateSubarray(n - midRow + 1, midCol + 1); // Bottom-left
    *sub4 = allocateSubarray(n - midRow + 1, m - midCol + 1); // Bottom-right

    // Fill subarray 1 (Top-left)
    for (int i = 0; i <= midRow; i++) {
        for (int j = 0; j <= midCol; j++) {
            (*sub1)[i][j] = A[i][j];
        }
    }

    // Fill subarray 2 (Top-right)
    for (int i = 0; i <= midRow; i++) {
        for (int j = midCol; j < m; j++) {
            (*sub2)[i][j - midCol] = A[i][j];
        }
    }

    // Fill subarray 3 (Bottom-left)
    for (int i = midRow; i < n; i++) {
        for (int j = 0; j <= midCol; j++) {
            (*sub3)[i - midRow][j] = A[i][j];
        }
    }

    // Fill subarray 4 (Bottom-right)
    for (int i = midRow; i < n; i++) {
        for (int j = midCol; j < m; j++) {
            (*sub4)[i - midRow][j - midCol] = A[i][j];
        }
    }
}

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
            arr[0][j] = 0;
            arr[n-1][j] = 0;
        }
        for (int i = 1; i < n-1; i++) {
            arr[i][0] = 0;
            arr[i][m-1] = 0;
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

    n += 2;
    m += 2;

    // printArray(arr, n, m);
    printArray(extendedArray, n, m);

    // printf("\n");

    FILE* topLeftFile = fopen("SATinputTL.txt", "w"); 
    FILE* topRightFile = fopen("SATinputTR.txt", "w");
    FILE* bottomLeftFile = fopen("SATinputBL.txt", "w");
    FILE* bottomRightFile = fopen("SATinputBR.txt", "w");
    
    printf("Generating SAT input file...\n");

    // n = 10
    // m = 10

    int **topLeftArray, **topRightArray, **bottomLeftArray, **bottomRightArray;

    divideArray(extendedArray, n, m, &topLeftArray, &topRightArray, &bottomLeftArray, &bottomRightArray);

    // Print the subarrays
    printf("Subarray 1:\n");
    printArray(topLeftArray, n / 2 + 1, m / 2 + 1);

    printf("Subarray 2:\n");
    printArray(topRightArray, n / 2 + 1, m - m / 2 + 1);

    printf("Subarray 3:\n");
    printArray(bottomLeftArray, n - n / 2 + 1, m / 2 + 1);

    printf("Subarray 4:\n");
    printArray(bottomRightArray, n - n / 2 + 1, m - m / 2 + 1);

    // topleft n = 0-5, m = 0-5
    // topright n = 0-5, m = 5-9
    // bottomleft n = 5-9, m = 0-5
    // bottomright n = 5-9, m = 5-9

    generateSAT(topLeftFile, topLeftArray, n/2 + 1, m/2 + 1, n, m);
    generateSAT(topRightFile, topRightArray, n/2 + 1, m - m/2 + 1, n, m);
    generateSAT(bottomLeftFile, bottomLeftArray, n - n/2 + 1, m/2 + 1, n, m);
    generateSAT(bottomRightFile, bottomRightArray, n - n/2 + 1, m - m/2 + 1, n, m);

    fclose(topLeftFile);
    fclose(topRightFile);
    fclose(bottomLeftFile);
    fclose(bottomRightFile);

    printf("Solving SAT problem...\n");

    system("./open-wbo/open-wbo SATinputTL.txt > SAToutputTL.txt");
    system("./open-wbo/open-wbo SATinputTR.txt > SAToutputTR.txt");
    system("./open-wbo/open-wbo SATinputBL.txt > SAToutputBL.txt");
    system("./open-wbo/open-wbo SATinputBR.txt > SAToutputBR.txt");

    printf("Reading output files...\n");

    readAndCombineOutputs(n, m);

    return 0;
}

// 4 6
// 0 0 0 0 0 0
// 0 0 1 1 0 0
// 0 0 0 1 0 0
// 0 0 0 1 0 0