#include "model.h"

#include <ctype.h>

#include <cmath>
#include <cstring>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace s21 {

extern "C" {
    double InputStr(const char* input) {
        std::string str(input);
        ModelCalculator calc;
        return static_cast<double>(calc.InputStr(str));
    }
}

long double ModelCalculator::InputStr(std::string &str) {
  ClearStacks();

  if (CheckStr(str)) {
    if (str == "-") {
      stack_number_.push(0);
    }
    ProcessExpression(str);
    result_ = finish(str);
  } else {
    status_ = fError;
    result_ = std::numeric_limits<long double>::quiet_NaN();
  }

  return result_;
}

void ModelCalculator::ClearStacks() {
  while (!stack_number_.empty()) {
    stack_number_.pop();
  }
  while (!stack_operand_.empty()) {
    stack_operand_.pop();
  }
}

void ModelCalculator::ProcessExpression(const std::string &str) {
  std::string::const_iterator prev = str.begin();
  for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
    if (is_digit(*it) ||
        (*it == '-' && is_digit(*(std::next(it))) &&
         (*prev == '(' || it == str.begin())) ||
        *it == '.' || *it == 'e') {
      ProcessNumber(it, str);
    } else if (*it == ' ') {
      continue;
    } else {
      ProcessOperator(it, str);
    }
    prev = it;
  }
}

void ModelCalculator::ProcessNumber(std::string::const_iterator &it,
                                    const std::string &str) {
  if (*it == '-') {
    if (std::next(it) != str.end() && is_digit(*(std::next(it)))) {
      ProcessNegativeNumber(it);
    }
  } else {
    std::string digit;
    bool hasDecimalPoint = false;
    if (str == "e" || str == "(e)") {
      stack_number_.push(2.71828182846);
    } else {
      while (is_digit(*it) || *it == '.' || *it == 'e') {
        if (*it == 'e') {
          if (!is_digit(*(std::prev(it))) && *(std::next(it)) != '+' &&
              *(std::next(it)) != '-') {
            digit = "2.71828182846";
          }
          digit.push_back(*it++);
          if (*it == '+' || *it == '-') {
            digit.push_back(*it++);
          }
        }
        digit.push_back(*it++);
        if (*it == '.') {
          if (hasDecimalPoint) {
            status_ = fError;
            return;
          }
          hasDecimalPoint = true;
        }
      }
      *it--;
      try {
        stack_number_.push(std::stod(digit));
      } catch (const std::out_of_range &e) {
        status_ = fError;
      }
    }
  }
}

void ModelCalculator::ProcessNegativeNumber(std::string::const_iterator &it) {
  std::string digit;
  digit.push_back(*it++);
  while (is_digit(*it) || *it == '.') {
    digit.push_back(*it++);
  }
  *it--;
  try {
    stack_number_.push(std::stod(digit));
  } catch (const std::out_of_range &e) {
    status_ = fError;
  }
}

void ModelCalculator::ProcessOperator(std::string::const_iterator &it,
                                      const std::string &str) {
  if (*it == '(') {
    stack_operand_.push(*it);
  } else if (*it == ')') {
    ProcessClosingParenthesis(str);
  } else {
    FindOperand(it);
  }
}

void ModelCalculator::ProcessClosingParenthesis(const std::string &str) {
  while (!stack_operand_.empty() && stack_operand_.top() != '(' &&
         CheckStr(str)) {
    calculation();
  }
  if (!stack_operand_.empty()) {
    stack_operand_.pop();
  }
}

