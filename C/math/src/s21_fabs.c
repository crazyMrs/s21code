#include "s21_math.h"

long double s21_fabs(double x) {  //абсолютное значение числа с плавающей точкой
  if (x < 0) x = -x;
  return x;
}