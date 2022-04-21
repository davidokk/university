#include "AllMethods.h"

#include <cmath>
using namespace std;

int RandInRange(int l, int r) { return l + rand() % (r - l + 1); }

void Lab1Task1::GenerateMatrix() {
  int n = RandInRange(12, 15);
  a.resize(n);
  for (int i = 0; i < n; i++) {
    a[i].resize(n);
    int sum = 0;
    for (int j = 0; j < n; j++)
      sum += (a[i][j] = i != j ? RandInRange(-4, 0) : 0);
    a[i][i] = -sum;
  }
  a[0][0] += pow(10, -K);
}

void Lab1Task2::GenerateMatrix() {
  int n = RandInRange(0, 1) ? 500 : 1000;
  a.resize(n);
  for (int i = 0; i < n; i++) {
    a[i].resize(n);
    for (int j = 0; j < n; j++)
      a[i][j] = RandInRange(-100, 100);
  }
}

void Lab2Task1::GenerateMatrix() {
  int n = RandInRange(10, 12);
  a.resize(n);
  for (int i = 0; i < n; i++) {
    a[i].resize(n);
    int sum = 0;
    for (int j = 0; j < n; j++)
      sum += (a[i][j] = i < j ? RandInRange(-4, 0) : a[j][i]);
    a[i][i] = -sum;
  }
  a[0][0] += pow(10, -K);
}

void Lab3Task1::GenerateMatrix() {
  K = 3;
  int n = RandInRange(10, 12);
  a.resize(n);
  for (int i = 0; i < n; i++) {
    a[i].resize(n);
    a[i][i] = M + K + i - 1;
    if (i > 0) {
      a[i - 1][i] = M - 2 + i;
      a[i][i - 1] = -K;
    }
  }
  a[0][0] = M;
}

void Lab4Task12::GenerateMatrix() {
  int n = RandInRange(10, 12);
  a.resize(n);
  for (int i = 0; i < n; i++) {
    a[i].resize(n);
    int sum = 0;
    for (int j = 0; j < n; j++)
      sum += (a[i][j] = i != j ? RandInRange(-4, 0) : 0);
    a[i][i] = -sum;
  }
  ++a[0][0];
}

void Lab5Task1::GenerateMatrix() {
  int n = 4;
  a.resize(n);
  for (auto& row : a) {
    row.resize(n);
    for (auto& el : row)
      el = RandInRange(-50, 50);
  }
}

void Lab6Task1::GenerateMatrix() {
  int n = RandInRange(10, 12);
  a.resize(n);
  for (int i = 0; i < n; i++) {
    a[i].resize(n);
    int sum = 0;
    for (int j = 0; j < n; j++)
      sum += (a[i][j] = i < j ? RandInRange(-4, 0) : a[j][i]);
    a[i][i] = -sum;
  }
  a[0][0] += pow(10, -K);
}



void LinearSystemSolver::GenerateValueColumn() {
  x.clear();
  x.resize(a.size());
  for (int i = 0; i < a.size(); i++)
    x[i] = i + M;
  b.clear();
  b.resize(a.size());
  for (int i = 0; i < a.size(); i++)
    for (int j = 0; j < a.size(); j++)
      b[i] += a[i][j] * x[j];
}
