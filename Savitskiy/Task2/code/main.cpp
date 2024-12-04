#include "header.hpp"
#define TASK 10


int main(int argc, char* argv[]) {
    time_t start, end;
    time(&start);
    int n, p, r, s;
    bool stop = false;


    const auto incorrectArgs = [&](void){
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P = %d\n",
            argv[0], TASK, -1.0, -1.0, -1.0, -1.0, 0, 0, 0
        );
    };


    if (argc > 6 || argc < 5) {
        std::cout << "Incorrect count of arguments\n";
        incorrectArgs();
        return 0;
    }


    const std::string filenameIn(argc == 6 ? argv[5] : "");
    try {
        n = std::stoi(argv[1]);
        p = std::stoi(argv[2]);
        r = std::stoi(argv[3]);
        s = std::stoi(argv[4]);
        if (s == 0 && argc == 5) stop = true;
    } catch (std::exception const& e) {
        stop = true;
    }


    if (stop) {
        std::cout << "Incorrect arguments\n";
        incorrectArgs();
        return 0;
    }


    std::vector<std::vector<double>> matrix;
    if (!Matrix::BuildCheck(matrix, n, s, filenameIn)) {
        std::cout << "Incorrect matrix\n";
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P = %d\n",
            argv[0], TASK, -1.0, -1.0, -1.0, -1.0, n, s, p
        );
        return 0;
    }


    std::vector<LinearEquation> system;
    for (size_t i = 0; i < matrix.size(); ++i) system.push_back(LinearEquation(matrix[i]));

    auto norm = Matrix::MatrixNorm(matrix);
    if (!SolveFuncs::Solver::Solve(system, norm, p)) {
        std::cout << "No solution\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P =%d\n", 
            argv[0], TASK, -1.0, -1.0, secs, 0.0, s, n, p
        );
        return 0;
    }
    if (system.size() < matrix.size()) {
        std::cout << "Infinitely many solutions.\nPrticular solution:\n";
    }
    std::vector<double> solution((size_t)n, 0.0);
    SolveFuncs::Solution::GetAnswer(system, solution);
    for (size_t i = 0; i < (size_t)r; ++i) {
        printf("x%zu = %10.3e\n", i+1, solution[i]);
    }
    std::cout << "\nMatrix of system of linear equations:\n";
    for (size_t i = 0; i < (size_t)r; ++i) {
        for (size_t j = 0; j < (size_t)r ; ++j) {
            printf("%10.3e ", matrix[i][j]);
            if ((size_t)j == (size_t)(n - 1)) {
                printf("| %10.3e", matrix[i][matrix.size()]);
            }
        }
        printf("\n");
    }
    std::cout << "Order: {";
    for (size_t i = 0; i < (size_t)r; ++i) {
        std::cout << system[0].Variables[i].index << " ";
    }
    std::cout << "}\n";
    std::cout << "Finished matrix:\n";
    for (size_t i = 0; i < (size_t)r; ++i) {
        for (size_t j = 0; j < (size_t)r ; ++j) {
            if (system.size() < i + 1) {
                printf("%10.3e ", 0.0);
            } else {
                printf("%10.3e ", system[i].Variables[j].coefficient);
            }
        }
        if (r == n) {
            printf("| %10.3e\n", system[i].FreeCoefficient);
        } else {
            printf("\n");
        }
    }

    time_t startN, endN;
    time(&startN);
    const auto r1r2 = Variation::GetVariation(matrix, solution);
    time(&endN);
    time(&end);
    double secs = (double)(end - start);
    double secsN = (double)(endN - startN);
    printf(
        "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P = %d\n",
        argv[0], TASK, std::get<0>(r1r2), std::get<1>(r1r2), secs, secsN, s, n, p
    );
    return 0;

}
