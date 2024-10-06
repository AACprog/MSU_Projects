#include "header.hpp"


double MatrixBuild::HelpFuncs::f1(const size_t& i, const size_t& j, const size_t& n) noexcept {
    return double(n) - double((i > j) ? i + 1 : j + 1) + 1;
}

double MatrixBuild::HelpFuncs::f2(const size_t& i, const size_t& j) noexcept {
    return double((i > j) ? i + 1 : j + 1); 
}

double MatrixBuild::HelpFuncs::f3(const size_t& i, const size_t& j) noexcept {
    return double((i > j) ? (i - j) : (j - i));
}

double MatrixBuild::HelpFuncs::f4(const size_t& i, const size_t& j) noexcept {
    return 1 / double(i + j + 1);
}


bool MatrixBuild::Build::matrixMake(
    std::vector<std::vector<double>>& matrix, 
    const size_t& s,
    const size_t& n,
    const std::string& filename
) noexcept {
    if (s == 0) {
        FileWork::matrixRead(matrix, filename);
        return FileWork::Checker::checkMatrix(matrix, n);
    }
    matrix.resize((size_t)n, std::vector<double>((size_t)n));
    for (size_t i = 0; i < (size_t)n; ++i) {
        for (size_t j = 0; j < (size_t)n; ++j) {
            switch (s) {
                case 1: matrix[i][j] = HelpFuncs::f1(i, j, (size_t)n); break;
                case 2: matrix[i][j] = HelpFuncs::f2(i, j); break;
                case 3: matrix[i][j] = HelpFuncs::f3(i, j); break;
                case 4: matrix[i][j] = HelpFuncs::f4(i, j); break;
            }
        }
    }
    return true;
}
