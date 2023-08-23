#include "s21_grep.h"

int main(int argc, char **argv) {
  int erro = 0;
  char pattern[SIZE_PATTERN] = {0};
  flags flag = {0};
  if (argc > 2) {
    read_flags(argc, argv, &erro, &flag, pattern);
    if (erro != -1) {
      read_file(argc, argv, pattern, flag);
    }
  } else {
    printf("grep: option requires an argument -- e\n");
    printf(
        "usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] "
        "[-C[num]]\n");
    printf(
        "	[-e pattern] [-f file] [--binary-files=value] "
        "[--color=when]\n");
    printf(
        "	[--context[=num]] [--directories=action] [--label] "
        "[--line-buffered]\n");
    printf("	[--null] [pattern] [file ...]\n");
    erro = -1;
  }
  return 0;
}

void read_flags(int argc, char **argv, int *erro, flags *flag, char *pattern) {
  int opt = 0;
  while ((*erro != -1) &&
         (opt = getopt_long(argc, argv, "e:ivnclsh", NULL, NULL)) != -1) {
    switch (opt) {
      case 'e':
        flag->e = 1;
        strncat(pattern, optarg, SIZE_PATTERN - strlen(pattern) - 1);
        strncat(pattern, "|", SIZE_PATTERN - strlen(pattern) - 1);
        break;
      case 'i':
        flag->i = 1;
        break;
      case 'c':
        flag->c = 1;
        break;
      case 'n':
        flag->n = 1;
        break;
      case 'l':
        flag->l = 1;
        break;
      case 'v':
        flag->v = 1;
        break;
      case 's':
        flag->s = 1;
        break;
      case 'h':
        flag->h = 1;
        break;
      default:
        fprintf(stderr,
                "usage: s21_grep [-eivclnhsfo] [-e pattern] [-f file] "
                "[pattern] [file]\n");
        *erro = -1;
        continue;
    }
  }
  if (flag->e == 1) pattern[strlen(pattern) - 1] = '\0';

  if (!flag->e) {
    strcat(pattern, argv[optind++]);
  }
}

void read_file(int argc, char **argv, char *pattern, flags flag) {
  count_file = argc - optind;
  FILE *file = NULL;
  for (; optind < argc; optind++) {
    if ((file = fopen(argv[optind], "r")) != NULL) {
      process_file(argv, pattern, file, &count_file, flag);
      fclose(file);
    } else {
      if (!flag.s)
        fprintf(stderr, "%s: %s: No such file or directory\n", argv[0],
                argv[optind]);
    }
  }
}

void process_file(char **argv, char *pattern, FILE *file, int *count_file,
                  flags flag) {
  regex_t regex;
  int count_sovp = 0;
  int num_line = 1;
  char line[SIZE_LINE] = {0};
  int i_check = 0;

  if (flag.i) i_check = REG_ICASE;

  regcomp(&regex, pattern, REG_EXTENDED | i_check);
  while (!feof(file)) {
    if (fgets(line, SIZE_LINE, file)) {
      int sovpadenie = check_sovpadenie(line, &regex, flag);
      if (sovpadenie != REG_NOMATCH) {
        output(argv, line, &num_line, file, count_file, flag);
        count_sovp += 1;
      }
      num_line += 1;
    }
  }
  check_cl_flag(argv, &count_sovp, count_file, flag);
  regfree(&regex);
}

int check_sovpadenie(char *line, regex_t *regex, flags flag) {
  int sovpadenie = regexec(regex, line, 0, NULL, 0);
  if (flag.v) {
    if (sovpadenie == REG_NOMATCH) {
      sovpadenie = 0;
    } else {
      sovpadenie = REG_NOMATCH;
    }
  }
  return sovpadenie;
}

void output(char **argv, char *line, int *num_line, FILE *file, int *count_file,
            flags flag) {
  if (!flag.c && !flag.l) {
    if (*count_file > 1 && !flag.h) {
      printf("%s:", argv[optind]);
    }
    if (flag.n) {
      printf("%d:", *num_line);
    }
    printf("%s", line);
    if (feof(file)) {
      printf("\n");
    }
  }
}

void check_cl_flag(char **argv, int *count_sovp, int *count_file, flags flag) {
  if (flag.c) {
    if (*count_file > 1 && !flag.h) {
      printf("%s:", argv[optind]);
    }
    if (flag.l && *count_sovp) {
      printf("1\n");
    } else {
      printf("%d\n", *count_sovp);
    }
  }
  if (flag.l && *count_sovp) {
    printf("%s\n", argv[optind]);
  }
}