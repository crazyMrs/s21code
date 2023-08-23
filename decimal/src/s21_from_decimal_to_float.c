#include "s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  conv_status err_code = CONVERTATION_OK;
  float res = 0.0;
  res = src.bits[0] * pow(4294967295, 0) + src.bits[1] * pow(4294967295, 1) +
        src.bits[2] * pow(4294967295, 2);
  int scale = s21_get_scale(src);
  res /= pow(10, scale);
  if (s21_get_sign(src)) {
    res *= -1;
  }
  *dst = res;
  return err_code;
}
