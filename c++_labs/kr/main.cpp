#include <iostream>
#include <iomanip>

#include "point.h"

using namespace std;

int main() {
  Point a(1, 2);
  Point a1(7, 3);
  Polygon p(2, 2, 4, 3);
  Polygon p1(1, 3, 3, 5);

  //p += a;
  //cout << p << endl;
  //p += p1;
  //cout << p << endl;


  cout << (a += p);

  // cout << boolalpha;
  // cout << a + a1 << endl;
  // cout << a + p << endl;
  //
  // cout << p + a << endl;
  // //не работает
  //
  // cout << p + p1 << endl;

}
