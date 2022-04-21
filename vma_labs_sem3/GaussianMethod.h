#ifndef GAUSSIANMETHOD_H
#define GAUSSIANMETHOD_H

#include "LinearSystemSolver.h"

class GaussianMethod : public LinearSystemSolver {
 protected:
  explicit GaussianMethod(std::ostream& output) : LinearSystemSolver(output) {}

  void Gauss();
  void GaussWithMainElement();
  void FindMaxAndSwap(int);

 private:
  void Gauss(bool);
};

class Lab1Task1 : public GaussianMethod {
 public:
  explicit Lab1Task1(std::ostream& output) : GaussianMethod(output) {}
  void Solve() override;
 private:
  void GenerateMatrix() override;
};

class Lab1Task2 : public GaussianMethod {
 public:
  explicit Lab1Task2(std::ostream& output) : GaussianMethod(output) {}
  void Solve() override;
 private:
  void GenerateMatrix() override;
};

#endif //GAUSSIANMETHOD_H
