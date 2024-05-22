#include "s21_decimal.h"

// Устанавливает бит с заданным индексом в числе s21_decimal
void s21_set_bit(s21_decimal *dst, int bit, int index) {
  int section = index / 32;
  int position = index % 32;

  if (bit == 1) {
    dst->bits[section] |= (1u << position);
  } else {
    dst->bits[section] &= (~((1u) << position));
  }
}

//Устанавливает все биты числа dst в нули
void s21_set_null(s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = 0;
  }
}

//Устанавливает бит знака числа dst в значение sign
void s21_set_sign(s21_decimal *dst, int sign) { s21_set_bit(dst, sign, 127); }

// Получает значение бита с заданным индексом из числа src
int s21_get_bit(s21_decimal src, int index) {
  int section = index / 32;
  int position = index % 32;
  unsigned int bit_mask = (1u << position);
  int bit = ((src.bits[section] & bit_mask) >> position);
  return bit;
}

//Получает значение знака числа src
int s21_get_sign(s21_decimal src) { return (s21_get_bit(src, SIGN_POS)); }

//Получает значение степени числа num
int s21_get_scale(s21_decimal num) {
  int mask = 255 << 16;
  int scale = (num.bits[3] & mask) >> 16;
  return scale;
}

//Устанавливает значение степени числа dst
void s21_set_scale(s21_decimal *dst, int scale) {
  int mask = scale << 16;
  dst->bits[3] = mask;
}