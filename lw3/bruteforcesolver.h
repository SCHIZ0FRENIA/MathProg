#pragma once

#include <list>
#include <mutex>
#include <atomic>

#include "matrix.hpp"

class BruteforceSolver {
public:
    using MatrixD = Matrix<double>;
    BruteforceSolver(const Matrix<double> &m);

    void solve();
    bool step();

    std::list<size_t> getSolution() const;
    std::list<size_t> getLastStep() const;
    double getRecord() const;

    BruteforceSolver(const BruteforceSolver&) = delete;
    BruteforceSolver &operator=(const BruteforceSolver&) = delete;

private:
    double cost(std::vector<size_t> solution) const;
    void candidateSolution(std::vector<size_t> solution);

    MatrixD _matrix;
    std::atomic<double> _record;
    std::list<size_t> _solution;
    std::vector<size_t> _lastSolution;
    mutable std::mutex _mutex;
};
