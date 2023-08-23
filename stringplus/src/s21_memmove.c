#include "s21_string.h"

/*Еще одна функция для копирования n символов из src в dest.*/

void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  if (dest != S21_NULL && src != S21_NULL) {
    char *ptr_dest = (char *)dest;
    char *ptr_src = (char *)src;
    if (ptr_dest > ptr_src) {
      for (s21_size_t copy_n = n; copy_n;) {
        copy_n--;
        *(ptr_dest + copy_n) = *(ptr_src + copy_n);
      }
    } else {
      for (s21_size_t i = 0; i < n; i++) {
        *(ptr_dest + i) = *(ptr_src + i);
      }
    }
  }
  return dest;
}