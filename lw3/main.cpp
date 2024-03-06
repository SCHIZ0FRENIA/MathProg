#include <iostream>
#include "matrix.hpp"
#include "bruteforcesolver.cpp"
#include "littlesolver.cpp"


int main(int argc, char *argv[])
{    
    Matrix<double> m(5);

    m(0, 0) = std::numeric_limits<double>::infinity();
    m(0, 1) = 2;
    m(0, 2) = 22;
    m(0, 3) = std::numeric_limits<double>::infinity();
    m(0, 4) = 1;

    m(1, 0) = 1;
    m(1, 1) = std::numeric_limits<double>::infinity();
    m(1, 2) = 16;
    m(1, 3) = 67;
    m(1, 4) = 83;

    m(2, 0) = 3;
    m(2, 1) = 3;
    m(2, 2) = std::numeric_limits<double>::infinity();
    m(2, 3) = 86;
    m(2, 4) = 50;

    m(3, 0) = 18;
    m(3, 1) = 57;
    m(3, 2) = 4;
    m(3, 3) = std::numeric_limits<double>::infinity();
    m(3, 4) = 3;

    m(4, 0) = 92;
    m(4, 1) = 67;
    m(4, 2) = 52;
    m(4, 3) = 14;
    m(4, 4) = std::numeric_limits<double>::infinity();

    m.printEndl();

    BruteforceSolver solver(m);

    solver.solve();

    std::list<size_t> solution = solver.getSolution();
    double record = solver.getRecord();

    for (const auto &iter : solution)
    std::cout << iter << " ";
    std::cout << "\nRecord: " << record << std::endl;

     LittleSolver lsolver(m, DBL_MAX);

    // Solve the problem
    lsolver.solve();

    // Print the solution and the record
    std::cout << "Solution: ";
    for (const auto &i : lsolver.getSolution()) {
        std::cout << i << " ";
    }
    std::cout << std::endl << "Record: " << lsolver.getRecord() << std::endl;

    return 0;
}
