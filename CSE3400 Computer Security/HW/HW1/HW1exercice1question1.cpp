#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define VALUE 1254632

void measure_time_for_counter(int64_t num_iterations) {
    clock_t start_time = clock();
    
    for (int64_t i = 0; i < num_iterations; i++) {
        int result = i & VALUE;
    }

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Time taken for %lld iterations: %f seconds\n", num_iterations, elapsed_time);
}


int main() {
    printf("Exercice 1 Question 1...\n");

    // Test cases
    measure_time_for_counter(1 << 10);
    measure_time_for_counter(1 << 20);
    measure_time_for_counter(1 << 30);

    return 0;
}


// I have as a result for 2 ^ 30 a time of 2.938000, so to estimate the time of a counter incremented 2^480 times, 
//we can use the fact that 2^480 = 2.938000 * 2^450. The number of seconds in a year is 3,154e+7. So the number of years is : 
//( 2.938000 * 2^450) / (3,154e+7)
//2^450 is 2.907355e+135, so the number of years is  : (2.938000 * 2.907355e+135) / (3,154e+7) = 1.32 x 10e128 years
