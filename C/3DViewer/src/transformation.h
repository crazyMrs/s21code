#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_PI 3.14159265358979323846

enum status { OK, ERROR };

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2

typedef struct {
  unsigned int amount_vert;
  double *points;
  double MinMax[6];
} vertex;

typedef struct {
  int *p;
  int amount_p;
  int verts_in_poly;
} polygon;

// парсер
void search_MinMax(vertex *verts);
int read_obj_file(char *filename, vertex *verts, polygon *poly);

void initialize_data(vertex *verts, polygon *poly);
void process_vertex_line(vertex *verts, char *line, float scaleFactor,
                         float centerX, float centerY, float centerZ);
void find_min_max(FILE *file, double *minMax, float *maxAbsValue);

int is_space(char ch);
int is_num(char ch);

int *find_nums_in_f(int *size_num_in_f, char *line, int pointers_size);
int number_reading_module(char *line, int *i);
void poly_add_values(polygon *poly, int *numbers_in_f, int all_points_in_poly,
                     int size_num_in_f);

void axis_moving(vertex *v, int axis_num, double prev_value, double value);

void axis_turn_oX(vertex *v, double a);
void axis_turn_oY(vertex *v, double a);
void axis_turn_oZ(vertex *v, double a);

void axis_scale(vertex *v, double result_scale);
