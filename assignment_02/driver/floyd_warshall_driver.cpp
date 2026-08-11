#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>
#include "floyd_warshall.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./floyd_warshall_driver <input_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile) {
        cerr << "Error: could not open input file: " << argv[1] << endl;
        return 1;
    }

    int V;
    infile >> V;

    vector<vector<long long>> matrix(V, vector<long long>(V));

    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            string token;
            infile >> token;
            if (token == "INF") {
                matrix[i][j] = FLOYD_WARSHALL_INF;
            } else {
                matrix[i][j] = stoll(token);
            }
        }
    }

    infile.close();

    // Timed region: algorithm only (matrix already loaded into memory)
    auto start = high_resolution_clock::now();
    FloydWarshallResult result = floydWarshall(matrix, V);
    auto end = high_resolution_clock::now();
    double elapsedMs = duration<double, milli>(end - start).count();

    cout << "Algorithm: Floyd-Warshall" << endl;

    if (result.negativeCycle) {
        cout << "Negative cycle: true" << endl;
    } else {
        cout << "Distance matrix:" << endl;
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (result.distance[i][j] >= FLOYD_WARSHALL_INF) {
                    cout << "INF";
                } else {
                    cout << result.distance[i][j];
                }
                if (j < V - 1) cout << " ";
            }
            cout << endl;
        }
        cout << "Negative cycle: none" << endl;
    }

    cout << "Execution time: " << elapsedMs << " ms" << endl;

    return 0;
}