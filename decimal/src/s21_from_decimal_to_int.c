#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  conv_status err_code = CONVERTATION_OK;
  long int buffer = 0;
  s21_decimal src_copy = src;
  int sign = s21_get_sign(src);

  if ((s21_get_bit(src, 31)) && s21_get_sign(src)) {
    s21_set_bit(&src_copy, 0, 31);
  }
  *dst = 0;
  int scale = s21_get_scale(src);

  if (src_copy.bits[0]) {
    buffer = src_copy.bits[0] * pow(4294967295, 0) +
             src_copy.bits[1] * pow(4294967295, 1) +
             src_copy.bits[2] * pow(4294967295, 2);
    buffer /= (int)pow(10, scale);

  } else {
    buffer = src_copy.bits[0];
  }
  if ((buffer >= s21_INT_MAX)) {
    buffer = s21_INT_MAX;
  }
  buffer = (sign) ? -buffer : buffer;

  *dst = buffer;
  return err_code;
}
