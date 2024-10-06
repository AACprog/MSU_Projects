#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <iterator>
#include <tuple>


typedef struct {
    double coefficient;
    size_t index;
} Variable;


class LinearEquation {
    public:
        LinearEquation(const std::vector<double>& row) noexcept;
        ~LinearEquation() = default;
        LinearEquation(const LinearEquation&) = default;
        LinearEquation& operator=(const LinearEquation&) = default;
        LinearEquation(LinearEquation&&) = default;

        LinearEquation& operator-=(const LinearEquation& le) noexcept;
        void Multiply(const double& multiplier) noexcept;
        std::tuple<bool, size_t> Normalize_isZeros_position() noexcept;

        std::vector<Variable> Variables;
        double FreeCoefficient;
};




namespace FileWork {
    void matrixRead(std::vector<std::vector<double>>& matrix, const std::string& filename);
    namespace Parser {
        std::vector<double> parseRow(const std::string& row);
    }
    namespace Checker {
        bool checkMatrix(const std::vector<std::vector<double>>& matrix, const int& n);
    }
}


namespace SolveFuncs {
    namespace Eliminator {
        LinearEquation MakeMultiplied(
            LinearEquation equation, 
            const double& multiplier
        ) noexcept;
        void EliminateOther(
            std::vector<LinearEquation>& equations,
            const size_t& numberOfMainEquation,
            const size_t& numberOfMainVariable
        ) noexcept;
    }
    namespace Reorders {
        void Reorder(
            std::vector<LinearEquation>& equations,
            const size_t& mainVariableNumber
        ) noexcept;
    }
    namespace Solver {
        bool Solve(std::vector<LinearEquation>& equations) noexcept;        
    }
}


std::tuple<double, double, double> answerVariation(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<LinearEquation>& equations
);


