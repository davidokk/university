#ifndef LAB_H
#define LAB_H

#include "AllMethods.h"

#include <fstream>
#include <ctime>

#define LAB(number) Lab##number lab##number; \
                     lab##number.Solve()

class Lab {
 public:
  explicit Lab(int number) : lab_number(number) {
    srand(time(nullptr));
    out = std::move(std::ofstream("lab" + std::to_string(lab_number) + ".txt"));
    out << "Лабораторная работа №" << lab_number << ". Гутько Давид\n";
  }
  virtual void Solve() = 0;

 protected:
  int lab_number;
  std::ofstream out;
};

class Lab1 : Lab {
 public:
  Lab1() : Lab(1) { out << "Решение СЛАУ методом Гаусса\n"; }
  void Solve() override {
    Lab1Task1 t1(out);
    t1.Solve();
    Lab1Task2 t2(out);
    t2.Solve();
  }
};

class Lab2 : Lab {
 public:
  Lab2() : Lab(2) { out << "Решение СЛАУ с помощью LDU разложения\n"; }
  void Solve() override {
    Lab2Task1 t1(out);
    t1.Solve();
  }
};

class Lab3 : Lab {
 public:
  Lab3() : Lab(3) { out << "Решение СЛАУ методом прогонки\n"; }
  void Solve() override {
    Lab3Task1 t1(out);
    t1.Solve();
  }
};

class Lab4 : Lab {
 public:
  Lab4() : Lab(4) { out << "Итерационные методы решения СЛАУ\n"; }
  void Solve() override {
    Lab4Task12 t12(out);
    t12.Solve();
  }
};

class Lab5 : Lab {
 public:
  Lab5() : Lab(5) { out << "Метод Данилевского\n"; }
  void Solve() override {
    Lab5Task1 t1(out);
    t1.Solve();
  }
};

class Lab6 : Lab {
 public:
  Lab6() : Lab(6) { out << "Итерационный степенной метод\n"; }
  void Solve() override {
    Lab6Task1 t1(out);
    t1.Solve();
  }
};

class Lab7 : Lab {
 public:
  Lab7() : Lab(7) { out << "Методы простой итерации и Ньютона решения нелинейных уравнений\n"; }
  void Solve() override {
    Lab7Task1 t1(out);
    t1.Solve();
  }
};

#endif //LAB_H
