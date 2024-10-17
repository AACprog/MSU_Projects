#include "header.hpp"


size_t Solve::RowWork::FindMaxAbs(
    const std::vector<LinearEquation>& leVec, 
    const size_t& index
) noexcept {
    double maxAbs = 0.0;
    size_t pos = 0;
    for (size_t i = index; i < leVec.size(); ++i) {
        if (maxAbs < std::abs(leVec[i].VariableCoefficients[index])) {
            pos = i;
            maxAbs = std::abs(leVec[i].VariableCoefficients[index]);
        }
    }
    return pos;
}


void Solve::RowWork::Normalize_SetOnMain(
    std::vector<LinearEquation>& leVec,
    const size_t& newIndex,
    const size_t& nowIndex
) noexcept {
    //leVec[nowIndex].divide(leVec[nowIndex].VariableCoefficients[nowIndex]);
    double divider = leVec[nowIndex].VariableCoefficients[nowIndex];
    leVec[nowIndex].FreeCoefficient /= divider;
    for (size_t i = 0; i < leVec[nowIndex].VariableCoefficients.size(); ++i) {
        leVec[nowIndex].VariableCoefficients[i] /= divider;
    }

    myswap(&leVec[newIndex], &leVec[nowIndex]);
}


std::tuple<bool, bool> Solve::RowWork::AllZeros_IsOk(
    const LinearEquation& le,
    const double& MatrixNorm    
) noexcept {
    for (size_t i = 0; i < le.VariableCoefficients.size(); ++i) {
        if (le.VariableCoefficients[i] > MatrixNorm * 10e-10) {
            return std::make_tuple(false, true);
        }
    }
    return std::make_tuple(true, (le.FreeCoefficient < MatrixNorm * 10e-10));
}


void Solve::RowWork::EliminateUnder(
    std::vector<LinearEquation>& leVec,
    const size_t& index
) noexcept {
    for (size_t i = index + 1; i < leVec.size(); ++i) {
        double multiplier = 
            leVec[i].VariableCoefficients[index] /
            leVec[index].VariableCoefficients[index];
        leVec[i] -= leVec[index].multiply(multiplier);
    }
}


bool Solve::Solver::Jordan(
    std::vector<LinearEquation>& leVec, 
    const double& MatrixNorm
) noexcept {
    size_t index = 0;
    while (index < leVec.size()) {
        size_t position = RowWork::FindMaxAbs(leVec, index);
        auto check = RowWork::AllZeros_IsOk(leVec[position], MatrixNorm);
        if (!std::get<1>(check)) return false;
        if (std::get<0>(check)) {
            leVec.erase(leVec.begin() + position);
            continue;
        }
        RowWork::Normalize_SetOnMain(leVec, index, position);
        RowWork::EliminateUnder(leVec, index);
        ++index;
    }
    return true;
}


std::vector<double> Solve::Solution::GetAnswer(
    const std::vector<LinearEquation>& leVec,
    const size_t& n
) noexcept {
    std::vector<double> xVec(n, 0.0);
    for (int i = leVec.size() - 1; i >= 0; --i) {
        xVec[(size_t)i] += leVec[(size_t)i].FreeCoefficient;
        for (size_t j = (size_t)i + 1; j < leVec.size(); ++j) {
            xVec[(size_t)i] -= leVec[(size_t)i].VariableCoefficients[j] * xVec[j];
        }
    }
    return xVec;
}


