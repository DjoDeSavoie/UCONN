#include <vector>
#include <set>
#include <iostream>
using namespace std;

#include "ECSumListGeneric.cpp"

int main()
{
  vector<int> vec;
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(3);
  vec.push_back(0);
  vec.push_back(1);
  int sum = ECSumList(vec);
  cout << "sum1: " << sum << endl;

  set<int> s1;
  s1.insert(2);
  s1.insert(5);
  cout << "Sum of s1: " << ECSumList(s1) << endl;

  set<double> ss;
  ss.insert(5.0);
  ss.insert(3.0);
  ss.insert(3.0);
  ss.insert(0.2);
  ss.insert(1.0);
  double sum2 = ECSumList(ss);
  cout << "sum2: " << sum2 << endl;
}
