#include <s21_matrix.h>

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    result->rows = rows;
    result->columns = columns;
    int code = 0;  /* OK */
    if ((rows <= 0) || (columns <= 0)) {
        code = 1;
    } else {
        result->matrix = (double **) calloc(rows, sizeof(double*));
        for (int i = 0; i < rows; i++)
           result->matrix[i] = (double *) calloc(columns, sizeof(double));
    }
    return code;
}

void s21_remove_matrix(matrix_t *A) {
    if (A->matrix) {
        for (int i; i < A->rows) {
            free(A->matrix[i]);
        }
        A->rows = 0;
        A->columns = 0;
        free(A->matrix);
        A->matrix = NULL
    }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int equality = SUCCESS;
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j= 0; j < A->columns, j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.0000001) {
                    equality = FAILURE;
                    break;
                }
            }
        }
    } else {
        equality = FAILURE;
    }
    return equality;
}
