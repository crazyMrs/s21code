#include "s21_decimal.h"

void bring_to_a_common_denominator(
    s21_decimal* value_1,
    s21_decimal*
        value_2) {  // функция работает со знаменателем и мантиссой(приводит в
                    // порядок для работы с вычислениями)
  int sign_value_max = s21_get_sign(*value_1);
  int sign_value_min = s21_get_sign(*value_2);
  // нужно определить какая из структур имеет меньший порядок
  int max_exp = s21_get_scale(*value_1);
  int min_exp = s21_get_scale(*value_2);
  if (s21_get_scale(*value_1) < s21_get_scale(*value_2)) {
    int buf = sign_value_max;
    min_exp = s21_get_scale(*value_1);
    max_exp = s21_get_scale(*value_2);
    sign_value_max = sign_value_min;
    sign_value_min = buf;
  }
  // начинаем работу по приданию общей экспоненты путем изменения бинарно
  // заданной мантиссы
  s21_decimal* copy_min_value =
      s21_get_scale(*value_1) < s21_get_scale(*value_2) ? value_1 : value_2;
  s21_decimal* copy_max_value =
      s21_get_scale(*value_1) < s21_get_scale(*value_2) ? value_2 : value_1;
  s21_decimal decimal_ten = {{10, 0, 0, 0}};
  int limit = 0;
  for (; min_exp != max_exp && limit == 0;) {
    if (min_exp < 28 && limit == 0) {  // изменяем непосредственно саму мантиссу
      limit = mul_bitwise(copy_min_value, *copy_min_value, decimal_ten);
      if (limit == 0) {
        min_exp += 1;
        s21_set_scale(copy_min_value, min_exp);
      }
    }
  }
  value_1->bits[3] = 0;
  value_2->bits[3] = 0;
  s21_set_scale(value_1, min_exp);
  s21_set_scale(value_2, max_exp);
  if (limit != 0) {
    int new_max_exp =
        s21_get_scale(*copy_max_value) -
        (s21_get_scale(*copy_max_value) - s21_get_scale(*copy_min_value));
    s21_set_scale(copy_max_value, (s21_get_scale(*copy_max_value) -
                                   s21_get_scale(*copy_min_value)));
    s21_round(*copy_max_value, copy_max_value);
    s21_set_scale(copy_max_value, new_max_exp);
  }
  s21_set_sign(copy_min_value, sign_value_min);
  s21_set_sign(copy_max_value, sign_value_max);
}

int buffer_dead_add(s21_decimal value_1, s21_decimal value_2) {
  int check = 0;
  s21_decimal trash;
  nullification(&trash);
  if (((s21_get_sign(value_1) && s21_get_sign(value_2)) ||
       (!s21_get_sign(value_1) && !s21_get_sign(value_2))) &&
      add_bitwise(&trash, value_1, value_2)) {
    check = 1;
    if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
      check = 2;
    }
  }
  return check;
}

int buffer_dead_sub(s21_decimal value_1, s21_decimal value_2) {
  int check = 0;
  int sign_value_1 = s21_get_sign(value_1);
  int sign_value_2 = s21_get_sign(value_2);
  s21_decimal trash;
  nullification(&trash);
  unsigned int sum = 0;
  if (sign_value_1 ^ sign_value_2) {
    sum = add_bitwise(&trash, value_1, value_2);
  }
  if (sum != 0) {
    check = 1;
    if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
      check = 2;
    }
  }
  return check;
}

int buffer_dead_mul(s21_decimal value_1, s21_decimal value_2) {
  int error = 0;
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int res_sign = sign1 ^ sign2;
  s21_decimal trash;
  nullification(&trash);
  if (mul_bitwise(&trash, value_1, value_2) && res_sign == 0) {
    error = 1;
  } else if (mul_bitwise(&trash, value_1, value_2) && res_sign == 1) {
    error = 2;
  }
  return error;
}

