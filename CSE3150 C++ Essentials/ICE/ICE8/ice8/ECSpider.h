#ifndef _EC_SPIDER_H
#define _EC_SPIDER_H

#include "ECLife.h"

// Spider
class ECSpider : virtual public ECLife
{
public:
  ECSpider();
  ECSpider(double life);
  void Weave();
};

#endif
