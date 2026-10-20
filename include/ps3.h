#ifndef PS3_H
#define PS3_H

#include <pthread.h>
#include <semaphore.h>
#include <stddef.h>

enum queue_kind { QUEUE_CONDVAR, QUEUE_SEMAPHORE };

struct work_queue {
    enum queue_kind kind;
    int *items;
    int capacity;
    int head;
    int tail;
    int count;
    pthread_mutex_t mutex;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
    sem_t *empty;
    sem_t *full;
    char empty_name[64];
    char full_name[64];
};

int run_counter(int workers, int increments, long *total);
int run_queue(enum queue_kind kind, int producers, int consumers,
              int items_per_producer, int capacity, int *items_consumed,
              long *sum);
int lock_graph_has_cycle(int lock_count, const int (*edges)[2], int edge_count);

#endif
