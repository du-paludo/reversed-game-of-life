#include "helper.h"

const int row_offset[8] = {-1, -1, -1,  0,  0,  1,  1,  1}; // UPPER_LEFT, UPPER, UPPER_RIGHT, LEFT, RIGHT, LOWER_LEFT, LOWER, LOWER_RIGHT
const int col_offset[8] = {-1,  0,  1, -1,  1, -1,  0,  1};

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

void generateLoneliness(FILE* file, int n, int m, int i, int j) {
    int totalSubsets = 1 << 8;
    for (int bitmask = 0; bitmask < totalSubsets; bitmask++) {
        // Count the number of set bits in the bitmask
        int count = 0;
        int temp = bitmask;
        while (temp > 0) {
            count += temp & 1;
            temp >>= 1;
        }

        if (count == 7) {
            fprintf(file, "%d ", n*m+1);
            for (int k = 0; k < 8; k++) {
                if (bitmask & (1 << k)) {
                    int varIdx = (i + row_offset[k]) * m + (j + col_offset[k]) + 1;
                    fprintf(file, "%d ", varIdx);
                    // fprintf(file, "+1x%d ", varIdx);
                }
            }
            fprintf(file, "0\n");
            // fprintf(file, ">= 1;\n");
        }
    }
}

void generateStagnation(FILE* file, int n, int m, int i, int j) {
    int totalSubsets = 1 << 8;
    for (int bitmask = 0; bitmask < totalSubsets; bitmask++) {
        // Count the number of set bits in the bitmask
        int count = 0;
        int temp = bitmask;
        while (temp > 0) {
            count += temp & 1;
            temp >>= 1;
        }

        if (count == 2) {
            fprintf(file, "%d ", n*m+1);
            fprintf(file, "%d ", i * m + j + 1);
            // fprintf(file, "1x%d ", i * m + j + 1);
            for (int k = 0; k < 8; k++) {
                int varIdx = (i + row_offset[k]) * m + (j + col_offset[k]) + 1;
                if (bitmask & (1 << k)) {
                    // fprintf(file, "-1x%d ", varIdx);
                    fprintf(file, "-%d ", varIdx);
                } else {
                    fprintf(file, "%d ", varIdx);
                    // fprintf(file, "+1x%d ", varIdx);
                }
            }
            fprintf(file, "0\n");
            // fprintf(file, ">= 1;\n");
        }
    }
}

void generateOvercrowding(FILE* file, int n, int m, int i, int j) {
    int totalSubsets = 1 << 8;
    for (int bitmask = 0; bitmask < totalSubsets; bitmask++) {
        // Count the number of set bits in the bitmask
        int count = 0;
        int temp = bitmask;
        while (temp > 0) {
            count += temp & 1;
            temp >>= 1;
        }

        if (count == 4) {
            fprintf(file, "%d ", n*m+1);
            for (int k = 0; k < 8; k++) {
                if (bitmask & (1 << k)) {
                    int varIdx = (i + row_offset[k]) * m + (j + col_offset[k]) + 1;
                    fprintf(file, "-%d ", varIdx);
                    // fprintf(file, "-1x%d ", varIdx);
                }
            }
            fprintf(file, "0\n");
            // fprintf(file, ">= 1;\n");
        }
    }
}

void generatePreservation(FILE* file, int n, int m, int i, int j) {
    int totalSubsets = 1 << 8;
    for (int bitmask = 0; bitmask < totalSubsets; bitmask++) {
        // Count the number of set bits in the bitmask
        int count = 0;
        int temp = bitmask;
        while (temp > 0) {
            count += temp & 1;
            temp >>= 1;
        }

        if (count == 2) {
            fprintf(file, "%d ", n*m+1);
            fprintf(file, "-%d ", i * m + j + 1);
            // fprintf(file, "-1x%d ", i * m + j + 1);
            for (int k = 0; k < 8; k++) {
                int varIdx = (i + row_offset[k]) * m + (j + col_offset[k]) + 1;
                if (bitmask & (1 << k)) {
                    fprintf(file, "-%d ", varIdx);
                    // fprintf(file, "-1x%d ", varIdx);
                } else {
                    fprintf(file, "%d ", varIdx);
                    // fprintf(file, "+1x%d ", varIdx);
                }
            }
            fprintf(file, "0\n");
            // fprintf(file, ">= 1;\n");
        }
    }
}

