#include "s21_string.h"

/*Выполняет поиск первого вхождения символа c (беззнаковый тип) в первых n
 * байтах строки, на которую указывает аргумент str.*/

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const char *find = (const char *)str;
  void *result = S21_NULL;
  for (s21_size_t copy_n = n; copy_n != 0; copy_n--) {
    if (*((unsigned char *)find) == (unsigned char)c) {
      result = (void *)find;
      break;
    }
    find++;
  }
  return result;
}