#ifndef CAT_H
#define CAT_H

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int b, e, n, s, t, v;
} FLAGS;

void open_file(char** argv, FLAGS flag);
void read_file(FLAGS flag, FILE* file);

#endif