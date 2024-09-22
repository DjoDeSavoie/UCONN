#include <iostream>
#include "./SeparateFolders/inc/ECNumbers.h"
#include "./SeparateFolders/inc/ECCalculator.h"

using namespace std;

int main()
{
  int number;

  // Read in an integer n
  // your code here
  cout << "Enter an integer: ";
  cin >> number;

  // Print out the square of it
  // your code here

  cout << "Square of " << number << " is " << ECNumbers::ECSquareN(number) << endl;

  // Print out 2n
  // your code here

  cout << "Two times " << number << " is " << ECNumbers::ECDoubleN(number) << endl;

  // Print out 4 times of n by invoking ECCalculator's function
  // your code here

  cout << "Four times " << number << " is " << ECFourTimesN(number) << endl;

  return 0;
}
