#include "s21_math.h"

long double s21_asin(double x) {
  long double res_s21_asin = 0.0;
  if (x != x || !(x >= -1 && x <= 1)) {
    res_s21_asin = S_NAN;
  } else {
    res_s21_asin = s21_atan(x / s21_sqrt(1 - s21_pow(x, 2)));
  }
  return res_s21_asin;
}
