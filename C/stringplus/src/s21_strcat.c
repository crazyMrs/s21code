#include "s21_string.h"

/*Добавляет строку, на которую указывает src, в конец строки, на которую
 * указывает dest.*/

char *s21_strcat(char *dest, const char *src) {
  s21_size_t n = s21_strlen(dest);
  char *ptr_dest = dest + n;
  for (; *src != '\0'; src++) {
    *ptr_dest = *src;
    ptr_dest++;
  }
  *ptr_dest = '\0';
  return dest;
}