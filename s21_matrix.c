#include "s21_matrix.h"

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
        for (int i = 0; i < A->rows; i++) {
            free(A->matrix[i]);
        }
        A->rows = 0;
        A->columns = 0;
        free(A->matrix);
        A->matrix = NULL;
    }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    int equality = SUCCESS;
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.0000001) {
                    equality = FAILURE;
                    i = B->rows;  /* break */
                    j = B->columns;  /* break */
                }
            }
        }
    } else {
        equality = FAILURE;
    }
    return equality;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int code = 0;
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
            }
        }
    } else {
        code = 2;
    }
    return code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int code = 0;
    if ((A->rows == B->rows) && (A->columns == B->columns)) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
            }
        }
    } else {
        code = 2;
    }
    return code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
        int code = 0;
    if ((A->rows > 0) && (A->columns > 0)) {
        s21_create_matrix(A->rows, A->columns, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[i][j] = number * A->matrix[i][j];
            }
        }
    } else {
        code = 1;
    }
    return code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int code = 0;
    if ((A->rows > 0) && (A->columns > 0) && (B->rows > 0) && (B->columns > 0)) {
        if (A->columns == B->rows) {
            s21_create_matrix(A->rows, B->columns, result);
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < B->columns; j++) {
                    for (int k = 0; k < A->columns; k++) {
                        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
                    }
                }
            }
        } else {
            code = 2;
        }
    } else {
        code = 1;
    }
    return code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    int code = 0;
    if ((A->rows > 0) && (A->columns > 0)) {
        s21_create_matrix(A->columns, A->rows, result);
        for (int i = 0; i < A->rows; i++) {
            for (int j = 0; j < A->columns; j++) {
                result->matrix[j][i] = A->matrix[i][j];
            }
        }
    } else {
        code = 1;
    }
    return code;
}

void s21_mini(int k, int p, matrix_t* A, matrix_t* sub_mtr) {
    int sub_i = 0;
    for (int i = 0; i < A->rows; i++) {
        int sub_j = 0;
        if (i != k) {
            for (int j = 0; j < A->columns; j++) {
                if (j != p) {
                    sub_mtr->matrix[sub_i][sub_j] = A->matrix[i][j];
                    sub_j++;
                }
            }
            sub_i++;
        }
    }
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
    int code = 0;
    if ((A->rows > 0) && (A->columns > 0)) {
        if (A->rows == A->columns) {
            s21_create_matrix(A->rows, A->columns, result);
            matrix_t sub_mtr;
            s21_create_matrix(A->rows - 1, A->columns - 1, &sub_mtr);
            for (int i = 0; i < A->rows; i++) {
                for (int j = 0; j < A->columns; j++) {
                    s21_mini(i, j, A, &sub_mtr);
                    s21_determinant(&sub_mtr, &result->matrix[i][j]);
                    result->matrix[i][j] *= pow(-1, i + j);
                }
            }
            s21_remove_matrix(&sub_mtr);
        } else {
            code = 2;
        }
    } else {
        code = 1;
    }
    return code;
}

int s21_determinant(matrix_t *A, double *result) {
    int code = 0;
    if ((A->rows > 0) && (A->columns > 0)) {
        if (A->rows == A->columns) {
            if (A->rows == 1) {
                *result = A->matrix[0][0];
            } else {
                *result = s21_det(A->rows, A);
            }
        } else {
            code = 2;
        }
    } else {
        code = 1;
    }
    return code;
}

double s21_det(int rows, matrix_t* A) {
    matrix_t sub_mtr;
    s21_create_matrix(A->rows, A->columns, &sub_mtr);
    double det = 0;
    if (rows == 2) {
        det = A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
        for (int c = 0; c < rows; c++) {
            int sub_i = 0;
            for (int i = 1; i < rows; i++) {
                int sub_j = 0;
                for (int j = 0; j < rows; j++) {
                    if (j != c) {
                        sub_mtr.matrix[sub_i][sub_j] = A->matrix[i][j];
                        sub_j++;
                    }
                }
                sub_i++;
            }
            det += pow(-1, c) * A->matrix[0][c] * s21_det(rows - 1, &sub_mtr);
        }
    }
    s21_remove_matrix(&sub_mtr);
    return det;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
    int code = 0;
    if ((A->rows > 0) && (A->columns > 0)) {
        if (A->rows == A->columns) {
            double det = 0;
            s21_determinant(A, &det);
            if (fabs(det) >= 0.0000001) {
                matrix_t alg_dop;
                matrix_t transpose_alg_dop;
                s21_calc_complements(A, &alg_dop);
                s21_transpose(&alg_dop, &transpose_alg_dop);
                s21_mult_number(&transpose_alg_dop, pow(det, -1), result);
                s21_remove_matrix(&alg_dop);
                s21_remove_matrix(&transpose_alg_dop);
            } else {
                code = 2;
            }
        } else {
            code = 2;
        }
    } else {
        code = 1;
    }
    return code;
}
