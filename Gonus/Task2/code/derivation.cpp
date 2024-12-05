#include "header.hpp"


std::tuple<double, double> answerDerivation(
    const std::vector<std::vector<double>>& startMatrix,
    const std::vector<std::vector<double>>& inversedMatrix,
    const size_t& p
) noexcept {
    if (startMatrix.size() > 11000) return std::make_tuple(0.0, 0.0);
    std::vector<std::vector<double>> result1 = std::vector<std::vector<double>>(
        startMatrix.size(), 
        std::vector<double>(startMatrix.size(), 0.0)
    );
    std::vector<std::vector<double>> result2 = std::vector<std::vector<double>>(
        startMatrix.size(), 
        std::vector<double>(startMatrix.size(), 0.0)
    );


    /*for (size_t i = 0; i < startMatrix.size(); ++i) {
        for (size_t j = 0; j < startMatrix.size(); j += p) {
            std::vector<std::thread> threads;
            for (size_t j1 = 0; j1 < p && j + j1 < startMatrix.size(); ++j1) {
                threads.emplace_back(
                    std::thread(
                        [&result1, &result2, i, j, j1, &startMatrix, &inversedMatrix](){
                            for (size_t k = 0; k < startMatrix.size(); ++k) {
                                result1[i][j + j1] += startMatrix[i][k] * inversedMatrix[k][j + j1];
                                result2[i][j + j1] += inversedMatrix[i][k] * startMatrix[k][j + j1];
                            }
                        }
                    )
                );
            }
            for (auto& th : threads) th.join();
        }
        result1[i][i] -= 1.0;
        result2[i][i] -= 1.0;
    }*/
    auto blockMultiply = [&startMatrix, &inversedMatrix, &result1, &result2](size_t blockStart, size_t blockEnd) {
        for (size_t i = blockStart; i < blockEnd; ++i) {
            for (size_t j = 0; j < inversedMatrix.size(); ++j) {
                for (size_t k = 0; k < startMatrix.size(); ++k) {
                    result1[i][j] += startMatrix[i][k] * inversedMatrix[k][j];
                    result2[i][j] += inversedMatrix[i][k] * startMatrix[k][j];
                }
            }   
            result1[i][i] -= 1.0;
            result2[i][i] -= 1.0;
        }
    };
    size_t blockSize = startMatrix.size() / p + ((startMatrix.size() % p == 0) ? 0 : 1);
    std::vector<std::thread> threads;
    for (size_t i = 0; i < startMatrix.size(); i += blockSize) {
        size_t blockEnd = std::min(i + blockSize, startMatrix.size());
        threads.emplace_back(
            std::thread(
                blockMultiply,
                i,
                blockEnd
            )
        );
    } 
    for (auto& thread : threads) thread.join();
    
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
