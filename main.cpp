#include "header.hpp"

int main(int argc, char* argv[]) {
    clock_t start;//, end;
    start = clock();
    std::tuple<double, double, double> r1r2time;
    //double secs;
    bool stop = false;
    if (argc > 5 || argc < 4) stop = true;
    const std::string filename(argc == 5 ? argv[4] : "");
    int ni, ri, si;
    size_t n, r, s;
    std::vector<std::vector<double>> matrix;
    PairedMatrix pairedMatrix;
    if (stop) {
        //end = clock();
        goto wrongdata;
    }
    try {
        ni = std::stoi(argv[1]);
        ri = std::stoi(argv[2]);
        si = std::stoi(argv[3]);
        if (si == 0 && argc == 4) {
            //end = clock();
            goto wrongdata;
        }
    } catch (std::exception const& e) {
        //end = clock();
        goto wrongdata;
    }
    if (ni < ri || ri < 1 || ni < 1 || si < 0 || si > 4) {
        //end = clock();
        goto wrongdata;
    }
    n = (size_t)ni;
    r = (size_t)ri;
    s = (size_t)si;
    if (!MatrixBuild::Build::matrixMake(matrix, s, n, filename) || n < r) {
        //end = clock();
        goto wrongdata;
    }
    pairedMatrix = PairedMatrix(matrix);
    if (!RowWork::Solver::Solve(pairedMatrix)) {
        std::cout << "Matrix can't be inversed\n";
        r1r2time = std::make_tuple(-1, -1, 0);
        goto wrongdata;
    }
    for (size_t i = 0; i < pairedMatrix.pairedRows.size(); ++i) {
        pairedMatrix.pairedRows[i]
            .Divide(
                pairedMatrix
                .pairedRows[i]
                .mainMatrixRow[i]
            );
    }
    std::cout << "Reversed matrix:\n";
    for (const auto& row : pairedMatrix.pairedRows) {
        for (const auto& element : row.helpMatrixRow) {
            printf("%10.3e ", element);
        }
        std::cout << "\n";
    }

    r1r2time = Check::count_R1_R2_Time(matrix, pairedMatrix);
    printf(
        "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
        argv[0], 
        228, 
        std::get<0>(r1r2time), 
        std::get<1>(r1r2time), 
        (double)(clock() - start) / CLOCKS_PER_SEC, 
        std::get<2>(r1r2time),
        (int)s,
        (int)n
    );
    return 0;
wrongdata:
    r1r2time = std::make_tuple(-1, -1, 0);
    printf(
        "%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",
        argv[0], 
        228, 
        std::get<0>(r1r2time), 
        std::get<1>(r1r2time), 
        (double)(clock() - start) / CLOCKS_PER_SEC, 
        std::get<2>(r1r2time),
        (int)s,
        (int)n
    );
    return 0;
}
