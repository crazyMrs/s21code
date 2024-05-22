#include "s21_string.h"

/*Копирует до n символов из строки, на которую указывает src, в dest.*/

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (dest != S21_NULL && src != S21_NULL) {
    char *ptr_dest = dest;
    for (s21_size_t i = 0; i < n && src[i] != '\0'; i++) {
      *ptr_dest = src[i];
      ptr_dest++;
    }
    *ptr_dest = '\0';
  }
  return dest;
}