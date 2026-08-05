#ifndef GEMM_H
#define GEMM_H

#include <vector>
using namespace std;

vector<vector<int>> gemmSimple(const vector<vector<int>>& A, const vector<vector<int>>& B,
                                int M, int K, int N);

vector<vector<int>> gemmBlocking(const vector<vector<int>>& A, const vector<vector<int>>& B,
                                  int M, int K, int N, int blockSize);                            
#endif