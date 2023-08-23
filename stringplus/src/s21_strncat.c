#include "s21_string.h"

/*Добавляет строку, на которую указывает src, в конец строки, на которую
 * указывает dest, длиной до n символов.*/

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t n_dest = s21_strlen(dest);
  char *ptr_dest = dest + n_dest;
  for (s21_size_t x = 0; x < n; x++) {
    *ptr_dest = src[x];
    ptr_dest++;
  }
  return dest;
}