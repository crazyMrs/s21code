#include "s21_string.h"

/*Вычисляет длину строки str, не включая завершающий нулевой символ.*/

s21_size_t s21_strlen(const char *str) {
  s21_size_t num = 0;
  if (str != S21_NULL) {
    for (; *str != '\0'; num++) {
      str++;
    }
  }
  return num;
}