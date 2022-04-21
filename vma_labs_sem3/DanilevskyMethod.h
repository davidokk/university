#ifndef DANILEVSKYMETHOD_H
#define DANILEVSKYMETHOD_H

#include "LinearSystemSolver.h"

class DanilevskyMethod : public LinearSystemSolver {
 protected:
  explicit DanilevskyMethod(std::ostream& out) : LinearSystemSolver(out) {}
  std::vector<float> DanilevskyAlgorithm(bool print_matrix = true);

 private:
  void PrintSmtMatrix(const Matrix& m, int num);
};

class Lab5Task1 : public DanilevskyMethod {
  friend class Lab7Task1;
 public:
  explicit Lab5Task1(std::ostream& out) : DanilevskyMethod(out) {}
  void Solve() override;
 private:
  void GenerateMatrix() override;
  void ComputeSp();
};

#endif //DANILEVSKYMETHOD_H
