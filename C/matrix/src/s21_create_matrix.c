#include "s21_matrix.h"

// Создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OKAY;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    res = NOCORRECT;
  } else {
    // Выделение памяти для строк матрицы
    result->matrix = calloc(rows, sizeof(double *));
    result->rows = rows;
    result->columns = columns;

    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        // Выделение памяти для столбцов матрицы
        result->matrix[i] = calloc(columns, sizeof(double));
      }
    }
  }
  return res;
}