int check_null(s21_decimal value) {
  int result = 0;
  for (int i = 0; i < 3; i++) {
    if (value.bits[i] == 0) {
      result += 1;
    }
  }
  return result;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  bring_to_a_common_denominator(&value_1, &value_2);
  int error = buffer_dead_add(value_1, value_2);
  if (result != NULL && error == 0) {
    if ((check_null(value_1) == 3 && check_null(value_2) != 3) ||
        (check_null(value_1) != 3 && check_null(value_2) == 3)) {
      add_bitwise(result, value_1, value_2);
      if (check_null(value_1) == 3) {
        s21_set_scale(result, s21_get_scale(value_2));
        s21_set_sign(result, s21_get_sign(value_2));
      } else {
        s21_set_scale(result, s21_get_scale(value_1));
        s21_set_sign(result, s21_get_sign(value_1));
      }
    } else {
      nullification(result);
      if (s21_get_sign(value_1) == 0 && s21_get_sign(value_2) == 0) {
        add_bitwise(result, value_1, value_2);
        s21_set_scale(result, s21_get_scale(value_1));
      } else if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
        add_bitwise(result, value_1, value_2);
        int scale_result = s21_get_scale(value_1);
        s21_set_scale(result, scale_result);
        s21_set_sign(result, 1);
      } else if (!s21_get_sign(value_1) && s21_get_sign(value_2)) {
        s21_decimal val_2 = {{0}};
        s21_negate(value_2, &val_2);
        if (s21_is_greater(val_2, value_1)) {
          sub_bitwise(result, val_2, value_1);
          s21_set_scale(result, s21_get_scale(value_2));
        } else if (s21_is_greater(value_1, val_2)) {
          sub_bitwise(result, value_1, val_2);
          s21_set_scale(result, s21_get_scale(value_1));
        } else {
          nullification(result);
        }
      } else if (s21_get_sign(value_1) && !s21_get_sign(value_2)) {
        s21_decimal val_1 = {{0}};
        s21_negate(value_1, &val_1);
        if (s21_is_greater(val_1, value_2)) {
          sub_bitwise(result, val_1, value_2);
          s21_set_scale(result, s21_get_scale(value_1));
          s21_set_signa(result, s21_get_sign(value_1));
        } else if (s21_is_greater(value_2, val_1)) {
          sub_bitwise(result, value_2, val_1);
        } else {
          nullification(result);
        }
      }
    }
  } else {
    if (result != NULL) {
      nullification(result);
    }
  }
  return error;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  bring_to_a_common_denominator(&value_1, &value_2);
  // s21_PrintDecimal(value_2);
  // s21_PrintDecimal(value_1);
  int error = buffer_dead_sub(value_1, value_2);
  if (result != NULL && error == 0) {
    nullification(result);
    if (!s21_get_sign(value_1) && !s21_get_sign(value_2)) {
      if (s21_is_greater_or_equal(value_1, value_2)) {
        sub_bitwise(result, value_1, value_2);
        s21_set_scale(result, s21_get_scale(value_1));
        s21_set_sign(result, 0);
      } else {
        sub_bitwise(result, value_2, value_1);
        s21_set_scale(result, s21_get_scale(value_2));
        s21_set_sign(result, 1);
      }
    } else if (s21_get_sign(value_1) && s21_get_sign(value_2)) {
      sub_bitwise(result, value_1, value_2);
      s21_set_signa(&value_1, 0);
      s21_set_signa(&value_2, 0);
      if (s21_is_greater_or_equal(value_1, value_2)) {
        sub_bitwise(result, value_1, value_2);
        s21_set_scale(result, s21_get_scale(value_1));
        s21_set_sign(result, 1);
      } else {
        sub_bitwise(result, value_2, value_1);
        s21_set_scale(result, s21_get_scale(value_2));
        s21_set_sign(result, 0);
      }
    } else {
      if (s21_get_sign(value_1) && !s21_get_sign(value_2)) {
        add_bitwise(result, value_1, value_2);
        s21_set_scale(result, s21_get_scale(value_1));
        s21_set_signa(result, 1);
      } else if (!s21_get_sign(value_1) && s21_get_sign(value_2)) {
        add_bitwise(result, value_1, value_2);
        s21_set_scale(result, s21_get_scale(value_1));
        s21_set_signa(result, 0);
      }
    }
  }
  return error;
}

