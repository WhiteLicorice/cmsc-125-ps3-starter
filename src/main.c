#include "ps3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int run_case(FILE *input)
{
    char kind[24];
    if (fscanf(input, "%23s", kind) != 1)
        return 1;
    if (strcmp(kind, "counter") == 0) {
        int workers;
        int increments;
        long total = 0;
        if (fscanf(input, "%d %d", &workers, &increments) != 2 ||
            run_counter(workers, increments, &total) != 0)
            return 1;
        printf("counter total=%ld\n", total);
        return 0;
    }
    if (strcmp(kind, "queue") == 0) {
        char mode[24];
        int producers;
        int consumers;
        int items;
        int capacity;
        int items_consumed = 0;
        long sum = 0;
        enum queue_kind queue_kind;
        if (fscanf(input, "%23s %d %d %d %d", mode, &producers,
                   &consumers, &items, &capacity) != 5)
            return 1;
        if (strcmp(mode, "condvar") == 0)
            queue_kind = QUEUE_CONDVAR;
        else if (strcmp(mode, "semaphore") == 0)
            queue_kind = QUEUE_SEMAPHORE;
        else
            return 1;
        if (run_queue(queue_kind, producers, consumers, items,
                      capacity, &items_consumed, &sum) != 0)
            return 1;
        printf("queue kind=%s items=%d sum=%ld\n", mode,
               items_consumed, sum);
        return 0;
    }
    if (strcmp(kind, "deadlock") == 0) {
        int locks;
        int edge_count;
        int edges[64][2];
        if (fscanf(input, "%d %d", &locks, &edge_count) != 2 ||
            locks < 1 || locks > 64 || edge_count < 0 || edge_count > 64)
            return 1;
        for (int i = 0; i < edge_count; ++i) {
            if (fscanf(input, "%d %d", &edges[i][0], &edges[i][1]) != 2)
                return 1;
        }
        int cycle = lock_graph_has_cycle(locks,
                                         (const int (*)[2])edges,
                                         edge_count);
        if (cycle < 0)
            return 1;
        printf("lock-order cycle=%s\n", cycle ? "yes" : "no");
        return 0;
    }
    return 1;
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        FILE *input = fopen(argv[1], "r");
        if (input == NULL) {
            perror("ps3: cannot open case");
            return 2;
        }
        int result = run_case(input);
        fclose(input);
        if (result != 0) {
            fputs("ps3: case failed\n", stderr);
            return 1;
        }
        return 0;
    }
    if (argc == 4 && strcmp(argv[1], "counter") == 0) {
        char *end;
        long workers = strtol(argv[2], &end, 10);
        if (*end != '\0' || workers < 1 || workers > 256)
            return 2;
        long increments = strtol(argv[3], &end, 10);
        if (*end != '\0' || increments < 1 || increments > 10000000)
            return 2;
        long total = 0;
        if (run_counter((int)workers, (int)increments, &total) != 0)
            return 1;
        printf("counter total=%ld\n", total);
        return 0;
    }
    fputs("usage: run <case-file> | run counter <workers> <increments>\n",
          stderr);
    return 2;
}
