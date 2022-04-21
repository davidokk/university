#include "TriDiagonalMatrixMethod.h"

void TriDiagonalMatrixMethod::TriDiagonalMatrixAlgorithm() {
  for (int i = 0; i < a.size(); ++i) {
    if (i == 0) {
      a[i][i + 1] = a[i][i + 1] / -a[i][i];
      b[i] = b[i] / a[i][i];
    } else if (i == a.size() - 1) {
      a[i][i] += a[i][i - 1] * a[i - 1][i];
      b[i] = (b[i] - a[i][i - 1] * b[i - 1]) / a[i][i];
    } else {
      a[i][i] += a[i][i - 1] * a[i - 1][i];
      a[i][i + 1] =  a[i][i + 1] / -a[i][i];
      b[i] = (b[i] - a[i][i - 1] * b[i - 1]) / a[i][i];
    }
  }
  for (int i = (int)b.size() - 2; i >= 0; --i)
    b[i] += a[i][i + 1] * b[i + 1];
}



void Lab3Task1::Solve() {
  GenerateMatrix();
  M = 1;
  GenerateValueColumn();
  out << "\nРазмерность матрицы " << a.size() << "\n";
  out << "Начальная матрица:\n";
  PrintMatrix();
  TriDiagonalMatrixAlgorithm();
  out << "Матрица после преобразования:\n";
  PrintMatrix(true);
  out << "Точное решение:\n";
  PrintColumn(x);
  out << "Приближенное решение:\n";
  PrintColumn(b);
  out << "Относительная погрешность " << GetAccuracy() * 100 << "%";
}
