#include "s21_math.h"

long double s21_ceil(double x) {  //возвращает ближайшее целое число, не меньшее
                                  //заданного значения
  long double result;
  if (S21_NAN(x) || S21_INF(x))
    result = x;
  else {
    int int_x = (int)x;
    result = (x == (double)int_x) ? x : ((x > 0) ? int_x + 1 : int_x);
  }
  return result;
}