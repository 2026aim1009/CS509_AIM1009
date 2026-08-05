#!/bin/bash
# Generates a full exhaustive set of test files for GEMM and CSR (individual task scope)

set -e  # stop if any command fails

TESTS_DIR="../tests"

echo "===== Generating GEMM test files ====="

# Small square matrices
./generator gemm 5 5 5 "$TESTS_DIR/gemm_test_01.txt"
./generator gemm 10 10 10 "$TESTS_DIR/gemm_test_02.txt"

# Medium square
./generator gemm 50 50 50 "$TESTS_DIR/gemm_test_03.txt"
./generator gemm 100 100 100 "$TESTS_DIR/gemm_test_04.txt"

# Larger stress test
./generator gemm 300 300 300 "$TESTS_DIR/gemm_test_05.txt"

# Non-square shapes
./generator gemm 20 50 10 "$TESTS_DIR/gemm_test_06.txt"
./generator gemm 100 10 100 "$TESTS_DIR/gemm_test_07.txt"

# Different value ranges
./generator gemm 20 20 20 "$TESTS_DIR/gemm_test_08.txt" 1 5      # small values
./generator gemm 20 20 20 "$TESTS_DIR/gemm_test_09.txt" 1 10000  # large values

echo ""
echo "===== Generating CSR test files (individual scope: small/medium only) ====="

# Small graphs, varying density
./generator csr 10 2 "$TESTS_DIR/csr_test_01.txt"
./generator csr 10 5 "$TESTS_DIR/csr_test_02.txt"

# Medium graphs
./generator csr 100 4 "$TESTS_DIR/csr_test_03.txt"
./generator csr 100 10 "$TESTS_DIR/csr_test_04.txt"

# Slightly larger, still individual-scope (not buddy-scale)
./generator csr 500 4 "$TESTS_DIR/csr_test_05.txt"
./generator csr 1000 6 "$TESTS_DIR/csr_test_06.txt"

# Directed variant
./generator csr 100 4 "$TESTS_DIR/csr_test_07.txt" 0 1 20 1

# Weighted variant (CSR format supports it structurally, even though SSSP itself is buddy task)
./generator csr 100 4 "$TESTS_DIR/csr_test_08.txt" 1 1 20

echo ""
echo "All test files generated in $TESTS_DIR"
echo "Note: manually-crafted edge case files (isolated vertex, self-loop, disconnected, etc.)"
echo "from earlier are separate and still valid — this script only adds randomly generated ones."