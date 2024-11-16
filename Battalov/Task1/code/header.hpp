#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <regex>
#include <iterator>
#include <tuple>


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



class LinearEquation {
    public:
        LinearEquation(const std::vector<double>&) noexcept;
        LinearEquation(const LinearEquation&) = default;
        ~LinearEquation() = default;
        LinearEquation& operator=(const LinearEquation&) = default;
        LinearEquation& operator-=(const LinearEquation&) noexcept;
        LinearEquation Multiply(const double&) const noexcept;
        LinearEquation& Divide(const double&) noexcept;
        std::vector<double> VariableCoefficients;
        double FreeCoefficient;
};


namespace SolveFuncs {
    namespace Solve {
        bool Solve(std::vector<LinearEquation>&, const double&) noexcept;
    }
    namespace Answer {
        std::vector<double> GetAnswer(const std::vector<LinearEquation>&, const double&) noexcept;
    }
}


std::tuple<double, double> answerVariation(const std::vector<std::vector<double>>&, const std::vector<double>&);