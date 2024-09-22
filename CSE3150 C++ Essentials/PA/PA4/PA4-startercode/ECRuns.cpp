//
//  ECRuns.cpp
//  
//
//  Created by Yufeng Wu on 08/22/23.
//
//
#include <string>
#include <iostream>
using namespace std;

// Return the number of runs, and the list of starting positions of runs in the passed in array (which you can assume it is large enough)
int ECRuns(const string &str, int *pListPositions )
{
    if (str.empty()){
        return 0;
    }

    int numberRuns = 0;
    int startPosition = 0;

    for(size_t i = 0; i <= str.size(); i++){
        
        // If current character is different from the previous one or we have reached the end of the string
        if (i == str.size() || str[i] != str[i - 1])
        {
            // Store the starting position of the current run
            pListPositions[numberRuns] = startPosition;
            numberRuns++; // Increment the number of runs

            // Update the start position for the next run
            startPosition = i;
        }
    }

    return numberRuns;    
}

