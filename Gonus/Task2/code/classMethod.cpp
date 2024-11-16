#include "header.hpp"


PairedMatrixRow::PairedMatrixRow(
    const std::vector<double>& row, 
    const size_t& index
) noexcept {
    this->MainRow = row;
    this->PairedRow = std::vector<double>(row.size(), 0);
    this->PairedRow[index] = 1.0;
}


PairedMatrixRow& PairedMatrixRow::operator-=(const PairedMatrixRow& pmr) noexcept {
    for (size_t i = 0; i < MainRow.size(); ++i) {
        this->MainRow[i] -= pmr.MainRow[i];
        this->PairedRow[i] -= pmr.PairedRow[i];
    }
    return *this;
}


PairedMatrixRow PairedMatrixRow::Multiply(const double& multiplier) const noexcept {
    PairedMatrixRow multiplied(*this);
    for (size_t i = 0; i < MainRow.size(); ++i) {
        multiplied.MainRow[i] *= multiplier;
        multiplied.PairedRow[i] *= multiplier;
    }
    return multiplied;
}


bool PairedMatrixRow::AllZeros(const double& norm) const noexcept {
    for (const auto& val : this->MainRow) {
        if (std::abs(val) > norm * 10e-16) {
            return false;
        }
    }
    return true;
}