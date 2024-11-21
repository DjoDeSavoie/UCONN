#include "ECTime.h"

// Source code

#include "ECTime.h"

ECTime :: ECTime(int h, int m, int s) : hour(h), min(m), sec(s)
{
}

ECTime :: ~ECTime()
{
}

void ECTime :: GetTime(int &h, int &m, int &s) const
{
 h = hour;
 m = min;
 s = sec;
}

void ECTime :: Overflow(int &valOver, int &valTo)
{
 if( valOver >= 60 )
 {
  valOver -= 60;
  ++valTo;
 }
}

ECTime ECTime :: operator+(const ECTime &tmToAdd)
{
 ECTime res(0, 0, 0) ;
 res.sec = this->sec + tmToAdd.sec;
 res.min = this->min + tmToAdd.min;
 Overflow(res.sec, res.min);
 res.hour = this->hour + tmToAdd.hour;
 Overflow(res.min, res.hour);

 return res;
}