#include "header.hpp"


std::tuple<double, double> answerVariation(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<double>& solution
) {
    auto Norm = [](const std::vector<double>& vec)->double{
        double sumAbs = 0.0;
        for (const auto& elem : vec) {
            sumAbs += std::abs(elem);
        }
        return sumAbs;
    };
    std::vector<double> ax(solution.size(), 0.0);
    std::vector<double> xx = solution;
    std::vector<double> x(solution.size());
    std::vector<double> b(solution.size());
    for (size_t i = 0; i < solution.size(); ++i) {
        for (size_t j = 0; j < solution.size(); ++j) {
            ax[i] += matrix[i][j] * solution[j];
        }
        ax[i] -= matrix[i][matrix.size()];
        xx[i] -= (double)((i + 1) % 2);
        b[i] = matrix[i][matrix.size()];
        x[i] = (double)((i + 1) % 2);
    }
    return std::make_tuple(
        Norm(ax) / Norm(b),
        Norm(xx) / Norm(x)
    );
}