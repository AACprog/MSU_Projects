#include "header.hpp"


bool SolveFuncs::Solver::Solve(
    std::vector<LinearEquation>& system,
    const double& matrixNorm,
    const int& numberOfThreads
) noexcept {
    if (system.size() < 2) return true;
    auto swapCols = [&system](const size_t& col1, const size_t& col2) {
        for (auto& eq : system) std::swap(eq.Variables[col1], eq.Variables[col2]);
    };

    size_t blockSize = (system.size() % numberOfThreads == 0) ? system.size() / numberOfThreads : (system.size() / numberOfThreads) + 1;
    if (blockSize == 0) blockSize = 1;
    size_t index = 0;
    while (index < system.size()) {
        auto check_pos = system[index].Normalize_isZeros_position(matrixNorm);
        auto allZeros = std::get<0>(check_pos);
        auto position = std::get<1>(check_pos);
        if (allZeros) {
            if (std::abs(system[index].FreeCoefficient) > matrixNorm * 10e-16) {
                std::cout << "Impossible for solving\n";
                return false;
            } 
            system.erase(system.begin() + index);
            continue;
        } 
        swapCols(index, position);
        std::vector<std::thread> threads;
        for (size_t i = index + 1; i < system.size(); i += blockSize) {
            size_t tmp = std::min(i + blockSize, system.size());
            threads.emplace_back(
                std::thread(
                    threadFunction,
                    std::ref(system),
                    i,
                    tmp,
                    index
                )
            );
        }
        for (auto& thread : threads) thread.join();
        index++;
    }
    return true;
}



void SolveFuncs::Solver::threadFunction(
    std::vector<LinearEquation>& system, 
    size_t blockStart,
    size_t blockEnd,
    size_t eqNumber
) noexcept {
    auto makeMultiplied = [](const LinearEquation& eq, const double& multiplier) -> LinearEquation {
        LinearEquation eqCopy(eq);
        eqCopy.FreeCoefficient *= multiplier;
        for (auto& variable : eqCopy.Variables) {
            variable.coefficient *= multiplier;
        }
        return eqCopy;
    };
    for (size_t i = blockStart; i < blockEnd; ++i) {
        double multiplier = system[i].Variables[eqNumber].coefficient;
        system[i] -= makeMultiplied(system[eqNumber], multiplier);
    }
}


void SolveFuncs::Solution::GetAnswer(
    const std::vector<LinearEquation>& system,
    std::vector<double>& solution
) noexcept {
    for (size_t i = system.size() - 1;; --i) {
        solution[system[i].Variables[i].index] = system[i].FreeCoefficient;
        for (size_t j = i + 1; j < system.size(); ++j) {
            solution[system[i].Variables[i].index] -= solution[system[i].Variables[j].index] * system[i].Variables[j].coefficient;
        }
        if (i == 0) {
            break;
        }
    }
}
