#include "s21_matrix.h"

// Минор матрицы и матрица алгебраических дополнений (calc_complements)
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OKAY;
  if (A == NULL) {
    res = NOCORRECT;
  } else if (A->rows != A->columns) {
    res = ERROR;
  } else if (A->rows == 1 && A->columns == 1) {
    res = ERROR;
  } else if (A->matrix == NULL) {
    // если нет матриц
    res = NOCORRECT;
  } else {
    res = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double minor = 0.0;
        matrix_t min1 = {0};
        s21_create_matrix(A->rows - 1, A->columns - 1, &min1);
        // Вычисляем минор для текущего элемента
        s21_calculate_minor(A, &min1, i, j);
        s21_determinant(&min1, &minor);

        // Вычисляем алгебраическое дополнение и сохраняем в result
        result->matrix[i][j] = minor * pow(-1, i + j);
        s21_remove_matrix(&min1);
      }
    }
  }
  return res;
}

void s21_calculate_minor(matrix_t *A, matrix_t *min, int n_row, int n_col) {
  // Создаем временную матрицу для подматрицы
  int i = 0, j = 0;
  for (int row = 0; row < A->rows; row++) {
    for (int col = 0; col < A->columns; col++) {
      if (row != n_row && col != n_col) {
        min->matrix[i][j] = A->matrix[row][col];
        j++;
        if (j == A->columns - 1) {
          j = 0;
          i++;
        }
      }
    }
  }
}
