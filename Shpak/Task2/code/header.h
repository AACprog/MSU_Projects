#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <pthread.h>

typedef struct {
    double* VariableCoefficients;
    double FreeCoefficient;
    int size;
} LE;


typedef struct {
    LE* systemPtr;
    int index;
    int blockStart;
    int blockEnd;
} ArgsForThread;


void* makeArgs(LE* system, int index, int blockStart, int blockEnd);
void freeArgs(ArgsForThread* args);

void MakeLE(LE* le, double* row, int size, int coeff);
void FreeLE(LE* le);
void Substract(LE* le, LE* other, double multiplier);

void swap(void *a, void *b, size_t size);


void createMatrixByFormula(double** matrix, int size, int s);
void readMatrix(double** matrix, const char* filename, int size);
void freeMatrix(double** matrix, int rows);
double normMatrix(double** matrix, int size);
void makeBCol(double** matrix, double* b, int size);

int findMaxAbs(LE* matrix, int colNumber);
void eliminate(LE* matrix, int index, int p);
void* blockElimination(void* args);

int solve(LE* matrix,  double norm, int p); 
void variation(double** matrix, double* answer, double* b, int answerSize, double* r1, double* r2);