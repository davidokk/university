#ifndef ITERATIVEMETHOD_H
#define ITERATIVEMETHOD_H

#include "LinearSystemSolver.h"

class IterativeMethod : public LinearSystemSolver {
 protected:
  explicit IterativeMethod(std::ostream& out) : LinearSystemSolver(out) {}

  void Jacobi();
  void Relaxation(float);
  void PrintIterationCount();

  int k = 0;
  const float EPS = 0.0001;
  const int K_MAX = 10000;
};

class Lab4Task12 : public IterativeMethod {
 public:
  explicit Lab4Task12(std::ostream& out) : IterativeMethod(out) {}
  void Solve() override;
 private:
  void GenerateMatrix() override;
};

#endif //ITERATIVEMETHOD_H
