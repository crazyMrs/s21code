#include "s21_math.h"

long double s21_log(double x) {
  long double num_iteration = 100.0;
  long double res_s21_log = 0.0;

  if (x == 0)
    return INF_NEG;
  else if (x != INF_NEG && x != INF_POS && x != S_NAN && x > 0.0) {
    for (long double i = 0; i < num_iteration; i++) {
      long double delta =
          2 * (x - s21_exp(res_s21_log)) / (x + s21_exp(res_s21_log));
      res_s21_log += delta;
    }
  } else if (x == INF_NEG) {
    res_s21_log = S_NAN;
  } else if (x == INF_POS) {
    res_s21_log = INF_POS;
  } else if (x == S_NAN) {
    res_s21_log = S_NAN;
  } else {
    res_s21_log = S_NAN;
  }
  return res_s21_log;
}