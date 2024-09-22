// To build test code: g++ ECInverseIntTest.cpp -o test
#include <string>
#include <iostream>
#include <chrono>
using namespace std;

#include "ECInverseInt.cpp"

template <class T>
void ASSERT_EQ(T x, T y)
{
  if (x == y)
  {
    cout << "Test passed: equal: " << x << "  " << y << endl;
  }
  else
  {
    cout << "Test FAILED: equal: " << x << "  " << y << endl;
  }
}

static void Test1()
{
  string str1 = "2011";
  ASSERT_EQ(ECInverseInt(str1), string("1102"));
  string str2 = "1";
  ASSERT_EQ(ECInverseInt(str2), string("1"));
}
static void Test2()
{
  string str1 = "2000";
  ASSERT_EQ(ECInverseInt(str1), string("2"));
  string str2 = "201010";
  ASSERT_EQ(ECInverseInt(str2), string("10102"));
}
static void Test3()
{
  string str1 = "0";
  ASSERT_EQ(ECInverseInt(str1), string("0"));
}

int main()
{
  Test1();
  Test2();
  Test3();
}
