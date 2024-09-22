#include <iostream>
using namespace std;

void bar()
{
  int u = 3;
  cout << "u: " << u << endl;

  cout << "address of u: " << (long)u << endl;
}

// a simple function
void foo()
{
  int x = 1;
  cout << "x = " << x << endl;

  cout << "address of local var x: " << (long)(&x) << endl;

  int *pz = new int;
  *pz = 2;
  cout << "pz points to to: " << *pz << endl;

  cout << "address of heap-allocated buffer pointed by pz: " << (unsigned long)pz << endl;
  delete pz;

  char arr[10] = "hello";
  cout << "arr = " << arr << endl;
  cout << "address of local var arr: " << (long)arr << endl;

  // call bar
  bar();
}

int g = 0;
int main()
{
  cout << "address of global var g: " << (long)(&g) << endl;
  cout << "address of main func: " << (long)(main) << endl;

  foo();
}
