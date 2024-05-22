#include "s21_matrix.h"

// Транспонирование матрицы (transpose)
// замена строк этой матрицы ее столбцами с сохранением их номеров
int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = OKAY;
  if (A->matrix == NULL) {
    // если нет матриц
    res = NOCORRECT;
  } else {
    // Создание матрицы result с размерами, обратными размерам матрицы A
    res = s21_create_matrix(A->columns, A->rows, result);
    // если произошла ошибка при создании
    if (res == OKAY) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] += A->matrix[i][j];
        }
      }
    }
  }
  return res;
}