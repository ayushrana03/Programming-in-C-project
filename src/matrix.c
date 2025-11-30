#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "matrix.h"

/* Create matrix with allocated rows x cols, initialized to 0 */
Matrix* create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) return NULL;
    Matrix *m = (Matrix*) malloc(sizeof(Matrix));
    if (!m) return NULL;
    m->rows = rows;
    m->cols = cols;
    m->data = (double**) malloc(rows * sizeof(double*));
    if (!m->data) { free(m); return NULL; }
    for (int i = 0; i < rows; ++i) {
        m->data[i] = (double*) calloc(cols, sizeof(double));
        if (!m->data[i]) {
            /* rollback */
            for (int j = 0; j < i; ++j) free(m->data[j]);
            free(m->data); free(m);
            return NULL;
        }
    }
    return m;
}

void free_matrix(Matrix *m) {
    if (!m) return;
    for (int i = 0; i < m->rows; ++i) free(m->data[i]);
    free(m->data);
    free(m);
}

/* Read matrix from stdin (asks for rows cols then entries) */
Matrix* read_matrix_from_input(void) {
    int r, c;
    printf("Enter rows and columns (e.g. 3 3): ");
    if (scanf("%d %d", &r, &c) != 2) {
        printf("Invalid input.\n");
        return NULL;
    }
    Matrix *m = create_matrix(r, c);
    if (!m) { printf("Memory allocation failed.\n"); return NULL; }
    printf("Enter %d elements (row-wise):\n", r * c);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (scanf("%lf", &m->data[i][j]) != 1) {
                printf("Invalid number. Aborting read.\n");
                free_matrix(m);
                return NULL;
            }
        }
    }
    return m;
}

void print_matrix(const Matrix *m) {
    if (!m) { printf("NULL matrix\n"); return; }
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            printf("%8.3f ", m->data[i][j]);
        }
        printf("\n");
    }
}

/* Save to text file - simple CSV-like rows */
void save_matrix_to_file(const Matrix *m, const char *filename) {
    if (!m || !filename) return;
    FILE *f = fopen(filename, "a"); /* append so multiple results accumulate */
    if (!f) { printf("Error opening file %s for writing.\n", filename); return; }
    fprintf(f, "Matrix %dx%d\n", m->rows, m->cols);
    for (int i = 0; i < m->rows; ++i) {
        for (int j = 0; j < m->cols; ++j) {
            fprintf(f, "%.6f", m->data[i][j]);
            if (j < m->cols - 1) fprintf(f, ",");
        }
        fprintf(f, "\n");
    }
    fprintf(f, "----\n");
    fclose(f);
    printf("Saved result to %s\n", filename);
}

/* Check square */
int is_square(const Matrix *m) {
    if (!m) return 0;
    return m->rows == m->cols;
}

/* Add */
Matrix* add_matrix(const Matrix *a, const Matrix *b) {
    if (!a || !b) return NULL;
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix *r = create_matrix(a->rows, a->cols);
    if (!r) return NULL;
    for (int i = 0; i < a->rows; ++i)
        for (int j = 0; j < a->cols; ++j)
            r->data[i][j] = a->data[i][j] + b->data[i][j];
    return r;
}

/* Subtract */
Matrix* subtract_matrix(const Matrix *a, const Matrix *b) {
    if (!a || !b) return NULL;
    if (a->rows != b->rows || a->cols != b->cols) return NULL;
    Matrix *r = create_matrix(a->rows, a->cols);
    if (!r) return NULL;
    for (int i = 0; i < a->rows; ++i)
        for (int j = 0; j < a->cols; ++j)
            r->data[i][j] = a->data[i][j] - b->data[i][j];
    return r;
}

/* Multiply */
Matrix* multiply_matrix(const Matrix *a, const Matrix *b) {
    if (!a || !b) return NULL;
    if (a->cols != b->rows) return NULL;
    Matrix *r = create_matrix(a->rows, b->cols);
    if (!r) return NULL;
    for (int i = 0; i < a->rows; ++i) {
        for (int j = 0; j < b->cols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < a->cols; ++k)
                sum += a->data[i][k] * b->data[k][j];
            r->data[i][j] = sum;
        }
    }
    return r;
}

/* Transpose */
Matrix* transpose_matrix(const Matrix *a) {
    if (!a) return NULL;
    Matrix *t = create_matrix(a->cols, a->rows);
    if (!t) return NULL;
    for (int i = 0; i < a->rows; ++i)
        for (int j = 0; j < a->cols; ++j)
            t->data[j][i] = a->data[i][j];
    return t;
}

/* Helper to get submatrix excluding row p and column q */
static Matrix* get_submatrix(const Matrix *m, int p, int q) {
    Matrix *sub = create_matrix(m->rows - 1, m->cols - 1);
    if (!sub) return NULL;
    int subi = 0;
    for (int i = 0; i < m->rows; ++i) {
        if (i == p) continue;
        int subj = 0;
        for (int j = 0; j < m->cols; ++j) {
            if (j == q) continue;
            sub->data[subi][subj] = m->data[i][j];
            subj++;
        }
        subi++;
    }
    return sub;
}

/* Determinant using recursive Laplace expansion */
double determinant_matrix(const Matrix *m) {
    if (!m || !is_square(m)) {
        fprintf(stderr, "Determinant: matrix must be square\n");
        return NAN;
    }
    int n = m->rows;
    if (n == 1) return m->data[0][0];
    if (n == 2) {
        return m->data[0][0]*m->data[1][1] - m->data[0][1]*m->data[1][0];
    }
    double det = 0.0;
    for (int col = 0; col < n; ++col) {
        Matrix *sub = get_submatrix(m, 0, col);
        double subdet = determinant_matrix(sub);
        double sign = ((col % 2) == 0) ? 1.0 : -1.0;
        det += sign * m->data[0][col] * subdet;
        free_matrix(sub);
    }
    return det;
}

/* Optional: cofactor matrix */
Matrix* cofactor_matrix(const Matrix *a) {
    if (!a || !is_square(a)) return NULL;
    int n = a->rows;
    Matrix *cof = create_matrix(n, n);
    if (!cof) return NULL;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Matrix *sub = get_submatrix(a, i, j);
            double subdet = determinant_matrix(sub);
            double sign = (((i + j) % 2) == 0) ? 1.0 : -1.0;
            cof->data[i][j] = sign * subdet;
            free_matrix(sub);
        }
    }
    return cof;
}
