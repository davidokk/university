#ifndef TRIDIAGONALMATRIXMETHOD_H
#define TRIDIAGONALMATRIXMETHOD_H

#include "LinearSystemSolver.h"

class TriDiagonalMatrixMethod : public LinearSystemSolver {
 protected:
  explicit TriDiagonalMatrixMethod(std::ostream& output) : LinearSystemSolver(output) {}

  void TriDiagonalMatrixAlgorithm();
};

class Lab3Task1 : public TriDiagonalMatrixMethod {
 public:
  explicit Lab3Task1(std::ostream& output) : TriDiagonalMatrixMethod(output) {}
  void Solve() override;
 private:
  void GenerateMatrix() override;
};

#endif //TRIDIAGONALMATRIXMETHOD_H
