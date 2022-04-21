#pragma once
#include <iostream>
#include <windows.h>

class KCharToOem
{
 public:
  KCharToOem(const char * aTxt)
    {fTxt = new char [strlen(aTxt)+1];
     CharToOemA(aTxt,fTxt);
    }
  ~KCharToOem () { delete []fTxt; }
  friend std::ostream& operator << (std::ostream& os, KCharToOem const& s)
  { return os << s.fTxt; }
 private:
  char * fTxt;
};
