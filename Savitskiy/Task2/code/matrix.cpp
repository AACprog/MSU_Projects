#include "header.hpp"


double Matrix::HelpFuncs::f1(const size_t& i, const size_t& j, const size_t& n) noexcept {
    return (double)(n - std::max(i, j));
}


double Matrix::HelpFuncs::f2(const size_t& i, const size_t& j) noexcept {
    return (double)(std::max(i, j) + 1);
}


double Matrix::HelpFuncs::f3(const size_t& i, const size_t& j) noexcept {
    return (double)(std::max(i, j) - std::min(i, j));
}


double Matrix::HelpFuncs::f4(const size_t& i, const size_t& j) noexcept {
    return 1.0 / (double)(i + j + 1);
}


void Matrix::Build::MatrixRead(std::vector<std::vector<double>>& matrix, const std::string& filename) noexcept {
    auto parse = [](const std::string& row)->std::vector<double> {
        std::vector<double> parsed;
        std::regex r(R"(-?\d+(\.\d+)?([eE]-?\d+(\.\d+)?)?)");
        auto rowBegin = std::sregex_iterator(row.begin(), row.end(), r);
        auto rowEnd = std::sregex_iterator();
        for (std::sregex_iterator i = rowBegin; i != rowEnd; i++) {
            std::smatch match = *i;
            std::string match_str = match.str();
            try {
                parsed.push_back(std::stod(match_str));
            } catch (std::exception const& e) {
                std::cout << "String is incorrect\n"; 
            }
        }
        return parsed;
    };

    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        matrix.push_back(parse(line));
    }
    file.close();
}

void Matrix::Build::BuildMatrix(std::vector<std::vector<double>>& matrix, const int& n, const int& s, const std::string& filename) noexcept {
    if (s == 0) {
        MatrixRead(matrix, filename);
        return;
    }
    size_t n1 = (size_t)n;
    matrix.resize(n);
    for (size_t i = 0; i < n1; ++i) {
        matrix[i].resize(n);
        for (size_t j = 0; j < n1; ++j) {
            switch (s) {
                case 1: matrix[i][j] = HelpFuncs::f1(i, j, n1); break;
                case 2: matrix[i][j] = HelpFuncs::f2(i, j); break;
                case 3: matrix[i][j] = HelpFuncs::f3(i, j); break;
                case 4: matrix[i][j] = HelpFuncs::f4(i, j); break;
            }
        }
    }
}


bool Matrix::Check::CheckMatrix(const std::vector<std::vector<double>>& matrix, const size_t& n) noexcept {
    if (matrix.size() != n) return false;
    for (size_t i = 0; i < n; ++i) {
        if (matrix[i].size() != n) return false;
    }
    return true;
}



bool Matrix::BuildCheck(std::vector<std::vector<double>>& matrix, const int& n, const int& s, const std::string& filename) noexcept {
    Build::BuildMatrix(matrix, n, s, filename);
    if (!Check::CheckMatrix(matrix, (size_t)n)) {
        return false;
    }
    BuildBCol(matrix);
    return true;
}


void Matrix::BuildBCol(std::vector<std::vector<double>>& matrix) noexcept {
    size_t n = matrix.size();
    for (size_t i = 0; i < n; ++i) {
        matrix[i].push_back(0.0);
        for (size_t k = 0; k < (n + 1) / 2; ++k) {
            matrix[i][n] += matrix[i][2 * k];
        }
    }
}


double Matrix::MatrixNorm(const std::vector<std::vector<double>>& matrix) noexcept {
    double maxSumAbs = 0.0;
    for (const auto& row : matrix) {
        double sumAbs = 0.0;
        for (double val : row) {
            sumAbs += std::abs(val);
        }
        sumAbs -= std::abs(row[row.size() - 1]);
        if (sumAbs > maxSumAbs) maxSumAbs = sumAbs;
    }
    return maxSumAbs;
}