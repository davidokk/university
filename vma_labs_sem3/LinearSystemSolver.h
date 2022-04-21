#ifndef LINEARSYSTEMSOLVER_H
#define LINEARSYSTEMSOLVER_H

#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<float>>;
using Column = std::vector<float>;

Matrix MultiplicationMatrix(const Matrix& l, const Matrix& r);
Matrix TransposeMatrix(const Matrix& m);
std::vector<float> MatrixMultiplyByVector(const Matrix& l, const std::vector<float>& r);

class LinearSystemSolver {
 protected:
  explicit LinearSystemSolver(std::ostream& output) : out(output) {}
  virtual void Solve() = 0;

  virtual void GenerateMatrix() = 0;
  void GenerateValueColumn();

  float GetAccuracy() const;

  void PrintMatrix(bool round = false) const;
  void PrintColumn(const Column&) const;

  void SaveMatrix();
  void SetK(int nk);
  void Reload();

 protected:
  int K = 0;
  int M = 3;

  Matrix a, copy_a;
  Column b, copy_b; // столбец значений
  Column x; // точное решение
  std::ostream& out;
};

#endif //LINEARSYSTEMSOLVER_H
