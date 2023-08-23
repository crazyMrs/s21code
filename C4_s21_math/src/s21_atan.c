#include "s21_math.h"

long double s21_atan(double x) {
  long double res = 0.0;
  if (x != x) {
    res = S_NAN;

  } else if (((x > -1) || (x < 1)) && x != 0 && x != INF_POS && x != INF_NEG) {
    long double y = x / (1 + s21_sqrt(1 + s21_pow(x, 2)));
    for (long double k = 0; k < 1000000; k++) {
      long double delta =
          s21_pow(-1, k) * s21_pow(y, (1 + 2 * k)) / (1 + 2 * k);
      res += delta;
      if (s21_fabs(delta) < S21_ECS) break;
    }
    res *= 2.0;

  } else if (((x < -1.0) || (x > 1.0)) && x != 0 && x != INF_POS &&
             x != INF_NEG) {
  } else if (x == 0 && x != INF_POS && x != INF_NEG) {
    res = 0.0;

  } else if (x == INF_NEG && x != INF_POS) {
    res = -S21_PI / 2.0;

  } else if (x != INF_NEG && x == INF_POS) {
    res = S21_PI / 2.0;
  }
  return res;
}
