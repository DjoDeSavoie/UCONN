#include <vector>
#include <set>
#include <iostream>
using namespace std;

// I want to have a generic function that can work with any types of numbers
// AND any type of container. Is this possible?
template <class T>
typename T::value_type ECSumList(const T &listNums)
{

  typename T::value_type res = 0;
  for (auto x : listNums) // can put T or auto
  {
    res += x;
  }

  return res;
}
