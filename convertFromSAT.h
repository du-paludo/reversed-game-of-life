#ifndef CONVERT_FROM_SAT_H
#define CONVERT_FROM_SAT_H

void printExtendedArray(int** A, int n, int m);

int convertSATtoArray(FILE* file, int** A, int n, int m);

void readOutputFile(int n, int m);

void printArray2(int** A, int n, int m);

void combineSubarrays(int** A, int** sub1, int** sub2, int** sub3, int** sub4, int n, int m);

void readAndCombineOutputs(int n, int m);

#endif