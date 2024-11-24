#pragma once


#include <vector>
#include <string>
#include <regex>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cmath>


namespace Matrix {
    namespace HelpFuncs {
        double f1(const size_t&, const size_t&, const size_t&) noexcept;
        double f2(const size_t&, const size_t&) noexcept;
        double f3(const size_t&, const size_t&, const size_t&) noexcept;
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
    double MatrixNorm(const std::vector<std::vector<double>>&) noexcept;


}


namespace Solve {
    std::tuple<size_t, size_t> FindElemenForZeroing(const std::vector<std::vector<double>>&) noexcept;
    void JacobianRotation(std::vector<std::vector<double>>&, const double&, const size_t&, size_t&) noexcept; 
    void MakeRotationMatrix(std::vector<std::vector<double>>&, const size_t&, const size_t&, const double&) noexcept;
    void Rotate(std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&, const size_t&, const size_t&) noexcept;
}


std::tuple<double, double> Variation(const std::vector<std::vector<double>>&, const std::vector<double>&) noexcept;
