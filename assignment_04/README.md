# CS509 Assignment 04 — Individual

## Overview

Assignment 04 (individual task) implements:

- **Vertex Coloring** — Greedy algorithm, Welsh-Powell ordering
- **PageRank**

Vertex Coloring runs on an unweighted, undirected CSR graph. PageRank runs on
an unweighted, directed CSR graph. Each algorithm operates on its own graph
input and is timed independently.

## 1. Vertex Coloring

### Objective

Assign a color to every vertex of an undirected graph such that no two
adjacent vertices share the same color, using as few colors as possible
(a greedy approximation of the chromatic number).

### Approach

- The input adjacency list is converted to CSR before timing.
- Vertex degrees are computed directly from the CSR `row_ptr` array.
- Vertices are ordered by non-increasing degree (Welsh-Powell heuristic),
  ties broken by vertex id for reproducibility.
- Vertices are processed in that order; each is assigned the smallest
  color index not already used by an already-colored neighbour.
- Validity (no two adjacent vertices share a color) is checked after the
  timed region, since it is reporting, not part of the timed algorithm.

### Input Format

```text
V E
u0 degree neighbor1 neighbor2 ...
u1 degree neighbor1 neighbor2 ...
...
u(V-1) degree neighbor1 neighbor2 ...
```

Undirected, unweighted. Every edge appears in both endpoints' adjacency
lists. No self-loops. `E` counts each undirected edge once.

### Output Format

```text
Algorithm: Greedy Vertex Coloring
Vertex colors:
0 0
1 1
2 2
3 0
4 1
Colors used: 3
Valid: Yes
Execution time: <value> ms
```

### Files

```text
assignment_04/
├── README.md
├── src/
│   ├── vertex_coloring.h
│   ├── vertex_coloring.cpp
│   ├── pagerank.h
│   └── pagerank.cpp
├── driver/
│   ├── vertex_coloring_driver.cpp
│   └── pagerank_driver.cpp
├── tests/
│   ├── color_*.txt
│   └── pagerank_*.txt
└── tools/
    ├── generate_color_tests.py
    ├── generate_pagerank_tests.py
    └── run_all_tests.sh
```

The CSR implementation used by Vertex Coloring and PageRank is maintained in:

```text
common/csr/
├── csr.h
└── csr.cpp
```

### Build and Run

From the repository root:

```bash
make vertex_coloring
./assignment_04/driver/vertex_coloring_driver assignment_04/tests/color_10.txt
```

### Generating Test Files

Test files are randomly generated, unweighted, undirected graphs
(`E ≈ 2V` to `4V`), which may be connected or disconnected:

```bash
python3 assignment_04/tools/generate_color_tests.py
```

This produces `color_10.txt`, `color_100.txt`, `color_10000.txt`,
`color_50000.txt`, and `color_100000.txt` in `assignment_04/tests/`.

### Results

| File | V | E | Colors Used | Valid? | Time (ms) | Status |
|---|---:|---:|---:|---|---:|---|
| `color_10.txt` | 10 | 30 | 5 | Yes | 0.001421 | Pass |
| `color_100.txt` | 100 | 300 | 5 | Yes | 0.014261 | Pass |
| `color_10000.txt` | 10,000 | 30,000 | 6 | Yes | 1.20795 | Pass |
| `color_50000.txt` | 50,000 | 100,000 | 5 | Yes | 5.49867 | Pass |
| `color_100000.txt` | 100,000 | 200,000 | 5 | Yes | 12.9178 | Pass |

### Complexity

- **Time:** `O(V log V + E)` (Welsh-Powell degree sort dominates over the
  `O(V + E)` coloring pass).
- **Space:** `O(V + E)`.

---

## 2. PageRank

### Objective

Estimate the relative importance of every vertex in a directed graph based
on the structure of incoming links.

### Approach

- The input adjacency list (outgoing edges only) is converted to CSR
  before timing.
- All vertices are initialized with rank `1 / N`.
- Each iteration computes
  `PR(v) = (1 - d) / N + d * sum_{u->v} PR(u) / outdegree(u)`
  simultaneously for all vertices, using the previous iteration's values.
- A dangling vertex (outdegree 0) has its rank redistributed evenly across
  all `N` vertices instead of being dropped, so the total rank mass stays
  approximately 1.0 after every iteration.
- Iteration stops when the total absolute change across all vertices is
  `<= TOLERANCE`, or `MAX_ITERATIONS` is reached.
- All iterations of the update loop are inside the timed region.

### Input Format

```text
V E
u0 outdegree neighbor1 neighbor2 ...
u1 outdegree neighbor1 neighbor2 ...
...
u(V-1) outdegree neighbor1 neighbor2 ...
DAMPING d
TOLERANCE epsilon
MAX_ITERATIONS n
```

Directed, unweighted. Only outgoing edges are listed for each vertex.

### Output Format

