//
#include <iostream>
using namespace std;

int main()
{
  // allocate an array of char in heap
  char *px = new char[10];
  // set this array to 'a', 'b' and so on

  char *px1 = px;

  // your code here...
  for (int i = 0; i < 10; ++i)
  {
    *px1 = 'a' + i;
    ++px1;
  }

  // print out
  for (int i = 0; i < 10; ++i)
  {
    cout << *(px + i);
  }
  cout << endl;

  delete[] px; // NOT delete px

  return 0;
}
