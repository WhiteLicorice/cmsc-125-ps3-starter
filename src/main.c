#include "ps3.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int at_end_of_input(FILE *input)
{
    int ch;
    while ((ch = fgetc(input)) != EOF) {
        if (!isspace((unsigned char)ch))
            return 0;
    }
    return 1;
}

static int parse_long(const char *text, long *out)
{
    char *end;
    long value;

    errno = 0;
    value = strtol(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0')
        return -1;
    *out = value;
    return 0;
}

static int read_long(FILE *input, long *out)
{
    char text[32];

    if (fscanf(input, "%31s", text) != 1)
        return -1;
    return parse_long(text, out);
}

static int read_int(FILE *input, long low, long high, int *out)
{
    long value;

    if (read_long(input, &value) != 0 || value < low || value > high)
        return -1;
    *out = (int)value;
    return 0;
}

static int run_case(FILE *input)
{
    char kind[24];
    if (fscanf(input, "%23s", kind) != 1)
        return 1;
    if (strcmp(kind, "counter") == 0) {
        int workers;
        int increments;
        long total = 0;
        if (read_int(input, 1, 256, &workers) != 0 ||
            read_int(input, 1, 10000000, &increments) != 0)
            return 1;
        if (!at_end_of_input(input))
            return 1;
        if (run_counter(workers, increments, &total) != 0)
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
        if (fscanf(input, "%23s", mode) != 1)
            return 1;
        if (read_int(input, 1, 64, &producers) != 0 ||
            read_int(input, 1, 64, &consumers) != 0 ||
            read_int(input, 0, 100000, &items) != 0 ||
            read_int(input, 1, 256, &capacity) != 0)
            return 1;
        if (strcmp(mode, "condvar") == 0)
            queue_kind = QUEUE_CONDVAR;
        else if (strcmp(mode, "semaphore") == 0)
            queue_kind = QUEUE_SEMAPHORE;
        else
            return 1;
        if (!at_end_of_input(input))
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
        if (read_int(input, 1, 64, &locks) != 0 ||
            read_int(input, 0, 64, &edge_count) != 0)
            return 1;
        for (int i = 0; i < edge_count; ++i) {
            long from;
            long to;
            if (read_long(input, &from) != 0 ||
                read_long(input, &to) != 0)
                return 1;
            if (from < INT_MIN || from > INT_MAX ||
                to < INT_MIN || to > INT_MAX)
                return 1;
            edges[i][0] = (int)from;
            edges[i][1] = (int)to;
        }
        if (!at_end_of_input(input))
            return 1;
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
