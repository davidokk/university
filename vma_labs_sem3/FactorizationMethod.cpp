#include "FactorizationMethod.h"

#include <vector>
#include <iomanip>

void FactorizationMethod::Factorization() {
  // декомпозиция
  int n = a.size();
  std::vector<float> t(n);
  for (int k = 0; k < n - 1; k++) {
    for (int i = k + 1; i < n; i++) {
      t[i] = a[i][k];
      a[i][k] /= a[k][k];
      for (int j = k + 1; j <= i; j++)
        a[i][j] -= a[i][k] * t[j];
    }
  }
  // Ly = b, L - нижнетреугольная
  for (int i = 0; i < n; i++)
    for (int j = 0; j < i; j++)
      b[i] -= a[i][j] * b[j];
  // Dz = y, D - диагональная
  for (int i = 0; i < n; i++)
    b[i] /= a[i][i];
  // Ltx = z, Lt - верхнетреугольная
  for (int i = n - 1; i >= 0; i--)
    for (int j = i + 1; j < n; j++)
      b[i] -= a[j][i] * b[j];
}

void FactorizationMethod::PrintLowerTriangularMatrix() const {
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a.size(); j++) {
      out << std::setprecision(2) << std::setw(7);
      if (i > j)
        out << a[i][j];
      else if (i < j)
        out << 0;
      else out << 1;
      out << " ";
    }
    out << std::endl;
  }
}

void FactorizationMethod::PrintDiagonalMatrix() const {
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < a.size(); j++)
      out << std::setprecision(5) << std::setw(7) << (i == j? a[i][j] : 0) << " ";
    out << std::endl;
  }
}



void Lab2Task1::Solve() {
  GenerateMatrix();
  GenerateValueColumn();
  SaveMatrix();
  out << "\nРазмерность матрицы " << a.size() << "\n";
  out << "При k = 0 начальная матрица:\n";
  PrintMatrix();
  Factorization();
  out << "Нижнетреугольная матрица L:\n";
  PrintLowerTriangularMatrix();
  out << "Диагональная матрица D:\n";
  PrintDiagonalMatrix();
  out << "Точное решение:\n";
  PrintColumn(x);
  out << "Приближенное решение:\n";
  PrintColumn(b);
  out << "Относительная погрешность " << GetAccuracy() * 100 << "%\n";
  Reload();
  SetK(3);
  Factorization();
  out << "При k = 3 относительная погрешность " << GetAccuracy() * 100 << "%\n";
}
