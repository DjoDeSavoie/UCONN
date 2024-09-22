//
//  ECStringMatch.cpp
//  
//
//  Created by Yufeng Wu on 6/16/24.
//

#include "ECStringMatch.h"
#include <iostream>

// Brute-force matching: given text strText and pattern strPattern
// return true if strPattern is an exact substring of strText, and false otherwise
bool ECStrMatchBruteForce(const string &strText, const string &strPattern)
{
    int n = strText.length();
    int m = strPattern.length();
    
    for (int i = 0; i <= n - m; ++i)
    {
        int j = 0;
        while (j < m && strText[i + j] == strPattern[j])
        {
            j++;
        }
        if (j == m)
        {
            return true;  // Match found
        }
    }
    return false;  // No match found
}


// C++ library based striing matching: simply call C++ string's find function
// This function is given; DON'T CHANGE IT
bool ECStrMatchBuiltIn(const string &strText, const string &strPattern)
{
    return strText.find(strPattern) != string::npos;
}

// Implement a slightly more complicated algorithm based on nummerical computation
// given text strText and pattern strPattern, an integer d, a prime number q 
// return true if strPattern is an exact substring of strText, and false otherwise
// The algorithm would work as follows:
// For each position i of strText, convert the subtring strText[i..i+length(strPattern)]
// to an integer (where d is the base of this integer) and then take modulo of q
// We also convert strPattern to an integer P in the same way. Then we simply compare 
// the integers constructed from strText. The key is, if the text integer doesn't match
// P, then the corresponding substring cannot match strPattern. Only when 
// P is equal to the text integer, we would conduct a letter-by-letter check to see if
// there is indeed a match at this position 
// Be careful: you need to implement the above procedure efficiently; 
// a naive implementation would be even slower than the brute-force!
// Be sure to look for ways to make your code more efficient.
bool ECStrMatchNumCompare(const string &strText, const string &strPattern, int d, int q)
{
    int n = strText.length();
    int m = strPattern.length();
    if (m > n) return false;

    int h = 1;
    int pHash = 0;  // Hash value for pattern
    int tHash = 0;  // Hash value for the current window of text

    // The value of h would be "pow(d, m-1) % q"
    for (int i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate the hash value of the pattern and the first window of text
    for (int i = 0; i < m; i++)
    {
        pHash = (d * pHash + strPattern[i]) % q;
        tHash = (d * tHash + strText[i]) % q;
    }

    // Slide the pattern over text one by one
    for (int i = 0; i <= n - m; i++)
    {
        // If the hash values match, check for characters one by one
        if (pHash == tHash)
        {
            bool match = true;
            for (int j = 0; j < m; j++)
            {
                if (strText[i + j] != strPattern[j])
                {
                    match = false;
                    break;
                }
            }
            if (match)
                return true;  // Match found
        }

        // Calculate hash value for the next window of text
        if (i < n - m)
        {
            tHash = (d * (tHash - strText[i] * h) + strText[i + m]) % q;
            // We might get a negative value, convert it to positive
            if (tHash < 0)
                tHash = (tHash + q);
        }
    }

    return false;  // No match found
}