int s21_scale_options(s21_decimal value_1, s21_decimal value_2) {
  int result = (s21_get_scale(value_1) + s21_get_scale(value_2));
  if ((s21_get_scale(value_1) + s21_get_scale(value_2)) > SCALE_MAX) {
    result = SCALE_MAX;
  }
  return result;
}

void copy_s21_decimal(s21_decimal* result, s21_decimal value) {
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  bring_to_a_common_denominator(&value_1, &value_2);
  int error = buffer_dead_mul(value_1, value_2);
  if (result != NULL && error == 0) {
    int sign1 = s21_get_sign(value_1);
    int sign2 = s21_get_sign(value_2);
    int res_sign = sign1 ^ sign2;
    nullification(result);
    int orig = s21_scale_options(value_1, value_2);
    s21_decimal num_ten = {{10, 0, 0, 0}};
    if ((s21_is_equal(value_1, num_ten)) && orig >= 1) {
      copy_s21_decimal(result, value_2);
      int scale_res = s21_get_scale(value_2) - 1;
      s21_set_scale(result, scale_res);
    } else if (s21_is_equal(value_2, num_ten) && orig >= 1) {
      int scale_res = s21_get_scale(value_1) - 1;
      s21_set_scale(result, scale_res);
    } else {
      mul_bitwise(result, value_1, value_2);
      s21_set_scale(result, orig);
      if (res_sign) {
        s21_set_signa(result, 1);
      } else {
        s21_set_signa(result, 0);
      }
      if (s21_get_scale(*result) > 0) {
        low_scale_mul(result);
      }
    }
  } else {
    if (result != NULL) {
      nullification(result);
    }
  }
  return error;
}

int buffer_dead_div(s21_decimal value_1, s21_decimal value_2) {
  int code_error = 0;
  s21_decimal trash;
  nullification(&trash);
  s21_decimal zero_num;
  float num_fl = 0.0;
  s21_from_decimal_to_float(value_2, &num_fl);
  nullification(&zero_num);
  if (check_null(value_2) == 3 || s21_is_equal(zero_num, value_2)) {
    code_error = 3;
  } else if (num_fl < 1.) {
    float num_check = 1. / num_fl;
    s21_decimal delitel;
    nullification(&delitel);
    s21_from_float_to_decimal(num_check, &delitel);
    if (mul_bitwise(&trash, value_1, delitel)) {
      code_error = 1;
      if (s21_get_sign(value_1) ^ s21_get_sign(value_2)) {
        code_error = 2;
      }
    }
  }
  return code_error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  bring_to_a_common_denominator(&value_1, &value_2);
  int code_error = buffer_dead_div(value_1, value_2);
  int sign1 = s21_get_sign(value_1);
  int sign2 = s21_get_sign(value_2);
  int res_sign = sign1 ^ sign2;
  int res_scale = 0;
  if (code_error == 0 && result != NULL) {
    s21_decimal fract;
    s21_decimal zero_num;
    nullification(&zero_num);
    nullification(&fract);
    nullification(result);
    int scale1 = s21_get_scale(value_1);
    int scale2 = s21_get_scale(value_2);
    value_1.bits[3] = 0;
    value_2.bits[3] = 0;
    if (s21_is_equal(value_1, value_2)) {
      s21_set_bit(result, 1, 0);
    } else if (s21_is_greater_or_equal(value_1, value_2)) {
      s21_decimal fract;
      nullification(&fract);
      div_bitwise(result, value_1, value_2, &fract);
      if (scale1 > scale2) {
        res_scale = scale1 - scale2;
      } else {
        res_scale = scale1 - scale2;
      }
      if (fract.bits[0] != 0) {
        res_scale += 1;
      }
    } else if (s21_is_less(value_1, value_2)) {
      nullification(result);
    }
    s21_set_scale(result, res_scale);
    s21_set_sign(result, res_sign);
  } else {
    if (result != NULL) {
      nullification(result);
    }
  }
  return code_error;
}

