#include <check.h>

#include "transformation.h"

START_TEST(variant_1) {
  char *filename = "obj_files/cube.obj";
  vertex v;
  polygon p;
  double v_true_arr[] = {-1, -1, 1,  1, -1, 1,  1, 1, 1,  -1, 1, 1,
                         -1, -1, -1, 1, -1, -1, 1, 1, -1, -1, 1, -1};
  read_obj_file(filename, &v, &p);
  for (unsigned int i = 0; i < v.amount_vert * 3; i++) {
    ck_assert_double_eq_tol(v.points[i], v_true_arr[i], 1e-7);
  }
  free(v.points);
  free(p.p);
}
END_TEST

START_TEST(variant_1_rotationX) {
  char *filename = "obj_files/cube.obj";
  vertex v;
  polygon p;
  double a = 30.;
  double v_true_arr[] = {-1, -0.366025, 1.366025,  1,  -0.366025, 1.366025,
                         1,  1.366025,  0.366025,  -1, 1.366025,  0.366025,
                         -1, -1.366025, -0.366025, 1,  -1.366025, -0.366025,
                         1,  0.366025,  -1.366025, -1, 0.366025,  -1.366025};
  read_obj_file(filename, &v, &p);
  axis_turn_oX(&v, a);
  for (unsigned int i = 0; i < v.amount_vert * 3; i++) {
    ck_assert_double_eq_tol(v.points[i], v_true_arr[i], 1e-6);
  }
  free(v.points);
  free(p.p);
}
END_TEST

START_TEST(variant_2_rotationY) {
  char *filename = "obj_files/cube.obj";
  vertex v;
  polygon p;
  double a = 90.;
  double v_true_arr[] = {1,  -1, 1, 1,  -1, -1, 1,  1, -1, 1,  1, 1,
                         -1, -1, 1, -1, -1, -1, -1, 1, -1, -1, 1, 1};
  read_obj_file(filename, &v, &p);
  axis_turn_oY(&v, a);
  for (unsigned int i = 0; i < v.amount_vert * 3; i++) {
    ck_assert_double_eq_tol(v.points[i], v_true_arr[i], 1e-7);
  }
  free(v.points);
  free(p.p);
}
END_TEST

START_TEST(variant_3_rotationZ) {
  char *filename = "obj_files/cube.obj";
  vertex v;
  polygon p;
  double a = 50.;
  double v_true_arr[] = {-1.408832, 0.123257,  1,  -0.123257, -1.408832, 1,
                         1.408832,  -0.123257, 1,  0.123257,  1.408832,  1,
                         -1.408832, 0.123257,  -1, -0.123257, -1.408832, -1,
                         1.408832,  -0.123257, -1, 0.123257,  1.408832,  -1};
  read_obj_file(filename, &v, &p);
  axis_turn_oZ(&v, a);
  for (unsigned int i = 0; i < v.amount_vert * 3; i++) {
    ck_assert_double_eq_tol(v.points[i], v_true_arr[i], 1e-6);
  }
  free(v.points);
  free(p.p);
}
END_TEST

START_TEST(test_scale) {
  char *filename = "obj_files/cube.obj";
  vertex v;
  polygon p;
  double v_true_arr[] = {-1, -1, 1,  1, -1, 1,  1, 1, 1,  -1, 1, 1,
                         -1, -1, -1, 1, -1, -1, 1, 1, -1, -1, 1, -1};
  read_obj_file(filename, &v, &p);
  int scale_add_coef = 1;
  axis_scale(&v, scale_add_coef);
  for (unsigned int i = 0; i < 3; i++) {
    ck_assert_double_eq_tol(v.points[i], v_true_arr[i], 1e-6);
  }
  free(v.points);
  free(p.p);
}
END_TEST

START_TEST(variant_amount_verts_1) {
  char *filename = "obj_files/cube.obj";
  vertex v;
  polygon p;
  int true_amount_vert = 8;
  read_obj_file(filename, &v, &p);
  ck_assert_int_eq(v.amount_vert, true_amount_vert);
  free(v.points);
  free(p.p);
}
END_TEST

START_TEST(variant_amount_verts_2) {
  char *filename = "obj_files/Shrek.obj";
  vertex v;
  polygon p;
  int true_amount_vert = 1274;
  read_obj_file(filename, &v, &p);
  ck_assert_int_eq(v.amount_vert, true_amount_vert);
  free(v.points);
  free(p.p);
}
END_TEST

START_TEST(variant_amount_verts_3) {
  char *filename = "obj_files/female2a.obj";
  vertex v;
  polygon p;
  int true_amount_vert = 62338;
  read_obj_file(filename, &v, &p);
  ck_assert_int_eq(v.amount_vert, true_amount_vert);
  free(v.points);
  free(p.p);
}
END_TEST

START_TEST(test_points_in_poly) {
  char *filename = "obj_files/cube.obj";
  vertex v;
  polygon p;
  int true_verts_in_poly = 36;
  read_obj_file(filename, &v, &p);
  ck_assert_int_eq(p.verts_in_poly, true_verts_in_poly);
  free(v.points);
  free(p.p);
}
END_TEST

START_TEST(test_translate) {
  char *filename = "obj_files/cube.obj";
  vertex v;
  polygon p;
  double v_true_arr[] = {-0.9, -1, 1,  1.1, -1, 1,  1.1, 1, 1,  -0.9, 1, 1,
                         -0.9, -1, -1, 1.1, -1, -1, 1.1, 1, -1, -0.9, 1, -1};
  read_obj_file(filename, &v, &p);
  axis_moving(&v, X_AXIS, 0, 0.1);
  for (unsigned int i = 0; i < v.amount_vert * 3; i++) {
    ck_assert_double_eq_tol(v.points[i], v_true_arr[i], 1e-7);
  }
  free(v.points);
  free(p.p);
}
END_TEST

START_TEST(error_incorrect_filename) {
  char *filename = "madagascar";
  vertex v;
  polygon p;
  int status = OK;
  status = read_obj_file(filename, &v, &p);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

START_TEST(error_filename_NULL) {
  char *filename = NULL;
  vertex v;
  polygon p;
  int status = OK;
  status = read_obj_file(filename, &v, &p);
  ck_assert_int_eq(status, ERROR);
}
END_TEST

void calculation_tests(TCase *tc1_1) {
  tcase_add_test(tc1_1, variant_1);
  tcase_add_test(tc1_1, variant_1_rotationX);
  tcase_add_test(tc1_1, variant_2_rotationY);
  tcase_add_test(tc1_1, variant_3_rotationZ);
  tcase_add_test(tc1_1, variant_amount_verts_1);
  tcase_add_test(tc1_1, variant_amount_verts_2);
  tcase_add_test(tc1_1, variant_amount_verts_3);
  tcase_add_test(tc1_1, test_points_in_poly);
  tcase_add_test(tc1_1, error_incorrect_filename);
  tcase_add_test(tc1_1, error_filename_NULL);
  tcase_add_test(tc1_1, test_scale);
  tcase_add_test(tc1_1, test_translate);
}

int main() {
  Suite *s1 = suite_create("s21_viewer: ");
  TCase *tc1_1 = tcase_create("s21_viewer: ");
  SRunner *sr = srunner_create(s1);
  int nf;
  suite_add_tcase(s1, tc1_1);
  calculation_tests(tc1_1);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);
  return nf == 0 ? 0 : 1;
}
