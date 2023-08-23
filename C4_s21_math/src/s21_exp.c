#include "s21_math.h"

long double s21_exp(double x) {
  long double result = 1.0;
  long int index = 0;
  long double increment = 1.0;
  if (x > S21_DBL_MAX)
    result = INF_POS;
  else if (x < S21_DBL_MIN)
    result = POS_ZERO;
  else if ((x == POS_ZERO) || (x == NEG_ZERO) || (x == 0))
    result = 1.0;
  else if (x == 1)
    result = S21_E;
  else if (x < 0 && x > S21_DBL_MIN)
    result = 1.0 / s21_exp(-x);
  else {
    while (s21_fabs(increment) > S21_ECS / 100.0 && result != INF_POS) {
      index += 1;
      increment = increment * x / index;
      result += increment;
      if (result > S21_DBL_MAX) result = INF_POS;
    }
  }
  return result;
}