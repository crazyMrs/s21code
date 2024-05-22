#include "transformation.h"

int read_obj_file(char *filename, vertex *verts, polygon *poly) {
  int status = OK;
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    status = ERROR;
  } else {
    int all_points_in_poly = 0;
    initialize_data(verts, poly);
    char line[256];
    float maxAbsValue = 0.0f;
    find_min_max(file, &(verts->MinMax[0]), &maxAbsValue);
    float scaleFactor = (maxAbsValue > 1.0f) ? (1.0f / maxAbsValue) : 1.0f;
    float centerX = (verts->MinMax[0] + verts->MinMax[1]) / 2.0f;
    float centerY = (verts->MinMax[2] + verts->MinMax[3]) / 2.0f;
    float centerZ = (verts->MinMax[4] + verts->MinMax[5]) / 2.0f;
    fseek(file, 0, SEEK_SET);
    while (fgets(line, sizeof(line), file)) {
      if (line[0] == 'v' && line[1] == ' ') {
        process_vertex_line(verts, line, scaleFactor, centerX, centerY,
                            centerZ);
        search_MinMax(verts);
      } else if (line[0] == 'f' && line[1] == ' ') {
        int size_num_in_f;
        int *numbers_in_f =
            find_nums_in_f(&size_num_in_f, &line[0], verts->amount_vert);
        all_points_in_poly += 2 * size_num_in_f;
        poly->verts_in_poly += size_num_in_f;
        poly->amount_p += 1;
        poly->p = realloc(poly->p, all_points_in_poly * sizeof(int));
        poly_add_values(poly, numbers_in_f, all_points_in_poly, size_num_in_f);
        free(numbers_in_f);
      }
    }
    fclose(file);
  }
  return status;
}

void poly_add_values(polygon *poly, int *numbers_in_f, int all_points_in_poly,
                     int size_num_in_f) {
  poly->p[all_points_in_poly - size_num_in_f * 2] = numbers_in_f[0] - 1;
  int j = 1;
  for (int i = all_points_in_poly - size_num_in_f * 2 + 1;
       i < all_points_in_poly - 1; i++) {
    poly->p[i++] = numbers_in_f[j] - 1;
    poly->p[i] = numbers_in_f[j++] - 1;
  }
  poly->p[all_points_in_poly - 1] = numbers_in_f[0] - 1;
}

int *find_nums_in_f(int *size_num_in_f, char *line, int pointers_size) {
  int *p = NULL;
  *size_num_in_f = 0;
  for (int i = 0; line[i] != '\0'; i += 1) {
    int this_num_neg = 0;
    if (line[i] == '-') {
      this_num_neg = 1;
      i += 1;
    }
    if (is_num(line[i])) {
      *size_num_in_f += 1;
      p = (int *)realloc(p, *size_num_in_f * sizeof(int));
      p[*size_num_in_f - 1] = number_reading_module(line, &i);
      if (this_num_neg) {
        p[*size_num_in_f - 1] *= (-1);
        p[*size_num_in_f - 1] += pointers_size + 1;
      }
    }
  }
  return p;
}

int number_reading_module(char *line, int *i) {
  int result = 0;
  while (is_num(line[*i])) {
    result *= 10;
    result += (int)line[*i] - 48;
    *i += 1;
  }
  while (is_space(line[*i]) == 0 && line[*i] != '\0' && line[*i] != '\n') {
    *i += 1;
  }
  return result;
}

void initialize_data(vertex *verts, polygon *poly) {
  verts->amount_vert = 0;
  verts->points = NULL;
  verts->MinMax[0] = INFINITY;
  verts->MinMax[1] = -INFINITY;
  verts->MinMax[2] = INFINITY;
  verts->MinMax[3] = -INFINITY;
  verts->MinMax[4] = INFINITY;
  verts->MinMax[5] = -INFINITY;
  poly->p = NULL;
  poly->amount_p = 0;
  poly->verts_in_poly = 0;
}

void find_min_max(FILE *file, double *minMax, float *maxAbsValue) {
  char line[256];

  while (fgets(line, sizeof(line), file)) {
    if (line[0] == 'v' && line[1] == ' ') {
      double x = 0., y = 0., z = 0.;
      char str[2];
      sscanf(line, "%s %lf %lf %lf", str, &x, &y, &z);

      if (fabs(x) > *maxAbsValue)
        *maxAbsValue = fabs(x);
      if (fabs(y) > *maxAbsValue)
        *maxAbsValue = fabs(y);
      if (fabs(z) > *maxAbsValue)
        *maxAbsValue = fabs(z);

      if (x > minMax[1])
        minMax[1] = x;
      if (y > minMax[3])
        minMax[3] = y;
      if (z > minMax[5])
        minMax[5] = z;

      if (x < minMax[0])
        minMax[0] = x;
      if (y < minMax[2])
        minMax[2] = y;
      if (z < minMax[4])
        minMax[4] = z;
    }
  }
}

