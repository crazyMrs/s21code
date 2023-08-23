#include "s21_matrix.h"

// Очистка матриц
void s21_remove_matrix(matrix_t *A) {
  // если матрица А не равна 0, то очищаем память
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      // очищаем память каждой строки матрицы
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    // освобождаем память массива указателей
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  }
}