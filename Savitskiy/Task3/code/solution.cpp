#include "header.hpp"


std::tuple<size_t, size_t> Solve::FindElemenForZeroing(const std::vector<std::vector<double>>& matrix, const std::vector<double>& colSums) noexcept {
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


void Solve::Rotate(
    std::vector<std::vector<double>>& matrix, 
    const double& phi,
    const size_t& p, 
    const size_t& q
) noexcept {
    double rotpp = std::cos(phi),
        rotqq = std::cos(phi),
        rotpq = -std::sin(phi),
        rotqp = std::sin(phi);
    for (size_t j = 0; j < matrix.size(); ++j) {
        auto respj = matrix[p][j];
        auto resqj = matrix[q][j];
        matrix[p][j] = rotpp * respj + rotpq * resqj;
        matrix[q][j] = rotqp * respj + rotqq * resqj;
    }
    for (size_t i = 0; i < matrix.size(); ++i) {
        auto resip = matrix[i][p];
        auto resiq = matrix[i][q];
        matrix[i][p] = resip * rotpp + resiq * rotpq;
        matrix[i][q] = resip * rotqp + resiq * rotqq;
    }
}


void Solve::JacobianRotation(
    std::vector<std::vector<double>>& matrix,
    const double& eps,
    const size_t& iterCnt,
    size_t& iterations
) noexcept {
    std::vector<double> colSums(matrix.size(), 0.0);
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.size(); ++j) {
            colSums[i] += matrix[j][i] * matrix[j][i];
        }
        colSums[i] -= matrix[i][i] * matrix[i][i];
    }
    size_t n = matrix.size();
    for (size_t i = 0; i < iterCnt; ++i) {
        ++iterations;
        if ((iterations + 1) / 1000 * 1000 == iterations + 1) {
            printf("iteration[%d]\n", (int)iterations + 1);
        }
        std::tuple<size_t, size_t> RC = FindElemenForZeroing(matrix, colSums);
        size_t row = std::get<0>(RC), col = std::get<1>(RC);
        double val = matrix[row][col];
        if (std::abs(val) < eps || row == col) {
            break;
        }
        double phi;
        if (std::abs(matrix[col][col] - matrix[row][row]) < eps) {
            phi = M_PI / 4;
        } else {
            phi = 0.5 * std::atan(-(2 * matrix[row][col]) / (matrix[row][row] - matrix[col][col]));
        }
        Rotate(matrix, phi, row, col);
        colSums[row] = 0.0;
        colSums[col] = 0.0;
        for (size_t j = 0; j < n; ++j) {
            colSums[row] += matrix[j][row] * matrix[j][row];
            colSums[col] += matrix[j][col] * matrix[j][col];
        }
        colSums[row] -= matrix[row][row] * matrix[row][row];
        colSums[col] -= matrix[col][col] * matrix[col][col];
    }
}


std::tuple<double, double> Variation(const std::vector<std::vector<double>>& matrix, const std::vector<double>& lambdas) noexcept {
    double r1up = 0.0, r2up1 = 0.0, r2up2 = 0.0;
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
    if (norm < 1e-100) {
        return std::make_tuple(0.0, 0.0);
    }
    return std::make_tuple(std::abs(r1up) / norm, std::abs(std::sqrt(r2up1) - std::sqrt(r2up2)) / norm);
}
