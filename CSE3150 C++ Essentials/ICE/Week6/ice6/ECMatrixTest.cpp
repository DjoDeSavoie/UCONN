#include <iostream>
#include "ECMatrix.h"
using namespace std;
#include <chrono>
using namespace std::chrono;

int main()
{
  const int NR=100;
  const int NC=100;
  ECMatrix mat1(NR, NC);
  mat1.SetVal(1,1, 1.0);
  // create scaling repetitively
  auto ts = high_resolution_clock::now();

  const int NUMS=2;
  double valSum = 0.0;
  for(int i=0; i<NUMS; ++i)
  {
//    ECMatrix mat2 ( mat1.Scale(i) );
    ECMatrix mat2 = std::move( mat1.Scale(i) );
//    ECMatrix mat2;
//    mat2  =  mat1.Scale(i);
    valSum += mat2.GetVal(1,1);
  }
  cout << "valSum: " << valSum << endl;

  // test operators
  cout << "\nTesting operators...\n";
  ECMatrix mat3(2,2);
  mat3[0,0] = 1.0;
  mat3[0,1] = 2.0;
  mat3[1,0] = 3.0;
  mat3[1,1] = 4.0;
  double v1 = mat3[1,1];
  cout << "v1: " << v1 << endl;
  mat3[1,1] = 3.0;
  cout << "After setting, v1: " << mat3[1,1] << endl;
  // test sum of two matrices
  ECMatrix mat4(2,2);
  mat4[0,0] = 4.0;
  mat4[0,1] = 3.0;
  mat4[1,0] = 2.0;
  mat4[1,1] = 1.0;
  ECMatrix mat5 = mat3 + mat4;
  cout << "sum matrix at 1,1: " << mat5[1,1] << endl;

  auto te = high_resolution_clock::now();
  auto duration = duration_cast<microseconds>(te-ts);
  cout << "Elapsed time (microseconds): " << duration.count() << endl;
  return 0;
}


