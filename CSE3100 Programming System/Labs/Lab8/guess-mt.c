#define _POSIX_C_SOURCE      199309L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>

// search TODO to find the place you need to work on

void die(char *s)
{
    fprintf(stderr, "Error: %s\n", s);
    if (errno)
        perror("errno");
    exit(EXIT_FAILURE);
}

void check_pthread_return(int rv, char *msg)
{
    if (rv == 0)
        return;
    errno = rv;
    die(msg);
}

#define MAX_VALUE       1000
#define MSG_BUF_SIZE    100

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

/********* thread specific **************/

void my_msleep(int r)
{
    // limit to 100ms
    struct timespec req = {0, (r % 100 + 1) * 1000000};

    // printf("%ld\n", req.tv_nsec);
    nanosleep(&req, NULL);
}

/* both threads will communicate with the fields in this structure */

// status values, S_GUESS means guess is ready, and so on
// We could use only two values to indicate data from thread P or C is ready
// You can change the status values, if you like.
enum {S_INIT, S_GUESS, S_RESULT, S_MAX};

// You may change (add or delete) the fields in the structure,
// but it is not necessary.
//
// Alternative ways:
//
//      We could use other synchornization mechanisms, e.g., barriers
//      Even with condition, we could use one or three condition varaibles.
//
//      We could define two status fields, one for each condition variable.  
//      If you feel it is easier, you can add another status field. 
//
//      We could use a single int field to pass value between two threads, 
//      instead of using three: max, guess, and result 
typedef struct thread_arg_tag {
    int seed;
    int max;
    int guess;
    int result;
    char message[MSG_BUF_SIZE];     // final message
    int status;                     // status for condition
    pthread_mutex_t mutex;
    pthread_cond_t cond_guess;      // indicate guess is ready
    pthread_cond_t cond_result;     // indicate result is ready
} thread_arg_t;


// Thread C main function. This is the thread that generates the random number.
// 
// This thread does not print any characters, except for error messages.


void * thread_c(void * arg_in)
{
    thread_arg_t *arg = arg_in;

    gmn_t gmn;
    gmn_init(&gmn, arg->seed);
    my_msleep(rand());


    // TODO
    //  send max value
    //  repeat the following until guess is correct 
    //      wait for a guess from thread_p 
    //      call gmn_check() 
    //      send the result and, if the guess is correct, the final message to thread_p

    // Send max value to thread_p
    pthread_mutex_lock(&arg->mutex);
    arg->max = gmn_get_max();
    arg->status = S_MAX;
    pthread_cond_signal(&arg->cond_result); // Notify that max value is set
    pthread_mutex_unlock(&arg->mutex);

    // Repeat until the guess is correct
    int done = 0;
    while (!done) {
        pthread_mutex_lock(&arg->mutex);

        // Wait until thread_p makes a guess
        while (arg->status != S_GUESS) {
            pthread_cond_wait(&arg->cond_guess, &arg->mutex);
        }

        // Check the guess
        int result = gmn_check(&gmn, arg->guess);
        arg->result = result;
        if (result == 0) { // Correct guess
            strcpy(arg->message, gmn_get_message(&gmn));
            done = 1;
        }

        // Signal thread_p that result is ready
        arg->status = S_RESULT;
        pthread_cond_signal(&arg->cond_result);
        pthread_mutex_unlock(&arg->mutex);
    }

    return NULL;
}

// Thread P main function. This is the thread that guesses the number.
void * thread_p(void *arg_in)
{
    thread_arg_t *arg = arg_in;

    int min = 1;
    int max;
    int guess;
    int result;

    my_msleep(arg->seed);

    // Wait for max from thread_c
    pthread_mutex_lock(&arg->mutex);
    while (arg->status != S_MAX) {
        pthread_cond_wait(&arg->cond_result, &arg->mutex);
    }
    max = arg->max;
    pthread_mutex_unlock(&arg->mutex);

    // Guessing loop
    do {
        guess = (min + max) / 2;
        printf("My guess: %d\n", guess);

        // Send guess to thread_c
        pthread_mutex_lock(&arg->mutex);
        arg->guess = guess;
        arg->status = S_GUESS;
        pthread_cond_signal(&arg->cond_guess); // Notify thread_c of the guess

        // Wait for result from thread_c
        while (arg->status != S_RESULT) {
            pthread_cond_wait(&arg->cond_result, &arg->mutex);
        }
        result = arg->result;

        // Adjust min/max based on result
        if (result > 0) {
            min = guess + 1;
        } else if (result < 0) {
            max = guess - 1;
        }
        pthread_mutex_unlock(&arg->mutex);
    } while (result != 0);

    // Print the final message
    printf("%s", arg->message);

    return NULL;
}

int main(int argc, char *argv[])
{
    int seed = 5050;
    int demo = 0;

    // Parse the command line arguments
    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "demo")) {
            demo = 1;
        } else if (isdigit(argv[i][0])) {
            seed = atoi(argv[i]);
            if (seed <= 0)
                die("seed is 0 or it is too large.");
        } else {
            fprintf(stderr, "Usage: %s [<seed>] [demo]\n", argv[0]);
            return 1;
        }
    }

    if (demo) {
        guess_my_number(seed);
        exit(0);
    }

    thread_arg_t arg;
    arg.seed = seed;
    arg.status = S_INIT;

    // Initialize mutex and condition variables
    pthread_mutex_init(&arg.mutex, NULL);
    pthread_cond_init(&arg.cond_guess, NULL);
    pthread_cond_init(&arg.cond_result, NULL);

    // Create threads
    pthread_t thread_c_id, thread_p_id;
    check_pthread_return(pthread_create(&thread_c_id, NULL, thread_c, &arg), "Failed to create thread C");
    check_pthread_return(pthread_create(&thread_p_id, NULL, thread_p, &arg), "Failed to create thread P");

    // Wait for threads to finish
    pthread_join(thread_c_id, NULL);
    pthread_join(thread_p_id, NULL);

    // Clean up
    pthread_mutex_destroy(&arg.mutex);
    pthread_cond_destroy(&arg.cond_guess);
    pthread_cond_destroy(&arg.cond_result);

    return 0;
}