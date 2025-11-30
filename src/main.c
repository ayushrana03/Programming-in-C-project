#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"

#define RESULT_FILE "matrix_results.txt"

void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/* Menu and operation loop */
int main(void) {
    int choice;
    printf("Matrix Calculator - Full Version\n");
    while (1) {
        printf("\nMenu:\n");
        printf("1. Add two matrices\n");
        printf("2. Subtract two matrices\n");
        printf("3. Multiply two matrices\n");
        printf("4. Transpose of a matrix\n");
        printf("5. Determinant of a matrix\n");
        printf("6. Save last result to file\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Try again.\n");
            clear_input_buffer();
            continue;
        }
        Matrix *A = NULL, *B = NULL, *R = NULL;
        double detval = 0.0;
        switch (choice) {
            case 1:
                printf("Matrix A:\n"); A = read_matrix_from_input();
                if (!A) break;
                printf("Matrix B:\n"); B = read_matrix_from_input();
                if (!B) { free_matrix(A); break; }
                R = add_matrix(A, B);
                if (!R) printf("Addition not possible (size mismatch).\n");
                else { printf("Result (A + B):\n"); print_matrix(R); }
                break;
            case 2:
                printf("Matrix A:\n"); A = read_matrix_from_input();
                if (!A) break;
                printf("Matrix B:\n"); B = read_matrix_from_input();
                if (!B) { free_matrix(A); break; }
                R = subtract_matrix(A, B);
                if (!R) printf("Subtraction not possible (size mismatch).\n");
                else { printf("Result (A - B):\n"); print_matrix(R); }
                break;
            case 3:
                printf("Matrix A:\n"); A = read_matrix_from_input();
                if (!A) break;
                printf("Matrix B:\n"); B = read_matrix_from_input();
                if (!B) { free_matrix(A); break; }
                R = multiply_matrix(A, B);
                if (!R) printf("Multiplication not possible (incompatible sizes).\n");
                else { printf("Result (A * B):\n"); print_matrix(R); }
                break;
            case 4:
                printf("Matrix A:\n"); A = read_matrix_from_input();
                if (!A) break;
                R = transpose_matrix(A);
                printf("Transpose:\n"); print_matrix(R);
                break;
            case 5:
                printf("Matrix A:\n"); A = read_matrix_from_input();
                if (!A) break;
                if (!is_square(A)) {
                    printf("Determinant requires a square matrix.\n");
                } else {
                    detval = determinant_matrix(A);
                    printf("Determinant = %.6f\n", detval);
                }
                break;
            case 6:
                /* Save last computed result R or if determinant saved as numeric */
                if (R) {
                    save_matrix_to_file(R, RESULT_FILE);
                } else {
                    printf("No matrix result in memory to save.\n");
                }
                break;
            case 7:
                printf("Exiting. Goodbye!\n");
                /* Ensure no memory leak if user exits mid-operation */
                free_matrix(A); free_matrix(B); free_matrix(R);
                return 0;
            default:
                printf("Invalid choice.\n");
        }
        /* free temp matrices and loop */
        free_matrix(A); free_matrix(B);
        free_matrix(R);
    }
    return 0;
}
