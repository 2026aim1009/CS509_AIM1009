#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <vector>

using namespace std;

struct FloydWarshallResult {
    vector<vector<long long>> distance;
    bool negativeCycle;
};

// sentinel used for "no direct edge" — exposed so the driver can build/print it
extern const long long FLOYD_WARSHALL_INF;

FloydWarshallResult floydWarshall(const vector<vector<long long>>& matrix, int V);

#endif