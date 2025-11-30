#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>

typedef struct {
    int rows;
    int cols;
    double **data; 
} Matrix;

Matrix* create_matrix(int rows, int cols);
void free_matrix(Matrix *m);


Matrix* read_matrix_from_input(void);
void print_matrix(const Matrix *m);
void save_matrix_to_file(const Matrix *m, const char *filename);


Matrix* add_matrix(const Matrix *a, const Matrix *b);
Matrix* subtract_matrix(const Matrix *a, const Matrix *b);
Matrix* multiply_matrix(const Matrix *a, const Matrix *b);
Matrix* transpose_matrix(const Matrix *a);
double determinant_matrix(const Matrix *a); 
Matrix* cofactor_matrix(const Matrix *a);

/* Utilities */
int is_square(const Matrix *m);

#endif /* MATRIX_H */
