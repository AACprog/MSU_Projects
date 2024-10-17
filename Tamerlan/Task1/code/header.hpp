//#pragma once


#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>
#include <tuple>
#include <iterator>
#include <ctime>
#include <algorithm>

class LinearEquation {
    public:
        LinearEquation(const std::vector<double>&) noexcept;
        LinearEquation(const LinearEquation&) noexcept;
        LinearEquation& operator-=(const LinearEquation&) noexcept;
        LinearEquation& operator=(const LinearEquation&) noexcept;
        LinearEquation multiply(const double&) noexcept;
        ~LinearEquation(void) = default;
        std::vector<double> VariableCoefficients;
        double FreeCoefficient;
};


void myswap(LinearEquation*, LinearEquation*) noexcept;
size_t mymax(const size_t&, const size_t&) noexcept;
size_t mymin(const size_t&, const size_t&) noexcept;
double MatrixNorm(const std::vector<std::vector<double>>&) noexcept;


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
        void BuildBCol(std::vector<std::vector<double>>&) noexcept;
    }
    namespace Check {
        bool CheckMatrix(const std::vector<std::vector<double>>&, const size_t&) noexcept;
    }
    bool BuildCheck(std::vector<std::vector<double>>&, const int&, const int&, const std::string&) noexcept;
}


namespace Solve {
    namespace RowWork {
        size_t FindMaxAbs(const std::vector<LinearEquation>&, const size_t&) noexcept;
        void Normalize_SetOnMain(std::vector<LinearEquation>&, const size_t&, const size_t&) noexcept;
        std::tuple<bool, bool> AllZeros_IsOk(const LinearEquation&, const double&) noexcept;
        void EliminateUnder(std::vector<LinearEquation>&, const size_t&) noexcept;
    }
    namespace Solver {
        bool Jordan(std::vector<LinearEquation>&, const double&) noexcept;
    }
    namespace Solution {
        std::vector<double> GetAnswer(const std::vector<LinearEquation>&, const size_t&) noexcept;
    }
}


std::tuple<double, double> answerVariation(
    const std::vector<std::vector<double>>&,
    const std::vector<LinearEquation>&,
    const std::vector<double>&
) noexcept;



