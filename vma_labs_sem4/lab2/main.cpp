#include <iostream>
#include <cmath>
#include <iomanip>

int main() {

  const double eps = 1e-6;
  const double a = 1;
  const double b = 2;

  auto f = [](double x) { return exp(x) * cos(x) + log(x); };

  int n = 1;
  double prev;
  double cur = 0;

  while (true) {
    n *= 2;
    prev = cur;
    cur = 0;
    double h = (b - a) / n;

    auto xi = [=](double idx) { return a + h * idx; };
    for (int i = 1; i <= n; i++)
      cur += f(xi(i - 1)) + 4 * f(xi(i - 0.5)) + f(xi(i));
    cur *= h / 6;

    if (fabs(prev - cur) < eps)
      break;
  }

  std::cout << std::setprecision(12)<< "I" << n << " = " << cur;

  return 0;
}
