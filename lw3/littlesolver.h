#pragma once

#include <list>
#include <utility>
#include <memory>
#include <cfloat>
#include <mutex>
#include <atomic>

template<typename T>
class Matrix;

class LittleSolver {
 public:
    using arclist = std::list<std::pair<size_t, size_t>>;
    using MatrixD = Matrix<double>;
    using MatrixPtr = std::unique_ptr<MatrixD>;

    LittleSolver(const Matrix<double> &m, double record = DBL_MAX);
    ~LittleSolver();

    void solve();

    std::list<size_t> getSolution() const;
    arclist getLastStep() const;
    arclist getBestStep() const;
    double getRecord() const;
    bool isSolved() const;

    LittleSolver(const LittleSolver&) = delete;
    LittleSolver &operator=(const LittleSolver&) = delete;

 private:
    void handleMatrix(const Matrix<double> &m, const arclist &arcs, double bottomLimit);
    double cost(const arclist &arcs) const;
    void candidateSolution(const arclist &arcs);
    void addInfinity(MatrixD &m);
    double subtractFromMatrix(MatrixD &m) const;
    std::list<std::pair<size_t, size_t>>  findBestZeros(const MatrixD &matrix) const;
    static double getCoefficient(const MatrixD &m, size_t r, size_t c);
    void logPath(const arclist &path);

    MatrixPtr _sourceMatrix;
    std::atomic<double> _record;
    arclist _arcs;
    std::list<size_t> _solution;
    arclist _lastStep;
    mutable std::mutex _mutex;
    double _infinity;
};
