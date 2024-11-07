#pragma once


#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <iterator>
#include <tuple>
#include <ctime>
#include <algorithm>


class LinearEquation {
    public:
        LinearEquation(const std::vector<double>&) noexcept;
        ~LinearEquation() = default;
        LinearEquation(const LinearEquation&) = default;
        LinearEquation& operator=(const LinearEquation&) = default;
        LinearEquation& operator-=(const LinearEquation&) noexcept;

        std::vector<double> VariableCoefficients;
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


namespace Solve {
    namespace Solver {
        size_t FindMaxAbs(const std::vector<LinearEquation>&, const size_t&) noexcept;
        void Eliminate(std::vector<LinearEquation>&, const size_t&) noexcept;
        bool Solve(std::vector<LinearEquation>&, const double&) noexcept;
    }
    namespace Answer {
        void GetAnswer(
            const std::vector<LinearEquation>&, 
            std::vector<double>&,
            const double&
        ) noexcept;
    }
}


std::tuple<double, double> answerVariation(
    const std::vector<std::vector<double>>& matrix,
    const std::vector<LinearEquation>& equations,
    const std::vector<double>& solution
);


