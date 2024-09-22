#include <iostream>
using namespace std;

int ECRemoveSpace(int nums[], int len, int val)
{
  // your code here
  int j = 0; // Pointer for placing elements not equal to `val`

    // Traverse the array
    for (int i = 0; i < len; ++i) {
        if (nums[i] != val) {
            // Place element at index `j` and increment `j`
            nums[j] = nums[i];
            ++j;
        }
    }

    // Return the new length of the array with `val` removed
    return j;
}


