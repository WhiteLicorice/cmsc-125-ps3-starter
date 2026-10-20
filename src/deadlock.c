#include "ps3.h"

static int visit(int node, int lock_count, int graph[64][64],
                 int color[64])
{
    (void)node;
    (void)lock_count;
    (void)graph;
    (void)color;
    /* TODO: Mark the current lock gray before searching its edges. */
    /* TODO: Inspect each possible outgoing lock-order edge. */
    /* TODO: Detect a back edge whose destination is gray. */
    /* TODO: Visit each white destination in the adjacency list. */
    /* TODO: Propagate a cycle result from a deeper visit. */
    /* TODO: Mark the current lock black after all edges are checked. */
    /* TODO: Return whether this part of the graph contains a cycle. */
    return -1;
}

int lock_graph_has_cycle(int lock_count, const int (*edges)[2], int edge_count)
{
    (void)lock_count;
    (void)edges;
    (void)edge_count;
    /* TODO: Require lock counts within the public range. */
    /* TODO: Require edge counts within the public range. */
    /* TODO: Fail when edges exist without an edge array. */
    int graph[64][64];
    int color[64];
    /* TODO: Reset every adjacency-list length before adding supplied edges. */
    /* TODO: Reset every depth-first color to white before graph scanning. */
    /* TODO: Read the source endpoint from each supplied edge. */
    /* TODO: Read the destination endpoint from each supplied edge. */
    /* TODO: Reject either endpoint outside the lock range. */
    /* TODO: Append each destination to its source lock's adjacency list. */
    /* TODO: Start a depth-first visit at each unvisited lock. */
    /* TODO: Stop when a visit finds a cycle. */
    /* TODO: Return one for a cycle and zero when no cycle exists. */
    /* TODO: Return failure for invalid graph input. */
    (void)graph;
    (void)color;
    (void)visit;
    return -1;
}
