#!/bin/bash

# Get repository root
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
REPO_ROOT="$(cd "$SCRIPT_DIR/../.." && pwd)"

cd "$REPO_ROOT" || exit 1

echo "=============================================="
echo " CS509 Assignment 03 - MST Test Cases"
echo "=============================================="

echo
echo "Compiling MST (Kruskal + Prim)..."
make mst

if [ $? -ne 0 ]; then
    echo "MST compilation failed."
    exit 1
fi

for test_file in assignment_03/tests/mst_*.txt
do
    echo
    echo "----------------------------------------------"
    echo "Test: $test_file"
    echo "----------------------------------------------"

    output=$(./assignment_03/driver/mst_driver "$test_file")

    echo "$output" | grep -E "Algorithm:|Total MST weight:|Execution time:|Warning:"
done

echo
echo "=============================================="
echo " All tests completed."
echo "=============================================="
