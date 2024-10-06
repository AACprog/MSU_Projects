#include "header.hpp"


std::tuple<double, double, double> Check::count_R1_R2_Time(
    const std::vector<std::vector<double>>& matrix,
    const PairedMatrix& reversedMatrix
) noexcept {
    clock_t start = clock();
    //double R1 = 0.0;
    //double R2 = 0.0;
    std::vector<std::vector<double>> res1(matrix.size(), std::vector<double>(matrix.size()));
    std::vector<std::vector<double>> res2(matrix.size(), std::vector<double>(matrix.size()));
    //std::cout << matrix.size() << "\n" << matrix[0].size() << "\n";
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.size(); ++j) {
            res1[i][j] = (i == j) ? -1 : 0;
            res2[i][j] = (i == j) ? -1 : 0;
            for (size_t r = 0; r < matrix.size(); ++r) {
                res1[i][j] += matrix[i][r] * reversedMatrix.pairedRows[r].helpMatrixRow[j];
                res2[i][j] += matrix[r][j] * reversedMatrix.pairedRows[i].helpMatrixRow[r];
            }
        }
    }
    
    auto matrixNorm1 = [](const std::vector<std::vector<double>>& m)->double {
        double maxRowAbsSum = 0;
        for (const auto& row : m) {
            double rowAbsSum = 0;
            for (const auto& element : row) {
                rowAbsSum += std::abs(element);
            }
            maxRowAbsSum = (maxRowAbsSum < rowAbsSum) ? rowAbsSum : maxRowAbsSum;
        }
        return maxRowAbsSum;
    };
    
    return std::make_tuple(matrixNorm1(res1), matrixNorm1(res2), (double)(clock() - start) / CLOCKS_PER_SEC); 
}
