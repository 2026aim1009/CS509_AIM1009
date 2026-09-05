#include "vertex_coloring.h"
#include <algorithm>
#include <numeric>

ColoringResult greedyVertexColoring(const CSRGraph& graph, int V) {
    ColoringResult result;
    result.colors.assign(V, -1);
    result.numColors = 0;

    if (V == 0) {
        return result;
    }

    // Step 1: degree of every vertex, straight from CSR row_ptr.
    vector<int> degree(V);
    for (int v = 0; v < V; v++) {
        degree[v] = graph.row_ptr[v + 1] - graph.row_ptr[v];
    }

    // Step 2: Welsh-Powell ordering -- vertices sorted by non-increasing
    // degree. Ties broken by vertex id for reproducibility.
    vector<int> order(V);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&degree](int a, int b) {
        if (degree[a] != degree[b]) return degree[a] > degree[b];
        return a < b;
    });

    // Step 3: process vertices in that order, assigning the smallest
    // color not used by any already-colored neighbour.
    int maxColorUsed = -1;
    for (int idx = 0; idx < V; idx++) {
        int u = order[idx];

        // Colors currently used by u's already-colored neighbours.
        // Sized to (degree[u] + 1): the mex of at most degree[u] used
        // colors can never exceed degree[u].
        vector<bool> usedColor(degree[u] + 1, false);
        for (int e = graph.row_ptr[u]; e < graph.row_ptr[u + 1]; e++) {
            int nb = graph.col_idx[e];
            int c = result.colors[nb];
            if (c >= 0 && c < (int)usedColor.size()) {
                usedColor[c] = true;
            }
        }

        int chosen = 0;
        while (chosen < (int)usedColor.size() && usedColor[chosen]) {
            chosen++;
        }

        result.colors[u] = chosen;
        if (chosen > maxColorUsed) maxColorUsed = chosen;
    }

    result.numColors = maxColorUsed + 1;
    return result;
}

bool isValidColoring(const CSRGraph& graph, int V, const vector<int>& colors) {
    for (int u = 0; u < V; u++) {
        for (int e = graph.row_ptr[u]; e < graph.row_ptr[u + 1]; e++) {
            int nb = graph.col_idx[e];
            if (nb != u && colors[u] == colors[nb]) {
                return false;
            }
        }
    }
    return true;
}
