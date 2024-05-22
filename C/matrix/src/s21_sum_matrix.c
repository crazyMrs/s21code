#include "s21_matrix.h"

// Сложение (sum_matrix)
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OKAY;
  if (A->matrix == NULL || B->matrix == NULL) {
    // если нет матриц
    res = NOCORRECT;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    // если не совпадают размеры
    res = ERROR;
  } else {
    res = s21_create_matrix(A->rows, A->columns, result);
    // если произошла ошибка при создании
    // if(res != OKAY) return result;
    if (res == OKAY) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return res;
}