# CS509 Laboratory Repository — Individual Assignments

## Student Details

- **Name:** KANAK
- **Entry Number:** 2026AIM1009

---

## Repository Overview

This repository contains the individual laboratory assignments for **CS509**.

---

## Language and Environment

- **Language:** C++
- **Standard:** C++17
- **Compiler:** `g++`(Ubuntu 15.2.0-16ubuntu1) 15.2.0
- **Operating System:** Ubuntu

---

## Repository Structure

```text
CS509_AIM1009/
├── README.md
├── Makefile
│
├── common/
│   ├── csr/
│      ├── csr.h
│      └── csr.cpp
│   
│
├── common_wrapper/
│   └── wrapper.cpp
│
├── assignment_01/
│   ├── README.md
│   ├── src/
│   ├── driver/
│   ├── tests/
│   ├── tools/
│   └── outputs/
│
├── assignment_02/
│   ├── README.md
│   ├── src/
│   ├── driver/
│   ├── tests/
│   └── tools/
│
└── assignment_03/
    ├── README.md
    ├── src/
    ├── driver/
    ├── tests/
    ├── tools/
    └── outputs/
```

---

# Assignments

## Assignment 01

Assignment 01 contains the following individual implementations:

1. **GEMM — Simple**
2. **GEMM — Blocking**
3. **Adjacency List to CSR Conversion**

Detailed documentation, including algorithms, input formats, execution instructions, complexity analysis, and results, is available in:

```text
assignment_01/README.md
```

---

## Assignment 02

Assignment 02 contains the following individual implementations:

1. **Bellman-Ford**
2. **Floyd-Warshall**

Detailed documentation, including algorithms, input formats, execution instructions, complexity analysis, and results, is available in:

```text
assignment_02/README.md
```

---

## Assignment 03

Assignment 03 contains the following individual implementation:

1. **Minimum Spanning Tree — Kruskal's algorithm**
2. **Minimum Spanning Tree — Prim's algorithm**



Detailed documentation, including algorithms, input formats, execution instructions, complexity analysis, and results, is available in:

```text
assignment_03/README.md
```

---

# Common Components

## CSR

The CSR (Compressed Sparse Row) implementation is maintained under `common/csr/` because it is a reusable graph representation and conversion component used by multiple assignments.

```text
common/csr/
├── csr.h
└── csr.cpp
```



These components are intended to be shared across assignments wherever required.

---

# Common Wrapper

The file:

```text
common_wrapper/wrapper.cpp
```

provides a menu-driven interface for compiling and running the individual assignment programs.

The wrapper is intended to be executed from the **repository root**.

---

## Building and Running the Wrapper

From the repository root:

```bash
make wrapper
./common_wrapper/wrapper
```

The wrapper provides a menu containing the available individual assignment programs.

For test cases, the wrapper accepts the **test case number** instead of requiring the complete test filename.

For example:

```text
01
```

is used to select the corresponding test case according to the naming convention of the selected algorithm.

---

# Build System

Compilation is handled by the root `Makefile`.

## Build All Programs

```bash
make all
```

## Build Individual Programs
```bash
make gemm
make csr
make bellman_ford
make floyd_warshall
make mst
make wrapper
```
## Remove generated executables:
```bash
make clean
```







