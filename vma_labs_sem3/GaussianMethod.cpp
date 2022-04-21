#include "GaussianMethod.h"

using namespace std;

void GaussianMethod::Gauss(bool main) {
  // прямой ход
  int n = a.size();
  for (int k = 0; k < n - 1; k++) {
    // выбор главного элемента
    if (main)
      FindMaxAndSwap(k);
    for (int i = k + 1; i < n; i++) {
      float l = a[i][k] / a[k][k];
      b[i] -= l * b[k];
      for (int j = k; j < n; j++)
        a[i][j] -= l * a[k][j];
      a[i][k] = 0;
    }
  }
  // обратный ход
  for (int i = n - 1; i >= 0; i--) {
    for (int j = i + 1; j < n; j++)
      b[i] -= a[i][j] * b[j];
    b[i] /= a[i][i];
  }
}

void GaussianMethod::Gauss() { Gauss(false); }
void GaussianMethod::GaussWithMainElement() { Gauss(true); }

void GaussianMethod::FindMaxAndSwap(int k) {
  int pos = k;
  for (int i = k + 1; i < a.size(); i++)
    if (abs(a[pos][k]) < abs(a[i][k]))
      pos = i;
  swap(a[k], a[pos]);
  swap(b[k], b[pos]);
}



void Lab1Task1::Solve() {
  out << "\nЗадание 1\n\n";
  GenerateMatrix();
  GenerateValueColumn();
  SaveMatrix();
  out << "Размерность матрицы " << a.size() << "\n";
  out << "При k = 0 начальная матрица:\n";
  PrintMatrix();
  Gauss();
  out << "Матрица после прямого хода Гаусса:\n";
  PrintMatrix(true);
  out << "Точное решение: ";
  PrintColumn(x);
  out << "Приближенное решение: ";
  PrintColumn(b);
  out << "Относительная погрешность " << GetAccuracy() * 100 << "%\n";
  Reload();
  SetK(3);
  Gauss();
  out << "При k = 3 относительная погрешность " << GetAccuracy() * 100 << "%\n";
}

void Lab1Task2::Solve() {
  out << "\nЗадание 2\n\n";
  GenerateMatrix();
  GenerateValueColumn();
  SaveMatrix();
  out << "Размерность матрицы " << a.size() << "\n";
  Gauss();
  out << "Относительная погрешность при вычислении без выбора главного элемента " << GetAccuracy() * 100 << "%\n";
  Reload();
  GaussWithMainElement();
  out << "С выбором главного элемента " << GetAccuracy() * 100 << "%";
}