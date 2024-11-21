#include <iostream>
using namespace std;

// base class
class ECLife
{
public:
  void Die() {}
};

// derived class
class ECCat : public ECLife
{
public:
  void Mew() { }
};

// derived class 2
class ECDog : public ECLife
{
public:
  void Bark() { }
};

// test code
int main()
{
  ECLife *pl1 = new ECCat;
  ECLife *pl2 = new ECDog;
  ECLife *pl3 = new ECCat;

  // How to tell what kind of life it is?
  // How to tell if say pl1 and pl2 point to the same kind of life?


  delete pl1;
  delete pl2;
  delete pl3; 
}

