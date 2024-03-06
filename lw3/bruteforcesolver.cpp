#include "bruteforcesolver.h"

using std::list;
using std::mutex;
using std::lock_guard;

BruteforceSolver::BruteforceSolver(const Matrix<double> &m)
    :_matrix(m), _record(DBL_MAX) {
    _lastSolution.resize(m.size());
    for (size_t i = 0; i < m.size(); ++i)
        _lastSolution[i] = i;

    candidateSolution(_lastSolution);
}

void BruteforceSolver::solve() {
    if (_matrix.size() <=2)
        throw "matrix smaller than 2x2";

    while (step());
}

bool BruteforceSolver::step() {
    size_t n = _lastSolution.size() - 1;
    int j = n - 2;
    while (j != -1 && _lastSolution[j] >= _lastSolution[j + 1]) j--;
        if (j == -1)
            return false; 
    int k = n - 1;
    while (_lastSolution[j] >= _lastSolution[k])
        k--;
    std::swap(_lastSolution[j], _lastSolution[k]);
    int l = j + 1, r = n - 1; 
    while (l<r)
        std::swap(_lastSolution[l++], _lastSolution[r--]);
    candidateSolution(_lastSolution);
    return true;
}

std::list<size_t> BruteforceSolver::getSolution() const {
    return _solution;
}

std::list<size_t> BruteforceSolver::getLastStep() const {
    lock_guard<mutex> g(_mutex);
    list<size_t> solution;
    for (const auto &iter : _lastSolution)
        solution.push_back(iter);
    solution.push_back(solution.front());
    return solution;
}

double BruteforceSolver::getRecord() const {
    return _record;
}

double BruteforceSolver::cost(std::vector<size_t> solution) const {
    double result = 0;
    for (size_t i = 1; i < solution.size(); ++i)
        result += _matrix(solution[i - 1], solution[i]);
    result += _matrix(solution.back(), solution.front());
    return result;
}

void BruteforceSolver::candidateSolution(std::vector<size_t> solution) {
    double curCost = cost(solution);
    if (curCost >= _record)
        return;
    lock_guard<mutex> g(_mutex);
    _record = curCost;
    _solution.clear();
    for (const auto &iter : solution)
        _solution.push_back(iter);
    _solution.push_back(solution.front());
}
