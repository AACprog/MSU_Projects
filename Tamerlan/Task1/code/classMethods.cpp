#include "header.hpp"


LinearEquation::LinearEquation(const std::vector<double>& matrixRow) noexcept {
    VariableCoefficients = std::vector<double>(matrixRow.size() - 1);
    for (size_t i = 0; i < matrixRow.size() - 1; ++i) {
        VariableCoefficients[i] = matrixRow[i];
    }
    FreeCoefficient = matrixRow[matrixRow.size() - 1];
}


LinearEquation::LinearEquation(const LinearEquation& le) noexcept {
    VariableCoefficients = le.VariableCoefficients;
    FreeCoefficient = le.FreeCoefficient;
}


LinearEquation& LinearEquation::operator-=(const LinearEquation& le) noexcept {
    for (size_t i = 0; i < VariableCoefficients.size(); ++i) {
        VariableCoefficients[i] -= le.VariableCoefficients[i];
    }
    FreeCoefficient -= le.FreeCoefficient;
    return *this;
}


LinearEquation& LinearEquation::operator=(const LinearEquation& le) noexcept {
    VariableCoefficients = le.VariableCoefficients;
    FreeCoefficient = le.FreeCoefficient;
    return *this;
}



LinearEquation LinearEquation::multiply(const double& multiplier) noexcept {
    LinearEquation multiplied(*this);
    for (size_t i = 0; i < multiplied.VariableCoefficients.size(); ++i) {
        multiplied.VariableCoefficients[i] *= multiplier;
    }
    multiplied.FreeCoefficient *= multiplier;
    return multiplied;
}
