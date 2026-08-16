#!/usr/bin/env python3
"""
Generates the required MST (mst_*.txt) test files for CS509 Assignment 3,


Produces following files:
  mst_10.txt, mst_100.txt, mst_10000.txt, mst_50000.txt, mst_100000.txt

Each graph is:
  - connected (required for a valid MST input, Section 5.1)
  - sparse, with E approximately 2V to 4V (Section 4.2)
  - undirected: every edge is written into both endpoints' adjacency
    lists with the same weight (Section 5.1)

Run from the repository root:
    python3 assignment_03/tools/generate_mst_tests.py
"""

import os
import random

OUTPUT_DIR = os.path.abspath(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "tests")
)

# (filename, V, E-per-V multiplier). Multiplier chosen so E stays in the
# approximate 2V-4V sparse range requested by Section 4.2.
SIZES = [
    ("mst_10.txt", 10, 3),
    ("mst_100.txt", 100, 3),
    ("mst_10000.txt", 10000, 3),
    ("mst_50000.txt", 50000, 2),
    ("mst_100000.txt", 100000, 2),
]

WEIGHT_MIN = 1
WEIGHT_MAX = 1000


def generate_connected_sparse_graph(V, target_E, seed=None):
    """
    Builds a connected, undirected, weighted graph with approximately
    target_E edges.

    Step 1: build a random spanning tree over a shuffled vertex order
            (guarantees the graph is connected).
    Step 2: add random extra edges (no duplicates, no self-loops) until
            the edge count reaches target_E.
    """
    rng = random.Random(seed)
    edges = set()  # set of (min(u, v), max(u, v))

    # Step 1: random spanning tree.
    order = list(range(V))
    rng.shuffle(order)
    for i in range(1, V):
        u = order[i]
        v = order[rng.randrange(i)]
        a, b = (u, v) if u < v else (v, u)
        edges.add((a, b))

    target_E = max(target_E, V - 1)

    # Step 2: extra random edges up to target_E.
    attempts = 0
    max_attempts = target_E * 20 + 2000
    while len(edges) < target_E and attempts < max_attempts:
        attempts += 1
        u = rng.randrange(V)
        v = rng.randrange(V)
        if u == v:
            continue
        a, b = (u, v) if u < v else (v, u)
        edges.add((a, b))

    adj = {i: [] for i in range(V)}
    for (a, b) in edges:
        w = rng.randint(WEIGHT_MIN, WEIGHT_MAX)
        adj[a].append((b, w))
        adj[b].append((a, w))

    return adj, len(edges)


def write_mst_file(filename, V, adj, E):
    path = os.path.join(OUTPUT_DIR, filename)
    with open(path, "w") as f:
        f.write(f"{V} {E}\n")
        for u in range(V):
            neighbors = adj.get(u, [])
            parts = [str(u), str(len(neighbors))]
            for (v, w) in neighbors:
                parts.append(str(v))
                parts.append(str(w))
            f.write(" ".join(parts) + "\n")
    print(f"  wrote {filename}  (V={V}, E={E})")


def main():
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    print("Generating MST test files (Assignment 3, individual task)...")
    for (filename, V, mult) in SIZES:
        target_E = V * mult
        adj, E = generate_connected_sparse_graph(V, target_E, seed=V)
        write_mst_file(filename, V, adj, E)
    print("Done.")


if __name__ == "__main__":
    main()
