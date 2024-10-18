#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
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


namespace Solve {
    namespace SolveFuncs {
        std::tuple<size_t, size_t> FindMaxAbs(const std::vector<std::vector<double>>&, const size_t&) noexcept;
        void EliminateUnder(std::vector<std::vector<double>>&, const size_t&) noexcept;
        void Eliminate(std::vector<std::vector<double>>&, const size_t&, const size_t&) noexcept;
        std::tuple<bool, std::vector<size_t>> Solve(std::vector<std::vector<double>>&, const double&) noexcept;
    }
    namespace Answer {
        std::vector<double> GetAnswer(const std::vector<std::vector<double>>&, const std::vector<size_t>&) noexcept;
    }
}


std::tuple<double, double> answerVariation(const std::vector<std::vector<double>>&, const std::vector<double>&);
