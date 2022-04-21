#ifndef FACTORIZATIONMETHOD_H
#define FACTORIZATIONMETHOD_H

#include "LinearSystemSolver.h"

class FactorizationMethod : public LinearSystemSolver {
 protected:
  explicit FactorizationMethod(std::ostream& output) : LinearSystemSolver(output) {}

  void Factorization();

  void PrintLowerTriangularMatrix() const;
  void PrintDiagonalMatrix() const;
};

class Lab2Task1 : public FactorizationMethod {
 public:
  explicit Lab2Task1(std::ostream& output) : FactorizationMethod(output) {}
  void Solve() override;
 private:
  void GenerateMatrix() override;
};


#endif //FACTORIZATIONMETHOD_H
