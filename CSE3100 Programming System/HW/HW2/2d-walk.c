#include <stdio.h>
#include <stdlib.h>

double two_d_random(int n) {
    int visited[128][128] = {0};  
    int x = 0, y = 0; 
    int total_visited = 1;  
    int total_points = (2 * n - 1) * (2 * n - 1);  

    visited[n][n] = 1;  
    
    while (x > -n && x < n && y > -n && y < n) {
        
        int r = rand() % 4;
        if (r == 0) y++;  
        else if (r == 1) x++;  
        else if (r == 2) y--;  
        else if (r == 3) x--; 

        
        if (x > -n && x < n && y > -n && y < n) {
           
            if (!visited[x + n][y + n]) {
                visited[x + n][y + n] = 1;  
                total_visited++;
            }
        }
    }

    return (double)total_visited / total_points;
}

// Main function (do not change)
int main(int argc, char* argv[]) {
    int trials = 1000;
    int i, n, seed;

    if (argc == 2) seed = atoi(argv[1]);
    else seed = 12345;

    srand(seed);

    for (n = 1; n <= 64; n *= 2) {
        double sum = 0.;
        for (i = 0; i < trials; i++) {
            double p = two_d_random(n);
            sum += p;
        }
        printf("%d %.3lf\n", n, sum / trials);
    }

    return 0;
}
