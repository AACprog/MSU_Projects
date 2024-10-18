#include "header.hpp"


std::tuple<size_t, size_t> Solve::SolveFuncs::FindMaxAbs(
    const std::vector<std::vector<double>>& matrix,
    const size_t& colNumber
) noexcept {
    double maxAbs = 0.0;
    size_t posi = 0, posj = 0;
    for (size_t i = colNumber; i < matrix.size(); ++i) {
        for (size_t j = colNumber; j < matrix.size(); ++j) {
            double elAbs = std::abs(matrix[i][j]);
            if (maxAbs < elAbs) {
                posi = i;
                posj = j;
                maxAbs = elAbs;
            }
        }
    }
    return std::make_tuple(posi, posj);
}


void Solve::SolveFuncs::Eliminate(
    std::vector<std::vector<double>>& matrix,
    const size_t& mainNumber,
    const size_t& toKillNumber
) noexcept {
    double multiplier = matrix[toKillNumber][mainNumber];
    for (size_t i = 0; i < matrix[toKillNumber].size(); ++i) {
        matrix[toKillNumber][i] -= multiplier * matrix[mainNumber][i];
    }
}


void Solve::SolveFuncs::EliminateUnder(
    std::vector<std::vector<double>>& matrix,
    const size_t& mainNumber
) noexcept {
    for (size_t i = mainNumber + 1; i < matrix.size(); ++i) {
        Eliminate(matrix, mainNumber, i);
    }
}


std::tuple<bool, std::vector<size_t>> Solve::SolveFuncs::Solve(
    std::vector<std::vector<double>>& matrix,
    const double& norm
) noexcept {
    std::vector<size_t> order(matrix.size());
    for (size_t i = 0; i < order.size(); ++i) {
        order[i] = i;
    }
    size_t mainNumber = 0;
    while (mainNumber < matrix.size()) {
        std::tuple<size_t, size_t> pos = FindMaxAbs(matrix, mainNumber);
        size_t posj = std::get<0>(pos);
        size_t posi = std::get<1>(pos);
        double divider = matrix[posi][posj];
        if (std::abs(divider) < norm * 10e-10) {
            for (size_t i = 0; i < matrix.size(); ++i) {
                if (std::abs(matrix[i][matrix[i].size() - 1]) < norm * 10e-10) continue;
                for (size_t j = 0; j < matrix[i].size() - 1; ++j) {
                    if (std::abs(matrix[i][j]) > norm * 10e-10) break;
                }
                return std::make_tuple(false, order);
            }
            matrix.resize(mainNumber + 1);
            return std::make_tuple(true, order);
        }
        for (size_t j = 0; j < matrix[posi].size(); ++j) {
            matrix[posi][j] /= divider;
        }
        for (size_t i = 0; i < matrix.size(); ++i) {
            std::swap(matrix[i][mainNumber], matrix[i][posj]);
        }
        std::swap(matrix[mainNumber], matrix[posi]);
        std::swap(order[mainNumber], order[posj]);
        EliminateUnder(matrix, mainNumber);
        ++mainNumber;
    }
    return std::make_tuple(true, order);
}


std::vector<double> Solve::Answer::GetAnswer(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<size_t>& order
) noexcept {
    std::vector<double> tmp(order.size(), 0.0);
    for (size_t i = matrix.size() - 1;; --i) {
        tmp[i] = matrix[i][matrix[i].size() - 1];
        for (size_t j = matrix.size() - 1; j > i; --j) {
            tmp[i] -= matrix[i][j] * tmp[j];
        }
        if (i == 0) break;
    }
    std::vector<double> answer(order.size(), 0.0);
    for (size_t i = 0; i < order.size(); ++i) {
        answer[i] = tmp[order[i]];
    }
    return answer;
}