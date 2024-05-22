#include "s21_matrix.h"

// Умножение матрицы на число (mult_number)
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = OKAY;
  res = s21_create_matrix(A->rows, A->columns, result);
  if (A == NULL || A->matrix == NULL) {
    // если нет матриц
    res = NOCORRECT;
  } else if (A->rows != result->rows || A->columns != result->columns) {
    // если не совпадают размеры
    res = ERROR;
  } else {
    if (res == OKAY) {
      for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return res;
}