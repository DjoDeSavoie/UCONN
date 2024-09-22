#include <string>
#include <iostream>

// You are given a list of integers listNumbers and its size
// These numbers are the permutaiton of the first sz integers, starting from 1
// After the function returns, listNumbers would contain the next permutation
// For example, if the list is 1 3 4 2  ==> 1 4 2 3
// Note: you don't need to check whether the given input is indeed a permutation
// That is, listNumbers always contains a valid permutation

void ECNextPermutation(int *listNumbers, int sz)
{
    // Your code here
    //We study the value of the penultimate number, to see if it is bigger or smaller than the last one
    //to see if there is an index where we can do a permutation
    int i = sz - 2;
    while (i >= 0 && listNumbers[i] >= listNumbers[i + 1])
    {
        --i;
    }

    if (i >= 0) // If such an index exists
    {
        //We find the largest index j greater than i such that listNumbers[i] < listNumbers[j]
        int j = sz - 1;
        while (listNumbers[j] <= listNumbers[i])
        {
            --j;
        }

        // Swap elements at indices i and j
        int temp = listNumbers[i];
        listNumbers[i] = listNumbers[j];
        listNumbers[j] = temp;
    }

  //Reverse the sequence from i + 1 to the end manually
    int left = i + 1;
    int right = sz - 1;
    while (left < right)
    {
        int temp = listNumbers[left];
        listNumbers[left] = listNumbers[right];
        listNumbers[right] = temp;
        ++left;
        --right;
    }
}