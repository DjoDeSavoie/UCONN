#include <iostream>
using namespace std;

// function takes a const int pointer and then modify it
void foo(const int *px)
{
  // cast to non-const and then modify the int pointed by it
  int *pcx = const_cast<int *>(px);
  *pcx = 1;
}

// do the following casting work?
int main()
{
  // cast an int to char
  char ch1 = 'a'; // no cast needed
  // int x1 = static_cast<int>(ch1); 
  int x1 = ch1; // implicit casting from char to int
  cout << "x1 = " << x1 << ", ch1 = " << ch1 << endl;

  // cast a pointer to an int to a pointer to a double
  int y1 = 10;
  double *py1 = reinterpret_cast<double *>(&y1); // dangerous cast, but works syntactically
  cout << "*py1: " << *py1 << endl; // the output here will likely be garbage data due to incompatible types

  // cast a pointer to char to a pointer to int
  char ch = 'a';
  int *pch = reinterpret_cast<int *>(&ch); // casting char* to int* using reinterpret_cast
  cout << "*pch: " << *pch << endl; // will print garbage value as well, since it's an incompatible cast

  // cast a void pointer to point to int
  int x4 = 20;
  void *px4 = &x4; // void pointer can hold the address of any type
  int *px4i = static_cast<int *>(px4); // static_cast to convert void* back to int*
  cout << "*px4i: " << *px4i << endl;

  // const_cast
  // cast a const int pointer to a non-const pointer to int and then modify it
  const int x5 = 0;
  int *px5 = const_cast<int *>(&x5); // removes constness of x5
  *px5 = 1; // modifies the value
  cout << "x5: " << x5 << ", *px5: " << *px5 << endl; // undefined behavior since x5 is const

  // const_cast and function call
  // const int x6 = 0;
  int x6 = 0; // removed const to avoid undefined behavior
  foo(&x6); // passes a const int* to the function, but foo removes const and modifies it
  cout << "x6: " << x6 << endl; // prints modified value of x6

  return 0;
}
