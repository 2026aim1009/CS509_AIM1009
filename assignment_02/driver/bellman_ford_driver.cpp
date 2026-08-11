#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include "csr.h"
#include "bellman_ford.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./bellman_ford_driver <input_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error: could not open input file: " << argv[1] << endl;
        return 1;
    }

    int V, E;
    infile >> V >> E;

    vector<vector<pair<int, int>>> adjList(V);

    for (int i = 0; i < V; i++) {
        int u, degree;
        infile >> u >> degree;
        for (int d = 0; d < degree; d++) {
            int neighbor, weight;
            infile >> neighbor >> weight;
            adjList[u].push_back(make_pair(neighbor, weight));
        }
    }

    string sourceLabel;
    int source;
    infile >> sourceLabel >> source;

    if (sourceLabel != "SOURCE") {
        cerr << "Error: expected SOURCE line, got: " << sourceLabel << endl;
        return 1;
    }
    if (source < 0 || source >= V) {
        cerr << "Error: source vertex out of range: " << source << endl;
        return 1;
    }

    infile.close();

    // Preprocessing: adjacency-list -> CSR (NOT timed)
    CSRGraph graph = convertToCSR(adjList, V);

    // Timed region: algorithm only
    auto start = high_resolution_clock::now();
    BellmanFordResult result = bellmanFord(graph, V, source);
    auto end = high_resolution_clock::now();
    double elapsedMs = duration<double, milli>(end - start).count();

    cout << "Algorithm: Bellman-Ford" << endl;
    cout << "Source: " << source << endl;

    if (result.negativeCycle) {
        cout << "Negative cycle: true" << endl;
    } else {
        cout << "Vertex Distance" << endl;
        for (int i = 0; i < V; i++) {
            cout << i << " ";
            if (result.distance[i] == BELLMAN_FORD_INF) {
                cout << "INF" << endl;
            } else {
                cout << result.distance[i] << endl;
            }
        }
        cout << "Negative cycle: none" << endl;
    }

    cout << "Execution time: " << elapsedMs << " ms" << endl;

    return 0;
}