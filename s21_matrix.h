#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <stdlib.h>
#include <math.h>

typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;

#define SUCCESS 1
#define FAILURE 0

int s21_create_matrix(int rows, int columns, matrix_t *result); // создание матрицы
void s21_remove_matrix(matrix_t *A);  // очистка матрицы
int s21_eq_matrix(matrix_t *A, matrix_t *B);  // сравнение матрицы

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  // сложение
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  // вычитание

int s21_mult_number(matrix_t *A, double number, matrix_t *result);  // скаляр
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);  // цмножение матриц

int s21_transpose(matrix_t *A, matrix_t *result);  // транспонировать

int s21_calc_complements(matrix_t *A, matrix_t *result);  // минор

int s21_determinant(matrix_t *A, double *result);  // определитель

int s21_inverse_matrix(matrix_t *A, matrix_t *result);  // обратная матрица  A^{-1}=\frac{1} {|A|} × A_*^T

 
#endif  // SRC_S21_MATRIX_H_
