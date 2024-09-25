#include <stdio.h>
#include <stdlib.h>

/* This program should print the sum of the elements
 *     1^2, 2^2, 3^2, ..., n^2
 * where n is an integer provided by the user on the
 * command line. Hunt down the bugs and squash them!
 * Seek out the memory leaks and plug them up! */

/* Computes the sum of the first n elements in the array. */
int sum(int n, int* arr)
{
    // --------- I debugged using the man of arg to int to know which librarie I had to include, then i used 
    // print functions to display the value of arr[i] in the loop of the fillSquares function. The problem wasn't there because the value made sense
    // Then i printed the value of the sum, which wasn't according to the values that were supposed to be summed. So it was a hint to know what
    //was the problem. The problem was that the sum variable wasn't initialised to 0.
    int i, sum = 0;
    for(i = 0; i < n; i++){
        sum += arr[i];
    }
    return sum;
}

/* Fills the given array with the values
 * 1^2, 2^2, 3^2, ..., (n-1)^2, n^2. */
void fillSquares(int n, int* arr)
{
    int i;
    for(i = 1; i <= n; i++){
        arr[i-1] = i*i;
        printf("%d", arr[i-1]);
    }
        
}

/* Reads an integer n from arguments,
 * fills array with squares, and computes
 * the sum of the squares. Prints out the
 * sum before freeing all used memory. */
int main(int argc, char* argv[])
{
    int n, total;
    int* arr;

    // There must be at least 1 argument after the program
    // although only the first one is used.
    if(argc < 2) {
        printf("usage: ./squares n\n");
        return 1;
    }

    // convert the first argument from a string to a number
    n = atoi(argv[1]);
    if (n <= 0) {
        printf("n must be positive.");
        return 1;
    }
    arr = (int*) malloc(n * sizeof(int));
    
    //check if malloc worked properly
    if (arr == NULL) {
        printf("Malloc didn't worked properly ! \n");
        return 1;
    }

    fillSquares(n, arr);
    total = sum(n, arr);
    printf("total: %d\n", total);

    free(arr);
    return 0;
}