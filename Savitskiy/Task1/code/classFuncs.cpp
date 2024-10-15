#include "header.hpp"


LinearEquation::LinearEquation(const std::vector<double>& row) noexcept {
    for (size_t i = 0; i < row.size() - 1; ++i) {
        Variable v_tmp;
        v_tmp.coefficient = row[i];
        v_tmp.index = i;
        Variables.push_back(v_tmp);
    }
    FreeCoefficient = row[row.size() - 1];
}


LinearEquation& LinearEquation::operator-=(const LinearEquation& le) noexcept {
    for (size_t i = 0; i < le.Variables.size(); ++i) {
        Variables[i].coefficient -= le.Variables[i].coefficient;
    }
    FreeCoefficient -= le.FreeCoefficient;
    return *this;
}


void LinearEquation::Multiply(const double& multiplier) noexcept {
    for (size_t i = 0; i < Variables.size(); ++i) {
        Variables[i].coefficient *= multiplier;
    }
    FreeCoefficient *= multiplier;
}


std::tuple<bool, size_t> LinearEquation::Normalize_isZeros_position(const double& MatrixNorm) noexcept {
    double maxAbs = 0;
    size_t pos = 0;
    for (size_t i = 0; i < Variables.size(); ++i) {
        if (std::abs(Variables[i].coefficient) > maxAbs) {
            maxAbs = std::abs(Variables[i].coefficient);
            pos = i;
        }
    }

    if (maxAbs < MatrixNorm * 10e-10) {
        return std::make_tuple(true, 0);
    }
    double mx = Variables[pos].coefficient;
    for (size_t i = 0; i < Variables.size(); ++i) {
        Variables[i].coefficient /= mx;
    }
    FreeCoefficient /= mx;
    return std::make_tuple(false, pos);
}
