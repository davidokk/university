//---------------------------------------------------------------------------

#ifndef KRatH
#define KRatH
//---------------------------------------------------------------------------
#include <iostream>
#include <exception>
#include <assert.h>
#include <tuple>

using namespace std;

class KRat;

class KNumProxy
  {
   public:
    KNumProxy (KRat& _r): r(_r) { }

    inline KRat& operator = (int aNum);
          inline operator int();

   private:
    KRat& r;
  };

class KRat
  {public:
     friend class KNumProxy;

     bool operator== (const KRat& r) const { return fNum == r.fNum && fDenom == r.fDenom; }
     bool operator< (const KRat& r) { return std::tie(fNum, fDenom) < std::tie(r.fNum, r.fDenom); }

     //explicit KRat (int aNum = 0, int aDenom = 1): fNum(aNum), fDenom(aDenom)
     //         {if (fDenom==0)
     //            throw invalid_argument("Denominator equals zero");
     //          Normalize();
     //         }
              
              KRat ():         fNum(0), fDenom(1) { }
     explicit KRat (int aNum): fNum(aNum), fDenom(1) { }
     /*explicit*/ KRat (int aNum, int aDenom): fNum(aNum), fDenom(aDenom)
                {if (fDenom==0)
                   throw invalid_argument("Denominator equals zero");
                 //assert(fDenom != 0);
                 Normalize();
                }         
                ~KRat() {  }

     // Accessors
      KNumProxy Numerator ()       { return *this; }
     const int& Numerator () const { return fNum; }
           int& Denominator()       { return fDenom; }   // ������� ���������
     const int& Denominator() const { return fDenom; }  

                   KRat& operator += (const KRat& r);
                   KRat& operator += (int a);

            inline KRat& operator *= (const KRat& r);
            inline KRat& operator *= (int a);

            inline KRat&      operator ++ ();     //prefix
            inline KRat const operator ++ (int);  //postfix

            inline KRat const operator + (KRat const& r) const;   // ������������ const, ����� ����������� r1+r2=r3
            inline KRat const operator + (int a) const;
     friend inline KRat const operator + (int a,KRat const& r2);

            inline KRat const operator * (const KRat& r) const;
            inline KRat const operator * (int a) const;
     friend inline KRat const operator * (int a,const KRat& r2);

                explicit operator double () const { return (double)fNum / fDenom;  }   // �� �� ������ ������ ����������

     friend        std::istream& operator >> (std::istream& is, KRat& r);
     friend inline std::ostream& operator << (std::ostream& os, const KRat& r);

   private:
     static int GCD (int, int); //���
           void Normalize();

   private:
     int fNum;
     int fDenom;
  };    // end of KRat

//----------------------------- inline implementation --------------------------

inline KRat& KNumProxy::operator = (int aNum)
  { r.fNum = aNum;
    r.Normalize();
    return r;
  }

//------------------------------------------------------------------------------

inline KNumProxy::operator int() { return r.fNum; }

//------------------------------------------------------------------------------

inline KRat& KRat::operator *= (const KRat& r)
  { fNum *= r.fNum;
    fDenom *= r.fDenom;
    return *this;
  }
//------------------------------------------------------------------------------

inline KRat& KRat::operator *= (int a)
  {
   fNum *= a;
   return *this;
  }
//------------------------------------------------------------------------------

inline KRat& KRat::operator ++ ()     //prefix
  {
   fNum += fDenom;
   return *this;
   //return *this+=KRat(1);
  }
//------------------------------------------------------------------------------

inline KRat const KRat::operator ++ (int)  //postfix
  {
   KRat r = *this;
   ++*this;
   return r;
  }

//--------------------------- Friends ------------------------------------------

inline KRat const KRat::operator * (const KRat& r) const
  {
    return KRat(fNum*r.fNum, fDenom*r.fDenom);
  }
//------------------------------------------------------------------------------

inline KRat const KRat::operator * (int a) const
  {
    return KRat(fNum*a, fDenom);
  }
//------------------------------------------------------------------------------

inline KRat const operator * (int a,const KRat& r2)
  {
    return KRat(a*r2.fNum, r2.fDenom);
  }
//------------------------------------------------------------------------------

inline KRat const KRat::operator + (KRat const& r) const
  {
   return KRat (fNum * r.fDenom + r.fNum * fDenom, fDenom * r.fDenom);
  }
//------------------------------------------------------------------------------

inline KRat const KRat::operator + (int a) const
  {
   return KRat (fNum + a * fDenom, fDenom);
  }
//------------------------------------------------------------------------------

inline KRat const  operator + (int a,KRat const& r2)
  {
    return KRat (a * r2.fDenom + r2.fNum, r2.fDenom);
  }
//------------------------------------------------------------------------------

inline std::ostream& operator << (std::ostream& os, const KRat& r)
  { os << r.fNum;
    if (1 != r.fDenom)
      os << '/' << r.fDenom ;
    return os;
  }

#endif
