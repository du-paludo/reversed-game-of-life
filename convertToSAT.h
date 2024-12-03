#ifndef CONVERT_TO_SAT_H
#define CONVERT_TO_SAT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void generateLoneliness(FILE* file, int n, int m, int i, int j);

void generateStagnation(FILE* file, int n, int m, int i, int j);

void generateOvercrowding(FILE* file, int n, int m, int i, int j);

void generatePreservation(FILE* file, int n, int m, int i, int j);

void generateLife(FILE* file, int n, int m, int i, int j);

void generateSAT(FILE* file, int** A, int n, int m);

#endif