#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//TODO
//Implement the below function
//Simulate one particle moving n steps in random directions
//Use a random number generator to decide which way to go at every step
//When the particle stops at a final location, use the memory pointed to by grid to 
//record the number of particles that stop at this final location
//Feel free to declare, implement and use other functions when needed

void one_particle(int *grid, int n) {
    // Start at the origin (0, 0, 0)
    int x = 0, y = 0, z = 0;

    // Simulate n steps
    for (int i = 0; i < n; i++) {
        int direction = rand() % 6;  // Random direction from 0 to 5
        switch(direction) {
            case 0: x -= 1; break;  // Move left (x decreases)
            case 1: x += 1; break;  // Move right (x increases)
            case 2: y -= 1; break;  // Move down (y decreases)
            case 3: y += 1; break;  // Move up (y increases)
            case 4: z -= 1; break;  // Move backward (z decreases)
            case 5: z += 1; break;  // Move forward (z increases)
        }
    }

    // Map the 3D coordinates (x, y, z) to a 1D array index in grid
    int index = (x + n) * (2 * n + 1) * (2 * n + 1) + (y + n) * (2 * n + 1) + (z + n);
    grid[index] += 1;  // Increment particle count at the final location
}


//TODO
//Implement the following function
//This function returns the fraction of particles that lie within the distance
//r*n from the origin (including particles exactly r*n away)
//The distance used here is Euclidean distance
//Note: you will not have access to math.h when submitting on Mimir
double density(int *grid, int n, double r) {
    int radius_squared = (int)((r * n) * (r * n));  // (r * n)^2 for comparison
    int total_particles = 0;
    int inside_count = 0;

    // Iteraye over all possible (x, y, z) positions in the grid
    for (int x = -n; x <= n; x++) {
        for (int y = -n; y <= n; y++) {
            for (int z = -n; z <= n; z++) {
                int index = (x + n) * (2 * n + 1) * (2 * n + 1) + (y + n) * (2 * n + 1) + (z + n);
                int dist_squared = x*x + y*y + z*z;

                if (dist_squared <= radius_squared) {
                    inside_count += grid[index];
                }
                total_particles += grid[index];
            }
        }
    }

    return (double)inside_count / total_particles;  // Proportion within radius
}


//use this function to print results
void print_result(int *grid, int n)
{
    printf("radius density\n");
    for(int k = 1; k <= 20; k++)
    {
        printf("%.2lf   %lf\n", 0.05*k, density(grid, n, 0.05*k));
    }
}

//TODO
//Finish the following function
//See the assignment decription on Piazza for more details
void diffusion(int n, int m)
{
	//fill in a few line of code below
	// Allocate memory for the grid, where the grid is (2n+1)^3 in size
    int grid_size = (2 * n + 1) * (2 * n + 1) * (2 * n + 1);
    int *grid = (int *)calloc(grid_size, sizeof(int));  // Initialize grid to 0

	for(int i = 1; i<=m; i++) one_particle(grid, n);

	print_result(grid, n);
	//fill in some code below
	free(grid);

}

int main(int argc, char *argv[])
{
	
	if(argc != 3)
	{
		printf("Usage: %s n m\n", argv[0]);
		return 0; 
	}
	int n = atoi(argv[1]);
	int m = atoi(argv[2]);

	assert(n >= 1 && n <=50);
	assert(m >= 1 && m <= 1000000);
	srand(12345);
	diffusion(n, m);
	return 0;
}