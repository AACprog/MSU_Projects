#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <fstream>
#include <tuple>
#include <ctime>


class PairedMatrixRow {
public:
    std::vector<double> mainMatrixRow;
    std::vector<double> helpMatrixRow;
    
    PairedMatrixRow(const std::vector<double>& matrixRow, const size_t& number) noexcept;
    ~PairedMatrixRow() = default;
    PairedMatrixRow(const PairedMatrixRow&) = default;
    
    PairedMatrixRow& operator=(const PairedMatrixRow&) noexcept;
    PairedMatrixRow& operator-=(const PairedMatrixRow& pmr) noexcept;
    
    void Multiply(const double& multiplier) noexcept;  
    void Divide(const double& divider) noexcept;
};


class PairedMatrix {
public:
    std::vector<PairedMatrixRow> pairedRows;
    
    PairedMatrix() = default;
    PairedMatrix(const std::vector<std::vector<double>>& matrix) noexcept;
    ~PairedMatrix() = default;
    PairedMatrix(const PairedMatrix&) = default;
    PairedMatrix(PairedMatrix&&) = default;

    PairedMatrix operator=(const PairedMatrix& pmr);
    
    std::tuple<bool, size_t> FindMaxAbs_isZeros_numberRow(const size_t& colNumber) const noexcept;
};



namespace RowWork {
    namespace Reorder {
        void Reorder(PairedMatrix& matrix, const size_t& pos) noexcept;
    }
    namespace Eliminator {
        void Eliminate(PairedMatrix& matrix, const size_t& index) noexcept;
        PairedMatrixRow makeMultiplied(PairedMatrixRow row, const double& multiplier) noexcept;
    }
    namespace Solver {
        bool Solve(PairedMatrix& matrix) noexcept;
    }
}



namespace FileWork {
    void matrixRead(std::vector<std::vector<double>>& matrix, const std::string& filename);
    namespace Parser {
        std::vector<double> parseRow(const std::string& row);
    }
    namespace Checker {
        bool checkMatrix(const std::vector<std::vector<double>>& matrix, const size_t& n);
    }
}


namespace MatrixBuild {
    namespace HelpFuncs {
        double f1(const size_t& i, const size_t& j, const size_t& n) noexcept;
        double f2(const size_t& i, const size_t& j) noexcept;
        double f3(const size_t& i, const size_t& j) noexcept;
        double f4(const size_t& i, const size_t& j) noexcept;
    }
    namespace Build {
        bool matrixMake(
            std::vector<std::vector<double>>& matrix, 
            const size_t& s, 
            const size_t& n,
            const std::string& filename
        ) noexcept;
    }
}


namespace Check {
    std::tuple<double, double, double> count_R1_R2_Time(
        const std::vector<std::vector<double>>& matrix, 
        const PairedMatrix& reversedMatrix
    ) noexcept;
    //double matrixNorm(const std::vector<std::vector<double>>& matrix) noexcept;
}
