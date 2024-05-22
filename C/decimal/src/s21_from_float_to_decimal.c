#include "s21_decimal.h"

/* Преобразует float в десятичное представление
    s21_decimal*/
int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  conv_status status = CONVERTATION_OK;
  bool sign = false;

  if (dst && !is_inf(src) && !is_nan(src)) {
    s21_set_null(dst);

    if (signbit(src)) {
      src *= -1.0f;
      sign = true;
    }

    float fl_int = 0.0;
    float fl_fract = modff(src, &fl_int);
    src = s21_float_format((int)fl_int, fl_fract, dst);
    int scale_temp = s21_get_scale(*dst);
    s21_from_int_to_decimal(src, dst);
    s21_set_scale(dst, scale_temp);
    s21_set_sign(dst, sign);
  } else {
    if (dst) s21_set_null(dst);
    status = CONVERTATION_ERROR;
  }

  return status;
}

int s21_float_format(int integer, float fract, s21_decimal *value) {
  char fr_str[255] = {0};
  char int_str[255] = {0};
  int cnt = 0;
  int exp = 0;

  if (fract != 0.0) {
    sprintf(fr_str, "%.9f", fract);
  }
  sprintf(int_str, "%d", integer);

  memmove(fr_str, fr_str + 2, strlen(fr_str));
  exp = strlen(int_str);
  strcat(int_str, fr_str);

  size_t cnt_sign_number = strlen(int_str);
  cnt = cnt_sign_number;

  if (cnt_sign_number > 7 && strlen(fr_str) > 0) {
    while (cnt != 7) {
      int_str[cnt--] = '\0';
    }
    if ((int)int_str[cnt] - '0' > 4) {
      cnt--;
      if (int_str[cnt] == '9') {
        while (int_str[cnt] == '9') {
          int_str[cnt--] = '0';
        }
        if (cnt != -1) {
          int_str[cnt]++;
        }
      } else {
        int_str[cnt]++;
      }
      int_str[7] = '\0';
      cnt = strlen(int_str) - 1;
      while (int_str[cnt] == '0') {
        int_str[cnt--] = '\0';
      }
    } else {
      while (int_str[cnt] == '0') {
        int_str[cnt--] = '\0';
      }
    }
  }
  exp = (strlen(int_str) - exp);
  s21_set_scale(value, exp);

  return atoi(int_str);
}
