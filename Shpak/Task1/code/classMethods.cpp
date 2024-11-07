#include "header.hpp"


LinearEquation::LinearEquation(const std::vector<double>& matrixRow) noexcept {
    this->VariableCoefficients = matrixRow;
    this->VariableCoefficients.resize(matrixRow.size() - 1);
    this->FreeCoefficient = matrixRow[matrixRow.size() - 1];
}


LinearEquation& LinearEquation::operator-=(const LinearEquation& other) noexcept {
    for (size_t i = 0; i < this->VariableCoefficients.size(); ++i) {
        this->VariableCoefficients[i] -= other.VariableCoefficients[i];
    }
    this->FreeCoefficient -= other.FreeCoefficient;
    return *this;
}
