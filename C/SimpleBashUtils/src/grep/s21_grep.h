#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#define SIZE_PATTERN 8192
#define SIZE_LINE 4096

typedef struct {
  int e, i, v, n, c, l, s, h;
} flags;

int count_file = 0;

void read_flags(int argc, char **argv, int *erro, flags *flag, char *pattern);
void read_file(int argc, char **argv, char *pattern, flags flag);
void process_file(char **argv, char *pattern, FILE *file, int *count_file,
                  flags flag);
int check_sovpadenie(char *line, regex_t *regex, flags flag);
void output(char **argv, char *line, int *num_line, FILE *file, int *count_file,
            flags flag);
void check_cl_flag(char **argv, int *count_sovp, int *count_file, flags flag);

#endif