#include "header.hpp"


PairedMatrixRow::PairedMatrixRow(
    const std::vector<double>& matrixRow, 
    const size_t& number
) noexcept {
    mainMatrixRow = matrixRow;
    helpMatrixRow = std::vector<double>(matrixRow.size(), 0);
    helpMatrixRow[number] = 1;
}



PairedMatrixRow& PairedMatrixRow::operator=(const PairedMatrixRow& pmr) noexcept {
    this->mainMatrixRow = pmr.mainMatrixRow;
    this->helpMatrixRow = pmr.helpMatrixRow;
    return *this;
}



PairedMatrixRow& PairedMatrixRow::operator-=(const PairedMatrixRow& pmr) noexcept {
    for (size_t i = 0; i < this->mainMatrixRow.size(); ++i) {
        this->mainMatrixRow[i] -= pmr.mainMatrixRow[i];
        this->helpMatrixRow[i] -= pmr.helpMatrixRow[i];
    }
    return *this;
}


void PairedMatrixRow::Multiply(const double& multiplier) noexcept {
    for (size_t i = 0; i < this->mainMatrixRow.size(); ++i) {
        this->mainMatrixRow[i] *= multiplier;
        this->helpMatrixRow[i] *= multiplier;
    }
}


void PairedMatrixRow::Divide(const double& divider) noexcept {
    for (size_t i = 0; i < this->mainMatrixRow.size(); ++i) {
        this->mainMatrixRow[i] /= divider;
        this->helpMatrixRow[i] /= divider;
    }
}


PairedMatrix::PairedMatrix(const std::vector<std::vector<double>>& matrix) noexcept {
    for (size_t i = 0; i < matrix.size(); ++i) {
        pairedRows.push_back(PairedMatrixRow(matrix[i], i));
    }
}


std::tuple<bool, size_t> PairedMatrix::FindMaxAbs_isZeros_numberRow(const size_t& colNumber) const noexcept {
    static size_t start = 0;
    size_t maxAbsNumber = 0;
    double maxAbs = 0;
    
    for (size_t i = start; i < pairedRows.size(); ++i) {
        if (maxAbs < std::abs(pairedRows[i].mainMatrixRow[colNumber])) {
            maxAbs = std::abs(pairedRows[i].mainMatrixRow[colNumber]);
            maxAbsNumber = i;
        } 
    }
    start++;
    
    if (maxAbs < 10e-10) {
        return std::make_tuple(true, 0);
    }
    return std::make_tuple(false, maxAbsNumber);
}


PairedMatrix PairedMatrix::operator=(const PairedMatrix& pmr) {
    pairedRows = pmr.pairedRows;
    return *this;
}