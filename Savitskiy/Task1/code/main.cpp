#include "header.hpp"
#include <ctime>
#define TASK 10

int main(int argc, char* argv[]) {
	clock_t start, end;
	start = clock();
    if (argc > 5 || argc < 4) {
        std::cout << "Incorrect count of arguments\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
                "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
                argv[0],
                TASK,
                -1.0,
                -1.0,
                secs,
                0.0,
                0,
                0
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

    if (stop) {
        std::cout << "Incorrect arguments\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
                "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
                argv[0],
                TASK,
                -1.0,
                -1.0,
                secs,
                0.0,
                (int)s,
                (int)n
            );
        return 0;
    }
    if (n < r || s < 0 || s > 4 || r < 0 || n < 0) {
        std::cout << "Incorrect data\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
                "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
                argv[0],
                TASK,
                -1.0,
                -1.0,
                secs,
                0.0,
                (int)s,
                (int)n
            );
        return 0;
    }
    std::vector<std::vector<double>> matrix;

    if (argc == 5) {
        FileWork::matrixRead(matrix, filenameIn);
    } else {
        auto f1 = [](const size_t& i, const size_t& j, const size_t& n)->double{ return double(n) - double((i > j) ? i + 1 : j + 1) + 1; };
        auto f2 = [](const size_t& i, const size_t& j)->double{ return double((i > j) ? i + 1 : j + 1); };
        auto f3 = [](const size_t& i, const size_t& j)->double{ return double((i > j) ? (i - j) : (j - i)); };
        auto f4 = [](const size_t& i, const size_t& j)->double{ return 1 / double(i + j + 1); };
        matrix.resize(n, std::vector<double>(n + 1));
        for (size_t i = 0; i < (size_t)n; ++i) {
            for (size_t j = 0; j < (size_t)n; ++j) {
                switch (s) {
                    case 1: matrix[i][j] = f1(i, j, n); break;
                    case 2: matrix[i][j] = f2(i, j); break;
                    case 3: matrix[i][j] = f3(i, j); break;
                    case 4: matrix[i][j] = f4(i, j); break;
                }
            }
            matrix[i][n] = 0;
            for (size_t k = 0; k < ((size_t)n + 1) / 2; ++k) {
            	matrix[i][n] += matrix[i][2 * k + 1];
            }
        }
    }
    
    if (s == 0 && !FileWork::Checker::checkMatrix(matrix, n)) {
        std::cout << "Incorrect matrix\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
                "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
                argv[0],
                TASK,
                -1.0,
                -1.0,
                secs,
                0.0,
                (int)s,
                (int)n
            );
        return 0;
    }
    if (s == 0) {
        for (size_t i = 0; i < (size_t)n; ++i) {
            matrix[i].push_back(0);
            for (size_t k = 0; k < ((size_t)n + 1) / 2; ++k) {
                matrix[i][n] += matrix[i][2 * k + 1];
            }
        }
    }
    std::vector<LinearEquation> system;
    for (const auto& i : matrix) {
        system.push_back(LinearEquation(i));
    }
    if (!SolveFuncs::Solver::Solve(system)) {
        std::cout << "No solution\n";
        end = clock();
    	double secs = (double)(end - start) / CLOCKS_PER_SEC;
        printf(
                "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
                argv[0],
                TASK,
                -1.0,
                -1.0,
                secs,
                0.0,
                (int)s,
                (int)n
            );
        return 0;
    }

    std::vector<double> solution((size_t)n, 0);
    for (size_t i = 0; i < system.size(); ++i) {
        solution[system[i].Variables[i].index] = system[i].FreeCoefficient;
    }
    for (size_t i = 0; i < (size_t)n; ++i) {
        printf("x%zu = %10.3e\n", i+1, solution[i]);
    }
    std::cout << "\nMatrix of system of linear equations:\n";
    for (size_t i = 0; i < (size_t)r; ++i) {
        for (size_t j = 0; j < (size_t)r ; ++j) {
            printf("%10.3e ", matrix[i][j]);
        }
        if ((size_t)r == matrix.size()) {
            printf("| %10.3e\n", matrix[i][matrix.size() - 1]);
        } else {
            printf("\n");
        }
    }




    end = clock();
    double secs = (double)(end - start) / CLOCKS_PER_SEC;
    std::tuple<double, double, double> r1r2time = answerVariation(matrix, system, solution);
    printf(
            "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
            argv[0],
            TASK,
            std::get<0>(r1r2time),
            std::get<1>(r1r2time),
            secs,
            std::get<2>(r1r2time),
            (int)s,
            (int)n
        );
    return 0;
}
