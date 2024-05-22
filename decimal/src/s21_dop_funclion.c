#include "s21_decimal.h"

// Округляет указанное Decimal число до ближайшего целого числа в сторону
// отрицательной бесконечности
int s21_floor(s21_decimal value, s21_decimal *result) {
  if (result) {
    //  Инициализация результата нулями
    s21_set_null(result);
    int sign = s21_get_sign(value);
    s21_decimal temp_val = value;
    s21_truncate(value, &temp_val);
    if (sign == 1 && s21_compare(temp_val, value) != 0) {
      temp_val.bits[0] += 1;
    }
    *result = temp_val;  // Просто копируем обрезанное значение в результат
  } else {
    return OTHER_ERROR;
  }
  return OTHER_OK;
}

// Возвращает целые цифры указанного Decimal числа
int s21_truncate(s21_decimal value, s21_decimal *result) {
  s21_set_null(result);
  int scale = take_scale(value);
  int sign = s21_get_sign(value);
  while (scale > 0) {
    unsigned long long numberber = value.bits[2];
    int last_numberber = 0;
    for (int j = 2; j >= 0; j--) {
      last_numberber = numberber % 10;
      value.bits[j] = numberber / 10;
      numberber = last_numberber * (4294967296) + value.bits[j - 1];
    }
    value.bits[3] = 0;
    scale--;
  }
  *result = value;
  s21_set_sign(result, sign);
  return 0;
}

// Возвращает значение cтепени числа number
int take_scale(s21_decimal number) {
  int bit_mask = 127 << 16;
  int scale = (bit_mask & number.bits[3]) >> 16;
  return scale;
}

//Округляет Decimal до ближайшего целого числа
int s21_round(s21_decimal value, s21_decimal *result) {
  if (result) {
    s21_set_null(result);
    s21_decimal temp_value = value;  // Создаем копию value для изменений
    if (take_scale(temp_value) == 0) {
      *result = temp_value;
    } else {
      // Учитываем масштаб (scale)
      int scale = take_scale(temp_value);

      //  Округляем число
      s21_truncate(value, result);

      s21_decimal pochti_ostatok;  // сюда мы закинем результат почти транкейта
      s21_set_null(&pochti_ostatok);
      pochti_truncate(value, &pochti_ostatok);
      unsigned int ostatok;
      ostatok = pochti_ostatok.bits[0] % 10u;  // остаток нашелся
      if (scale > 0)
        if (ostatok >= 5) {
          if (ostatok == 8) {  // особый случай округления к ближайшему четному
          } else {
            result->bits[0] += 1;
          }
        }
      //  Применяем знак к результату
      s21_set_sign(result, s21_get_sign(value));
    }
  } else {
    return OTHER_ERROR;
  }
  return OTHER_OK;
}

// почти транкейт - функция недоделывает транкейт один раз; в result окажется
// число (чей нулевой бит мы поделим на 10, чтобы узнать остаток)
int pochti_truncate(s21_decimal value, s21_decimal *result) {
  s21_set_null(result);
  int scale = take_scale(value);
  int sign = s21_get_sign(value);
  while (scale > 1) {
    unsigned long long numberber = value.bits[2];
    int last_numberber = 0;
    for (int j = 2; j >= 0; j--) {
      last_numberber = numberber % 10;
      value.bits[j] = numberber / 10;
      numberber = last_numberber * (4294967296) + value.bits[j - 1];
    }
    value.bits[3] = 0;
    scale--;
  }
  *result = value;
  s21_set_sign(result, sign);
  return 0;
}

//Возвращает результат умножения указанного Decimal на -1
int s21_negate(s21_decimal value, s21_decimal *result) {
  if (result) {
    // Инициализация результата нулями
    s21_set_null(result);
    s21_set_scale(result,
                  take_scale(value));  // Копирование степени исходного значения

    if (s21_get_bit(value, 127) == 0) {
      s21_set_bit(result, 1, 127);
    } else {
      s21_set_bit(result, 0, 127);
    }
    // Если исходное значение имеет нулевой бит знака, копируем нулевой бит в
    // результат, иначе удаляем нулевой бит из результата

    for (size_t position = 0; position < 96; position++) {
      if (s21_get_bit(value, position) == 0) {
        s21_set_bit(result, 0, position);  // Если бит значения равен нулю,
                                           // удаляем его из результата
      } else {
        s21_set_bit(result, 1, position);  // Если бит значения равен единице,
                                           // копируем его в результат
      }
    }
  } else {
    return OTHER_ERROR;  // Если передан нулевой указатель на результат,
                         // возвращаем ошибку
  }

  return OTHER_OK;  // Возвращаем статус выполнения операции
}
