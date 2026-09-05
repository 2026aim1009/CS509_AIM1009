#ifndef VERTEX_COLORING_H
#define VERTEX_COLORING_H

#include <vector>
#include "csr.h"

using namespace std;

struct ColoringResult {
    vector<int> colors;   // colors[v] = color index assigned to vertex v
    int numColors;         // total distinct colors used (max color index + 1)
};

// graph: CSR representation of an unweighted, undirected graph. Every
//        undirected edge must appear in both endpoints' adjacency lists
//        (guaranteed by the Section 5.1 input format / CSR conversion).
// V:     number of vertices.
//
// Greedy Vertex Coloring using Welsh-Powell ordering:
//   1. Compute the degree of every vertex from the CSR row_ptr array.
//   2. Order vertices by non-increasing degree.
//   3. Process vertices in that order; assign each the smallest color
//      index not already used by any already-colored neighbour.
// An isolated vertex (degree 0) is simply assigned color 0.
ColoringResult greedyVertexColoring(const CSRGraph& graph, int V);

// Checks that no two adjacent vertices share the same color.
// Not part of the timed algorithm -- used by the driver for reporting.
bool isValidColoring(const CSRGraph& graph, int V, const vector<int>& colors);

#endif
