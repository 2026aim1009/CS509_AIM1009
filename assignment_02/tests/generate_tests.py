#!/usr/bin/env python3
"""
Generates the required Bellman-Ford (bf_*.txt) and Floyd-Warshall (fw_*.txt)
test files for CS509 Assignment 2, per:
  - Section 4.2 (Required Graph Input Sizes)
  - Section 12 (Suggested Test-File Naming)
  - Section 5.1 / 6.1 (file formats)

Produces exactly 10 files:
  bf_10.txt, bf_100.txt, bf_10000.txt, bf_50000.txt, bf_100000.txt
  fw_10.txt, fw_100.txt, fw_500.txt, fw_1000.txt, fw_2000.txt

Run from the repository root:
    python3 assignment_02/tests/generate_tests.py
"""

import os
import random

OUTPUT_DIR = os.path.dirname(os.path.abspath(__file__))

# ---------------------------------------------------------------------------
# File writers (match spec formats exactly)
# ---------------------------------------------------------------------------

def write_bf_file(filename, V, adj, source):
    """adj: dict u -> list of (neighbor, weight). Writes Section 5.1 format."""
    E = sum(len(v) for v in adj.values())
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
        f.write(f"SOURCE {source}\n")
    print(f"  wrote {filename}  (V={V}, E={E})")


def write_fw_file(filename, V, matrix):
    """matrix: V x V list of ints or the string 'INF'. Writes Section 6.1 format."""
    path = os.path.join(OUTPUT_DIR, filename)
    with open(path, "w") as f:
        f.write(f"{V}\n")
        for row in matrix:
            f.write(" ".join(str(x) for x in row) + "\n")
    print(f"  wrote {filename}  (V={V})")


# ---------------------------------------------------------------------------
# Graph generation
# ---------------------------------------------------------------------------

def random_digraph_with_negatives(V, avg_out_degree, seed=None,
                                   potential_range=15, extra_range=5):
    """
    Builds a random directed graph with SOME negative edge weights, and
    GUARANTEES no negative cycle exists anywhere in the graph (not just
    "not reachable from source") -- by construction, not by retrying.

    Technique: assign each vertex a random integer potential h[v]. Every
    edge weight is w(u,v) = h[v] - h[u] + c, with c >= 0 random. Any cycle's
    weights telescope to sum(c) >= 0, so a negative cycle is impossible,
    while individual edges are still negative whenever h[v] < h[u].
    """
    rng = random.Random(seed)
    h = [rng.randint(0, potential_range) for _ in range(V)]

    adj = {u: [] for u in range(V)}
    target_edges = V * avg_out_degree
    for _ in range(target_edges):
        u = rng.randrange(V)
        v = rng.randrange(V)
        if u == v:
            continue
        c = rng.randint(0, extra_range)
        w = h[v] - h[u] + c
        adj[u].append((v, w))
    return adj


def random_digraph_positive(V, avg_out_degree, weight_range, seed=None):
    """Random directed graph with positive weights only (trivially no
    negative cycle) -- used for the large sparse graphs."""
    rng = random.Random(seed)
    adj = {u: [] for u in range(V)}
    target_edges = V * avg_out_degree
    for _ in range(target_edges):
        u = rng.randrange(V)
        v = rng.randrange(V)
        if u == v:
            continue
        w = rng.randint(weight_range[0], weight_range[1])
        adj[u].append((v, w))
    return adj


def adj_to_matrix(V, adj, no_edge="INF"):
    """Builds a dense V x V matrix from an adjacency dict for Floyd-Warshall.
    Diagonal is 0, missing entries are INF."""
    matrix = [[no_edge for _ in range(V)] for _ in range(V)]
    for i in range(V):
        matrix[i][i] = 0
    for u, neighbors in adj.items():
        for (v, w) in neighbors:
            if u == v:
                continue
            if matrix[u][v] == no_edge or w < matrix[u][v]:
                matrix[u][v] = w
    return matrix


# ---------------------------------------------------------------------------
# Required test files only (Section 4.2 sizes, Section 12 names)
# ---------------------------------------------------------------------------

def generate_bf_fw_pairs():
    """V=10 and V=100: both algorithms are required at these sizes, and the
    spec (end of Section 6.3) requires cross-checking Bellman-Ford against
    Floyd-Warshall at these two sizes -- so bf_V.txt and fw_V.txt must encode
    the same underlying graph."""
    for V, avg_deg, seed in [(10, 3, 1001), (100, 6, 1002)]:
        adj = random_digraph_with_negatives(V, avg_deg, seed=seed)
        write_bf_file(f"bf_{V}.txt", V, adj, source=0)
        write_fw_file(f"fw_{V}.txt", V, adj_to_matrix(V, adj))


def generate_bf_large():
    """V=10,000 / 50,000 / 100,000: BF-only. Kept sparse (E ~ 2V-3V) per the
    Section 4.2 note. Positive weights only."""
    for V, avg_deg, seed in [(10_000, 3, 2001), (50_000, 2, 2002), (100_000, 2, 2003)]:
        adj = random_digraph_positive(V, avg_deg, weight_range=(1, 20), seed=seed)
        write_bf_file(f"bf_{V}.txt", V, adj, source=0)


def generate_fw_only():
    """V=500 / 1,000 / 2,000: FW-only per Section 4.2 (FW excluded from the
    50k/100k scale). Positive weights only."""
    for V, density, seed in [(500, 0.05, 3001), (1000, 0.02, 3002), (2000, 0.01, 3003)]:
        rng = random.Random(seed)
        matrix = [[("INF" if i != j else 0) for j in range(V)] for i in range(V)]
        for i in range(V):
            for j in range(V):
                if i != j and rng.random() < density:
                    matrix[i][j] = rng.randint(1, 20)
        write_fw_file(f"fw_{V}.txt", V, matrix)


def main():
    os.makedirs(OUTPUT_DIR, exist_ok=True)

    print("Generating bf_10/fw_10 and bf_100/fw_100 (matched pairs for cross-check)...")
    generate_bf_fw_pairs()

    print("Generating bf_10000, bf_50000, bf_100000...")
    generate_bf_large()

    print("Generating fw_500, fw_1000, fw_2000...")
    generate_fw_only()

    print("\nDone. 10 files written to:", OUTPUT_DIR)


if __name__ == "__main__":
    main()