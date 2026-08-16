# CS509 Assignment 03 — Individual

## Overview

Assignment 03 (individual task) implements **Minimum Spanning Tree (MST)**:

- **Kruskal's algorithm**
- **Prim's algorithm**

Both algorithms run on the same weighted, undirected CSR graph and must
report the same total MST weight.


## 1. Minimum Spanning Tree (MST)

### Objective

Connect all vertices of a connected, weighted, undirected graph using
exactly `V - 1` edges while minimizing total edge weight.

### Approach

- The input adjacency list is converted to CSR before timing.
- **Kruskal:** the undirected edge list is extracted from the CSR
  representation (each edge kept once, via `neighbor > u`), sorted by
  non-decreasing weight, and added greedily using a Disjoint Set Union
  (Union-Find, path compression + union by rank) to reject edges that
  would form a cycle. Extraction and sorting happen inside the timed
  Kruskal call.
- **Prim:** starts at vertex 0 (recommended for reproducibility) and
  grows one tree using a min-priority queue over frontier edge keys,
  with lazy deletion of stale queue entries.
- Both implementations accept positive, zero, or negative integer edge
  weights.
- If the input graph is not connected, the driver still reports the
  partial forest and total weight found, and prints an explicit warning
  rather than silently producing an incomplete MST.

### Input Format

```text
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree neighbor1 weight1 neighbor2 weight2 ...
```

Every undirected edge appears in both endpoints' adjacency lists with
the same weight. `E` counts each undirected edge once.

### Output Format 

```text
Algorithm: Kruskal's MST
MST edges:
0 1 2
1 2 3
1 4 5
0 3 6
Total MST weight: 16
Execution time: <value> ms

Algorithm: Prim's MST
MST edges:
0 1 2
1 2 3
1 4 5
0 3 6
Total MST weight: 16
Execution time: <value> ms
```

### Files

```text
assignment_03/
├── README.md
├── src/
│   ├── mst.h
│   └── mst.cpp
├── driver/
│   └── mst_driver.cpp
├── tests/
│   └── mst_*.txt
├── tools/
│   ├── generate_mst_tests.py
│   └── run_all_tests.sh
└── outputs/
```

The CSR implementation used by MST is maintained in:

```text
common/csr/
├── csr.h
└── csr.cpp
```

### Build and Run

From the repository root:

```bash
make mst
./assignment_03/driver/mst_driver assignment_03/tests/mst_10.txt
```

### Generating Test Files

Test files are randomly generated, connected, sparse graphs
(`E ≈ 2V` to `4V`) with positive integer weights:

```bash
python3 assignment_03/tools/generate_mst_tests.py
```

This produces `mst_10.txt`, `mst_100.txt`, `mst_10000.txt`,
`mst_50000.txt`, and `mst_100000.txt` in `assignment_03/tests/`.

### Running All Tests

```bash
bash assignment_03/tools/run_all_tests.sh
```

### Results

| File | V | E | Kruskal Weight | Prim Weight | Kruskal Time (ms) | Prim Time (ms) | Equal? | Status |
|---|---:|---:|---:|---:|---:|---:|---|---|
| `mst_10.txt` | 10 | 30 | 1,630 | 1,630 | 0.002447 | 0.002516 | Yes | Pass |
| `mst_100.txt` | 100 | 300 | 19,955 | 19,955 | 0.026674 | 0.027647 | Yes | Pass |
| `mst_10000.txt` | 10,000 | 30,000 | 1,997,665 | 1,997,665 | 2.23682 | 3.64043 | Yes | Pass |
| `mst_50000.txt` | 50,000 | 100,000 | 14,288,579 | 14,288,579 | 8.22938 | 17.7987 | Yes | Pass |
| `mst_100000.txt` | 100,000 | 200,000 | 28,631,860 | 28,631,860 | 19.8346 | 38.5544 | Yes | Pass |


### Complexity

- **Kruskal:** Time `O(E log E)` (edge sort dominates), Space `O(V + E)`.
- **Prim:** Time `O(E log V)` (binary-heap priority queue), Space `O(V + E)`.

### Correctness Checks Performed

- Total MST weight matches between Kruskal and Prim on every test file.
- Negative-weight edges accepted and produce a correct (possibly
  negative) total weight.
- Disconnected input and single-vertex input handled without crashing.
- Missing/invalid input file returns a clear error and non-zero exit
  code instead of undefined behavior.
