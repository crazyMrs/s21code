#include "s21_string.h"

void* s21_trim(const char* src, const char* trim_chars) {
  char* result = S21_NULL;
  if (src && trim_chars) {
    char* left_str = (char*)src;
    char* right_str = (char*)src + s21_strlen(src);
    for (; *left_str && s21_strchr(trim_chars, *left_str); left_str++)
      ;
    for (; right_str != left_str && s21_strchr(trim_chars, *(right_str - 1));
         right_str--)
      ;
    result = (char*)calloc((right_str - left_str + 1), sizeof(char));
    if (result) {
      s21_strncpy(result, left_str, right_str - left_str);
      *(result + (right_str - left_str)) = '\0';
    }
  }
  return result;
}