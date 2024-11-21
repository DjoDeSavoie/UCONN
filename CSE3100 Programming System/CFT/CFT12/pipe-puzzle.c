#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_LINE 80
#define MAX 100

void write_solution(int b[], int moves, int pd) {
    char buffer[MAX_LINE], temp_str[MAX_LINE];

    strcpy(buffer, "");
    for (int k = 0; k < moves; k++) {
        sprintf(temp_str, "->%d ", b[k]);
        strcat(buffer, temp_str);
    }
    strcat(buffer, "\n");

    // Write the solution to the pipe
    write(pd, buffer, strlen(buffer));
}

int read_solution(int pd, char buffer[]) {
    char c;
    int count = 0;
    while (read(pd, &c, 1) > 0) {
        if (c != '\n') {
            buffer[count] = c;
            count++;
        } else {
            buffer[count] = '\0';
            return 1;
        }
    }
    if (count > 0) {
        buffer[count] = '\0';
        return 1;
    }
    return 0;
}

// Recursive function to solve the puzzle
void solve_puzzle(int a[], int b[], int cur, int moves, int pd, int n) {
    if (moves > 10) return;  // Limit to 10 moves
    if (a[cur] == 0) {       // Reached index 9, solution found
        b[moves] = cur;
        write_solution(b, moves + 1, pd);
        return;
    }

    b[moves] = cur;  // Record the current index in the move list

    // Move forward (right)
    if (cur + a[cur] < n) {
        solve_puzzle(a, b, cur + a[cur], moves + 1, pd, n);
    }

    // Move backward (left)
    if (cur - a[cur] >= 0) {
        solve_puzzle(a, b, cur - a[cur], moves + 1, pd, n);
    }
}

int main(int argc, char *argv[]) {
    int a[] = {3, 6, 4, 1, 3, 4, 2, 5, 3, 0};  // The puzzle array
    int b[10];  // Array to store the walker's path
    int n = 10;  // Size of the puzzle

    int pd[2];
    if (pipe(pd) == -1) {
        perror("Error.");
        return -1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        // Child process: solve the puzzle
        close(pd[0]);  // Child doesn't read from pipe

        // Initialize the walker at index 0
        solve_puzzle(a, b, 0, 0, pd[1], n);

        close(pd[1]);  // Close write end of the pipe after solving
        return 0;
    }

    // Parent process: read the solutions from the pipe
    close(pd[1]);  // Parent only reads, so close write end

    int status;
    waitpid(pid, &status, 0);  // Wait for child process to finish

    char buffer[MAX_LINE];
    int count = 0;
    char results[MAX][MAX_LINE];

    // Read all solutions from the pipe
    while (read_solution(pd[0], buffer)) {
        strcpy(results[count++], buffer);
    }

    printf("Found solutions %d times.\n", count);

    // Find the shortest solution
    int min_len = strlen(results[0]);
    int min_k = 0;
    for (int i = 1; i < count; i++) {
        if (strlen(results[i]) < strlen(results[min_k])) {
            min_len = strlen(results[i]);
            min_k = i;
        }
    }

    // Print the shortest solution
    printf("%d moves in the shortest solution.\n", min_len / 4);  // Each move is '->N '
    printf("Shortest solution:\n%s\n", results[min_k]);

    close(pd[0]);  // Close read end of the pipe
    return 0;
}
