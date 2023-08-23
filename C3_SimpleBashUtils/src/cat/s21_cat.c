#include "cat.h"

FLAGS read_flags(int argc, char** argv) {
  static struct option long_oprions[] = {{"number-nonblank", 0, NULL, 'b'},
                                         {"number", 0, NULL, 'n'},
                                         {"squeeze-blank", 0, NULL, 's'},
                                         {NULL, 0, NULL, 0}};
  FLAGS flag = {0};
  int f = 0;
  while (f != -1) {
    f = getopt_long(argc, argv, "+beEnstTv", long_oprions, NULL);
    if (f == -1) break;
    switch (f) {
      case 'b':
        flag.b = 1;
        break;
      case 'e':
        flag.e = 1;
        flag.v = 1;
        break;
      case 'E':
        flag.e = 1;
        break;
      case 'n':
        flag.n = 1;
        break;
      case 's':
        flag.s = 1;
        break;
      case 't':
        flag.t = 1;
        flag.v = 1;
        break;
      case 'T':
        flag.t = 1;
        break;
      case 'v':
        flag.v = 1;
        break;
      default:
        printf("usage: cat [-benstuv] [file ...]\n");
        break;
    }
  }
  return flag;
}

void open_file(char** argv, FLAGS flag) {
  FILE* file = fopen(argv[optind], "r");
  if (!file) {
    printf("cat: %s: %s\n", argv[optind], strerror(errno));
  } else {
    read_file(flag, file);
    fclose(file);
  }
}

void read_file(FLAGS flag, FILE* file) {
  int symbol, prev = '\n', duplicate = 0, count = 1, first = 1;
  while ((symbol = fgetc(file)) != EOF) {
    if (flag.s) {
      if (symbol == '\n' && first) duplicate = duplicate + 1;
      if (symbol == '\n') duplicate++;
      if (symbol != '\n') duplicate = 0;
    }
    if (symbol == '\n' && (!flag.s || duplicate < 3)) {
      if (flag.n && prev == '\n' && !flag.b) printf("%6d\t", count++);
      if (flag.e) printf("$");
      printf("%c", symbol);
    }
    if (symbol != '\n') {
      if ((prev == '\n' || first == 1) && (flag.n || flag.b))
        printf("%6d\t", count++);
      if (symbol < 32 && symbol != 9 && symbol != 10 && flag.v)
        printf("^%c", symbol + 64);
      else if (symbol > 127 && symbol < 160 && flag.v)
        printf("M-^%c", symbol - 64);
      else if (symbol == 127 && flag.v)
        printf("^%c", symbol - 64);
      else if (symbol == '\t' && flag.t)
        printf("^I");
      else
        printf("%c", symbol);
    }
    prev = symbol;
    first = 0;
  }
}

int main(int argc, char** argv) {
  FLAGS flag = read_flags(argc, argv);
  while (optind < argc) {
    open_file(argv, flag);
    optind++;
  }
  return 0;
}
