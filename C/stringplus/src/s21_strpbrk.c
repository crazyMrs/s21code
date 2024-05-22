#include "s21_string.h"

/*Находит первый символ в строке str1, который соответствует любому символу,
 * указанному в str2.*/

char *s21_strpbrk(const char *str1, const char *str2) {
  char *result = S21_NULL;
  for (; *str1 != '\0' && result == S21_NULL; str1++) {
    s21_size_t j = 0;
    while (str2[j] != '\0') {
      if (*str1 == str2[j]) {
        result = (char *)str1;
      }
      j++;
    }
  }
  return result;
}