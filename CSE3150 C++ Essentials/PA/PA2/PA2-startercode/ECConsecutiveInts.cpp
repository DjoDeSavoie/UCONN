//
//  ECConsecutiveInts.cpp
//  
//
//  Created by Yufeng Wu on 1/15/23.
//
//

#include <iostream>
#include <string>
using namespace std;

// Test whether strInput is a string composed of consecutive and increasing integers (in decimal formats)
// Return true if yes and false otherwise (return false if there are unexpected characters)
// For example, 1234578 would return false, while 1213141516 would return true (12 13 14 15 16)
// You may assume the integers is at most 999999 and there is no any seperators between numbers
// You may also assume integers are all non-negatives

// Tip: try to use library functions instead of writing a lot of code yourself
// functions in C++ string you may find useful:
// substr: extract a substring from a string
// stoi:  convert string to integer (be careful about how to handle exception)
// and so on..

bool ECConsecutiveInts(const string &strInput)
{
  // your code  here
  int length = strInput.length();

    for (int len = 1; len <= 6; ++len)
    {
        if (length % len != 0) continue;

        int currentIndex = 0;
        int previousNum = -1;
        bool valid = true;

        while (currentIndex < length)
        {
            string numStr = "";
            for (int k = 0; k < len; k++)
            {
                if (currentIndex + k < length)
                    numStr += strInput[currentIndex + k];
            }

            int num;
            try
            {
                num = stoi(numStr);
            }
            catch (...)
            {
                valid = false;
                break;
            }

            if (previousNum != -1 && num != previousNum + 1)
            {
                valid = false;
                break;
            }

            previousNum = num;
            currentIndex += len;
        }

        if (valid)
            return true;
    }

    return false;
}

