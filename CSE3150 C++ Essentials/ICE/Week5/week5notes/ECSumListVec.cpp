#include <vector>
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

// return the sum of the numbers

template <class T>
T ECSumList(const vector<T> &listNums)
{

  T res = 0;
  for (auto x : listNums) // can put T or auto
  {
    res += x;
  }

  return res;
}
