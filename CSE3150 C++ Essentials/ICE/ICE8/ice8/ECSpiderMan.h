#ifndef _EC_SPIDERMAN_H
#define _EC_SPIDERMAN_H

#include "ECSpider.h"
#include "ECHuman.h"

// Spiderman
class ECSpiderMan : public ECSpider, public ECHuman
{
public:
  ECSpiderMan(double life);
  void Work();
};

#endif
