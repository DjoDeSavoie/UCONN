#ifndef _EC_STUDENT_H
#define _EC_STUDENT_H

#include <string>

// Student class
class ECStudent
{
public:
  ECStudent(const std::string &nameIn) : mt(0.0), fl(0.0), hw(0.0), sn(nameIn) {}
  double GetMT() const { return mt; }
  void SetMT(double s) { mt = s; }
  double GetFinal() const { return fl; }
  void SetFinal(double s) { fl = s; }
  double GetHW() const { return hw; }
  void SetHW(double s) { hw = s; }
  std::string GetName() const { return sn; }
  // ave score: 20% HW, 30% Midterm, 50% Final
  double GetAve() const { return 0.2 * GetHW() + 0.3 * GetMT() + 0.5 * GetFinal(); }

private:
  // ???
  double mt;
  double fl;
  double hw;

  std::string sn;
};

#endif
