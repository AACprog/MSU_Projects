#include "header.hpp"


bool SolveFuncs::Solve::Solve(std::vector<LinearEquation>& system, const double& norm, const size_t& p) noexcept {
    if(system.size() < 2) return true;
    const auto findMaxAbs = [&system]()->std::tuple<size_t, size_t> {
        double maxAbs = 0.0;
        size_t row = 0;
        size_t col = 0;
        for (size_t i = 0; i < system.size(); ++i) {
            for (size_t j = 0; j < i; ++j) {
                if (std::abs(system[i].VariableCoefficients[j]) > maxAbs) {
                    maxAbs = std::abs(system[i].VariableCoefficients[j]);
                    row = i;
                    col = j;
                }
            }
        }
        return std::make_tuple(row, col);
    };
    const auto eliminateUnder = [&system, &p](const size_t& n) {
        auto eliminate = [&system, &n](size_t i) {
            system[i] -= system[n].Multiply(system[i].VariableCoefficients[n]);
        };

        for (size_t i = n + 1; i < system.size(); i += p) {
            std::vector<std::thread> threads;
            for (size_t j = 0; j < p && i + j < system.size(); ++j) {
                threads.emplace_back(
                    std::thread(
                        eliminate,
                        i + j
                    )
                );
            }
            for (auto& thread : threads) thread.join();
        }
    };
    const auto check = [&system, &norm]()->bool{
        for (const auto& eq : system) {
            bool isZeros = true;
            for (const auto& var : eq.VariableCoefficients) {
                if (std::abs(var) > 10e-16 * norm) {
                    isZeros = false;
                    break;
                }
            }
            if (isZeros && std::abs(eq.FreeCoefficient) > 10e-16 * norm) return false;
        }
        return true;
    };
    while (true) {
        auto findres = findMaxAbs();
        size_t row = std::get<0>(findres);
        size_t col = std::get<1>(findres);
        double res = system[row].VariableCoefficients[col];
        
        if (std::abs(system[row].VariableCoefficients[col]) < 10e-16 * norm || (row == 0 && col == 0)) {
            break;;
        }
        system[row].Divide(res);
        std::swap(system[row], system[col]);
        eliminateUnder(col);
    }
    if (!check()) return false;
    for (size_t i = 0; i < system.size(); ++i) {
        if (std::abs(system[i].VariableCoefficients[i]) > norm * 10e-16) {
            double tmp = system[i].VariableCoefficients[i];
            system[i].Divide(tmp);
        }
    }
    return true;
}


std::vector<double> SolveFuncs::Answer::GetAnswer(const std::vector<LinearEquation>& system, const double& norm) noexcept {
    std::vector<double> ans(system.size(), 0.0);
    for (size_t i = system.size() - 1;; --i) {
        if (std::abs(system[i].VariableCoefficients[i]) > norm * 1e-16) {
            ans[i] = system[i].FreeCoefficient;
            for (size_t j = system.size(); j > i; --j) {
                ans[i] -= ans[j] * system[i].VariableCoefficients[j];
            }
        }
        if (i == 0) break;
    }
    return ans;
}