/*ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ*/

int s21_int_set_sign(s21_decimal src) { return s21_int_set_bit(src, 1, 127); }

int s21_int_set_bit(s21_decimal dst, int bit, int index) {
  int section = index / 32;
  int position = index % 32;
  return (bit == 1) ? (dst.bits[section] |= (1u << position))
                    : (dst.bits[section] &= (~((1u) << position)));
}

void s21_set_signa(s21_decimal* src, int sign) { s21_set_bit(src, sign, 127); }

void nullification(
    s21_decimal* src) {  // обнуляем массивы в оригинальном s21_decimal
  for (int i = 0; i < 4; i++) {
    src->bits[i] = 0;
  }
}

int s21_shift_left(s21_decimal* time_result) {
  int limit = 0;
  if (s21_get_bit(*time_result, MAX_HIGH_BIT) != 0) {
    limit = 1;
  }
  if (limit == 0) {
    int arr_last_zero = s21_get_bit(*time_result, 31);
    int arr_last_one = s21_get_bit(*time_result, 63);
    time_result->bits[0] = (unsigned int)time_result->bits[0] << 1;
    time_result->bits[1] = (unsigned int)time_result->bits[1] << 1;
    time_result->bits[2] = (unsigned int)time_result->bits[2] << 1;
    s21_set_bit(time_result, arr_last_zero, 32);
    s21_set_bit(time_result, arr_last_one, 64);
    s21_set_bit(time_result, 0, 0);
  }
  return limit;
}

/*ФУНКЦИИ ПОБИТОВЫХ ОПЕРАЦИЙ*/
int add_bitwise(s21_decimal* result, s21_decimal value_1, s21_decimal value_2) {
  nullification(result);
  int overflow = 0;
  int bit_yes = 0;
  for (int i = 0; i <= MAX_HIGH_BIT; i++) {
    bit_yes = (s21_get_bit(value_1, i) ^ s21_get_bit(value_2, i) ^ overflow);
    s21_set_bit(result, bit_yes, i);
    overflow = (s21_get_bit(value_1, i) && s21_get_bit(value_2, i)) ||
               (s21_get_bit(value_1, i) && overflow) ||
               (s21_get_bit(value_2, i) && overflow);
  }
  return overflow;
}

void sub_bitwise(s21_decimal* result, s21_decimal value_1,
                 s21_decimal value_2) {
  nullification(result);
  int subtrahend, subtractor;
  s21_decimal* ptr_value_1 = &value_1;
  s21_decimal* ptr_value_2 = &value_2;
  for (int i = 0; i <= MAX_HIGH_BIT; i++) {
    subtrahend = s21_get_bit(*ptr_value_1, i);
    subtractor = s21_get_bit(*ptr_value_2, i);
    if ((!subtractor && subtrahend) || (subtractor && !subtrahend)) {
      s21_set_bit(result, 1, i);
    }
    if ((!subtractor && !subtrahend) || (subtractor && subtrahend)) {
      s21_set_bit(result, 0, i);
    }
    if (!subtrahend && subtractor) {
      int num = i + 1;
      for (int j = i; !s21_get_bit(*ptr_value_1, j) && j <= MAX_HIGH_BIT; j++) {
        s21_set_bit(ptr_value_1, 1, j);
        num = j + 1;
      }
      s21_set_bit(ptr_value_1, 0, num);
    }
  }
}

