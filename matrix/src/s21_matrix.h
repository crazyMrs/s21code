#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define OKAY 0
#define NOCORRECT 1
#define ERROR 2
#define EPS 1e-7

typedef struct matrix_struct {
  double **matrix;
  int rows;     // строки
  int columns;  // столбцы
} matrix_t;

// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

// Создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Очистка матриц
void s21_remove_matrix(matrix_t *A);

// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Сложение (sum_matrix) и вычитание матриц (sub_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножение матрицы на число (mult_number). Умножение двух матриц (mult_matrix)
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирование матрицы (transpose)
int s21_transpose(matrix_t *A, matrix_t *result);

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result);
void s21_calculate_minor(matrix_t *A, matrix_t *min, int n_row, int n_col);

// Определитель матрицы (determinant), вычисление определителя
int s21_determinant(matrix_t *A, double *result);

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif  //  S21_MATRIX_H_