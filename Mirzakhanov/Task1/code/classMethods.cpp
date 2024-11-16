#include "header.hpp"


LinearEquation::LinearEquation(const std::vector<double>& row) noexcept {
    this->VariableCoefficients = row;
    this->VariableCoefficients.resize(row.size() - 1);
    this->FreeCoefficient = row[row.size() - 1];
}


LinearEquation& LinearEquation::operator-=(const LinearEquation& le) noexcept {
    for (size_t i = 0; i < VariableCoefficients.size(); ++i) {
        this->VariableCoefficients[i] -= le.VariableCoefficients[i];
    }
    this->FreeCoefficient -= le.FreeCoefficient;
    return *this;
}


LinearEquation LinearEquation::Multiply(const double& multipier) const noexcept {
    LinearEquation le(*this);
    for (auto& v : le.VariableCoefficients) {
        v *= multipier;
    }
    le.FreeCoefficient *= multipier;
    return le;
}


LinearEquation& LinearEquation::Divide(const double& divisor) noexcept {
    for (auto& v : VariableCoefficients) {
        v /= divisor;
    }
    FreeCoefficient /= divisor;
    return *this;
}
