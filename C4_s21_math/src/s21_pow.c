#include "s21_math.h"

long double s21_pow(double base,
                    double exp) {  //возводит число в заданную степень
  long double result = 0;
  int sign_base = 0;
  if (!exp) {
    result = 1;
  } else if (base == INF_NEG && exp == INF_NEG) {
    result = 0;
  } else if (base == INF_NEG && exp == INF_POS) {
    result = INF_POS;
  } else if (base < 0 && exp != (long long int)exp) {
    result = S_NAN;
  } else {
    sign_base = base < 0 ? -1 : 1;
    result = s21_exp(exp * s21_log(base * sign_base));
    if (s21_fmod(exp, 2)) {  //если exp не является целым числом
      result *= sign_base;
    }
  }
  return result;
}
