#include "s21_string.h"

/*Копирует строку, на которую указывает src, в dest.*/

char *s21_strcpy(char *dest, const char *src) {
  if (dest != S21_NULL && src != S21_NULL) {
    char *ptr_dest = dest;
    for (s21_size_t i = 0; src[i] != '\0'; i++) {
      *ptr_dest = src[i];
      ptr_dest++;
    }
    *ptr_dest = '\0';
  }
  return dest;
}