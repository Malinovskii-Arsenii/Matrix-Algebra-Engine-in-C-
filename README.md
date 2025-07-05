# Matrix Algebra Engine in C++

A C++ library for matrix operations: addition, subtraction, multiplication, division (via inversion), and matrix inversion using Gauss-Jordan elimination.

## Features

- Class-based matrix implementation
- Operator overloading: `+`, `-`, `*`, `/`, `[]`
- Matrix inversion with pivoting (Gauss method)
- Manual memory management (no STL)
- CLI input/output interface

## How to Use

```bash
# Compile
g++ matrix.cpp -o matrix

# Run
./matrix
