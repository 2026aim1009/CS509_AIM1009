#include "gemm.h"
#include <algorithm>
// Simple GEMM

vector<vector<int>> gemmSimple(const vector<vector<int>>& A, const vector<vector<int>>& B,
                                int M, int K, int N) {
    vector<vector<int>> C(M, vector<int>(N, 0));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int sum = 0;
            for (int k = 0; k < K; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}

// Blocking GEMM

vector<vector<int>> gemmBlocking(const vector<vector<int>>& A, const vector<vector<int>>& B,
                                  int M, int K, int N, int blockSize) {
    vector<vector<int>> C(M, vector<int>(N, 0));

    for (int ii = 0; ii < M; ii += blockSize) {
        for (int jj = 0; jj < N; jj += blockSize) {
            for (int kk = 0; kk < K; kk += blockSize) {

                int iMax = min(ii + blockSize, M);
                int jMax = min(jj + blockSize, N);
                int kMax = min(kk + blockSize, K);

                for (int i = ii; i < iMax; i++) {
                    for (int j = jj; j < jMax; j++) {
                        int sum = C[i][j];
                        for (int k = kk; k < kMax; k++) {
                            sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;
                    }
                }

            }
        }
    }

    return C;
}