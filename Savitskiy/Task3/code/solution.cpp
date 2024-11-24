#include "header.hpp"


std::tuple<size_t, size_t> Solve::FindElemenForZeroing(const std::vector<std::vector<double>>& matrix) noexcept {
    std::vector<double> colSums(matrix.size(), 0.0);
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.size(); ++j) {
            colSums[i] += matrix[j][i] * matrix[j][i];
        }
        colSums[i] -= matrix[i][i] * matrix[i][i];
    }
    size_t col = 0;
    double maxSum = colSums[0];
    for (size_t i = 1; i < colSums.size(); ++i) {
        if (colSums[i] > maxSum) {
            maxSum = colSums[i];
            col = i;
        }
    }
    size_t row = 0;
    double maxVal = 0.0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        if (std::abs(matrix[i][col]) > maxVal && i != col) {
            maxVal = std::abs(matrix[i][col]);
            row = i;
        }
    }
    return std::make_pair(row, col);
}


void Solve::MakeRotationMatrix(std::vector<std::vector<double>>& matrix, const size_t& row, const size_t& col, const double& phi) noexcept {
    for (size_t i = 0; i < matrix.size(); ++i) {
        matrix[i][i] = 1;
    }
    matrix[row][row] = std::cos(phi);
    matrix[col][col] = std::cos(phi);
    matrix[row][col] = -std::sin(phi);
    matrix[col][row] = std::sin(phi);
}


void Solve::Rotate(
    std::vector<std::vector<double>>& matrix, 
    const std::vector<std::vector<double>>& rotationMatrix, 
    const size_t& p, 
    const size_t& q
) noexcept {
    std::vector<std::vector<double>> res = matrix; 
    for (size_t j = 0; j < matrix.size(); ++j) {
        res[p][j] = rotationMatrix[p][p] * matrix[p][j] + rotationMatrix[q][p] * matrix[q][j];
        res[q][j] = rotationMatrix[p][q] * matrix[p][j] + rotationMatrix[q][q] * matrix[q][j];
    }
    matrix = res;
    for (size_t i = 0; i < matrix.size(); ++i) {
        matrix[i][p] = res[i][p] * rotationMatrix[p][p] + res[i][q] * rotationMatrix[q][p];
        matrix[i][q] = res[i][p] * rotationMatrix[p][q] + res[i][q] * rotationMatrix[q][q];
    }
}


void Solve::JacobianRotation(
    std::vector<std::vector<double>>& matrix,
    const double& eps,
    const size_t& iterCnt,
    size_t& iterations
) noexcept {
    size_t n = matrix.size();
    for (size_t i = 0; i < iterCnt; ++i) {
        ++iterations;
        if ((iterations + 1) / 100 * 100 == iterations + 1) {
            printf("iteration[%d]\n", (int)iterations + 1);
        }
        std::tuple<size_t, size_t> RC = FindElemenForZeroing(matrix);
        size_t row = std::get<0>(RC), col = std::get<1>(RC);
        double val = matrix[row][col];
        if (std::abs(val) < eps || row == col) {
            break;
        }
        std::vector<std::vector<double>> rotationMatrix(n, std::vector<double>(n, 0.0));
        double phi;
        if (std::abs(matrix[col][col] - matrix[row][row]) < eps) {
            phi = M_PI / 4;
        } else {
            phi = 0.5 * std::atan(-(2 * matrix[row][col]) / (matrix[row][row] - matrix[col][col]));
        }
        MakeRotationMatrix(rotationMatrix, row, col, phi);
        Rotate(matrix, rotationMatrix, row, col);
    }
}


std::tuple<double, double> Variation(const std::vector<std::vector<double>>& matrix, const std::vector<double>& lambdas) noexcept {
    double r1up = 0.0, r2up1 = 0.0, r2up2;
    for (size_t i = 0; i < matrix.size(); ++i) {
        r1up += lambdas[i] - matrix[i][i];
        r2up2 += lambdas[i] * lambdas[i];
        for (size_t j = 0; j < matrix.size(); ++j) {
            r2up1 += matrix[i][j] * matrix[j][i]; 
        }   
    }
    double norm = 0.0;
    for (const auto& row : matrix) {
        double tmp = 0.0;
        for (const auto& elem : row) {
            tmp += std::abs(elem);
        }
        norm = std::max(tmp, norm);
    }
    return std::make_tuple(std::abs(r1up) / norm, std::abs(std::sqrt(r2up1) - std::sqrt(r2up2)) / norm);
}
