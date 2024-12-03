#include "header.h"


void swap(void *a, void *b, size_t size) {
    char temp[size];
    memcpy(temp, a, size);
    memcpy(a, b, size);
    memcpy(b, temp, size);
}

void createMatrixByFormula(double** matrix, int size, int s) {
    int i, j;
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            switch (s) {
                case 1: matrix[i][j] = (double)(size - ((i > j) ? i : j)); break;            
                case 2: matrix[i][j] = (double)((i > j) ? i : j) + 1; break;        
                case 3: matrix[i][j] = fabs((double)(i - j)); break;        
                case 4: matrix[i][j] = 1 / (double)(i + j + 1); break;            
            }
        }
    }
}

void readMatrix(double** matrix, const char* filename, int size) {
    int i, j;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return;
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (fscanf(file, "%lf", &matrix[i][j]) != 1) {
                fprintf(stderr, "Error reading matrix values.\n");
                return;
            }
        }
    }
    fclose(file);
}


void freeMatrix(double** matrix, int rows) {
    int i;
    for (i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


double normMatrix(double** matrix, int size) {
    int i, j;
    double sum = 0;
    double maxSum = 0;
    for (i = 0; i < size; i++) {
        sum = 0;
        for (j = 0; j < size; j++) {
            sum += fabs(matrix[i][j]);
        }
        if (sum > maxSum) {
            maxSum = sum;
        }
    }
    return maxSum;
}


void makeBCol(double** matrix, double* b, int size) {
    int i, j;
    
    for (i = 0; i < size; ++i) {
        b[i] = 0;
        for (j = 0; j < (size + 1) / 2 && j < size / 2; ++j) {
            b[i] += matrix[i][2 * j];
        }
    }
}