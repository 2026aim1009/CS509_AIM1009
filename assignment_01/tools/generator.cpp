#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <set>

using namespace std;

// ---------- GEMM generation ----------
void generateGEMM(int M, int K, int N, const string& outFile, int minVal, int maxVal) {
    ofstream out(outFile);
    if (!out.is_open()) {
        cerr << "Error: could not create file " << outFile << endl;
        exit(1);
    }

    out << M << " " << K << " " << N << endl;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            out << (minVal + rand() % (maxVal - minVal + 1));
            if (j < K - 1) out << " ";
        }
        out << endl;
    }

    for (int i = 0; i < K; i++) {
        for (int j = 0; j < N; j++) {
            out << (minVal + rand() % (maxVal - minVal + 1));
            if (j < N - 1) out << " ";
        }
        out << endl;
    }

    out.close();
    cout << "Generated GEMM file " << outFile << " with A(" << M << "x" << K
         << ") and B(" << K << "x" << N << "), values in [" << minVal << "," << maxVal << "]" << endl;
}

// ---------- CSR / graph generation ----------
// weighted = true adds "neighbor weight" pairs; false is plain unweighted format
void generateGraph(int V, int avgDegree, const string& outFile, bool weighted,
                    int minWeight, int maxWeight, bool directed) {
    vector<set<int>> adj(V);

    long long targetEdges = (long long)V * avgDegree / 2;
    long long attempts = 0;
    long long maxAttempts = targetEdges * 20 + 1000;
    long long currentEdges = 0;

    while (currentEdges < targetEdges && attempts < maxAttempts) {
        int u = rand() % V;
        int v = rand() % V;
        attempts++;
        if (u == v) continue; // skip self-loops

        bool added = adj[u].insert(v).second; // true if newly inserted (no duplicate)
        if (added) {
            currentEdges++;
            if (!directed) adj[v].insert(u);
        }
    }

    ofstream out(outFile);
    if (!out.is_open()) {
        cerr << "Error: could not create file " << outFile << endl;
        exit(1);
    }

    out << V << " " << currentEdges << endl;

    for (int i = 0; i < V; i++) {
        out << i << " " << adj[i].size();
        for (int nbr : adj[i]) {
            out << " " << nbr;
            if (weighted) out << " " << (minWeight + rand() % (maxWeight - minWeight + 1));
        }
        out << endl;
    }

    out << "SOURCE 0" << endl;
    out.close();

    cout << "Generated graph file " << outFile << " with V=" << V << ", E=" << currentEdges
         << (weighted ? " (weighted)" : " (unweighted)") << endl;
}

int main(int argc, char* argv[]) {
    srand(time(nullptr));

    if (argc < 2) {
        cerr << "Usage:" << endl;
        cerr << "  ./generator gemm <M> <K> <N> <output_file> [min] [max]" << endl;
        cerr << "  ./generator csr <V> <avgDegree> <output_file> [weighted:0/1] [minWeight] [maxWeight] [directed:0/1]" << endl;
        return 1;
    }

    string mode = argv[1];

    if (mode == "gemm") {
        if (argc < 6) {
            cerr << "Usage: ./generator gemm <M> <K> <N> <output_file> [min] [max]" << endl;
            return 1;
        }
        int M = atoi(argv[2]);
        int K = atoi(argv[3]);
        int N = atoi(argv[4]);
        string outFile = argv[5];
        int minVal = (argc > 6) ? atoi(argv[6]) : 1;
        int maxVal = (argc > 7) ? atoi(argv[7]) : 100;

        generateGEMM(M, K, N, outFile, minVal, maxVal);
    }
    else if (mode == "csr") {
        if (argc < 5) {
            cerr << "Usage: ./generator csr <V> <avgDegree> <output_file> [weighted:0/1] [minWeight] [maxWeight] [directed:0/1]" << endl;
            return 1;
        }
        int V = atoi(argv[2]);
        int avgDegree = atoi(argv[3]);
        string outFile = argv[4];
        bool weighted = (argc > 5) ? (atoi(argv[5]) != 0) : false;
        int minWeight = (argc > 6) ? atoi(argv[6]) : 1;
        int maxWeight = (argc > 7) ? atoi(argv[7]) : 20;
        bool directed = (argc > 8) ? (atoi(argv[8]) != 0) : false;

        generateGraph(V, avgDegree, outFile, weighted, minWeight, maxWeight, directed);
    }
    else {
        cerr << "Unknown mode: " << mode << ". Use 'gemm' or 'csr'." << endl;
        return 1;
    }

    return 0;
}