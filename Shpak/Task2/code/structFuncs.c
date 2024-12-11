#include "header.h"


void MakeLE(LE* le, double* row, int size, int coeff) {
    (*le).FreeCoefficient = coeff;
    (*le).VariableCoefficients = (double*)malloc(sizeof(double) * size);
    (*le).size = size;
    memcpy((*le).VariableCoefficients, row, size * sizeof(double));
}


void FreeLE(LE* le) {
    free((*le).VariableCoefficients);
    (*le).VariableCoefficients = NULL;
    (*le).size = 0;
    (*le).FreeCoefficient = 0;
}


void Substract(LE* le, LE* other, double multiplier) {
    int i, size = (*le).size;
    for (i = 0; i < size; i++) {
        (*le).VariableCoefficients[i] -= multiplier * (*other).VariableCoefficients[i];
    }
    (*le).FreeCoefficient -= multiplier * (*other).FreeCoefficient;
}



void* makeArgs(LE* system, int index, int blockStart, int blockEnd) {
    ArgsForThread* args = (ArgsForThread*)malloc(sizeof(ArgsForThread));
    (*args).systemPtr = system;
    (*args).index = index;
    (*args).blockStart = blockStart;
    (*args).blockEnd = blockEnd;
    return (void*)args;
}


void freeArgs(ArgsForThread* args) {
    //free((*args).systemPtr);
    free(args);
}

