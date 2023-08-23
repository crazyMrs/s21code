#include "s21_math.h"

long double s21_fmod(double x,
                     double y) {  //остаток от деления x на y = числитель —
                                  //(целое частное) * знаменателю
  long double result;
  long int s = x / y;  //целая часть от деления
  if (y == 0.0 || x == INF_POS || x == INF_NEG) {
    result = S_NAN;
  } else if (y == INF_POS || y == INF_NEG) {
    result = x;
  } else {
    result = x - (s * y);
  }
  return result;
}