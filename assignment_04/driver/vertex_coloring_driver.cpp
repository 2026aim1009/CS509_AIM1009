#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include "csr.h"
#include "vertex_coloring.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./vertex_coloring_driver <input_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error: could not open input file: " << argv[1] << endl;
        return 1;
    }

    int V, E;
    infile >> V >> E;
    if (!infile || V <= 0 || E < 0) {
        cerr << "Error: invalid or missing vertex/edge count in input file." << endl;
        return 1;
    }

    // Adjacency list; weight slot unused for this unweighted graph (kept
    // as 0) so the same convertToCSR() from Assignment 1 can be reused.
    vector<vector<pair<int, int>>> adjList(V);
    vector<int> declaredDegree(V, 0);

    for (int i = 0; i < V; i++) {
        int u, degree;
        infile >> u >> degree;
        if (!infile || u < 0 || u >= V || degree < 0) {
            cerr << "Error: malformed adjacency entry in input file (line " << i
                 << "): out-of-range vertex id or negative degree." << endl;
            return 1;
        }
        declaredDegree[u] = degree;
        for (int d = 0; d < degree; d++) {
            int neighbor;
            infile >> neighbor;
            if (!infile || neighbor < 0 || neighbor >= V) {
                cerr << "Error: malformed edge entry for vertex " << u
                     << ": out-of-range neighbour id." << endl;
                return 1;
            }
            if (neighbor == u) {
                cerr << "Error: self-loop found at vertex " << u
                     << "; Vertex Coloring input must not contain self-loops."
                     << endl;
                return 1;
            }
            adjList[u].push_back(make_pair(neighbor, 0));
        }
    }

    infile.close();

    // Cross-check declared degree against the actual neighbour count read.
    for (int u = 0; u < V; u++) {
        if ((int)adjList[u].size() != declaredDegree[u]) {
            cerr << "Error: declared degree for vertex " << u
                 << " does not match the number of neighbours read." << endl;
            return 1;
        }
    }

    // Preprocessing: adjacency-list -> CSR (NOT timed, per Section 4.1/9).
    CSRGraph graph = convertToCSR(adjList, V);

    // Timed region: greedy Welsh-Powell coloring only.
    auto start = high_resolution_clock::now();
    ColoringResult result = greedyVertexColoring(graph, V);
    auto end = high_resolution_clock::now();
    double elapsedMs = duration<double, milli>(end - start).count();

    // Validity check happens after timing -- it is reporting, not part
    // of the timed algorithm.
    bool valid = isValidColoring(graph, V, result.colors);

    cout << "Algorithm: Greedy Vertex Coloring" << endl;
    cout << "Vertex colors:" << endl;
    for (int v = 0; v < V; v++) {
        cout << v << " " << result.colors[v] << endl;
    }
    cout << "Colors used: " << result.numColors << endl;
    cout << "Valid: " << (valid ? "Yes" : "No") << endl;
    cout << "Execution time: " << elapsedMs << " ms" << endl;

    return 0;
}