void ModelCalculator::FindOperand(std::string::const_iterator &str) {
  char oper;
  int priority = -1;
  std::string::const_iterator prev = str - 1;

  while (*prev == ' ') {
    prev--;
  }

  std::vector<std::string> operations = {
      "+",   "-",   "/",   "*",  "mod",  "%",    "^",    "cos",
      "sin", "tan", "log", "ln", "acos", "asin", "atan", "sqrt"};

  std::string operation = FindOperation(str, operations);
  if (!operation.empty()) {
    ReadOperand(operation, &oper);
    priority = PriorityFunc(oper);
    int skipChars = operation.size() - 1;
    int Check_prior = -1;
    if (!stack_operand_.empty()) {
      char top_operator = stack_operand_.top();
      Check_prior = PriorityFunc(top_operator);
    }

    while (!stack_operand_.empty() && Check_prior >= priority &&
           Check_prior != 6 && oper != '(') {
      if (oper == '^' && Check_prior == priority) {
        break;
      }
      calculation();
      if (!stack_operand_.empty()) {
        char top_operator = stack_operand_.top();
        Check_prior = PriorityFunc(top_operator);
      }
    }
    for (int i = 0; i < skipChars; ++i) {
      ++str;
    }
    stack_operand_.push(oper);
  } else {
    status_ = fError;
  }
}

std::string ModelCalculator::FindOperation(
    std::string::const_iterator &it,
    const std::vector<std::string> &operations) {
  std::string::const_iterator str_begin = it;
  for (const std::string &operation : operations) {
    if (std::equal(operation.begin(), operation.end(), it)) {
      it = str_begin;
      return operation;
    }
  }
  it = str_begin;
  return "";
}

int ModelCalculator::PriorityFunc(char oper) {
  int priority = -1;
  if (oper == '+' || oper == '-') priority = 0;
  if (oper == '*' || oper == '/') priority = 1;
  if (oper == 'm' || oper == '%') priority = 2;
  if (oper == '^') priority = 3;
  if (oper == 'c' || oper == 's' || oper == 't' || oper == 'l' || oper == 'A' ||
      oper == 'S' || oper == 'T' || oper == 'Q' || oper == 'L')
    priority = 4;
  if (oper == '(') priority = 6;
  return priority;
}

enum Status ModelCalculator::ReadOperand(std::string &str, char *oper) {
  if (str == "+") {
    *oper = '+';
  } else if (str == "-") {
    *oper = '-';
  } else if (str == "/") {
    *oper = '/';
  } else if (str == "*") {
    *oper = '*';
  } else if ((str == "mod") || (str == "%")) {
    *oper = 'm';
  } else if (str == "^") {
    *oper = '^';
  } else if (str.substr(0, 3) == "cos") {
    *oper = 'c';
  } else if (str.substr(0, 3) == "sin") {
    *oper = 's';
  } else if (str.substr(0, 3) == "tan") {
    *oper = 't';
  } else if (str.substr(0, 3) == "log") {
    *oper = 'l';
  } else if (str.substr(0, 2) == "ln") {
    *oper = 'L';
  } else if (str.substr(0, 4) == "acos") {
    *oper = 'A';
  } else if (str.substr(0, 4) == "asin") {
    *oper = 'S';
  } else if (str.substr(0, 4) == "atan") {
    *oper = 'T';
  } else if (str.substr(0, 4) == "sqrt") {
    *oper = 'Q';
  } else {
    status_ = fError;
  }
  return status_;
}

void ModelCalculator::calculation() {
  if (!stack_number_.empty()) {
    long double num1 = 0;
    long double num2 = stack_number_.top();
    char oper = 0;
    stack_number_.pop();
    if (!stack_operand_.empty()) {
      oper = stack_operand_.top();
      stack_operand_.pop();
    }
    long double result;

    if (strchr("/+-*m^", oper) && !stack_number_.empty()) {
      num1 = stack_number_.top();
      stack_number_.pop();
    }

    if ((oper == '/' || oper == 'm') && num2 == 0) {
      status_ = fError;
      return;
    }

    if (strchr("/m", oper) && num2 == 0) num2 = -1;

    if (oper == '+' || oper == '-' || oper == '*' || oper == '/' ||
        oper == '^' || oper == 'm' || oper == '%') {
      result = SimpleCalculate(num2, num1, oper);
    } else if (oper == 'c' || oper == 's' || oper == 't' || oper == 'A' ||
               oper == 'S' || oper == 'T' || oper == 'Q' || oper == 'L' ||
               oper == 'l') {
      result = TrigonomCalculate(num2, oper);
    }

    stack_number_.push(result);
  } else {
    status_ = fError;
    return;
  }
}