void generateLife(FILE* file, int n, int m, int i, int j) {
    int totalSubsets = 1 << 8;
    for (int bitmask = 0; bitmask < totalSubsets; bitmask++) {
        // Count the number of set bits in the bitmask
        int count = 0;
        int temp = bitmask;
        while (temp > 0) {
            count += temp & 1;
            temp >>= 1;
        }

        if (count == 3) {
            fprintf(file, "%d ", n*m+1);
            // fprintf(file, "+1x%d ", i * m + j + 1);
            for (int k = 0; k < 8; k++) {
                int varIdx = (i + row_offset[k]) * m + (j + col_offset[k]) + 1;
                if (bitmask & (1 << k)) {
                    fprintf(file, "-%d ", varIdx);
                    // fprintf(file, "-1x%d ", varIdx);
                } else {
                    fprintf(file, "%d ", varIdx);
                    // fprintf(file, "+1x%d ", varIdx);
                }
            }
            fprintf(file, "0\n");
            // fprintf(file, ">= 1;\n");
        }
    }
}

void generateBorders(FILE* file, int n, int m) {
    // Top row (i = 0)
    for (int j = 0; j < m; j++) {
        int varIdx = 0 * m + j + 1;
        // fprintf(file, "-%d 0\n", varIdx); // Force cell to be dead
        fprintf(file, "%d -%d 0\n", n*m+1, varIdx);
        // fprintf(file, "1x%d >= 1;\n", varIdx);
    }

    // Bottom row (i = n-1)
    for (int j = 0; j < m; j++) {
        int varIdx = (n - 1) * m + j + 1;
        // fprintf(file, "-%d 0\n", varIdx); // Force cell to be dead
        fprintf(file, "%d -%d 0\n", n*m+1, varIdx);
        // fprintf(file, "1x%d >= 1;\n", varIdx);
    }

    // Left column (j = 0)
    for (int i = 1; i < n-1; i++) {
        int varIdx = i * m + 0 + 1;
        // fprintf(file, "-%d 0\n", varIdx); // Force cell to be dead
        fprintf(file, "%d -%d 0\n", n*m+1, varIdx);
        // fprintf(file, "1x%d >= 1;\n", varIdx);
    }

    // Right column (j = m-1)
    for (int i = 1; i < n-1; i++) {
        int varIdx = i * m + (m - 1) + 1;
        // fprintf(file, "-%d 0\n", varIdx); // Force cell to be dead
        fprintf(file, "%d -%d 0\n", n*m+1, varIdx);
        // fprintf(file, "˜x%d >= 1;\n", varIdx);
    }
}

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

void generateSAT(FILE* file, int** A, int n, int m) {
    int varNumber = n * m;

    int clauseCount = varNumber + 2*(n+m-2);
    // int clauseCount = 0;
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-1; j++) {
            if (A[i][j]) {
                clauseCount += nCr(8, 7) + nCr(8, 2) + nCr(8, 4);
            } else {
                if (verifyAllNeighborsZero(A, n, m, i, j)) {
                    clauseCount += 1;
                } else {
                    clauseCount += nCr(8, 2) + nCr(8, 3);
                }
            }
        }
    }

    fprintf(file, "p wcnf %d %d %d\n", varNumber, clauseCount, varNumber+1); // WCNF format

    // Generate soft clauses
    for (int i = 1; i <= varNumber; i++) {
        fprintf(file, "1 -%d 0\n", i);
    }

    generateBorders(file, n, m);

    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < m-1; j++) {

            if (A[i][j]) {
                // printf("Generating loneliness, stagnation and overcrowding for cell (%d, %d)\n", i, j);
                generateLoneliness(file, n, m, i, j);
                generateStagnation(file, n, m, i, j);
                generateOvercrowding(file, n, m, i, j);
            } else {
                int teste = 1;
                for (int k = 0; k < 8; k++) {
                    if (A[i + row_offset[k]][j + col_offset[k]]) {
                        teste = 0;
                        break;
                    }
                }
                // if (teste) {
                if (verifyAllNeighborsZero(A, n, m, i, j)) {
                    fprintf(file, "%d ", n*m+1);
                    fprintf(file, "-%d 0\n", i * m + j + 1);
                } else {
                    generatePreservation(file, n, m, i, j);
                    generateLife(file, n, m, i, j);
                }
            }
        }
    }
}

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

// 3 3
// 0 0 0
// 0 1 0
// 0 0 0