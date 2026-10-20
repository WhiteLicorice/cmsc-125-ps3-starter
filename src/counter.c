#include "ps3.h"

#include <stdlib.h>

struct counter_state {
    pthread_mutex_t mutex;
    long value;
    int increments;
};

struct counter_arg {
    struct counter_state *state;
};

static void *count_work(void *data)
{
    struct counter_arg *arg = data;
    /* TODO: Read the shared state pointer from the worker argument. */
    /* TODO: Repeat the worker's requested number of increments. */
    /* TODO: Lock the mutex before each shared read. */
    /* TODO: Copy the protected total into a local value. */
    /* TODO: Add one to the local value. */
    /* TODO: Store the new total while the mutex remains locked. */
    /* TODO: Unlock the mutex after each shared write. */
    /* TODO: Return a result that lets the joiner detect worker failure. */
    (void)arg;
    return NULL;
}

int run_counter(int workers, int increments, long *total)
{
    (void)workers;
    (void)increments;
    (void)total;
    /* TODO: Validate worker counts against the run contract. */
    /* TODO: Validate increments against the run contract. */
    /* TODO: Require a nonnull output pointer. */
    /* TODO: Allocate one thread handle for every worker. */
    /* TODO: Allocate one argument record for every worker. */
    /* TODO: Check the thread handle allocation. */
    /* TODO: Check the worker argument allocation. */
    /* TODO: Set the shared total to zero. */
    /* TODO: Store the increment limit in the shared state. */
    /* TODO: Initialize the mutex before starting workers. */
    /* TODO: Store the shared-state pointer in each worker argument. */
    /* TODO: Create each worker thread. */
    /* TODO: Record how many worker threads started. */
    /* TODO: Stop creating workers after the first creation error. */
    /* TODO: Join every worker that started. */
    /* TODO: Record a join error without skipping later joins. */
    /* TODO: Lock the mutex before reading the final shared total. */
    /* TODO: Copy the protected total to the caller's output. */
    /* TODO: Unlock the mutex after copying the result. */
    /* TODO: Destroy the mutex after every worker has joined. */
    /* TODO: Free the worker argument records. */
    /* TODO: Free the thread handle array. */
    /* TODO: Return failure when setup, creation, or joining failed. */
    (void)count_work;
    return -1;
}
