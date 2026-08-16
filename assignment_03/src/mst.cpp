#include "mst.h"
#include <algorithm>
#include <climits>
#include <queue>

namespace {

// Disjoint Set Union (Union-Find) with path compression and union by
// rank. Used internally by Kruskal's algorithm to detect cycles.
struct DSU {
    vector<int> parent;
    vector<int> rankArr;

    explicit DSU(int n) : parent(n), rankArr(n, 0) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find(int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]]; // path compression
            x = parent[x];
        }
        return x;
    }

    // Returns true if a and b were in different components (and were
    // merged); false if they were already connected.
    bool unite(int a, int b) {
        int ra = find(a);
        int rb = find(b);
        if (ra == rb) return false;

        if (rankArr[ra] < rankArr[rb]) swap(ra, rb);
        parent[rb] = ra;
        if (rankArr[ra] == rankArr[rb]) rankArr[ra]++;
        return true;
    }
};

} // namespace

MSTResult kruskalMST(const CSRGraph& graph, int V) {
    // Extract each undirected edge exactly once from the CSR
    // representation. Since every undirected edge appears in both
    // endpoints' adjacency lists, keeping only entries where the
    // neighbor index is greater than the current vertex avoids
    // processing the same edge twice. This extraction + the sort below
    // are part of Kruskal's algorithm and remain inside the timed call.
    vector<MSTEdge> allEdges;
    allEdges.reserve(graph.col_idx.size() / 2);
    for (int u = 0; u < V; u++) {
        for (int e = graph.row_ptr[u]; e < graph.row_ptr[u + 1]; e++) {
            int v = graph.col_idx[e];
            if (v > u) {
                allEdges.push_back(MSTEdge{u, v, graph.values[e]});
            }
        }
    }

    sort(allEdges.begin(), allEdges.end(),
         [](const MSTEdge& a, const MSTEdge& b) { return a.weight < b.weight; });

    DSU dsu(V);
    MSTResult result;
    result.totalWeight = 0;
    result.edges.reserve(V > 0 ? V - 1 : 0);

    for (const MSTEdge& edge : allEdges) {
        if ((int)result.edges.size() == V - 1) break; // MST complete
        if (dsu.unite(edge.u, edge.v)) {
            result.edges.push_back(edge);
            result.totalWeight += edge.weight;
        }
    }

    result.connected = ((int)result.edges.size() == V - 1);
    return result;
}

MSTResult primMST(const CSRGraph& graph, int V, int startVertex) {
    vector<long long> key(V, LLONG_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    // Min-priority queue of (key, vertex). Stale entries (a vertex whose
    // key improved after it was pushed) are skipped lazily on pop.
    priority_queue<pair<long long, int>,
                   vector<pair<long long, int>>,
                   greater<pair<long long, int>>>
        pq;

    key[startVertex] = 0;
    pq.push({0LL, startVertex});

    while (!pq.empty()) {
        pair<long long, int> top = pq.top();
        pq.pop();
        int u = top.second;

        if (inMST[u]) continue; // stale entry, skip
        inMST[u] = true;

        for (int e = graph.row_ptr[u]; e < graph.row_ptr[u + 1]; e++) {
            int v = graph.col_idx[e];
            long long w = graph.values[e];
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }

    MSTResult result;
    result.totalWeight = 0;
    result.edges.reserve(V > 0 ? V - 1 : 0);
    for (int v = 0; v < V; v++) {
        if (v != startVertex && parent[v] != -1) {
            result.edges.push_back(MSTEdge{parent[v], v, key[v]});
            result.totalWeight += key[v];
        }
    }

    result.connected = ((int)result.edges.size() == V - 1);
    return result;
}
