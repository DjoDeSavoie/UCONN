// Given two arrays of integers, return true (and also store the smallest integer that is in both arrays). Return false if no such integer exists 
// For example, suppose A1={1, 5, 3, 1} and A2={3, 7, 2}. Then ECCommonNumber(A1, 4, A2, 3, val) would return true (and val would be 3 after function call returns). Here, A1 is the first array, 4 is the size of the first array, A2 is the second array and 3 is the size of the second array. 
// Note: you must implement your algorithm as efficiently as possible
// Also, you need to define the function yourself: how are you going to take
// Tip: don't reinvent the wheel; try to use C++ standard library functions

#include <cstring>
#include <algorithm>
using namespace std;

// Function to find the smallest common number between two arrays using pointers
bool ECCommonNumber(const int *A, int szA, const int *B, int szB, int &val) {
    bool found = false;       // indicate if a common number is found
    int smallestCommon = -1;  // store the smallest common number

    // copies of A and B because we will modify them by sorting
    int *sortedA = new int[szA];
    int *sortedB = new int[szB];

    // Copy the elements from A and B to the sorted arrays
    std::copy(A, A + szA, sortedA);
    std::copy(B, B + szB, sortedB);

    // Sort the copied arrays
    std::sort(sortedA, sortedA + szA);
    std::sort(sortedB, sortedB + szB);

    // Iterate through the first sorted array and search in the second using binary search
    for (int i = 0; i < szA; ++i) {
        if (std::binary_search(sortedB, sortedB + szB, sortedA[i])) {
            // If a common number is found, update the smallest common number
            if (!found || sortedA[i] < smallestCommon) {
                smallestCommon = sortedA[i];
                found = true;
            }
        }
    }

    // Clean up dynamically allocated memory
    delete[] sortedA;
    delete[] sortedB;

    if (found) {
        val = smallestCommon;  // Update val with the smallest common number
        return true;           // Return true if a common number was found
    }

    return false;  // Return false if no common number was found
}

