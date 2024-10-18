#include "header.hpp"


std::tuple<double, double> answerDerivation(
    const std::vector<std::vector<double>>& startMatrix,
    const std::vector<std::vector<double>>& inversedMatrix
) noexcept {
    if (startMatrix.size() > 11000) return std::make_tuple(0.0, 0.0);
    std::vector<std::vector<double>> result1 = std::vector<std::vector<double>>(
        startMatrix.size(), 
        std::vector<double>(
            startMatrix.size(), 
            0.0
        )
    );
    std::vector<std::vector<double>> result2 = std::vector<std::vector<double>>(
        startMatrix.size(), 
        std::vector<double>(
            startMatrix.size(), 
            0.0
        )
    );


    for (size_t i = 0; i < startMatrix.size(); ++i) {
        for (size_t j = 0; j < startMatrix.size(); ++j) {
            for (size_t k = 0; k < startMatrix.size(); ++k) {
                result1[i][j] += startMatrix[i][k] * inversedMatrix[k][j];
                result2[i][j] += inversedMatrix[i][k] * startMatrix[k][j];
            }
        }
        result1[i][i] -= 1.0;
        result2[i][i] -= 1.0;
    }
    
    auto Norm = [](const std::vector<std::vector<double>>& matrix)->double{
        double maxSumAbs = 0.0;
        for (const auto& row : matrix) {
            double sumAbs = 0.0;
            for (double val : row) {
                sumAbs += std::abs(val);
            }
            if (sumAbs > maxSumAbs) maxSumAbs = sumAbs;
        }
        return maxSumAbs;
    };

    return std::make_tuple(Norm(result1), Norm(result2));
}
