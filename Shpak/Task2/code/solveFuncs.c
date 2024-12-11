#include "header.h"
#define min(a, b) (a < b) ? a : b




int findMaxAbs(LE* matrix, int colNumber) {
    int size = matrix[0].size;
    double maxAbs = 0;
    double elAbs;
    int pos = 0, i;
    for (i = colNumber; i < size; ++i) {
        elAbs = fabs(matrix[i].VariableCoefficients[colNumber]);
        if (elAbs > maxAbs) {
            maxAbs = elAbs;
            pos = i;
        }
    }
    return pos;
}



void* blockElimination(void* args) {
    ArgsForThread* realArgs = (ArgsForThread*)args;
    int i;
    int index = (*realArgs).index;
    double multiplier;
    for (i = (*realArgs).blockStart; i < (*realArgs).blockEnd && i < (*realArgs).systemPtr[0].size; ++i) {
        if (i == index) continue;
        multiplier = (*realArgs).systemPtr[i].VariableCoefficients[index];
        Substract((*realArgs).systemPtr + i, (*realArgs).systemPtr + index, multiplier);
    }

    freeArgs(args);
    return NULL;
}




void eliminate(LE* matrix, int index, int p) {
    int blockSize = matrix[0].size / p + ((matrix[0].size % p == 0) ? 0 : 1);
    int i, cnt;
    p = min(p, matrix[0].size);
    pthread_t *threads = (pthread_t*)malloc(sizeof(pthread_t) * p);
    cnt = 0;
    for (i = 0; i < matrix[0].size; i += blockSize) {
        pthread_create(threads + cnt, NULL, blockElimination, makeArgs(matrix, index, i, min((i + blockSize), matrix[0].size)));
        ++cnt;
    }
    for (i = 0; i < cnt; ++i) {
        pthread_join(threads[i], NULL);
    }
    free(threads);
}


int solve(LE* matrix,  double norm, int p) {
    int i, maxAbsPos, j;
    double divider;
    for (i = 0; i < matrix[0].size; ++i) {
        maxAbsPos = findMaxAbs(matrix, i);
        if (fabs(matrix[maxAbsPos].VariableCoefficients[i]) < norm * 1e-16) {
            return 1;
        }
        divider = matrix[maxAbsPos].VariableCoefficients[i];
        for (j = 0; j < matrix[0].size; ++j) {
            matrix[maxAbsPos].VariableCoefficients[j] /= divider;
        }
        matrix[maxAbsPos].FreeCoefficient /= divider;
        swap((void*)(matrix + i), (void*)(matrix + maxAbsPos), sizeof(LE));
        eliminate(matrix, i, p);
    }
    return 0;
}


void variation(double** matrix, double* answer, double* b, int answerSize, double* r1, double* r2) {
    int i, j;
    double tmp;
    double bnorm = 0, xnorm = 0;
    (*r1) = 0;
    (*r2) = 0;
    for (i = 0; i < answerSize; ++i) {
        xnorm += (double)((i + 1) % 2);
        bnorm += fabs(b[i]);
        (*r2) += fabs(answer[i] - (double)((i + 1) % 2));
        tmp = 0;
        for (j = 0; j < answerSize; ++j) {
            tmp += matrix[i][j] * answer[j]; 
        }
        (*r1) += fabs(tmp - b[i]);
    }
    (*r1) /= bnorm;
    (*r2) /= xnorm;
}