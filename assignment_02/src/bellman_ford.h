#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include <vector>
#include "csr.h"

using namespace std;

struct BellmanFordResult {
    vector<int> distance;
    bool negativeCycle;
};

extern const int BELLMAN_FORD_INF;

// graph: CSR representation of a directed, weighted graph (weights may be negative)
// V: number of vertices, source: source vertex
BellmanFordResult bellmanFord(const CSRGraph& graph, int V, int source);

#endif