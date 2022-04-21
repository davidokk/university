#include "LinearSystemSolver.h"

#include <iomanip>
#include <cmath>
#include <sstream>
using namespace std;

void LinearSystemSolver::PrintMatrix(bool round) const {
  for (const auto& row : a) {
    for (const auto& i : row) {
      if (round)
        out << setprecision(3);
      out << setw(7) << i << " ";
    }
    out << std::endl;
  }
}

void LinearSystemSolver::PrintColumn(const Column& c) const {
  for (const auto& i : c)
    out << setprecision(5) << i << " ";
  out << endl;
}

float LinearSystemSolver::GetAccuracy() const {
  float mx = abs(x[0] - b[0]);
  for (int i = 0; i < x.size(); i++)
    mx = max(mx, abs(x[i] - b[i]));
  return mx / x.back();
}

void LinearSystemSolver::SetK(int nk) {
  copy_a[0][0] += pow(10, -nk) - pow(10, -K);
  a[0][0] = copy_a[0][0];
  GenerateValueColumn();
  copy_b = b;
}

void LinearSystemSolver::Reload() { a = copy_a; b = copy_b; }

void LinearSystemSolver::SaveMatrix() { copy_a = a; copy_b = b; }

Matrix MultiplicationMatrix(const Matrix& l, const Matrix& r) {
  Matrix result(l.size(), Column(r[0].size()));
  for (int i = 0; i < result.size(); ++i)
    for (int j = 0; j < result[0].size(); ++j)
      for (int s = 0; s < l[0].size(); ++s)
        result[i][j] += l[i][s] * r[s][j];
  return result;
}

Matrix TransposeMatrix(const Matrix& m) {
  Matrix t(m[0].size(), Column(m.size()));
  for (int i = 0; i < m.size(); i++)
    for (int j = 0; j < m[0].size(); j++)
      t[j][i] = m[i][j];
  return t;
}

std::vector<float> MatrixMultiplyByVector(const Matrix& l, const std::vector<float>& r) {
  return TransposeMatrix(MultiplicationMatrix(l, TransposeMatrix(vector<Column>{r})))[0];
}
