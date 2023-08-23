#include "s21_string.h"

/*Сравнивает не более первых n байтов str1 и str2.*/

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;
  if (n == 0) {
    result = 0;
  } else {
    const char *ptr_str1 = str1;
    const char *ptr_str2 = str2;
    for (s21_size_t i = 0; i < n && *ptr_str1 != '\0' && *ptr_str2 != '\0';
         i++) {
      if (result == 0 && *ptr_str1 != *ptr_str2) {
        result = *((unsigned char *)ptr_str1) - *((unsigned char *)ptr_str2);
      }
      ptr_str1++;
      ptr_str2++;
    }
    if (*ptr_str1 != *ptr_str2 && result == 0) {
      result = *((unsigned char *)ptr_str1) - *((unsigned char *)ptr_str2);
    }
  }
  return result;
}