void low_scale_mul(s21_decimal* result) {
  int last_scale = s21_get_scale(*result);
  int sign = s21_get_sign(*result);
  s21_decimal fract;
  s21_decimal trash;
  s21_decimal ten = {{10, 0, 0, 0}};
  nullification(&fract);
  nullification(&trash);
  div_bitwise(&trash, *result, ten, &fract);
  for (; fract.bits[0] == 0 && last_scale > 0; last_scale -= 1) {
    nullification(&fract);
    div_bitwise(result, *result, ten, &fract);
    nullification(&fract);
    div_bitwise(&trash, *result, ten, &fract);
  }
  s21_set_scale(result, last_scale);
  s21_set_sign(result, sign);
}

int mul_bitwise(s21_decimal* result, s21_decimal value_1, s21_decimal value_2) {
  s21_decimal copy_result = *result;
  nullification(result);
  int num = 0;  // количество сдвигов надо как-то регулировать
  int begunok = 0;
  int limit = 0;  // возможно при умножении на 10 будет переполнение
  s21_decimal time_result;
  nullification(&time_result);
  while (num <= 95 && limit == 0) {
    if (s21_get_bit(value_2, num)) {
      time_result = value_1;
      begunok = 1;
    }
    if (begunok) {
      for (int i = 0; i <= (num - 1) && limit == 0; i++) {
        limit = s21_shift_left(&time_result);
      }
      if (limit == 0) {
        int limit2 = 0;
        limit2 = add_bitwise(result, *result, time_result);
        if (limit2 != 0) {
          limit = limit2;
          nullification(result);
        }
      }
    }
    begunok = 0;
    num += 1;
    nullification(&time_result);
  }
  if (limit) {
    *result = copy_result;
  }
  return limit;
}

int div_bitwise(s21_decimal* result, s21_decimal value_1, s21_decimal value_2,
                s21_decimal* fract) {
  int error_div = 0;
  // bring_to_a_common_denominator(&value_1, &value_2);
  value_1.bits[3] = 0;
  value_2.bits[3] = 0;
  s21_decimal value_1_copy = value_1;
  s21_decimal zero_num;
  s21_decimal sum = {{1, 0, 0, 0}};
  nullification(&zero_num);
  nullification(result);
  if (s21_is_equal(value_2, zero_num)) {
    error_div = 1;  // деление на ноль дает либо +inf, -inf, nan
  } else if (s21_is_equal(value_1, zero_num)) {
    result = &value_1;
  } else if (s21_is_equal(value_1, value_2)) {
    s21_set_bit(result, 1, 0);
  } else {
    while (s21_is_less(value_2, value_1_copy)) {
      s21_decimal value_2_copy = value_2;
      int num = 0;
      s21_decimal check_fin_value_2 = value_2;
      while (s21_is_less(check_fin_value_2, value_1_copy)) {
        error_div = s21_shift_left(&check_fin_value_2);
        if (error_div != 0) {
          break;
        }
        if (s21_is_less_or_equal(check_fin_value_2, value_1_copy)) {
          num += 1;
        }
      }
      if (error_div != 0) {
        break;
      }
      while (num != 0) {
        error_div = s21_shift_left(&value_2_copy);
        if (error_div != 0) {
          break;
        }
        s21_shift_left(&sum);
        num -= 1;
      }
      if (error_div != 0) {
        break;
      }
      sub_bitwise(&value_1_copy, value_1_copy, value_2_copy);
      add_bitwise(result, sum, *result);
      nullification(&sum);
      s21_set_bit(&sum, 1, 0);
    }
    check_and_give(value_1, value_2, result);
  }
  mul_bitwise(fract, *result, value_2);
  sub_bitwise(fract, value_1, *fract);
  return error_div;
}
void check_and_give(s21_decimal value_1_copy, s21_decimal value_2_const,
                    s21_decimal* result) {
  s21_decimal trash_1 = {{0, 0, 0, 0}};
  s21_decimal trash_2 = {{0, 0, 0, 0}};
  mul_bitwise(&trash_1, *result, value_2_const);
  sub_bitwise(&trash_2, value_1_copy, trash_1);  // 25 - 20 = 5
  if (s21_is_greater_or_equal(trash_2, value_2_const)) {
    s21_decimal one = {{1, 0, 0, 0}};
    add_bitwise(result, *result, one);
  }
}

