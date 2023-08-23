#include "s21_matrix.h"

// Обратная матрица (inverse_matrix)
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = OKAY;
  if (A->matrix == NULL || A->rows < 1 || A->columns < 1)
    res = NOCORRECT;
  else if (A->rows != A->columns)
    res = ERROR;
  else {
    double deter = 0;
    s21_determinant(A, &deter);
    if (deter == 0) res = ERROR;
    if (res == OKAY) {
      matrix_t mat = {0};
      res = s21_create_matrix(A->rows, A->columns, &mat);
      s21_calc_complements(A, result);
      s21_transpose(result, &mat);
      s21_mult_number(&mat, (1 / deter), result);
      s21_remove_matrix(&mat);
    }
  }
  return res;
}