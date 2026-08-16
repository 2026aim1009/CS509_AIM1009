#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include "csr.h"
#include "mst.h"

using namespace std;
using namespace std::chrono;

static void printMSTResult(const string& label, const MSTResult& result, double elapsedMs) {
    cout << "Algorithm: " << label << endl;
    cout << "MST edges:" << endl;
    for (const MSTEdge& edge : result.edges) {
        cout << edge.u << " " << edge.v << " " << edge.weight << endl;
    }
    cout << "Total MST weight: " << result.totalWeight << endl;
    if (!result.connected) {
        cout << "Warning: input graph is not connected -- only "
             << result.edges.size() << " of (V-1) required edges were found."
             << endl;
    }
    cout << "Execution time: " << elapsedMs << " ms" << endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./mst_driver <input_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error: could not open input file: " << argv[1] << endl;
        return 1;
    }

    int V, E;
    infile >> V >> E;
    if (!infile || V <= 0) {
        cerr << "Error: invalid or missing vertex count in input file." << endl;
        return 1;
    }

    vector<vector<pair<int, int>>> adjList(V);

    for (int i = 0; i < V; i++) {
        int u, degree;
        infile >> u >> degree;
        if (!infile || u < 0 || u >= V || degree < 0) {
            cerr << "Error: malformed adjacency entry in input file (vertex "
                 << i << ")." << endl;
            return 1;
        }
        for (int d = 0; d < degree; d++) {
            int neighbor, weight;
            infile >> neighbor >> weight;
            if (!infile || neighbor < 0 || neighbor >= V) {
                cerr << "Error: malformed edge entry in input file (vertex "
                     << u << ")." << endl;
                return 1;
            }
            adjList[u].push_back(make_pair(neighbor, weight));
        }
    }

    infile.close();

    if (V > 1) {
        bool hasAnyEdge = false;
        for (int i = 0; i < V && !hasAnyEdge; i++) {
            if (!adjList[i].empty()) hasAnyEdge = true;
        }
        if (!hasAnyEdge) {
            cerr << "Error: graph with V > 1 has no edges; a valid MST input "
                 << "cannot contain an isolated vertex." << endl;
            return 1;
        }
    }

    // Preprocessing: adjacency-list -> CSR (NOT timed, per Section 4.1/8).
    CSRGraph graph = convertToCSR(adjList, V);

    // Timed region: Kruskal's algorithm only (edge extraction from CSR
    // and sorting happen inside kruskalMST, per Section 8).
    auto startK = high_resolution_clock::now();
    MSTResult kruskalResult = kruskalMST(graph, V);
    auto endK = high_resolution_clock::now();
    double kruskalMs = duration<double, milli>(endK - startK).count();

    // Timed region: Prim's algorithm only, on the same CSR graph.
    auto startP = high_resolution_clock::now();
    MSTResult primResult = primMST(graph, V, 0);
    auto endP = high_resolution_clock::now();
    double primMs = duration<double, milli>(endP - startP).count();

    printMSTResult("Kruskal's MST", kruskalResult, kruskalMs);
    cout << endl;
    printMSTResult("Prim's MST", primResult, primMs);

    if (kruskalResult.connected && primResult.connected &&
        kruskalResult.totalWeight != primResult.totalWeight) {
        cerr << endl
             << "Warning: Kruskal and Prim total weights differ ("
             << kruskalResult.totalWeight << " vs " << primResult.totalWeight
             << "). Check input graph / implementation." << endl;
    }

    return 0;
}