```text
Algorithm: PageRank
Damping: 0.850000
Vertex ranks:
0 0.226283
1 0.267536
2 0.297557
3 0.208624
Sum of ranks: 1.000000
Iterations: <value>
Converged: true
Top vertex: <v> (rank <value>)
Execution time: <value> ms
```

`Top vertex` is additional bookkeeping used to fill the report's "Top
Vertex" column; it does not conflict with the required output format.

### Files

Same layout as Section 1 (`assignment_04/src/pagerank.*`,
`assignment_04/driver/pagerank_driver.cpp`,
`assignment_04/tests/pagerank_*.txt`).

### Build and Run

From the repository root:

```bash
make pagerank
./assignment_04/driver/pagerank_driver assignment_04/tests/pagerank_10.txt
```

### Generating Test Files

Test files are randomly generated, unweighted, directed graphs built from
a ring (`i -> i+1`) plus random extra edges, so every vertex has at least
one incoming and one outgoing edge:

```bash
python3 assignment_04/tools/generate_pagerank_tests.py
```

This produces `pagerank_10.txt`, `pagerank_100.txt`, `pagerank_1000.txt`,
`pagerank_10000.txt`, and `pagerank_50000.txt` in `assignment_04/tests/`,
each using `DAMPING 0.85`, `TOLERANCE 0.0001`, `MAX_ITERATIONS 100`.

### Results

| File | V | E | Damping | Top Vertex (rank) | Sum of Ranks | Iterations | Converged? | Time (ms) | Status |
|---|---:|---:|---:|---|---:|---:|---|---:|---|
| `pagerank_10.txt` | 10 | 30 | 0.85 | 0 (0.155747) | 1.000000 | 14 | Yes | 0.001628 | Pass |
| `pagerank_100.txt` | 100 | 300 | 0.85 | 1 (0.026150) | 1.000000 | 15 | Yes | 0.007891 | Pass |
| `pagerank_1000.txt` | 1,000 | 3,000 | 0.85 | 186 (0.003261) | 1.000000 | 15 | Yes | 0.06381 | Pass |
| `pagerank_10000.txt` | 10,000 | 30,000 | 0.85 | 6722 (0.000402) | 1.000000 | 15 | Yes | 1.31587 | Pass |
| `pagerank_50000.txt` | 50,000 | 100,000 | 0.85 | 6917 (0.000091) | 1.000000 | 21 | Yes | 25.8845 | Pass |

### Complexity

- **Time:** `O(iterations × (V + E))`.
- **Space:** `O(V + E)`.

> **Note on the spec's worked PageRank example (Section 6.2/6.3):**
> vertex 3 in that example graph (`3 1 2`, i.e. `3 -> 2`) has no incoming
> edges at all, so its rank must stay pinned at `(1-d)/N = 0.0375` on every
> iteration — it cannot reach `0.208624` as printed in the spec. This was
> verified by hand-tracing the formula in Section 2.2 against the given
> edges. This implementation follows the formula exactly and satisfies the
> "sum of ranks ≈ 1.0" invariant on every test case above; the discrepancy
> appears to be an error in the spec's example table rather than in this
> implementation.

---

## Timing

Timing is measured only around the algorithm call using
`high_resolution_clock`.

For both algorithms, input parsing, validation, and adjacency-list-to-CSR
conversion are completed before the timer starts. Coloring validity
checking and rank-sum/top-vertex reporting happen after the timer stops.

File I/O, input parsing, preprocessing, and output printing are excluded
from the measured region.

All timings are reported in milliseconds (`ms`).

## Run All Test Cases

To compile both algorithms and run all Assignment 04 test cases:

```bash
chmod +x assignment_04/tools/run_all_tests.sh
./assignment_04/tools/run_all_tests.sh
```

The script runs the test cases sequentially and prints the execution time
for each test.

## Correctness Checks Performed

- Every generated coloring is validated (no two adjacent vertices share a
  color) on every test file.
- Sum of PageRank values stays approximately 1.0 after every iteration on
  every test file, including with dangling-vertex handling.
- Isolated vertices (degree 0) are accepted for Vertex Coloring and
  assigned color 0.
- Missing/invalid input file, self-loops, mismatched degree/neighbour
  counts, out-of-range vertex ids, and invalid PageRank parameters
  (`DAMPING`, `TOLERANCE`, `MAX_ITERATIONS`) are rejected with a clear
  error instead of undefined behavior.

## References

1. [CS509 Laboratory Work Guidelines](../README.md)
2. [Introduction to Algorithms — MIT Press](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/)
3. [Welsh-Powell Algorithm — GraphStream](https://graphstream-project.org/doc/Algorithms/Welsh-Powell)
4. [PageRank — Stanford CS106M](https://web.stanford.edu/class/cs106m/meetings/03-pagerank)
5. [Graph Coloring — Wikipedia](https://en.wikipedia.org/wiki/Graph_coloring)
