#ifndef POWERMETHOD_H
#define POWERMETHOD_H

#include "LinearSystemSolver.h"

class PowerMethod : public LinearSystemSolver {
 protected:
  explicit PowerMethod(std::ostream& out) : LinearSystemSolver(out) {}
  void IterativePowerAlgorithm();

 private:
  static float ScalarMultiplication(const std::vector<float>&, const std::vector<float>&);
  static std::vector<float> Difference(const std::vector<float>&, float, const std::vector<float>&);
  static int MaxNorm(const std::vector<float>& v);
};

class Lab6Task1 : public PowerMethod {
 public:
  Lab6Task1(std::ostream& out) : PowerMethod(out) {}
  void Solve() override;
 private:
  void GenerateMatrix() override;
};

#endif //POWERMETHOD_H
