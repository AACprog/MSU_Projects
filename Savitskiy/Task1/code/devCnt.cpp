#include "header.hpp"


std::tuple<double, double> answerVariation(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<LinearEquation>& equations,
    const std::vector<double>& solution
) {
    double b = 0, AxbNorm = 0;
    double r_up2 = 0, r_down2 = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        double AxbRow = 0;
        for (size_t j = 0; j < matrix.size(); ++j) {
            AxbRow += solution[j] * matrix[i][j];
        }
        AxbNorm += std::abs(AxbRow - matrix[i][matrix.size()]);
    }
    for (size_t i = 0; i < equations.size(); ++i) {
        b += std::abs(matrix[i][matrix.size()]);    
        r_up2 += std::abs(equations[i].FreeCoefficient - double((equations[i].Variables[i].index + 1) % 2));
        r_down2 += double((equations[i].Variables[i].index + 1) % 2);

    }
    for (size_t i = equations.size(); i < matrix.size(); ++i) {
        b += std::abs(matrix[i][matrix.size()]);
    }

    double r1 = AxbNorm / b;
    double r2 = r_up2 / r_down2;
    return std::make_tuple(r1, r2);
}
