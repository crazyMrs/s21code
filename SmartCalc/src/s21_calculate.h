#ifndef S21_CALCULATE_H_
#define S21_CALCULATE_H_

#include <ctype.h>

#include "s21_stack.h"

long double simplecalc(double val1, double val2, char oper);
long double trigonomcalc(double val, char oper);
int input_str(char *str, long double *result);
int readoperand(char **str, char *oper);
int proccesoper(char **str, stack_number **numstack, stack_operand **operstack);
int calculation(stack_number **numstack, stack_operand **operstack);
int is_operator(char c);
int is_digit(char c);
int is_valid_operand(char c);
int is_valid_function(char c);
int is_valid_symbol(char c);
int checkstr(char *str);
int finish(stack_number **numstack, stack_operand **operstack, int error,
           long double *result);
int priority_func(char **str, char oper);

#endif