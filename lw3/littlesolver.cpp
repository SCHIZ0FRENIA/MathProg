#include <iostream>

#include "littlesolver.h"
#include "matrix.hpp"

using std::list;
using std::vector;
using std::pair;
using std::mutex;
using std::lock_guard;

LittleSolver::LittleSolver(const Matrix<double> &m, double record)
    :_record(record), _infinity(0) {
    _sourceMatrix = std::make_unique<MatrixD>(m);
    for (size_t i = 0; i < m.size(); i++)
        for (size_t j = i + 1; j < m.size(); j++)
            _infinity += (m.item(i, j) + m.item(j, i));
    for (size_t i = 0; i < _sourceMatrix->size(); i++)
        _sourceMatrix->item(i, i) = _infinity;
}

LittleSolver::~LittleSolver() {}

void LittleSolver::solve() {
    handleMatrix(*_sourceMatrix, arclist(), 0);
    _solution.push_back(0);
    while (!_arcs.empty()) {
        auto iter = _arcs.begin();
            while (iter != _arcs.end()) {
                if (iter->first == _solution.back()) {
                    _solution.push_back(iter->second);
                    iter = _arcs.erase(iter);
                }
                else
                    ++iter;
        }
    }
}

std::list<size_t> LittleSolver::getSolution() const {
    return _solution;
}

LittleSolver::arclist LittleSolver::getLastStep() const {
    std::lock_guard<std::mutex> g(_mutex);
    return _lastStep;
}

LittleSolver::arclist LittleSolver::getBestStep() const {
    std::lock_guard<std::mutex> g(_mutex);
    return _arcs;
}

double LittleSolver::getRecord() const {
    return _record;
}

bool LittleSolver::isSolved() const {
    return _solution.size() != 1;
}

void LittleSolver::handleMatrix(const Matrix<double> &m, const arclist &path, double bottomLimit) {
    if (m.size() < 2)
        throw std::logic_error("Matrix smaller than 2x2");

    if (m.size() == 2) {
        logPath(path);
        int i = m.item(0, 0) >= _infinity ? 1 : 0;
        arclist result(path);
        result.emplace_back(m.rowIndex(0), m.columnIndex(i));
        result.emplace_back(m.rowIndex(1), m.columnIndex(1 - i));
        candidateSolution(result);
        return;
    }


    Matrix<double> matrix(m);
    bottomLimit += subtractFromMatrix(matrix);
    if (bottomLimit > _record) {
        logPath(path);
        return;
    }

    auto zeros = findBestZeros(matrix);

    auto edge = zeros.front();
    auto newMatrix(matrix);
    newMatrix.removeRowColumn(edge.first, edge.second);
    auto newPath(path);
    newPath.emplace_back(matrix.rowIndex(edge.first),
                         matrix.columnIndex(edge.second));
    addInfinity(newMatrix);
    handleMatrix(newMatrix, newPath, bottomLimit);

    newMatrix = matrix;
    newMatrix(edge.first, edge.second) = _infinity + 1;
    handleMatrix(newMatrix, path, bottomLimit);
}

double LittleSolver::cost(const arclist &arcs) const {
    double result(0);
    for (auto &iter : arcs)
        result += _sourceMatrix->item(iter.first, iter.second);

    return result;
}

void LittleSolver::candidateSolution(const arclist &arcs) {
    double curCost;
    if (_record < (curCost = cost(arcs))) {
        return;
    }
    std::lock_guard<std::mutex> g(_mutex);
    _record = curCost;
    _arcs = arcs;
}

void LittleSolver::addInfinity(Matrix<double> &m) {
    vector<bool> infRow(m.size(), false), infColumn(m.size(), false);
    for (size_t i = 0; i < m.size(); i++)
        for (size_t j = 0; j < m.size(); j++)
            if (m.item(i, j) == _infinity) {
                infRow[i] = true;
                infColumn[j] = true;
            }
    size_t notInf;
    for (size_t i = 0; i < infRow.size(); i++)
        if (!infRow[i]) {
            notInf = i;
            break;
        }

    for (size_t j = 0; j < infColumn.size(); j++)
        if (!infColumn[j]) {
            m.item(notInf, j) = _infinity;
            break;
        }
}

double LittleSolver::subtractFromMatrix(MatrixD &m) const {
    double substractSum = 0;
    vector<double> minRow(m.size(), DBL_MAX),
        minColumn(m.size(), DBL_MAX);
    for (size_t i = 0; i < m.size(); ++i) {
        for (size_t j = 0; j < m.size(); ++j)
            if (m(i, j) < minRow[i])
                minRow[i] = m(i, j);

        for (size_t j = 0; j < m.size(); ++j) {
            if (m(i, j) < _infinity) {
                m(i, j) -= minRow[i];
            }
            if ((m(i, j) < minColumn[j]))
                minColumn[j] = m(i, j);
        }
    }

    for (size_t j = 0; j < m.size(); ++j)
        for (size_t i = 0; i < m.size(); ++i)
            if (m(i, j) < _infinity) {
                m(i, j) -= minColumn[j];
            }

    for (auto i : minRow)
        substractSum += i;

    for (auto i : minColumn)
        substractSum += i;

    return substractSum;
}

list<pair<size_t, size_t>> LittleSolver::findBestZeros(const MatrixD &matrix) const {
    list<pair<size_t, size_t>> zeros;
    list<double> coeffList;

    double maxCoeff = 0;
    for (size_t i = 0; i < matrix.size(); ++i)
        for (size_t j = 0; j < matrix.size(); ++j)
            if (!matrix(i, j)) {
                zeros.emplace_back(i, j);
                coeffList.push_back(getCoefficient(matrix, i, j));
                maxCoeff = std::max(maxCoeff, coeffList.back());
            }
    { 
        auto zIter = zeros.begin();
        auto cIter = coeffList.begin();
        while (zIter != zeros.end()) {
            if (*cIter != maxCoeff) {
                zIter = zeros.erase(zIter);
                cIter = coeffList.erase(cIter);
            }
            else {
                ++zIter;
                ++cIter;
            }
        }
    }

    return zeros;
}

double LittleSolver::getCoefficient(const MatrixD &m, size_t r, size_t c) {
    double rmin, cmin;
    rmin = cmin = DBL_MAX;
    for (size_t i = 0; i < m.size(); ++i) {
        if (i != r)
            rmin = std::min(rmin, m(i, c));
        if (i != c)
            cmin = std::min(cmin, m(r, i));
    }

    return rmin + cmin;
}

void LittleSolver::logPath(const LittleSolver::arclist &path) {
    std::lock_guard<std::mutex> g(_mutex);
    _lastStep = path;
}
