#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printArrayWithoutBorders(int** A, int n, int m);

void printArray(int** A, int n, int m);

int nCr(int n, int r);

int verifyAllNeighborsZero(int** A, int n, int m, int x, int y);

int** extendArray(int** A, int n, int m);

#endif