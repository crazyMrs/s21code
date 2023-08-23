#include "s21_string.h"

/*Сравнивает строку, на которую указывает str1, со строкой, на которую указывает
 * str2.*/

int s21_strcmp(const char *str1, const char *str2) {
  int result = 0;
  s21_size_t n1 = s21_strlen(str1);
  s21_size_t n2 = s21_strlen(str2);
  s21_size_t n = n1;
  if (n1 > n2) {
    n = n2;
  }
  for (s21_size_t i = 0; i < n; i++) {
    if (str1[i] != str2[i]) {
      result = str1[i] - str2[i];
      break;
    }
  }
  if (result == 0 && n1 != n2) {
    if (n1 > n2) {
      result = str1[n];
    } else {
      result = -str2[n];
    }
  }
  return result;
}