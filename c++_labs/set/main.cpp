#include <iostream>
#include <complex>
#include <algorithm>
#include <tuple>
#include "set.h"
#include "KRat.h"
using namespace std;

template <typename T, typename U>
ostream& operator<< (ostream& os, const pair<T, U>& p) {
  return os << "{" << p.first << ", " << p.second << "}";
}

namespace std {
  bool operator<(const complex<int>& a, const complex<int>& b) {
    return std::make_pair(a.imag(), a.real())
        < std::make_pair(b.imag(), b.real());
  }
}

#define DEBUG(x) cout << #x << " = " << x << endl

int main() {

  vector<KRat> v{{1, 2}, {3, 4}, {5, 6}};
  const Set<KRat> a(v.begin() + 1, v.end());
  for (auto i : a)
    cout << i << endl;

  Set<KRat> b(a.begin(), a.end());
  Set<KRat> c(v);
  DEBUG(b);
  DEBUG(c);

  Set<int> d{1, 2, 3};
  DEBUG(d);

  // {
  //
  //   Set<KRat> a;
  //   a.emplace_insert(2);
  //   for (auto it = a.begin(); it != a.end(); ++it) {
  //     cout << *it << " ";
  //   }
  //
  //   // Set<int> a{1, 2};
  //   // Set<int> b{2};
  //   // a[b] = Set<int>{3, 4};
  //   // cout << a;
  // }
  // try {
  //   {
  //     // итератор
  //     Set<int> a{1, 2, 3};
  //      for (auto i : a)
  //       cout << i << " ";
  //     cout << endl;
  //     cout << *std::max_element(a.begin(), a.end()) << endl;
  //   }
    // {
    //   // emplace метод
    //   Set<pair<int, int>> a{{1, 2}, {2, 3}, {4, 5}};
    //   a.emplace_insert(1, 7);
    //   a.emplace_insert(4, 5);
    //   cout << a << endl;
    // }
    // {
    //   Set<KRat> s{{1, 2}, {2, 3}};
    //   Set<complex<int>> s1{{1, 2}, {2, 3}};
    // }
    // {
    //   Set<double> a{1.2, 5.5};
    //   cout << *a.end() << endl;
    // }
  // } catch (exception& ex) {
  //   cout << ex.what();
  //   return 1;
  // }

    return 0;
}
