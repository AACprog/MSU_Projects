#include "header.hpp"


void FileWork::matrixRead(
    std::vector<std::vector<double>>& matrix, 
    const std::string& filename
) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Incorrect file\n";
        return;
    }
    std::vector<std::string> rows;
    std::string line;
    while (std::getline(file, line)) rows.push_back(line);
    file.close();
    for (const auto& i : rows) matrix.push_back(Parser::parseRow(i));
    return;
}


std::vector<double> FileWork::Parser::parseRow(const std::string& row) {
    std::vector<double> parsed;
    std::regex r(R"(-?\d+(\.\d+)?([eE]-?\d+(\.\d+)?)?)");
    auto rowBegin = std::sregex_iterator(row.begin(), row.end(), r);
    auto rowEnd = std::sregex_iterator();
    for (std::sregex_iterator i = rowBegin; i != rowEnd; i++) {
        std::smatch match = *i;
        std::string match_str = match.str();
        try {
            parsed.push_back(std::stod(match_str));
        } catch (std::exception const& e) {
            std::cout << "String is incorrect\n"; 
        }
    }
    return parsed;
}


bool FileWork::Checker::checkMatrix(const std::vector<std::vector<double>>& matrix, const int& n) {
    if (matrix.size() != (size_t)n) return false;
    for (const auto& row : matrix) {
        if (row.size() != (size_t)n) return false;
    }
    return true;
}
