#include "IterativeMethod.h"

#include <vector>
#include <cmath>
using namespace std;

void IterativeMethod::Jacobi() {
  vector<float> prev(a.size(), 0);
  vector<float> next(a.size(), 0);
  for (k = 0; k <= K_MAX; ++k) {
    float mx = 0;
    for (int i = 0; i < a.size(); ++i) {
      next[i] = b[i];
      for (int j = 0; j < a.size(); ++j)
        if (i != j)
          next[i] -= a[i][j] * prev[j];
      next[i] /= a[i][i];
      mx = max(mx, abs(next[i] - prev[i]));
    }
    prev = next;
    if (mx < EPS)
       break;
  }
  b = prev;
}

void IterativeMethod::Relaxation(float omega) {
  vector<float> t(a.size(), 0);
  for (k = 0; k <= K_MAX; ++k) {
    float mx = 0;
    for (int i = 0; i < a.size(); ++i) {
      float p = b[i];
      for (int j = 0; j < a.size(); ++j)
        if (i != j)
          p -= a[i][j] * t[j];
      p *= omega / a[i][i];
      p += (1 - omega) * t[i];
      mx = max(mx, abs(p - t[i]));
      t[i] = p;
    }
    if (mx < EPS)
      break;
  }
  b = t;
}

void Lab4Task12::Solve() {
  GenerateMatrix();
  GenerateValueColumn();
  SaveMatrix();
  out << "\nЗадание 1. Метод Якоби\n";
  out << "\nРазмерность матрицы " << a.size() << "\n";
  out << "Начальная матрица:\n";
  PrintMatrix();
  Jacobi();
  PrintIterationCount();
  out << "Приближенный вектор решений:\n";
  PrintColumn(b);
  out << "Точное решение: ";
  PrintColumn(x);
  Reload();
  out << "\nЗадание 2. Метод релаксации\n";
  out << "Матрица из задания 1\n";
  vector<float> w({0.5, 1, 1.5});
  for (auto i : w) {
    out << "\nw = " << i;
    Relaxation(i);
    out << "\nПриближенный вектор решений:\n";
    PrintColumn(b);
    PrintIterationCount();
    Reload();
  }
}

void IterativeMethod::PrintIterationCount() {
  if (k > K_MAX)
    out << "Был превышен максимум итераций K_MAX = " << K_MAX << "\n";
  out << "Ответ получен на итерации " << k - 1 << "\n";
}