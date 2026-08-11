#ifndef CSR_H
#define CSR_H

#include <vector>
using namespace std;

struct CSRGraph {
    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values; 
};


CSRGraph convertToCSR(const vector<vector<pair<int,int>>>& adjList, int V);

#endif
