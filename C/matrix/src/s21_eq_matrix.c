#include "s21_matrix.h"

// Сравнение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = FAILURE;
  if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0 ||
      A->matrix == NULL || B->matrix == NULL || A->rows != B->rows ||
      A->columns != B->columns) {
    res = FAILURE;
  } else if (A->rows == B->rows && A->columns == B->columns) {
    res = SUCCESS;
    for (int i = 0; i < A->rows && res != FAILURE; ++i) {
      for (int j = 0; j < A->columns && res != FAILURE; ++j) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) >= EPS) {
          res = FAILURE;
        }
      }
    }
  }
  return res;
}