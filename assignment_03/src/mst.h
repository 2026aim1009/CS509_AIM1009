#ifndef MST_H
#define MST_H

#include <vector>
#include "csr.h"

using namespace std;

struct MSTEdge {
    int u;
    int v;
    long long weight;
};

struct MSTResult {
    vector<MSTEdge> edges;
    long long totalWeight;
    bool connected; // true iff exactly V-1 edges were selected (spanning tree)
};

// graph: CSR representation of a weighted, undirected graph. Every
//        undirected edge must appear once in each endpoint's adjacency
//        list (as guaranteed by the Section 5.1 input format / CSR
//        conversion), with the same weight on both sides.
// V:     number of vertices.

// Kruskal's algorithm: sorts all edges by weight and greedily adds an
// edge whenever it does not create a cycle (Disjoint Set Union check).
MSTResult kruskalMST(const CSRGraph& graph, int V);

// Prim's algorithm: grows a single tree from startVertex, repeatedly
// selecting the minimum-weight edge that connects the tree to a new
// vertex (min-priority queue over frontier keys).
MSTResult primMST(const CSRGraph& graph, int V, int startVertex = 0);

#endif
