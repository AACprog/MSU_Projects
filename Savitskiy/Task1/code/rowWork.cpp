#include "header.hpp"


LinearEquation SolveFuncs::Eliminator::MakeMultiplied(
    LinearEquation equation, 
    const double& multiplier
 ) noexcept {
    equation.Multiply(multiplier);
    return equation;
}

void SolveFuncs::Eliminator::EliminateOther(
    std::vector<LinearEquation>& equations,
    const size_t& numberOfMainEquation,
    const size_t& numberOfMainVariable
) noexcept {
    for (size_t i = 0; i < numberOfMainEquation; ++i) {
        double multiplier = 
            equations[i].Variables[numberOfMainVariable].coefficient / 
            equations[numberOfMainEquation].Variables[numberOfMainVariable].coefficient;
        equations[i] -= MakeMultiplied(
            equations[numberOfMainEquation],
            multiplier
        );
    }
    for (size_t i = numberOfMainEquation + 1; i < equations.size(); ++i) {
        double multiplier = 
            equations[i].Variables[numberOfMainVariable].coefficient / 
            equations[numberOfMainEquation].Variables[numberOfMainVariable].coefficient;
        equations[i] -= MakeMultiplied(
            equations[numberOfMainEquation],
            multiplier
        );
    }
}


void SolveFuncs::Reorders::Reorder(
    std::vector<LinearEquation>& equations,
    const size_t& mainVariableNumber
) noexcept {
    static size_t number = 0;
    for (size_t i = 0; i < equations.size(); ++i) {
        Variable v_tmp = equations[i].Variables[mainVariableNumber];
        equations[i].Variables[mainVariableNumber] = equations[i].Variables[number];
        equations[i].Variables[number] = v_tmp;
    }
    number++;
}


bool SolveFuncs::Solver::Solve(std::vector<LinearEquation>& equations) noexcept {
    if (equations.size() == 1) {
        return true;
    }
    size_t index = 0;
    while (index < equations.size()) {
        std::tuple<bool, size_t> check_pos = equations[index].Normalize_isZeros_position();
        const bool allZeros = std::get<0>(check_pos);
        const size_t position = std::get<1>(check_pos);
        if (allZeros) {
            if (std::abs(equations[index].FreeCoefficient) > 10e-10) {
                std::cout << "Impossible for solving\n";
                return false;
            } 
            equations.erase(equations.begin() + index);
            continue;
        } 
        Eliminator::EliminateOther(
            equations,
            index,
            position
        );
        Reorders::Reorder(
            equations,
            position
        );
        index++;
    }
    return true;
}
