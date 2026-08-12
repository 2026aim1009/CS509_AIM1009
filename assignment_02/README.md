# CS509 Assignment 02 — Individual

## Overview

Assignment 02 implements:

- **Bellman-Ford**
- **Floyd-Warshall**

Both algorithms compute shortest paths in weighted graphs and detect reachable
negative cycles.

## 1. Bellman-Ford

### Objective

Compute single-source shortest paths in a directed, weighted graph. Edge
weights may be negative, and the implementation detects reachable negative
cycles.

### Approach

- The input adjacency list is converted to CSR before timing.
- All edges are relaxed `V - 1` times.
- One additional pass is used to detect a reachable negative cycle.
- Unreachable vertices are reported as `INF`.

### Input Format

```text
V E
u degree neighbor1 weight1 neighbor2 weight2 ...
...
SOURCE s
```

### Files

```text
assignment_02/
├── src/
│   ├── bellman_ford.h
│   └── bellman_ford.cpp
├── driver/
│   └── bellman_ford_driver.cpp
├── tests/
│   └── bf_*.txt
└── tools/
    └── run_all_tests.sh
```

The CSR implementation used by Bellman-Ford is maintained in:

```text
common/csr/
├── csr.h
└── csr.cpp
```

### Build and Run

From the repository root:

```bash
make bellman_ford
./assignment_02/driver/bellman_ford_driver assignment_02/tests/bf_10.txt
```

### Results

| Mode | Test File | Input Type | Input Size | Negative Cycle | Algorithm Time (ms) |
|---|---|---|---|---|---:|
| Individual | `bf_10.txt` | Adjacency list → CSR | V=10, E=26 | No negative cycle  | 0.000798 |
| Individual | `bf_100.txt` | Adjacency list → CSR | V=100, E=595 | No negative cycle  | 0.048847 |
| Individual | `bf_10000.txt` | Adjacency list → CSR | V=10,000, E=29,994 | No negative cycle  | 812.628 |
| Individual | `bf_50000.txt` | Adjacency list → CSR | V=50,000, E=99,996 | No negative cycle  | 18,294.2 |
| Individual | `bf_100000.txt` | Adjacency list → CSR | V=100,000, E=199,998 | No negative cycle | 3,117.05 |

### Complexity

- **Time:** `O(V × E)`
- **Space:** `O(V + E)`

---

## 2. Floyd-Warshall

### Objective

Compute shortest paths between every pair of vertices in a weighted graph and
detect negative cycles.

### Approach

- The distance matrix is loaded before timing.
- The standard `k`, `i`, `j` dynamic-programming loops update shortest paths.
- A negative cycle is detected if any diagonal entry becomes negative.
- `INF` represents the absence of a direct edge.

### Input Format

```text
V
V × V distance matrix
```

Use `INF` for pairs with no direct edge.

### Files

```text
assignment_02/
├── src/
│   ├── floyd_warshall.h
│   └── floyd_warshall.cpp
├── driver/
│   └── floyd_warshall_driver.cpp
└── tests/
    └── fw_*.txt
```

### Build and Run

From the repository root:

```bash
make floyd_warshall
./assignment_02/driver/floyd_warshall_driver assignment_02/tests/fw_10.txt
```

### Results

| Mode | Test File | Input Type | Input Size | Negative cycle | Algorithm Time (ms) |
|---|---|---|---|---|---:|
| Individual | `fw_10.txt` | Distance matrix | V=10 | No negative cycle  | 0.004617 |
| Individual | `fw_100.txt` | Distance matrix | V=100 | No negative cycle | 3.72939 |
| Individual | `fw_500.txt` | Distance matrix | V=500 | No negative cycle  | 89.4173 |
| Individual | `fw_1000.txt` | Distance matrix | V=1,000 | No negative cycle  | 1,062.44 |
| Individual | `fw_2000.txt` | Distance matrix | V=2,000 | No negative cycle  | 9,356.85 |

### Complexity

- **Time:** `O(V³)`
- **Space:** `O(V²)`

---

## Timing

Timing is measured only around the algorithm call using
`high_resolution_clock`.

For Bellman-Ford, adjacency-list parsing and adjacency-list-to-CSR conversion
are completed before the timer starts.

For Floyd-Warshall, input parsing and matrix construction are completed before
the timer starts.

File I/O, input parsing, preprocessing, and output printing are excluded from
the measured region.

All timings are reported in milliseconds (`ms`).

## Run All Test Cases

To compile both algorithms and run all Assignment 02 test cases:

```bash
chmod +x assignment_02/tools/run_all_tests.sh
./assignment_02/tools/run_all_tests.sh
```

The script runs the test cases sequentially and prints the execution time for
each test.

## References

1. [CS509 Laboratory Work Guidelines](../README.md)
2. [Introduction to Algorithms — MIT Press](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/)
3. [Bellman–Ford Algorithm — Wikipedia](https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm)
4. [Floyd–Warshall Algorithm — Wikipedia](https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm)
5. [Shortest Path — CP-Algorithms](https://cp-algorithms.com/graph/bellman_ford.html)
