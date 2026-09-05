#!/usr/bin/env python3
"""
Generates the required PageRank (pagerank_*.txt) test files for CS509
Assignment 4, individual task.

Produces the following files:
  pagerank_10.txt, pagerank_100.txt, pagerank_1000.txt,
  pagerank_10000.txt, pagerank_50000.txt

Each graph is:
  - directed and unweighted (only outgoing edges listed, Section 6.1)
  - built from a random Hamiltonian ring (vertex i -> i+1) plus random
    extra out-edges, so every vertex has at least one incoming AND one
    outgoing edge (Section 3: "every vertex reachable ... where
    practical") -- i.e. no dangling vertices in the generated files,
    though the algorithm itself still handles dangling vertices
    correctly per Section 2.2.
  - sparse for large sizes, with E approximately 2V to 4V

Run from the repository root:
    python3 assignment_04/tools/generate_pagerank_tests.py
"""

import os
import random

OUTPUT_DIR = os.path.abspath(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "tests")
)

# (filename, V, E-per-V multiplier).
SIZES = [
    ("pagerank_10.txt", 10, 3),
    ("pagerank_100.txt", 100, 3),
    ("pagerank_1000.txt", 1000, 3),
    ("pagerank_10000.txt", 10000, 3),
    ("pagerank_50000.txt", 50000, 2),
]

DAMPING = 0.85
TOLERANCE = 0.0001
MAX_ITERATIONS = 100


def generate_directed_graph(V, target_E, seed=None):
    """
    Builds a directed, unweighted graph with approximately target_E
    edges. Step 1 lays a ring i -> (i+1) % V so every vertex has at
    least one incoming and one outgoing edge (no dangling vertices,
    every vertex reachable). Step 2 adds random extra directed edges
    (no self-loops, no duplicates) until target_E is reached.
    """
    rng = random.Random(seed)
    edges = set()

    # Step 1: ring guarantees in-degree >= 1 and out-degree >= 1 for all.
    for i in range(V):
        edges.add((i, (i + 1) % V))

    target_E = max(target_E, V)

    # Step 2: random extra directed edges.
    attempts = 0
    max_attempts = target_E * 20 + 2000
    while len(edges) < target_E and attempts < max_attempts:
        attempts += 1
        u = rng.randrange(V)
        v = rng.randrange(V)
        if u == v:
            continue
        edges.add((u, v))

    adj = {i: [] for i in range(V)}
    for (u, v) in edges:
        adj[u].append(v)

    return adj, len(edges)


def write_pagerank_file(filename, V, adj, E):
    path = os.path.join(OUTPUT_DIR, filename)
    with open(path, "w") as f:
        f.write(f"{V} {E}\n")
        for u in range(V):
            neighbors = sorted(adj.get(u, []))
            parts = [str(u), str(len(neighbors))] + [str(n) for n in neighbors]
            f.write(" ".join(parts) + "\n")
        f.write(f"DAMPING {DAMPING}\n")
        f.write(f"TOLERANCE {TOLERANCE}\n")
        f.write(f"MAX_ITERATIONS {MAX_ITERATIONS}\n")
    print(f"  wrote {filename}  (V={V}, E={E})")


def main():
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    print("Generating PageRank test files (Assignment 4, individual task)...")
    for (filename, V, mult) in SIZES:
        target_E = V * mult
        adj, E = generate_directed_graph(V, target_E, seed=V)
        write_pagerank_file(filename, V, adj, E)
    print("Done.")


if __name__ == "__main__":
    main()
