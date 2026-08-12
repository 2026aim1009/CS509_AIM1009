# CS509 Assignment 01 — Individual

## Overview

Assignment 01 implements:

- **GEMM — Simple**
- **GEMM — Blocking**
- **Adjacency List to CSR Conversion**

## 1. GEMM

### Objective

Multiply matrix `A (M×K)` with matrix `B (K×N)` to produce `C (M×N)`.

### Approaches

- **Simple:** Standard triple-loop matrix multiplication.
- **Blocking:** Tiled matrix multiplication using a runtime `blockSize`.

### Input Format

```text
M K N
A matrix
B matrix
```

### Files

```text
assignment_01/
├── src/
│   ├── gemm.h
│   └── gemm.cpp
├── driver/
│   └── gemm_driver.cpp
├── tests/
│   └── gemm_test_*.txt
└── tools/
    ├── generator.cpp
    └── generate_all_tests.sh
```

### Build and Run

From the repository root:

```bash
make gemm
./assignment_01/driver/gemm_driver assignment_01/tests/gemm_test_01.txt 2
```

The last argument is the blocking size.

### Results

| Test | Input Size | Block Size | Simple (ms) | Blocking (ms) | Status |
|---|---|---:|---:|---:|---|
| `gemm_test_01.txt` | 5×5, 5×5 | 2 | 0.002648 | 0.004046 | Pass |
| `gemm_test_02.txt` | 10×10, 10×10 | 2 | 0.014422 | 0.017136 | Pass |
| `gemm_test_03.txt` | 50×50, 50×50 | 16 | 1.24615 | 1.30095 | Pass |
| `gemm_test_03.txt` | 50×50, 50×50 | 32 | 1.24615 | 1.37996 | Pass |
| `gemm_test_05.txt` | 300×300, 300×300 | 32 | 257.876 | 230.438 | Pass |

**Complexity:** `O(M × K × N)` time and `O(M × K + K × N + M × N)` space.

---

## 2. CSR Conversion

### Objective

Convert an adjacency-list graph into **Compressed Sparse Row (CSR)** format.

The CSR representation contains:

- `row_ptr`
- `col_idx`
- `values`

### Input Format

```text
V E
u degree neighbor1 neighbor2 ...
...
SOURCE s
```

### Files

CSR is maintained as a common component because it is reused by later
assignments.

```text
common/
└── csr/
    ├── csr.h
    └── csr.cpp

assignment_01/
├── driver/
│   └── csr_driver.cpp
└── tests/
    └── csr_test_*.txt
```

### Build and Run

From the repository root:

```bash
make csr
./assignment_01/driver/csr_driver assignment_01/tests/csr_test_01.txt
```

### Results

| Test | V | E | Time (ms) | Status |
|---|---:|---:|---:|---|
| `csr_test_01.txt` | 10 | 10 | 0.002421 | Pass |
| `csr_test_02.txt` | 10 | 25 | 0.002801 | Pass |
| `csr_test_03.txt` | 100 | 200 | 0.008962 | Pass |
| `csr_test_04.txt` | 100 | 500 | 0.014177 | Pass |

**Complexity:** `O(V + E)` time and `O(V + E)` space.

---

## Timing

Timing is measured only around the algorithm call using
`high_resolution_clock`.

File I/O, input parsing, and output printing are excluded from the measured
region.

All timings are reported in milliseconds (`ms`).

## References

1. [CS509 Assignment 01 Laboratory Specification](../README.md)
2. [Introduction to Algorithms — MIT Press](https://mitpress.mit.edu/9780262046305/introduction-to-algorithms/)
3. [Matrix Multiplication — Wikipedia](https://en.wikipedia.org/wiki/Matrix_multiplication)

