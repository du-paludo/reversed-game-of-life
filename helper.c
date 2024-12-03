#include "helper.h"

const int row_offset[8] = {-1, -1, -1,  0,  0,  1,  1,  1}; // UPPER_LEFT, UPPER, UPPER_RIGHT, LEFT, RIGHT, LOWER_LEFT, LOWER, LOWER_RIGHT
const int col_offset[8] = {-1,  0,  1, -1,  1, -1,  0,  1};

// Print array ignoring the first and last rows and columns
void printArrayWithoutBorders(int** A, int n, int m) {
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-2; j++) {
            printf("%d ", A[i][j]);
        }
        printf("%d\n", A[i][m-2]);
    }
}

void printArray(int** A, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m-1; j++) {
            printf("%d ", A[i][j]);
        }
        printf("%d\n", A[i][m-1]);
    }
}

// Calculates the binomial coefficient nCr using the logarithmic formula
int nCr(int n, int r) {
    // If r is greater than n, return 0
    if (r > n) return 0;
    // If r is 0 or equal to n, return 1
    if (r == 0 || n == r) return 1;
    // Initialize the logarithmic sum to 0
    double res = 0;
    // Calculate the logarithmic sum of the numerator and denominator using loop
    for (int i = 0; i < r; i++) {
        // Add the logarithm of (n-i) and subtract the logarithm of (i+1)
        res += log(n-i) - log(i+1);
    }
    // Convert logarithmic sum back to a normal number
    return (int)round(exp(res));
}

// Verifies if all neighbors and their neighbors are zero
int verifyAllNeighborsZero(int** A, int n, int m, int x, int y) {
    // Iterate over the cell's 8 neighbors
    for (int i = 0; i < 8; i++) {
        int nx = x + row_offset[i];
        int ny = y + col_offset[i];

        // Skip out-of-bounds neighbors
        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;

        // Check if the neighbor is non-zero
        if (A[nx][ny] != 0) {
            return 0; // Not all neighbors are zero
        }

        // Check the neighbors of the neighbor (second-level neighbors)
        for (int j = 0; j < 8; j++) {
            int nnx = nx + row_offset[j];
            int nny = ny + col_offset[j];

            // Skip out-of-bounds second-level neighbors
            if (nnx < 0 || nny < 0 || nnx >= n || nny >= m) continue;

            // Check if the second-level neighbor is non-zero
            if (A[nnx][nny] != 0) {
                return 0; // Not all second-level neighbors are zero
            }
        }
    }

    return 1; // All neighbors and their neighbors are zero
}

// Extends the array by adding a border of zeros around it
int** extendArray(int** A, int n, int m) {
    int newN = n + 2;
    int newM = m + 2;

    int** newArray = malloc(sizeof(int*) * newN);
    for (int i = 0; i < newN; i++) {
        newArray[i] = malloc(sizeof(int) * newM);
    }

    for (int i = 0; i < newN; i++) {
        for (int j = 0; j < newM; j++) {
            if (i == 0 || i == newN-1 || j == 0 || j == newM-1) {
                newArray[i][j] = 0;
            } else {
                newArray[i][j] = A[i-1][j-1];
            }
        }
    }

    return newArray;
}