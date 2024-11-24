#include "header.hpp"


LinearEquation makeLE(const std::vector<double>& matrixRow) noexcept {
    std::vector<double> vec = matrixRow;
    vec.resize(matrixRow.size() - 1);
    return std::make_pair(vec, matrixRow.back());
}

 
void substracteqLE(LinearEquation& eq1, const LinearEquation& eq2) noexcept {
    for (size_t i = 0; i < eq1.first.size(); ++i) {
        eq1.first[i] -= eq2.first[i];
    }
    eq1.second -= eq2.second;
}