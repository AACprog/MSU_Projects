#include "header.hpp"
#define TASK 10


int main(int argc, char* argv[]) {
    clock_t start = clock(), end;
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
    std::vector<std::thread> threads(p);


    if (!SolveFuncs::Solver::Solve(system, Matrix::MatrixNorm(matrix), p)) {
        std::cout << "No solution\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P =%d\n", 
            argv[0], TASK, -1.0, -1.0, secs, 0.0, s, n, p
        );
        return 0;
    }

    std::vector<double> solution((size_t)n, 0);
    SolveFuncs::Solution::GetAnswer(system, solution);
    for (size_t i = 0; i < (size_t)r; ++i) {
        printf("x%zu = %10.3e\n", i+1, solution[i]);
    }
    std::cout << "\nMatrix of system of linear equations:\n";
    for (size_t i = 0; i < (size_t)r; ++i) {
        for (size_t j = 0; j < (size_t)r ; ++j) {
            printf("%10.3e ", matrix[i][j]);
            if ((size_t)r == j+1) {
                printf("| %10.3e\n", matrix[i][matrix.size()]);
            }
        }
    }

    clock_t startN = clock();
    const auto r1r2 = Variation::GetVariation(matrix, solution, p);
    clock_t endN = clock();
    end = clock();
    double secs = (double)(end - start) / CLOCKS_PER_SEC;
    double secsN = (double)(endN - startN) / CLOCKS_PER_SEC;
    printf(
        "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d P = %d\n",
        argv[0], TASK, std::get<0>(r1r2), std::get<1>(r1r2), secs, secsN, s, n, p
    );
    return 0;

}


