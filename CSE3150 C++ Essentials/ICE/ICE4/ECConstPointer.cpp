#include <iostream>
using namespace std;

int ECSumArray(const int *listNums, int sz)
{
  // You need to loop through the array using pointer. How to define this pointer?
  int sum = 0;
  for (int i = 0; i < sz; ++i)
  {
    sum += *listNums;
    ++listNums;
  }

  return sum;
}

int main()
{
  int array[] = {1, 2, 3, 5, 10};
  int s = ECSumArray(array, 5);
  cout << "Sum: " << s << endl;
  return 0;
}
