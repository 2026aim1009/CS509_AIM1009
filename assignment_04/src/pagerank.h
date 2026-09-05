#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>
#include "csr.h"

using namespace std;

struct PageRankResult {
    vector<double> ranks;
    int iterations;
    bool converged;
};

// graph: CSR representation of an unweighted, directed graph. Only the
//        outgoing edges of each vertex are stored (Section 6.1).
// V:     number of vertices.
// damping, tolerance, maxIterations: parsed from the input file.
//
// PR(v) = (1 - d) / N + d * sum_{u -> v} ( PR(u) / outdegree(u) )
//
// A dangling vertex (outdegree 0) contributes its rank evenly across
// all vertices instead of being dropped, so the total rank mass stays
// approximately 1.0 after every iteration. Iteration stops when the
// total absolute change across all vertices is <= tolerance, or when
// maxIterations is reached.
PageRankResult computePageRank(const CSRGraph& graph, int V, double damping,
                                double tolerance, int maxIterations);

#endif
