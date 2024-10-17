#include "header.hpp"


void myswap(LinearEquation* el1, LinearEquation* el2) noexcept {
    std::swap(*el1, *el2);
}


size_t mymax(const size_t& el1, const size_t& el2) noexcept {
    return (el1 > el2) ? el1 : el2;
}


size_t mymin(const size_t& el1, const size_t& el2) noexcept {
    return (el1 < el2) ? el1 : el2;
}


double MatrixNorm(const std::vector<std::vector<double>>& matrix) noexcept {
    double mx = 0.0;
    for (const auto& row : matrix) {
        for (const auto& el : row) {
            mx = (mx > std::abs(el)) ? mx : std::abs(el);
        } 
    }
    return mx;
}