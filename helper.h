#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void printArray(int** A, int n, int m);

int nCr(int n, int r);

void generateLoneliness(FILE* file, int n, int m, int i, int j);

void generateStagnation(FILE* file, int n, int m, int i, int j);

void generateOvercrowding(FILE* file, int n, int m, int i, int j);

void generatePreservation(FILE* file, int n, int m, int i, int j);

void generateLife(FILE* file, int n, int m, int i, int j);

void generateSAT(FILE* file, int** A, int n, int m);

int** extendArray(int** A, int n, int m);

#endif