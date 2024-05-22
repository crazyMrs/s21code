#include "s21_math.h"

long double s21_acos(double x) {
  long double res_s21_acos = 0.0;
  if (x != x || !(x >= -1 && x <= 1)) {
    res_s21_acos = S_NAN;
  } else if (((x >= 0) && (x <= 1))) {
    res_s21_acos = s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / x);
  }

  else if (((x < 0) && (x >= -1))) {
    res_s21_acos = S21_PI + (s21_atan(s21_sqrt(1 - s21_pow(x, 2)) / x));
  }
  return res_s21_acos;
}
