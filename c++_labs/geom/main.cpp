#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using Point = pair<double, double>;

const vector<int> dx{1, 1, 0, -1, -1, -1, 0, 1};
const vector<int> dy{0, -1, -1, -1, 0, 1, 1, 1};

namespace std {
Point& operator+=(Point& l, const Point& r) {
  l.first += r.first;
  l.second += r.second;
  return l;
}
Point& operator*=(Point& p, double a) {
  p.first *= a;
  p.second *= a;
  return p;
}
Point& operator/=(Point& p, double a) {
  return p *= 1 / a;
}
Point operator*(const Point& p, double a) {
  Point t = p;
  return t *= a;
}
Point operator/(const Point& p, double a) {
  Point t = p;
  return t /= a;
}
Point operator+(const Point& l, const Point& r) {
  Point t = l;
  return t += r;
}
}

Point next(Point p, int step) {
  return {p.first + dx[step], p.second + dy[step]};
}

Point center(Point a, Point b, Point c) {
  return (a + b + c) / 3;
}

double square(Point a, Point b, Point c) {
  return ((b.first - a.first) * (c.second - a.second) - (b.second - a.second) * (c.first - a.first)) / 2.0;
}

int main() {

  cout << "Enter number of steps: ";
  int n;
  cin >> n;

  cout << "Enter" << n << " steps" << endl;
  vector<Point> a{{0, 0}};
  for (int i = 0; i < n; i++) {
    int x; cin >> x;
    a.push_back(next(a.back(), x));
  }

  if (a.back() != a.front()) {
    cout << "Wrong shape";
    return 1;
  }

  a.pop_back();
  double total_s = 0;
  Point c{0, 0};
  for (int i = 1; i < n - 1; i++) {
    double s = square(a[0], a[i], a[i + 1]);
    c += center(a[0], a[i], a[i + 1]) * s;
    total_s += s;
  }
  c /= total_s;

  cout << c.first << " " << c.second;

  return 0;
}
