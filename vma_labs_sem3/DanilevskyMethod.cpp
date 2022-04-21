#include "DanilevskyMethod.h"

#include <iomanip>
#include <algorithm>

using namespace std;

std::vector<float> DanilevskyMethod::DanilevskyAlgorithm(bool print_matrix) {
  for (size_t n = a.size() - 1; n > 0; --n) {
    Matrix m(a.size(), Column(a.size())), m1(m);
    for (int i = 0; i < a.size(); ++i) {
      m[i][i] = 1;
      m[n - 1][i] = -a[n][i] / a[n][n - 1];
      m1[i][i] = 1;
      m1[n - 1][i] = a[n][i];
    }
    m[n - 1][n - 1] = 1 / a[n][n - 1];

    if (print_matrix)
      PrintSmtMatrix(m, n);
    a = std::move(MultiplicationMatrix(MultiplicationMatrix(m1, a), m));
  }
  return a[0];
}

void DanilevskyMethod::PrintSmtMatrix(const Matrix& m, int num) {
  out << "Матрица M" << num << std::endl;
  for (const auto& row : m) {
    for (const auto& el : row)
      out << setprecision(3) << setw(7) << el << " ";
    out << endl;
  }
}

void Lab5Task1::ComputeSp() {
  out << "\np1 = " << a[0][0] << "\n";
  Reload();
  int sum = 0;
  bool first = true;
  out << "Sp(A) = ";
  for (int i = 0; i < a.size(); ++i) {
    if (!first)
      out << (a[i][i] > 0 ? " + " : " - ");
    sum += a[i][i];
    first = false;
    out << (i == 0 ? a[i][i] : abs(a[i][i]));
  }
  out << " = " << sum << " = p1";
}

void Lab5Task1::Solve() {
  GenerateMatrix();
  GenerateValueColumn();
  SaveMatrix();
  out << "\nМатрица А\n";
  PrintMatrix();
  DanilevskyAlgorithm();
  out << "Матрица F\n";
  PrintMatrix();
  ComputeSp();
}