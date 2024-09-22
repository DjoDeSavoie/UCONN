// test code for ECStringMatch
// To build: g++ ECStringMatch.cpp ECStringMatchTest.cpp -std=c++11 -o test

#include "ECStringMatch.h"
#include <string>
#include <iostream>
#include <ctime>
#include <type_traits>
#include <chrono>
using namespace std;
using namespace std::chrono;

template<class T>
void ASSERT_EQ(T x, T y)
{
  if( x == y )
  {
    cout << "Test passed: equal: " << x << "  " << y << endl;
  }
  else
  {
    cout << "Test FAILED: equal: " << x << "  " << y << endl;
  }
}

// basic testing
static void Test1()
{
  cout << "*****Test1\n";
  string strText = "mississippi";
  string strPattern = "iss";
  string strPattern1 = "ssp";
  ASSERT_EQ( ECStrMatchBruteForce(strText, strPattern), true );
  ASSERT_EQ( ECStrMatchBuiltIn(strText, strPattern), true );
  ASSERT_EQ( ECStrMatchNumCompare(strText, strPattern), true );

  ASSERT_EQ( ECStrMatchBruteForce(strText, strPattern1), false );
  ASSERT_EQ( ECStrMatchBuiltIn(strText, strPattern1), false );
  ASSERT_EQ( ECStrMatchNumCompare(strText, strPattern1), false );
}

// check some special cases
static void Test2()
{
  cout << "*****Test2\n";
  string strText = "mississippi";
  string strPattern = "iss";
  string strPattern1 = "isp";
  string strPattern2 = "ppi";
  ASSERT_EQ( ECStrMatchBruteForce(strText, strText), true );
  ASSERT_EQ( ECStrMatchBuiltIn(strText, strText), true );
  ASSERT_EQ( ECStrMatchNumCompare(strText, strText), true );

  ASSERT_EQ( ECStrMatchBruteForce(strPattern, strText), false );
  ASSERT_EQ( ECStrMatchBuiltIn(strPattern, strText), false );
  ASSERT_EQ( ECStrMatchNumCompare(strPattern, strText), false );

  ASSERT_EQ( ECStrMatchBruteForce(strPattern1, strPattern), false );
  ASSERT_EQ( ECStrMatchBuiltIn(strPattern1, strPattern), false );
  ASSERT_EQ( ECStrMatchNumCompare(strPattern1, strPattern), false );

  ASSERT_EQ( ECStrMatchBruteForce(strText, strPattern2), true );
  ASSERT_EQ( ECStrMatchBuiltIn(strText, strPattern2), true );
  ASSERT_EQ( ECStrMatchNumCompare(strText, strPattern2), true );
}

// basic testing
static void Test3()
{
  // now a more complicated case
  cout << "*****Test3\n";
  string str1 = "abcdefghijklmnopqrst";
  int numCopies = 10;
  string strText;
  for(int i=0; i<numCopies; ++i)
  {
    strText += str1;
  }
  // append one x to the end
  strText += "x";
  //strText += str1;

  // patterns
  string strPattern = str1 + 'x';   // this should match!
  string strPattern1 = str1 + 'b';  // this shoudln't match!

  ASSERT_EQ( ECStrMatchBruteForce(strText, strPattern), true );
  ASSERT_EQ( ECStrMatchBuiltIn(strText, strPattern), true );
  ASSERT_EQ( ECStrMatchNumCompare(strText, strPattern), true );

  ASSERT_EQ( ECStrMatchBruteForce(strText, strPattern1), false );
  ASSERT_EQ( ECStrMatchBuiltIn(strText, strPattern1), false );
  ASSERT_EQ( ECStrMatchNumCompare(strText, strPattern1), false );
}

