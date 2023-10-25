
#ifndef S21_STACK_H_
#define S21_STACK_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_operand {
  char oper;                  // символы
  int priority;               //приоритет
  struct stack_operand *next; // ссылка на след указатель
} stack_operand;

typedef struct stack_number {
  double number; // цифры
  struct stack_number *next;
} stack_number;

void push_number(stack_number **head, double number);
void push_operand(stack_operand **head, char oper, int priority);
int pop_operand(stack_operand **head);
int pop_number(stack_number **head, long double *number);
int peak_type(stack_operand **head);
#endif