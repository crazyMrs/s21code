#include "s21_stack.h"

// добавляет новые значания в вершину стека
void push_number(stack_number **head, double number) {
  stack_number *new_number = (stack_number *)malloc(sizeof(stack_number));
  new_number->number = number;
  new_number->next = (*head);
  (*head) = new_number;
}

void push_operand(stack_operand **head, char oper, int priority) {
  stack_operand *new_operand = (stack_operand *)malloc(sizeof(stack_operand));
  new_operand->oper = oper;
  new_operand->priority = priority;
  new_operand->next = *head;
  *head = new_operand;
}

// удаляет и возвращает значение из вершины стека
int pop_operand(stack_operand **head) {
  int error = 0;
  if (*head != NULL) {
    stack_operand *to_out = *head;
    *head = (*head)->next;
    error = to_out->oper;
    free(to_out);
  } else {
    error = -1;
  }
  return error;
}

int pop_number(stack_number **head, long double *number) {
  int error = 0;
  if (*head) {
    stack_number *to_out = (*head);
    (*head) = (*head)->next;
    *number = to_out->number;
    free(to_out);
  } else
    error = -1;
  return error;
}

// возвращает приоритет операнда вершины стека
int peak_type(stack_operand **head) {
  int error = 0;
  if (*head != 0) {
    error = (*head)->priority;
  } else
    error = -1;
  return error;
}