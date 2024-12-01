#include "header.hpp"
#define ITERATION_COUNT 1e6

int main(int argc, char* argv[]) {
    const auto incorrectArgs = [&argv](){
        printf (
            "%s : Residual1 = %e Residual2 = %e Iterations = %d Iterations1 = %d Elapsed1 = %.2f Elapsed2 = %.2f\n",
            argv[0], -1.0, -1.0, 0, 0, -1.0, -1.0
        );
    };
    clock_t start1 = clock(), start2;
    size_t iters = 0;
    int n, m, k;
    double eps;
    const std::string filename = (argc == 6) ? argv[5] : "";
    if (argc > 6 || argc < 5 || (argc == 6 && filename.empty())) {
        incorrectArgs();
        return 0;
    }
    try {
	    n = std::stoi(argv[1]);
        m = std::stoi(argv[2]);
        eps = std::stod(argv[3]);
        k = std::stoi(argv[4]);
    } catch (std::exception const& e) {
        return 0;
    }
    if (n <= 0 || m <= 0 || eps < 0 || k < 0 || k > 4 || n < m) {
        incorrectArgs();
        return 0;
    }
    std::vector<std::vector<double>> matrix;
    if (!Matrix::BuildCheck(matrix, n, k, filename)) {
        incorrectArgs();
        return 0;
    }
    auto matrixCopy = matrix;
    Solve::JacobianRotation(matrixCopy, eps, ITERATION_COUNT, iters);
    std::vector<double> lambdas(n);
    for (size_t i = 0; i < (size_t)n; ++i) {
        lambdas[i] = matrixCopy[i][i];
    }
    clock_t end1 = clock();
    start2 = clock();
    auto r1r2 = Variation(matrix, lambdas);
    clock_t end2 = clock();
    std::cout << "Matrix:\n";
    for (size_t i = 0; i < (size_t)m; ++i) {
        for (size_t j = 0; j < (size_t)m; ++j) {
            printf("%10.3e ", matrix[i][j]);
        }
	    printf("\n");
    }
    std::cout << "Reworked matrix:\n";
    for (size_t i = 0; i < (size_t)m; ++i) {
        for (size_t j = 0; j < (size_t)m; ++j) {
            printf("%10.3e ", matrixCopy[i][j]);
        }
	    printf("\n");
    }
    std::cout << "Eigenvalues:\n";
    for (size_t i = 0; i < (size_t)m; ++i) {
        printf("l%zu =%10.3e\n", i + 1, lambdas[i]);
    }
    printf (
        "%s : Residual1 = %e Residual2 = %e Iterations = %d Iterations1 = %d Elapsed1 = %.2f Elapsed2 = %.2f\n",
        argv[0], std::get<0>(r1r2), std::get<1>(r1r2), (int)iters, (int)iters / n, 
        (double)(end1 - start1) / CLOCKS_PER_SEC, (double)(end2 - start2) / CLOCKS_PER_SEC
    );
    return 0;
}
