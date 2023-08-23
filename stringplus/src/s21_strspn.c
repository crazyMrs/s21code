#include "s21_string.h"

/*Вычисляет длину начального сегмента str1, который полностью состоит из
 * символов str2.*/

s21_size_t s21_strspn(const char* str1, const char* str2) {
  s21_size_t result = 0;
  s21_size_t result_last = result;
  for (const char* ptr_str1 = str1; *ptr_str1; ptr_str1++) {
    for (const char* ptr_str2 = str2; *ptr_str2 && result == result_last;
         ptr_str2++) {
      if (*ptr_str1 == *ptr_str2) {
        result = result + 1;
      }
    }
    if (result == result_last) {
      break;
    }
    result_last = result;
  }
  return result;
}