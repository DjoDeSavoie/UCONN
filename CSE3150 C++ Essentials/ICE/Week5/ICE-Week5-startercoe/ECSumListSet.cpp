#include <set>
#include <vector>
#include <iostream>
using namespace std;

template <class T>
T ECSumList(const set<T> &listNums)
{
  // your code goes here ...
  T res = 0;
  for(auto x : listNums){
    res+=x;
  }
  return res;
}

