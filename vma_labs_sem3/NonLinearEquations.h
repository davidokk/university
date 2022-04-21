#ifndef NONLINEAREQUATIONS_H
#define NONLINEAREQUATIONS_H

#include <iostream>
#include <vector>

class NonLinearEquations {
 public:
  explicit NonLinearEquations(std::ostream& out) : out_(out) {}
  void SolvePolynomial(std::vector<float>& v);

 private:
  static double P2(float, float, double);
  static double P3(float, float, float, double);
  static double P4(float, float, float, float, double);

 protected:
  std::ostream& out_;
};

class Lab7Task1 : public NonLinearEquations {
 public:
  explicit Lab7Task1(std::ostream& out) : NonLinearEquations(out) {}
  void Solve();
 private:
  void PrintPolynomial(const std::vector<float>& p) const;
};


#endif //NONLINEAREQUATIONS_H
