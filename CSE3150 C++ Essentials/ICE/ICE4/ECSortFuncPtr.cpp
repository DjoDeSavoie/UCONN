#include <iostream>
using namespace std;

// compare: smaller goes first
bool Cmp1(int x, int y)
{
  return x <= y;
}

bool Cmp2(int x, int y)
{
  return y <= x;
}

// even number first, then odd nums, if both even/odd, use <= as before
bool Cmp3(int x, int y)
{
  bool fx = (x % 2 == 0);
  bool fy = (y % 2 == 0);
  if (fx && !fy)
  {
    return true;
  }
  else if (!fx && fy)
  {
    return false;
  }
  else
  {
    return x <= y;
  }
}

// complete the definition of the sorting function ...
void ECSortFP(int *listNumbers, int size, bool (*cmp)(int, int))
{
  // your code here'...
  //  implpement insertion sort
  for (int i = 1; i < size; ++i)
  {
    int x = listNumbers[i];
    bool fIns = false;
    for (int j = i - 1; j >= 0; --j)
    {

      if (cmp(x, listNumbers[j]))
      {
        // if [i] <= [j] then move the current number to right to make space for new number
        listNumbers[j + 1] = listNumbers[j];
      }
      else
      {
        fIns = true;
        listNumbers[j + 1] = x; // place x in the space we just madej

        break;
      }
    }
    //
    if (fIns == false)
    {
      listNumbers[0] = x;
    }
  }
}
/*
bool IsEarlier(int x, int y)
{
  // prefer smaller item earlier (standard sorting)
}
bool IsEarlierReverse(int x, int y)
{
  // prefer larger one earlier
}
bool IsEarlierParity(int x, int y)
{
  // put even number earlier; if both are even or both are odd, sort by their values
}

bool IsEarlierPrime(int x, int y)
{
  // put prime numbers earlier, if both are prime or both are not prime, sort by their values
}
*/
int main()
{
  int arr[] = {1, 3, 2, 4};
  // ECSortFP(arr, 4, Cmp1);
  ECSortFP(arr, 4, Cmp2);

  // print it out
  for (int i = 0; i < 4; ++i)
  {
    cout << arr[i] << " ";
  }
  cout << endl;
}
