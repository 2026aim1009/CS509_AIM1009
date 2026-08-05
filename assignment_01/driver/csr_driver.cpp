#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "../src/csr.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./csr_driver <input_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Error: could not open file " << argv[1] << endl;
        return 1;
    }
    int V, E;
    infile >> V >> E;

    vector<vector<pair<int,int>>> adjList(V);

    for (int i = 0; i < V; i++) {
        int vertex, degree;
        infile >> vertex >> degree;
        for (int j = 0; j < degree; j++) {
            int neighbor;
            infile >> neighbor;
            adjList[vertex].push_back({neighbor, 1}); // weight=1, unweighted format
        }
    }

    string label;
    int source = -1;
    if (infile >> label >> source) {
        // SOURCE line present, read but not needed for CSR itself
    }

    infile.close();

    // Timing the conversion itself (this is preprocessing, kept separate/labeled) ----
    auto start = high_resolution_clock::now();
    CSRGraph g = convertToCSR(adjList, V);
    auto end = high_resolution_clock::now();
    duration<double, milli> elapsed = end - start;

    cout << "Algorithm: Adjacency List to CSR Conversion" << endl;
    cout << "V = " << V << ", E = " << E << endl;

    cout << "row_ptr: ";
    for (int x : g.row_ptr) cout << x << " ";
    cout << endl;

    cout << "col_idx: ";
    for (int x : g.col_idx) cout << x << " ";
    cout << endl;

    cout << "values: ";
    for (int x : g.values) cout << x << " ";
    cout << endl;

    cout << "Conversion time: " << elapsed.count() << " ms" << endl;
 

    return 0;
}
