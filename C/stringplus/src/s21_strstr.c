#include "s21_string.h"

/*Находит первое вхождение всей строки needle (не включая завершающий нулевой
 * символ), которая появляется в строке haystack.*/

char *s21_strstr(const char *haystack, const char *needle) {
  char *result = S21_NULL;
  if (haystack == S21_NULL || needle == S21_NULL) {
    result = S21_NULL;
  } else {
    if (!(*haystack)) {
      result = (char *)haystack;
    } else {
      s21_size_t n_hay = s21_strlen(haystack);
      s21_size_t n_need = s21_strlen(needle);
      for (s21_size_t i = 0; i < n_hay && result == S21_NULL; i++) {
        s21_size_t count = 0;
        for (s21_size_t j = 0; j < n_need; j++) {
          if (haystack[i] == needle[j]) {
            i++;
            count++;
          }
        }
        if (count == n_need) {
          result = (char *)haystack + (i - count);
        }
      }
    }
  }
  return result;
}