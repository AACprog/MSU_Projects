#include "header.hpp"

#define TASK 9

int main(int argc, char* argv[]) {
    int n, r, s, p;
    int i, j;
    double** matrix;
    double* b;
    double* answer;
    double norm;
    clock_t start1, end1, start2, end2;
    double t1, t2;
    start1 = clock();
    LE* system;
    double r1, r2;
    const char* filename = ((argc == 5) ? argv[4] : ""); 
    double n1 = 0, n2 = 0, n3 = 0;
    if (argc < 4 || argc > 5) {
        fprintf(stderr, "Usage: %s <n> <r> <s> <input_file>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    p = atoi(argv[2]);
    r = atoi(argv[3]);
    s = atoi(argv[4]);
    if (n < 0 || n < r || s < 0 || s > 4 || p < 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    matrix = (double**)malloc(sizeof(double*) * n);
    for (i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(sizeof(double) * n);
    }

    if (s == 0) {
        readMatrix(matrix, filename, n);
    } else {
        createMatrixByFormula(matrix, n, s);
    }
    if (!matrix) {
        fprintf(stderr, "Failed to read matrix\n");
        return 1;
    }
    b = (double*)malloc(sizeof(double) * n);
    makeBCol(matrix, b, n);
    printf("Matrix of linear equation:\n");
    for (i = 0; i < r; ++i) {
        for (j = 0; j < r; ++j) {
            printf("%10.3e ", matrix[i][j]);
        }
        if (r == n) {
            printf("| %10.3e\n", b[i]);
        } else {
            printf("\n");
        }
    }

    system = (LE*)malloc(sizeof(LE) * n);
    for (i = 0; i < n; ++i) {
        MakeLE(system + i, matrix[i], n, b[i]);
    }
    norm = normMatrix(matrix, n);
    if (solve(system, norm, p) != 0) {
        
        printf("System has linear equations which are lineary dependent\n");
        free(b);
        freeMatrix(matrix, n);
        for (i = 0; i < n; ++i) {
            FreeLE(system + i);
        }
        free(system);
        return 0;
    } else {
        printf("Matrix of linear equation:\n");
        for (i = 0; i < r; ++i) {
            for (j = 0; j < r; ++j) {
                printf("%10.3e ", matrix[i][j]);
            }
            if (r == n) {
                printf("| %10.3e\n", b[i]);
            } else {
                printf("\n");
            }
        }
        printf("Solution:\n");
        answer = (double*)malloc(sizeof(double) * n);
        for (i = 0; i < n; ++i) {
            answer[i] = system[i].FreeCoefficient;
        }

        for (i = 0; i < r; ++i) {
            printf("x%d = %10.3e\n", i + 1, answer[i]);
        }
        start2 = clock();
        variation(matrix, answer, b, n, &r1, &r2);
        end2 = clock();
        for (i = 0; i < n; ++i) {
            n1 += fabs(answer[i]); 
            n2 += pow(answer[i], 2); 
            n3 = (n3 > fabs(answer[i])) ? n3 : fabs(answer[i]);
        }
        free(answer);
    }
    freeMatrix(matrix, n);
    for (i = 0; i < n; ++i) {
        FreeLE(system + i);
    }
    free(system);
    free(b);
    end1 = clock();
    t1 = (double)((end1 - start1) / CLOCKS_PER_SEC);
    t2 = (double)((end2 - start2) / CLOCKS_PER_SEC);
    printf(
        "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
        argv[0], TASK, r1, r2, t1, t2, s, n
    );
    printf("Norm1 = %lf Norm2 = %lf NormInf = %lf\n", n1, sqrt(n2), n3);
    return 0;
}