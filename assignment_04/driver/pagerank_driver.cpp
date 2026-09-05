#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include <iomanip>
#include "csr.h"
#include "pagerank.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./pagerank_driver <input_file>" << endl;
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

    // Adjacency list of OUTGOING edges only (directed graph, Section 6.1).
    // Weight slot unused so the same convertToCSR() from Assignment 1 can
    // be reused for this unweighted directed graph.
    vector<vector<pair<int, int>>> adjList(V);
    vector<int> declaredOutdeg(V, 0);

    for (int i = 0; i < V; i++) {
        int u, outdegree;
        infile >> u >> outdegree;
        if (!infile || u < 0 || u >= V || outdegree < 0) {
            cerr << "Error: malformed adjacency entry in input file (line " << i
                 << "): out-of-range vertex id or negative outdegree." << endl;
            return 1;
        }
        declaredOutdeg[u] = outdegree;
        for (int d = 0; d < outdegree; d++) {
            int neighbor;
            infile >> neighbor;
            if (!infile || neighbor < 0 || neighbor >= V) {
                cerr << "Error: malformed edge entry for vertex " << u
                     << ": out-of-range neighbour id." << endl;
                return 1;
            }
            adjList[u].push_back(make_pair(neighbor, 0));
        }
    }

    for (int u = 0; u < V; u++) {
        if ((int)adjList[u].size() != declaredOutdeg[u]) {
            cerr << "Error: declared outdegree for vertex " << u
                 << " does not match the number of neighbours read." << endl;
            return 1;
        }
    }

    // Trailing parameters: DAMPING, TOLERANCE, MAX_ITERATIONS (Section 6.1).
    string token;
    double damping = -1.0, tolerance = -1.0;
    int maxIterations = -1;
    bool haveDamping = false, haveTolerance = false, haveMaxIter = false;

    while (infile >> token) {
        if (token == "DAMPING") {
            infile >> damping;
            haveDamping = true;
        } else if (token == "TOLERANCE") {
            infile >> tolerance;
            haveTolerance = true;
        } else if (token == "MAX_ITERATIONS") {
            infile >> maxIterations;
            haveMaxIter = true;
        } else {
            cerr << "Error: unrecognized token '" << token
                 << "' while reading PageRank parameters." << endl;
            return 1;
        }
    }
    infile.close();

    if (!haveDamping || damping <= 0.0 || damping >= 1.0) {
        cerr << "Error: DAMPING must be present and satisfy 0 < d < 1." << endl;
        return 1;
    }
    if (!haveTolerance || tolerance <= 0.0) {
        cerr << "Error: TOLERANCE must be present and positive." << endl;
        return 1;
    }
    if (!haveMaxIter || maxIterations <= 0) {
        cerr << "Error: MAX_ITERATIONS must be present and positive." << endl;
        return 1;
    }

    // Preprocessing: adjacency-list -> CSR (NOT timed, per Section 4.1/9).
    CSRGraph graph = convertToCSR(adjList, V);

    // Timed region: all iterations of the PageRank update loop (Section 9).
    auto start = high_resolution_clock::now();
    PageRankResult result = computePageRank(graph, V, damping, tolerance, maxIterations);
    auto end = high_resolution_clock::now();
    double elapsedMs = duration<double, milli>(end - start).count();

    double sumRanks = 0.0;
    for (double r : result.ranks) sumRanks += r;

    int topVertex = 0;
    for (int v = 1; v < V; v++) {
        if (result.ranks[v] > result.ranks[topVertex]) topVertex = v;
    }

    cout << fixed << setprecision(6);
    cout << "Algorithm: PageRank" << endl;
    cout << "Damping: " << damping << endl;
    cout << "Vertex ranks:" << endl;
    for (int v = 0; v < V; v++) {
        cout << v << " " << result.ranks[v] << endl;
    }
    cout << "Sum of ranks: " << sumRanks << endl;
    cout << "Iterations: " << result.iterations << endl;
    cout << "Converged: " << (result.converged ? "true" : "false") << endl;
    cout << "Top vertex: " << topVertex << " (rank " << result.ranks[topVertex] << ")" << endl;
    cout << defaultfloat;
    cout << "Execution time: " << elapsedMs << " ms" << endl;

    return 0;
}
