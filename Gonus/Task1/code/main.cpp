#include "header.hpp"


#define TASK 12


int main(int argc, char* argv[]) {
    clock_t start, end;
	start = clock();
    if (argc > 5 || argc < 4) {
        std::cout << "Incorrect count of arguments\n";
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
            argv[0], TASK, -1.0, -1.0, -1.0, -1.0, 0, 0
        );
        return 0;
    }
    const std::string filenameIn(argc == 5 ? argv[4] : "");
    int n, r, s;
    bool stop = false;
    try {
        n = std::stoi(argv[1]);
        r = std::stoi(argv[2]);
        s = std::stoi(argv[3]);
        if (s == 0 && argc == 4) {
            stop = true;
        }
    } catch (std::exception const& e) {
        stop = true;
    }
    if (stop || n < r || s < 0 || s > 4 || r < 0 || n < 0) {
        std::cout << "Incorrect arguments\n";
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
            argv[0], TASK, -1.0, -1.0, -1.0, -1.0, (int)s, (int)n
        );
        return 0;
    }

    std::vector<std::vector<double>> matrix;
    if (!Matrix::BuildCheck(matrix, n, s, filenameIn)) {
        std::cout << "Incorrect matrix\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
            argv[0], TASK, -1.0, -1.0, secs, 0.0, (int)s, (int)n
        );
        return 0;
    }

    std::vector<PairedMatrixRow> pmatrix;
    for (size_t i = 0; i < matrix.size(); ++i) {
        pmatrix.push_back(PairedMatrixRow(matrix[i], i));
    }

    auto Norm = [](const std::vector<std::vector<double>>& matrix)->double{
        double maxSumAbs = 0.0;
        for (const auto& row : matrix) {
            double sumAbs = 0.0;
            for (double val : row) {
                sumAbs += std::abs(val);
            }
            if (sumAbs > maxSumAbs) maxSumAbs = sumAbs;
        }
        return maxSumAbs;
    };
    double norm = Norm(matrix);

    if (!Solve::Solver::Solve(pmatrix, norm)) {
        std::cout << "No solution\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
            argv[0], TASK, -1.0, -1.0, secs, 0.0, (int)s, (int)n
        );
        return 0;
    }

    const auto solution = Solve::Answer::GetAnswer(pmatrix);
    printf("Matrix:\n");
    for (size_t i = 0; i < (size_t)r; ++i) {
        for (size_t j = 0; j < (size_t)r; ++j) {
            printf("%10.3e ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("Solution:\n");
    for (size_t i = 0; i < (size_t)r; ++i) {
        for (size_t j = 0; j < (size_t)r; ++j) {
            printf("%10.3e ", solution[i][j]);
        }
        printf("\n");
    }

    clock_t startN = clock();
    auto r1r2 = answerDerivation(matrix, solution);
    double timeN = (double)(clock() - startN) / CLOCKS_PER_SEC;
    end = clock();
    double secs = (double)(end - start) / CLOCKS_PER_SEC;
    printf(
        "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
        argv[0], TASK, std::get<0>(r1r2), std::get<1>(r1r2), secs, timeN, (int)s, (int)n
    );
    return 0;


}