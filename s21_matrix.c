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
