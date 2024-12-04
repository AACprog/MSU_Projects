#include "header.hpp"


std::tuple<double, double> Variation::GetVariation(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<double>& solution
) noexcept {
    double axbNorm = 0, bNorm = 0, r2up = 0, r2down = 0; 
    for (size_t ind = 0; ind < matrix.size(); ++ind) {
        double sum = 0;
        for (size_t j = 0; j < matrix.size(); ++j) {
            sum += solution[j] * matrix[ind][j];
        }
        axbNorm += std::abs(sum - matrix[ind][matrix.size()]);
        bNorm += std::abs(matrix[ind][matrix.size()]);
        r2up += std::abs(solution[ind] - (double)((ind + 1) % 2));
        r2down += (double)((ind + 1) % 2);
    }
    return std::make_tuple(axbNorm / bNorm, r2up / r2down);
}
