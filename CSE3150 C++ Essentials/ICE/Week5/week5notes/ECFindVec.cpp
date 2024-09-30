#include <vector>
#include <iostream>
using namespace std;

// return true if x is in vector of ints, else false
bool ECFind(const vector<int> &listVecs, int x)
{
  for (auto y : listVecs)
  {
    if (x == y)
    {
      return true;
    }
  }
  return false;
}
