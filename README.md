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

| Test File | Input Size (MxK, KxN) | Expected Output | Actual Output | Simple Time (ms) | Blocking Time (ms) | Block Size | Status |
|---|---|---|---|---|---|---|---|
| gemm_test_01.txt | 5x5, 5x5 | 12068 14986 9428 11717 14426 .. | 12068 14986 9428 11717 14426 .. | 0.002648  | 0.004046 | 2 | Pass |
| gemm_test_02.txt | 10x10, 10x10 | 24840 27540 20022 22092 25141.. | 24840 27540 20022 22092 25141.. | 0.014422 | 0.017136 | 2 | Pass |
| gemm_test_03.txt | 50x50, 50x50 | 126923 114949 138924 125585 116154.. | 126923 114949 138924 125585 116154.. | 1.24615 | 1.30095 | 16 | Pass |
| gemm_test_03.txt | 50x50, 50x50 | 126923 114949 138924 125585 116154.. | 126923 114949 138924 125585 116154.. | 1.24615 | 1.37996 | 32 | Pass |
| gemm_test_05.txt | 300x300, 300x300 | .. | ... | 257.876 | 230.438 | 32 | pass |
| gemm_test_05.txt | .. | .. | ... | ... | ... | ... | ... |
| gemm_test_06.txt | .. | .. | ... | ... | ... | ... | ... |
| gemm_test_07.txt | .. | .. | ... | ... | ... | ... | ... |
| gemm_test_08.txt | .. | .. | ... | ... | ... | ... | ... |
| gemm_test_09.txt | .. | .. | ... | ... | ... | ... | ... |



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

| Test File | V | E | Description | Expected row_ptr / col_idx | Actual Output | Conversion Time (ms) | Status |
|---|---|---|---|---|---|---|---|
| csr_test_01.txt | 10 | 10 | .. | row_ptr: 0 4 4 6 8 12 12 12 17 19 20  / col_idx: 4 7 8 9 4 7 4 7 0 2 3 7 0 2 3 4 8 0 7 0  | matches | 0.002421 | Pass |
| csr_test_02.txt | 10 | 25 | .. | row_ptr: 0 6 9 15 20 25 29 33 38 46 50  / col_idx: 2 4 5 7 8 9 6 8 9 0 3 4 6 7 8 2 4 6 7 8 0 2 3 7 8 0 6 8 9 1 2 3 5 0 2 3 4 8 0 1 2 3 4 5 7 9 0 1 5 8  | matches | 0.002801 | Pass |
| csr_test_03.txt | 100 | 200 | .. | row_ptr: 0 1 6 9 16 19 21 27 32 40 42 49 54 59 64 70 71 78 79 82 84 90 93 95 100 100 102 105 110 115 117 127 131 135 139 143 148 150 154 157 158 165 170 177 181 190 192 198 204 208 212 217 220 226 231 234 239 243 252 257 262 266 270 280 286 290 292 296 299 305 305 308 311 315 317 321 326 330 331 335 340 343 345 349 350 355 359 361 361 362 362 367 371 373 376 379 386 388 391 393 400 / col_idx: 64 23 35 53 64 70 50 59 93 11 17 34 40 42 52 99 12 43 61 8 95 35 55 66 82 90 91 33 34 63 68 97 5 13 30 52 53 57 74 90 10 48 9 15 28 57 72 76 85 3 16 27 43 53 4 26 43 58 75 8 16 18 74 82 27 30 32 42 76 98 10 11 13 19 38 44 60 62 3 13 49 56 16 40 30 53 54 59 61 75 46 56 68 65 80 1 28 34 58 68 26 68 12 25 84 11 14 32 40 73 10 23 47 63 78 80 99 8 14 20 44 46 47 59 60 65 95 38 47 52 95 14 27 72 77 7 41 48 75 3 7 23 90 1 6 49 71 74 46 81 42 54 91 99 16 31 57 59 3 19 27 41 62 74 92 33 40 46 47 76 3 14 37 50 51 71 80 4 11 12 99 16 30 51 54 57 67 72 82 88 59 85 21 30 36 41 57 63 28 30 31 41 52 78 9 33 49 57 18 35 48 50 2 42 49 62 86 42 44 66 3 8 31 47 66 93 1 8 11 20 79 20 37 44 6 57 60 70 84 18 21 60 90 8 10 38 44 46 48 55 62 84 12 23 78 94 97 2 20 30 39 45 16 30 55 56 4 20 62 79 16 40 50 57 61 68 84 85 90 95 7 28 46 76 86 93 0 1 67 98 22 30 6 51 52 71 44 64 75 7 21 23 25 62 94 1 55 99 35 42 66 10 32 44 78 27 94 8 13 35 40 12 20 33 67 92 10 14 41 63 32 28 47 58 72 53 61 81 83 91 22 29 42 36 79 6 13 44 84 79 26 55 57 62 82 10 45 62 95 50 63 44 6 8 34 56 62 6 37 79 96 40 75 2 52 63 58 68 73 5 30 31 62 85 96 99 91 95 7 58 99 14 64 3 29 37 43 70 95 97  | matches | 0.008962 | Pass |
| csr_test_04.txt | 100 | 500 | .. | row_ptr: 0 8 19 30 44 48 53 64 80 98 103 119 132 142 149 164 168 182 187 196 201 213 225 230 243 247 253 260 269 285 293 314 327 336 347 353 366 374 381 392 400 410 419 436 446 460 468 478 493 499 506 521 533 544 556 563 571 578 591 601 613 626 6....../ col_idx: col_idx: 39 53 57 61 64 74 85 95 7 8 12 23 35 53 64 70 74 77 98 7 14 23 33 50 53 59 76 80 91 93 11 15 17 28 34 40 41 42 52 63 76 78 95 99 12 43 61 87 8 16 58 68 95 11 35 36 39 55 63 66 82 90 91 95 1 2 18 31 32 33 34 35 49 52 63 66 68 78 86 97 1 5 10 13 30 31 32 36 38 50 52 53 57 66 74 80 90 96 10 15 47 48 60 8 9 15 28 33 43 47 57 60 72 75 76 82 85 90 94 3 6 16 24 27 43 45 53 65 70 86 88 94 1 4 19 22 26 43 58 75 91 98 8 16 18 42 60 74 82 2 26 27 30 32 42 45 48 50 62 76 82 89 91 98 3 9 10 58 5 11 13 18 19 38 42 44 46 50 52 60 62 64 3 23 63 81 91 7 13 16 37 45 49 55 56 60 12 16 31 40 88 22 30 33 34 42 50 53 54 59 61 75 82 31 35 42 46 56 60 62 68 69 76 81 94 12 20 47 65 80 1 2 17 28 34 41 42 45 58 60 68 94 98 11 29 30 95 26 30 38 44 68 83 12 14 25 54 61 71 84 11 14 32 35 40 62 70 73 82 3 10 23 30 37 38 40 41 44 47 51 55 59 63 73 78 24 39 68 69 80 85 88 99 8 14 20 24 25 28 31 42 44 46 47 59 60 61 65 66 67 82 95 96 97... | matches | 0.014177 | Pass |


### Complexity
- Time: O(V + E)
- Space: O(V + E)

### References
