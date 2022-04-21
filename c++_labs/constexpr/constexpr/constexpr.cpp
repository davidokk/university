#include <iostream>

template <size_t ...Args> 
struct U;

template<>
struct U<0> { enum { lengthOf = 1 }; };

template<>
struct U<1> { enum { lengthOf = 2 }; };

template<>
struct U<2> { enum { lengthOf = 1 }; };

template<size_t n> 
struct U<n> {
    enum {
        lengthOf = n == 0 ? U<0>::lengthOf : n == 1 ? U<1>::lengthOf : n == 2 ? U<2>::lengthOf 
        : U<n - 1>::lengthOf + 2 * (const int)U<n - 2>::lengthOf + (const int)U<n - 3>::lengthOf
    };
};

template <typename T, size_t n, T ...Idx> 
struct MyArray {
    T arr[U<n>::lengthOf] = { Idx... };
    T& operator[] (size_t index) { return arr[index]; }
};

int main() {
    // u(n) = u(n-1) + 2u(n-2) +u(n-3)
    // u(0) = 1, u(1) = 2, u(2) = 1

    MyArray<int, 1, 5, 7> a;
    int n = sizeof(a.arr) / sizeof(a.arr[0]);
    for (int i = 0; i < n; i++)
        std::cout << a[i] << " ";
   

    //std::cout << sizeof(b) / sizeof(b[0]);

    // 0  1  2  3  4   5   6   7    8    9    10
    // 1  2  1  6  10  23  49  105  226  485  1042
}       
