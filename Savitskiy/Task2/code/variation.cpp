#include "header.hpp"


std::tuple<double, double> Variation::GetVariation(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<double>& solution,
    const int& p
) noexcept {
    std::vector<double> AxMinusB(matrix.size());
    auto substituteForRow = [&](const size_t& index){
        double out = 0.0;
        for (size_t i = 0; i < solution.size(); ++i) {
            out += solution[i] * matrix[index][i];
        }
        AxMinusB[index] = out - matrix[index][matrix[index].size() - 1];
    };
    for (size_t rowNumber = 0; rowNumber < matrix.size(); rowNumber = rowNumber + p) {
        std::vector<std::thread> th;
        for (size_t j = 0; j < (size_t)p && rowNumber + j < matrix.size(); ++j) {
            th.emplace_back(std::thread(substituteForRow, rowNumber + j));
        }
        for (auto& thr : th) thr.join();
    }
    std::vector<std::thread> lastThreading;
    for (size_t rowNumber = matrix.size() - (matrix.size() % (size_t)p) + 1; rowNumber < matrix.size(); ++rowNumber) {
        lastThreading.emplace_back(std::thread(substituteForRow, rowNumber));
    }
    for (auto& thr : lastThreading) thr.join();

    double axbNorm = 0, bNorm = 0, r2up = 0, r2down = 0; 
    for (size_t ind = 0; ind < matrix.size(); ++ind) {
        axbNorm += std::abs(AxMinusB[ind]);
        bNorm += std::abs(matrix[ind][matrix[0].size() - 1]);
        r2up += std::abs(solution[ind] - (double)((ind + 1) % 2));
        r2down += (double)((ind + 1) % 2);
    }
    return std::make_tuple(axbNorm / bNorm, r2up / r2down);
}
