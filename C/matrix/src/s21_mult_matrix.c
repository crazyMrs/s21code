#include "s21_matrix.h"

// Умножение двух матриц (mult_matrix)
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OKAY;
  if (A->matrix == NULL || B->matrix == NULL || A->rows <= 0 ||
      A->columns <= 0 || B->rows <= 0 || B->columns <= 0 || result == NULL) {
    // если нет матриц
    res = NOCORRECT;
  } else if (A->columns != B->rows) {
    // если не совпадают размеры
    res = ERROR;
  } else if (s21_create_matrix(A->rows, B->columns, result)) {
    res = NOCORRECT;
  } else {
    if (res == OKAY) {
      for (int a = 0; a < result->rows; ++a) {
        for (int b = 0; b < result->columns; ++b) {
          result->matrix[a][b] = 0;
          for (int k = 0; k < A->columns; ++k) {
            result->matrix[a][b] += A->matrix[a][k] * B->matrix[k][b];
          }
        }
      }
    }
  }
  return res;
}