#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  int error = ((!src || !str) || (!src && !str));
  char *p_str = S21_NULL;
  int check_lenght = 0;
  if (!error) check_lenght = (s21_strlen(src) < start_index);
  if (!error && *src && !check_lenght) {
    int lenght = s21_strlen((char *)src) + s21_strlen((char *)str) + 2;
    if ((p_str = calloc(lenght, sizeof(char))) != S21_NULL) {
      for (int i = 0, j = 0; j < lenght - 2; ++i, ++j) {
        if (i == (int)start_index) {
          while (*str) {
            p_str[j] = *str;
            str++, j++;
          }
        }
        p_str[j] = src[i];
      }
    }
  }
  return p_str;
}