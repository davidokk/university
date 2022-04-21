//------------------------------------------------------------------------------
#include <stdexcept>

#include "KRat.h"

using namespace std;

KRat& KRat::operator += (const KRat& r)
  {
    fNum = fNum * r.fDenom + r.fNum * fDenom;
    fDenom *= r.fDenom;
    return *this;
  }
//------------------------------------------------------------------------------

KRat& KRat::operator += (int a)
  {
    fNum = fNum  + a * fDenom;
    Normalize();
    return *this;
  }

//------------------------------------------------------------------------------

std::istream& operator >> (std::istream& is, KRat& r)
  {
    char ch;
    is >> r.fNum;
    auto fls = is.flags();          // Запомнить флаги  
    is.unsetf(ios_base::skipws);   
    is >> ch;
    if (ch == '/')
      is >> r.fDenom;
    else
      {is.putback(ch);
       r.fDenom = 1;
      }
    is.flags(fls);         // Восстановить флаги
    if (r.fDenom==0) throw runtime_error("Знаменатель не может быть равен нулю");
    r.Normalize();
    return is;
  }
//------------------------------------------------------------------------------

int KRat::GCD(int a, int b)    // НОД
  {
    a = abs(a); b = abs(b);
    while (a && b)
      a>b ? a %= b : b %= a;   //Алгоритм Евклида
    return (a+b);
  }
//------------------------------------------------------------------------------

void KRat::Normalize()
  {
    int gcd = GCD(fNum,fDenom);
    fNum /= gcd;
    fDenom /= gcd;
    return;
  }
//------------------------------------------------------------------------------

//!!! Работа с отрицательными числами