void process_vertex_line(vertex *verts, char *line, float scaleFactor,
                         float centerX, float centerY, float centerZ) {
  verts->amount_vert++;
  verts->points =
      realloc(verts->points, verts->amount_vert * 3 * sizeof(double));
  double x, y, z;
  sscanf(line, "v %lf %lf %lf\n", &x, &y, &z);
  verts->points[(verts->amount_vert - 1) * 3] = x;
  verts->points[(verts->amount_vert - 1) * 3 + 1] = y;
  verts->points[(verts->amount_vert - 1) * 3 + 2] = z;

  verts->points[(verts->amount_vert - 1) * 3] =
      (verts->points[(verts->amount_vert - 1) * 3] - centerX) * scaleFactor;
  verts->points[(verts->amount_vert - 1) * 3 + 1] =
      (verts->points[(verts->amount_vert - 1) * 3 + 1] - centerY) * scaleFactor;
  verts->points[(verts->amount_vert - 1) * 3 + 2] =
      (verts->points[(verts->amount_vert - 1) * 3 + 2] - centerZ) * scaleFactor;
}

void search_MinMax(vertex *verts) {
  for (int i = 0; i <= Z_AXIS; i++) {
    if (verts->points[(verts->amount_vert - 1) * 3 + i] <
        verts->MinMax[i * 2]) {
      verts->MinMax[i * 2] = verts->points[(verts->amount_vert - 1) * 3 + i];
    } else if (verts->points[(verts->amount_vert - 1) * 3 + i] >
               verts->MinMax[i * 2 + 1]) {
      verts->MinMax[i * 2 + 1] =
          verts->points[(verts->amount_vert - 1) * 3 + i];
    }
  }
}

int is_space(char ch) { return ch == ' '; }
int is_num(char ch) { return ch <= '9' && ch >= '0'; }

void axis_scale(vertex *v, double result_scale) {
  if (result_scale != 0.) {
    for (unsigned int i = 0; i < v->amount_vert * 3; i++) {
      v->points[i] *= result_scale;
    }
  }
}

void axis_moving(vertex *v, int axis_num, double prev_value, double value) {
  value -= prev_value;
  for (unsigned int i = 0; i < v->amount_vert; i++) {
    v->points[i * 3 + axis_num] += value;
  }
}

void axis_turn_oX(vertex *v, double a) {
  a = a * S21_PI / 180.;
  for (unsigned int i = 0; i < v->amount_vert; i++) {
    double newY =
        v->points[i * 3 + Y_AXIS] * cos(a) + v->points[i * 3 + Z_AXIS] * sin(a);
    v->points[i * 3 + Z_AXIS] = -v->points[i * 3 + Y_AXIS] * sin(a) +
                                v->points[i * 3 + Z_AXIS] * cos(a);
    v->points[i * 3 + Y_AXIS] = newY;
  }
}

void axis_turn_oY(vertex *v, double a) {
  a = a * S21_PI / 180.;
  for (unsigned int i = 0; i < v->amount_vert; i++) {
    double newX =
        v->points[i * 3 + X_AXIS] * cos(a) + v->points[i * 3 + Z_AXIS] * sin(a);
    v->points[i * 3 + Z_AXIS] = -v->points[i * 3 + X_AXIS] * sin(a) +
                                v->points[i * 3 + Z_AXIS] * cos(a);
    v->points[i * 3 + X_AXIS] = newX;
  }
}

void axis_turn_oZ(vertex *v, double a) {
  a = a * S21_PI / 180.;
  for (unsigned int i = 0; i < v->amount_vert; i++) {
    double newX =
        v->points[i * 3 + X_AXIS] * cos(a) + v->points[i * 3 + Y_AXIS] * sin(a);
    double newY = -v->points[i * 3 + X_AXIS] * sin(a) +
                  v->points[i * 3 + Y_AXIS] * cos(a);
    v->points[i * 3 + X_AXIS] = newX;
    v->points[i * 3 + Y_AXIS] = newY;
  }
}