/*ФУНКЦИИ СРАВНЕНИЯ*/

int s21_is_less(s21_decimal d1, s21_decimal d2) {  // Меньше
  // Функция для проверки, является ли d1 меньшим числом, чем d2
  int result = -1;
  int sign1 =
      s21_get_bit(d1, SIGN_POS);  // Получение значения знака числа d1 и d2
  int sign2 = s21_get_bit(d2, SIGN_POS);
  bring_to_a_common_denominator(&d1, &d2);  // нормализация
  if (s21_is_equal(d1, d2)) {               // если равно то 0
    result = 0;
  } else if (sign1 > sign2) {  // если знак d1 больше то 1
    result = 1;
  } else if (sign1 == 0 && sign2 == 1) {
    result = 0;
  } else if (sign1 == 1 && sign2 == 1) {  // если оба отрицательные
    if (s21_compare(d1, d2) == 1) {  // Сравниваем их абсолютные значения
      result = 0;
    } else {
      result = 1;
    }
  } else {
    result = s21_compare(d1, d2);  // во всех других случаях
  }
  return result;
}

// Функция для проверки, равны ли числа d1 и d2
int s21_is_equal(s21_decimal d1, s21_decimal d2) {  // равно
                                                    // это для 0
  if (d1.bits[0] == 0 && d2.bits[0] == 0 && d1.bits[1] == 0 &&
      d2.bits[1] == 0 && d1.bits[2] == 0 && d2.bits[2] == 0) {
    return 1;
  }
  bring_to_a_common_denominator(&d1, &d2);

  int sign1 = s21_int_set_sign(d1),
      sign2 = s21_int_set_sign(d2);  // Установка знака числа d1 и d2

  // Возвращаем результат сравнения или 0, если знаки разные
  return (sign1 == sign2) ? s21_equal_compare(d1, d2) : 0;
}

// Функция для сравнения чисел на равенство
int s21_equal_compare(s21_decimal d1, s21_decimal d2) {
  int result = -1;
  for (int i = 0; i < 4; i++) {
    if (d1.bits[i] != d2.bits[i]) {
      result = 0;  // Если хотя бы одна секция отличается, числа не равны
      break;
    } else {
      result = 1;  // Если все секции равны, числа равны
    }
  }
  return result;
}

// Функция для сравнения двух положительных чисел 1 - д1 меньше
int s21_compare(s21_decimal d1, s21_decimal d2) {
  int result = -1;
  // Сравниваем биты чисел d1 и d2 на каждой позиции, начиная с позиции 95
  for (int i = 2; i >= 0; i--) {
    if (d1.bits[i] < d2.bits[i]) {
      result = 1;
      break;
    } else if (d1.bits[i] > d2.bits[i]) {
      result = 0;
      break;
    } else {
      result = 0;
    }
  }
  return result;  // Возвращаем результат сравнения
}

// меньше или равно
int s21_is_less_or_equal(s21_decimal d1, s21_decimal d2) {
  return s21_is_less(d1, d2) || s21_is_equal(d1, d2);
}

// больше
int s21_is_greater(s21_decimal d1, s21_decimal d2) {
  return s21_is_less(d2, d1);
}

// больше или равно
int s21_is_greater_or_equal(s21_decimal d1, s21_decimal d2) {
  return !s21_is_less(d1, d2);
}

// не равно
int s21_is_not_equal(s21_decimal d1, s21_decimal d2) {
  return !s21_is_equal(d1, d2);
}

/*Convertors and parsers*/
