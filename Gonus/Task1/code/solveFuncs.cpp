#include "header.hpp"


size_t Solve::Solver::FindMaxAbs(
    const std::vector<PairedMatrixRow>& matrix,
    const size_t& colNumber
) noexcept {
    size_t pos = 0;
    double maxAbs = 0.0;
    for (size_t i = colNumber; i < matrix.size(); ++i) {
        double elAbs = std::abs(matrix[i].MainRow[colNumber]);
        if (elAbs > maxAbs) {
            pos = i;
            maxAbs = elAbs;
        }
    }
    return pos;
}


void Solve::Solver::Eliminate(
    std::vector<PairedMatrixRow>& matrix,
    const size_t& index
) noexcept {
    for (size_t i = 0; i < index; ++i) {
        double multiplier = matrix[i].MainRow[index];
        matrix[i] -= matrix[index].Multiply(multiplier);
    }
    for (size_t i = index + 1; i < matrix.size(); ++i) {
        double multiplier = matrix[i].MainRow[index];
        matrix[i] -= matrix[index].Multiply(multiplier);
    }
}


bool Solve::Solver::Solve(
    std::vector<PairedMatrixRow>& matrix,
    const double& norm
) noexcept {
    for (size_t i = 0; i < matrix.size(); ++i) {
        size_t maxAbsPos = FindMaxAbs(matrix, i);
        if (std::abs(matrix[i].MainRow[maxAbsPos]) < norm * 10e-10) {
            return false;
        }
        double divider = matrix[maxAbsPos].MainRow[i];
        for (size_t i = 0; i < matrix[maxAbsPos].MainRow.size(); ++i) {
            matrix[maxAbsPos].MainRow[i] /= divider;
            matrix[maxAbsPos].PairedRow[i] /= divider;
        }
        std::swap(matrix[i], matrix[maxAbsPos]);
        Eliminate(matrix, i);
    }
    return true;
}


std::vector<std::vector<double>> Solve::Answer::GetAnswer(
    const std::vector<PairedMatrixRow>& pmr
) noexcept {
    std::vector<std::vector<double>> answer(pmr.size());
    for (size_t i = 0; i < pmr.size(); ++i) answer[i] = pmr[i].PairedRow;
    return answer;
}