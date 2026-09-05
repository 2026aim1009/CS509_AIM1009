#!/usr/bin/env python3
"""
Generates the required Vertex Coloring (color_*.txt) test files for
CS509 Assignment 4, individual task.

Produces the following files:
  color_10.txt, color_100.txt, color_10000.txt, color_50000.txt,
  color_100000.txt

Each graph is:
  - undirected and unweighted
  - sparse for large sizes, with E approximately 2V to 4V (Section 4.2)
  - free of self-loops and duplicate edges (Section 5.1)
  - written with every edge appearing in BOTH endpoints' adjacency
    lists (Section 5.1)

Run from the repository root:
    python3 assignment_04/tools/generate_color_tests.py
"""

import os
import random

OUTPUT_DIR = os.path.abspath(
    os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "tests")
)

# (filename, V, E-per-V multiplier). Multiplier chosen so E stays in the
# approximate 2V-4V sparse range requested by Section 4.2.
SIZES = [
    ("color_10.txt", 10, 3),
    ("color_100.txt", 100, 3),
    ("color_10000.txt", 10000, 3),
    ("color_50000.txt", 50000, 2),
    ("color_100000.txt", 100000, 2),
]


def generate_undirected_graph(V, target_E, seed=None):
    """
    Builds an undirected, unweighted graph with approximately target_E
    edges, no self-loops, no duplicate edges. May be disconnected
    (allowed for Vertex Coloring, Section 5.1).
    """
    rng = random.Random(seed)
    edges = set()  # set of (min(u, v), max(u, v))

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
        adj[a].append(b)
        adj[b].append(a)

    return adj, len(edges)


def write_color_file(filename, V, adj, E):
    path = os.path.join(OUTPUT_DIR, filename)
    with open(path, "w") as f:
        f.write(f"{V} {E}\n")
        for u in range(V):
            neighbors = sorted(adj.get(u, []))
            parts = [str(u), str(len(neighbors))] + [str(n) for n in neighbors]
            f.write(" ".join(parts) + "\n")
    print(f"  wrote {filename}  (V={V}, E={E})")


def main():
    os.makedirs(OUTPUT_DIR, exist_ok=True)
    print("Generating Vertex Coloring test files (Assignment 4, individual task)...")
    for (filename, V, mult) in SIZES:
        target_E = V * mult
        adj, E = generate_undirected_graph(V, target_E, seed=V)
        write_color_file(filename, V, adj, E)
    print("Done.")


if __name__ == "__main__":
    main()
