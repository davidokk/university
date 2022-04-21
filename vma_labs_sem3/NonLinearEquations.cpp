#include "NonLinearEquations.h"
#include "DanilevskyMethod.h"

#include <cmath>

using namespace std;

void NonLinearEquations::SolvePolynomial(std::vector<float>& p) {
  // 1
  bool sign = false;
  vector<pair<int, int>> periods;
  for (int x = -250; x < 251; ++x) {
    double value = P4(p[1], p[2], p[3], p[4], x);
    bool cur = value < 0;
    if (sign != cur) {
      periods.emplace_back(x - 1, x);
    }
    sign = cur;
  }
  out_ << "Отделение корней многочлена P(l)" << std::endl;
  for (auto el : periods) {
    out_ << "[" << el.first << ";" << el.second << "]\n";
  }

  // 1.1
  pair<int, int> period;
  sign = true;
  for (int x = -250; x < 251; ++x) {
    double value = P3(p[1], p[2], p[3], x);
    bool cur = value < 0;
    if (sign != cur) {
      period = {x -1, x};
    }
    sign = cur;
  }
  out_ << "Отделение корней многочлена P'(l)" << std::endl;
  out_ << "[" << period.first << ";" << period.second << "]" << std::endl;
  double x = period.first;
  while (P3(p[1], p[2], p[3], x) > 0.000001) {
    x = x - P3(p[1], p[2], p[3], x) / P2(p[1], p[2], x);
  }
  out_ << "Промежутки монотонности: (inf; " << x << "), (" << x << "; sup)" << std::endl;

  // 2
  out_ << "Приближенные вещественные корни методом Ньютона" << std::endl;
  for (auto el : periods) {
    x = el.first;
    while (fabs(P4(p[1], p[2], p[3], p[4], x)) > 0.00001) {
      double val = P4(p[1], p[2], p[3], p[4], x);
      x = x - val / P3(p[1], p[2], p[3], x);
    }
    out_ << "x = " <<  x << std::endl;
  }
  out_ << "Приближенные вещественные корни методом деления отрезка пополам" << std::endl;
  for (auto el : periods) {
    double x0 = el.first;
    double x1 = el.second;
    x = (x0 + x1) / 2;
    while (fabs(P4(p[1], p[2], p[3], p[4], x)) > 0.0001) {
      if (P4(p[1], p[2], p[3], p[4], x) * P4(p[1], p[2], p[3], p[4], x0) < 0) {
        x1 = x;
      } else {
        x0 = x;
      }
      x = (x0 + x1) / 2;
    }
    out_ << "x = " <<  x << "\n";
  }
}

void Lab7Task1::Solve() {
  Lab5Task1 lab5(out_);
  lab5.GenerateMatrix();
  vector<float> p = lab5.DanilevskyAlgorithm(false);
  lab5.PrintMatrix();
  p.insert(p.begin(), 1);
  PrintPolynomial(p);
  SolvePolynomial(p);
}

double NonLinearEquations::P4(float p1, float p2, float p3, float p4, double x) {
  return x * x * x * x + p1 * x * x * x + p2 * x * x + p3 * x + p4;
}

double NonLinearEquations::P3(float p1, float p2, float p3, double x) {
  return 4 * x * x * x + 3 * p1 * x * x + 2 * p2 * x + p3;
}

double NonLinearEquations::P2(float p1, float p2, double x) {
  return 12 * x * x + 6 * p1 * x + 2 * p2;
}

void Lab7Task1::PrintPolynomial(const std::vector<float>& p) const {
  out_ << "\nP(x) = ";
  int q = (int)p.size() - 1;
  bool first = true;
  for (float i : p) {
    if (!first) {
      if (i > 0)
        out_ << "+";
    }
    first = false;
    if (i != 1)
      out_ << i;
    if (q == 1)
      out_ << "x";
    else if (q != 0)
      out_ << "x^" << q;
    q--;
  }
  out_ << "\n\n";
}