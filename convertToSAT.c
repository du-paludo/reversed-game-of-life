#include "convertToSAT.h"
#include "helper.h"

extern const int row_offset[8], col_offset[8];

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
                }
            }
            fprintf(file, "0\n");
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
            for (int k = 0; k < 8; k++) {
                int varIdx = (i + row_offset[k]) * m + (j + col_offset[k]) + 1;
                if (bitmask & (1 << k)) {
                    fprintf(file, "-%d ", varIdx);
                } else {
                    fprintf(file, "%d ", varIdx);
                }
            }
            fprintf(file, "0\n");
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
                }
            }
            fprintf(file, "0\n");
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
            for (int k = 0; k < 8; k++) {
                int varIdx = (i + row_offset[k]) * m + (j + col_offset[k]) + 1;
                if (bitmask & (1 << k)) {
                    fprintf(file, "-%d ", varIdx);
                } else {
                    fprintf(file, "%d ", varIdx);
                }
            }
            fprintf(file, "0\n");
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
            for (int k = 0; k < 8; k++) {
                int varIdx = (i + row_offset[k]) * m + (j + col_offset[k]) + 1;
                if (bitmask & (1 << k)) {
                    fprintf(file, "-%d ", varIdx);
                } else {
                    fprintf(file, "%d ", varIdx);
                }
            }
            fprintf(file, "0\n");
        }
    }
}

void generateBorders(FILE* file, int n, int m) {
    // Top row (i = 0)
    for (int j = 0; j < m; j++) {
        int varIdx = 0 * m + j + 1;
        fprintf(file, "%d -%d 0\n", n*m+1, varIdx);
    }

    // Bottom row (i = n-1)
    for (int j = 0; j < m; j++) {
        int varIdx = (n - 1) * m + j + 1;
        fprintf(file, "%d -%d 0\n", n*m+1, varIdx);
    }

    // Left column (j = 0)
    for (int i = 1; i < n-1; i++) {
        int varIdx = i * m + 0 + 1;
        fprintf(file, "%d -%d 0\n", n*m+1, varIdx);
    }

    // Right column (j = m-1)
    for (int i = 1; i < n-1; i++) {
        int varIdx = i * m + (m - 1) + 1;
        fprintf(file, "%d -%d 0\n", n*m+1, varIdx);
    }
}

void generateSAT(FILE* file, int** A, int n, int m) {
    int varNumber = n * m;

    int clauseCount = varNumber + 2*(n+m-2);
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
                generateLoneliness(file, n, m, i, j);
                generateStagnation(file, n, m, i, j);
                generateOvercrowding(file, n, m, i, j);
            } else {
                // int teste = 1;
                // for (int k = 0; k < 8; k++) {
                //     if (A[i + row_offset[k]][j + col_offset[k]]) {
                //         teste = 0;
                //         break;
                //     }
                // }
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