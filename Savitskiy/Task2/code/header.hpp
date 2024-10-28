#pragma once 


#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <iterator>
#include <vector>
#include <tuple>
#include <thread>
#include <algorithm>
#include <ctime>


typedef struct {
    double coefficient;
    size_t index;
} Variable;


class LinearEquation {
    public:
        LinearEquation(const std::vector<double>&) noexcept;
        ~LinearEquation() = default;
        LinearEquation(const LinearEquation&) = default;
        LinearEquation(LinearEquation&&) = default;

        LinearEquation& operator=(const LinearEquation&) = default;
        LinearEquation& operator-=(const LinearEquation&) noexcept;
        LinearEquation operator*(const double&) const noexcept;

        std::tuple<bool, size_t> Normalize_isZeros_position(const double&) noexcept;

        std::vector<Variable> Variables;
        double FreeCoefficient;
};


namespace Matrix {
    namespace HelpFuncs {
        double f1(const size_t&, const size_t&, const size_t&) noexcept;
        double f2(const size_t&, const size_t&) noexcept;
        double f3(const size_t&, const size_t&) noexcept;
        double f4(const size_t&, const size_t&) noexcept;
    }
    namespace Build {
        void BuildMatrix(std::vector<std::vector<double>>&, const int&, const int&, const std::string&) noexcept;
        void MatrixRead(std::vector<std::vector<double>>&, const std::string&) noexcept;
    }
    namespace Check {
        bool CheckMatrix(const std::vector<std::vector<double>>&, const size_t&) noexcept;
    }
    bool BuildCheck(std::vector<std::vector<double>>&, const int&, const int&, const std::string&) noexcept;
    void BuildBCol(std::vector<std::vector<double>>&) noexcept;
    double MatrixNorm(const std::vector<std::vector<double>>&) noexcept;
}


namespace SolveFuncs {
    namespace Solver {
        bool Solve(std::vector<LinearEquation>&, const double&, const int&) noexcept;
    }
    namespace Solution
    {
        void GetAnswer(const std::vector<LinearEquation>&, std::vector<double>&) noexcept;
    }
}


namespace Variation {
    std::tuple<double, double> GetVariation(
        const std::vector<std::vector<double>>&, 
        const std::vector<double>&,
        const int&
    ) noexcept;
}
