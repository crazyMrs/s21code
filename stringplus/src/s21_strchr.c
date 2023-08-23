#include "s21_string.h"

/*Выполняет поиск первого вхождения символа c (беззнаковый тип) в строке, на
 * которую указывает аргумент str.*/

char* s21_strchr(const char* str, int c) {
  char* result = S21_NULL;
  char* ptr_str = (char*)str;
  s21_size_t n = s21_strlen(str) + 1;
  for (s21_size_t i = 0; i < n; i++) {
    if ((unsigned char)c == str[i]) {
      result = ptr_str;
      break;
    }
    ptr_str++;
  }
  return result;
}