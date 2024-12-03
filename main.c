#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "helper.h"
#include "convertFromSAT.h"
#include "convertToSAT.h"

int main(int argc, char* argv[]) {
    int random = 0;
    int n, m;
    fscanf(stdin, "%d %d", &n, &m);

    if (argc > 1) {
        if (strcmp(argv[1], "random") == 0) {
            random = 1;
        }
    }

    int** arr = malloc(sizeof(int*) * n);
    for (int i = 0; i < m; i++) {
        arr[i] = malloc(sizeof(int) * m);
    }

    srand(time(NULL));

    if (random) {
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

    if (random) {
        printArrayWithoutBorders(extendedArray, n, m);
    }

    FILE* inputFile = fopen("SATinput.txt", "w"); 
    if (inputFile == NULL) {
        fprintf(stderr, "Failed to open file\n");
        exit(0);
    }
    
    // printf("Generating SAT input file...\n");

    generateSAT(inputFile, extendedArray, n, m);
    fclose(inputFile);

    // printf("Solving SAT problem...\n");

    system("./open-wbo/open-wbo SATinput.txt > SAToutput.txt");
    readOutputFile(n, m);

    for (int i = 0; i < n-2; i++) {
        free(arr[i]);
    }
    free(arr);

    for (int i = 0; i < n; i++) {
        free(extendedArray[i]);
    }
    free(extendedArray);

    return 0;
}