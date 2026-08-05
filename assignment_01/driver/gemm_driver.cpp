#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include "../src/gemm.h"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Usage: ./gemm_driver <input_file>" << endl;
        return 1;
    }

    ifstream infile(argv[1]);
    if (!infile.is_open()) {
        cerr << "Error: could not open file " << argv[1] << endl;
        return 1;
    }

    int M, K, N;
    infile >> M >> K >> N;

    vector<vector<int>> A(M, vector<int>(K));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < K; j++)
            infile >> A[i][j];

    vector<vector<int>> B(K, vector<int>(N));
    for (int i = 0; i < K; i++)
        for (int j = 0; j < N; j++)
            infile >> B[i][j];

    infile.close();

    int blockSize = (argc > 2) ? atoi(argv[2]) : 32; // default 32 if not given

    // ---- Simple GEMM timing ----
    auto start1 = high_resolution_clock::now();
    vector<vector<int>> C1 = gemmSimple(A, B, M, K, N);
    auto end1 = high_resolution_clock::now();
    duration<double, milli> elapsed1 = end1 - start1;

    cout << "Algorithm: GEMM Simple" << endl;
    cout << "Result matrix:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            cout << C1[i][j] << " ";
        cout << endl;
    }
    cout << "Execution time: " << elapsed1.count() << " ms" << endl;

    cout << endl;

    // ---- Blocking GEMM timing ----
    auto start2 = high_resolution_clock::now();
    vector<vector<int>> C2 = gemmBlocking(A, B, M, K, N, blockSize);
    auto end2 = high_resolution_clock::now();
    duration<double, milli> elapsed2 = end2 - start2;

    cout << "Algorithm: GEMM Blocking (block size = " << blockSize << ")" << endl;
    cout << "Result matrix:" << endl;
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++)
            cout << C2[i][j] << " ";
        cout << endl;
    }
    cout << "Execution time: " << elapsed2.count() << " ms" << endl;

    return 0;
}
