#include "header.hpp"


void RowWork::Reorder::Reorder(PairedMatrix& matrix, const size_t& pos) noexcept {
    static size_t posToPlace = 0;
    PairedMatrixRow pmr_tmp = matrix.pairedRows[posToPlace];
    matrix.pairedRows[posToPlace++] = matrix.pairedRows[pos];
    matrix.pairedRows[pos] = pmr_tmp;
}


PairedMatrixRow RowWork::Eliminator::makeMultiplied(PairedMatrixRow row, const double& multiplier) noexcept {
    row.Multiply(multiplier);
    return row;
}


void RowWork::Eliminator::Eliminate(PairedMatrix& matrix, const size_t& index) noexcept {
    static size_t colNumber = 0;
    for (size_t i = 0; i < index; ++i) {
        PairedMatrixRow pmr_tmp = makeMultiplied(
            matrix.pairedRows[index], 
            matrix.pairedRows[i].mainMatrixRow[colNumber] / matrix.pairedRows[index].mainMatrixRow[colNumber]
        ); 
        matrix.pairedRows[i] -= pmr_tmp;
    }
    for (size_t i = index + 1; i < matrix.pairedRows.size(); ++i) {
        PairedMatrixRow pmr_tmp = makeMultiplied(
            matrix.pairedRows[index], 
            matrix.pairedRows[i].mainMatrixRow[colNumber] / matrix.pairedRows[index].mainMatrixRow[colNumber]
        ); 
        matrix.pairedRows[i] -= pmr_tmp;
    }
    colNumber++;
}


bool RowWork::Solver::Solve(PairedMatrix& matrix) noexcept {
    for (size_t i = 0; i < matrix.pairedRows.size(); ++i) {
        std::tuple<bool, size_t> tmpTuple = matrix.FindMaxAbs_isZeros_numberRow(i);
        bool isZeros = std::get<0>(tmpTuple);
        if (isZeros) {
            return false;
        }
        size_t position = std::get<1>(tmpTuple);
        matrix.pairedRows[i].Divide(matrix.pairedRows[position].mainMatrixRow[i]);
        Eliminator::Eliminate(matrix, position);
        Reorder::Reorder(matrix, position);
    }
    return true;
}
