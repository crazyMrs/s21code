#include <check.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "s21_math.h"

// CEIL
START_TEST(s21_ceil_test1) {
  ck_assert_double_eq_tol(s21_ceil(-0.3), ceil(-0.3), 0.000001);
}
END_TEST

START_TEST(s21_ceil_test2) {
  ck_assert_double_eq_tol(s21_ceil(-318.6), ceil(-318.6), 0.000001);
}
END_TEST

START_TEST(s21_ceil_test3) {
  ck_assert_double_eq_tol(s21_ceil(80), ceil(80), 0.000001);
}
END_TEST

START_TEST(s21_ceil_test4) {
  ck_assert_double_nan(s21_ceil(NAN));
  ck_assert_double_nan(ceil(NAN));
}
END_TEST

START_TEST(s21_ceil_test5) {
  ck_assert_double_eq(s21_ceil(INFINITY), ceil(INFINITY));
}
END_TEST

Suite *ceil_suite(void) {
  Suite *s = suite_create("ceil(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_ceil_test1);
  tcase_add_test(tc_core, s21_ceil_test2);
  tcase_add_test(tc_core, s21_ceil_test3);
  tcase_add_test(tc_core, s21_ceil_test4);
  tcase_add_test(tc_core, s21_ceil_test5);
  suite_add_tcase(s, tc_core);
  return s;
}

// SQRT

START_TEST(s21_sqrt_test1) {
  for (double a = -1500; a < 1500; a += 123) {
    for (double b = -12; b < 12; b += 1.25) {
      ck_assert_double_eq(fmod(a, b), s21_fmod(a, b));
      ck_assert_double_eq(fmod(b, a), s21_fmod(b, a));
    }
  }
}
END_TEST

START_TEST(s21_sqrt_test2) {
  ck_assert_double_nan(s21_sqrt(-0.03));
  ck_assert_double_nan(sqrt(-0.03));
}
END_TEST

START_TEST(s21_sqrt_test3) {
  ck_assert_double_nan(s21_sqrt(NAN));
  ck_assert_double_nan(sqrt(NAN));
}
END_TEST

START_TEST(s21_sqrt_test4) {
  ck_assert_double_nan(s21_sqrt(-INFINITY));
  ck_assert_double_nan(sqrt(-INFINITY));
}
END_TEST

START_TEST(s21_sqrt_test5) {
  ck_assert_double_eq(s21_sqrt(INFINITY), sqrt(INFINITY));
}
END_TEST

Suite *sqrt_suite(void) {
  Suite *s = suite_create("sqrt(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_sqrt_test1);
  tcase_add_test(tc_core, s21_sqrt_test2);
  tcase_add_test(tc_core, s21_sqrt_test3);
  tcase_add_test(tc_core, s21_sqrt_test4);
  tcase_add_test(tc_core, s21_sqrt_test5);
  suite_add_tcase(s, tc_core);
  return s;
}

// FLOOR

START_TEST(s21_floor_test1) {
  ck_assert_double_eq_tol(s21_floor(-18.6), floor(-18.6), 0.000001);
}
END_TEST

START_TEST(s21_floor_test2) {
  ck_assert_double_eq_tol(s21_floor(0.6), floor(0.6), 0.000001);
}
END_TEST

START_TEST(s21_floor_test3) {
  ck_assert_double_nan(s21_floor(NAN));
  ck_assert_double_nan(floor(NAN));
}
END_TEST

START_TEST(s21_floor_test4) {
  ck_assert_double_eq(s21_floor(INFINITY), floor(INFINITY));
}
END_TEST

START_TEST(s21_floor_test5) {
  ck_assert_double_eq(s21_floor(-INFINITY), floor(-INFINITY));
}
END_TEST

Suite *floor_suite(void) {
  Suite *s = suite_create("floor(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_floor_test1);
  tcase_add_test(tc_core, s21_floor_test2);
  tcase_add_test(tc_core, s21_floor_test3);
  tcase_add_test(tc_core, s21_floor_test4);
  tcase_add_test(tc_core, s21_floor_test5);
  suite_add_tcase(s, tc_core);
  return s;
}

// FMOD

START_TEST(s21_fmod_test1) {
  ck_assert_double_nan(s21_fmod(NAN, NAN));
  ck_assert_double_nan(fmod(NAN, NAN));
  ck_assert_double_nan(s21_fmod(NAN, INFINITY));
  ck_assert_double_nan(fmod(NAN, INFINITY));
  ck_assert_double_nan(s21_fmod(NAN, -INFINITY));
  ck_assert_double_nan(fmod(NAN, -INFINITY));
  ck_assert_double_nan(s21_fmod(-INFINITY, NAN));
  ck_assert_double_nan(fmod(-INFINITY, NAN));
  ck_assert_double_nan(s21_fmod(INFINITY, NAN));
  ck_assert_double_nan(fmod(INFINITY, NAN));
  ck_assert_double_nan(s21_fmod(INFINITY, -INFINITY));
  ck_assert_double_nan(fmod(INFINITY, -INFINITY));
  ck_assert_double_nan(s21_fmod(INFINITY, 2));
  ck_assert_double_nan(fmod(INFINITY, 2));
  ck_assert_double_nan(s21_fmod(-INFINITY, -1));
  ck_assert_double_nan(fmod(-INFINITY, -1));
  ck_assert_double_nan(s21_fmod(NAN, 3));
  ck_assert_double_nan(fmod(NAN, 3));
  ck_assert_double_eq(fmod(0, -1), s21_fmod(0, -1));
  ck_assert_double_eq(fmod(0, 1), s21_fmod(0, 1));
}
END_TEST

START_TEST(s21_fmod_test2) {
  ck_assert_double_eq(s21_fmod(0, INFINITY), fmod(0, INFINITY));
  ck_assert_double_eq(s21_fmod(90, -INFINITY), fmod(90, -INFINITY));
}
END_TEST

START_TEST(s21_fmod_test3) {
  for (double a = -1500; a < 1500; a += 123) {
    for (double b = -12; b < 12; b += 1.25) {
      ck_assert_double_eq(fmod(a, b), s21_fmod(a, b));
      ck_assert_double_eq(fmod(b, a), s21_fmod(b, a));
    }
  }
}
END_TEST

Suite *fmod_suite(void) {
  Suite *s = suite_create("fmod(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_fmod_test1);
  tcase_add_test(tc_core, s21_fmod_test2);
  tcase_add_test(tc_core, s21_fmod_test3);
  suite_add_tcase(s, tc_core);
  return s;
}

// COS

START_TEST(s21_cos_test1) {
  ck_assert_double_nan(s21_cos(NAN));
  ck_assert_double_nan(cos(NAN));
}
END_TEST

START_TEST(s21_cos_test3) {
  ck_assert_double_nan(s21_cos(INFINITY));
  ck_assert_double_nan(cos(INFINITY));
}
END_TEST

START_TEST(s21_cos_test4) {
  ck_assert_double_nan(s21_cos(-INFINITY));
  ck_assert_double_nan(cos(-INFINITY));
}
END_TEST

START_TEST(s21_cos_test2) {
  ck_assert_double_eq_tol(s21_cos(15000), cos(15000), 0.000001);
  ck_assert_double_eq_tol(s21_cos(-13.57), cos(-13.57), 0.000001);
  ck_assert_double_eq_tol(s21_cos(0), cos(0), 0.000001);
  ck_assert_double_eq_tol(s21_cos(-1), cos(-1), 0.000001);
  ck_assert_double_eq_tol(s21_cos(M_PI_2), cos(M_PI_2), 0.000001);
  ck_assert_double_eq_tol(s21_cos(-M_PI_2), cos(-M_PI_2), 0.000001);
  ck_assert_double_eq_tol(s21_cos(M_PI), cos(M_PI), 0.000001);
}
END_TEST

Suite *cos_suite(void) {
  Suite *s = suite_create("cos(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_cos_test1);
  tcase_add_test(tc_core, s21_cos_test2);
  tcase_add_test(tc_core, s21_cos_test3);
  tcase_add_test(tc_core, s21_cos_test4);
  suite_add_tcase(s, tc_core);
  return s;
}

// SIN

START_TEST(s21_sin_test1) {
  ck_assert_double_nan(s21_sin(NAN));
  ck_assert_double_nan(sin(NAN));
}
END_TEST

START_TEST(s21_sin_test3) {
  ck_assert_double_nan(s21_sin(INFINITY));
  ck_assert_double_nan(sin(INFINITY));
}
END_TEST

START_TEST(s21_sin_test4) {
  ck_assert_double_nan(s21_sin(-INFINITY));
  ck_assert_double_nan(sin(-INFINITY));
}
END_TEST

START_TEST(s21_sin_test2) {
  ck_assert_double_eq_tol(s21_sin(-14.96), sin(-14.96), 0.000001);
  ck_assert_double_eq_tol(s21_sin(100000), sin(100000), 0.000001);
  ck_assert_double_eq_tol(s21_sin(-10000), sin(-10000), 0.000001);
  ck_assert_double_eq_tol(s21_sin(0), sin(0), 0.000001);
  ck_assert_double_eq_tol(s21_sin(-1), sin(-1), 0.000001);
  ck_assert_double_eq_tol(s21_sin(1), sin(1), 0.000001);
  ck_assert_double_eq_tol(s21_sin(M_PI_2), sin(M_PI_2), 0.000001);
  ck_assert_double_eq_tol(s21_sin(-M_PI_2), sin(-M_PI_2), 0.000001);
  ck_assert_double_eq_tol(s21_sin(M_PI), sin(M_PI), 0.000001);
}
END_TEST

Suite *sin_suite(void) {
  Suite *s = suite_create("sin(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_sin_test1);
  tcase_add_test(tc_core, s21_sin_test2);
  tcase_add_test(tc_core, s21_sin_test3);
  tcase_add_test(tc_core, s21_sin_test4);
  suite_add_tcase(s, tc_core);
  return s;
}

// ABS

START_TEST(s21_abs_test1) {
  ck_assert_int_eq(s21_abs((int)INFINITY), abs((int)INFINITY));
  ck_assert_int_eq(s21_abs((int)-INFINITY), abs((int)-INFINITY));
  ck_assert_int_eq(s21_abs((int)NAN), abs((int)NAN));
}
END_TEST

START_TEST(s21_abs_test2) {
  for (int a = -1500; a < 1500; a += 123) {
    ck_assert_double_eq(abs((int)a), s21_abs((int)a));
  }
}
END_TEST

Suite *abs_suite(void) {
  Suite *s = suite_create("abs(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_abs_test1);
  tcase_add_test(tc_core, s21_abs_test2);
  suite_add_tcase(s, tc_core);
  return s;
}

// FABS

START_TEST(s21_fabs_test1) {
  ck_assert_double_eq_tol(s21_fabs(234.34), fabs(234.34), 0.000001);
  ck_assert_double_eq_tol(s21_fabs(-6949.45), fabs(-6949.45), 0.000001);
  ck_assert_double_eq_tol(s21_fabs(150555.42), fabs(150555.42), 0.000001);
  ck_assert_double_eq(s21_fabs(INFINITY), fabs(INFINITY));
  ck_assert_double_eq(s21_fabs(-INFINITY), fabs(-INFINITY));
  ck_assert_double_nan(s21_fabs(NAN));
  ck_assert_double_nan(fabs(NAN));
}
END_TEST

START_TEST(s21_fabs_test2) {
  for (double a = -5500.00; a < 5500.00; a++) {
    ck_assert_double_eq_tol(s21_fabs(a), fabs(a), 0.000001);
  }
}
END_TEST

Suite *fabs_suite(void) {
  Suite *s = suite_create("fabs(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_fabs_test1);
  tcase_add_test(tc_core, s21_fabs_test2);
  suite_add_tcase(s, tc_core);
  return s;
}

// ATAN

START_TEST(s21_atan_test1) {
  ck_assert_ldouble_eq_tol(s21_atan(0), atan(0), 0.000001);
  ck_assert_ldouble_eq_tol(s21_atan(1.0), atan(1.0), 0.000001);
  ck_assert_ldouble_eq_tol(s21_atan(-1.0), atan(-1.0), 0.000001);
  ck_assert_ldouble_eq_tol(s21_atan(-0.5), atan(-0.5), 0.000001);
  ck_assert_ldouble_eq_tol(s21_atan(0.7), atan(0.7), 0.000001);
  ck_assert_ldouble_eq_tol(s21_atan(-6.45), atan(-6.45), 0.000001);
  ck_assert_ldouble_eq_tol(s21_atan(15.42), atan(15.42), 0.000001);
}
END_TEST

START_TEST(s21_atan_test2) {
  ck_assert_double_eq(s21_atan(INFINITY), atan(INFINITY));
  ck_assert_double_eq(s21_atan(-INFINITY), atan(-INFINITY));
}
END_TEST

START_TEST(s21_atan_test3) {
  ck_assert_double_nan(s21_atan(NAN));
  ck_assert_double_nan(atan(NAN));
}
END_TEST

Suite *atan_suite(void) {
  Suite *s = suite_create("atan(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_atan_test1);
  tcase_add_test(tc_core, s21_atan_test2);
  tcase_add_test(tc_core, s21_atan_test3);
  suite_add_tcase(s, tc_core);
  return s;
}

// POW

START_TEST(s21_pow_test1) {
  ck_assert_double_eq(s21_pow(-INFINITY, -INFINITY), pow(-INFINITY, -INFINITY));
  ck_assert_double_eq(s21_pow(-INFINITY, INFINITY), pow(-INFINITY, INFINITY));
  ck_assert_double_eq(s21_pow(INFINITY, -INFINITY), pow(INFINITY, -INFINITY));
  ck_assert_double_eq(s21_pow(INFINITY, INFINITY), pow(INFINITY, INFINITY));
}
END_TEST

START_TEST(s21_pow_test2) {
  ck_assert_double_nan(s21_pow(-INFINITY, NAN));
  ck_assert_double_nan(pow(-INFINITY, NAN));
}
END_TEST

START_TEST(s21_pow_test3) {
  ck_assert_double_eq_tol(s21_pow(20, 0.4), pow(20, 0.4), 0.000001);
  ck_assert_double_eq_tol(s21_pow(-20.63, 3), pow(-20.63, 3), 0.000001);
  ck_assert_double_eq_tol(s21_pow(-20.63, 6), pow(-20.63, 6), 0.000001);
  ck_assert_ldouble_eq_tol(s21_pow(1, 2), pow(1, 2), 0.000001);
  ck_assert_ldouble_eq_tol(s21_pow(1, -2), pow(1, -2), 0.000001);
  ck_assert_ldouble_eq_tol(s21_pow(S21_PI / 2, 10), pow(S21_PI / 2, 10),
                           0.000001);
  ck_assert_ldouble_eq_tol(s21_pow(138.7, 20.5e-34), pow(138.7, 20.5e-34),
                           0.000001);
  ck_assert_ldouble_eq_tol(s21_pow(555.55, -34), pow(555.55, -34), 0.000001);
  ck_assert_ldouble_eq_tol(s21_pow(-10.0, -3.0), pow(-10.0, -3.0), 0.000001);
}
END_TEST

Suite *pow_suite(void) {
  Suite *s = suite_create("pow(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_pow_test1);
  tcase_add_test(tc_core, s21_pow_test2);
  tcase_add_test(tc_core, s21_pow_test3);
  suite_add_tcase(s, tc_core);
  return s;
}

// ASIN

START_TEST(s21_asin_test1) {
  ck_assert_double_nan(s21_asin(NAN));
  ck_assert_double_nan(asin(NAN));
}
END_TEST

START_TEST(s21_asin_test3) {
  ck_assert_double_nan(s21_asin(INFINITY));
  ck_assert_double_nan(asin(INFINITY));
}
END_TEST

START_TEST(s21_asin_test4) {
  ck_assert_double_nan(s21_asin(-INFINITY));
  ck_assert_double_nan(asin(-INFINITY));
}
END_TEST

START_TEST(s21_asin_test5) {
  ck_assert_double_nan(s21_asin(-14));
  ck_assert_double_nan(asin(-14));
}
END_TEST

START_TEST(s21_asin_test6) {
  ck_assert_double_nan(s21_asin(14));
  ck_assert_double_nan(asin(14));
}
END_TEST

START_TEST(s21_asin_test2) {
  ck_assert_double_eq_tol(s21_asin(0), asin(0), 0.000001);
  ck_assert_double_eq_tol(s21_asin(-1), asin(-1), 0.000001);
  ck_assert_double_eq_tol(s21_asin(1), asin(1), 0.000001);
}
END_TEST

Suite *asin_suite(void) {
  Suite *s = suite_create("asin(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_asin_test1);
  tcase_add_test(tc_core, s21_asin_test2);
  tcase_add_test(tc_core, s21_asin_test3);
  tcase_add_test(tc_core, s21_asin_test4);
  tcase_add_test(tc_core, s21_asin_test5);
  tcase_add_test(tc_core, s21_asin_test6);
  suite_add_tcase(s, tc_core);
  return s;
}

// ACOS
START_TEST(s21_acos_test1) {
  ck_assert_double_eq_tol(s21_acos(0), acos(0), 0.000001);
}
END_TEST

START_TEST(s21_acos_test2) {
  ck_assert_double_eq_tol(s21_acos(-1), acos(-1), 0.000001);
}
END_TEST

START_TEST(s21_acos_test3) {
  ck_assert_double_eq_tol(s21_acos(1), acos(1), 0.000001);
}
END_TEST

START_TEST(s21_acos_test7) {
  ck_assert_double_nan(s21_acos(NAN));
  ck_assert_double_nan(acos(NAN));
}
END_TEST

START_TEST(s21_acos_test8) {
  ck_assert_double_nan(s21_acos(INFINITY));
  ck_assert_double_nan(acos(INFINITY));
}
END_TEST

START_TEST(s21_acos_test4) {
  ck_assert_double_nan(s21_acos(-INFINITY));
  ck_assert_double_nan(acos(-INFINITY));
}
END_TEST

START_TEST(s21_acos_test5) {
  ck_assert_double_nan(s21_acos(-14));
  ck_assert_double_nan(acos(-14));
}
END_TEST

START_TEST(s21_acos_test6) {
  ck_assert_double_nan(s21_acos(14));
  ck_assert_double_nan(acos(14));
}
END_TEST

Suite *acos_suite(void) {
  Suite *s = suite_create("acos(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_acos_test1);
  tcase_add_test(tc_core, s21_acos_test2);
  tcase_add_test(tc_core, s21_acos_test3);
  tcase_add_test(tc_core, s21_acos_test4);
  tcase_add_test(tc_core, s21_acos_test5);
  tcase_add_test(tc_core, s21_acos_test6);
  tcase_add_test(tc_core, s21_acos_test7);
  tcase_add_test(tc_core, s21_acos_test8);
  suite_add_tcase(s, tc_core);
  return s;
}

// TAN

START_TEST(s21_tan_test1) {
  ck_assert_double_nan(s21_tan(NAN));
  ck_assert_double_nan(tan(NAN));
}
END_TEST

START_TEST(s21_tan_test3) {
  ck_assert_double_nan(s21_tan(INFINITY));
  ck_assert_double_nan(tan(INFINITY));
}
END_TEST

START_TEST(s21_tan_test4) {
  ck_assert_double_nan(s21_tan(-INFINITY));
  ck_assert_double_nan(tan(-INFINITY));
}
END_TEST

START_TEST(s21_tan_test2) {
  ck_assert_ldouble_eq_tol(s21_tan(94703), tan(94703), 0.000001);
  ck_assert_ldouble_eq_tol(s21_tan(-15), tan(-15), 0.000001);
  ck_assert_ldouble_eq_tol(s21_tan(100000), tan(100000), 0.000001);
  ck_assert_ldouble_eq_tol(s21_tan(0), tan(0), 0.000001);
  ck_assert_ldouble_eq_tol(s21_tan(-1), tan(-1), 0.000001);
  ck_assert_ldouble_eq_tol(s21_tan(1), tan(1), 0.000001);
  ck_assert_ldouble_eq_tol(s21_tan(M_PI), tan(M_PI), 0.000001);
}
END_TEST

Suite *tan_suite(void) {
  Suite *s = suite_create("tan(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_tan_test1);
  tcase_add_test(tc_core, s21_tan_test2);
  tcase_add_test(tc_core, s21_tan_test3);
  tcase_add_test(tc_core, s21_tan_test4);
  suite_add_tcase(s, tc_core);
  return s;
}

// LOG

START_TEST(s21_log_test1) {
  ck_assert_double_nan(s21_log(NAN));
  ck_assert_double_nan(log(NAN));
}
END_TEST

START_TEST(s21_log_test3) { ck_assert_ldouble_infinite(s21_log(INFINITY)); }
END_TEST

START_TEST(s21_log_test4) {
  ck_assert_double_nan(s21_log(-INFINITY));
  ck_assert_double_nan(log(-INFINITY));
}
END_TEST

START_TEST(s21_log_test2) {
  ck_assert_ldouble_eq_tol(s21_log(94703.44), log(94703.44), 0.000001);
}
END_TEST

START_TEST(s21_log_test5) { ck_assert_ldouble_nan(s21_log(-13.5)); }
END_TEST

START_TEST(s21_log_test6) {
  ck_assert_double_eq(s21_log(0), log(0));
  ck_assert_double_eq(s21_log(1.0), log(1.0));
  ck_assert_ldouble_nan(s21_log(-1));
}
END_TEST

Suite *log_suite(void) {
  Suite *s = suite_create("log(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_log_test1);
  tcase_add_test(tc_core, s21_log_test2);
  tcase_add_test(tc_core, s21_log_test3);
  tcase_add_test(tc_core, s21_log_test4);
  tcase_add_test(tc_core, s21_log_test5);
  tcase_add_test(tc_core, s21_log_test6);
  suite_add_tcase(s, tc_core);
  return s;
}

// EXP

START_TEST(s21_exp_test1) {
  ck_assert_double_nan(s21_exp(NAN));
  ck_assert_double_nan(exp(NAN));
}
END_TEST

START_TEST(s21_exp_test3) {
  ck_assert_ldouble_eq(exp(INFINITY), s21_exp(INFINITY));
  ck_assert_ldouble_eq(exp(-INFINITY), s21_exp(-INFINITY));
}
END_TEST

START_TEST(s21_exp_test2) {
  ck_assert_ldouble_eq_tol(s21_exp(-18.3427), exp(-18.3427), 0.000001);
}
END_TEST

START_TEST(s21_exp_test5) {
  ck_assert_ldouble_eq_tol(s21_exp(-13.5), exp(-13.5), 0.000001);
}
END_TEST

START_TEST(s21_exp_test6) {
  ck_assert_double_eq(s21_exp(0), exp(0));
  ck_assert_double_eq(s21_exp(1), exp(1));
  ck_assert_double_eq(s21_exp(-1), exp(-1));
}
END_TEST

Suite *exp_suite(void) {
  Suite *s = suite_create("exp(x)");
  TCase *tc_core = tcase_create("core");
  tcase_add_test(tc_core, s21_exp_test1);
  tcase_add_test(tc_core, s21_exp_test2);
  tcase_add_test(tc_core, s21_exp_test3);
  tcase_add_test(tc_core, s21_exp_test5);
  tcase_add_test(tc_core, s21_exp_test6);
  suite_add_tcase(s, tc_core);
  return s;
}

//Запуск тестов

void case_test(Suite *s, int *error) {
  SRunner *suite_runner = srunner_create(s);
  srunner_run_all(suite_runner, CK_NORMAL);
  *error = srunner_ntests_failed(suite_runner);
  srunner_free(suite_runner);
}

int main() {
  int error = 0;
  case_test(abs_suite(), &error);
  case_test(acos_suite(), &error);
  case_test(asin_suite(), &error);
  case_test(atan_suite(), &error);
  case_test(ceil_suite(), &error);
  case_test(cos_suite(), &error);
  case_test(exp_suite(), &error);
  case_test(fabs_suite(), &error);
  case_test(floor_suite(), &error);
  case_test(fmod_suite(), &error);
  case_test(log_suite(), &error);
  case_test(pow_suite(), &error);
  case_test(sin_suite(), &error);
  case_test(sqrt_suite(), &error);
  case_test(tan_suite(), &error);
  return error;
}