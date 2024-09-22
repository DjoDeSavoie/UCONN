//
//  RemoveDupPointers.cpp
//  
//
//  Created by Yufeng Wu on 1/18/21.
//
//

#include <string>
#include <vector>
using namespace std;

void RemoveDupPointers(vector<string *> &arrayPtrs)
{
    // Loop to check each element
    for (size_t i = 0; i < arrayPtrs.size(); ++i)
    {
        // Double loop to compare the current string with the rest of the elements
        for (size_t j = i + 1; j < arrayPtrs.size();)
        {
            // Compare the strings that the pointers are pointing to
            if (*arrayPtrs[i] == *arrayPtrs[j])
            {
                // Remove duplicate string pointer
                arrayPtrs.erase(arrayPtrs.begin() + j);
            }
            else
            {
                // Move to the next element if no deletion occurred
                ++j;
            }
        }
    }
}
