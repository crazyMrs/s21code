#include "s21_calculate.h"

long double simplecalc(double val1, double val2, char oper) {
  long double res = -1;

  if (oper == '+') {
    res = val1 + val2;
  } else if (oper == '-') {
    res = val2 - val1;
  } else if (oper == '/') {
    res = val2 / val1;
  } else if (oper == '*') {
    res = val1 * val2;
  } else if (oper == '^') {
    res = powl(val2, val1);
  } else if (oper == 'm' || oper == '%') {
    res = fmod(val2, val1);
  } else {
    printf("Error simple operand");
  }
  return res;
}

long double trigonomcalc(double val, char oper) {
  long double res = -1;

  if (oper == 'c') {
    res = cosl(val);
  } else if (oper == 's') {
    res = sinl(val);
  } else if (oper == 't') {
    res = tanl(val);
  } else if (oper == 'A') {
    res = acosl(val);
  } else if (oper == 'S') {
    res = asinl(val);
  } else if (oper == 'T') {
    res = atanl(val);
  } else if (oper == 'Q') {
    res = sqrtl(val);
  } else if (oper == 'L') {
    res = logl(val);
  } else if (oper == 'l') {
    res = log10l(val);
  } else {
    printf("Error trigonometric operand");
  }
  return res;
}

int input_str(char *str, long double *result) {
  stack_number *numstack = NULL;
  stack_operand *operstack = NULL;
  int error = checkstr(str);

  if (*str == '-')
    push_number(&numstack, 0);

  while (*str != '\0' && !error) {
    if (is_digit(*str)) {
      long double number = strtold(str, &str);
      push_number(&numstack, number);
    } else {
      if (*str == '(') {
        push_operand(&operstack, *str, 6);
      } else if (*str == ')') {
        while (operstack->oper != '(' && !error)
          error = calculation(&numstack, &operstack);
        pop_operand(&operstack);
      } else if (*str != ' ') {
        if (*str == 'x') {
          long double x_num = strtold(str, &str);
          push_number(&numstack, x_num);
        } else {
          error = proccesoper(&str, &numstack, &operstack);
        }
      }
      str++;
    }
  }

  if (!error) {
    error = finish(&numstack, &operstack, error, result);
  }

  free(numstack);
  free(operstack);

  return error;
}

int readoperand(char **str, char *oper) {
  int result = 0;
  if (strchr("+", **str)) {
    *oper = '+';
  } else if (strchr("-", **str)) {
    *oper = '-';
  } else if (strchr("/", **str)) {
    *oper = '/';
  } else if (strchr("*", **str)) {
    *oper = '*';
  } else if (strchr("mod", **str) || strchr("%", **str)) {
    *oper = 'm';
  } else if (strchr("^", **str)) {
    *oper = '^';
  } else if (!strncmp(*str, "cos", 3)) {
    *oper = 'c';
  } else if (!strncmp(*str, "sin", 3)) {
    *oper = 's';
  } else if (!strncmp(*str, "tan", 3)) {
    *oper = 't';
  } else if (!strncmp(*str, "log", 3)) {
    *oper = 'l';
  } else if (!strncmp(*str, "ln", 2)) {
    *oper = 'L';
  } else if (!strncmp(*str, "acos", 4)) {
    *oper = 'A';
  } else if (!strncmp(*str, "asin", 4)) {
    *oper = 'S';
  } else if (!strncmp(*str, "atan", 4)) {
    *oper = 'T';
  } else if (!strncmp(*str, "sqrt", 4)) {
    *oper = 'Q';
  } else {
    result = -1;
  }

  return result;
}

int proccesoper(char **str, stack_number **numstack,
                stack_operand **operstack) {
  int error = 0;
  char oper = 0;
  int priority = -1;

  char *prev = *str - 1;
  while (*prev == ' ') {
    prev--;
  }
  if ((**str == '-') && (strchr("-(", *prev)))
    push_number(numstack, 0);

  error = readoperand(str, &oper);
  if (error == 0) {
    priority = priority_func(str, oper);

    int check_prior = peak_type(operstack);
    while (check_prior >= priority && check_prior != 6) {
      if (oper == '^' && check_prior == priority) {
        break;
      }
      error = calculation(numstack, operstack);
      check_prior = peak_type(operstack);
    }

    push_operand(operstack, oper, priority);
  }
  return error;
}

int priority_func(char **str, char oper) {
  int priority = -1;
  if (oper == '+' || oper == '-')
    priority = 0;
  if (oper == '*' || oper == '/')
    priority = 1;
  if (oper == 'm') {
    priority = 2;
    if (*(*str + 1) == 'o' && *(*str + 2) == 'd')
      *str += 2;
  }
  if (oper == '^')
    priority = 3;
  if (oper == 'c' || oper == 's' || oper == 't' || oper == 'l' || oper == 'A' ||
      oper == 'S' || oper == 'T' || oper == 'Q' || oper == 'L') {
    priority = 4;
    if (oper == 'c' || oper == 's' || oper == 't' || oper == 'l' || oper == 'm')
      *str += 2;
    if (oper == 'A' || oper == 'S' || oper == 'T' || oper == 'Q')
      *str += 3;
    if (oper == 'L')
      *str += 1;
  }
  if (oper == '(')
    priority = 6;
  return priority;
}

int calculation(stack_number **numstack, stack_operand **operstack) {
  long double num1 = 0, num2 = 0;
  long double number = pop_number(numstack, &num2);
  char oper = pop_operand(operstack);
  long double result;

  if (strchr("/+-*m^", oper))
    pop_number(numstack, &num1);
  if (strchr("/m", oper) && num2 == 0)
    number = -1;

  if (oper == 43 || oper == 42 || oper == 45 || oper == 47 || oper == 94 ||
      oper == 37 || oper == 109) {
    result = simplecalc(num2, num1, oper);
  } else {
    result = trigonomcalc(num2, oper);
  }

  push_number(numstack, result);

  return number;
}

int finish(stack_number **numstack, stack_operand **operstack, int error,
           long double *result) {
  while (*operstack && !error) {
    error = calculation(numstack, operstack);
  }
  if (!error)
    pop_number(numstack, result);
  else
    *result = 0;
  return error;
}

// проверка строки
int is_digit(char c) { return c >= '0' && c <= '9'; }

int checkstr(char *str) {
  int bracket = 0, error = 0;
  char prev = 0;

  while (*str) {
    if (!isspace(*str)) {
      if (*str == '(') {
        bracket++;
      } else if (*str == ')') {
        bracket--;
        if (bracket < 0)
          error = -1;
      }

      if (!strchr("sincoqrtalmdg.-+x()*/+-%^", *str) && !isdigit(*str)) {
        error = -1;
      }

      if (strchr("/*^m)", *str) && strchr("+-(/*m^", prev))
        error = -1;
      if (strchr("*", *str) && strchr("(", prev))
        error = -1;

      prev = *str;
    }
    str++;
  }

  if (!strchr(")x", prev) && !isdigit(prev))
    error = -1;
  if (bracket != 0)
    error = -1;

  return error;
}