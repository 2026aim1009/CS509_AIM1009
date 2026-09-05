#include "pagerank.h"
#include <cmath>

PageRankResult computePageRank(const CSRGraph& graph, int V, double damping,
                                double tolerance, int maxIterations) {
    PageRankResult result;
    result.iterations = 0;
    result.converged = false;

    if (V == 0) {
        return result;
    }

    // Outdegree of every vertex, straight from CSR row_ptr.
    vector<int> outdeg(V);
    for (int v = 0; v < V; v++) {
        outdeg[v] = graph.row_ptr[v + 1] - graph.row_ptr[v];
    }

    // All vertices initialized with rank 1/N (Section 2.2).
    vector<double> rank(V, 1.0 / V);
    vector<double> newRank(V, 0.0);

    const double base = (1.0 - damping) / V;

    for (int iter = 1; iter <= maxIterations; iter++) {
        fill(newRank.begin(), newRank.end(), base);

        // Sum of rank mass held by dangling vertices (outdegree 0),
        // redistributed evenly across all vertices so no mass is lost.
        double danglingSum = 0.0;
        for (int u = 0; u < V; u++) {
            if (outdeg[u] == 0) {
                danglingSum += rank[u];
            }
        }
        double danglingShare = damping * danglingSum / V;

        for (int v = 0; v < V; v++) {
            newRank[v] += danglingShare;
        }

        // Distribute each non-dangling vertex's rank to its out-neighbours.
        for (int u = 0; u < V; u++) {
            if (outdeg[u] == 0) continue;
            double share = damping * rank[u] / outdeg[u];
            for (int e = graph.row_ptr[u]; e < graph.row_ptr[u + 1]; e++) {
                int v = graph.col_idx[e];
                newRank[v] += share;
            }
        }

        // Total change across all vertices (simultaneous update using
        // the previous iteration's values, per Section 2.2).
        double totalChange = 0.0;
        for (int v = 0; v < V; v++) {
            totalChange += fabs(newRank[v] - rank[v]);
        }

        rank.swap(newRank);
        result.iterations = iter;

        if (totalChange <= tolerance) {
            result.converged = true;
            break;
        }
    }

    result.ranks = rank;
    return result;
}
