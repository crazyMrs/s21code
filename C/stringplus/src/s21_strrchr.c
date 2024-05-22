#include "s21_string.h"

/*Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке, на
 * которую указывает аргумент str.*/

char* s21_strrchr(const char* str, int c) {
  char* ptr_str = (char*)str;
  char* result = S21_NULL;
  if (str != S21_NULL) {
    for (s21_size_t n = s21_strlen(str) + 1; n; n--) {
      if (*ptr_str == (unsigned char)c) {
        result = (char*)ptr_str;
      }
      ptr_str++;
    }
  }
  return result;
}