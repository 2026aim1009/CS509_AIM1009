#include "floyd_warshall.h"

// Large but safe sentinel (long long avoids overflow when we do add two finite values)
const long long FLOYD_WARSHALL_INF = 1000000000000LL;

FloydWarshallResult floydWarshall(const std::vector<std::vector<long long>>& matrix, int V) {
    std::vector<std::vector<long long>> dist = matrix;

    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            if (dist[i][k] >= FLOYD_WARSHALL_INF) continue;
            for (int j = 0; j < V; j++) {
                if (dist[k][j] >= FLOYD_WARSHALL_INF) continue;
                long long candidate = dist[i][k] + dist[k][j];
                if (candidate < dist[i][j]) {
                    dist[i][j] = candidate;
                }
            }
        }
    }

    bool negativeCycle = false;
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            negativeCycle = true;
            break;
        }
    }

    FloydWarshallResult result;
    result.negativeCycle = negativeCycle;
    if (!negativeCycle) {
        result.distance = dist;
    }
    return result;
}