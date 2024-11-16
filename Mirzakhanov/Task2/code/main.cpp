#include "header.hpp"


#define TASK 17


int main(int argc, char* argv[]) {
    clock_t start, end;
	start = clock();
    if (argc > 6 || argc < 5) {
        std::cout << "Incorrect count of arguments\n";
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P = %d\n",
            argv[0], TASK, -1.0, -1.0, -1.0, -1.0, 0, 0, 0
        );
        return 0;
    }
    const std::string filenameIn(argc == 5 ? argv[4] : "");
    int n, p, r, s;
    bool stop = false;
    try {
        n = std::stoi(argv[1]);
        p = std::stoi(argv[2]);
        r = std::stoi(argv[3]);
        s = std::stoi(argv[4]);
        if (s == 0 && argc == 5) {
            stop = true;
        }
    } catch (std::exception const& e) {
        stop = true;
    }
    if (stop || n < r || s < 0 || s > 4 || r < 0 || n < 0 || p < 1) {
        std::cout << "Incorrect arguments\n";
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P = %d\n",
            argv[0], TASK, -1.0, -1.0, -1.0, -1.0, s, n, p
        );
        return 0;
    }

    std::vector<std::vector<double>> matrix;
    if (!Matrix::BuildCheck(matrix, n, s, filenameIn)) {
        std::cout << "Incorrect matrix\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P = %d\n",
            argv[0], TASK, -1.0, -1.0, secs, 0.0, s, n, p
        );
        return 0;
    }

    double MatrixNorm = Matrix::MatrixNorm(matrix);
    std::vector<LinearEquation> system;
    for (const auto& row : matrix) system.push_back(LinearEquation(row));
    if (!SolveFuncs::Solve::Solve(system, MatrixNorm, (size_t)p)) {
        std::cout << "No solution\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P = %d\n",
            argv[0], TASK, -1.0, -1.0, secs, 0.0, s, n, p
        );
        return 0;
    }
    auto solution = SolveFuncs::Answer::GetAnswer(system, MatrixNorm);
    printf("Matrix:\n");
    for (size_t i = 0; i < (size_t)r; ++i) {
        for (size_t j = 0; j < (size_t)r; ++j) {
            printf("%10.3e ", matrix[i][j]);
        }
        if ((size_t)r == matrix.size()) {
            printf("| %10.3e ", matrix[i][matrix.size()]);
        }
        printf("\n");
    }
    printf("Solution:\n");
    for (size_t i = 0; i < (size_t)r; ++i) {
        printf("x%zu %10.3e\n", i+1, solution[i]);
    }

    clock_t startN = clock();
    auto r1r2 = answerVariation(matrix, solution);
    double timeN = (double)(clock() - startN) / CLOCKS_PER_SEC;
    end = clock();
    double secs = (double)(end - start) / CLOCKS_PER_SEC;
    printf(
        "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P = %d\n",
        argv[0], TASK, std::get<0>(r1r2), std::get<1>(r1r2), secs, timeN, s, n, p
    );
}