#include "s21_matrix.h"

// Определитель матрицы (determinant), вычисление определителя
int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL) return NOCORRECT;

  if (A->rows != A->columns) {
    *result = 0.0;  // Возвращаем 0 при несоответствии числа строк и столбцов
    return ERROR;
  }

  if (A->rows == 0 || A->columns == 0) {
    *result = 0.0;  // Возвращаем 0 при пустой матрице
    return OKAY;
  }

  // int res = OKAY;
  double det = 0.0;
  double minor_det = 0.0;

  if (A->rows == 1) {
    *result = A->matrix[0][0];
  } else if (A->rows == 2) {
    *result = (A->matrix[0][0] * A->matrix[1][1]) -
              (A->matrix[0][1] * A->matrix[1][0]);
  } else if (A->rows > 2) {
    matrix_t minor = {0};
    for (int i = 0; i < A->rows; i++) {
      int res_minor = s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
      if (res_minor == OKAY) {
        s21_calculate_minor(A, &minor, i, 0);
        s21_determinant(&minor, &minor_det);
        int sign = (i % 2 == 0) ? 1 : -1;
        det += sign * A->matrix[i][0] * minor_det;
        s21_remove_matrix(&minor);
      }
    }
    *result = det;
  }

  return OKAY;
}
