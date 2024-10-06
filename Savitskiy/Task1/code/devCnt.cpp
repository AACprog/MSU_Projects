#include "header.hpp"


std::tuple<double, double, double> answerVariation(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<LinearEquation>& equations
) {
    clock_t start = clock();
    double Axb = 0, b = 0;
    double r_up2 = 0, r_down2 = 0;
    for (size_t i = 0; i < equations.size(); ++i) {
        Axb += std::abs(equations[i].FreeCoefficient * matrix[i][equations[i].Variables[i].index] - matrix[i][matrix.size() - 1]);  
        b += std::abs(matrix[i][matrix.size() - 1]);    
        r_up2 += std::abs(equations[i].FreeCoefficient - double(equations[i].Variables[i].index % 2));
        r_down2 += double(equations[i].Variables[i].index % 2);

    }
    for (size_t i = equations.size(); i < matrix.size(); ++i) {
        b += std::abs(matrix[i][matrix.size() - 1]);
    }

    double r1 = Axb / b;
    double r2 = r_up2 / r_down2;
    return std::make_tuple(r1, r2, (double)(clock() - start) / CLOCKS_PER_SEC);
}
