#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>

// search TODO to find the place you need to work on

void die(char *s)
{
    fprintf(stderr, "Error: %s\n", s);
    if (errno)
        perror("errno");
    exit(EXIT_FAILURE);
}

#define MAX_VALUE       1000
#define MSG_BUF_SIZE    100
#define PIPEFD_READ 0
#define PIPEFD_WRITE 1

typedef  struct {
    int v;
    int num_attempts;
    char message[MSG_BUF_SIZE]; 
} gmn_t;

void gmn_init(gmn_t *pg, int seed)
{
    srand(seed);
    pg->v = rand() % MAX_VALUE + 1;
    pg->num_attempts = 0;
    strcpy(pg->message, "You have not got the right number yet.\n");
} 

int gmn_check(gmn_t *pg, int guess)
{
    pg->num_attempts ++;
    if (pg->v == guess) {
        snprintf(pg->message, MSG_BUF_SIZE, 
                "It took you %d attempt(s) to guess the number %d.\n", 
                pg->num_attempts, pg->v);  
        return 0;
    }
    if (pg->v > guess)
        return 1;
    return -1;
}

char * gmn_get_message(gmn_t *pg)
{
    return pg->message;
}

int    gmn_get_max()
{
    return MAX_VALUE;
}

// this function runs the demo session
// all gmn_ functions should be called in child process 
// and then send the result to the parent process
void guess_my_number(int seed)
{
    gmn_t gmn;

    // initialize the game
    gmn_init(&gmn, seed);

    int min = 1;
    int max = gmn_get_max();
    int result;

    do {
        // make a guess
        int guess = (min + max)/2;
        printf("My guess: %d\n", guess);

        // check
        result = gmn_check(&gmn, guess);

        // if not correct, prepare for the next guess
        if(result > 0) 
            min = guess + 1;
        else if(result < 0)
            max = guess - 1;
    } while (result != 0);

    // print out the final message
    fputs(gmn_get_message(&gmn), stdout);
}


// Tasks for the child process. 
// 
// Parameters:
//  fdp:    the pipe for parent to write and for child to read 
//  fdc:    the pipe for child to write and for parent to read
//  seed:   seed for the random numer
//
// This function should not return.
// This function does not print any characters, except for error messages.
void    child_main(int fdp[], int fdc[], int seed)
{
    gmn_t   gmn;

    gmn_init(&gmn, seed);

    // Close unused file descriptors
    close(fdp[PIPEFD_WRITE]);  // child doesn't write to parent
    close(fdc[PIPEFD_READ]);   // child doesn't read from parent

    // Send max value to the parent
    int max_value = gmn_get_max();
    if (write(fdc[PIPEFD_WRITE], &max_value, sizeof(int)) != sizeof(int)) {
        die("Failed to send max value to parent.");
    }

    int guess, result;
    do {
        // Wait for a guess from parent
        if (read(fdp[PIPEFD_READ], &guess, sizeof(int)) != sizeof(int)) {
            die("Failed to read guess from parent.");
        }

        // Check the guess
        result = gmn_check(&gmn, guess);

        // Send the result to the parent
        if (write(fdc[PIPEFD_WRITE], &result, sizeof(int)) != sizeof(int)) {
            die("Failed to send result to parent.");
        }
    } while (result != 0);

    // Send the final message back (as a string)
    char *message = gmn_get_message(&gmn);
    if (write(fdc[PIPEFD_WRITE], message, strlen(message)) != strlen(message)) {
        die("Failed to send final message to parent.");
    }

    // Close all pipe file descriptors
    close(fdp[PIPEFD_READ]);
    close(fdc[PIPEFD_WRITE]);

    exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[])
{
    int seed = 3100;
    int demo = 0;

    // parse the command line arguments
    for (int i = 1; i < argc; i ++) {
        if (! strcmp(argv[i], "demo")) {
            demo = 1;
        } else if (! strcmp(argv[i], "-h")) {
            fprintf(stderr, "Usage: %s [<seed>] [demo]\n", argv[0]);
            return 1;
        } else {
            seed = atoi(argv[i]);
            if (seed <= 0)
                die("seed must be a postive number.");
        }
    }

    if (demo) {
        guess_my_number(seed);
        exit(0);
    }

    // Now, we do it using two processes
    // The child generates a random number
    // The parent tries to guess the number.
    // The child tells the parent

    // two pipes
    // fdp : parent writes
    // fdc : child writes
    
    int fdp[2], fdc[2];

    //pipe creation
    if (pipe(fdp) == -1)
        die("pipe() failed.");

    if (pipe(fdc) == -1)
        die("pipe() failed.");

    pid_t pid = fork();

    if (pid < 0)
        die("fork() failed.");

    if(pid == 0)
        child_main(fdp, fdc, seed); // never returns
    
    // parent continues
    
    int min = 1;
    int max;
    int guess;
    int result;

    // Close unused pipe file descriptors
    close(fdp[PIPEFD_READ]);  // parent doesn't read from this pipe
    close(fdc[PIPEFD_WRITE]); // parent doesn't write to this pipe

    // Get max from the child
    if (read(fdc[PIPEFD_READ], &max, sizeof(int)) != sizeof(int)) {
        die("Failed to receive max value from child.");
    }
    
    do {
        guess = (min + max) / 2;
        printf("My guess: %d\n", guess);

        // Send guess to the child
        if (write(fdp[PIPEFD_WRITE], &guess, sizeof(int)) != sizeof(int)) {
            die("Failed to send guess to child.");
        }

        // Wait for the result from the child
        if (read(fdc[PIPEFD_READ], &result, sizeof(int)) != sizeof(int)) {
            die("Failed to read result from child.");
        }

        // Adjust range based on result
        if (result > 0)
            min = guess + 1;
        else if (result < 0)
            max = guess - 1;
    } while (result != 0);

    // Flush stdout buffer
    fflush(stdout);

    // Receive the final message and print it to stdout
    char buffer[MSG_BUF_SIZE];
    ssize_t n;
    while ((n = read(fdc[PIPEFD_READ], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[n] = '\0';  // null-terminate the string
        fputs(buffer, stdout);
    }

    // Close all pipe file descriptors
    close(fdc[PIPEFD_READ]);
    close(fdp[PIPEFD_WRITE]);

    // Wait for the child process to finish
    wait(NULL);

    return 0;
}
