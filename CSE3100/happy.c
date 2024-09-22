#include <stdio.h>
#include <stdlib.h>

int sum_of_squares(int n) {
    int sum = 0;
    while (n > 0) {
        int digit = n % 10;  // Get the last digit
        sum += digit * digit;  // Add the square of the digit to sum
        n /= 10;  // Remove the last digit
    }
    return sum;
}

int main() {
    int n;
    printf("n = ");
    scanf("%d", &n);
    int m = n;  // Store the original number

    // Start processing the number
    while (n != 1 && n != 4) {
        n = sum_of_squares(n);  // Calculate sum of squares of digits
        printf("%d\n", n);  // Print each intermediate number
    }
    
    // Final condition check (after printing 1 or 4)
    if (n == 1) 
        printf("%d is a happy number.\n", m);
    else 
        printf("%d is NOT a happy number.\n", m);

    return 0;
}
