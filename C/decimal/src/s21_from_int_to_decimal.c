#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  conv_status err_code = CONVERTATION_OK;
  if (dst) {
    s21_set_null(dst);
    uint64_t src_long = src;
    int sign = 0;
    if (src < 0) {
      src_long = -src_long;
      sign = 1;
    }
    if (src <= INT32_MAX) {
      dst->bits[0] = src_long;
      s21_set_sign(dst, sign);
    } else {
      s21_set_null(dst);
      err_code = CONVERTATION_ERROR;
    }
  } else {
    err_code = CONVERTATION_ERROR;
  }
  return err_code;
}
