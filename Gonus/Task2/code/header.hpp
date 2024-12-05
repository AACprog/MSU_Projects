#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <iterator>
#include <tuple>
#include <algorithm>
#include <thread>

class PairedMatrixRow {
    public:
        PairedMatrixRow(const std::vector<double>&, const size_t&) noexcept;
        ~PairedMatrixRow(void) = default;
        PairedMatrixRow(const PairedMatrixRow&) = default;
        PairedMatrixRow& operator-=(const PairedMatrixRow&) noexcept;
        PairedMatrixRow Multiply(const double&) const noexcept;
        bool AllZeros(const double&) const noexcept;
        std::vector<double> MainRow;
        std::vector<double> PairedRow;
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
}


namespace Solve {
    namespace Solver {
        size_t FindMaxAbs(const std::vector<PairedMatrixRow>&, const size_t&) noexcept;
        void Eliminate(std::vector<PairedMatrixRow>&, const size_t&, const size_t&) noexcept;
        bool Solve(std::vector<PairedMatrixRow>&, const double&, const size_t&) noexcept;
    }
    namespace Answer {
        std::vector<std::vector<double>> GetAnswer(const std::vector<PairedMatrixRow>&) noexcept;
    }
}


std::tuple<double, double> answerDerivation(
    const std::vector<std::vector<double>>&,
    const std::vector<std::vector<double>>&,
    const size_t&
) noexcept;
