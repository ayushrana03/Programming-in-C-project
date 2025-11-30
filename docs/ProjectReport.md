# Project Report
## Project Title
Matrix Calculator - Full Version

## Course
C Programming Major Project (CSEG1032)

## Student
<Your Name>

## Instructor
Dr. Srinivasan Ramachandran

## Date
<DD Month YYYY>

## Abstract
This project implements a modular Matrix Calculator in C that supports matrix addition, subtraction, multiplication, transpose, determinant calculation, and saving results to a file. The implementation demonstrates use of dynamic memory allocation, pointers, structures, recursion, and file I/O.
  

## Problem Definition
Many basic matrix calculators lack modular, memory-safe implementations. This project aims to create a reusable C program that performs typical matrix operations with clear, maintainable code and persistent result logging.


## System Design
### Data Structure
- `Matrix` structure containing `rows`, `cols`, and `double** data` (dynamic 2D array).

### Modules
- `matrix.c` — implementations for create, free, add, subtract, multiply, transpose, determinant, save.
- `main.c` — interactive menu and orchestration.

### File format
- Results are saved to `matrix_results.txt` in CSV-like rows with a header.


## Algorithms
### Addition / Subtraction
Element-wise loops for matching dimensions.

### Multiplication
Standard triple loop: `C[i][j] = sum_k A[i][k] * B[k][j]`.

### Transpose
Swap indices: `T[j][i] = A[i][j]`.

### Determinant (Recursion)
Laplace expansion: recursively compute determinants of submatrices (suitable for small n).

### Memory management
All matrices allocated with `malloc`/`calloc` and freed using `free` to avoid leaks.


## Implementation Details
- Language: C
- Files:
  - `include/matrix.h`
  - `src/matrix.c`
  - `src/main.c`
- Compile command: `gcc -Iinclude src/main.c src/matrix.c -o matrix_calc -lm`

Key functions:
- `create_matrix`, `free_matrix`
- `add_matrix`, `subtract_matrix`, `multiply_matrix`
- `transpose_matrix`
- `determinant_matrix`
- `save_matrix_to_file`

## Testing & Results
### Test case 1: Addition
A = [[1,2],[3,4]], B = [[5,6],[7,8]] → A+B = [[6,8],[10,12]]

### Test case 2: Multiplication
A = [[1,2],[3,4]], B = [[2,0],[1,2]] → A*B = [[4,4],[10,8]]

### Test case 3: Determinant
A = [[1,2],[3,4]] → det(A) = -2

### Persistence
Saved matrices appended in `matrix_results.txt` and re-checkable.

## Conclusion & Future Work
The project meets course requirements and demonstrates use of studied C topics. Future improvements:
- Implement determinant via LU decomposition for better performance.
- Add inverse matrix computation.
- Add GUI or web front-end.
- Add unit tests and input validation improvements.

## References
- C standard library documentation (`stdio.h`, `stdlib.h`, `string.h`, `math.h`)
- Course guidelines and example repository.


## Appendix
- Source code listings (include full source files in appendix or attach as files).
