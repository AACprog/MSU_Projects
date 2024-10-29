#include "header.hpp"


bool SolveFuncs::Solver::Solve(
    std::vector<LinearEquation>& system,
    const double& MatrixNorm,
    const int& p
) noexcept {
    if (system.size() < 2) return true;
    
    auto makeMultiplied = [](const LinearEquation& le, const double& multiplier)->LinearEquation{
        LinearEquation out(le);
        for (size_t i = 0; i < out.Variables.size(); ++i) {
            out.Variables[i].coefficient *= multiplier;
        }
        out.FreeCoefficient *= multiplier;
        return out;
    };
    auto eliminator = [&](
        const size_t& indexOfEquation,
        const size_t& indexOfVariable
    )->void {
        for (size_t i = 0; i < indexOfEquation; i += p) {
            std::vector<std::thread> thr;
            for (size_t j = 0; j < (size_t)p && i + j < indexOfEquation; ++j) {
                thr.emplace_back(
                    [&system, indexOfEquation, indexOfVariable, i, j, &makeMultiplied]() {
                        system[i + j] -= makeMultiplied(system[indexOfEquation], system[i + j].Variables[indexOfVariable].coefficient);
                    }
                );
            }
            for (auto& th : thr) th.join();
        }
        for (size_t i = indexOfEquation + 1; i < system.size(); i += p) {
            std::vector<std::thread> thr;
            for (size_t j = 0; j < (size_t)p && i + j < system.size(); ++j) {
                thr.emplace_back(
                    [&system, indexOfEquation, indexOfVariable, i, j, &makeMultiplied]() {
                        system[i + j] -= makeMultiplied(system[indexOfEquation], system[i + j].Variables[indexOfVariable].coefficient);
                    }
                );
            }
            for (auto& th : thr) th.join();
        } 
    };
    auto swapper = [&system](
        const size_t& index, 
        const size_t& position
    )->void{
        for (size_t i = 0; i < system.size(); ++i) {
            Variable v_tmp = system[i].Variables[index];
            system[i].Variables[index] = system[i].Variables[position];
            system[i].Variables[position] = v_tmp;
        }
    };

    size_t index = 0;
    while (index < system.size()) {
        std::tuple<bool, size_t> check_pos = system[index].Normalize_isZeros_position(MatrixNorm);
        const bool allZeros = std::get<0>(check_pos);
        const size_t position = std::get<1>(check_pos);
        if (allZeros) {
            if (std::abs(system[index].FreeCoefficient) > MatrixNorm * 10e-16) {
                std::cout << "Impossible for solving\n";
                return false;
            } 
            system.erase(system.begin() + index);
            continue;
        } 
        eliminator(
            index,
            position
        );
        swapper(
            index, 
            position
        );
        index++;
    }
    return true;
}


void SolveFuncs::Solution::GetAnswer(
    const std::vector<LinearEquation>& system,
    std::vector<double>& solution
) noexcept {
    for (size_t i = 0; i < system.size(); ++i) 
        solution[system[i].Variables[i].index] = system[i].FreeCoefficient;
}
