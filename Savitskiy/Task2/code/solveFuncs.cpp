#include "header.hpp"


bool SolveFuncs::Solver::Solve(
    std::vector<LinearEquation>& system,
    const double& MatrixNorm,
    const int& p
) noexcept {
    if (system.size() < 2) return true;
    auto print = [&](void)->void{
        for (const auto& row : system) {
            for (const auto& var :row.Variables) {
                printf("%10.3e ", var.coefficient);
            }
            printf("| %10.3e\n", row.FreeCoefficient);
        }
    };
    auto eliminator = [&](
        const size_t& indexOfEquation,
        const size_t& indexOfVariable
    )->void {
        for (size_t i = 0; i < indexOfEquation / p; i += p) {
            std::vector<std::thread> thr;
            for (size_t j = 0; j < (size_t)p && i + j < indexOfEquation; ++j) {
                thr.emplace_back(
                    [&system, indexOfEquation, indexOfVariable, i, j]() {
                        system[i + j] -= system[indexOfEquation] * system[i + j].Variables[indexOfVariable].coefficient;
                    }
                );
            }
            for (auto& th : thr) th.join();
        }
        for (size_t i = indexOfEquation + 1; i < system.size(); i += p) {
            std::vector<std::thread> thr;
            for (size_t j = 0; j < (size_t)p && i + j < system.size(); ++j) {
                thr.emplace_back(
                    [&system, indexOfEquation, indexOfVariable, i, j]() {
                        system[i + j] -= system[indexOfEquation] * system[i + j].Variables[indexOfVariable].coefficient;
                    }
                );
            }
            for (auto& th : thr) th.join();
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
        std::cout << "Indexes:\n";
        for (const auto& ind : system[0].Variables) {
            std::cout << ind.index << " ";
        }
        std::cout << "\n";
        print();
        std::swap(system[index], system[position]);
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