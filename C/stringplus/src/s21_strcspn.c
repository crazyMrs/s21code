#include "s21_string.h"

/*Вычисляет длину начального сегмента str1, который полностью состоит из
 * символов, не входящих в str2.*/

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t n_str1 = s21_strlen(str1);
  s21_size_t n_str2 = s21_strlen(str2);
  s21_size_t result = n_str1;
  s21_size_t result_prev = result;
  for (s21_size_t i = 0; i < n_str1; i++) {
    if (result_prev > result) {
      break;
    }
    for (s21_size_t j = 0; j < n_str2; j++) {
      if (str1[i] == str2[j]) {
        if (i < result) {
          result = i;
          break;
        }
      }
    }
  }

  return result;
}