// testing: compare run time between the brute-force and numeric-based comparison
static void Test4()
{
  cout << "*****Test4\n";
  string str1 = "abcdefghijklmnopqrst";
  int numCopies = 10000000;
  string strText;
  for(int i=0; i<numCopies; ++i)
  {
    strText += str1;
  }
  // append one x to the end
  strText += "x";
  //strText += str1;

  // patterns
  string strPattern = str1 + 'x';   // this should match!
  string strPattern1 = str1 + 'b';  // this shoudln't match!

  std::chrono::steady_clock::time_point cpu_clock_start1 = std::chrono::steady_clock::now();
  ASSERT_EQ( ECStrMatchBruteForce(strText, strPattern), true );
  std::chrono::steady_clock::time_point cpu_clock_end1 = std::chrono::steady_clock::now();
  //ASSERT_EQ( ECStrMatchBuiltIn(strText, strPattern), true );
  
  std::chrono::steady_clock::time_point cpu_clock_start2 = std::chrono::steady_clock::now();
  ASSERT_EQ( ECStrMatchNumCompare(strText, strPattern), true );
  std::chrono::steady_clock::time_point cpu_clock_end2 = std::chrono::steady_clock::now();

  ASSERT_EQ( ECStrMatchBruteForce(strText, strPattern1), false );
  //ASSERT_EQ( ECStrMatchBuiltIn(strText, strPattern1), false );
  ASSERT_EQ( ECStrMatchNumCompare(strText, strPattern1), false );

  // now analyze time
  const auto cpu_clock_elapsed1 = duration_cast<std::chrono::microseconds>(cpu_clock_end1-cpu_clock_start1).count();
  cout << "elapsed time for brute-force: " << cpu_clock_elapsed1 << endl;
  const auto cpu_clock_elapsed2 = duration_cast<std::chrono::microseconds>(cpu_clock_end2-cpu_clock_start2).count();
  cout << "elapsed time for numeric-based comparision: " << cpu_clock_elapsed2 << endl;
  // your numeric comparison must be at least twice as fast as the brute-force one
  ASSERT_EQ( 2*cpu_clock_elapsed2 <= cpu_clock_elapsed1, true);
}

// another testing: compare run time between C++ built-in string matching and numeric-based comparison
static void Test5()
{
  cout << "*****Test5\n";
  const int SZ1 = 500000;
  string str1;
  for(int i=0; i<SZ1; ++i)
  {
    str1 += 'a';
  }
  str1 += 'b';

  // create pattern
  const int SZ2 = 10;
  string strText;
  for(int i=0; i<SZ2; ++i)
  {
    strText += str1;
  }
  string strPattern = str1;
  string strPattern1 = str1+'b';

  // the matching case should be fast
  //ASSERT_EQ( ECStrMatchBruteForce(strText, strPattern), true );
  ASSERT_EQ( ECStrMatchBuiltIn(strText, strPattern), true );
  ASSERT_EQ( ECStrMatchNumCompare(strText, strPattern), true );

  //ASSERT_EQ( ECStrMatchBruteForce(strText, strPattern1), false );
  std::chrono::steady_clock::time_point cpu_clock_start1 = std::chrono::steady_clock::now();
  ASSERT_EQ( ECStrMatchBuiltIn(strText, strPattern1), false );
  std::chrono::steady_clock::time_point cpu_clock_end1 = std::chrono::steady_clock::now();
  
  std::chrono::steady_clock::time_point cpu_clock_start2 = std::chrono::steady_clock::now();
  ASSERT_EQ( ECStrMatchNumCompare(strText, strPattern1), false );
  std::chrono::steady_clock::time_point cpu_clock_end2 = std::chrono::steady_clock::now();
  
  // now analyze time
  const auto cpu_clock_elapsed1 = duration_cast<std::chrono::microseconds>(cpu_clock_end1-cpu_clock_start1).count();
  cout << "elapsed time using std::string::find " << cpu_clock_elapsed1 << endl;
  const auto cpu_clock_elapsed2 = duration_cast<std::chrono::microseconds>(cpu_clock_end2-cpu_clock_start2).count();
  cout << "elapsed time for numeric-based comparision: " << cpu_clock_elapsed2 << endl;
  // your numeric comparison must be at least 100 times as fast as the one given by C++ std::string::find!
  ASSERT_EQ( 100*cpu_clock_elapsed2 <= cpu_clock_elapsed1, true);
}

int main()
{
  Test1();
  Test2();
  Test3();
  Test4();
  Test5();
}

