#include "s21_math.h"

long double s21_tan(double x) {
  long double sin_x = s21_sin(x);
  long double cos_x = s21_cos(x);
  long double tan_x = sin_x / cos_x;

  return tan_x;
}
