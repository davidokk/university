#ifndef POINT_H
#define POINT_H

#include <iostream>

class Point;

class Proxy {
 public:
  Proxy(Point* p) : p_(p) {}
  ~Proxy();

  Proxy operator+(Point const& r) const;

  operator Point const&() const;
  operator Point&();

  friend std::ostream& operator<<(std::ostream& os, Proxy const& p);

 private:
  Point* p_;
};

class Polygon;

class Point {
 public:
  Point(double x_, double y_);
  virtual ~Point() {}

  virtual Proxy operator+(const Point& r) const;
  virtual Point& operator+=(const Point& r);

  virtual Point* Clone() const { return new Point(x, y); }

  virtual bool operator==(const Point& r) const {
    return std::make_pair(x, y) == std::make_pair(r.x, r.y) && r.getn() == 0;
  }
  virtual bool operator<(const Point& r) const {
    return std::make_tuple(x, y, getn(), getd()) < std::make_tuple(r.x, r.y, getn(), getd());
  }
  virtual bool operator>(const Point& r) const {
    return std::make_tuple(x, y, getn(), getd())
        > std::make_tuple(r.x, r.y, getn(), getd());
  }
  virtual bool operator!=(const Point& r) const { return !operator==(r); }
  virtual bool operator<=(const Point& r) const { return !operator>(r); }
  virtual bool operator>=(const Point& r) const { return !operator<(r); }

  virtual void Print(std::ostream& os) const {
    os << "Point: x = " << x << " y = " << y;
  }

  virtual double getn() const { return 0; }
  virtual double getd() const { return 0; }

  virtual void setN(double a) {}
  virtual void setD(double a) {}

  friend std::ostream& operator<<(std::ostream& os, Point const& p);

  double x, y;
};

class Polygon : public Point {
 public:
  Polygon(double x, double y, double n_, double d_) : Point(x, y), n(n_), d(d_) {}

  //Polygon& operator+=(const Polygon& r);
  Polygon& operator+=(const Point& r) override;
  Proxy operator+(const Point& r) const;

  Point* Clone() const override { return new Polygon(x, y, n, d); }

  bool operator==(const Point& r) const override { return std::make_pair(x, y) == std::make_pair(r.x, r.y); }
  bool operator<(const Point& r) const override { return std::make_pair(x, y) < std::make_pair(r.x, r.y); }
  bool operator>(const Point& r) const override { return std::make_pair(x, y) > std::make_pair(r.x, r.y); }
  bool operator!=(const Point& r) const override { return !operator==(r); }
  bool operator<=(const Point& r) const override { return !operator>(r); }
  bool operator>=(const Point& r) const override { return !operator<(r); }

  void Print(std::ostream& os) const override {
    os << "Polygon: x = " << x << " y = " << y << " n = " << n << " d = " << d;
  }

  double getn() const override { return n; }
  double getd() const override { return d; }

  virtual void setN(double a) override { n = a; }
  virtual void setD(double a) override { d = a; }

 private:
  double n, d;
};

#endif //POINT_H
