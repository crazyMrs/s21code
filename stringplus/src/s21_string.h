#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int s21_size_t;

#define S21_NULL (void *)0

void *s21_memchr(const void *str, int c, s21_size_t n);             // done
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);   // done
void *s21_memcpy(void *dest, const void *src, s21_size_t n);        // done
void *s21_memset(void *str, int c, s21_size_t n);                   // done
char *s21_strcat(char *dest, const char *src);                      // done
char *s21_strncat(char *dest, const char *src, s21_size_t n);       // done
char *s21_strchr(const char *str, int c);                           // done
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);  // done
char *s21_strcpy(char *dest, const char *src);                      // done
char *s21_strncpy(char *dest, const char *src, s21_size_t n);       // done
s21_size_t s21_strcspn(const char *str1, const char *str2);         // done

char *s21_strerror(int incoming_number);
s21_size_t s21_strlen(const char *str);                      // done
char *s21_strpbrk(const char *str1, const char *str2);       // done
char *s21_strrchr(const char *str, int c);                   // done
char *s21_strstr(const char *haystack, const char *needle);  // done
char *s21_strtok(char *str, const char *delim);              // done
int s21_sprintf(char *str, const char *format, ...);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *str, const char *trim_chars);
int s21_sscanf(char *src, const char *format, ...);
