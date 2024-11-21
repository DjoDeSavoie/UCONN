#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "matrix.h"

// Search TODO to find the locations where code needs to be completed

#define     NUM_THREADS     2

typedef struct {
    unsigned int id;
    TMatrix *m, *n, *t;
} thread_arg_t;


static void * thread_main(void * p_arg)
{
    // TODO
    thread_arg_t *args = (thread_arg_t *)p_arg;
    unsigned int id = args->id;
    TMatrix *m = args->m;
    TMatrix *n = args->n;
    TMatrix *t = args->t;

    unsigned int rows_per_thread = (m->nrows + NUM_THREADS - 1) / NUM_THREADS;
    unsigned int start_row = id * rows_per_thread;
    unsigned int end_row = (start_row + rows_per_thread > m->nrows) ? m->nrows : start_row + rows_per_thread;

    for (unsigned int i = start_row; i < end_row; i++) {
        for (unsigned int j = 0; j < n->ncols; j++) {
            int sum = 0;
            for (unsigned int k = 0; k < m->ncols; k++) {
                sum += m->data[i][k] * n->data[k][j];
            }
            t->data[i][j] = sum;
        }
    }

    return NULL;
}

/* Return the sum of two matrices.
 *
 * If any pthread function fails, report error and exit. 
 * Return NULL if anything else is wrong.
 *
 * Similar to mulMatrix, but with multi-threading.
 */
TMatrix * mulMatrix_thread(TMatrix *m, TMatrix *n)
{
    if (    m == NULL || n == NULL
         || m->ncols != n->nrows )
        return NULL;

    TMatrix * t = newMatrix(m->nrows, n->ncols);
    if (t == NULL)
        return t;

    // TODO

    pthread_t threads[NUM_THREADS];
    thread_arg_t thread_args[NUM_THREADS];

    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].id = i;
        thread_args[i].m = m;
        thread_args[i].n = n;
        thread_args[i].t = t;
        
        if (pthread_create(&threads[i], NULL, thread_main, &thread_args[i]) != 0) {
            fprintf(stderr, "Error creating thread %u\n", i);
            freeMatrix(t);
            return NULL;
        }
    }

    for (unsigned int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            fprintf(stderr, "Error joining thread %u\n", i);
            freeMatrix(t);
            return NULL;
        }
    }

    return t;
}
