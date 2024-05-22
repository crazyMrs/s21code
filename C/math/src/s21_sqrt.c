#include "s21_math.h"

long double s21_sqrt(double x) {  //вычисляет квадратный корень
  long double result;
  if (x < 0 || x == INF_NEG || S21_NAN(x)) {
    result = S_NAN;
  } else if (x == 0 || S21_INF(x))
    result = (long double)x;
  else {
    long double half_x = x / 2;
    long double error =
        x - half_x * half_x;  //Вычисляется значение ошибки, которая будет
                              //использоваться для проверки точности вычисления

    while (error > S21_ECS ||
           error <
               -S21_ECS) {  // продолжаем пока ошибка не станет меньше чем 1e-6
      half_x = (half_x + x / half_x) / 2;
      error = x - half_x * half_x;  //Вычисляется новая ошибка
    }
    result = half_x;
  }
  return result;
}