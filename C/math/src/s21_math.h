#ifndef S21_MATH_H
#define S21_MATH_H
#include <float.h>
#include <limits.h>
#include <stdio.h>

#define S21_PI 3.14159265358979323846
#define S_NAN 0.0 / 0.0
#define INF_POS 1.0 / 0.0
#define INF_NEG -1.0 / 0.0
#define S21_NAN(x) (x != x)
#define S21_INF(x) (x == INF_NEG || x == INF_POS)
#define S21_ECS 1e-16
#define POS_ZERO +0.0
#define NEG_ZERO -0.0
#define S21_DBL_MAX 1.7976931348623157E+308
#define S21_DBL_MIN -1.7976931348623157E+308
#define S21_E 2.718281828459045235360287471350

long double s21_ceil(double x);
long double s21_sqrt(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_pow(double base, double exp);
long double s21_atan(double x);
long double s21_asin(double x);
long double s21_acos(double x);
long double s21_cos(double x);
long double s21_sin(double x);
long double s21_tan(double x);
int s21_abs(int x);
long double s21_fabs(double x);
long double s21_log(double x);
long double s21_exp(double x);
long double s21_pow_1(double base, long long int exp);

#endif  // S21_MATH_H
