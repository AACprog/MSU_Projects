#include "header.hpp"


size_t Solve::Solver::FindMaxAbs(
    const std::vector<LinearEquation>& system,
    const size_t& colNumber
) noexcept {
    size_t pos = 0; 
    double maxAbs = 0.0;
    for (size_t i = colNumber; i < system.size(); ++i) {
        double absValue = std::abs(system[i].first[colNumber]);
        if (absValue > maxAbs) {
            maxAbs = absValue;
            pos = i;
        }
    }
    return pos;
}


void Solve::Solver::Eliminate(
    std::vector<LinearEquation>& system,
    const size_t& rowNumber
) noexcept {
    auto makeMultiplied = [](
        const LinearEquation& eq, 
        const double& multiplier
    )-> LinearEquation {
        LinearEquation newEq(eq);
        for (auto& i : newEq.first) {
            i *= multiplier;
        }
        newEq.second *= multiplier;
        return newEq;
    };

    for (size_t i = 0; i < rowNumber; ++i) {
        substracteqLE(system[i], makeMultiplied(
            system[rowNumber], 
            system[i].first[rowNumber]
        ));
    }

    for (size_t i = rowNumber + 1; i < system.size(); ++i) {
        substracteqLE(system[i], makeMultiplied(
            system[rowNumber], 
            system[i].first[rowNumber]
        ));
    }
}


bool  Solve::Solver::Solve(
    std::vector<LinearEquation>& system,
    const double& norm
) noexcept {
    size_t colNumber = 0;
    double eps = 10e-16;

    auto normalize = [](LinearEquation& eq,  const size_t& pos) {
        double divider = eq.first[pos];
        for (auto& i : eq.first) {
            i /= divider;
        }
        eq.second /= divider;
    };


    auto allZeros_isOk = [&eps, &norm](const  LinearEquation& eq)-> std::tuple<bool, bool> {
        for (const auto& i : eq.first) {
            if (std::abs(i) > norm * eps) return std::make_tuple(false, true);
        }
        if (std::abs(eq.second) < norm * eps)  return std::make_tuple(true, true);
        return std::make_tuple(true, false);
    };


    while (colNumber < system.size()) {
        size_t pos = FindMaxAbs(system, colNumber);
        if (std::abs(system[pos].first[colNumber]) < norm * eps) {
            auto check = allZeros_isOk(system[pos]);
            if (!std::get<1>(check)) {
                return false;
            }
            if (std::get<0>(check)) {
                system.erase(system.begin() + pos);
            }
            ++colNumber;
            continue;
        }
        normalize(system[pos], colNumber);
        std::swap(system[pos], system[colNumber]);
        Eliminate(system, colNumber);
        ++colNumber;
    }
    return true;
}


void Solve::Answer::GetAnswer(
    const std::vector<LinearEquation>& system,
    std::vector<double>& answer,
    const double& norm
) noexcept {
    double eps = 10e-16;
    for (size_t i = 0;  i < system.size(); ++i) {
        if (std::abs(system[i].first[i]) < norm * eps) {
            answer[i] = 0;
        } else {
            answer[i] = system[i].second;
        }
    }
}
