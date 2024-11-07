#include "header.hpp"

#define TASK 9


int main(int argc, char* argv[]) {
    clock_t start = clock(), end;
    int n, r, s;
    bool stop = false;
    const auto incorrectArgs = [&](void){
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
            argv[0], TASK, -1.0, -1.0, -1.0, -1.0, 0, 0
        );
    };
    const std::string filenameIn(argc == 5 ? argv[4] : "");
    if (argc != 4 && argc != 5) {
        incorrectArgs();
        return 0;
    }
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
    if (stop || n < 1 || n < r || s < 0 || s > 4) {
        incorrectArgs();
        return 0;
    }
    
    std::vector<std::vector<double>> matrix;
    if (!Matrix::BuildCheck(matrix, n, s, filenameIn)) {
        std::cout << "Incorrect matrix\n";
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
            argv[0], TASK,  -1.0, -1.0, -1.0, -1.0, s, n
        );
        return 0;
    }
    double norm = 0.0;
    for (const auto& i : matrix) {
        double absSum = 0.0;
        for (size_t j = 0; j < (size_t)n - 1; ++j) {
            absSum += std::abs(i[j]);
        }
        norm = std::max(absSum, norm);
    }
    std::vector<LinearEquation> system;
    for (const auto& i : matrix) {
        system.push_back(LinearEquation(i));
    }
    if (!Solve::Solver::Solve(system, norm)) {
        std::cout << "No solution\n";
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
            argv[0], TASK,  -1.0, -1.0, -1.0, -1.0, s, n
        );
        return 0;
    }
    std::vector<double> answer(matrix.size(), 0.0);
    Solve::Answer::GetAnswer(system, answer, norm);
    for (size_t i = 0; i < (size_t)r; ++i) {
        printf("x%zu = %10.3e\n", i+1, answer[i]);
    }
    std::cout << "\nMatrix of system of linear equations:\n";
    for (size_t i = 0; i < (size_t)r; ++i) {
        for (size_t j = 0; j < (size_t)r ; ++j) {
            printf("%10.3e ", matrix[i][j]);
            if (j + 1 == (size_t)n) {
                printf("| %10.3e", matrix[i][matrix.size()]);
            }
	    }
        printf("\n");
    }
    clock_t startN = clock();
    auto r1r2 = answerVariation(matrix, system,  answer);
    double timeN = (double)(clock() - startN) / CLOCKS_PER_SEC;
    end = clock();
    double secs = (double)(end - start) / CLOCKS_PER_SEC;
    printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
            argv[0], TASK, std::get<0>(r1r2), std::get<1>(r1r2), secs, timeN, (int)s, (int)n
        );
    return 0;

}