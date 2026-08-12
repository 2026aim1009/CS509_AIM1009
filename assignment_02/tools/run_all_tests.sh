#!/bin/bash

# Get repository root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"

cd "$REPO_ROOT" || exit 1

echo "=============================================="
echo " CS509 Assignment 02 - All Test Cases"
echo "=============================================="

# Compile both algorithms once
echo
echo "Compiling Bellman-Ford..."
make bellman_ford

if [ $? -ne 0 ]; then
    echo "Bellman-Ford compilation failed."
    exit 1
fi

echo
echo "Compiling Floyd-Warshall..."
make floyd_warshall

if [ $? -ne 0 ]; then
    echo "Floyd-Warshall compilation failed."
    exit 1
fi

# --------------------------------------------------
# Bellman-Ford
# --------------------------------------------------

echo
echo "=============================================="
echo " Bellman-Ford Test Cases"
echo "=============================================="

for test_file in assignment_02/tests/bf_*.txt
do
    echo
    echo "----------------------------------------------"
    echo "Test: $test_file"
    echo "----------------------------------------------"

    output=$(./assignment_02/driver/bellman_ford_driver "$test_file")

    echo "$output" | grep -E "Algorithm:|Source:|Negative cycle:|Execution time:"
done

# --------------------------------------------------
# Floyd-Warshall
# --------------------------------------------------

echo
echo "=============================================="
echo " Floyd-Warshall Test Cases"
echo "=============================================="

for test_file in assignment_02/tests/fw_*.txt
do
    echo
    echo "----------------------------------------------"
    echo "Test: $test_file"
    echo "----------------------------------------------"

    output=$(./assignment_02/driver/floyd_warshall_driver "$test_file")

    echo "$output" | grep -E "Algorithm:|Negative cycle:|Execution time:"
done

echo
echo "=============================================="
echo " All tests completed."
echo "=============================================="