long double ModelCalculator::finish(std::string &str) {
  while (!stack_operand_.empty() && CheckStr(str)) {
    calculation();
  }

  if (CheckStr(str)) {
    result_ = stack_number_.top();
    stack_number_.pop();
  }

  return result_;
}


long double ModelCalculator::SimpleCalculate(double val1, double val2, const char oper) {
  long double res = -1;

  if (oper == '+') {
    res = val2 + val1;
  } else if (oper == '-') {
    res = val2 - val1;
  } else if (oper == '/') {
    if (val1 == 0) {
      if (val2 > 0) {
        res = std::numeric_limits<long double>::infinity();
      } else {
        res = -std::numeric_limits<long double>::infinity();
      }
    } else {
      res = val2 / val1;
    }
  } else if (oper == '*') {
    res = val1 * val2;
  } else if (oper == '^') {
    res = powl(val2, val1);
  } else if (oper == 'm' || oper == '%') {
    res = fmod(val2, val1);
  } else {
    throw std::invalid_argument("Error simple operand");
  }

  if (std::isinf(res)) {
    res = std::numeric_limits<long double>::infinity();
  } else if (res > std::numeric_limits<long double>::max()) {
    res = std::numeric_limits<long double>::infinity();
  } else if (res < -std::numeric_limits<long double>::max()) {
    res = -std::numeric_limits<long double>::infinity();
  }

  return res;
}

long double ModelCalculator::TrigonomCalculate(double val, char oper) {
  long double res = -1;

  if (oper == 'c') {
    res = std::cos(val);
  } else if (oper == 's') {
    res = std::sin(val);
  } else if (oper == 't') {
    res = std::tan(val);
  } else if (oper == 'A') {
    res = std::acos(val);
  } else if (oper == 'S') {
    res = std::asin(val);
  } else if (oper == 'T') {
    res = std::atan(val);
  } else if (oper == 'Q') {
    res = std::sqrt(val);
  } else if (oper == 'L') {
    res = std::log(val);
  } else if (oper == 'l') {
    res = std::log10(val);
  } else {
    throw std::invalid_argument("Error trigonometric operand");
  }
  return res;
}

bool ModelCalculator::is_digit(char c) noexcept { return c >= '0' && c <= '9'; }

bool ModelCalculator::CheckStr(const std::string &str) noexcept {
  if (str.empty()) {
    status_ = fError;
    return false;
  }
  int bracket = 0;
  char prev = 0;

  for (char ch : str) {
    if (!isspace(ch)) {
      if (!CheckValidCharacter(ch)) status_ = fError;
      if (!CheckBracket(bracket, ch)) status_ = fError;
      if (!CheckConsecutiveOperators(prev, ch)) status_ = fError;
      if (ch == 'e' && !is_digit(prev)) status_ = fError;
    }
    prev = ch;
  }

  if (!CheckLastCharacter(prev)) status_ = fError;
  if (!CheckBracketBalance(bracket)) status_ = fError;
  if (str.find("()") != std::string::npos) status_ = fError;

  return status_ == fOk;
}

bool ModelCalculator::CheckValidCharacter(char ch) noexcept {
  return strchr("sincoqrtalmdg.-+x()*/+-%^e", ch) || isdigit(ch);
}

bool ModelCalculator::CheckBracket(int &bracket, char ch) noexcept {
  if (ch == '(') {
    bracket++;
  } else if (ch == ')') {
    bracket--;
    if (bracket < 0) return false;
  }
  return true;
}

bool ModelCalculator::CheckConsecutiveOperators(char prev, char ch) noexcept {
  return !((strchr("/*^m)", ch) && strchr("+-/*m^", prev)) ||
           (strchr("*", ch) && strchr("(", prev)));
}

bool ModelCalculator::CheckLastCharacter(char prev) noexcept {
  return strchr(")x", prev) || isdigit(prev) || "e";
}

bool ModelCalculator::CheckBracketBalance(int bracket) noexcept {
  return bracket == 0;
}

};  // namespace s21
