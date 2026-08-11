#include "bellman_ford.h"
#include <climits>

const int BELLMAN_FORD_INF = INT_MAX;

BellmanFordResult bellmanFord(const CSRGraph& graph, int V, int source) {
    std::vector<int> distance(V, BELLMAN_FORD_INF);
    distance[source] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int u = 0; u < V; u++) {
            if (distance[u] == BELLMAN_FORD_INF) continue;
            for (int e = graph.row_ptr[u]; e < graph.row_ptr[u + 1]; e++) {
                int v = graph.col_idx[e];
                int w = graph.values[e];
                if (distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                }
            }
        }
    }

    // One extra pass: if anything still relaxes, a negative cycle is reachable
    bool negativeCycle = false;
    for (int u = 0; u < V && !negativeCycle; u++) {
        if (distance[u] == BELLMAN_FORD_INF) continue;
        for (int e = graph.row_ptr[u]; e < graph.row_ptr[u + 1]; e++) {
            int v = graph.col_idx[e];
            int w = graph.values[e];
            if (distance[u] + w < distance[v]) {
                negativeCycle = true;
                break;
            }
        }
    }

    BellmanFordResult result;
    result.negativeCycle = negativeCycle;
    if (!negativeCycle) {
        result.distance = distance;
    }
    return result;
}