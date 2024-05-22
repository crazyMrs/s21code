#include "s21_math.h"

long double s21_sin(double x) {
  long double result = x;

  if (x == S_NAN || x == INF_NEG || x == INF_POS) {
    result = S_NAN;  // если x равен неопределенным или бесконечным значениям,
                     // возвращаем S_NAN
  } else {
    // Приводим x к интервалу [-pi, pi]
    x = s21_fmod(x, 2 * S21_PI);
    if (x > S21_PI) {
      x -= 2 * S21_PI;
    }

    long double sum = x;
    long double term = x;
    long double prev = x;
    int i = 3;

    while ((term < 0 ? -term : term) > S21_ECS) {
      term *= -x * x / ((long double)i * (long double)(i - 1));
      sum += term;
      if (sum == prev) break;
      prev = sum;
      i += 2;
    }

    result = sum;  // присваиваем вычисленное значение суммы ряда Тейлора
                   // переменной result
  }

  return result;
}