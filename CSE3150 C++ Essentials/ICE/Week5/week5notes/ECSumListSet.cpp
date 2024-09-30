#include <set>
#include <vector>
#include <iostream>
using namespace std;

template <class T>
int ECSumList(const set<T> &listNums)
{
  // your code goes here ...

  T res = 0;
  for (auto x : listNums) // can put T or auto
  {
    res += x;
  }

  return res;
}
