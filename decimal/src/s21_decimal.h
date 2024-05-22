#ifndef SRC_S21_DECIMAL_H_
#define SRC_S21_DECIMAL_H_

#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define s21_NAN 2143289344
#define s21_NEG_NAN -2143289344
#define s21_INT_MAX 2147483647
#define s21_INT_MIN -2147483648
#define s21_DECIMAL_MAX_NUM                       \
  {                                               \
    (0b11111111111111111111111111111111),         \
        (0b11111111111111111111111111111111),     \
        (0b11111111111111111111111111111111), (0) \
  }
#define s21_DECIMAL_MIN_NUM                   \
  {                                           \
    (0b11111111111111111111111111111111),     \
        (0b11111111111111111111111111111111), \
        (0b11111111111111111111111111111111), \
        (0b10000000000000000000000000000000)  \
  }
#define SIGN_POS 127
#define SCALE_MAX 28
#define MAX_HIGH_BIT 95
#define is_fin(x) __builtin_isfinite(x)
#define is_nan(x) __builtin_isnan(x)
#define is_inf(x) __builtin_isinf(x)

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef enum { CONVERTATION_OK, CONVERTATION_ERROR } conv_status;

typedef enum { OTHER_OK, OTHER_ERROR } other_result;

// Функции возвращают код ошибки:
// 0 - OK
// 1 - число слишком велико или равно бесконечности
// 2 - число слишком мало или равно отрицательной бесконечности
// 3 - деление на 0

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void low_scale_mul(s21_decimal *result);

/*ФУНКЦИИ ДЛЯ РАБОТЫ С DECIMAL*/

void sub_bitwise(s21_decimal *result, s21_decimal value_1, s21_decimal value_2);
int add_bitwise(s21_decimal *result, s21_decimal value_1, s21_decimal value_2);
int mul_bitwise(s21_decimal *result, s21_decimal value_1, s21_decimal value_2);
int div_bitwise(s21_decimal *result, s21_decimal value_1, s21_decimal value_2,
                s21_decimal *fract);

/*Сравнение*/
int s21_is_less(s21_decimal d1, s21_decimal d2);
int s21_equal_compare(s21_decimal d1, s21_decimal d2);
int s21_is_equal(s21_decimal d1, s21_decimal d2);
int s21_compare(s21_decimal d1, s21_decimal d2);
int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2);
int s21_is_greater(s21_decimal d1, s21_decimal d2);
int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2);
int s21_is_not_equal(s21_decimal d1, s21_decimal d2);

/*Convertors and parsers*/
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_float_format(int integer, float fract, s21_decimal *value);

int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int take_scale(s21_decimal num);
int pochti_truncate(s21_decimal value, s21_decimal *result);

/*Дополнительные функции*/
int s21_int_set_sign(s21_decimal src);
int s21_int_set_bit(s21_decimal dst, int bit, int index);
void s21_set_bit(s21_decimal *dst, int bit, int index);
int s21_get_bit(s21_decimal src, int index);
int s21_get_sign(s21_decimal src);
void s21_set_sign(s21_decimal *dst, int sign);
void s21_set_signa(s21_decimal *src, int sign);
int s21_get_scale(s21_decimal num);
void s21_set_scale(s21_decimal *dst, int scale);
void s21_set_null(s21_decimal *dst);
void nullification(s21_decimal *src);
void bring_to_a_common_denominator(s21_decimal *value_1, s21_decimal *value_2);
int s21_shift_left(s21_decimal *time_result);
int s21_scale_options(s21_decimal value_1, s21_decimal value_2);
void copy_s21_decimal(s21_decimal *result, s21_decimal value);
int check_null(s21_decimal value);
int buffer_dead_div(s21_decimal value_1, s21_decimal value_2);

int buffer_dead_add(s21_decimal val_1, s21_decimal val_2);
int buffer_dead_sub(s21_decimal val_1, s21_decimal val_2);
int buffer_dead_mul(s21_decimal value_1, s21_decimal value_2);

void check_and_give(s21_decimal value_1_copy, s21_decimal value_2_const,
                    s21_decimal *result);
int s21_seven_normalization(float src, s21_decimal *dst);

#endif  //  SRC_S21_DECIMAL_H_
