#include <iostream>
#include <type_traits>

using namespace std;

template<class T> struct isInteger_ : false_type { };
template<> struct isInteger_<int> : true_type {};
template<> struct isInteger_<long long> : true_type {};
template<> struct isInteger_<short> : true_type {};
template<> struct isInteger_<long> : true_type {};
template<> struct isInteger_<char> : true_type {};

template<class T> struct isInteger : isInteger_<remove_cv_t<T>>::type {};

int cur = 0;
int mx = 0;
int previous;

template <bool b, typename T>
struct SelectValue;

template <typename T>
struct SelectValue<true, T> {
  static int Value(T x) { return x; }
};

template <typename T>
struct SelectValue<false, T> {
  static int Value(T x) { return 0; }
};


template <typename T, typename U>
void Check(T x, U y) {
  if (SelectValue<isInteger<T>::value, T>::Value(x) ==  SelectValue<isInteger<U>::value, U>::Value(y)) {
    if (cur == 0)
      cur = 2;
    else
      ++cur;
  } else if (isInteger<T>::value) {
    cur = 1;
  } else {
    cur = 0;
  }
  mx = std::max(cur, mx);
}

int MaxPlatform() { return 0; }

template<typename T>
int MaxPlatform(T x) { return isInteger<T>::value; }

template<typename T, typename U>
int MaxPlatform(T x, U y) {
  Check(x, y);
  return std::max(cur, mx);
}

template<typename T, typename U, typename... Args>
auto MaxPlatform(T x, U y, Args... args) {
  Check(x, y);
  return std::max(mx, MaxPlatform(y, args...));
}

int main() {

  int a[MaxPlatform(2, 3.5, 4, 4, 4, 4, 4, 'a', 32, string("abc") , (short)12, 1, 1, 1, 1, 1, 1,1 ,1 ,1 ,1, 1,1, 1,1, 1)];
  cout << sizeof(a) / sizeof(a[0]);

  return 0;
}
