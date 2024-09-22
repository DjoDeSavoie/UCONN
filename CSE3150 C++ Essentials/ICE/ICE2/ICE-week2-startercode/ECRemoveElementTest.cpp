#include <iostream>
using namespace std;

extern int ECRemoveSpace(int nums[], int len, int val);

int main()
{
  int nums1[] = {3,2,2,3};
  int res = ECRemoveSpace(nums1, 4, 3); 
  cout << "nums1: " << res << endl;
  for(int i=0; i<4; ++i)
  {
    cout << nums1[i] << " ";
  } 
  cout << endl;
  int nums2[] = {0,1,2,2,3,0,4,2};
  res = ECRemoveSpace(nums2, 8, 2); 
  cout << "nums2: " << res << endl;
  for(int i=0; i<8; ++i)
  {
    cout << nums2[i] << " ";
  } 
  cout << endl;
  return 0;
}

