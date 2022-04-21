#include "point.h"
#include <iostream>

Point::Point(double x_, double y_) : x(x_), y(y_) {}

Proxy Point::operator+(const Point& r) const {
  Point* p = r.Clone();
  p->x += x;
  p->x /= 2;
  p->y += y;
  p->y /= 2;
  p->setN(std::max(p->getn(), r.getn()));
  p->setD(p->getd() + r.getd());
  return Proxy(p);
}

Point& Point::operator+=(const Point& r) {
  x += r.x; y += r.y;
  x /= 2; y /= 2;
  return *this;
}
std::ostream& operator<<(std::ostream& os, const Point& p) {
  p.Print(os);
  return os;
}

/*Polygon& Polygon::operator+=(const Polygon& r) {
  std::cout << "+= polygon\n";
  d += r.d;
  n = std::max(n, r.n);
  x += r.x; y += r.y;
  x /= 2; y /= 2;
  return *this;
}*/

Proxy Polygon::operator+(const Point& r) const {
  Point* p = Clone();
  p->x += r.x;
  p->x /= 2;
  p->y += r.y;
  p->y /= 2;
  p->setD(p->getd() + r.getd());
  p->setN(std::max(p->getn(), r.getn()));
  return Proxy(p);
}

Polygon& Polygon::operator+=(const Point& r)  {
  x += r.x; y += r.y;
  x /= 2; y /= 2;
  setD(getd() + r.getd());
  setN(std::max(getn(), r.getn()));
  return *this;
}

Proxy Proxy::operator+(Point const& r) const {
  return *p_ + r;
}
std::ostream& operator<<(std::ostream& os, const Proxy& p) {
  return os << *(p.p_);
}

Proxy::~Proxy() { delete p_; }

Proxy::operator Point const&() const { return *p_; }

Proxy::operator Point&() { return *p_; }