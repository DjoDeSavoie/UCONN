#ifndef _EC_LIFE_H
#define _EC_LIFE_H

class ECLife
{
public:
  ECLife(double life) : lifeRemain(life) {}
  virtual ~ECLife() {}
  double GetLifeRemain() const { return lifeRemain; }
  void SetLife(double life) { lifeRemain = life; }

protected:
  double lifeRemain;
};

#endif
