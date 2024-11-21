#include "ECSpiderMan.h"
#include <iostream>
using namespace std;

// Spiderman
ECSpiderMan::ECSpiderMan(double life) : ECLife(life), ECSpider(life), ECHuman(life) {}

void ECSpiderMan::Work()
{
  Weave();
  Run();
}
