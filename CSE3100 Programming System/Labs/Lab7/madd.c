#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;

/* the main function of threads */
static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t *args = (thread_arg_t *)p_arg;
    unsigned int start_row, end_row;
    unsigned int rows_per_thread = args->m->nrows / NUM_THREADS;

    // Calculate start and end rows for this thread
    start_row = args->id * rows_per_thread;
    end_row = (args->id == NUM_THREADS - 1) ? args->m->nrows : start_row + rows_per_thread;

    for (unsigned int i = start_row; i < end_row; i++) {
        for (unsigned int j = 0; j < args->m->ncols; j++) {
            args->t->data[i][j] = args->m->data[i][j] + args->n->data[i][j];
        }
    }

    return NULL;
}

/* Return the sum of two matrices. The result is in a newly creaed matrix. 
 *
 * If a pthread function fails, report error and exit. 
 * Return NULL if something else is wrong.
 *
 * Similar to addMatrix, but this function uses 2 threads.
 */
TMatrix * addMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->nrows != n->nrows || m->ncols != n->ncols )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, m->ncols);
    if (t == NULL)
        return t;

    // TODO
    pthread_t threads[NUM_THREADS];
    thread_arg_t thread_args[NUM_THREADS];

    // Create threads
    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].id = i;
        thread_args[i].m = m;
        thread_args[i].n = n;
        thread_args[i].t = t;
        
        if (pthread_create(&threads[i], NULL, thread_main, &thread_args[i]) != 0) {
            perror("Failed to create thread");
            freeMatrix(t);
            return NULL;
        }
    }

    // Join threads
    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    
    return t;
}
