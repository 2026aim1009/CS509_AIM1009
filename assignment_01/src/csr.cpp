#include "csr.h"

CSRGraph convertToCSR(const vector<vector<pair<int,int>>>& adjList, int V) {
    CSRGraph graph;
    graph.row_ptr.resize(V + 1, 0);

  
    for (int i = 0; i < V; i++) {
        graph.row_ptr[i + 1] = graph.row_ptr[i] + adjList[i].size();
    }

    int totalEdges = graph.row_ptr[V];
    graph.col_idx.resize(totalEdges);
    graph.values.resize(totalEdges);

   
    for (int i = 0; i < V; i++) {
        int pos = graph.row_ptr[i];
        for (auto& edge : adjList[i]) {
            graph.col_idx[pos] = edge.first;   
            graph.values[pos] = edge.second;   
            pos++;
        }
    }

    return graph;
}
