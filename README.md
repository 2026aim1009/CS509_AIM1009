# CS509 Laboratory Repository — Individual Assignments

## Repository Overview
This repository contains individual assignment work for CS509.

## Student Details
- Name: KANAK
- Entry Number: 2026AIM1009

## Language and Environment
- Language: C++
- Compiler: g++ (git version 2.53.0)
- OS: Ubuntu
- Standard: C++17

## Directory Structure

```
CS509_AIM1009/
├── README.md
├── common_wrapper/
│   └── wrapper.cpp          — menu to compile/run GEMM and CSR
└── assignment_01/
    ├── src/
    │   ├── gemm.h / gemm.cpp   — GEMM Simple and Blocking implementations
    │   └── csr.h / csr.cpp     — Adjacency-list to CSR conversion
    ├── driver/
    │   ├── gemm_driver.cpp     — reads GEMM input, times & runs algorithm, prints result
    │   └── csr_driver.cpp      — reads graph input, times & runs CSR conversion, prints result
    ├── tools/
    │   ├── generator.cpp       — generates GEMM and CSR test files
    │   └── generate_all_tests.sh
    ├── tests/                  — all test input files
    └── outputs/                — optional saved outputs
```

## Common Wrapper: Build and Usage
```bash
cd common_wrapper
g++ -std=c++17 -o wrapper wrapper.cpp
./wrapper
```
- Option 1: Run one GEMM test file (prompts for filename and block size)
- Option 2: Run one CSR test file (prompts for filename)
- Option 0: Exit

## General Conventions
- Test files follow the naming pattern `gemm_test_XX.txt` / `csr_test_XX.txt` .
- Timing is measured only around the algorithm call (`high_resolution_clock`), excluding file I/O,
  parsing, and output printing, per assignment requirements.
- Reported in milliseconds (ms).

---

## Assignment 01 — GEMM (Individual)

### Objective
Multiply two matrices A (M×K) and B (K×N) to produce C (M×N), using both a direct
triple-loop (Simple) implementation and a cache-friendly tiled (Blocking) implementation.

### Algorithm / Approach
- **Simple**: standard three nested loops (i, j, k)
- **Blocking**: matrices are divided into `blockSize × blockSize` tiles to improve cache reuse;
  block size is passed as a command-line argument at run time

### Input Format
M K N
A row 0 ... A row M-1
B row 0 ... B row K-1

### File Structure
- `src/gemm.h`, `src/gemm.cpp` — `gemmSimple()`, `gemmBlocking()`
- `driver/gemm_driver.cpp` — reads file, times both algorithms, prints results

### Compilation
```bash
cd assignment_01/driver
g++ -o gemm_driver gemm_driver.cpp ../src/gemm.cpp
```

### Execution
```bash
./gemm_driver ../tests/gemm_test_01.txt <blockSize>
```

### Result Table

| Test File | Input Size (MxK, KxN)  | Simple Time (ms) | Blocking Time (ms) | Block Size | Status |
|---|---|---|---|---|---|
| gemm_test_01.txt | 5x5, 5x5 |  0.002648  | 0.004046 | 2 | Pass |
| gemm_test_02.txt | 10x10, 10x10 |  0.014422 | 0.017136 | 2 | Pass |
| gemm_test_03.txt | 50x50, 50x50 |  1.24615 | 1.30095 | 16 | Pass |
| gemm_test_03.txt | 50x50, 50x50 |  1.24615 | 1.37996 | 32 | Pass |
| gemm_test_05.txt | 300x300, 300x300 |  257.876 | 230.438 | 32 | pass |



### Complexity
- Time: O(M×K×N) for both Simple and Blocking
- Space: O(M×K + K×N + M×N)



---

## CSR — Adjacency List to CSR Conversion (Individual)

### Objective
Convert an adjacency-list graph representation into Compressed Sparse Row (CSR) format
(`row_ptr`, `col_idx`, `values`), as required preprocessing for graph algorithms.

### Algorithm / Approach
- Compute `row_ptr` by accumulating each vertex's degree
- Fill `col_idx` and `values` by placing each vertex's neighbors starting at its `row_ptr` offset

### Input Format

V E
u0 degree neighbor1 neighbor2 ...
...
SOURCE s

### File Structure
- `src/csr.h`, `src/csr.cpp` — `CSRGraph` struct, `convertToCSR()`
- `driver/csr_driver.cpp` — reads adjacency-list file, times & runs conversion, prints CSR arrays

### Compilation
```bash
cd assignment_01/driver
g++ -o csr_driver csr_driver.cpp ../src/csr.cpp
```

### Execution
```bash
./csr_driver ../tests/csr_test_01.txt
```

### Result Table

| Test File | V | E | Conversion Time (ms) | Status |
|---|---|---|---|---|
| csr_test_01.txt | 10 | 10 | 0.002421 | Pass |
| csr_test_02.txt | 10 | 25 | 0.002801 | Pass |
| csr_test_03.txt | 100 | 200 | 0.008962 | Pass |
| csr_test_04.txt | 100 | 500 |  0.014177 | Pass |


### Complexity
- Time: O(V + E)
- Space: O(V + E)

### References
