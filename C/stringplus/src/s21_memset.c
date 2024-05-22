#include "s21_string.h"

/*Копирует символ c (беззнаковый тип) в первые n символов строки, на которую
 * указывает аргумент str.*/

void *s21_memset(void *str, int c, s21_size_t n) {
  char *ptr_str = (char *)str;
  for (s21_size_t copy_n = 0; copy_n < n;) {
    *((unsigned char *)ptr_str + copy_n) = (unsigned char)c;
    copy_n++;
  }
  return str;
}