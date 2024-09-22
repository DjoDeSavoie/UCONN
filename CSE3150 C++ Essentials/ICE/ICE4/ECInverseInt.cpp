#include <string>
using namespace std;

// Function to reverse the digits of a string representing an integer
string ECInverseInt(string x)
{
    // Check if the number is negative
    bool isNegative = (x[0] == '-');
    
    // Set the starting point for reversal
    int start = isNegative ? 1 : 0;
    
    // Manually reverse the string
    int end = x.size() - 1;
    while (start < end)
    {
        // Swap the characters at 'start' and 'end'
        char temp = x[start];
        x[start] = x[end];
        x[end] = temp;

        // Move pointers toward the center
        start++;
        end--;
    }

    // Remove leading zeros
    int i = isNegative ? 1 : 0; // Start after the negative sign, if present
    while (i < x.size() && x[i] == '0') {
        i++;
    }

    // If all digits are zeros, keep one zero
    if (i == x.size()) {
        return isNegative ? "-0" : "0";
    }

    // Return the result after trimming leading zeros
    return (isNegative ? "-" : "") + x.substr(i);
}