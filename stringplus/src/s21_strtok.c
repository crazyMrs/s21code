#include "s21_string.h"

/*Разбивает строку str на ряд токенов, разделенных delim.*/

void check_delim(char** last_result, const char* delim) {
  int flag = 0;
  for (s21_size_t i = 0; **last_result != '\0' && delim[i] != '\0' && !flag;
       i++) {
    if (**last_result == delim[i]) {
      flag = 1;
    }
  }
  while (**last_result != '\0' && flag) {
    int f = 0;
    for (s21_size_t i = 0; delim[i] != '\0' && !f; i++) {
      if (**last_result == delim[i]) {
        f = 1;
        *last_result += 1;
      }
    }
    if (!f) {
      flag = 0;
    }
  }
}

int check_null(char** last_result) {
  return *last_result == S21_NULL || **last_result == '\0' ? 1 : 0;
}

char* str_on(char** last_result, char** base2, char** base) {
  char* result;
  if (**last_result == '\0' && !(*base - *last_result)) {
    *last_result = S21_NULL;
    result = S21_NULL;
  } else {
    if (*base2 != S21_NULL) {
      *last_result = *base2;
      **last_result = '\0';
      *last_result += 1;
    }
    result = *base;
  }
  return result;
}

char* s21_strtok(char* str, const char* delim) {
  static char* last_result;
  const char* result;
  if (str != S21_NULL) {
    last_result = str;
  }
  if (check_null(&last_result)) {
    result = S21_NULL;
  }
  if (!check_null(&last_result)) {
    check_delim(&(last_result), delim);
    char* base = last_result;
    char* base2 = s21_strpbrk(base, delim);
    if (base2 == S21_NULL) {
      while (*last_result != '\0') {
        last_result++;
      }
    }
    result = str_on(&last_result, &base2, &base);
  }
  return (char*)result;
}
