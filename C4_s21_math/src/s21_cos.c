#include "s21_math.h"

long double s21_cos(double x) {
  long double result = x;

  if (x == S_NAN || x == INF_NEG || x == INF_POS) {
    result = S_NAN;  // если x равен неопределенным или бесконечным значениям,
                     // возвращаем S_NAN
  } else {
    // Приводим a к интервалу [-pi/2, pi/2]
    if (x < 0) {
      x = -x;
    }
    while (x > 2 * S21_PI) {
      x -= 2 * S21_PI;
    }
    if (x > S21_PI) {
      x -= 2 * S21_PI;
    }

    // Инициализируем переменные
    long double sum = 1.0;
    long double term = 1.0;
    long double sign = -1.0;
    int n = 2;

    // Вычисляем сумму ряда Тейлора
    while (term > S21_ECS) {
      double numerator = 1;
      double denominator = 1;
      for (int i = 2; i <= n; i += 2) {
        numerator *=
            x * x;  //числитель ряда Тейлора с учетом предыдущих четных чисел
        denominator *= (i - 1) * i;  //знаменатель ряда Тейлора
      }
      term = numerator / denominator;
      term *= sign;
      sum += term;
      sign = -sign;
      n += 2;
      if (term < 0) {
        term = -term;
      }
    }

    result = sum;  // присваиваем вычисленное значение суммы ряда Тейлора
                   // переменной result
  }

  return result;
}