#!/bin/bash

# Get repository root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"

cd "$REPO_ROOT" || exit 1

echo "=============================================="
echo " CS509 Assignment 04 - Vertex Coloring Tests"
echo "=============================================="

echo
echo "Compiling Vertex Coloring..."
make vertex_coloring

if [ $? -ne 0 ]; then
    echo "Vertex Coloring compilation failed."
    exit 1
fi

for test_file in assignment_04/tests/color_*.txt
do
    echo
    echo "----------------------------------------------"
    echo "Test: $test_file"
    echo "----------------------------------------------"

    output=$(./assignment_04/driver/vertex_coloring_driver "$test_file")

    echo "$output" | grep -E "Algorithm:|Colors used:|Valid:|Execution time:"
done

echo
echo "=============================================="
echo " CS509 Assignment 04 - PageRank Tests"
echo "=============================================="

echo
echo "Compiling PageRank..."
make pagerank

if [ $? -ne 0 ]; then
    echo "PageRank compilation failed."
    exit 1
fi

for test_file in assignment_04/tests/pagerank_*.txt
do
    echo
    echo "----------------------------------------------"
    echo "Test: $test_file"
    echo "----------------------------------------------"

    output=$(./assignment_04/driver/pagerank_driver "$test_file")

    echo "$output" | grep -E "Algorithm:|Damping:|Sum of ranks:|Iterations:|Converged:|Top vertex:|Execution time:"
done

echo
echo "=============================================="
echo " All tests completed."
echo "=============================================="
