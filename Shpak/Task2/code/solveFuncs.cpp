#include "header.hpp"


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


void eliminate(LE* matrix, int index, int numberOfThreads) {
    int i;
    int blockSize = matrix[0].size / numberOfThreads + ((matrix[0].size % numberOfThreads == 0) ? 0 : 1);
    int tmp;
    auto blockElimination = [&matrix](int index, int blockStart, int blockEnd) {
        for (int i = blockStart; i < blockEnd; ++i) {
            if (i == (int)index) continue;
            double multiplier = matrix[i].VariableCoefficients[index];
            Substract(matrix + i, matrix + index, multiplier);
        }
    };
    std::vector<std::thread> threads;
    for (i = 0; i < matrix[0].size; i += blockSize) {
        tmp = std::min(i + blockSize, matrix[0].size);
        threads.emplace_back(
            std::thread(
                blockElimination, index, i, tmp
            )
        );
    }
    for (auto& t : threads) t.join();
}


int solve(LE* matrix,  double norm, int numberOfThreads) {
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
        eliminate(matrix, i, numberOfThreads);
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