#include "s21_string.h"

/*Сравнивает первые n байтов str1 и str2.*/

int s21_memcmp(const void* str1, const void* str2, s21_size_t n) {
  int difference = 0;
  const unsigned char* ptr_to_str1 = (const unsigned char*)str1;
  const unsigned char* ptr_to_str2 = (const unsigned char*)str2;
  for (s21_size_t copy_n = n; copy_n != 0;) {
    if (*ptr_to_str1 == *ptr_to_str2) {
      ptr_to_str1++;
      ptr_to_str2++;
    } else {
      difference = (int)*ptr_to_str1 - (int)*ptr_to_str2;
      break;
    }
    copy_n--;
  }
  return difference;
}