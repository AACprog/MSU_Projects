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
    const size_t& index,
    const size_t& p
) noexcept {
    size_t blockSize = matrix.size() / p + ((matrix.size() % p == 0) ? 0 : 1);
    auto blockEliminate = [&matrix, &index](size_t blockStart, size_t blockEnd) {
        for (size_t i = blockStart; i < blockEnd; ++i) {
            if (i == index) continue;
            double multiplier = matrix[i].MainRow[index];
            matrix[i] -= matrix[index].Multiply(multiplier);
        }
    };
    std::vector<std::thread> threads;
    for (size_t i = 0; i < p; ++i) {
        size_t blockStart = i * blockSize;
        size_t blockEnd = std::min(matrix.size(), blockStart + blockSize);
        threads.emplace_back(
            std::thread(
                blockEliminate,
                blockStart,
                blockEnd
            )
        );
    }
    for (auto& thread : threads) thread.join();
}


bool Solve::Solver::Solve(
    std::vector<PairedMatrixRow>& matrix,
    const double& norm,
    const size_t& p
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
        Eliminate(matrix, i, p);
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
